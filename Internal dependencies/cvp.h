#pragma once
#include "declare.h"
template<typename T, typename... Args>
inline bool inrange(T&& val, Args&&... range) { return(... || (val == range)); }
template<typename... Args>
inline auto bplus(Args&&... args) { return(... | args); }
template<typename T, typename... Args>
inline T bminus(T&& val, Args&&... args) { return(val & ~bplus(args...)); }
template< typename... Args>
inline auto or (Args&&... args) { return(... || args); }
template<typename... Args>
inline auto and (Args&&... args) { return(... && args); }
template<typename T, typename Cmp = std::less<T> >
inline T limit(T min, T input, T max) {
	Cmp cmp = Cmp();
	if (cmp(input, max)) {
		if (cmp(min, input))return input;
		else if (cmp(min, max))return min;
		else return max;
	} else {
		if (cmp(min, max))return max;
		else if (cmp(min, input))return min;
		else return input;
	}
}
template<typename T>
inline T cut(T min, float rate, T max) {
	return (T)(min + rate * (max - min));
}
template<typename T>
inline T cut(T min, double rate, T max) {
	return (T)(min + rate * (max - min));
}
template<typename T>
inline float getcut(T min, T mid, T max) {
	return (float)(mid - min) / (float)(max - min);
}
template<typename T>
inline float getcutd(T min, T mid, T max) {
	return (double)(mid - min) / (double)(max - min);
}
template<typename T1, typename T2>
inline T2 recut(T1 min_in, T1 mid, T1 max_in, T2 min_out, T2 max_out) {
	return cut(min_out, getcut(min_in, mid, max_in), max_out);
}
template<typename T1, typename T2>
inline T2 recutd(T1 min_in, T1 mid, T1 max_in, T2 min_out, T2 max_out) {
	return cut(min_out, getcutd(min_in, mid, max_in), max_out);
}
template<typename T>
struct Point {
	T mX;
	T mY;
	template<typename T1>
	Point(const T1& _x, const T1& _y) : mX((T)_x), mY((T)_y) {}
	template<typename T1>
	Point(const Point<T1>& that) : mX((T)that.mX), mY((T)that.mY) {}
	template<typename T1>
	Point<T> operator+(const Point<T1>& that)const {
		return Point<T>(mX + (T)that.mX, mY + (T)that.mY);
	}
	template<typename T1>
	Point<T> operator-(const Point<T1>& that)const {
		return Point<T>(mX - (T)that.mX, mY - (T)that.mY);
	}
	template<typename T1>
	Point<T> operator*(const T1& that)const {
		return Point<T>(mX * (T)that, mY * (T)that);
	}
	template<typename T1>
	Point<T> operator/(const T1& that)const {
		return Point<T>(mX / (T)that, mY / (T)that);
	}
	T Distance()const {
		return (T)sqrt(mX * mX + mY * mY);
	}
};

struct Rect {
	int mX;
	int mY;
	int mW;
	int mH;
	Rect() { mX = mY = mW = mH = 0; }
	Rect(int x, int y, int w, int h) { mX = x, mY = y, mW = w, mH = h; }
	bool Intersects(const Rect& theRect)const { return !((theRect.mX + theRect.mW <= mX) || (theRect.mY + theRect.mH <= mY) || (theRect.mX >= mX + mW) || (theRect.mY >= mY + mH)); }
	bool Intersects(int x, int y, int r)const {
		int xdif = 0;
		int ydif = 0;
		if (x < mX)xdif = mX - x;
		else if (x > mX + mW)xdif = x - mX - mW;
		if (y < mY)ydif = mY - y;
		else if (y > mY + mH)ydif = y - mY - mH;
		return  xdif * xdif + ydif * ydif <= r * r;
	}
	int IntersectWidth(const Rect& theRect)const {
		int LL, LR, RL, RR;
		if (mX < theRect.mX) {
			LL = mX;
			LR = mX + mW;
			RL = theRect.mX;
			RR = theRect.mX + theRect.mW;
		} else {
			LL = theRect.mX;
			LR = theRect.mX + theRect.mW;
			RL = mX;
			RR = mX + mW;
		}
		if (LR <= RL) {
			return LR - RL;
		}
		if (LR <= RR) {
			return LR - RL;
		}
		return RR - RL;
	}
	Rect Intersection(const Rect& theRect)const {
		int x1 = max(mX, theRect.mX);
		int x2 = min(mX + mW, theRect.mX + theRect.mW);
		int y1 = max(mY, theRect.mY);
		int y2 = min(mY + mH, theRect.mY + theRect.mH);
		if (((x2 - x1) < 0) || ((y2 - y1) < 0))return Rect(0, 0, 0, 0);
		else return Rect(x1, y1, x2 - x1, y2 - y1);
	}
	Point<int> Limit(Point<int> p)const {
		return Point<int>(limit(mX, p.mX, mX + mW), limit(mY, p.mY, mY + mH));
	}
	RECT ToRECT()const {
		return { mX, mY, mX + mW, mY + mH };
	}
	bool Contains(int theX, int theY)const {
		return((theX >= mX) && (theX < mX + mW) && (theY >= mY) && (theY < mY + mH));
	}
	Rect Merge(const Rect& theRect) {
		return Rect(min(mX, theRect.mX), min(mY, theRect.mY), max(mX + mW, theRect.mX + theRect.mW) - min(mX, theRect.mX), max(mY + mH, theRect.mY + theRect.mH) - min(mY, theRect.mY));
	}
	template<typename T>
	Rect operator+(const Point<T>& that) {
		return Rect(mX + that.mX, mY + that.mY, mW, mH);
	}
	template<typename T>
	Rect& operator+=(const Point<T>& that) {
		mX += that.mX; mY += that.mY;	return *this;
	}
	template<typename T>
	Rect operator-(const Point<T>& that) {
		return Rect(mX - that.mX, mX - that.mY, mW, mH);
	}
	template<typename T>
	Rect& operator-=(const Point<T>& that) {
		mX -= that.mX; mY -= that.mY;	return *this;
	}
};

