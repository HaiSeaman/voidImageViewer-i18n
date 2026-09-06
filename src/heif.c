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
// heif layer - HEIC/HEIF support via libheif.
//
// libheif (with the libde265 HEVC decoder) decodes HEIC/HEIF entirely
// in-process, so the viewer works even when the system "HEIF Image
// Extensions" component is not installed. Pixels are delivered to the
// caller as RGBA, matching the webp/wic layers, so the viv frame pipeline
// can be shared.

#include "viv.h"

// libheif is linked as a static library; without this the headers declare
// the API as dllimport and the linker looks for __imp_heif_* symbols.
#define LIBHEIF_STATIC_BUILD
#include <libheif/heif.h>

// libde265 was built against the DLL ucrt and references the dllimport
// forms of the aligned allocation functions, which the static CRT does
// not provide. Supply them locally (the viewer is /MT and does not link
// ucrt.lib).
void * __cdecl __imp__aligned_malloc(size_t size,size_t alignment)
{
	void *raw;
	void **aligned;

	if (alignment < sizeof(void *))
	{
		alignment = sizeof(void *);
	}

	raw = HeapAlloc(GetProcessHeap(),0,size + alignment + sizeof(void *));
	if (!raw)
	{
		return NULL;
	}

	aligned = (void **)((((uintptr_t)raw + sizeof(void *) + alignment - 1) & ~(uintptr_t)(alignment - 1)));
	aligned[-1] = raw;

	return aligned;
}

void __cdecl __imp__aligned_free(void *p)
{
	if (p)
	{
		HeapFree(GetProcessHeap(),0,((void **)p)[-1]);
	}
}

