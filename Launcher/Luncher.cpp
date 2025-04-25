#include <windows.h>
int main() {
	wchar_t thePath[MAX_PATH];//目标文件路径
	wchar_t myPath[MAX_PATH];//当前路径
	GetModuleFileNameW(nullptr, myPath, MAX_PATH);
	for (wchar_t* ptr = myPath + wcslen(myPath); *(ptr - 1) != L'\\'; *--ptr = 0);//当前目录
	WIN32_FIND_DATAW FindFileData;
	HANDLE hFile = FindFirstFileW(L"*.*", &FindFileData);
	while (FindNextFileW(hFile, &FindFileData)) {
		if ((FindFileData.cFileName[wcslen(FindFileData.cFileName) - 3] == L'd') &&
			(FindFileData.cFileName[wcslen(FindFileData.cFileName) - 2] == L'l') &&
			(FindFileData.cFileName[wcslen(FindFileData.cFileName) - 1] == L'l')) {//dll文件
			wcscpy(thePath, myPath);
			wcscat(thePath, FindFileData.cFileName);//目标文件路径
            //加载器应提供extern"C" void __declspec(dllexport) __stdcall dll_init(const wchar_t*)形式的接口
			void(__stdcall * dll_init)(const wchar_t*) = (void(__stdcall*)(const wchar_t*))GetProcAddress(LoadLibraryW(thePath), "_dll_init@4");
			if(dll_init) dll_init(thePath);
		}
	}
	FindClose(hFile);
	return 0;
}