// v3.7: 最近打开 / 收藏夹路径列表的真实逻辑测试。
// 直接链接 src/config.c、ini.c、string.c、utf8.c、mem.c，验证：
// 去重、置顶、上限淘汰、UTF-8 保存/加载、特殊字符路径。
//
// 构建（在仓库根目录，已执行 vcvars64.bat）：
//   cl /nologo /W3 tests\test_config_paths.c src\config.c src\ini.c src\string.c src\utf8.c src\mem.c /Fe:tests\build\test_config_paths.exe /link user32.lib shlwapi.lib
//   tests\build\test_config_paths.exe

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>

#include "../src/viv.h"

static int failure_count;

void debug_fatal(const char *format,...)
{
	(void)format;
	ExitProcess(1);
}

// ---- 被测模块依赖的最小桩 ----
void os_copy_memory(void *d,const void *s,int size) { CopyMemory(d,s,size); }
void os_move_memory(void *d,const void *s,int size) { MoveMemory(d,s,size); }
void os_qsort(void **base,uintptr_t count,int (*compare)(const void *,const void *))
{
	// 项目里的 os_qsort 把“元素指针”直接传给比较函数（不是 qsort 的指针的指针），
	// 这里用插入排序复刻同样的语义。
	uintptr_t i;
	
	for(i=1;i<count;i++)
	{
		void *key;
		uintptr_t j;
		
		key = base[i];
		j = i;
		
		while((j > 0) && (compare(base[j - 1],key) > 0))
		{
			base[j] = base[j - 1];
			j--;
		}
		
		base[j] = key;
	}
}

int viv_get_command_count(void) { return 0; }
int viv_menu_name_to_ini_name(utf8_t *buf,int command_index) { (void)buf; (void)command_index; return 0; }
void viv_key_add(int command_index,DWORD keyflags) { (void)command_index; (void)keyflags; }
void viv_key_clear_all(int command_index) { (void)command_index; }
config_key_t *viv_key_get_start(int command_index) { (void)command_index; return 0; }

static void expect(const char *name,int condition)
{
	if (condition)
	{
		printf("pass %s\n",name);
	}
	else
	{
		failure_count++;
		printf("FAIL %s\n",name);
	}
}

static void expect_wstr(const char *name,const wchar_t *actual,const wchar_t *expected)
{
	if ((actual) && (wcscmp(actual,expected) == 0))
	{
		printf("pass %s\n",name);
	}
	else
	{
		failure_count++;
		printf("FAIL %s (expected %ls, got %ls)\n",name,expected,actual ? actual : L"(null)");
	}
}

static void test_ini_path(wchar_t *buf,int size)
{
	wchar_t exe[1024];
	wchar_t *p;
	
	GetModuleFileNameW(NULL,exe,1024);
	p = wcsrchr(exe,L'\\');
	if (p)
	{
		*p = 0;
	}
	wcscpy(buf,exe);
	wcscat(buf,L"\\voidImageViewer.ini");
	(void)size;
}

int main(void)
{
	wchar_t ini_path[1024];
	wchar_t path[STRING_SIZE];
	int i;
	int count;
	
	setvbuf(stdout,NULL,_IONBF,0);
	
	test_ini_path(ini_path,1024);
	DeleteFileW(ini_path);
	
	config_recent_clear();
	config_favorite_clear();
	
	// 1. 最近列表上限 20，最新的在最前，最旧的被淘汰。
	for(i=0;i<25;i++)
	{
		swprintf(path,STRING_SIZE,L"C:\\test\\img%d.jpg",i);
		config_recent_add(path);
	}
	
	expect("recent count capped at 20",config_recent_count() == CONFIG_RECENT_MAX);
	expect_wstr("newest recent is first",config_recent_get(0),L"C:\\test\\img24.jpg");
	expect_wstr("oldest kept is img5",config_recent_get(CONFIG_RECENT_MAX - 1),L"C:\\test\\img5.jpg");
	
	// 2. 重复路径移到最前，不产生重复。
	config_recent_add(L"C:\\test\\img10.jpg");
	expect("recent duplicate count unchanged",config_recent_count() == CONFIG_RECENT_MAX);
	expect_wstr("recent duplicate moved to front",config_recent_get(0),L"C:\\test\\img10.jpg");
	
	count = 0;
	for(i=0;i<config_recent_count();i++)
	{
		if (wcscmp(config_recent_get(i),L"C:\\test\\img10.jpg") == 0)
		{
			count++;
		}
	}
	expect("recent duplicate only once",count == 1);
	
	// 3. 大小写不敏感去重。
	config_recent_clear();
	config_recent_add(L"C:\\Case\\A.JPG");
	config_recent_add(L"c:\\case\\a.jpg");
	expect("recent case-insensitive dedupe",config_recent_count() == 1);
	
	// 4. 收藏上限 100，满后拒绝新增。
	for(i=0;i<CONFIG_FAVORITE_MAX;i++)
	{
		swprintf(path,STRING_SIZE,L"C:\\fav\\img%d.jpg",i);
		if (config_favorite_add(path) != 1)
		{
			failure_count++;
		}
	}
	expect("favorite add reached full count",config_favorite_count() == CONFIG_FAVORITE_MAX);
	expect("favorite over limit rejected",config_favorite_add(L"C:\\fav\\overflow.jpg") == 0);
	expect("favorite remove works",config_favorite_remove(L"C:\\fav\\img0.jpg") == 1);
	expect("favorite count after remove",config_favorite_count() == CONFIG_FAVORITE_MAX - 1);
	expect("favorite remove missing returns 0",config_favorite_remove(L"C:\\fav\\no-such.jpg") == 0);
	
	// 5. 特殊字符与中文路径保存/加载。
	config_recent_clear();
	config_recent_add(L"C:\\A & B\\x=y.png");
	config_recent_add(L"C:\\测试\\图片.jpg");
	
	config_save_settings(0);
	
	config_recent_clear();
	config_favorite_clear();
	config_load_settings();
	
	expect("recent count after reload",config_recent_count() == 2);
	expect_wstr("utf8/&/= path reloaded",config_recent_get(0),L"C:\\测试\\图片.jpg");
	expect_wstr("&/= path reloaded",config_recent_get(1),L"C:\\A & B\\x=y.png");
	expect("favorite count after reload",config_favorite_count() == CONFIG_FAVORITE_MAX - 1);
	
	DeleteFileW(ini_path);
	
	printf("%s: %d assertion(s) failed\n",failure_count ? "FAILURE" : "SUCCESS",failure_count);
	return failure_count ? 1 : 0;
}
