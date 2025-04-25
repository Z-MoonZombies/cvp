#pragma once
#include "cvp.h"
namespace Template {

	template<typename T>string makeFormat(string& input) { return typeid(T).name(); }


	template<typename T>inline string convertstr(T) { return u8""; }
	template<typename T>inline wstring convertwcs(T) { return L""; }
	template<>inline string convertstr(string val) { return move(val); }
	template<>inline wstring convertwcs(wstring val) { return move(val); }
	template<>inline string convertstr(string_view val) { return string(val); }
	template<>inline wstring convertwcs(wstring_view val) { return wstring(val); }
	template<>inline string convertstr(const char* val) { return string(val); }
	template<>inline wstring convertwcs(const wchar_t* val) { return wstring(val); }
	template<typename = void>inline string convertstr(void) { return u8""; }
	template<typename = void>inline wstring convertwcs(void) { return L""; }

	template<typename T>inline T convert(string_view str) { return convert<T>(convert<wstring>(str)); }
	template<typename T>inline T convert(const char* str) { return convert<T>(string_view(str)); }
	template<typename T>inline T convert(wstring_view str) { return convert<T>(convert<string>(str)); }
	template<typename T>inline T convert(const wchar_t* str) { return convert<T>(wstring_view(str)); }
	template<>inline wstring convert<wstring>(string_view str) { return Cvp::__utf2wcs(str); }
	template<>inline wstring convert<wstring>(wstring_view str) { return wstring(str); }
	template<>inline string convert<string>(string_view str) { return string(str); }
	template<>inline string convert<string>(wstring_view str) { return Cvp::__wcs2utf(str); }

	template<>inline int convert<int>(string_view str) { return atoi(str.data()); }
	template<>inline long convert<long>(string_view str) { return atol(str.data()); }
	template<>inline long long convert<long long>(string_view str) { return atoll(str.data()); }
	template<>inline float convert<float>(string_view str) { return (float)atof(str.data()); }
	template<>inline double convert<double>(string_view str) { return atof(str.data()); }
	template<>inline void* convert<void*>(string_view str) { return (void*)strtoul(str.data(), nullptr, 16); }
	template<>inline KeyCode convert<KeyCode>(string_view str) { return (KeyCode)(DWORD)convert<void*>(str); }


	template<typename T>int serializeN(const T* _this = nullptr) { static_assert(std::is_trivially_copyable_v<T>); return sizeof(T); }
	template<typename T>void serialize(const T& _this, BYTE* buffer) { static_assert(std::is_trivially_copyable_v<T>); memcpy(buffer, &_this, serializeN<T>()); }
	template<typename T>void deserialize(T& _this, BYTE* buffer, int len = serializeN<T>()) { static_assert(std::is_trivially_copyable_v<T>); if (len >= sizeof(T))memcpy(&_this, buffer, sizeof(T)); else memcpy(&_this, buffer, len); }

	template<>inline int serializeN(const string* _this) { if (_this)return _this->size(); else return 0; }
	template<>inline void serialize(const string& _this, BYTE* buffer) { memcpy(buffer, &_this[0], _this.size()); }
	template<>inline void deserialize(string& _this, BYTE* buffer, int len) { _this.resize(len); memcpy(&_this[0], buffer, len); }
	template<>inline int serializeN(const vector<string>* _this) { if (!_this)return 0; int ans = sizeof(DWORD) * (_this->size() + 1); for (auto&& p : *_this)ans += p.size(); return ans; }
	template<>inline void serialize(const vector<string>& _this, BYTE* buffer) { serialize((DWORD)_this.size(), buffer), buffer += sizeof(DWORD); for (auto&& p : _this) serialize((DWORD)p.size(), buffer), buffer += sizeof(DWORD), serialize(p, buffer), buffer += p.size(); }
	template<>inline void deserialize(vector<string>& _this, BYTE* buffer, int len) { _this.clear(); DWORD size; deserialize(size, buffer, sizeof(DWORD)); buffer += sizeof(DWORD); _this.resize(size, u8""); for (auto&& p : _this)deserialize(size, buffer, sizeof(DWORD)), buffer += sizeof(DWORD), deserialize(p, buffer, size), buffer += size; }
	template<>inline int serializeN(const vector<DWORD>* _this) { if (!_this)return 0; return sizeof(DWORD) * (_this->size() + 1); }
	template<>inline void serialize(const vector<DWORD>& _this, BYTE* buffer) { serialize((DWORD)_this.size(), buffer), buffer += sizeof(DWORD); memcpy(buffer, &_this[0], sizeof(DWORD) * _this.size()); }
	template<>inline void deserialize(vector<DWORD>& _this, BYTE* buffer, int len) { _this.clear(); DWORD size; deserialize(size, buffer, sizeof(DWORD)); buffer += sizeof(DWORD); _this.resize(size, 0x0ul); memcpy(&_this[0], buffer, sizeof(DWORD) * _this.size()); }
}