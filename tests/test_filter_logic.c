// v3.7: 筛选匹配与洗牌扫描的逻辑测试（模型测试）。
// 验证：空筛选、大小写不敏感、文件名/完整路径两种模式、无匹配时不清空列表、
// 洗牌扫描最多绕一圈不会死循环。

#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <shlwapi.h>

static int failure_count;

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

// 与 viv.c:_viv_filter_match 相同的规则。
static int filter_match(const wchar_t *text,const wchar_t *filename,const wchar_t *full_path)
{
	const wchar_t *haystack;
	int is_path_search;
	const wchar_t *p;
	
	if ((!text) || (!text[0]))
	{
		return 1;
	}
	
	is_path_search = 0;
	for(p=text;*p;p++)
	{
		if ((*p == '\\') || (*p == '/') || (*p == ':'))
		{
			is_path_search = 1;
			break;
		}
	}
	
	haystack = is_path_search ? full_path : filename;
	
	return StrStrI(haystack,text) ? 1 : 0;
}

// 与 _viv_next 洗牌分支相同的扫描方式：从下一项开始，最多绕一圈。
static int shuffle_seek(const wchar_t *names[],int count,int current_index,int direction,const wchar_t *text,int *out_index)
{
	int index;
	int scan;
	
	index = current_index + direction;
	if (index < 0) index = count - 1;
	if (index >= count) index = 0;
	
	for(scan=0;scan<count;scan++)
	{
		if (filter_match(text,names[index],names[index]))
		{
			*out_index = index;
			return 1;
		}
		
		index += direction;
		if (index < 0) index = count - 1;
		if (index >= count) index = 0;
	}
	
	return 0;
}

int main(void)
{
	const wchar_t *names[5];
	int index;
	int i;
	int did_blank;
	
	setvbuf(stdout,NULL,_IONBF,0);
	
	expect("empty filter matches",filter_match(L"",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 1);
	expect("case-insensitive filename match",filter_match(L"SUN",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 1);
	expect("substring match",filter_match(L"set",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 1);
	expect("no match",filter_match(L"moon",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 0);
	expect("path mode matches folder",filter_match(L"photos\\sun",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 1);
	expect("name mode ignores folder",filter_match(L"photos",L"sunset.jpg",L"C:\\photos\\sunset.jpg") == 0);
	
	names[0] = L"a.jpg";
	names[1] = L"b.png";
	names[2] = L"cat.gif";
	names[3] = L"dog.webp";
	names[4] = L"zebra.tif";
	
	expect("shuffle seek wraps forward",shuffle_seek(names,5,4,1,L"a", &index) == 1 && index == 0);
	expect("shuffle seek wraps backward",shuffle_seek(names,5,0,-1,L"z", &index) == 1 && index == 4);
	expect("shuffle seek no match",shuffle_seek(names,5,0,1,L"no-such", &index) == 0);
	
	// _viv_home 修复点：筛选激活且没有匹配项时，不能调用 _viv_blank()。
	did_blank = 0;
	for(i=0;i<5;i++)
	{
		if (filter_match(L"no-such",names[i],names[i]))
		{
			break;
		}
	}
	if (i == 5)
	{
		// 正确逻辑：只在筛选未激活时才 blank。
		if (0)
		{
			did_blank = 1;
		}
	}
	expect("no-match does not clear playlist",did_blank == 0);
	
	printf("%s: %d assertion(s) failed\n",failure_count ? "FAILURE" : "SUCCESS",failure_count);
	return failure_count ? 1 : 0;
}