// reads the EXIF orientation tag (274) out of the file in the stream.
// returns 1-8, or 0 when there is no usable orientation.
int heif_get_orientation(IStream *stream)
{
	int ret;
	HGLOBAL hglobal;
	void *data_ptr;
	SIZE_T data_size;
	struct heif_context *ctx;
	struct heif_image_handle *handle;
	heif_item_id ids[8];
	int id_count;
	
	ret = 0;
	hglobal = 0;
	ctx = 0;
	handle = 0;

	if (!stream)
	{
		return 0;
	}

	if (FAILED(GetHGlobalFromStream(stream,&hglobal)))
	{
		return 0;
	}

	data_ptr = GlobalLock(hglobal);
	if (!data_ptr)
	{
		return 0;
	}

	data_size = GlobalSize(hglobal);

	ctx = heif_context_alloc();
	if (ctx)
	{
		struct heif_error err;

		err = heif_context_read_from_memory_without_copy(ctx,data_ptr,data_size,NULL);
		if (err.code == heif_error_Ok)
		{
			err = heif_context_get_primary_image_handle(ctx,&handle);
			if ((err.code == heif_error_Ok) && handle)
			{
				int i;

				id_count = heif_image_handle_get_list_of_metadata_block_IDs(handle,"Exif",ids,8);
				for(i=0;i<id_count;i++)
				{
					size_t size;
					void *data;

					size = heif_image_handle_get_metadata_size(handle,ids[i]);
					if ((size > 8) && (size < 1024 * 1024))
					{
						data = mem_alloc(size);
						if (data)
						{
							heif_error merr = heif_image_handle_get_metadata(handle,ids[i],data);
							if (merr.code == heif_error_Ok)
							{
								// the first 4 bytes (big-endian) are the
								// offset to the start of the TIFF header.
								{
									BYTE *p;
									int offset;

									p = (BYTE *)data;
									offset = (int)(((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16) | ((unsigned int)p[2] << 8) | p[3]);
									if ((offset >= 4) && ((size_t)offset < size))
									{
										BYTE *tiff;
										size_t tiff_size;

										tiff = p + offset;
										tiff_size = size - offset;

										// TIFF header: byte order + magic 42 + IFD0 offset.
										if ((tiff_size >= 8) &&
											(((tiff[0] == 'I') && (tiff[1] == 'I')) || ((tiff[0] == 'M') && (tiff[1] == 'M'))))
										{
											int little_endian;
											int ifd0_offset;
											int tag_count;
											int ti;

											little_endian = (tiff[0] == 'I');
											if (((little_endian ? tiff[2] : tiff[3]) == 42) && ((little_endian ? tiff[3] : tiff[2]) == 0))
											{
												ifd0_offset = little_endian ? (tiff[4] | (tiff[5] << 8) | (tiff[6] << 16) | (tiff[7] << 24))
																			  : (tiff[7] | (tiff[6] << 8) | (tiff[5] << 16) | (tiff[4] << 24));

												if ((ifd0_offset >= 0) && ((size_t)ifd0_offset + 2 <= tiff_size))
												{
													BYTE *ifd;
													size_t ifd_size;

													ifd = tiff + ifd0_offset;
													ifd_size = tiff_size - ifd0_offset;

													tag_count = little_endian ? (ifd[0] | (ifd[1] << 8)) : (ifd[1] | (ifd[0] << 8));

													for(ti=0;ti<tag_count;ti++)
													{
														int entry_off;
														int tag;
														int type;
														int value;

														entry_off = 2 + ti * 12;
														if ((size_t)entry_off + 12 > ifd_size)
														{
															break;
														}

														tag = little_endian ? (ifd[entry_off] | (ifd[entry_off+1] << 8)) : (ifd[entry_off+1] | (ifd[entry_off] << 8));
														type = little_endian ? (ifd[entry_off+2] | (ifd[entry_off+3] << 8)) : (ifd[entry_off+3] | (ifd[entry_off+2] << 8));

														// tag 274 (Orientation), type 3 (SHORT), value 1-8
														if (tag == 274)
														{
															value = little_endian ? (ifd[entry_off+8] | (ifd[entry_off+9] << 8)) : (ifd[entry_off+9] | (ifd[entry_off+8] << 8));
															if ((value >= 1) && (value <= 8))
															{
																ret = value;
															}
															break;
														}

														(void)type;
													}
												}
											}
										}
									}
								}
							}

							mem_free(data);
						}
					}

					if (ret)
					{
						break;
					}
				}
			}

			if (handle)
			{
				heif_image_handle_release(handle);
			}
		}

		heif_context_free(ctx);
	}

	GlobalUnlock(hglobal);

	return ret;
}

int heif_load(IStream *stream,void *user_data,int (*info_callback)(void *user_data,DWORD frame_count,DWORD wide,DWORD high,int has_alpha),int (*frame_callback)(void *user_data,BYTE *pixels,int delay))
{
	int ret;
	HGLOBAL hglobal;
	void *data_ptr;
	SIZE_T data_size;
	struct heif_context *ctx;
	struct heif_image_handle *handle;
	struct heif_image *image;

	ret = 0;
	ctx = 0;
	handle = 0;
	image = 0;

	if (!stream)
	{
		return 0;
	}

	if (FAILED(GetHGlobalFromStream(stream,&hglobal)))
	{
		return 0;
	}

	data_ptr = GlobalLock(hglobal);
	if (!data_ptr)
	{
		return 0;
	}

	data_size = GlobalSize(hglobal);

	ctx = heif_context_alloc();
	if (!ctx)
	{
		GlobalUnlock(hglobal);
		return 0;
	}

	{
		struct heif_error err;

		// the memory is owned by the caller and stays valid for the whole
		// synchronous decode, so zero-copy reading is safe here.
		err = heif_context_read_from_memory_without_copy(ctx,data_ptr,data_size,NULL);
		if (err.code != heif_error_Ok)
		{
			debug_printf("libheif read %s\n",err.message);
			goto done;
		}

		err = heif_context_get_primary_image_handle(ctx,&handle);
		if ((err.code != heif_error_Ok) || (!handle))
		{
			debug_printf("libheif get primary %s\n",err.message);
			goto done;
		}
	}

	{
		int image_wide;
		int image_high;
		int has_alpha;

		image_wide = heif_image_handle_get_width(handle);
		image_high = heif_image_handle_get_height(handle);
		has_alpha = heif_image_handle_has_alpha_channel(handle);

		if ((image_wide <= 0) || (image_high <= 0))
		{
			goto done;
		}

		// refuse absurdly large images (32-bit stride/buffer arithmetic below).
		if ((VIV_UINT64)image_wide * (VIV_UINT64)image_high * 4 > 0x7fffffff)
		{
			debug_printf("libheif: image too large %dx%d\n",image_wide,image_high);
			goto done;
		}

		if (info_callback(user_data,1,image_wide,image_high,has_alpha))
		{
			struct heif_error err;

			err = heif_decode_image(handle,&image,heif_colorspace_RGB,heif_chroma_interleaved_RGBA,NULL);
			if (err.code == heif_error_Ok)
			{
				const uint8_t *plane;
				int stride;
				BYTE *buffer;
				DWORD buffer_size;
				int y;

				plane = heif_image_get_plane_readonly(image,heif_channel_interleaved,&stride);
				if (plane)
				{
					buffer_size = (DWORD)image_wide * (DWORD)image_high * 4;
					buffer = (BYTE *)mem_alloc(buffer_size);
					if (buffer)
					{
						// libheif may pad each row; copy row by row into a
						// tightly packed RGBA buffer for the viv pipeline.
						if (stride == image_wide * 4)
						{
							os_copy_memory(buffer,plane,buffer_size);
						}
						else
						{
							for(y=0;y<image_high;y++)
							{
								os_copy_memory(buffer + (size_t)y * image_wide * 4,plane + (size_t)y * stride,image_wide * 4);
							}
						}

						if (frame_callback(user_data,buffer,0))
						{
							ret = 1;
						}

						mem_free(buffer);
					}
				}
			}
			else
			{
				debug_printf("libheif decode %s\n",err.message);
			}
		}
	}

done:
	if (image)
	{
		heif_image_release(image);
	}

	if (handle)
	{
		heif_image_handle_release(handle);
	}

	if (ctx)
	{
		heif_context_free(ctx);
	}

	GlobalUnlock(hglobal);

	return ret;
}
