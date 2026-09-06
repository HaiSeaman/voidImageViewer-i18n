//
// Copyright 2025 voidtools / David Carpenter
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// wic layer - HEIC/HEIF support via the Windows Imaging Component.
//
// WIC (Windows Imaging Component, Vista+) can decode HEIC/HEIF when the
// "HEIF Image Extensions" component is installed (built into Windows 10
// 1809+ and Windows 11). Pixels are delivered to the caller as RGBA,
// matching the webp layer, so the viv frame pipeline can be shared.

#include "viv.h"
#include <wincodec.h>

// returns 1 when the given WIC pixel format carries an alpha channel.
static int _wic_pixel_format_has_alpha(const WICPixelFormatGUID *format)
{
	// formats known not to have alpha.
	if (IsEqualGUID(format,&GUID_WICPixelFormat24bppBGR) ||
		IsEqualGUID(format,&GUID_WICPixelFormat24bppRGB) ||
		IsEqualGUID(format,&GUID_WICPixelFormat48bppRGB) ||
		IsEqualGUID(format,&GUID_WICPixelFormat48bppBGR) ||
		IsEqualGUID(format,&GUID_WICPixelFormat8bppGray) ||
		IsEqualGUID(format,&GUID_WICPixelFormat16bppGray) ||
		IsEqualGUID(format,&GUID_WICPixelFormat32bppGrayFloat) ||
		IsEqualGUID(format,&GUID_WICPixelFormat16bppBGR565) ||
		IsEqualGUID(format,&GUID_WICPixelFormat1bppIndexed) ||
		IsEqualGUID(format,&GUID_WICPixelFormat2bppIndexed) ||
		IsEqualGUID(format,&GUID_WICPixelFormat4bppIndexed) ||
		IsEqualGUID(format,&GUID_WICPixelFormat8bppIndexed))
	{
		return 0;
	}

	// everything else (including unknown formats) is treated as having
	// alpha: viv blends semi-transparent pixels against the background
	// color and fully opaque pixels are unaffected, so this is the safe
	// default.
	return 1;
}

int wic_load(IStream *stream,void *user_data,int (*info_callback)(void *user_data,DWORD frame_count,DWORD wide,DWORD high,int has_alpha),int (*frame_callback)(void *user_data,BYTE *pixels,int delay))
{
	IWICImagingFactory *factory;
	IWICBitmapDecoder *decoder;
	IWICBitmapFrameDecode *frame;
	IWICFormatConverter *converter;
	WICPixelFormatGUID pixel_format;
	UINT frame_count;
	UINT wide;
	UINT high;
	UINT stride;
	UINT buffer_size;
	BYTE *buffer;
	HRESULT hr;
	int ret;
	VIV_UINT64 size64;

	ret = 0;
	factory = NULL;
	decoder = NULL;
	frame = NULL;
	converter = NULL;
	buffer = NULL;

	if (!stream)
	{
		return 0;
	}

	// GDI+ may have left the stream anywhere; WIC reads from the start.
	{
		LARGE_INTEGER li;

		li.QuadPart = 0;
		if (FAILED(IStream_Seek(stream,li,STREAM_SEEK_SET,NULL)))
		{
			return 0;
		}
	}

	hr = CoCreateInstance(&CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,&IID_IWICImagingFactory,(LPVOID*)&factory);
	if (FAILED(hr))
	{
		debug_printf("CoCreateInstance IWICImagingFactory %08x\n",hr);
		return 0;
	}

	hr = IWICImagingFactory_CreateDecoderFromStream(factory,stream,NULL,WICDecodeMetadataCacheOnDemand,&decoder);
	if (FAILED(hr))
	{
		// no decoder available (eg: HEIF image extensions not installed).
		debug_printf("IWIC CreateDecoderFromStream %08x\n",hr);
		goto done;
	}

	// only the first frame is decoded (HEIC sequences are rare; GIF/WebP
	// animation is already handled by GDI+/libwebp before we get here).
	if (FAILED(IWICBitmapDecoder_GetFrameCount(decoder,&frame_count)))
	{
		frame_count = 0;
	}

	if (!frame_count)
	{
		goto done;
	}

	hr = IWICBitmapDecoder_GetFrame(decoder,0,&frame);
	if (FAILED(hr))
	{
		debug_printf("IWIC GetFrame %08x\n",hr);
		goto done;
	}

	if (FAILED(IWICBitmapFrameDecode_GetSize(frame,&wide,&high)))
	{
		goto done;
	}

	if ((!wide) || (!high))
	{
		goto done;
	}

	// refuse absurdly large frames (32-bit stride/buffer arithmetic below).
	size64 = (VIV_UINT64)wide * (VIV_UINT64)high * 4;
	if (size64 > 0x7fffffff)
	{
		debug_printf("wic: frame too large %ux%u\n",wide,high);
		goto done;
	}

	if (FAILED(IWICBitmapFrameDecode_GetPixelFormat(frame,&pixel_format)))
	{
		goto done;
	}

	stride = wide * 4;
	buffer_size = stride * high;
	buffer = (BYTE *)mem_alloc(buffer_size);
	if (!buffer)
	{
		goto done;
	}

	// HEIC decoders usually deliver 32bppBGRA directly; skip the format
	// converter (a full pixel conversion) in that common case.
	if (IsEqualGUID(&pixel_format,&GUID_WICPixelFormat32bppBGRA))
	{
		hr = IWICBitmapFrameDecode_CopyPixels(frame,NULL,stride,buffer_size,buffer);
		if (FAILED(hr))
		{
			debug_printf("IWIC CopyPixels %08x\n",hr);
			goto done;
		}
	}
	else
	{
		hr = IWICImagingFactory_CreateFormatConverter(factory,&converter);
		if (SUCCEEDED(hr))
		{
			hr = IWICFormatConverter_Initialize(converter,(IWICBitmapSource *)frame,&GUID_WICPixelFormat32bppBGRA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeMedianCut);
		}

		if (SUCCEEDED(hr))
		{
			hr = IWICFormatConverter_CopyPixels(converter,NULL,stride,buffer_size,buffer);
		}

		if (FAILED(hr))
		{
			debug_printf("IWIC FormatConverter %08x\n",hr);
			goto done;
		}
	}

	// WIC delivers BGRA; the viv frame pipeline expects RGBA (like webp).
	{
		BYTE *p;
		DWORD run;

		run = (DWORD)wide * high;
		p = buffer;

		while(run)
		{
			BYTE b;

			b = p[0];
			p[0] = p[2];
			p[2] = b;

			p += 4;
			run--;
		}
	}

	if (info_callback(user_data,1,wide,high,_wic_pixel_format_has_alpha(&pixel_format)))
	{
		if (frame_callback(user_data,buffer,0))
		{
			ret = 1;
		}
	}

done:
	if (buffer)
	{
		mem_free(buffer);
	}

	if (converter)
	{
		IWICFormatConverter_Release(converter);
	}

	if (frame)
	{
		IWICBitmapFrameDecode_Release(frame);
	}

	if (decoder)
	{
		IWICBitmapDecoder_Release(decoder);
	}

	IWICImagingFactory_Release(factory);

	return ret;
}
