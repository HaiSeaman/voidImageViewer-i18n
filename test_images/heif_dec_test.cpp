// Minimal console harness: decodes a HEIC/HEIF file with the exact same
// libheif API sequence as src/heif.c (heif_load) and dumps the tightly
// packed RGBA rows for x86/x64 comparison. GUI-free verification only.

#define LIBHEIF_STATIC_BUILD
#include <libheif/heif.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// same shims as src/heif.c: libde265 was built against the DLL ucrt and
// imports these through __imp_*, which a static-CRT app must provide.
static void * __cdecl __imp__aligned_malloc(size_t size, size_t alignment)
{
	void *raw;
	void **aligned;

	if (alignment < sizeof(void *))
	{
		alignment = sizeof(void *);
	}

	raw = HeapAlloc(GetProcessHeap(), 0, size + alignment + sizeof(void *));
	if (!raw)
	{
		return NULL;
	}

	aligned = (void **)((((uintptr_t)raw + sizeof(void *) + alignment - 1) & ~(uintptr_t)(alignment - 1)));
	aligned[-1] = raw;

	return aligned;
}

static void __cdecl __imp__aligned_free(void *p)
{
	if (p)
	{
		HeapFree(GetProcessHeap(), 0, ((void **)p)[-1]);
	}
}

// report the faulting address before dying, so the crash site can be
// mapped back to a function through the .map file.
static LONG CALLBACK _crash_report(EXCEPTION_POINTERS *ep)
{
	uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	uintptr_t off = (uintptr_t)ep->ExceptionRecord->ExceptionAddress - base;
	CONTEXT *c = ep->ContextRecord;
	int i;

	printf("CRASH code=%08lx addr=%p imagebase=%p offset=%llx\n",
		ep->ExceptionRecord->ExceptionCode,
		ep->ExceptionRecord->ExceptionAddress,
		(void *)base,
		(unsigned long long)off);
#ifdef _WIN64
	printf("  rax=%p rbx=%p rcx=%p rdx=%p rsi=%p rdi=%p\n",
		(void *)c->Rax,(void *)c->Rbx,(void *)c->Rcx,(void *)c->Rdx,(void *)c->Rsi,(void *)c->Rdi);
	printf("  r8=%p r9=%p r10=%p r11=%p r12=%p r13=%p r14=%p r15=%p\n",
		(void *)c->R8,(void *)c->R9,(void *)c->R10,(void *)c->R11,(void *)c->R12,(void *)c->R13,(void *)c->R14,(void *)c->R15);
#endif

	// scan_h / scan_v / scan_d pointer tables plus neighbours (.data).
	for(i=0;i<7;i++)
	{
		printf("  table[%d] h=%p v=%p d=%p\n",i,
			(void *)*(uintptr_t *)(base + 0x195740 + (uintptr_t)i*8),
			(void *)*(uintptr_t *)(base + 0x195778 + (uintptr_t)i*8),
			(void *)*(uintptr_t *)(base + 0x1957B0 + (uintptr_t)i*8));
	}

	printf("  misc d0=%p e0=%p\n",
		(void *)*(uintptr_t *)(base + 0x1957D0),
		(void *)*(uintptr_t *)(base + 0x1957E0));

	// contents of the arrays being searched (Sub = rdi, Pos = rax)
#ifdef _WIN64
	{
		unsigned char *p;
		int j;

		printf("  rdi[]:");
		for(j=0;j<32;j++)
		{
			printf(" %02x", ((unsigned char *)c->Rdi)[j]);
		}

		printf("\n  rax[]:");
		for(j=0;j<32;j++)
		{
			printf(" %02x", ((unsigned char *)c->Rax)[j]);
		}

		printf("\n  r10[]:");
		for(j=0;j<8;j++)
		{
			printf(" %02x", ((unsigned char *)c->R10)[j]);
		}

		printf("\n");
	}
#endif

	fflush(stdout);
	return EXCEPTION_CONTINUE_SEARCH;
}

// registered as early as possible so a crash in another static
// initializer (libheif's plugin/tables) is still reported.
static struct _crash_report_init
{
	_crash_report_init()
	{
		AddVectoredExceptionHandler(1, _crash_report);
	}
} _g_crash_report_init;

int main(int argc, char **argv)
{
	const char *path = (argc > 1) ? argv[1] : "autumn.heic";
	const char *outpath = (argc > 2) ? argv[2] : "decoded.raw";
	FILE *f;
	long fsize;
	char *data;
	struct heif_context *ctx;
	struct heif_image_handle *handle;
	struct heif_image *image;
	struct heif_error err;
	int stride;
	const uint8_t *plane;
	FILE *out;
	int w;
	int h;

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("imagebase=%p\n", (void *)GetModuleHandle(NULL));

	f = fopen(path, "rb");
	if (!f)
	{
		printf("FAIL cannot open %s\n", path);
		return 2;
	}

	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	data = (char *)malloc((size_t)fsize);
	if (!data || (fread(data, 1, (size_t)fsize, f) != (size_t)fsize))
	{
		printf("FAIL read %s\n", path);
		return 2;
	}

	fclose(f);
	printf("read %ld bytes\n", fsize);

	printf("calling heif_context_alloc...\n");
	ctx = heif_context_alloc();
	printf("ctx=%p\n", (void *)ctx);
	if (!ctx)
	{
		printf("FAIL heif_context_alloc\n");
		return 3;
	}

	printf("calling heif_context_read_from_memory_without_copy...\n");
	err = heif_context_read_from_memory_without_copy(ctx, data, (size_t)fsize, NULL);
	printf("read err.code=%d msg=%s\n", err.code, err.message);
	if (err.code != heif_error_Ok)
	{
		printf("FAIL heif_context_read: %s\n", err.message);
		return 3;
	}

	printf("calling heif_context_get_primary_image_handle...\n");
	err = heif_context_get_primary_image_handle(ctx, &handle);
	printf("primary err.code=%d msg=%s\n", err.code, err.message);
	if (err.code != heif_error_Ok)
	{
		printf("FAIL get_primary: %s\n", err.message);
		return 3;
	}

	w = heif_image_handle_get_width(handle);
	h = heif_image_handle_get_height(handle);
	printf("dims: %d x %d alpha=%d\n", w, h, heif_image_handle_has_alpha_channel(handle));

	err = heif_decode_image(handle, &image, heif_colorspace_RGB, heif_chroma_interleaved_RGBA, NULL);
	if (err.code != heif_error_Ok)
	{
		printf("FAIL heif_decode_image: %s\n", err.message);
		return 3;
	}

	plane = heif_image_get_plane_readonly(image, heif_channel_interleaved, &stride);
	if (!plane)
	{
		printf("FAIL no interleaved plane\n");
		return 3;
	}

	printf("stride: %d (expect %d)\n", stride, w * 4);

	out = fopen(outpath, "wb");
	if (out)
	{
		int y;

		for(y=0;y<h;y++)
		{
			fwrite(plane + (size_t)y * stride, 1, (size_t)w * 4, out);
		}

		fclose(out);
		printf("wrote %s\n", outpath);
	}

	printf("first px: %02x %02x %02x %02x\n", plane[0], plane[1], plane[2], plane[3]);

	heif_image_release(image);
	heif_image_handle_release(handle);
	heif_context_free(ctx);
	free(data);
	return 0;
}