struct Color {
	int mRed;
	int mGreen;
	int mBlue;
	int mAlpha;
	Color() { mRed = mGreen = mBlue = mAlpha = 0; }
	Color(DWORD argb) { mAlpha = argb >> 24; mRed = argb >> 16 & 0xffu; mGreen = argb >> 8 & 0xffu; mBlue = argb & 0xffu; }
	Color(int r, int g, int b, int a) { mRed = r, mGreen = g, mBlue = b, mAlpha = a; }
	Color operator*(const Color& that)const {
		return Color(mRed * that.mRed / 255, mGreen * that.mGreen / 255, mBlue * that.mBlue / 255, mAlpha * that.mAlpha / 255);
	}
	DWORD ARGB()const { return((mAlpha & 0xffu) << 24) | ((mRed & 0xffu) << 16) | ((mGreen & 0xffu) << 8) | ((mBlue & 0xffu) << 0); }
};
struct Matrix3 {
	static constexpr float m20 = 0.0f;
	static constexpr float m21 = 0.0f;
	static constexpr float m22 = 1.0f;
	static constexpr float g = 0.0f;
	static constexpr float h = 0.0f;
	static constexpr float i = 1.0f;
	union {
		float m[3][3];
		struct {
			float m00, m01, m02;
			float m10, m11, m12;
		};
		struct {
			float a, b, c;
			float d, e, f;
		};
		struct {
			float ru_x, ru_y, x;
			float lb_x, lb_y, y;
		};
		struct {
			float xStrech, xSlope, xDiff;
			float ySlope, yStrech, yDiff;
			float _0, __0, _1;
		};
	};
	Matrix3(float x, float y, float r = 0.0f, float xs = 1.0f, float ys = 1.0f) {
		xStrech = xs * cos(r), xSlope = -xs * sin(r), xDiff = xs * x;
		ySlope = ys * sin(r), yStrech = ys * cos(r), yDiff = ys * y;
		_0 = 0.0f, __0 = 0.0f, _1 = 1.0f;
	}
	Matrix3() {
		a = 1.0f, b = 0.0f, c = 0.0f;
		d = 0.0f, e = 1.0f, f = 0.0f;
		_0 = 0.0f, __0 = 0.0f, _1 = 1.0f;
	}
	Matrix3(float _a, float _b, float _c, float _d, float _e, float _f) {
		a = _a; b = _b; c = _c;
		d = _d; e = _e; f = _f;
		_0 = 0.0f, __0 = 0.0f, _1 = 1.0f;
	}
	static Matrix3 Move(float x, float y) { return Matrix3(1.0f, 0.0f, x, 0.0f, 1.0f, y); }
	static Matrix3 Rotate(float r) { return Matrix3(cos(r), -sin(r), 0.0f, sin(r), cos(r), 0.0f); }
	static Matrix3 Strech(float xs, float ys) { return Matrix3(xs, 0.0f, 0.0f, 0.0f, ys, 0.0f); }
	Matrix3 GetInverse() {
		float D = a * e - b * d;
		if (D == 0.0f)return Matrix3();
		return Matrix3(e / D, -b / D, (b * f - c * e) / D, -d / D, a / D, (c * d - a * f) / D);
	}
	Matrix3 operator*(const Matrix3& that)const {
		return Matrix3(
			a * that.a + b * that.d,
			a * that.b + b * that.e,
			a * that.c + b * that.f + c,
			d * that.a + e * that.d,
			d * that.b + e * that.e,
			d * that.c + e * that.f + f
		);
	}
};
class BasicVertex {
	float __x, __y, __z, __rhw;
	DWORD __color;
public:
	BasicVertex() :__x(0.0f), __y(0.0f), __z(0.0f), __rhw(0.0f), __color(0) {}
	BasicVertex(float x, float y, DWORD color) :__x(x), __y(y), __z(0.0f), __rhw(1.0f), __color(color) {}
	BasicVertex(int x, int y, DWORD color) :__x((float)x), __y((float)y), __z(0.0f), __rhw(1.0f), __color(color) {}
};
namespace Cvp {
	inline nullptr_t valloc(size_t size) { void* const p = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE); if (p)memset(p, 0, size); return *(nullptr_t*)&p; }
	inline void vfree(void* memory) { VirtualFree(memory, 0, MEM_RELEASE); }
	__declspec(selectany) BYTE* volatile __common_buffer = valloc(0x1000);
	__declspec(selectany) size_t volatile __buffer_size = 0x1000;
	static char* volatile& __char_buffer = *(char**)&__common_buffer;
	static wchar_t* volatile& __wchar_buffer = *(wchar_t**)&__common_buffer;
	inline void __clear_buffer(size_t len = 0x7fffffff) { memset(__common_buffer, 0, min(len, __buffer_size)); }
	template<bool conserve = false>
	inline bool __realloc_buffer(size_t len) {
		if (len < __buffer_size)return false;
		len |= len >> 1; len |= len >> 2; len |= len >> 4; len |= len >> 8; len |= len >> 16;
		BYTE* temp = valloc(len + 1);
		if constexpr (conserve) memcpy(temp, __common_buffer, __buffer_size);
		__buffer_size = len + 1;
		vfree(__common_buffer);
		__common_buffer = temp;
		return true;
	}
}
__declspec(selectany)extern char __hex_table[16]{ u8'0',u8'1',u8'2',u8'3',u8'4',u8'5',u8'6',u8'7',u8'8',u8'9',u8'A',u8'B',u8'C',u8'D',u8'E',u8'F' };
template<size_t a, size_t b>constexpr size_t CTmin = (a < b) ? (a) : (b);
template<size_t a, size_t b>constexpr size_t CTadd = ((a | b)>>15) ? (0xffffffff) : (a + b);
template<size_t, typename...>struct CTget;
template<size_t i, typename Head, typename...Args>struct CTget<i, Head, Args...> { static auto get(Head head, Args...args) { return CTget<i - 1, Args...>::get(args...); } };
template<typename Head, typename...Args>struct CTget<0ul, Head, Args...> { static auto get(Head head, Args...) { return head; } };
template<char chr>struct CTchr { static constexpr bool isCTchr = true; static constexpr char val = chr; };
template<typename...Args>class CTstr;
template<typename, size_t>struct CTstr_iterator;
template<typename Str>
struct CTstr_buffer {
	static constexpr size_t size = Str::size();
	struct buffer {
		char val[size + 1ul];
		template<size_t...i>buffer(std::index_sequence<i...>) { ((val[i] = CTstr_iterator<Str, i>::val_T::val), ...);	val[size] = u8'\0'; }
	};
	static inline const buffer val = buffer(std::make_index_sequence<size>());
};
template<typename car, typename...cdr>
class CTstr<car, cdr...> {
	static constexpr size_t _size = 1ul + sizeof...(cdr);
public:
	static constexpr size_t npos = 0xfffffffful;
	using Car = car;
	using Cdr = CTstr<cdr...>;
	using this_T = CTstr<car, cdr...>;
	using buffer = CTstr_buffer<this_T>;
	static constexpr bool isCTstr = true;
	static constexpr bool empty() { return false; };
	static constexpr size_t size() { return _size; }
	static constexpr decltype(auto) data() { return &buffer::val.val; }
	static constexpr const char* c_str() { return &buffer::val.val[0ul]; }
	template<size_t i>using iterator_T = typename CTstr_iterator<this_T, i>::val_T;
	template<typename Chr>using _appendChr_T = typename CTstr<car, cdr..., Chr>;
};
template<>
class CTstr<> {
	static constexpr size_t _size = 0ul;
public:
	static constexpr size_t npos = 0xfffffffful;
	using this_T = CTstr<>;
	using buffer = CTstr_buffer<this_T>;
	static constexpr bool isCTstr = true;
	static constexpr bool empty() { return true; };
	static constexpr size_t size() { return _size; }
	static constexpr decltype(auto) data() { return &buffer::val.val; }
	static constexpr const char* c_str() { return &buffer::val.val[0ul]; }
	template<typename Chr>using _appendChr_T = typename CTstr<Chr>;
};
template<typename Str, size_t i>struct CTstr_iterator { using val_T = typename CTstr_iterator<typename Str::Cdr, i - 1ul>::val_T; };
template<typename Str>	struct CTstr_iterator<Str, 0ul> { using val_T = typename Str::Car; };
template<char...>struct _CTstrMaker;
template<char Tail, char...Head>struct _CTstrMaker<Tail, Head...> { using val_T = typename _CTstrMaker< Head...>::val_T::template _appendChr_T<CTchr<Tail>>; };
template<char...Head>struct _CTstrMaker<u8'\0', Head...> { using val_T = typename _CTstrMaker< Head...>::val_T; };
template<>struct _CTstrMaker<> { using val_T = CTstr<>; };
template<size_t n, typename Chr>struct _CTstrMakerDefault { using val_T = typename _CTstrMakerDefault<n - 1, Chr>::val_T::template _appendChr_T<Chr>; };
template<typename Chr>struct _CTstrMakerDefault<0ul, Chr> { using val_T = CTstr<>; };
template<size_t n>constexpr char _strpos(const char(&str)[n], size_t i) {
	static_assert(n < 0x100ul);
	return str[i < n ? i : (n - 1ul)];
}
#define _MakeCTstr16(str, index)\
	_strpos(str, index ## f), _strpos(str, index ## e), _strpos(str, index ## d), _strpos(str, index ## c),\
	_strpos(str, index ## b), _strpos(str, index ## a), _strpos(str, index ## 9), _strpos(str, index ## 8),\
	_strpos(str, index ## 7), _strpos(str, index ## 6), _strpos(str, index ## 5), _strpos(str, index ## 4),\
	_strpos(str, index ## 3), _strpos(str, index ## 2), _strpos(str, index ## 1), _strpos(str, index ## 0)
#define _MakeCTstr256(str, index)\
	_MakeCTstr16(str, index ## f), _MakeCTstr16(str, index ## e), _MakeCTstr16(str, index ## d), _MakeCTstr16(str, index ## c),\
	_MakeCTstr16(str, index ## b), _MakeCTstr16(str, index ## a), _MakeCTstr16(str, index ## 9), _MakeCTstr16(str, index ## 8),\
	_MakeCTstr16(str, index ## 7), _MakeCTstr16(str, index ## 6), _MakeCTstr16(str, index ## 5), _MakeCTstr16(str, index ## 4),\
	_MakeCTstr16(str, index ## 3), _MakeCTstr16(str, index ## 2), _MakeCTstr16(str, index ## 1), _MakeCTstr16(str, index ## 0)
template<typename Str, typename Chr>struct _CTstr_appendHelper { using val_T = typename Str::template _appendChr_T<Chr>; };
template<typename Str1, typename Str2>struct _CTstr_addHelper { using val_T = typename _CTstr_addHelper<typename Str1::template _appendChr_T<Str2::Car>, typename Str2::Cdr>::val_T; };
template<typename Str>struct _CTstr_addHelper<Str, CTstr<>> { using val_T = Str; };
template<typename Str, size_t begin>struct _CTstr_cutfrontHelper { using val_T = typename _CTstr_cutfrontHelper<typename Str::Cdr, begin - 1>::val_T; };
template<typename Str>struct _CTstr_cutfrontHelper<Str, 0ul> { using val_T = Str; };
template<size_t begin>struct _CTstr_cutfrontHelper<CTstr<>, begin> { using val_T = CTstr<>; };
template<>struct _CTstr_cutfrontHelper<CTstr<>, 0ul> { using val_T = CTstr<>; };
template<typename Str, size_t end>struct _CTstr_getfrontHelper { using val_T = typename _CTstr_appendHelper<typename _CTstr_getfrontHelper<Str, end - 1ul>::val_T, typename _CTstr_cutfrontHelper<Str, end - 1ul>::val_T::Car>::val_T; };
template<typename Str>struct _CTstr_getfrontHelper<Str, 0ul> { using val_T = CTstr<>; };
template<size_t end>struct _CTstr_getfrontHelper<CTstr<>, end> { using val_T = CTstr<>; };
template<>struct _CTstr_getfrontHelper<CTstr<>, 0ul> { using val_T = CTstr<>; };
template<typename Str, typename Chr>struct _CTstr_findchrHelper { static constexpr size_t val = (std::is_same_v<typename Str::Car, Chr>) ? (0ul) : (1ul + _CTstr_findchrHelper<typename Str::Cdr, Chr>::val); };
template<typename Chr>struct _CTstr_findchrHelper<CTstr<>, Chr> { static constexpr size_t val = 0ul; };
template<typename Str1, typename Str2>struct _CTstr_findstrHelper { static constexpr size_t val = (Str1::size() < Str2::size()) ? (Str1::size()) : ((std::is_same_v<typename _CTstr_getfrontHelper<Str1, (Str1::size() < Str2::size()) ? (Str1::size()) : (Str2::size())>::val_T, Str2>) ? (0ul) : (1ul + _CTstr_findstrHelper<typename Str1::Cdr, Str2>::val)); };
template<typename Str>struct _CTstr_findstrHelper<CTstr<>, Str> { static constexpr size_t val = 0ul; };
template<typename Str1, typename Str2, typename Str3, bool replace = true>struct _CTstr_replaceallHelper { static constexpr size_t pos = _CTstr_findstrHelper<Str1, Str3>::val; using val_T = typename _CTstr_addHelper<typename _CTstr_addHelper<typename _CTstr_getfrontHelper<Str1, pos>::val_T, std::conditional_t<pos == Str1::size(), CTstr<>, Str2>>::val_T, typename _CTstr_replaceallHelper<typename _CTstr_cutfrontHelper<Str1, pos + Str3::size()>::val_T, Str2, Str3, pos != Str1::size()>::val_T>::val_T; };
template<typename Str1, typename Str2, typename Str3>struct _CTstr_replaceallHelper<Str1, Str2, Str3, false> { using val_T = Str1; };
template<typename Str1, typename Str2, bool replace>struct _CTstr_replaceallHelper<Str1, Str2, CTstr<>, replace> { using val_T = Str1; };
#define MakeCTstr(str) _CTstrMaker<_MakeCTstr256(str,0x)>::val_T
template<size_t n = 0, char Chr = u8'\0'> using CTstr_default = typename _CTstrMakerDefault<n, typename CTchr<Chr>>::val_T;
template<typename Str, typename Chr, typename = std::enable_if_t<Str::isCTstr&& Chr::isCTchr>>
using CTstr_append_T = typename _CTstr_addHelper<Str, Chr>::val_T;
template<typename Str1, typename Str2, typename = std::enable_if_t<Str1::isCTstr&& Str2::isCTstr>>
using CTstr_add_T = typename _CTstr_addHelper<Str1, Str2>::val_T;
template<typename Str, size_t begin = 0ul, typename = std::enable_if_t<Str::isCTstr>>
using CTstr_cutfront_T = typename _CTstr_cutfrontHelper<Str, CTmin<begin, Str::size()>>::val_T;
template<typename Str, size_t end = 0xfffffffful, typename = std::enable_if_t<Str::isCTstr>>
using CTstr_getfront_T = typename _CTstr_getfrontHelper<Str, CTmin<end, Str::size()>>::val_T;
template<typename Str, size_t rbegin = 0ul, typename = std::enable_if_t<Str::isCTstr>>
using CTstr_cutback_T = typename CTstr_getfront_T<Str, Str::size() - CTmin<rbegin, Str::size()>>;
template<typename Str, size_t rend = 0xfffffffful, typename = std::enable_if_t<Str::isCTstr>>
using CTstr_getback_T = typename CTstr_cutfront_T<Str, Str::size() - CTmin<rend, Str::size()>>;
template<typename Str, size_t begin = 0ul, size_t len = 0x7ffffffful, typename = std::enable_if_t<Str::isCTstr>>
using CTstr_substr_T = typename CTstr_getfront_T<CTstr_cutfront_T<Str, CTmin<begin, Str::size()>>, CTmin<CTadd<begin, len>, Str::size()>-CTmin<begin, Str::size()>>;
template<typename Str, typename Chr, size_t begin = 0, typename = std::enable_if_t<Str::isCTstr&& Chr::isCTchr>>
constexpr size_t CTstr_findchr_v = (_CTstr_findchrHelper<CTstr_cutfront_T<Str, CTmin<begin, Str::size()>>, Chr>::val == CTstr_cutfront_T<Str, CTmin<begin, Str::size()>>::size()) ? (CTstr<>::npos) : (CTmin<begin, Str::size()> +_CTstr_findchrHelper<CTstr_cutfront_T<Str, CTmin<begin, Str::size()>>, Chr>::val);
template<typename Str1, typename Str2, size_t begin = 0, typename = std::enable_if_t<Str1::isCTstr&& Str2::isCTstr>>
constexpr size_t CTstr_findstr_v = (_CTstr_findstrHelper<CTstr_cutfront_T<Str1, CTmin<begin, Str1::size()>>, Str2>::val == CTstr_cutfront_T<Str1, CTmin<begin, Str1::size()>>::size()) ? (CTstr<>::npos) : (CTmin<begin, Str1::size()> +_CTstr_findstrHelper<CTstr_cutfront_T<Str1, CTmin<begin, Str1::size()>>, Str2>::val);
template<typename Str1, typename Str2, size_t begin = 0ul, size_t len = 0x7ffffffful, typename = std::enable_if_t<Str1::isCTstr&& Str2::isCTstr>>
using CTstr_replace_T = typename CTstr_add_T<CTstr_add_T<typename CTstr_getfront_T<Str1, CTmin<begin, Str1::size()>>, Str2>, typename CTstr_cutfront_T<Str1, CTmin<CTadd<begin, len>, Str1::size()>>>;
template<typename Str1, typename Str2, typename Str3, typename = std::enable_if_t<Str1::isCTstr&& Str2::isCTstr&& Str3::isCTstr && !std::is_same_v<Str2, Str3> && (CTstr_findstr_v<Str2, Str3> == CTstr<>::npos)>>
using CTstr_replaceall_T = typename _CTstr_replaceallHelper<Str1, Str2, Str3>::val_T;

template<typename T>auto _CT_TypeName_F() { return CTstr_cutback_T<CTstr_cutfront_T<MakeCTstr(__FUNCSIG__), 1ul + CTstr_findchr_v<MakeCTstr(__FUNCSIG__), CTchr<'<'>>>, 7ul>(); }
template<typename T, T Enum>auto _CT_EnumName_F() { return CTstr_cutback_T<CTstr_cutfront_T<MakeCTstr(__FUNCSIG__), 0xffffffe2ul + 2 * CTstr_findchr_v<MakeCTstr(__FUNCSIG__), CTchr<','>>>, 7ul>(); }
#define CT_TypeName(T) decltype(_CT_TypeName_F<T>())
#define CT_EnumName(T, Enum) decltype(_CT_EnumName_F<T, T##::##Enum>())
#define CT_EnumName_v(T, num) decltype(_CT_EnumName_F<T, (T)num>())
template<typename...>struct CTformat;
template<typename = void>class CTformat_buffer;
template<typename, typename>struct CTformat_atom;
template<bool, size_t, size_t, typename, typename, typename, size_t, typename...>class combined;
template<size_t _reserve, size_t d_reserve, typename Buffer, typename Atom, typename FmtNext, size_t pos, typename...Args>
class combined<false, _reserve, d_reserve, Buffer, Atom, FmtNext, pos, Args...> {
	template<size_t...i>
	static void _format_elem(Buffer& buffer, std::index_sequence<i...>, Args...args) {
		Atom::_format<0ul>(buffer, CTget<i, Args...>::get(args...)...);
	}
	template<size_t...i>
	static void _format_next(Buffer& buffer, std::index_sequence<i...>, Args...args) {
		FmtNext::_format(buffer, CTget<i + pos, Args...>::get(args...)...);
	}
public:
	template<size_t reserve = 0ul>
	static void _format(Buffer& buffer, Args...args) {
		_format_elem(buffer, std::make_index_sequence<pos>(), args...);
		_format_next(buffer, std::make_index_sequence<sizeof...(Args) - pos>(), args...);
		if constexpr (reserve)buffer.reserve(reserve);
	}
	static decltype(auto) format(Args...args) {
		Buffer ans;
		if constexpr ((d_reserve != 0xfffffffful) && (d_reserve != 0ul))ans.reserve(d_reserve);
		_format(ans, args...);
		return ans.get();
	}
};
template<size_t _reserve, size_t d_reserve, typename Buffer, typename Atom, typename FmtNext, size_t pos, typename...Args>
class combined<true, _reserve, d_reserve, Buffer, Atom, FmtNext, pos, Args...> {
	template<size_t...i>
	static void _format_elem(Buffer& buffer, std::index_sequence<i...>, Args...args) {
		Atom::_format<_reserve>(buffer, CTget<i, Args...>::get(args...)...);
	}
	template<size_t...i>
	static void _format_next(Buffer& buffer, std::index_sequence<i...>, Args...args) {
		FmtNext::_format(buffer, CTget<i + pos, Args...>::get(args...)...);
	}
public:
	template<size_t reserve = 0ul>
	static void _format(Buffer& buffer, Args...args) {
		_format_elem(buffer, std::make_index_sequence<pos>(), args...);
		_format_next(buffer, std::make_index_sequence<sizeof...(Args) - pos>(), args...);
		if constexpr (reserve)buffer.reserve(reserve);
	}
	static decltype(auto) format(Args...args) {
		Buffer ans;
		if constexpr ((d_reserve != 0xfffffffful) && (d_reserve != 0ul))ans.reserve(d_reserve);
		_format(ans, args...);
		return ans.get();
	}
};

template<bool reserve, size_t _reserve, size_t d_reserve, typename Buffer, typename Atom, typename...ArgsAtom>
struct AtomWrapper {
	template<typename...>struct _combine;
	template<typename Fmt, typename...ArgsFmt>struct _combine<Fmt, void(*)(Buffer&, ArgsFmt...)> { using type_T = typename combined<reserve, _reserve, d_reserve, Buffer, Atom, Fmt, sizeof...(ArgsAtom), ArgsAtom..., ArgsFmt...>; };
	template<typename Fmt>using combine_T = typename _combine<Fmt, decltype(&Fmt::template _format<0>)>::type_T;
};
template<bool, size_t, size_t, typename, typename, typename>struct _AtomFmt;
template<bool reserve, size_t _reserve, size_t d_reserve, typename Buffer, typename Atom, typename Fmt, typename...ArgsAtom>struct _AtomFmt<reserve, _reserve, d_reserve, Atom, void(*)(Buffer&, ArgsAtom...), Fmt> { using type_T = typename AtomWrapper<reserve, _reserve, d_reserve, Buffer, Atom, ArgsAtom...>::template combine_T<Fmt>; };
template<bool reserve, size_t _reserve, size_t d_reserve, typename Atom, typename Fmt>using AtomFmt = typename _AtomFmt<reserve, _reserve, d_reserve, Atom, decltype(&Atom::template _format<0ul>), Fmt>::type_T;



template<typename Buffer_T, typename car, typename...cdr>
struct CTformat<typename CTformat_buffer<Buffer_T>, car, cdr...> :
	public AtomFmt<
	(CTformat_atom<typename CTformat_buffer<Buffer_T>, car>::sizeDefault != CTformat_atom<typename CTformat_buffer<Buffer_T>, car>::sizeMax) && (CTformat<typename CTformat_buffer<Buffer_T>, cdr...>::reserve_extern != 0xfffffffful),
	CTformat<typename CTformat_buffer<Buffer_T>, cdr...>::reserve_extern,
	CTadd<CTformat_atom<typename CTformat_buffer<Buffer_T>, car>::sizeDefault, CTformat<typename CTformat_buffer<Buffer_T>, cdr...>::reserve_default>,
	typename CTformat_atom<typename CTformat_buffer<Buffer_T>, car>,
	typename CTformat<typename CTformat_buffer<Buffer_T>, cdr...>
	> {
	using Buffer = CTformat_buffer<Buffer_T>;
	using Car = typename CTformat_atom<Buffer, car>;
	using Cdr = typename CTformat<Buffer, cdr...>;
	static constexpr bool isCTformat = true;
	static constexpr bool sizestatic = (Car::sizeDefault == Car::sizeMax);
	static constexpr size_t reserve_extern = (sizestatic) ? (CTadd<Car::sizeMax, Cdr::reserve_extern>) : (0ul);
	static constexpr size_t reserve_default = CTadd<Car::sizeDefault, Cdr::reserve_default>;
	template<typename...Args>static constexpr size_t _elemargsnum(void(*)(Buffer&, Args...)) { return sizeof...(Args); };
	static constexpr size_t elemargsnum = _elemargsnum(&Car::template _format<0ul>);
	static constexpr size_t argsnum = Cdr::argsnum + elemargsnum;
	using Base = typename AtomFmt<(Car::sizeDefault != Car::sizeMax) && (Cdr::reserve_extern != 0xfffffffful), Cdr::reserve_extern, reserve_default, Car, Cdr>;
};
template<typename Buffer>
struct CTformat<Buffer> {
	static constexpr bool isCTformat = true;
	static constexpr bool sizestatic = true;
	static constexpr size_t reserve_inner = 0ul;
	static constexpr size_t reserve_extern = 0ul;
	static constexpr size_t reserve_default = 0ul;
	static constexpr size_t elemargsnum = 0ul;
	static constexpr size_t argsnum = 0ul;
	template<size_t reserve = 0ul>
	static void _format(Buffer&) {}
};

template<>
class CTformat_buffer<void> {
	inline static size_t pos;
public:
	CTformat_buffer() { pos = 0ul; };
	void reserve(size_t size) { Cvp::__realloc_buffer<true>(pos + size); };
	//char* resize(size_t size) { Cvp::__realloc_buffer<true>(pos + size); memset(Cvp::__char_buffer + pos, 0, size); pos += size; return Cvp::__char_buffer + pos - size; };
	void put(const char* str, size_t size) { memcpy(Cvp::__char_buffer + pos, str, size); Cvp::__char_buffer[pos += size] = u8'0'; };
	const char* get() { Cvp::__char_buffer[pos] = u8'\0'; return Cvp::__char_buffer; }
};
template<>
class CTformat_buffer<string> {
	string __val;
public:
	void reserve(size_t size) { __val.reserve(__val.size() + size); };
	//char* resize(size_t size) { __val.append(size, u8'\0'); return &__val[__val.size() - size]; };
	void put(const char* str, size_t size) { __val.append(str, size); };
	string get() { if (__val.capacity() > __val.size() * 2)__val.shrink_to_fit(); return move(__val); }
};

template<typename Buffer>struct CTformat_atom<Buffer, int> {
	inline static constexpr size_t sizeDefault = 11ul;
	inline static constexpr size_t sizeMax = 11ul;
	template<size_t reserve>
	static void _format(Buffer& buffer, int a) {
		char temp[11];
		char* p = &temp[12];
		bool sub = (a < 0);
		if (a < 0)a = -a;
		if (!a)*(--p) = u8'0';
		while (a)*(--p) = (a % 10 + u8'0'), a /= 10;
		if (sub)*(--p) = u8'-';
		buffer.put(p, &temp[12] - p);
	}
};
template<typename Buffer>struct CTformat_atom<Buffer, DWORD> {
	inline static constexpr size_t sizeDefault = 10ul;
	inline static constexpr size_t sizeMax = 10ul;
	template<size_t reserve>
	static void _format(Buffer& buffer, DWORD a) {
		char temp[10];
		char* p = &temp[11];
		if (!a)*(--p) = u8'0';
		while (a)*(--p) = __hex_table[a & 0xf], a >>= 4;
		*(--p) = u8'x';
		*(--p) = u8'0';
		buffer.put(p, &temp[11] - p);
	}
};
template<typename Buffer>struct CTformat_atom<Buffer, void*> {
	inline static constexpr size_t sizeDefault = 10ul;
	inline static constexpr size_t sizeMax = 10ul;
	template<size_t reserve>
	static void _format(Buffer& buffer, void* p) {
		DWORD a = (DWORD)p;
		char temp[10];
		temp[9] = __hex_table[a & 0xf], a >>= 4;
		temp[8] = __hex_table[a & 0xf], a >>= 4;
		temp[7] = __hex_table[a & 0xf], a >>= 4;
		temp[6] = __hex_table[a & 0xf], a >>= 4;
		temp[5] = __hex_table[a & 0xf], a >>= 4;
		temp[4] = __hex_table[a & 0xf], a >>= 4;
		temp[3] = __hex_table[a & 0xf], a >>= 4;
		temp[2] = __hex_table[a & 0xf], a >>= 4;
		temp[1] = u8'x';
		temp[0] = u8'0';
		buffer.put(&temp[0], 10ul);
	}
};
template<typename Buffer>struct CTformat_atom<Buffer, float> {
	inline static constexpr size_t sizeDefault = 10ul;
	inline static constexpr size_t sizeMax = 0xfffffffful;
	template<size_t reserve>
	static void _format(Buffer& buffer, float a) {
		const int len = _scprintf(u8"%g", a);
		char* p = (char*)_malloca(len + 1);
		snprintf(p, len + 1, u8"%g", a);
		buffer.put(p, len);
		_freea(p);
	}
};
template<typename Buffer, typename...Args>struct CTformat_atom<Buffer, typename CTformat<Args...>>:public CTformat<Args...>::Base {
	inline static constexpr size_t sizeDefault = CTformat<Args...>::reserve_default;
	inline static constexpr size_t sizeMax = 0xfffffffful;
};
template<typename Buffer>struct CTformat_atom<Buffer, string_view> {
	inline static constexpr size_t sizeDefault = 0x10ul;
	inline static constexpr size_t sizeMax = 0xfffffffful;
	template<size_t reserve>
	static void _format(Buffer& buffer, const char* str, size_t len) { buffer.reserve(reserve + len); buffer.put(str, len); }
};
template<typename Buffer>struct CTformat_atom<Buffer, const char*> {
	inline static constexpr size_t sizeDefault = 0x10ul;
	inline static constexpr size_t sizeMax = 0xfffffffful;
	template<size_t reserve>
	static void _format(Buffer& buffer, const char* str) { buffer.reserve(reserve + strlen(str)); buffer.put(str, strlen(str)); }
};
template<typename Buffer, typename...Args>struct CTformat_atom<Buffer, typename CTstr<Args...>> {
	using Str = typename CTstr<Args...>;
	inline static constexpr size_t sizeDefault = Str::size();
	inline static constexpr size_t sizeMax = Str::size();
	template<size_t>
	static void _format(Buffer& buffer) { buffer.put(Str::c_str(), Str::size()); }
};
namespace Cvp{
	inline string __wcs2utf(wstring_view in) {
		int len = WideCharToMultiByte(CP_UTF8, 0, in.data(), in.size(), __char_buffer, __buffer_size, nullptr, nullptr);
		if (__realloc_buffer(len + 1))len = WideCharToMultiByte(CP_UTF8, 0, in.data(), in.size(), __char_buffer, __buffer_size, nullptr, nullptr);
		__char_buffer[len] = u8'\0';
		return string(__char_buffer);
	}
	inline wstring __utf2wcs(string_view in) {
		int len = MultiByteToWideChar(CP_UTF8, 0, in.data(), in.size(), __wchar_buffer, __buffer_size / sizeof(wchar_t));
		if (__realloc_buffer((len + 1) * sizeof(wchar_t)))len = MultiByteToWideChar(CP_UTF8, 0, in.data(), in.size(), __wchar_buffer, __buffer_size / sizeof(wchar_t)); ;
		__wchar_buffer[len] = L'\0';
		return wstring(__wchar_buffer);
	}
	inline DWORD __murmurhash32(string_view str) {
		DWORD hash = 0x0ul;
		DWORD temp = 0x0ul;
		DWORD* p = (DWORD*)str.data();
		for (DWORD* q = p + (str.size() >> 2); p != q; ++p) {
			temp = *p;
			temp *= 0xcc9e2d51ul;
			temp = (temp << 15) | (temp >> 17);
			temp *= 0x1b873593ul;
			hash ^= temp;
			hash = (hash << 13) | (hash >> 19);
			hash = (hash * 5) + 0xe6546b64ul;
		}
		temp = *p;
		temp &= (0xfffffffful >> ((4 - (str.size() % 3)) << 3));
		temp *= 0xcc9e2d51ul;
		temp = (temp << 15) | (temp >> 17);
		temp *= 0x1b873593ul;
		hash ^= temp;
		hash ^= str.size();
		hash ^= hash >> 16;
		hash *= 0x85ebca6bul;
		hash ^= hash >> 13;
		hash *= 0xc2b2ae35ul;
		hash ^= hash >> 16;
		return hash;
	}


	template<typename Ret, typename F, typename...Args>decltype(auto)__convertfunctionhelper(typename Ret(__thiscall F::*)(Args...)const, const F& func) { return function<Ret(Args...)>(func); }
	template<typename Ret, typename F, typename...Args>decltype(auto)__convertfunctionhelper(typename Ret(__thiscall F::*)(Args...)const, F&& func) { return function<Ret(Args...)>(move(func)); }
	template<typename F>decltype(auto)convertfunction(F&& func) { return __convertfunctionhelper(&std::_Remove_cvref_t<F>::operator(), forward<F>(func)); }

	template<size_t i, typename T, typename...Args>
	struct ArgsRankTrait {
		using type = typename ArgsRankTrait<i - 1, Args...>::type;
	};
	template<typename T, typename...Args>
	struct ArgsRankTrait<0, T, Args...> {
		using type = T;
	};
	template<size_t i, typename T>
	struct ArgsRankTrait<i, T>;
	template<typename T>
	struct ArgsRankTrait<0, T> {
		using type = T;
	};
	template<typename F>
	struct FunctorTrait {
		template<typename Ret, typename...Args>
		static constexpr size_t argsNumHelper(typename Ret(__thiscall std::_Remove_cvref_t<F>::*)(Args...)const) { return sizeof...(Args); };
		static constexpr size_t argsnum = argsNumHelper(&std::_Remove_cvref_t<F>::operator());

		template<size_t i, typename Ret, typename...Args>
		static auto argsPosHelper(typename Ret(__thiscall std::_Remove_cvref_t<F>::*)(Args...)const)->typename ArgsRankTrait<i, Args...>::type;
		template<size_t i>using argspos_T = decltype(argsPosHelper<i>(&std::_Remove_cvref_t<F>::operator()));

		template<typename Ret, typename...Args>
		static auto retHelper(typename Ret(__thiscall std::_Remove_cvref_t<F>::*)(Args...)const)->Ret;
		using ret_T = decltype(retHelper(&std::_Remove_cvref_t<F>::operator()));
	};
	template<size_t i, typename...Args>using argsnpos_T = typename ArgsRankTrait<i, Args...>::type;
	template<typename F, size_t i>using funcargspos_T = typename FunctorTrait<F>::template argspos_T<i>;
	template<typename F>static constexpr size_t funcargsnum = typename FunctorTrait<F>::argsnum;
	template<typename F>using ret_T = typename FunctorTrait<F>::ret_T;
	template<typename F, size_t ...i, typename Tuple>decltype(auto)__callfunc_helper(const F& func, std::index_sequence<i...>, Tuple&& tuple) { return func(get<i>(tuple)...); }
	template<typename F, typename ...Args>decltype(auto)callfunc(const F& func, const tuple<Args...>& args) { return __callfunc_helper(func, std::index_sequence_for<Args...>(), args); }
	template<typename F, typename ...Args>decltype(auto)callfunc(const F& func, tuple<Args...>&& args) { return __callfunc_helper(func, std::index_sequence_for<Args...>(), move(args)); }
	template<size_t n, typename F, typename Iterator, typename = std::enable_if_t<n>, typename...Args>decltype(auto)__callfunc_helper_l(const F& func, Iterator begin, Args&&...rest) { return __callfunc_helper_l<n - 1>(func, begin++, *begin, forward<Args>(rest)...); }
	template<size_t n, typename F, typename Iterator, typename = void, typename = std::enable_if_t<!n>, typename...Args>decltype(auto)__callfunc_helper_l(const F& func, Iterator begin, Args&&...rest) { return func(forward<Args>(rest)...); }
	template<typename F, typename T, template<typename...>typename Container>decltype(auto)callfunc(const F& func, const Container<T>& args) { return __callfunc_helper_l<argsnum_T<F>::value>(func, args.begin()); }
	template<size_t n, typename F, typename Iterator, typename = std::enable_if_t<n>, typename...Args>decltype(auto)__callfunc_helper_r(const F& func, Iterator begin, Args&&...rest) { return __callfunc_helper_r<n - 1>(func, begin++, move(*begin), forward<Args>(rest)...); }
	template<size_t n, typename F, typename Iterator, typename = void, typename = std::enable_if_t<!n>, typename...Args>decltype(auto)__callfunc_helper_r(const F& func, Iterator begin, Args&&...rest) { return func(forward<Args>(rest)...); }
	template<typename F, typename T, template<typename...>typename Container>decltype(auto)callfunc(const F& func, Container<T>&& args) { return __callfunc_helper_r<argsnum_T<F>::value>(func, args.begin()); }





	class KeyCode {
		BYTE __key;
		bool __shift;
		bool __ctrl;
		bool __alt;
	public:
		KeyCode(::KeyCode key, bool shift = false, bool ctrl = false, bool alt = false) :__key((BYTE)(DWORD)key), __shift(shift), __ctrl(ctrl), __alt(alt) {}
		::KeyCode Code()const { return (::KeyCode)(DWORD)__key; }
		DWORD Val()const { return *(DWORD*)this; }
		static constexpr DWORD MakeVal(::KeyCode key, bool shift = false, bool ctrl = false, bool alt = false) {
			return (DWORD)key | (shift ? 0x100u : 0) | (shift ? 0x10000ul : 0) | (shift ? 0x1000000ul : 0);
		}
		bool Shift()const { return __shift; }
		bool Ctrl()const { return __ctrl; }
		bool Alt()const { return __alt; }
		bool operator==(const KeyCode& that) { return Val() == that.Val(); }
	};
	enum class MouseCode :DWORD { LEFT, RIGHT, MID };



	template <typename... Args>
	string format(const char* format, Args... args) {
		__clear_buffer();
		size_t n = snprintf(__char_buffer, __buffer_size, format, args...);
		if (__realloc_buffer(n))n = snprintf(__char_buffer, __buffer_size, format, args...);
		return string(__char_buffer, n);
	}


	template <typename... Args>
	int __msgbox(DWORD a, const char* _format, Args... args) {
		char temp[10];
		temp[9] = __hex_table[a & 0xf], a >>= 4;
		temp[8] = __hex_table[a & 0xf], a >>= 4;
		temp[7] = __hex_table[a & 0xf], a >>= 4;
		temp[6] = __hex_table[a & 0xf], a >>= 4;
		temp[5] = __hex_table[a & 0xf], a >>= 4;
		temp[4] = __hex_table[a & 0xf], a >>= 4;
		temp[3] = __hex_table[a & 0xf], a >>= 4;
		temp[2] = __hex_table[a & 0xf], a >>= 4;
		temp[1] = u8'x';
		temp[0] = u8'0';
		return MessageBoxA(0, format(_format, args...).data(), &temp[0], 0);
	}
	template <>
	inline int __msgbox<>(DWORD a, const char* _format) {
		char temp[11];
		temp[10] = u8'\0';
		temp[9] = __hex_table[a & 0xf], a >>= 4;
		temp[8] = __hex_table[a & 0xf], a >>= 4;
		temp[7] = __hex_table[a & 0xf], a >>= 4;
		temp[6] = __hex_table[a & 0xf], a >>= 4;
		temp[5] = __hex_table[a & 0xf], a >>= 4;
		temp[4] = __hex_table[a & 0xf], a >>= 4;
		temp[3] = __hex_table[a & 0xf], a >>= 4;
		temp[2] = __hex_table[a & 0xf], a >>= 4;
		temp[1] = u8'x';
		temp[0] = u8'0';
		return MessageBoxA(0, _format, &temp[0], 0);
	}

	template <typename... Args>
	__declspec(noreturn)void error(const char* _format, Args... args) {
		__msgbox(GetLastError(), _format, args...);
		*(char*)0 = u8'!';
	}

#ifdef WIN32
	inline DWORD __declspec(naked)__getCurrentAddr() {
		__asm {
			pop eax
			push eax
			ret
		}
	}
#endif
	template<typename = void>inline int msgbox(DWORD addr) { return __msgbox(addr, nullptr); }
	template<typename = void>inline int msgbox(DWORD addr, void* val) { return __msgbox(addr, CTformat<CTformat_buffer<>, void*>::format(val)); }
	template<typename = void>inline int msgbox(DWORD addr, const char* val) { return __msgbox(addr, val); }
	template<typename T>std::enable_if_t<std::numeric_limits<T>::is_integer&& std::numeric_limits<T>::is_signed, int> msgbox(DWORD addr, T val) { return __msgbox(addr, CTformat<CTformat_buffer<>, int>::format(val)); }
	template<typename T>std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed, int> msgbox(DWORD addr, T val) { return __msgbox(addr, CTformat<CTformat_buffer<>, DWORD>::format(val)); }
	template<typename T>std::enable_if_t<std::numeric_limits<T>::is_iec559, int> msgbox(DWORD addr, T val) { return __msgbox(addr, CTformat<CTformat_buffer<>, float>::format(val)); }
	template<typename... Args>int msgbox(DWORD addr, const char* _format, Args&&... args) { return __msgbox(addr, format(_format, args...).data()); }
	template <typename... Args>inline int MsgBox(Args&&... args) { return msgbox(__getCurrentAddr(), forward<Args>(args)...); }


	template<typename T>
	inline std::enable_if_t<std::is_trivially_copyable_v<T>, T> RegRead(const char* key, const char* path = u8"Software\\cvp") {
		T ans;
		ZeroMemory(&ans, sizeof(T));
		HKEY hkey;
		DWORD size = sizeof(T);
		DWORD type = REG_BINARY;
		if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_READ, &hkey))RegQueryValueExA(hkey, key, 0, &type, (LPBYTE)&ans, &size);
		RegCloseKey(hkey);
		return ans;
	}
	template<typename T>
	inline std::enable_if_t<std::is_trivially_copyable_v<T>> RegRead(T& ans, const char* key, const char* path = u8"Software\\cvp") {
		HKEY hkey;
		DWORD size = sizeof(T);
		DWORD type = REG_BINARY;
		if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_READ, &hkey))RegQueryValueExA(hkey, key, 0, &type, (LPBYTE)&ans, &size);
		RegCloseKey(hkey);
	}
	template<typename T>
	inline std::enable_if_t<std::is_trivially_copyable_v<T>> RegWrite(const T& value, const char* key, const char* path = u8"Software\\cvp") {
		HKEY hkey;
		DWORD dw;
		DWORD type = REG_BINARY;
		if (ERROR_SUCCESS == RegCreateKeyExA(HKEY_CURRENT_USER, path, 0, u8"Key", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hkey, &dw))RegSetValueExA(hkey, key, 0, type, (const BYTE*)&value, sizeof(T));
		RegCloseKey(hkey);
	}



	inline void ClipBoardWrite(string_view str) {
		if (!OpenClipboard(0))return;
		EmptyClipboard();
		HANDLE hStr = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(char) * (str.size() + 1));
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			strcpy_s((char*)p, str.size() + 1, str.data());
			((char*)p)[str.size()] = u8'\0';
			GlobalUnlock(hStr);
			SetClipboardData(CF_TEXT, hStr);
		}
		CloseClipboard();
	}
	inline void ClipBoardWrite(wstring_view str) {
		if (!OpenClipboard(0))return;
		EmptyClipboard();
		HANDLE hStr = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(wchar_t) * (str.size() + 1));
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			wcscpy_s((wchar_t*)p, str.size() + 1, str.data());
			((wchar_t*)p)[str.size()] = L'\0';
			GlobalUnlock(hStr);
			SetClipboardData(CF_UNICODETEXT, hStr);
		}
		CloseClipboard();
	}
	inline void ClipBoardRead(string& ans) {
		ans.clear();
		if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(0))return;
		HANDLE hStr = GetClipboardData(CF_TEXT);
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			ans = (char*)p;
			GlobalUnlock(hStr);
		}
		CloseClipboard();
	}
	inline void ClipBoardRead(wstring& ans) {
		ans.clear();
		if (!IsClipboardFormatAvailable(CF_UNICODETEXT) || !OpenClipboard(0))return;
		HANDLE hStr = GetClipboardData(CF_UNICODETEXT);
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			ans = (wchar_t*)p;
			GlobalUnlock(hStr);
		}
		CloseClipboard();
	}
	template<typename T>T ClipBoardRead();
	template<>inline string ClipBoardRead<string>() {
		string ans;
		if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(0))return ans;
		HANDLE hStr = GetClipboardData(CF_TEXT);
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			ans = (char*)p;
			GlobalUnlock(hStr);
		}
		CloseClipboard();
		return ans;
	}
	template<>inline wstring ClipBoardRead<wstring>() {
		wstring ans;
		if (!IsClipboardFormatAvailable(CF_UNICODETEXT) || !OpenClipboard(0))return ans;
		HANDLE hStr = GetClipboardData(CF_UNICODETEXT);
		if (hStr) {
			void* p = GlobalLock(hStr);
			if (!p)error(u8"malloc failed");
			ans = (wchar_t*)p;
			GlobalUnlock(hStr);
		}
		CloseClipboard();
		return ans;
	}

	class hash32 {
		using NodeT = pair<DWORD, void*>;
		NodeT* __buffer;
		DWORD __mask;
		size_t __size;
		size_t __half_capacity;
	public:
		static DWORD hash(string_view str) { return __murmurhash32(str) | 0x00010000ul; }
		hash32(void* _default = nullptr, size_t half_capacity = 0x100ul) :__buffer(valloc(half_capacity * 2 * sizeof(NodeT))), __mask(half_capacity * 2 - 1), __size(0), __half_capacity(half_capacity) { __buffer[__mask] = make_pair(0x0000fffful, _default); }
		hash32(const hash32&) = delete;
		hash32& operator=(const hash32&) = delete;
		hash32(hash32&& that)noexcept :__buffer(that.__buffer), __mask(that.__mask), __size(that.__size), __half_capacity(that.__half_capacity) { that.__buffer = nullptr; }
		hash32& operator=(hash32&& that)noexcept { vfree(__buffer); __buffer = that.__buffer; __mask = that.__mask; __size = that.__size; __half_capacity = that.__half_capacity; that.__buffer = nullptr; return *this; }
		~hash32() { vfree(__buffer); }
		class iterator {
			friend class hash32;
			NodeT* __p;
			iterator(NodeT* p) :__p(p) {}
			iterator& normalize() { while (__p[0].first == 0x0ul) ++__p; return *this; }
		public:
			NodeT* operator->() { return __p; }
			NodeT& operator*() { return *__p; }
			iterator& operator++() { ++__p; return normalize(); }
			bool operator==(iterator that) { return __p == that.__p; }
			bool operator!=(iterator that) { return __p != that.__p; }
		};
		void clear() { __size = 0; memset(__buffer, 0, __mask * sizeof(NodeT)); }
		iterator begin()const { return iterator(__buffer).normalize(); };
		iterator end()const { return iterator(__buffer + __mask); };
		void*& find(DWORD key)const {
			key |= 0x00010000ul;
			size_t i = __mask & key;
			while (__buffer[i].first) {
				if (__buffer[i].first == key)return __buffer[i].second;
				i += key >> 16;
				i &= __mask;
			}
			return __buffer[__mask].second;
		}
		void*& find(string_view key)const { return find(hash(key)); }
		void*& operator[](DWORD key) {
			key |= 0x00010000ul;
			size_t i = __mask & key;
			while (__buffer[i].first) {
				if (__buffer[i].first == key)return __buffer[i].second;
				i += key >> 16;
				i &= __mask;
			}
			++__size;
			if (__size == __half_capacity) {
				hash32 newhash(end()->second, __half_capacity * 2);
				for (auto&& p : *this)newhash[p.first] = p.second;
				void** ans=&newhash[key];
				*this = move(newhash);
				return *ans;
			} else {
				__buffer[i] = make_pair(key, end()->second);
				return __buffer[i].second;
			}
		}
		void*& operator[](string_view key) { return (*this)[hash(key)]; }
	};


	class Buffer {
		friend class DataMap;
		BYTE* __head;
		BYTE* __begin;
		BYTE* __end;
		BYTE* __tail;
		void __realloc(int size) {
			if (__tail - __head >= size * 2) {
				memcpy(__head, __begin, __end - __begin);
				__end = __end - __begin + __head;
				__begin = __head;
			} else {
				BYTE* _new = valloc(size * 2);
				memcpy(_new, __begin, __end - __begin);
				__tail = _new + size * 2;
				__end = __end - __begin + _new;
				__begin = _new;
				vfree(__head);
				__head = _new;
			}
		}
	public:
		Buffer(DWORD size = 0x1000u) :__head(valloc(size)), __begin(__head), __end(__head), __tail(__head + 0x1000u) {}
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer(Buffer&& that) noexcept :__head(that.__head), __begin(that.__begin), __end(that.__end), __tail(that.__tail) {
			that.__head = that.__begin = that.__end = that.__tail = nullptr;
		};
		Buffer& operator=(Buffer&& that) noexcept {
			vfree(__head);
			__head = that.__head; __begin = that.__begin; __end = that.__end; __tail = that.__tail;
			that.__head = that.__begin = that.__end = that.__tail = nullptr;
		}
		Buffer(const char* path) {
			FILE* aFP;
			fopen_s(&aFP, path, u8"rb");
			if (!aFP) {
				this->Buffer::Buffer();
				return;
			}
			DWORD size;
			fread(&size, sizeof(DWORD), 1, aFP);
			this->Buffer::Buffer(size);
			fread(__head, 1, size, aFP);
			__begin = __head;
			__end = __begin + size;
			fclose(aFP);
		}
		void Write(const char* path)const {
			FILE* aFP;
			fopen_s(&aFP, path, u8"wb");
			if (!aFP)error(CTformat<CTformat_buffer<void>, MakeCTstr(u8"serializing file access failed: "), const char*>::format(path));
			DWORD size;
			size = __end - __begin;
			fwrite(&size, sizeof(DWORD), 1, aFP);
			fwrite(__begin, 1, size, aFP);
			fclose(aFP);
		}
		~Buffer() { vfree(__head); }
		void Push(const void* p, int n) {
			if (__end + n > __tail)__realloc(__end - __begin + n);
			memcpy(__end, p, n);
			__end = __end + n;
		};
		void Pop(void* p, int n) {
			if (__begin + n > __end)error(u8"buffer pop failed: empty buffer");
			memcpy(p, __begin, n);
			__begin = __begin + n;
		};
		template<typename T>
		friend std::enable_if_t<std::is_trivially_copyable_v<T>, Buffer&> operator<<(Buffer& _this, const T& val) {
			_this.Push(&val, sizeof(T));
			return _this;
		}
		template<typename T>
		friend std::enable_if_t<std::is_trivially_copyable_v<T>, Buffer&> operator>>(Buffer& _this, T& val) {
			_this.Pop(&val, sizeof(T));
			return _this;
		}
		friend Buffer& operator<<(Buffer& _this, const string& val) {
			_this << val.size() + 1;
			_this.Push((void*)val.data(), val.size() + 1);
			return _this;
		}
		friend Buffer& operator>>(Buffer& _this, string& val) {
			DWORD len;
			_this >> len;
			__realloc_buffer(len);
			_this.Pop(__char_buffer, len);
			val = __char_buffer;
			return _this;
		}
		DWORD Test()const {
			if (__begin + sizeof(DWORD) > __end)return 0x0000fffful;
			return *(DWORD*)__begin;
		}
	};
	class DataMap {
	public:
		class Data {
			DWORD __size;
			union {
				BYTE* __buffer;
				DataMap* __child;
			};
		public:
			bool isEmpty()const { return !__buffer; }
			bool isData()const { return __buffer && __size != 0xfffffffful; }
			bool isTree()const { return __buffer && __size == 0xfffffffful; }
			void checkEmpty()const { if (!isEmpty())this->~Data(); }
			void checkNotEmpty()const { if (isEmpty())error(u8"Data get failed: empty data"); }
			void checkData()const { if (!isData())error(u8"Data get failed: pod needed"); }
			void checkTree()const { if (!isTree())error(u8"Data get failed: tree needed"); }
			Data(const Data&) = delete;
			Data(Data&& that) noexcept : __size(that.__size), __buffer(that.__buffer) {
				that.__buffer = nullptr;
			};
			Data() :__size(0), __buffer(nullptr) {}
			static Data& GlobalEmpty() {
				DataMap::_GlobalEmptyData.checkEmpty();
				return DataMap::_GlobalEmptyData;
			}
			~Data() {
				if (isData()) vfree(__buffer);
				else if (isTree()) __child->~DataMap(), vfree(__child);
				__buffer = nullptr;
			}
			Data& operator=(const Data&) = delete;
			Data& operator=(Data&& that)noexcept {
				checkEmpty();
				__size = that.__size;
				__buffer = that.__buffer;
				that.__buffer = nullptr;
				return *this;
			};
			template<typename T>
			void Push(const T& val) {
				checkEmpty();
				__size = Template::serializeN<T>(&val);
				__buffer = valloc(__size);
				Template::serialize(val, __buffer);
			}
			template<typename T>
			void Pop(T& val)const {
				checkData();
				Template::deserialize(val, __buffer, __size);
			}
			void SetChild(DataMap&& val) {
				checkEmpty();
				__size = 0xfffffffful;
				__child = new DataMap(move(val));
			}
			DataMap& GetChild()const {
				checkTree();
				return *__child;
			}
			void PushFromBuffer(Buffer& buffer) {
				checkEmpty();
				buffer >> __size;
				if (__size != 0xfffffffful) {
					__buffer = valloc(__size);
					buffer.Pop(__buffer, __size);
				} else {
					SetChild(DataMap());
					buffer >> *__child;
					DWORD temp;
					buffer >> temp;
				}
			}
			void PopToBuffer(Buffer& buffer)const {
				checkNotEmpty();
				if (isData()) {
					buffer << __size;
					buffer.Push(__buffer, __size);
				}
				if (isTree()) {
					buffer << 0xfffffffful;
					buffer << GetChild();
					buffer << 0x0000fffful;
				}
			}
		};
		static inline Data _GlobalEmptyData;
	private:
		vector<pair<DWORD, Data>> __map;
		struct cmp {
			bool operator()(const pair<DWORD, Data>& a, const pair<DWORD, Data>& b) { return a.first < b.first; }
			bool operator()(const pair<DWORD, Data>& a, DWORD b) { return a.first < b; }
			bool operator()(DWORD a, const pair<DWORD, Data>& b) { return a < b.first; }
		};
	public:
		DataMap(const DataMap&) = delete;
		DataMap& operator=(const DataMap&) = delete;
		DataMap(DataMap&& that) noexcept :__map(move(that.__map)) {}
		DataMap& operator=(DataMap&& that) noexcept { __map = move(that.__map); }
		DataMap() :__map() {}
		DataMap(const char* path) :__map() {
			Buffer(path) >> *this;
		}
		void Write(const char* path)const {
			(Buffer() << *this).Write(path);
		}
		friend Buffer& operator<<(Buffer& buffer, const DataMap& val) {
			for (auto&& p : val.__map)buffer << p.first, p.second.PopToBuffer(buffer);
			return buffer;
		}
		friend Buffer& operator>>(Buffer& buffer, DataMap& val) {
			while (buffer.Test() != 0x0000fffful) {
				{
					DWORD label;
					Data data;
					buffer >> label;
					data.PushFromBuffer(buffer);
					val.__map.emplace_back(move(label), move(data));
				}
			}
			return buffer;
		}
		Data& Get(DWORD label)const {
			auto p = std::equal_range(__map.begin(), __map.end(), label, cmp());
			if (p.first != p.second)return *(Data*)(&p.first->second);
			return Data::GlobalEmpty();
		}
		decltype(auto) begin()const {
			return __map.begin();
		}
		decltype(auto) end()const {
			return __map.end();
		}
		void Set(DWORD label, Data&& data) {
			__map.emplace_back(label, move(data));
		}
		void Sort() {
			std::sort(__map.begin(), __map.end(), cmp());
		}
	};
	using Data = DataMap::Data;
	class Command {
		template<typename...Args>
		struct funcWrapper {
			template<typename F, size_t...i>
			static function<string(vector<string_view>)> Wrap(F&& func, std::index_sequence<i...>) {
				return[func = forward<F>(func)](const vector<string_view>& vec)->string{
					if (funcargsnum<F>> vec.size())return u8"too few args";
					if constexpr (!std::is_same_v<void, ret_T<F>>)return Template::convertstr(func(forward<std::remove_cv_t<argsnpos_T<i, Args...>>>(Template::convert< std::_Remove_cvref_t<argsnpos_T<i, Args...>>>(vec[i]))...));
					func(forward<std::remove_cv_t<argsnpos_T<i, Args...>>>(Template::convert<std::_Remove_cvref_t<argsnpos_T<i, Args...>>>(vec[i]))...); return u8"";
				};
			}
		};
		template<typename F, size_t...i>
		static function<string(vector<string_view>)>* funcWrap(F&& func, std::index_sequence<i...>) {
			return new function<string(vector<string_view>)>(funcWrapper<funcargspos_T<F, i>...>::Wrap(forward<F>(func), std::index_sequence_for<funcargspos_T<F, i>...>()));
		}
		template<typename...Args>
		static std::enable_if_t <!sizeof...(Args), string*> __makeFormatHelper(string* input) {
			*input += u8" void";
			return input;
		}
		template<typename T, typename...Args>
		static std::enable_if_t <sizeof...(Args), string*> __makeFormatHelper(string* input) {
			*input += u8' ';
			*input += Template::makeFormat<T>(*input);
			return __makeFormatHelper<Args...>(input);
		}
		template<typename T>
		static string* __makeFormatHelper(string* input) {
			*input += u8' ';
			*input += Template::makeFormat<T>(*input);
			return input;
		}
		template<typename F, size_t...i>
		static string* __makeFormat(std::index_sequence<i...>) {
			return __makeFormatHelper<funcargspos_T<F, i>...>(new string());
		}

		string __command;
		function<bool(void)>* __active;
		vector<pair<string, Command*>> __children;
		function<string(const vector<string_view>)>* __func;
		const string* __format;
		struct cmp {
			bool operator()(const pair<string, Command*>& a, const pair<string, Command*>& b) { return a.first < b.first; }
			bool operator()(const pair<string, Command*>& a, const string& b) { return a.first < b; }
			bool operator()(const string& a, const pair<string, Command*>& b) { return a < b.first; }
		};
		bool __ifactive()const {
			if (__active && !(*__active)())return false;
			if (__func)return true;
			for (auto&& p : __children) if (p.second->__ifactive())return true;
			return false;
		}
		void __makeList(string_view head, size_t phead, vector<string>& dst, vector<string>& fdst, vector<string>& tdst)const {
			size_t space = head.find(u8' ', phead);
			string mode(head.substr(phead, space - phead));
			if (space != string_view::npos) {
				auto next = std::equal_range(__children.begin(), __children.end(), mode, cmp());
				if (next.first != next.second && next.first->second->__ifactive()) return next.first->second->__makeList(head, space + 1, dst, fdst, tdst);
				if (__format) {
					dst.emplace_back(head.substr(0, phead));
					fdst.emplace_back(head.substr(0, phead - 1)); fdst.back() += *__format;
					tdst.emplace_back(head.substr(phead));
				}
			} else {
				if (__format) {
					dst.emplace_back(head.substr(0, phead));
					fdst.emplace_back(head.substr(0, phead - 1)); fdst.back() += *__format;
					tdst.emplace_back(head.substr(phead));
				}
				auto _begin = std::lower_bound(__children.begin(), __children.end(), mode, cmp());
				if (_begin == __children.end())_begin = __children.begin();
				for (auto&& p = _begin; p != __children.end(); ++p) if (p->second->__ifactive()) {
					string t(head.substr(0, phead));
					t += p->second->__command;
					dst.emplace_back(t);
					fdst.emplace_back(move(t));
					tdst.emplace_back(u8"");
				}
			}
		}
		string __call(string_view cmd, size_t pcmd)const {
			size_t space = cmd.find(u8' ', pcmd);
			auto next = std::equal_range(__children.begin(), __children.end(), string(cmd.substr(pcmd, space - pcmd)), cmp());
			if (next.first != next.second)return next.first->second->__call(cmd, space + 1);
			if (!__func)return u8"invalid command";
			if (!__ifactive()) return u8"inactive command";
			vector<string_view> args;
			while (space != string_view::npos) {
				args.emplace_back(cmd.substr(pcmd, space - pcmd));
				pcmd = space + 1;
				space = cmd.find(u8' ', pcmd);
			}
			return (*__func)(args);
		}
	public:
		Command(Command&& that)noexcept :__command(move(that.__command)), __active(that.__active), __children(move(that.__children)), __func(that.__func), __format(that.__format) {
			that.__active = nullptr;
			that.__func = nullptr;
			that.__format = nullptr;
		}
		Command(const Command&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&& that) = delete;
		~Command() {
			delete __active;
			delete __func;
			delete __format;
			for (auto&& p : __children) delete p.second;
		}
		Command(string_view command) : __command(command), __active(nullptr), __children(), __func(nullptr), __format(nullptr) {}
		void InitActive(function<bool(void)>&& active) { if (!__active)__active = new function<bool(void)>(move(active)); }
		template<typename F, typename...Args>void InitFunc(F&& func) {
			if (__func) return;
			__func = funcWrap(forward<F>(func), std::make_index_sequence<funcargsnum<F>>());;
			__format = __makeFormat<F>(std::make_index_sequence<funcargsnum<F>>());
		}

		Command& operator+=(Command* that) {
			auto p = std::lower_bound(__children.begin(), __children.end(), that->__command, cmp());
			if (p == __children.end()) __children.emplace_back(make_pair(that->__command, that));
			else if (p->second->__command != that->__command)__children.insert(p, make_pair(that->__command, that));
			else {
				if (that->__format) {
					if (!p->second->__format)p->second->__format = that->__format, that->__format = nullptr, p->second->__func = that->__func, that->__func = nullptr;
					else if (*that->__format != *p->second->__format) error(
						CTformat<CTformat_buffer<void>, MakeCTstr(u8"Command combine conflicted: "), const char*, MakeCTstr(u8"("), const char*, MakeCTstr(u8") with "), const char*, MakeCTstr(u8"("), const char*, MakeCTstr(u8")")>::format(that->__command.data(), p->second->__format->data(), that->__command.data(), that->__format->data()));
				}
				for (auto&& q : that->__children) *p->second += q.second, q.second = nullptr;
				delete that;
			}
			return *this;
		}
		void __MakeList(string_view mode, vector<string>& dst, vector<string>& fdst, vector<string>& tdst)const {
			string newMode;
			char prev = u8' ';
			for (char chr : mode) {
				if (chr >= u8' ' && chr <= u8'~' && (prev != u8' ' || chr != u8' '))newMode += chr;
				prev = chr;
			}
			dst.clear();
			fdst.clear();
			tdst.clear();
			__makeList(newMode, 0, dst, fdst, tdst);
			if (dst.empty())dst.emplace_back(u8"");
			if (fdst.empty())fdst.emplace_back(u8"");
			if (tdst.empty())tdst.emplace_back(u8"");
			return;
		}
		string __Call(string_view cmd)const {
			string newCmd;
			char prev = u8' ';
			for (char chr : cmd) {
				if (chr >= u8' ' && chr <= u8'~' && (prev != u8' ' || chr != u8' '))newCmd += chr;
				prev = chr;
			}
			return __call(newCmd, 0);
		}
	};
	class UPCommand {
		mutable Command* __p;
	public:
		Command* Move()const { Command* ans = __p; __p = nullptr; return ans; }
		UPCommand(string_view command) :__p(new Command(command)) {}
		template<typename...Args>UPCommand(string_view command, Args&&...args) : __p(nullptr) { UPCommand temp(command); (*this) = move(temp)(forward< Args>(args)...); }
		UPCommand(const UPCommand&) = delete;
		UPCommand& operator=(const UPCommand&) = delete;
		UPCommand(UPCommand&& that)noexcept :__p(that.Move()) {}
		UPCommand& operator=(UPCommand&& that)noexcept { delete __p;  __p = that.Move(); return *this; }
		~UPCommand() { delete __p; }
		UPCommand& operator+=(const UPCommand& that) { *__p += that.Move(); return *this; };
		template<typename F, typename = void, typename = std::enable_if_t<!std::is_convertible_v<std::_Remove_cvref_t<F>, function<bool(void)>>>>UPCommand operator()(F&& func)&& { __p->InitFunc(convertfunction(move(func))); return move(*this); }
		template<typename F, typename = std::enable_if_t<std::is_convertible_v<std::_Remove_cvref_t<F>, function<bool(void)>>>>UPCommand operator()(F&& active)&& { __p->InitActive(move(active)); return move(*this); }
		template<typename = void>UPCommand operator()(initializer_list<UPCommand> children)&& { for (auto&& p : children)*__p += p.Move(); return move(*this); }
		template<typename = void>UPCommand operator()(UPCommand&& child)&& { *__p += child.Move(); return move(*this); }

		template<typename T, typename...Args>UPCommand operator()(T&& first, Args&&...args)&& { return move(*this)(forward<T>(first))(forward<Args>(args)...); }

		void __MakeList(string_view mode, vector<string>& dst, vector<string>& fdst, vector<string>& tdst)const { __p->__MakeList(mode, dst, fdst, tdst); }
		string Call(string_view cmd)const { return __p->__Call(cmd); }
	};
}
inline bool __inPvz_helper() {
	wchar_t modulePath[MAX_PATH];
	GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
	DWORD base = (DWORD)GetModuleHandleW(modulePath);
	return 0x49ECF563ul == *(DWORD*)(*(DWORD*)(base + 0x3Cu) + base + 0x8u);
}
inline bool __inPvz() {
	static bool val = __inPvz_helper(); return val;
}
#include "template.h"