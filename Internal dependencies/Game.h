#ifndef CVP
#pragma once
#include "dynamic_language.h"
#include <fstream>
class Game {
public:
	static void entrLock(bool a);//进程入口锁
//读写函数封装
	static void writeptr(DWORD Address, LPVOID ptr, int size);
	static void readptr(DWORD Address, LPVOID ptr, int size);
	//按地址
	template<typename T> static void write(DWORD Address, const T& Code, int size = sizeof(T)) { writeptr(Address, (LPVOID)&Code, size); }
	template<typename T> static void read(DWORD Address, T& Code, int size = sizeof(T)) { readptr(Address, &Code, size); }
	template<typename T> static T read(DWORD Address) { T temp;	read(Address, temp); return temp; }
	//调用pvz函数
	static DWORD rLoadDll(const wchar_t* path);
	static DWORD rLoadCvp(const wchar_t* path);
	//创建游戏进程
	static bool start(const wchar_t* pvzPath, const wchar_t* dllPath);
	static void release();
private:
	//释放窗口及内存
	static void __stdcall __loadCvp(const wchar_t* dllPath);
	static HANDLE hProcess;
	static DWORD insertBase;
	static DWORD argsAddr;
};
#endif