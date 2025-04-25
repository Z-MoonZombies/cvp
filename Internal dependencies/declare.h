#pragma once
#pragma warning( disable : 4530 )
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"comctl32.lib")
#include <string>
#include <cwchar>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <initializer_list>
#include <functional>
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
__declspec(selectany) HANDLE& PvzHeapHandle = *(HANDLE*)0x6A6DD4ul;
constexpr float Pi = 3.1415927f;
enum class KeyCode :DWORD {
	NIL = 0x00u,
	LBUTTON = 0x01u,
	RBUTTON = 0x02u,
	CANCEL = 0x03u,
	MBUTTON = 0x04u,
	BACKSPACE = 0x08u,
	TAB = 0x09u,
	CLEAR = 0x0Cu,
	RETURN = 0x0Du,
	SHIFT = 0x10u,
	CONTROL = 0x11u,
	MENU = 0x12u,
	PAUSE = 0x13u,
	CAPITAL = 0x14u,
	KANA = 0x15u,
	HANGEUL = 0x15u,
	HANGUL = 0x15u,
	JUNJA = 0x17u,
	FINAL = 0x18u,
	HANJA = 0x19u,
	KANJI = 0x19u,
	ESCAPE = 0x1Bu,
	CONVERT = 0x1Cu,
	NONCONVERT = 0x1Du,
	ACCEPT = 0x1Eu,
	MODECHANGE = 0x1Fu,
	SPACE = 0x20u,
	PRIOR = 0x21u,
	NEXT = 0x22u,
	END = 0x23u,
	HOME = 0x24u,
	LEFT = 0x25u,
	UP = 0x26u,
	RIGHT = 0x27u,
	DOWN = 0x28u,
	SELECT = 0x29u,
	PRINT = 0x2Au,
	EXECUTE = 0x2Bu,
	SNAPSHOT = 0x2Cu,
	INSERT = 0x2Du,
	DELETE_ = 0x2Eu,
	HELP = 0x2Fu,
	NUM_0 = 0x30u,
	NUM_1 = 0x31u,
	NUM_2 = 0x32u,
	NUM_3 = 0x33u,
	NUM_4 = 0x34u,
	NUM_5 = 0x35u,
	NUM_6 = 0x36u,
	NUM_7 = 0x37u,
	NUM_8 = 0x38u,
	NUM_9 = 0x39u,
	A = 0x41u,
	B = 0x42u,
	C = 0x43u,
	D = 0x44u,
	E = 0x45u,
	F = 0x46u,
	G = 0x47u,
	H = 0x48u,
	I = 0x49u,
	J = 0x4Au,
	K = 0x4Bu,
	L = 0x4Cu,
	M = 0x4Du,
	N = 0x4Eu,
	O = 0x4Fu,
	P = 0x50u,
	Q = 0x51u,
	R = 0x52u,
	S = 0x53u,
	T = 0x54u,
	U = 0x55u,
	V = 0x56u,
	W = 0x57u,
	X = 0x58u,
	Y = 0x59u,
	Z = 0x5Au,
	LWIN = 0x5Bu,
	RWIN = 0x5Cu,
	APPS = 0x5Du,
	SLEEP = 0x5Fu,
	NUMPAD0 = 0x60u,
	NUMPAD1 = 0x61u,
	NUMPAD2 = 0x62u,
	NUMPAD3 = 0x63u,
	NUMPAD4 = 0x64u,
	NUMPAD5 = 0x65u,
	NUMPAD6 = 0x66u,
	NUMPAD7 = 0x67u,
	NUMPAD8 = 0x68u,
	NUMPAD9 = 0x69u,
	MULTIPLY = 0x6Au,
	ADD = 0x6Bu,
	SEPARATOR = 0x6Cu,
	SUBTRACT = 0x6Du,
	DECIMAL = 0x6Eu,
	DIVIDE = 0x6Fu,
	F1 = 0x70u,
	F2 = 0x71u,
	F3 = 0x72u,
	F4 = 0x73u,
	F5 = 0x74u,
	F6 = 0x75u,
	F7 = 0x76u,
	F8 = 0x77u,
	F9 = 0x78u,
	F10 = 0x79u,
	F11 = 0x7Au,
	F12 = 0x7Bu,
	F13 = 0x7Cu,
	F14 = 0x7Du,
	F15 = 0x7Eu,
	F16 = 0x7Fu,
	F17 = 0x80u,
	F18 = 0x81u,
	F19 = 0x82u,
	F20 = 0x83u,
	F21 = 0x84u,
	F22 = 0x85u,
	F23 = 0x86u,
	F24 = 0x87u,
	NUMLOCK = 0x90u,
	SCROLL = 0x91u,
	SEMICOLON = 0xBAu,
	PLUS = 0xBBu,
	COMMA = 0xBCu,
	MINUS = 0xBDu,
	PERIOD = 0xBEu,
	SLASH = 0xBFu,
	TILDE = 0xC0u,
	BRACKET_LEFT = 0xDBu,
	BACK_SLASH = 0xDCu,
	BRACKET_RIGHT = 0xDDu,
	QUOTE = 0xDEu,
	MAX = 0xFFu
};
using std::initializer_list;
using std::pair;
using std::make_pair;
using std::array;
using std::vector;
using std::list;
using std::string;
using std::wstring;
using std::string_view;
using std::wstring_view;
using std::tuple;
using std::tie;
using std::get;
using std::function;
using std::move;
using std::forward;
using ulong = ULONG;
using uchar = UCHAR;
using LPVOID = void*;
//using BYTE = uint8_t;
//using WORD = uint16_t;
//using DWORD = uint32_t;
using QWORD = uint64_t;
using SoundId = DWORD;
constexpr int cvp_version = 0x00070000ul;
#ifdef CVP
extern"C" inline DWORD __declspec(dllexport)__cdecl cvp_ex_getversion() { return cvp_version; }
extern"C" inline void __declspec(dllexport)__cdecl cvp_ex_init();
#endif