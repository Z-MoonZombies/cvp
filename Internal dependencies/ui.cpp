#include "ui.h"
namespace Ui {
	SharedImage SharedImage::__makeAlphaImage(int w, int h, DWORD* bits) {
		SharedImage ans;
		ans.__p = new ref();
		ans->Create(w, h);
		DWORD* dst = ans->GetBits();
		for (int i = 0; i < w * h; ++i)*dst++ = ((*bits++) << 24) | 0xFFFFFFul;
		ans->BitsChanged();
		return ans;
	}
	SharedImage SharedImage::__makeEmptyImage() {
		return SharedImage(0, 0, nullptr);
	}
	SharedImage::SharedImage() :__p(nullptr) {}
	SharedImage::SharedImage(int w, int h, DWORD* bits) : __p(new ref()) {
		Image()->Create(w, h);
		DWORD* dst = Image()->GetBits();
		memcpy(dst, bits, w * h * sizeof(DWORD));
		Image()->BitsChanged();
	}
	SharedImage::SharedImage(int w, int h, DWORD* bits, Rect rect) : __p(new ref()) {
		Image()->Create(rect.mW, rect.mH);
		DWORD* dst = Image()->GetBits();
		bits += (rect.mX + rect.mY * w);
		for (int i = 0; i < rect.mH; ++i) {
			memcpy(dst, bits, rect.mW * sizeof(DWORD));
			bits += w;
			dst += rect.mW;
		}
		Image()->BitsChanged();
	}
	SharedImage::SharedImage(Pvz::DDImage* img) :__p(nullptr) {
		if (!img)return;
		__p = new ref();
		Image()->Create(img->mWidth, img->mHeight);
		DWORD* dst = Image()->GetBits();
		memcpy(dst, img->mBits, img->mWidth * img->mHeight * sizeof(DWORD));
		Image()->BitsChanged();
	}
	SharedImage::SharedImage(const SharedImage& that) :__p(that.__p) { if (__p)++__p->Num(); }
	SharedImage::SharedImage(SharedImage&& that)noexcept :__p(that.__p) { that.__p = nullptr; }
	SharedImage& SharedImage::operator=(const SharedImage& that) {
		if (this == &that)return *this;
		if (__p && --__p->Num() == 0)delete __p;
		__p = that.__p;
		if (__p)++__p->Num();
		return *this;
	}
	SharedImage& SharedImage::operator=(SharedImage&& that)noexcept {
		if (__p && --__p->Num() == 0)delete __p;
		__p = that.__p;
		that.__p = nullptr;
		return *this;
	}
	SharedImage::~SharedImage() { if (__p && --__p->Num() == 0)delete __p; }
	Pvz::DDImage* SharedImage::Image()const {
		if (!__p) return nullptr;
		return &__p->Image();
	}
	SharedImage SharedImage::MakeBranch()const {
		if (!Image()) return SharedImage();
		return SharedImage(Image()->mWidth, Image()->mHeight, Image()->mBits);
	}
	SharedImage& SharedImage::Branch() {
		if (!Image()) {
			SharedImage temp;
			*this = temp;
			return *this;
		}
		SharedImage temp(Image()->mWidth, Image()->mHeight, Image()->mBits);
		*this = temp; 
		return *this; 
	}
	Pvz::DDImage* SharedImage::operator->()const { return Image(); }
	Pvz::DDImage& SharedImage::operator*()const { return *Image(); }
	SharedImage::operator Pvz::DDImage* ()const { return Image(); }
	void SharedImage::Draw(DWORD theColor, const Rect& theSrcRect, const Matrix3& theTransform, bool mix, const Rect& theDestRect)const {
		if (!Image()) return;
		//return Pvz::gGameApp->mDDInterface->mScreenImage->BltMatrix(Image(), 0.0f, 0.0f, theTransform, theSrcRect, theColor, mix, theDestRect, true);
		Pvz::D3DInterface* dinterface = __d3dinterface();
		if (!dinterface)return;
		const Matrix3* pTrans = &theTransform;
		const Rect* pSrcRect = &theSrcRect;
		const Color color(theColor);
		const Color* pColor = &color;
		const Rect* pClipRect = &theDestRect;
		IDirect3DDevice7* pd = dinterface->mD3DDevice;
		if (dinterface->PreDraw() && dinterface->CreateImageTexture(Image())) {
			//dinterface->mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_LINEAR);
			dinterface->mD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
			dinterface->mD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, mix ? D3DBLEND_ONE : D3DBLEND_INVSRCALPHA);
			//dinterface->mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, true);
			if (!dinterface->mTransformStack.empty()) {
				Matrix3 aTransform = dinterface->mTransformStack.back() * theTransform;
				pTrans = &aTransform;
			}
			void* pData = Image()->mD3DData;
			__asm {
				push ebx
				mov ebx, pd
				mov ecx, pColor
				push 0
				push 0
				push 0
				push pClipRect
				push pSrcRect
				push pTrans
				push pData
				mov eax, 0x566C50ul
				call eax
				pop ebx
			}
		}
		return;
	}
	SharedImage::SharedImage(const string& path) :__p(nullptr) {
		ImageLib::Image* img = ImageLib::GetImage(path);
		if (!img) return;
		__p = new ref();
		Image()->Create(img->mWidth, img->mHeight);
		DWORD* dst = Image()->GetBits();
		DWORD* bits = img->mBits;
		memcpy(dst, img->mBits, sizeof(DWORD) * img->mWidth * img->mHeight);
		Image()->BitsChanged();
		delete img;
	}
	bool SharedImage::Write(const string& path)const {
		ImageLib::Image img;
		img.mBits = Image()->mBits;
		img.mWidth = Image()->mWidth;
		img.mHeight = Image()->mHeight;
		const char* p = path.data() + path.size();
		while (*--p != u8'.'); ++p;
		if (!strcmp(p, u8"jpg")) return ImageLib::WriteJPEGImage(path, &img);
		if (!strcmp(p, u8"png")) return ImageLib::WritePNGImage(path, &img);
		if (!strcmp(p, u8"bmp")) return ImageLib::WriteBMPImage(path, &img);
		img.mBits = nullptr;
		Cvp::error(CTformat<CTformat_buffer<void>, MakeCTstr(u8"format not supported: "), const char*>::format(p));
		return false;
	}
	SharedImage SharedImage::TakeScreenShot() {
		LPDIRECTDRAWSURFACE aSurface = Pvz::gGameApp->mDDInterface->mDrawSurface;
		Pvz::gGameApp->mDDInterface->mDrawSurface = nullptr;
		SharedImage ans;
		ans.__p = new ref();
		ans->SetSurface(aSurface);
		ans->GetBits();
		ans->mSurface->Release();
		ans->mSurface = nullptr;
		Pvz::gGameApp->mDDInterface->mDrawSurface = aSurface;
		return ans;
	}
	SharedImage SharedImage::GetClipBoard() {
		SharedImage ans;
		ans.__p = new ref();
		if (!IsClipboardFormatAvailable(CF_DIB) || !OpenClipboard(0))return ans;
		HANDLE hDib = GetClipboardData(CF_DIB);
		if (hDib) {
			void* p = GlobalLock(hDib);
			if (!p)Cvp::error(u8"malloc failed");
			BITMAPINFOHEADER* pHead = (BITMAPINFOHEADER*)p;
			ans.Image()->Create(pHead->biWidth, pHead->biHeight);
			DWORD* bits = (DWORD*)((DWORD)p + GlobalSize(hDib) - sizeof(DWORD) * pHead->biWidth * pHead->biHeight);
			DWORD* src = bits;
			DWORD* end = ans.Image()->GetBits();
			DWORD* dst = end + pHead->biWidth * (pHead->biHeight - 1);
			while (dst >= end)memcpy(dst, src, sizeof(DWORD) * pHead->biWidth), dst -= pHead->biWidth, src += pHead->biWidth;
			ans.Image()->BitsChanged();
			GlobalUnlock(hDib);
		}
		CloseClipboard();
		return ans;
	}
	void SharedImage::SetClipBoard()const {
		if (!OpenClipboard(0))return;
		EmptyClipboard();
		HGLOBAL hDib = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER) + sizeof(DWORD) * Image()->mWidth * Image()->mHeight);
		if (hDib) {
			void* p = GlobalLock(hDib);
			if (!p)Cvp::error(u8"malloc failed");
			BITMAPINFOHEADER* pHead = (BITMAPINFOHEADER*)p;
			pHead->biSize = sizeof(BITMAPINFOHEADER);
			pHead->biWidth = Image()->mWidth;
			pHead->biHeight = Image()->mHeight;
			pHead->biPlanes = 1;
			pHead->biBitCount = 32;
			pHead->biCompression = BI_RGB;
			DWORD* bits = (DWORD*)((DWORD)p + GlobalSize(hDib) - sizeof(DWORD) * pHead->biWidth * pHead->biHeight);
			DWORD* dst = bits;
			DWORD* end = Image()->GetBits();
			DWORD* src = end + pHead->biWidth * (pHead->biHeight - 1);
			while (src >= end)memcpy(dst, src, sizeof(DWORD) * pHead->biWidth), dst += pHead->biWidth, src -= pHead->biWidth;
			GlobalUnlock(hDib);
			SetClipboardData(CF_DIB, hDib);
		}
		CloseClipboard();
	}
	void Geo::DrawLine(DWORD color, const Point<float>* point, size_t pointNum) {
		LineTrip(color, point, pointNum);
	}
	void Geo::DrawLine(DWORD color, initializer_list<Point<float> > point) {
		LineTrip(color, point);
	}
	void Geo::DrawTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate) {
		LineTrip(color, {
			mid,
			mid + Point<float>(-width * cos(rotate) / 2 - height * sin(rotate),height * cos(rotate) - width * sin(rotate) / 2),
			mid + Point<float>(width * cos(rotate) / 2 - height * sin(rotate),height * cos(rotate) + width * sin(rotate) / 2),
			mid
			});
	}
	void Geo::DrawFullTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate) {
		TriangleList(color, {
			mid,
			mid + Point<float>(-width * cos(rotate) / 2 - height * sin(rotate),height * cos(rotate) - width * sin(rotate) / 2),
			mid + Point<float>(width * cos(rotate) / 2 - height * sin(rotate),height * cos(rotate) + width * sin(rotate) / 2)
			});
	}
	void Geo::DrawTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3) {
		LineTrip(color, { point1,point2,point3,point1 });
	}
	void Geo::DrawFullTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3) {
		TriangleList(color, { point1,point2,point3 });
	}
	void Geo::DrawRect(DWORD color, const Rect& rect, float roundR) {
		if (roundR == 0.0f) {
			LineTrip(color, {
				{rect.mX,rect.mY},
				{rect.mX + rect.mW,rect.mY},
				{rect.mX + rect.mW,rect.mY + rect.mH},
				{rect.mX,rect.mY + rect.mH},
				{rect.mX,rect.mY}
				});
		} else {
			roundR = min(min(rect.mH, rect.mW), roundR);
			int n = (((int)(roundR * 2.22f) / 4) | 1) + 1;
			Vertex* _list = (Vertex*)_malloca((n * 4 + 5) * sizeof(Vertex));
			float r = Pi / (n * 2), s = sin(r), c = cos(r);
			float x = -roundR, y = 0.0f;
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)rect.mY + roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)rect.mY + roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)rect.mX + roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)rect.mX + roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
			new(_list + n + 1)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
			LineTrip(_list - 3 * n - 3, n * 4 + 5);
			_freea(_list);
		}
	}
	void Geo::DrawFullRect(DWORD color, const Rect& rect, float roundR) {
		if (roundR == 0.0f) {
			TriangleTrip(color, {
				{rect.mX,rect.mY},
				{rect.mX + rect.mW + 1,rect.mY},
				{rect.mX,rect.mY + rect.mH + 1},
				{rect.mX + rect.mW + 1,rect.mY + rect.mH + 1}
				});
		} else {
			roundR = min(min(rect.mH, rect.mW), roundR);
			int n = (((int)(roundR * 2.22f) / 4) | 1) + 1;
			Vertex* _list = (Vertex*)_malloca((n * 4 + 6) * sizeof(Vertex));
			new(_list++)Vertex(((float)(rect.mX * 2 + rect.mW)) / 2, ((float)(rect.mY * 2 + rect.mH)) / 2, color);
			float r = Pi / (n * 2), s = sin(r), c = cos(r);
			float x = -roundR, y = 0.0f;
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)rect.mY + roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)(rect.mX + rect.mW + 1) - roundR, y + (float)rect.mY + roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)(rect.mX + rect.mW) - roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)(rect.mX + rect.mW + 1) - roundR, y + (float)(rect.mY + rect.mH + 1) - roundR, color);
			_list += (n + 1);
			for (int i = 0; i < n; ++i) {
				new(_list + i)Vertex(x + (float)rect.mX + roundR, y + (float)(rect.mY + rect.mH) - roundR, color);
				r = x * c - y * s;
				y = y * c + x * s;
				x = r;
			}
			new(_list + n)Vertex(x + (float)rect.mX + roundR, y + (float)(rect.mY + rect.mH + 1) - roundR, color);
			new(_list + n + 1)Vertex(x + (float)rect.mX + roundR, y + (float)rect.mY + roundR, color);
			TriangleFan(_list - 3 * n - 4, n * 4 + 6);
			_freea(_list);
		}
	}
	void Geo::DrawCircle(DWORD color, const Point<float>& mid, float radius) {
		DrawPolygon(color, ((int)(radius * 2.22f) | 7) + 1, mid, radius, 0.0f);
	}
	void Geo::DrawFullCircle(DWORD color, const Point<float>& mid, float radius) {
		DrawFullPolygon(color, ((int)(radius * 2.22f) | 7) + 1, mid, radius, 0.0f);
	}
	void Geo::DrawPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate) {
		float r = 2 * Pi / edgeNum, s = sin(r), c = cos(r);
		Vertex* _list = (Vertex*)_malloca((edgeNum + 1) * sizeof(Vertex));
		float x = radius * sin(rotate), y = -radius * cos(rotate);
		for (size_t i = 0; i <= edgeNum; ++i) {
			new(_list + i)Vertex(x + mid.mX, y + mid.mY, color);
			r = x * c - y * s;
			y = y * c + x * s;
			x = r;
		}
		LineTrip(_list, edgeNum + 1);
		_freea(_list);
	}
	void Geo::DrawFullPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate) {
		float r = 2 * Pi / edgeNum, s = sin(r), c = cos(r);
		Vertex* _list = (Vertex*)_malloca((edgeNum + 2) * sizeof(Vertex));
		new(_list++)Vertex(mid.mX, mid.mY, color);
		float x = radius * sin(rotate), y = -radius * cos(rotate);
		for (size_t i = 0; i <= edgeNum; ++i) {
			new(_list + i)Vertex(x + mid.mX, y + mid.mY, color);
			r = x * c - y * s;
			y = y * c + x * s;
			x = r;
		}
		TriangleFan(_list - 1, edgeNum + 2);
		_freea(_list);
	}
	void Geo::DrawPolygon(DWORD color, const Point<float>* point, size_t edgeNum) {
		Vertex* _list = (Vertex*)_malloca((edgeNum + 1) * sizeof(Vertex));
		for (size_t i = 0; i <= edgeNum; ++i)new(_list + i)Vertex(point[i].mX, point[i].mY, color);
		LineTrip(_list, edgeNum + 1);
		_freea(_list);
	}
	void Geo::DrawFullPolygon(DWORD color, const Point<float>* point, size_t edgeNum) {
		TriangleFan(color, point, edgeNum + 1);
	}
	void Geo::DrawPolygon(DWORD color, initializer_list<Point<float> > point) {
		Vertex* _list = (Vertex*)_malloca((point.size() + 1) * sizeof(Vertex));
		for (size_t i = 0; i <= point.size(); ++i)new(_list + i)Vertex(point.begin()[i].mX, point.begin()[i].mY, color);
		LineTrip(_list, point.size() + 1);
		_freea(_list);
	}
	void Geo::DrawFullPolygon(DWORD color, initializer_list<Point<float> > point) {
		TriangleFan(color, point);
	}
	Font::Font():__w(0), __h(0), __g(0), __buffer(new SharedImage[0x10000ul]()) {}
	Font::~Font() {
		delete[] __buffer;
	}
	int Font::GetStringWidth(string_view str)const {
		return GetStringWidth(Template::convert<wstring>(str));
	}
	int Font::GetStringHeight(string_view str, int w)const {
		return GetStringHeight(Template::convert<wstring>(str), w);
	}
	int Font::GetStringLine(string_view str, int w)const {
		return GetStringLine(Template::convert<wstring>(str), w);
	}
	int Font::GetStringWidth(wstring_view str)const {
		int tmp = 0, max = 0;
		for (wchar_t chr : str){
			if (chr == L'\n') {
				if (tmp > max)max = tmp;
				tmp = 0;
			} else {
				const SharedImage& img = MakeImage(chr);
				if (img) tmp += img->mWidth;
			}
		}
		if (tmp > max)max = tmp;
		return max;
	}
	int Font::GetStringHeight(wstring_view str, int w)const {
		return (__h + __g) * GetStringLine(str, w) - __g;
	}
	int Font::GetStringLine(wstring_view str, int w)const {
		int tw = w, tl = 1;
		for (wchar_t chr : str) {
			if (chr == L'\n') {
				tw = w;
				++tl;
				continue;
			}
			const SharedImage& img = MakeImage(chr);
			if (!img.Image()) continue;
			if (tw - img->mWidth < 0 && tw != w) {
				tw = w;
				++tl;
			}
			tw -= img->mWidth;
		}
		return tl;
	}
	void Font::DrawString(int x, int y, string_view str, DWORD color, int w, int h)const {
		return DrawString(x, y, Template::convert<wstring>(str), color, w, h);
	}
	void Font::DrawString(int x, int y, wstring_view str, DWORD color, int w, int h)const {
		int tx = x, ty = y, line = (h + __g) / (__h + __g);
		w += x;
		for (wchar_t chr : str) {
			if (chr == L'\n') {
				tx = x;
				ty += (__h + __g);
				if (--line == 0)return;
				continue;
			}
			const SharedImage& img = MakeImage(chr);
			if (!img.Image()) continue;
			if (tx + img->mWidth > w && tx != x) {
				tx = x;
				ty += (__h + __g);
				if (--line == 0)return;
			}
			img.Draw(color, { 0,0,img->mWidth,img->mHeight }, Matrix3::Move((float)tx, (float)ty));
			tx += img->mWidth;
		}
	}
	void Font::DrawStringA(int x, int y, string_view str, DWORD color, int w, int h)const {
		int tx = x, ty = y, line = (h + __g) / (__h + __g);
		w += x;
		for (char chr : str) {
			if (chr == u8'\n') {
				tx = x;
				ty += (__h + __g);
				if (--line == 0)return;
				continue;
			}
			const SharedImage& img = MakeImage((wchar_t)chr);
			if (!img.Image()) return;
			if (tx + img->mWidth > w && tx != x) {
				tx = x;
				ty += (__h + __g);
				if (--line == 0)return;
			}
			img.Draw(color, { 0,0,img->mWidth,img->mHeight }, Matrix3::Move((float)tx, (float)ty));
			tx += img->mWidth;
		}
	}
	SharedImage Font::MakeImage(string_view str, int w)const {
		if (str.empty()) return SharedImage();
		return MakeImage(Template::convert<wstring>(str), w);
	}
	SysFont::SysFont(const char* name, int pointSize, int lineGap, int script, int weight, bool italics, bool underline, bool useDevCaps) {
		HDC hDc = GetDC(0);
		mHFont = CreateFontW(useDevCaps ? -MulDiv(pointSize, GetDeviceCaps(hDc, LOGPIXELSY), 72) : -pointSize, 0, 0, 0, weight, italics, underline, false, script, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH | FF_DONTCARE, Template::convert<wstring>(name).data());
		if (!mHFont) Cvp::error(CTformat<CTformat_buffer<void>, MakeCTstr(u8"Font create failed: "), const char*>::format(name));
		TEXTMETRICW aTextMetric;
		HFONT anOldFont = (HFONT)SelectObject(hDc, mHFont);
		GetTextMetricsW(hDc, &aTextMetric);
		SelectObject(hDc, anOldFont);
		ReleaseDC(0, hDc);
		__w = aTextMetric.tmMaxCharWidth;
		__h = aTextMetric.tmHeight;
		__g = lineGap;
		__buffer = new SharedImage[0x10000ul]();
	}
	const SharedImage& SysFont::MakeImage(wchar_t chr)const {
		if (__buffer[chr])return __buffer[chr];
		wchar_t str[2] = { chr,L'\0' };
		HDC hDc = CreateCompatibleDC(nullptr);
		HFONT anOldFont = (HFONT)SelectObject(hDc, mHFont);
		HBRUSH anOldBrush = (HBRUSH)SelectObject(hDc, GetStockObject(BLACK_BRUSH));
		RECT aRect = { 0,0,__w,__h + 1 };
		DrawTextW(hDc, str, 1, &aRect, DT_CALCRECT | DT_NOPREFIX);
		if (aRect.right == 0) {
			SelectObject(hDc, anOldBrush);
			SelectObject(hDc, anOldFont);
			return __buffer[chr] = __makeEmptyImage();
		}
		BITMAPINFO aBitmapInfo;
		memset(&aBitmapInfo, 0, sizeof(aBitmapInfo));
		BITMAPINFOHEADER& aHeader = aBitmapInfo.bmiHeader;
		aHeader.biSize = sizeof(aHeader);
		aHeader.biWidth = aRect.right;
		aHeader.biHeight = -__h - 1;
		aHeader.biPlanes = 1;
		aHeader.biBitCount = 32;
		aHeader.biCompression = BI_RGB;
		DWORD* aBits = nullptr;
		HBITMAP aBitmap = CreateDIBSection(hDc, &aBitmapInfo, DIB_RGB_COLORS, (void**)&aBits, nullptr, 0);
		if (!aBitmap) Cvp::error(u8"CreateDIBSection failed");
		HBITMAP anOldBitmap = (HBITMAP)SelectObject(hDc, aBitmap);
		Rectangle(hDc, 0, 0, aRect.right, __h + 1);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));
		RECT rect = { 0,1,aRect.right,__h + 1 };
		DrawTextW(hDc, str, 1, &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_NOPREFIX);
		GdiFlush();
		SelectObject(hDc, anOldBrush);
		SelectObject(hDc, anOldFont);
		SelectObject(hDc, anOldBitmap);
		auto ans = __makeAlphaImage(aRect.right, __h + 1, aBits);
		DeleteObject(aBitmap);
		return __buffer[chr] = ans;
	}
	SharedImage SysFont::MakeImage(wstring_view str, int w)const {
		if (str.empty()) return SharedImage();
		HDC hDc = CreateCompatibleDC(nullptr);
		HFONT anOldFont = (HFONT)SelectObject(hDc, mHFont);
		HBRUSH anOldBrush = (HBRUSH)SelectObject(hDc, GetStockObject(BLACK_BRUSH));
		RECT aRect = { 0,0,w,0x7ffffffful };
		int line = 0;
		const wchar_t* begin[32]{ str.data() };
		int len[32]{ 0 };
		const wchar_t* end = str.data() + str.length();
		int wmax = 0;
		while (begin[line] + len[line] < end) {
			if (begin[line][len[line]++] == L'\n') {
				begin[line + 1] = begin[line] + len[line];
				len[++line] = 0;
				continue;
			}
			DrawTextW(hDc, begin[line], len[line], &aRect, DT_CALCRECT | DT_NOPREFIX);
			if (aRect.right > w) {
				begin[line + 1] = begin[line] + --len[line];
				len[++line] = 0;
				continue;
			}
			if (aRect.right > wmax)wmax = aRect.right;
		}
		aRect = { 0,1,wmax,line * (__g + __h) + __h + 1 };
		BITMAPINFO aBitmapInfo;
		memset(&aBitmapInfo, 0, sizeof(aBitmapInfo));
		BITMAPINFOHEADER& aHeader = aBitmapInfo.bmiHeader;
		aHeader.biSize = sizeof(aHeader);
		aHeader.biWidth = wmax;
		aHeader.biHeight = -aRect.bottom;
		aHeader.biPlanes = 1;
		aHeader.biBitCount = 32;
		aHeader.biCompression = BI_RGB;
		DWORD* aBits = nullptr;
		HBITMAP aBitmap = CreateDIBSection(hDc, &aBitmapInfo, DIB_RGB_COLORS, (void**)&aBits, nullptr, 0);
		if (!aBitmap) Cvp::error(u8"CreateDIBSection failed");
		HBITMAP anOldBitmap = (HBITMAP)SelectObject(hDc, aBitmap);
		Rectangle(hDc, 0, 0, wmax, line * (__g + __h) + __h + 1);
		SetBkMode(hDc, TRANSPARENT);
		SetTextColor(hDc, RGB(255, 255, 255));
		for (int i = 0; i <= line; ++i) {
			DrawTextW(hDc, begin[i], len[i], &aRect, DT_NOPREFIX);
			aRect.top += (__g + __h);
		}
		GdiFlush();
		SelectObject(hDc, anOldBitmap);
		SelectObject(hDc, anOldBrush);
		SelectObject(hDc, anOldFont);
		auto ans = __makeAlphaImage(wmax, aRect.bottom, aBits);
		DeleteObject(aBitmap);
		return ans;
	}
	Widget::Widget(const Rect& rect, initializer_list<Widget*> children) :__rect(rect), __parent(nullptr), __modal(nullptr), __children(), __invisible(false), __inactive(false), __modaled(false), __closed(false), __over(false), __down(false), __focus(false) {
		AddChildren(children);
	}
	Widget::~Widget() {
		for (auto&& p : __children) delete p;
	}
	void Widget::Move(int dx, int dy) {
		__rect += Point<int>(dx, dy);
		for (auto&& p : __children) p->Move(dx, dy);
	}
	void Widget::MoveTo(int x, int y) {
		x -= __rect.mX;
		y -= __rect.mY;
		if (__parent) {
			x += __parent->GetX();
			y += __parent->GetY();
		}
		Move(x, y);
	}
	void Widget::SetParent(Widget* p) {
		p->AddChild(this);
	}
	void Widget::DoModal(Widget* widget) {
		if (__modal) delete widget;
		else SetModaled(__modal = widget);
	}
	size_t Widget::AddChild(Widget* child) {
		size_t ans = __children.size();
		__children.push_back(child);
		child->__parent = this;
		child->Move(__rect.mX, __rect.mY);
		SetInvisible(__invisible);
		SetInactive(__inactive);
		SetModaled(__modaled);
		return ans;
	}
	size_t Widget::AddChildren(initializer_list<Widget*> _list) {
		size_t ans = __children.size();
		__children.insert(__children.end(), _list.begin(), _list.end());
		for (auto&& p : _list) p->__parent = this, p->Move(__rect.mX, __rect.mY);
		SetInvisible(__invisible);
		SetInactive(__inactive);
		SetModaled(__modaled);
		return ans;
	}
	void Widget::SetInvisible(bool a) {
		__invisible = a; for (auto&& p : __children) p->SetInvisible(a);
	}
	void Widget::SetInactive(bool a) {
		__inactive = a; for (auto&& p : __children) p->SetInactive(a);
	}
	void Widget::SetModaled(bool a) {
		if (__modal) return;
		__modaled = a;
		for (auto&& p : __children) p->SetModaled(a);
	}
	void Widget::SetClosed() {
		__closed = true;
	}
	void Widget::SetFocus(bool a) {
		a ? WidgetManager::FocusWidget(this) : WidgetManager::ReleaseWidget(this);
	}
	void Widget::DrawImage(const SharedImage& theImage, int x, int y, DWORD theColor)const {
		if(theImage) theImage.Draw(theColor, { 0,0,theImage->mWidth, theImage->mHeight }, Matrix3::Move((float)(x + GetX()), (float)(y + GetY())), false);
	}
	void Widget::DrawImage(const SharedImage& theImage, const Rect& theDstRect, DWORD theColor)const {
		if (theImage) theImage.Draw(theColor, { 0,0,min(theDstRect.mW,theImage->mWidth),min(theDstRect.mH,theImage->mHeight) }, Matrix3::Move((float)(theDstRect.mX + GetX()), (float)(theDstRect.mY + GetY())), false);
	}
	void Widget::DrawImageMid(const SharedImage& theImage, const Rect& theDstRect, DWORD theColor)const {
		if (theImage) theImage.Draw(theColor, { 0,0,min(theDstRect.mW,theImage->mWidth),min(theDstRect.mH,theImage->mHeight) }, Matrix3::Move((float)(theDstRect.mX + GetX() + max(theDstRect.mW - theImage->mWidth, 0) / 2), (float)(theDstRect.mY + GetY() + max(theDstRect.mH - theImage->mHeight, 0) / 2)), false);
	}
	void Widget::DrawString(string_view str, int x, int y, DWORD theColor)const {
		GlobalFont().DrawString(x + GetX(), y + GetY(), str, theColor);
	}
	void Widget::DrawString(string_view str, const Rect& theDstRect, DWORD theColor)const {
		GlobalFont().DrawString(theDstRect.mX + GetX(), theDstRect.mY + GetY(), str, theColor, theDstRect.mW, theDstRect.mH);
	}
	void Widget::DrawString(wstring_view str, int x, int y, DWORD theColor)const {
		GlobalFont().DrawString(x + GetX(), y + GetY(), str, theColor);
	}
	void Widget::DrawString(wstring_view str, const Rect& theDstRect, DWORD theColor)const {
		GlobalFont().DrawString(theDstRect.mX + GetX(), theDstRect.mY + GetY(), str, theColor, theDstRect.mW, theDstRect.mH);
	}
	void Widget::DrawLine(DWORD color, const Point<float>* point, size_t pointNum)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca(pointNum * sizeof(Geo::Vertex));
		for (size_t i = 0; i < pointNum; ++i)new(_list + i)Geo::Vertex(point[i].mX + (float)__rect.mX, point[i].mY + (float)__rect.mY, color);
		Geo::LineTrip(_list, pointNum);
		_freea(_list);
	}
	void Widget::DrawLine(DWORD color, initializer_list<Point<float> > point)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca(point.size() * sizeof(Geo::Vertex));
		for (size_t i = 0; i < point.size(); ++i)new(_list + i)Geo::Vertex(point.begin()[i].mX + (float)__rect.mX, point.begin()[i].mY + (float)__rect.mY, color);
		Geo::LineTrip(_list, point.size());
		_freea(_list);
	}
	void Widget::DrawTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate)const {
		Geo::DrawTriangle(color, { mid.mX + __rect.mX, mid.mY + __rect.mY }, height, width, rotate);
	}
	void Widget::DrawFullTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate)const {
		Geo::DrawFullTriangle(color, { mid.mX + __rect.mX, mid.mY + __rect.mY }, height, width, rotate);
	}
	void Widget::DrawTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3)const {
		Geo::DrawTriangle(color,
			{ point1.mX + __rect.mX, point1.mY + __rect.mY },
			{ point2.mX + __rect.mX, point2.mY + __rect.mY },
			{ point3.mX + __rect.mX, point3.mY + __rect.mY }
		);
	}
	void Widget::DrawFullTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3)const {
		Geo::DrawFullTriangle(color,
			{ point1.mX + __rect.mX, point1.mY + __rect.mY },
			{ point2.mX + __rect.mX, point2.mY + __rect.mY },
			{ point3.mX + __rect.mX, point3.mY + __rect.mY }
		);
	}
	void Widget::DrawRect(DWORD color, const Rect& rect, float roundR)const {
		Geo::DrawRect(color, Rect(rect.mX + __rect.mX, rect.mY + __rect.mY, rect.mW, rect.mH), roundR);
	}
	void Widget::DrawFullRect(DWORD color, const Rect& rect, float roundR)const {
		Geo::DrawFullRect(color, Rect(rect.mX + __rect.mX, rect.mY + __rect.mY, rect.mW, rect.mH), roundR);
	}
	void Widget::DrawCircle(DWORD color, const Point<float>& mid, float radius)const {
		Geo::DrawCircle(color, { mid.mX + __rect.mX, mid.mY + __rect.mY }, radius);
	}
	void Widget::DrawFullCircle(DWORD color, const Point<float>& mid, float radius)const {
		Geo::DrawFullCircle(color, { mid.mX + __rect.mX, mid.mY + __rect.mY }, radius);
	}
	void Widget::DrawPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate)const {
		Geo::DrawPolygon(color, edgeNum, { mid.mX + __rect.mX, mid.mY + __rect.mY }, radius, rotate);
	}
	void Widget::DrawFullPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate)const {
		Geo::DrawFullPolygon(color, edgeNum, { mid.mX + __rect.mX, mid.mY + __rect.mY }, radius, rotate);
	}
	void Widget::DrawPolygon(DWORD color, const Point<float>* point, size_t edgeNum)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca((edgeNum + 1) * sizeof(Geo::Vertex));
		for (size_t i = 0; i <= edgeNum; ++i)new(_list + i)Geo::Vertex(point[i].mX + (float)__rect.mX, point[i].mY + (float)__rect.mY, color);
		Geo::LineTrip(_list, edgeNum + 1);
		_freea(_list);
	}
	void Widget::DrawFullPolygon(DWORD color, const Point<float>* point, size_t edgeNum)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca((edgeNum + 1) * sizeof(Geo::Vertex));
		for (size_t i = 0; i <= edgeNum; ++i)new(_list + i)Geo::Vertex(point[i].mX + (float)__rect.mX, point[i].mY + (float)__rect.mY, color);
		Geo::TriangleFan(_list, edgeNum + 1);
		_freea(_list);
	}
	void Widget::DrawPolygon(DWORD color, initializer_list<Point<float> > point)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca((point.size() + 1) * sizeof(Geo::Vertex));
		for (size_t i = 0; i <= point.size(); ++i)new(_list + i)Geo::Vertex(point.begin()[i].mX + (float)__rect.mX, point.begin()[i].mY + (float)__rect.mY, color);
		Geo::LineTrip(_list, point.size() + 1);
		_freea(_list);
	}
	void Widget::DrawFullPolygon(DWORD color, initializer_list<Point<float> > point)const {
		Geo::Vertex* _list = (Geo::Vertex*)_malloca((point.size() + 1) * sizeof(Geo::Vertex));
		for (size_t i = 0; i <= point.size(); ++i)new(_list + i)Geo::Vertex(point.begin()[i].mX + (float)__rect.mX, point.begin()[i].mY + (float)__rect.mY, color);
		Geo::TriangleFan(_list, point.size() + 1);
		_freea(_list);
	}
	int  Widget::GetX()const {
		return __rect.mX;
	}
	int  Widget::GetY()const {
		return __rect.mY;
	}
	int  Widget::GetW()const {
		return __rect.mW;
	}
	int  Widget::GetH()const {
		return __rect.mH;
	}
	Widget* Widget::GetParent()const {
		return __parent;
	}
	Widget* Widget::GetModal()const {
		return __modal;
	}
	const vector<Widget*>& Widget::GetChildren()const {
		return __children;
	}
	bool Widget::GetInvisible()const {
		return __invisible;
	}
	bool Widget::GetInactive()const {
		return __inactive || __modaled;
	}
	bool Widget::GetClosed()const {
		return __closed;
	}
	bool Widget::GetOver()const {
		return __over;
	}
	bool Widget::GetDown()const {
		return __down;
	}
	bool Widget::GetFocus()const {
		return __focus;
	}
	void Widget::AttachManager() {
		WidgetManager::AddWidget(this);
	}
	void Widget::AttachTab(string_view label) {
		WidgetManager::SetTab({ make_pair(label, this) });
	}
#ifndef  CVP
	list<Widget*> WidgetManager::__widgets{};
	TabWidget* WidgetManager::__tabWidget = nullptr;
	CmdWidget* WidgetManager::__cmdWidget = nullptr;
	Widget* WidgetManager::__over = nullptr;
	Widget* WidgetManager::__down = nullptr;
	Widget* WidgetManager::__focus = nullptr;
	int WidgetManager::__mouseX = 0;
	int WidgetManager::__mouseY = 0;
	bool WidgetManager::__mouse[4]{};//right/left/mid/reserve
	bool WidgetManager::__shift = false;
	bool WidgetManager::__ctrl = false;
	bool WidgetManager::__alt = false;
	const Cvp::MouseCode WidgetManager::__mousecode[3]{ Cvp::MouseCode::RIGHT, Cvp::MouseCode::LEFT, Cvp::MouseCode::MID };
	void WidgetManager::__setover(Widget* widget) {
		if (widget && widget->GetInactive()) return __setover(widget->GetParent());
		if (__over) __over->__over = false;
		__over = widget;
		if (__over) __over->__over = true;
	}
	void WidgetManager::__setdown(Widget* widget) {
		if (widget && widget->GetInactive()) return __setdown(widget->GetParent());
		if (__down) __down->__down = false;
		__down = widget;
		if (__down) __down->__down = true;
		else ::ReleaseCapture();
	}
	void WidgetManager::__setfocus(Widget* widget) {
		if (widget && widget->GetInactive()) return __setfocus(widget->GetParent());
		if (__focus) __focus->__focus = false;
		__focus = widget;
		if (__focus) __focus->__focus = true;
	}
	void WidgetManager::__regulate() {
		if (__over && __over->GetInvisible()) __setover(nullptr);
		if (__down && __down->GetInvisible()) __setdown(nullptr);
		if (__focus && __focus->GetInvisible()) __setfocus(nullptr);
		if (__down && __down->GetInactive()) __setdown(nullptr);
		if (__focus && __focus->GetInactive()) __setfocus(nullptr);
	}
	Widget* WidgetManager::__getWidget(int x, int y) {
		Widget* ans = nullptr;
		for (auto&& p = __widgets.begin(); p != __widgets.end(); ++p) if ((!(*p)->GetInvisible()) && (*p)->__rect.Contains(x, y)) { ans = *p; break; }
		if (!ans && __tabWidget && (!__tabWidget->GetInvisible()) && __tabWidget->__rect.Contains(x, y))  ans = __tabWidget;
		if (!ans && __cmdWidget && (!__cmdWidget->GetInvisible()) && __cmdWidget->__rect.Contains(x, y))  ans = __cmdWidget;
		if (!ans) return nullptr;
	__getWidget_recur:
		if (ans->GetChildren().empty()) return ans;
		for (auto&& p = ans->GetChildren().begin(); p != ans->GetChildren().end(); ++p) if ((!(*p)->GetInvisible()) && (*p)->__rect.Contains(x, y)) { ans = *p; goto __getWidget_recur; }
		return ans;
	}
	void WidgetManager::__reMouse(int x, int y) {
		Widget* widget = __getWidget(x, y);
		if (widget != __over) {
			if (__over) __over->MouseLeave();
			__setover(widget);
			if (__over) {
				__over->MouseEnter();
				__over->MouseMove(x - __over->GetX(), y - __over->GetY());
			}
		} else if ((__mouseX != x) || (__mouseY != y)) {
			if (__over)__over->MouseMove(x - __over->GetX(), y - __over->GetY());
		}
		__mouseX = x;
		__mouseY = y;
	}
	void WidgetManager::__clean(Widget* widget) {
		if (!widget)return;
		if (widget->GetModal()) {
			widget->GetModal()->Clean();
			if (widget->GetModal()->GetClosed()) {
				delete widget->GetModal();
				widget->__modal = nullptr;
				widget->SetModaled(false);
			}
		}
		for (auto&& p = widget->GetChildren().rbegin(); p != widget->GetChildren().rend(); ++p) __clean(*p);
		widget->Clean();
	}
	void WidgetManager::__update(Widget* widget) {
		if (!widget)return;
		if (widget->GetModal()) return __update(widget->GetModal());
		widget->Update();
		for (auto&& p = widget->GetChildren().rbegin(); p != widget->GetChildren().rend(); ++p) __update(*p);
	}
	void WidgetManager::__draw(Widget* widget) {
		if (!widget)return;
		if (widget->GetInvisible())return;
		widget->Draw();
		for (auto&& p = widget->GetChildren().rbegin(); p != widget->GetChildren().rend(); ++p) __draw(*p);
		widget->DrawOver();
		if (widget->GetModal()) __draw(widget->GetModal());
	}
	bool WidgetManager::MouseWheel(int delta) {
		if (Pvz::MouseWheelHook()(delta))return true;
		__regulate();
		if (__focus) __focus->MouseWheel(delta);
		return __focus;
	};
	bool WidgetManager::KeyDown(KeyCode key) {
		if (Pvz::KeyHook()(Cvp::KeyCode(key, __shift, __ctrl, __alt)))return true;
		__regulate();
		switch (key) {
		case KeyCode::SHIFT:__shift = true;break;
		case KeyCode::CONTROL:__ctrl = true;break;
		case KeyCode::MENU:__alt = true;break;
		}
		if (__focus) __focus->KeyDown(Cvp::KeyCode(key, __shift, __ctrl, __alt));
		return __focus;
	};
	bool WidgetManager::KeyUp(KeyCode key) {
		__regulate();
		switch (key) {
		case KeyCode::SHIFT:__shift = false; break;
		case KeyCode::CONTROL:__ctrl = false; break;
		case KeyCode::MENU:__alt = false; break;
		}
		if (__focus) __focus->KeyUp(Cvp::KeyCode(key, __shift, __ctrl, __alt));
		return __focus;
	};
	bool WidgetManager::KeyChar(char key) {
		__regulate();
		if (__focus) __focus->KeyChar(key);
		return __focus;
	};
	void WidgetManager::Update() {
		__regulate();
		Pvz::UpdateHook()();
		for (auto&& p = __widgets.begin(); p != __widgets.end(); ++p)__update(*p);
		if (__tabWidget)__update(__tabWidget);
		if (__cmdWidget)__update(__cmdWidget);
		for (auto&& p = __widgets.begin(); p != __widgets.end(); ++p)__clean(*p);
		if (__tabWidget)__clean(__tabWidget);
		if (__cmdWidget)__clean(__cmdWidget);
		for (auto&& p = __widgets.begin(); p != __widgets.end(); ++p) if ((*p)->GetClosed()) delete* p, p = __widgets.erase(p);
		if (__tabWidget && __tabWidget->GetClosed()) delete __tabWidget, __tabWidget = nullptr;
		if (__cmdWidget && __cmdWidget->GetClosed()) delete __cmdWidget, __cmdWidget = nullptr;
	};
	void WidgetManager::Draw() {
		__regulate();
		//Pvz::DDImage* aDDImage = Pvz::ImageToDDImage(Pvz::gGameApp->mWidgetManager->mImage);
		//bool surfaceLocked = false;
		//if (aDDImage != NULL)surfaceLocked = aDDImage->LockSurface();
		Pvz::DrawHook()();
		if (__cmdWidget)__draw(__cmdWidget);
		if (__tabWidget)__draw(__tabWidget);
		for (auto&& p = __widgets.rbegin(); p != __widgets.rend(); ++p)__draw(*p);
		//if (aDDImage != NULL && surfaceLocked)aDDImage->UnlockSurface();
	};
	bool WidgetManager::MouseDown(int x, int y, int key) {
		__regulate();
		__mouse[(key + 3) / 3] = true;
		__reMouse(x, y);
		if (!__down) {
			if (__over && __over->__rect.Contains(x, y))__setdown(__over);
			else __setdown(__getWidget(x, y));
		}
		if (__down != __focus) {
			if (__focus)__focus->LostFocus();
			__setfocus(__down);
			if (__focus)__focus->GotFocus();
		}
		if (!__down) return false;
		Widget* widget = __down;
		while (widget->GetParent())widget = widget->GetParent();
		auto p = find(__widgets.begin(), __widgets.end(), widget);
		if (p != __widgets.end()) {
			__widgets.push_front(*p);
			__widgets.erase(p);
		}
		__down->MouseDown(x - __down->GetX(), y - __down->GetY(), __mousecode[(key + 3) / 3]);
		return true;
	};
	bool WidgetManager::MouseUp(int x, int y, int key) {
		__regulate();
		if (!__mouse[(key + 3) / 3]) return false;
		__mouse[(key + 3) / 3] = false;
		if (!__down) return false;
		__down->MouseUp(x - __down->GetX(), y - __down->GetY(), __mousecode[(key + 3) / 3]);
		if (__mouse[0] || __mouse[1] || __mouse[2]); else __setdown(nullptr);
		__reMouse(x, y);
		return true;
	};
	bool WidgetManager::MouseMove(int x, int y) {
		x = limit(0, x, Pvz::gGameApp->mWidth);
		y = limit(0, y, Pvz::gGameApp->mHeight);
		__regulate();
		if (!__down) {
			__reMouse(x, y);
			return __over;
		} else {
			__down->MouseDrag(x - __mouseX, y - __mouseY);
			__down->MouseMove(x - __down->GetX(), y - __down->GetY());
			__setover(__getWidget(x, y));
			__mouseX = x;
			__mouseY = y;
			return true;
		}
	};
	void WidgetManager::AddWidget(Widget* widget) {
		__widgets.push_front(widget);
	}
	void WidgetManager::FocusWidget(Widget* widget) {
		if (widget != __focus) {
			if (__focus)__focus->LostFocus();
			__setfocus(widget);
			if (__focus)__focus->GotFocus();
		}
		if (!widget) return;
		while (widget->GetParent())widget = widget->GetParent();
		auto p = find(__widgets.begin(), __widgets.end(), widget);
		if (p != __widgets.end()) {
			__widgets.push_front(*p);
			__widgets.erase(p);
		}
	}
	void WidgetManager::ReleaseWidget(Widget* widget) {
		if (__focus == widget) __setfocus(nullptr), widget->LostFocus();
	}
	void WidgetManager::SetTab(initializer_list<pair<string_view, Widget*>> page) {
		if (__tabWidget) return __tabWidget->AddPage(page);
		__tabWidget = new TabWidget(page);
		__setfocus(__tabWidget);
	}
	void WidgetManager::SetCmd(initializer_list<Cvp::UPCommand> cmd) {
		if (!__cmdWidget)__cmdWidget = new CmdWidget();
		for (auto&& p : cmd)__GlobalCmd() += p;
	}
	bool WidgetManager::Shift() { return __shift; }
	bool WidgetManager::Ctrl() { return __ctrl; }
	bool WidgetManager::Alt() { return __alt; }
	TabWidget::TabWidget(initializer_list<pair<string_view, Widget*>> page) : Widget({ 800,0,479,719 }), __nowIndex(0), __shownIndex(0), __mousex(-1), __mousey(-1) {
		AddPage(page);
		GetChildren()[0]->SetInvisible(false);
	}
	void TabWidget::AddPage(initializer_list<pair<string_view, Widget*>> page) {
		for (auto&& p : page) {
			__titleList.push_back(GlobalFont().MakeImage(p.first));
			AddChild(p.second);
			p.second->MoveTo(0, __TitleHeight);
			p.second->SetInvisible(true);
		}
	}
	void TabWidget::SetIndex(size_t index) {
		GetChildren()[__nowIndex]->SetInvisible(true);
		while (index & 0x80000000ul)index += GetChildren().size();
		__nowIndex = index % GetChildren().size();
		GetChildren()[__nowIndex]->SetInvisible(false);
	}
	void TabWidget::MovePos(int delta) {
		__shownIndex += WidgetManager::Shift() ? delta * 3 : delta;
		while (__shownIndex & 0x80000000ul)__shownIndex += GetChildren().size();
		__shownIndex %= GetChildren().size();
	}
	void TabWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT || y > __TitleHeight) return;
		if (x < __GapEnd) return MovePos(-3);
		if (x + __GapEnd > GetW()) return MovePos(+3);
		int x2 = __GapEnd;
		size_t end = __shownIndex ? __shownIndex - 1 : GetChildren().size() - 1;
		for (size_t i = __shownIndex; ; ++i) {
			if (i >= GetChildren().size()) i -= GetChildren().size();
			if (x2 + min(__titleList[i]->mWidth, __TitleWeightMax) > GetW() - __GapEnd - 2 * __Gap) return;
			x2 += 2 * __Gap;
			x2 += min(__titleList[i]->mWidth, __TitleWeightMax);
			if (x2 >= x) {
				SetIndex(i);
				return;
			}
			if (i == end) return;
		}
	}
	void TabWidget::MouseLeave() {
		__mousex = __mousey = -1;
	}
	void TabWidget::MouseWheel(int delta) {
		MovePos(delta);
	}
	void TabWidget::MouseMove(int x, int y) {
		if (y > __TitleHeight || x < __GapEnd || x + __GapEnd > GetW()) __mousex = __mousey = -1;
		else __mousex = x, __mousey = y;
	}
	void TabWidget::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::TAB:SetIndex(__nowIndex + 1); MovePos(0); break;
		case KeyCode::LEFT:MovePos(-1); break;
		case KeyCode::RIGHT:MovePos(1); break;
		case KeyCode::UP:MovePos(-3); break;
		case KeyCode::DOWN:MovePos(3); break;
		}
	}
	void TabWidget::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),GetH() });
		DrawFullTriangle(GlobalStyle().LineColor, { 15, 23 }, { 15, 8 }, { 8, 15 });
		DrawFullTriangle(GlobalStyle().LineColor, { GetW() - 15, 23 }, { GetW() - 15, 8 }, { GetW() - 8, 15 });
		int x = __GapEnd;
		size_t end = __shownIndex ? __shownIndex - 1 : GetChildren().size() - 1;
		for (size_t i = __shownIndex; ; ++i) {
			if (i >= GetChildren().size()) i -= GetChildren().size();
			if (__titleList[i]->mWidth > __TitleWeightMax) {
				if (x + __TitleWeightMax > GetW() - __GapEnd - 2 * __Gap)return;
				DrawFullRect(i == __nowIndex ? GlobalStyle().SelectColor : GlobalStyle().BaseColor, { x, 0, __TitleWeightMax + 2 * __Gap, __TitleHeight });
				DrawRect(GlobalStyle().LineColor, { x, 0, __TitleWeightMax + 2 * __Gap, __TitleHeight });
				DrawImage(__titleList[i], { x + __Gap,(__TitleHeight - 20) / 2,__TitleWeightMax,20 }, GlobalStyle().LineColor);
				x += (2 * __Gap + __TitleWeightMax);
			} else {
				if (x + __titleList[i]->mWidth > GetW() - __GapEnd - 2 * __Gap)return;
				DrawFullRect(i == __nowIndex ? GlobalStyle().SelectColor : GlobalStyle().BaseColor, { x, 0, __titleList[i]->mWidth + 2 * __Gap, __TitleHeight });
				DrawRect(GlobalStyle().LineColor, { x, 0, __titleList[i]->mWidth + 2 * __Gap, __TitleHeight });
				DrawImage(__titleList[i], x + __Gap, (__TitleHeight - 20) / 2, GlobalStyle().LineColor);
				x += (2 * __Gap + __titleList[i]->mWidth);
			}
			if (i == end) return;
		}
	}
	void TabWidget::DrawOver() {
		if (__mousex == -1 || __mousey == -1) return;
		int x = __GapEnd;
		for (size_t i = __shownIndex; ; ++i) {
			if (i >= GetChildren().size()) i -= GetChildren().size();
			if (__titleList[i]->mWidth > __TitleWeightMax) {
				if (x + __TitleWeightMax > GetW() - __GapEnd - 2 * __Gap)return;
				x += (2 * __Gap + __TitleWeightMax);
				if (x >= __mousex) {
					x = __mousex - __titleList[i]->mWidth - __Gap;
					DrawFullRect(GlobalStyle().BaseColor, { x, __mousey, __mousex - x, 24 });
					DrawRect(GlobalStyle().LineColor, { x, __mousey, __mousex - x, 24 });
					DrawImage(__titleList[i], x + 8, __mousey + 2, GlobalStyle().LineColor);
					return;
				}
			} else {
				if (x + __titleList[i]->mWidth > GetW() - __GapEnd - 2 * __Gap)return;
				x += (2 * __Gap + __titleList[i]->mWidth);
				if (x >= __mousex) return;
			}
		}
	}
	CmdWidget::CmdWidget() :Widget({ 0,600,800,119 }), __buffer(), __log({ u8"--------------------------------------------GAME START--------------------------------------------" }), __logShownIndex(0), __lineList({ u8"" }), __lineListFormat({ u8"" }), __lineListTab({ u8"" }), __shownIndex(0), __selectIndex(0), __input(false) {
		__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
	}
	void CmdWidget::MovePos(int delta) {
		if (__input) {
			__shownIndex += WidgetManager::Shift() ? delta * 3 : delta;
			while (__shownIndex & 0x80000000ul)__shownIndex += __lineList.size();
			__shownIndex %= __lineList.size();
			if (__lineList.size() < __LineMax) __shownIndex = 0;
		} else {
			__logShownIndex -= WidgetManager::Shift() ? delta * 3 : delta;
			if (__logShownIndex < __LineMax - 1)__logShownIndex = __LineMax - 1;
			if (__logShownIndex > __log.size() - 1)__logShownIndex = __log.size() - 1;
		}
	}
	void CmdWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!Rect(0, __LineHeight, GetW(), GetH() - __LineHeight).Contains(x, y))__input = true;
		else if (__input)__selectIndex = __shownIndex + y / __LineHeight - 1;
	}
	void CmdWidget::MouseWheel(int delta) {
		MovePos(delta);
	}
	void CmdWidget::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::UP:if (__selectIndex)--__selectIndex; else __selectIndex = __lineList.size() - 1; break;
		case KeyCode::DOWN:++__selectIndex; if (__selectIndex == __lineList.size())__selectIndex = 0; break;
		case KeyCode::BACKSPACE:
			if (key.Shift()) {
				size_t p = __buffer.size();
				while (p && __buffer[p - 1] == u8' ')--p;
				while (p && __buffer[p - 1] != u8' ')--p;
				__buffer.resize(p);
			}
			else if (!__buffer.empty())__buffer.resize(__buffer.size() - 1);
			__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
			__selectIndex = __shownIndex = 0;
			__input = true;
			break;
		case KeyCode::ESCAPE:
			__buffer.clear();
			__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
			__selectIndex = __shownIndex = 0;
			__input = true;
			break;
		case KeyCode::TAB:
			__buffer = __lineList[__selectIndex] + __lineListTab[__selectIndex];
			if (!__buffer.empty() && __buffer.back() != u8' ')__buffer += u8' ';
			__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
			__selectIndex = __shownIndex = 0;
			__input = true;
			break;
		case KeyCode::RETURN:
			if (key.Shift()) {
				__buffer += u8'\n';
				break;
			}
		{
			if (!__buffer.empty() && __buffer.back() != u8' ')__buffer += u8' ';
			string ans = __GlobalCmd().Call(__buffer);
			__log.emplace_back(string(u8">>> ") + move(__buffer));
			if (!ans.empty()) {
				__log.emplace_back(string(u8"<<< ") + move(ans));
			}
			__logShownIndex = __log.size() - 1;
		}
		__buffer.clear();
		__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
		__selectIndex = __shownIndex = 0;
		__input = false;
		break;
		case KeyCode::C:
			if (!key.Ctrl())break;
			Cvp::ClipBoardWrite(__buffer);
			__input = true;
			break;
		case KeyCode::V:
			if (!key.Ctrl())break;
			__buffer += Cvp::ClipBoardRead<string>();
			__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
			__selectIndex = __shownIndex = 0;
			__input = true;
			break;
		}
	}
	void CmdWidget::KeyChar(char key) {
		__buffer += key;
		__GlobalCmd().__MakeList(__buffer, __lineList, __lineListFormat, __lineListTab);
		__input = true;
		__selectIndex = __shownIndex = 0;
	}
	void CmdWidget::LostFocus() {
		__input = false;
	}
	void CmdWidget::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() });
		int ydiff = __LineHeight;
		if (__input) for (size_t i = __shownIndex;;) {
			DrawString(__lineListFormat[i], { 8,ydiff,GetW() - 16, __LineHeight }, GlobalStyle().LightLineColor);
			DrawString(__lineList[i], { 8,ydiff,GetW() - 16, __LineHeight }, i == __selectIndex ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
			ydiff += __LineHeight;
			if (ydiff > GetY())break;
			++i;
			if (i >= __lineList.size()) i -= __lineList.size();
			if (i == __shownIndex || i == (__shownIndex + min(__LineMax, __lineList.size())) % __lineList.size())break;
		} else for (size_t i = __logShownIndex;;) {
			DrawString(__log[i], { 8,ydiff,GetW() - 16, __LineHeight }, GlobalStyle().LightLineColor);
			ydiff += __LineHeight;
			if (ydiff > GetY())break;
			if (i-- == 0)break;
		}
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), __LineHeight });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), __LineHeight });
		DrawString(__buffer, { 8,0,GetW() - 16, __LineHeight }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
		if (__input && GlobalFont().GetStringLine(__buffer, 784) > 1) {
			Geo::DrawFullRect(Geo::Transp(GlobalStyle().BaseColor), { 0,0,800, 600 });
			GlobalFont().DrawString(8, 0, __buffer, Geo::Transp(GlobalStyle().LineColor), 784, 600);
		}
	}
	Title::Title(string_view title, Widget* body, SharedImage icon) :Widget(Rect(body->GetX(), body->GetY(), body->GetW(), body->GetH() + __titleHeight)), __image(GlobalFont().MakeImage(title)), __icon(move(icon)) {
		body->MoveTo(0, __titleHeight);
		AddChild(body);
	}
	void Title::MouseDrag(int x, int y) {
		Move(x, y);
	}
	void Title::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT) return;
		if ((x - GetW() + __titleHeight / 2) * (x - GetW() + __titleHeight / 2) + (y - __titleHeight / 2) * (y - __titleHeight / 2) < 100) SetClosed();
	}
	void Title::Draw() {
		DrawFullRect(GlobalStyle().LightColor, { 0,0,GetW(), __titleHeight });
		if (__icon) {
			DrawImage(__icon, { 0, 0, __icon->mWidth, __titleHeight });
			DrawImage(__image, { 8, (__titleHeight - 24) / 2, GetW() - 16 - __titleHeight - __icon->mWidth, __titleHeight }, GlobalStyle().LineColor);
		} else {
			DrawImage(__image, { 8, (__titleHeight - 24) / 2, GetW() - 16 - __titleHeight, __titleHeight }, GlobalStyle().LineColor);
		}
		DrawFullCircle(0x80ff0000ul, { GetW() - __titleHeight / 2, __titleHeight / 2 }, 7);
	}
	void Title::Clean() {
		if (GetChildren()[0]->GetClosed()) SetClosed();
	}
	Label::Label(const Rect& rect, string_view label) : Widget(rect) {
		__image = GlobalFont().MakeImage(label);
	}
	void Label::Draw() {
		DrawImageMid(__image, { 0,0,GetW(),GetH() }, GlobalStyle().LineColor);
	}
	StringOutput::StringOutput(const Rect& rect, string& str) :Widget(rect), __buffer(str), __r(min(__Height, rect.mH)) {}
	void StringOutput::Draw() {
		DrawFullRect(GlobalStyle().LightColor, { 0,0,GetW(),GetH() }, (float)(__r / 2));
		DrawString(__buffer, { __r / 2,2,GetW() - __r,GetH() }, GlobalStyle().LineColor);
	}
	WstringOutput::WstringOutput(const Rect& rect, wstring& str) : Widget(rect), __buffer(str), __r(min(__Height, rect.mH)) {}
	void WstringOutput::Draw() {
		DrawFullRect(GlobalStyle().LightColor, { 0,0,GetW(),GetH() }, (float)(__r / 2));
		DrawString(__buffer, { __r / 2,2,GetW() - __r,GetH() }, GlobalStyle().LineColor);
	}
	KeySelector_Event::KeySelector_Event(Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default) : Widget({ pos.mX, pos.mY,__Width,__Height }), __func(func), __key(_default), __image(__KeyTag(_default.Code())), __specialColor(GlobalStyle().BaseColor) {}
	void KeySelector_Event::KeyDown(Cvp::KeyCode key) {
		if (inrange(key.Code(), KeyCode::SHIFT, KeyCode::CONTROL, KeyCode::MENU))return;
		__specialColor = (key.Shift() ? 0xffu : 0) | (key.Ctrl() ? 0xff00u : 0) | (key.Alt() ? 0xff0000ul : 0);
		__key = key, __image = __KeyTag(key.Code()), __func(key), SetFocus(false);
	}
	void KeySelector_Event::Draw() {
		DrawFullRect(Geo::Mix(GlobalStyle().BaseColor, __specialColor | GlobalStyle().BaseColor, GlobalStyle().MixRate), { 0,0,__Width,__Height }, (float)(__Height / 2));
		DrawRect(GlobalStyle().LineColor, { 0,0,__Width,__Height }, (float)(__Height / 2));
		if (__image) DrawImageMid(__image, { 0,0,__Width,__Height }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	StringInput_Event::StringInput_Event(const Rect& rect, const function<void(string_view)>& func, string_view _default) :Widget(rect), __buffer(_default), __func(func) {}
	void StringInput_Event::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if(!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void StringInput_Event::KeyChar(char key) {
		__buffer += key;
	}
	void StringInput_Event::LostFocus() {
		__func(__buffer);
	}
	void StringInput_Event::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	IntegerInput_Event::IntegerInput_Event(const Rect& rect, const function<void(int)>& func, int _default) : Widget(rect), __buffer(Cvp::format(u8"%d", _default)), __func(func) { if (__buffer.empty())__buffer = u8"0"; }
	void IntegerInput_Event::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if (!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void IntegerInput_Event::KeyChar(char key) {
		if ((key >= u8'0' && key <= u8'9') || key == u8'-')__buffer += key;
	}
	void IntegerInput_Event::LostFocus() {
		if (__buffer.empty())__buffer = u8"0";
		__func(Template::convert<int>(__buffer));
	}
	void IntegerInput_Event::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	FloatInput_Event::FloatInput_Event(const Rect& rect, const function<void(float)>& func, float _default) : Widget(rect), __buffer(Cvp::format(u8"%g", _default)), __func(func) { if (__buffer.empty())__buffer = u8"0.0"; }
	void FloatInput_Event::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if (!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void FloatInput_Event::KeyChar(char key) {
		if ((key >= u8'0' && key <= u8'9') || key == u8'-' || key == u8'.' || key == u8'E' || key == u8'e')__buffer += key;
	}
	void FloatInput_Event::LostFocus() {
		if (__buffer.empty())__buffer = u8"0.0";
		__func(Template::convert<float>(__buffer));
	}
	void FloatInput_Event::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	Slider_Event_H::Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default) :Widget(rect), __func(func), __gap(gap), __Min(Min), __Max(Max), __default(recut(Min, _default, Max, 2 * gap, rect.mW - 2 * gap)), __holding(false), __pos(__default), __defaultval(_default) {}
	Slider_Event_H::Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max) : Widget(rect), __func(func), __gap(gap), __Min(Min), __Max(Max), __default(rect.mW / 2), __holding(false), __pos(__default), __defaultval((Min + Max) / 2) {}
	Slider_Event_H::Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Max) : Widget(rect), __func(func), __gap(gap), __Min(0.0f), __Max(Max), __default(2 * gap), __holding(false), __pos(__default), __defaultval(0.0f) {}
	void Slider_Event_H::MovePos(int delta) {
		__pos = limit(2 * __gap, __pos + delta * (GetW() - 4 * __gap) * (WidgetManager::Shift() ? 4 : 1) / 64, GetW() - 2 * __gap);
		__func(recut(2 * __gap, __pos, GetW() - 2 * __gap, __Min, __Max));
	}
	void Slider_Event_H::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < __gap)MovePos(-1);
		else if (x > GetW() - __gap)MovePos(1);
		else if (Rect(__default - GetH() / 4, GetH() / 2, GetH() / 2, GetH() / 2).Contains(x, y)) __pos = __default, __func(__defaultval);
		else if (x > __pos - __gap && x < __pos + __gap) __holding = true;
	}
	void Slider_Event_H::MouseUp(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__holding) return;
		__holding = false;
		MovePos(0);
	}
	void Slider_Event_H::MouseWheel(int delta) {
		MovePos(-delta);
	}
	void Slider_Event_H::MouseMove(int x, int y) {
		if (!__holding) return;
		__pos = limit(2 * __gap, x, GetW() - 2 * __gap);
	}
	void Slider_Event_H::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::LEFT:MovePos(-1); break;
		case KeyCode::RIGHT:MovePos(1); break;
		case KeyCode::UP:MovePos(-4); break;
		case KeyCode::DOWN:MovePos(4); break;
		}
	}
	void Slider_Event_H::LostFocus() {
		if(__holding) MovePos(0);
		__holding = false;
	}
	void Slider_Event_H::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + __gap, GetY() + GetH(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + __gap, GetY(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor)
			});
		Geo::TriangleFan({
			Geo::Vertex(GetX() + GetW(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + GetW() - __gap, GetY() + GetH(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW() - __gap, GetY(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor)
			});
		if (GetFocus())DrawFullRect(GlobalStyle().SelectColor, { __pos - __gap,0,__gap * 2,GetH() });
		DrawRect(GlobalStyle().LineColor, { __pos - __gap,0,__gap * 2,GetH() });
		if (GetH() > 20)DrawLine(GetFocus() ? GlobalStyle().LineColor : GlobalStyle().LightLineColor, { {2 * __gap,GetH() / 2} ,{GetW() - 2 * __gap,GetH() / 2} });
		DrawFullTriangle(GlobalStyle().LineColor, { __pos, GetH() / 2 }, { __pos + GetH() / 4, 0 }, { __pos - GetH() / 4, 0 });
		DrawFullTriangle(GlobalStyle().LightColor, { __default, GetH() / 2 }, { __default + GetH() / 4, GetH() }, { __default - GetH() / 4, GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,__gap,GetH() });
		DrawRect(GlobalStyle().LineColor, { GetW() - __gap,0,__gap,GetH() });
	}
	Slider_Event_V::Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default) :Widget(rect), __func(func), __gap(gap), __Min(Min), __Max(Max), __default(recut(Min, _default, Max, 2 * gap, rect.mH - 2 * gap)), __holding(false), __pos(__default), __defaultval(_default) {}
	Slider_Event_V::Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max) : Widget(rect), __func(func), __gap(gap), __Min(Min), __Max(Max), __default(rect.mH / 2), __holding(false), __pos(__default), __defaultval((Min + Max) / 2) {}
	Slider_Event_V::Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Max) : Widget(rect), __func(func), __gap(gap), __Min(0.0f), __Max(Max), __default(2 * gap), __holding(false), __pos(__default), __defaultval(0.0f) {}
	void Slider_Event_V::MovePos(int delta) {
		__pos = limit(2 * __gap, __pos + delta * (GetH() - 4 * __gap) * (WidgetManager::Shift() ? 4 : 1) / 64, GetH() - 2 * __gap);
		__func(recut(2 * __gap, __pos, GetH() - 2 * __gap, __Min, __Max));
	}
	void Slider_Event_V::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (y < __gap)MovePos(-1);
		else if (y > GetH() - __gap)MovePos(1);
		else if (Rect(GetW() / 2, __default - GetW() / 4, GetW() / 2, GetW() / 2).Contains(x, y)) __pos = __default, __func(__defaultval);
		else if (y > __pos - __gap && y < __pos + __gap) __holding = true;
	}
	void Slider_Event_V::MouseUp(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__holding) return;
		__holding = false;
		MovePos(0);
	}
	void Slider_Event_V::MouseWheel(int delta) {
		MovePos(-delta);
	}
	void Slider_Event_V::MouseMove(int x, int y) {
		if (!__holding) return;
		__pos = limit(2 * __gap, y, GetH() - 2 * __gap);
	}
	void Slider_Event_V::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::LEFT:MovePos(-4); break;
		case KeyCode::RIGHT:MovePos(4); break;
		case KeyCode::UP:MovePos(-1); break;
		case KeyCode::DOWN:MovePos(1); break;
		}
	}
	void Slider_Event_V::LostFocus() {
		if (__holding) MovePos(0);
		__holding = false;
	}
	void Slider_Event_V::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY(), GlobalStyle().BaseColor)
			});
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + GetH() - __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH() - __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH(), GlobalStyle().BaseColor)
			});
		if (GetFocus())DrawFullRect(GlobalStyle().SelectColor, { 0,__pos - __gap,GetW(),__gap * 2 });
		DrawRect(GlobalStyle().LineColor, { 0,__pos - __gap,GetW(),__gap * 2 });
		if (GetW() > 20)DrawLine(GetFocus() ? GlobalStyle().LineColor : GlobalStyle().LightLineColor, { {GetW() / 2,2 * __gap} ,{GetW() / 2,GetH() - 2 * __gap} });
		DrawFullTriangle(GlobalStyle().LineColor, { GetW() / 2, __pos }, { 0, __pos + GetW() / 4 }, { 0, __pos - GetW() / 4 });
		DrawFullTriangle(GlobalStyle().LightColor, { GetW() / 2, __default }, { GetW(), __default + GetW() / 4 }, { GetW(), __default - GetW() / 4 });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),__gap });
		DrawRect(GlobalStyle().LineColor, { 0,GetH() - __gap,GetW(),__gap });
	}
	Check_Event::Check_Event(const Rect& rect, const function<void(bool)>& func, string_view label, bool _default) :Widget(rect), __func(func), __label(GlobalFont().MakeImage(label, rect.mW - __Height)), __buffer(_default) {}
	void Check_Event::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		__buffer = !__buffer, __func(__buffer);
	}
	void Check_Event::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawRect(GlobalStyle().LineColor, { (__Height - __Height1) / 2,(__Height - __Height1) / 2,__Height1,__Height1 });
		if (__buffer)DrawFullRect(GlobalStyle().LineColor, { (__Height - __Height2) / 2,(__Height - __Height2) / 2,__Height2,__Height2 });
		DrawImage(__label, { __Height, 2, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Event_Centralized::RadioButton::RadioButton(const Rect& rect, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __Height)), __buffer(false) {}
	void Radio_Event_Centralized::RadioButton::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		Radio_Event_Centralized* parent = (Radio_Event_Centralized*)GetParent();
		if (parent) parent->Select(this);
		else SetClosed();
	}
	void Radio_Event_Centralized::RadioButton::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height1 / 2));
		if (__buffer)DrawFullCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height2 / 2));
		DrawImage(__label, { __Height, 3, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Event_Centralized::Radio_Event_Centralized(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default, string_view label) : Widget(rect), __func(func), __label(GlobalFont().MakeImage(label, rect.mW - __TitleHeight)), __buffer(nullptr) {
		for (auto&& p : children) {
			RadioButton* temp = new RadioButton(p.first, p.second);
			if (__label)temp->Move(0, __TitleHeight);
			AddChild(temp);
		}
		__buffer = (RadioButton*)(GetChildren()[_default]);
		__buffer->__buffer = true;
	}
	void Radio_Event_Centralized::Select(RadioButton* child) {
		for (size_t i = 0; i < GetChildren().size(); ++i) if (GetChildren()[i] == child) {
			__buffer->__buffer = false;
			__buffer = child;
			__buffer->__buffer = true;
			__func(i);
		}
	}
	void Radio_Event_Centralized::Select(int child) {
		__buffer->__buffer = false;
		__buffer = (RadioButton*)(GetChildren()[child]);
		__buffer->__buffer = true;
		__func(child);
	}
	void Radio_Event_Centralized::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0, 0, GetW(), GetH() });
		DrawRect(GlobalStyle().LineColor, { 0, 0, GetW(), GetH() });
		if (__label) DrawImageMid(__label, { 0,0,GetW(), __TitleHeight }, GlobalStyle().LineColor);
	}
	Radio_Event_Distributed::RadioButton::RadioButton(const Rect& rect, const function<void(bool)>& func, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __Height)), __func(func), __buffer(false) {}
	void Radio_Event_Distributed::RadioButton::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		Radio_Event_Distributed* parent = (Radio_Event_Distributed*)GetParent();
		if (parent) parent->Select(this);
		else SetClosed();
	}
	void Radio_Event_Distributed::RadioButton::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height1 / 2));
		if (__buffer)DrawFullCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height2 / 2));
		DrawImage(__label, { __Height, 3, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Event_Distributed::Radio_Event_Distributed(const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __TitleHeight)), __buffer(nullptr) {
		for (auto&& p : children) {
			RadioButton* temp = new RadioButton(get<0>(p), get<1>(p), get<2>(p));
			if (__label)temp->Move(0, __TitleHeight);
			AddChild(temp);
		}
		__buffer = (RadioButton*)(GetChildren()[_default]);
		__buffer->__buffer = true;
	}
	void Radio_Event_Distributed::Select(RadioButton* child) {
		for (size_t i = 0; i < GetChildren().size(); ++i) if (GetChildren()[i] == child) {
			__buffer->__buffer = false;
			__buffer->__func(false);
			__buffer = child;
			__buffer->__buffer = true;
			__buffer->__func(true);
		}
	}
	void Radio_Event_Distributed::Select(int child) {
		__buffer->__buffer = false;
		__buffer->__func(false);
		__buffer = (RadioButton*)(GetChildren()[child]);
		__buffer->__buffer = true;
		__buffer->__func(true);
	}
	void Radio_Event_Distributed::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0, 0, GetW(), GetH() });
		DrawRect(GlobalStyle().LineColor, { 0, 0, GetW(), GetH() });
		if (__label) DrawImageMid(__label, { 0,0,GetW(), __TitleHeight }, GlobalStyle().LineColor);
	}
	ComboList_Event_Centralized::ListWidget::ListWidget(const Rect& rect, ComboList_Event_Centralized* base) :Widget(rect), __base(base) {
		AttachManager();
		SetInvisible();
	}
	void ComboList_Event_Centralized::ListWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__base)return SetClosed();
		__base->Select(y / __LineHeight);
	}
	void ComboList_Event_Centralized::ListWidget::MouseWheel(int delta) {
		if (!__base)return SetClosed();
		__base->Turn(__base->__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Event_Centralized::ListWidget::KeyDown(Cvp::KeyCode key) {
		if (!__base)return SetClosed();
		switch (key.Code()) {
		case KeyCode::RETURN:__base->Select(__base->__val); break;
		case KeyCode::LEFT:__base->Turn(__base->__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:__base->Turn(__base->__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:__base->Turn(__base->__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:__base->Turn(__base->__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Event_Centralized::ListWidget::LostFocus() {
		if (!__base)return SetClosed();
		__base->Select(__base->__val);
	}
	void ComboList_Event_Centralized::ListWidget::Draw() {
		if (!__base)return SetClosed();
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		int y = __LineHeight;
		while (y < GetH()) {
			DrawFullRect(GlobalStyle().LightColor, { 0,y,GetW(),__LineHeight - 1 });
			y += 2 * __LineHeight;
		}
		y = 0;
		for (size_t i = 0; i < __base->__buffer.size(); ++i) {
			DrawImageMid(__base->__buffer[i], { 0,y,GetW(), __LineHeight }, GlobalStyle().LineColor);
			y += __LineHeight;
		}
		DrawRect(GlobalStyle().LightLineColor, { 0,0,GetW(),GetH() });
	}
	void ComboList_Event_Centralized::ListWidget::Clean() {
		if (__base->GetClosed())SetClosed();
	}
	ComboList_Event_Centralized::ComboList_Event_Centralized(const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default) :Widget(rect), __buffer(), __val(_default), __list(new ListWidget({ GetX(),GetY(),GetW() - __Gap, (int)elements.size() * __LineHeight }, this)), __func(func) {
		__buffer.reserve(elements.size());
		for (auto&& p : elements) __buffer.push_back(GlobalFont().MakeImage(p));
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Event_Centralized::Turn(int val) {
		__val = limit<int>(0, val, __buffer.size() - 1);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Event_Centralized::Select(int val) {
		Turn(val);
		__func(__val);
		__list->SetInvisible();
		__list->SetFocus(false);
	}
	void ComboList_Event_Centralized::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < GetW() - __Gap) return;
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
		__list->SetInvisible(false);
		__list->SetFocus();
	}
	void ComboList_Event_Centralized::MouseWheel(int delta) {
		Turn(__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Event_Centralized::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::LEFT:Turn(__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:Turn(__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:Turn(__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:Turn(__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Event_Centralized::LostFocus() {
		if (__list->GetInvisible())__func(__val);
	}
	void ComboList_Event_Centralized::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() });
		DrawFullRect(GlobalStyle().LineColor, { GetW() - __Gap,0,__Gap, GetH() });
		DrawFullTriangle(GlobalStyle().LightColor, { (float)(GetW() - __Gap / 2 - 4),(float)(GetH() / 2 - 3) }, { (float)(GetW() - __Gap / 2),(float)(GetH() / 2 + 3) }, { (float)(GetW() - __Gap / 2 + 4),(float)(GetH() / 2 - 3) });
		DrawImageMid(__buffer[__val], { 0,0,GetW() - __Gap, GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() });
	}
	void ComboList_Event_Centralized::Clean() {
		if (__list->GetClosed())SetClosed();
	}
	ComboList_Event_Distributed::ListWidget::ListWidget(const Rect& rect, ComboList_Event_Distributed* base) :Widget(rect), __base(base) {
		AttachManager();
		SetInvisible();
	}
	void ComboList_Event_Distributed::ListWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__base)return SetClosed();
		__base->Select(y / __LineHeight);
	}
	void ComboList_Event_Distributed::ListWidget::MouseWheel(int delta) {
		if (!__base)return SetClosed();
		__base->Turn(__base->__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Event_Distributed::ListWidget::KeyDown(Cvp::KeyCode key) {
		if (!__base)return SetClosed();
		switch (key.Code()) {
		case KeyCode::RETURN:__base->Select(__base->__val); break;
		case KeyCode::LEFT:__base->Turn(__base->__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:__base->Turn(__base->__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:__base->Turn(__base->__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:__base->Turn(__base->__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Event_Distributed::ListWidget::LostFocus() {
		if (!__base)return SetClosed();
		__base->Select(__base->__val);
	}
	void ComboList_Event_Distributed::ListWidget::Draw() {
		if (!__base)return SetClosed();
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		int y = __LineHeight;
		while (y < GetH()) {
			DrawFullRect(GlobalStyle().LightColor, { 0,y,GetW(),__LineHeight - 1 });
			y += 2 * __LineHeight;
		}
		y = 0;
		for (size_t i = 0; i < __base->__buffer.size(); ++i) {
			DrawImageMid(__base->__buffer[i], { 0,y,GetW(), __LineHeight }, GlobalStyle().LineColor);
			y += __LineHeight;
		}
		DrawRect(GlobalStyle().LightLineColor, { 0,0,GetW(),GetH() });
	}
	void ComboList_Event_Distributed::ListWidget::Clean() {
		if (__base->GetClosed())SetClosed();
	}
	ComboList_Event_Distributed::ComboList_Event_Distributed(const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default) :Widget(rect), __buffer(), __val(_default), __prevVal(_default), __list(new ListWidget({ GetX(),GetY(),GetW() - __Gap, (int)elements.size() * __LineHeight }, this)), __func() {
		__buffer.reserve(elements.size());
		__func.reserve(elements.size());
		for (auto&& p : elements) __buffer.push_back(GlobalFont().MakeImage(p.first)), __func.push_back(p.second);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Event_Distributed::Turn(int val) {
		__val = limit<int>(0, val, __buffer.size() - 1);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Event_Distributed::Select(int val) {
		Turn(val);
		__func[__prevVal](false), __prevVal = __val, __func[__prevVal](true);
		__list->SetInvisible();
		__list->SetFocus(false);
	}
	void ComboList_Event_Distributed::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < GetW() - __Gap) return;
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
		__list->SetInvisible(false);
		__list->SetFocus();
	}
	void ComboList_Event_Distributed::MouseWheel(int delta) {
		Turn(__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Event_Distributed::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::LEFT:Turn(__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:Turn(__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:Turn(__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:Turn(__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Event_Distributed::LostFocus() {
		if (__list->GetInvisible())__func[__prevVal](false), __prevVal = __val, __func[__prevVal](true);
	}
	void ComboList_Event_Distributed::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() });
		DrawFullRect(GlobalStyle().LineColor, { GetW() - __Gap,0,__Gap, GetH() });
		DrawFullTriangle(GlobalStyle().LightColor, { (float)(GetW() - __Gap / 2 - 4),(float)(GetH() / 2 - 3) }, { (float)(GetW() - __Gap / 2),(float)(GetH() / 2 + 3) }, { (float)(GetW() - __Gap / 2 + 4),(float)(GetH() / 2 - 3) });
		DrawImageMid(__buffer[__val], { 0,0,GetW() - __Gap, GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() });
	}
	void ComboList_Event_Distributed::Clean() {
		if (__list->GetClosed())SetClosed();
	}










	Button::Button(const Rect& rect, const function<void(void)>& func, string_view label) :Widget(rect), __func(func), __mouse(0, 0), __label(GlobalFont().MakeImage(label)) {}
	void Button::MouseMove(int x, int y) {
		__mouse = Rect(0, 0, GetW(), GetH()).Limit(Point<int>(x, y));
	}
	void Button::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key == Cvp::MouseCode::LEFT)__func();
	}
	void Button::Draw() {
		if (GetDown()) {
			DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
			DrawRect(GlobalStyle().LineColor, { 1,1,GetW() - 2,GetH() - 2 });
		} else {
			DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
			DrawRect(GlobalStyle().LineColor, { 0,0,GetW() - 2,GetH() - 2 });
			DrawRect(GlobalStyle().LineColor, { 2,2,GetW() - 2,GetH() - 2 });
		}
		DrawImageMid(__label, { 2,2,GetW() - 4,GetH() - 4 }, GlobalStyle().LineColor);
		if (GetDown()) {
			Geo::TriangleFan({
				Geo::Vertex(GetX() + __mouse.mX, GetY() + __mouse.mY, Geo::Transp(GlobalStyle().LineColor, 0.6f)),
				Geo::Vertex(GetX(), GetY(), Geo::Transp(GlobalStyle().LineColor,1.0f)),
				Geo::Vertex(GetX() + GetW(), GetY(), Geo::Transp(GlobalStyle().LineColor,1.0f)),
				Geo::Vertex(GetX() + GetW(), GetY() + GetH(), Geo::Transp(GlobalStyle().LineColor,1.0f)),
				Geo::Vertex(GetX(), GetY() + GetH(), Geo::Transp(GlobalStyle().LineColor,1.0f)),
				Geo::Vertex(GetX(), GetY(), Geo::Transp(GlobalStyle().LineColor,1.0f))
				});
		}
	}
	KeySelector_Link::KeySelector_Link(Point<int> pos, Cvp::KeyCode& link) :Widget({ pos.mX,pos.mY,__Width,__Height }), __link(link), __image(__KeyTag(link.Code())), __specialColor(GlobalStyle().BaseColor) {}
	void KeySelector_Link::KeyDown(Cvp::KeyCode key) {
		if (inrange(key.Code(), KeyCode::SHIFT, KeyCode::CONTROL, KeyCode::MENU))return;
		__specialColor = (key.Shift() ? 0xffu : 0) | (key.Ctrl() ? 0xff00u : 0) | (key.Alt() ? 0xff0000ul : 0);
		__link = key, __image = __KeyTag(key.Code()), SetFocus(false);
	}
	void KeySelector_Link::Draw() {
		DrawFullRect(Geo::Mix(GlobalStyle().BaseColor, __specialColor | GlobalStyle().BaseColor, GlobalStyle().MixRate), { 0,0,__Width,__Height }, (float)(__Height / 2));
		DrawRect(GlobalStyle().LineColor, { 0,0,__Width,__Height }, (float)(__Height / 2));
		if (__image) DrawImageMid(__image, { 0,0,__Width,__Height }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	StringInput_Link::StringInput_Link(const Rect& rect, string& link) :Widget(rect), __link(link), __buffer(link) {}
	void StringInput_Link::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if (!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void StringInput_Link::KeyChar(char key) {
		__buffer += key;
	}
	void StringInput_Link::LostFocus() {
		__link = __buffer;
	}
	void StringInput_Link::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	IntegerInput_Link::IntegerInput_Link(const Rect& rect, int& link) : Widget(rect), __link(link), __buffer(CTformat<CTformat_buffer<string>, int>::format(link)) { if (__buffer.empty())__buffer = u8"0"; }
	void IntegerInput_Link::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if (!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void IntegerInput_Link::KeyChar(char key) {
		if ((key >= u8'0' && key <= u8'9') || key == u8'-')__buffer += key;
	}
	void IntegerInput_Link::LostFocus() {
		if (__buffer.empty())__buffer = u8"0";
		__link = Template::convert<int>(__buffer);
	}
	void IntegerInput_Link::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	FloatInput_Link::FloatInput_Link(const Rect& rect, float& link) : Widget(rect), __link(link), __buffer(CTformat<CTformat_buffer<string>, float>::format(link)) { if (__buffer.empty())__buffer = u8"0.0"; }
	void FloatInput_Link::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::ESCAPE:__buffer.clear(); break;
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::BACKSPACE:if (!__buffer.empty())__buffer.resize(__buffer.size() - 1); break;
		case KeyCode::C:if (key.Ctrl()) Cvp::ClipBoardWrite(__buffer); break;
		case KeyCode::V:if (key.Ctrl()) __buffer += Cvp::ClipBoardRead<string>(); break;
		}
	}
	void FloatInput_Link::KeyChar(char key) {
		if ((key >= u8'0' && key <= u8'9') || key == u8'-' || key == u8'.' || key == u8'E' || key == u8'e')__buffer += key;
	}
	void FloatInput_Link::LostFocus() {
		if (__buffer.empty())__buffer = u8"0.0";
		__link = Template::convert<float>(__buffer);
	}
	void FloatInput_Link::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawRect(GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor, { 0,0,GetW(),GetH() }, 4.0f);
		DrawString(__buffer, { 8,2,GetW() - 16,GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
	}
	Slider_Link_H::Slider_Link_H(const Rect& rect, float& link, int gap, float Min, float Max) : Widget(rect), __link(link), __gap(gap), __Min(Min), __Max(Max), __default(recut(Min, link, Max, 2 * gap, rect.mW - 2 * gap)), __holding(false), __pos(__default), __defaultval(link) {}
	Slider_Link_H::Slider_Link_H(const Rect& rect, float& link, int gap, float Max) : Widget(rect), __link(link), __gap(gap), __Min(0.0f), __Max(Max), __default(2 * gap), __holding(false), __pos(__default), __defaultval(0.0f) {}
	void Slider_Link_H::MovePos(int delta) {
		__pos = limit(2 * __gap, __pos + delta * (GetW() - 4 * __gap) * (WidgetManager::Shift() ? 4 : 1) / 64, GetW() - 2 * __gap);
		__link = recut(2 * __gap, __pos, GetW() - 2 * __gap, __Min, __Max);
	}
	void Slider_Link_H::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < __gap)MovePos(-1);
		else if (x > GetW() - __gap)MovePos(1);
		else if (Rect(__default - GetH() / 4, GetH() / 2, GetH() / 2, GetH() / 2).Contains(x, y)) __pos = __default, __link = __defaultval;
		else if (x > __pos - __gap && x < __pos + __gap) __holding = true;
	}
	void Slider_Link_H::MouseUp(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__holding) return;
		__holding = false;
		MovePos(0);
	}
	void Slider_Link_H::MouseWheel(int delta) {
		MovePos(-delta);
	}
	void Slider_Link_H::MouseMove(int x, int y) {
		if (!__holding) return;
		__pos = limit(2 * __gap, x, GetW() - 2 * __gap);
	}
	void Slider_Link_H::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::LEFT:MovePos(-1); break;
		case KeyCode::RIGHT:MovePos(1); break;
		case KeyCode::UP:MovePos(-4); break;
		case KeyCode::DOWN:MovePos(4); break;
		}
	}
	void Slider_Link_H::LostFocus() {
		if (__holding) MovePos(0);
		__holding = false;
	}
	void Slider_Link_H::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + __gap, GetY() + GetH(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + __gap, GetY(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor)
			});
		Geo::TriangleFan({
			Geo::Vertex(GetX() + GetW(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX() + GetW() - __gap, GetY() + GetH(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW() - __gap, GetY(), GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor)
			});
		if (GetFocus())DrawFullRect(GlobalStyle().SelectColor, { __pos - __gap,0,__gap * 2,GetH() });
		DrawRect(GlobalStyle().LineColor, { __pos - __gap,0,__gap * 2,GetH() });
		if (GetH() > 20)DrawLine(GetFocus() ? GlobalStyle().LineColor : GlobalStyle().LightLineColor, { {2 * __gap,GetH() / 2} ,{GetW() - 2 * __gap,GetH() / 2} });
		DrawFullTriangle(GlobalStyle().LineColor, { __pos, GetH() / 2 }, { __pos + GetH() / 4, 0 }, { __pos - GetH() / 4, 0 });
		DrawFullTriangle(GlobalStyle().LightColor, { __default, GetH() / 2 }, { __default + GetH() / 4, GetH() }, { __default - GetH() / 4, GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,__gap,GetH() });
		DrawRect(GlobalStyle().LineColor, { GetW() - __gap,0,__gap,GetH() });
	}
	Slider_Link_V::Slider_Link_V(const Rect& rect, float& link, int gap, float Min, float Max) : Widget(rect), __link(link), __gap(gap), __Min(Min), __Max(Max), __default(recut(Min, link, Max, 2 * gap, rect.mW - 2 * gap)), __holding(false), __pos(__default), __defaultval(link) {}
	Slider_Link_V::Slider_Link_V(const Rect& rect, float& link, int gap, float Max) : Widget(rect), __link(link), __gap(gap), __Min(0.0f), __Max(Max), __default(2 * gap), __holding(false), __pos(__default), __defaultval(0.0f) {}
	void Slider_Link_V::MovePos(int delta) {
		__pos = limit(2 * __gap, __pos + delta * (GetH() - 4 * __gap) * (WidgetManager::Shift() ? 4 : 1) / 64, GetH() - 2 * __gap);
		__link = recut(2 * __gap, __pos, GetH() - 2 * __gap, __Min, __Max);
	}
	void Slider_Link_V::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (y < __gap)MovePos(-1);
		else if (y > GetH() - __gap)MovePos(1);
		else if (Rect(GetW() / 2, __default - GetW() / 4, GetW() / 2, GetW() / 2).Contains(x, y)) __pos = __default, __link = __defaultval;
		else if (y > __pos - __gap && y < __pos + __gap) __holding = true;
	}
	void Slider_Link_V::MouseUp(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__holding) return;
		__holding = false;
		MovePos(0);
	}
	void Slider_Link_V::MouseWheel(int delta) {
		MovePos(-delta);
	}
	void Slider_Link_V::MouseMove(int x, int y) {
		if (!__holding) return;
		__pos = limit(2 * __gap, y, GetH() - 2 * __gap);
	}
	void Slider_Link_V::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::LEFT:MovePos(-4); break;
		case KeyCode::RIGHT:MovePos(4); break;
		case KeyCode::UP:MovePos(-1); break;
		case KeyCode::DOWN:MovePos(1); break;
		}
	}
	void Slider_Link_V::LostFocus() {
		if (__holding) MovePos(0);
		__holding = false;
	}
	void Slider_Link_V::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY(), GlobalStyle().BaseColor)
			});
		Geo::TriangleFan({
			Geo::Vertex(GetX(), GetY() + GetH(), GlobalStyle().BaseColor),
			Geo::Vertex(GetX(), GetY() + GetH() - __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH() - __gap, GetFocus() ? GlobalStyle().SelectColor : GlobalStyle().LightLineColor),
			Geo::Vertex(GetX() + GetW(), GetY() + GetH(), GlobalStyle().BaseColor)
			});
		if (GetFocus())DrawFullRect(GlobalStyle().SelectColor, { 0,__pos - __gap,GetW(),__gap * 2 });
		DrawRect(GlobalStyle().LineColor, { 0,__pos - __gap,GetW(),__gap * 2 });
		if (GetW() > 20)DrawLine(GetFocus() ? GlobalStyle().LineColor : GlobalStyle().LightLineColor, { {GetW() / 2,2 * __gap} ,{GetW() / 2,GetH() - 2 * __gap} });
		DrawFullTriangle(GlobalStyle().LineColor, { GetW() / 2, __pos }, { 0, __pos + GetW() / 4 }, { 0, __pos - GetW() / 4 });
		DrawFullTriangle(GlobalStyle().LightColor, { GetW() / 2, __default }, { GetW(), __default + GetW() / 4 }, { GetW(), __default - GetW() / 4 });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),GetH() });
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(),__gap });
		DrawRect(GlobalStyle().LineColor, { 0,GetH() - __gap,GetW(),__gap });
	}
	Check_Link::Check_Link(const Rect& rect, bool& link, string_view label) :Widget(rect), __link(link), __label(GlobalFont().MakeImage(label, rect.mW - __Height)) {}
	void Check_Link::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		__link = !__link;
	}
	void Check_Link::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawRect(GlobalStyle().LineColor, { (__Height - __Height1) / 2,(__Height - __Height1) / 2,__Height1,__Height1 });
		if (__link)DrawFullRect(GlobalStyle().LineColor, { (__Height - __Height2) / 2,(__Height - __Height2) / 2,__Height2,__Height2 });
		DrawImage(__label, { __Height, 0, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Link_Centralized::RadioButton::RadioButton(const Rect& rect, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __Height)), __buffer(false) {}
	void Radio_Link_Centralized::RadioButton::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		Radio_Link_Centralized* parent = (Radio_Link_Centralized*)GetParent();
		if (parent) parent->Select(this);
		else SetClosed();
	}
	void Radio_Link_Centralized::RadioButton::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height1 / 2));
		if (__buffer)DrawFullCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height2 / 2));
		DrawImage(__label, { __Height, 3, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Link_Centralized::Radio_Link_Centralized(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default, string_view label) :Widget(rect), __link(link), __label(GlobalFont().MakeImage(label, rect.mW - __TitleHeight)), __buffer(nullptr) {
		for (auto&& p : children) {
			RadioButton* temp = new RadioButton(p.first, p.second);
			if (__label)temp->Move(0, __TitleHeight);
			AddChild(temp);
		}
		__buffer = (RadioButton*)(GetChildren()[_default]);
		__buffer->__buffer = true;
	}
	void Radio_Link_Centralized::Select(RadioButton* child) {
		for (size_t i = 0; i < GetChildren().size(); ++i) if (GetChildren()[i] == child) {
			__buffer->__buffer = false;
			__buffer = child;
			__buffer->__buffer = true;
			__link = i;
		}
	}
	void Radio_Link_Centralized::Select(int child) {
		__buffer->__buffer = false;
		__buffer = (RadioButton*)(GetChildren()[child]);
		__buffer->__buffer = true;
		__link = child;
	}
	void Radio_Link_Centralized::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0, 0, GetW(), GetH() });
		DrawRect(GlobalStyle().LineColor, { 0, 0, GetW(), GetH() });
		if (__label) DrawImageMid(__label, { 0,0,GetW(), __TitleHeight }, GlobalStyle().LineColor);
	}
	Radio_Link_Distributed::RadioButton::RadioButton(const Rect& rect, bool& link, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __Height)), __link(link) {}
	void Radio_Link_Distributed::RadioButton::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (x > __Height || y > __Height)return;
		Radio_Link_Distributed* parent = (Radio_Link_Distributed*)GetParent();
		if (parent) parent->Select(this);
		else SetClosed();
	}
	void Radio_Link_Distributed::RadioButton::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,__Height,__Height });
		DrawCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height1 / 2));
		if (__link)DrawFullCircle(GlobalStyle().LineColor, { __Height / 2, __Height / 2 }, (float)(__Height2 / 2));
		DrawImage(__label, { __Height, 3, GetW() - __Height, GetH() }, GlobalStyle().LineColor);
	}
	Radio_Link_Distributed::Radio_Link_Distributed(const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default, string_view label) :Widget(rect), __label(GlobalFont().MakeImage(label, rect.mW - __TitleHeight)), __buffer(nullptr) {
		for (auto&& p : children) {
			RadioButton* temp = new RadioButton(get<0>(p), *get<1>(p), get<2>(p));
			if (__label)temp->Move(0, __TitleHeight);
			AddChild(temp);
		}
		__buffer = (RadioButton*)(GetChildren()[_default]);
	}
	void Radio_Link_Distributed::Select(RadioButton* child) {
		for (size_t i = 0; i < GetChildren().size(); ++i) if (GetChildren()[i] == child) {
			__buffer->__link = false;
			__buffer = child;
			__buffer->__link = true;
		}
	}
	void Radio_Link_Distributed::Select(int child) {
		__buffer->__link = false;
		__buffer = (RadioButton*)(GetChildren()[child]);
		__buffer->__link = true;
	}
	void Radio_Link_Distributed::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0, 0, GetW(), GetH() });
		DrawRect(GlobalStyle().LineColor, { 0, 0, GetW(), GetH() });
		if (__label) DrawImageMid(__label, { 0,0,GetW(), __TitleHeight }, GlobalStyle().LineColor);
	}
	ComboList_Link_Centralized::ListWidget::ListWidget(const Rect& rect, ComboList_Link_Centralized* base) :Widget(rect), __base(base) {
		AttachManager();
		SetInvisible();
	}
	void ComboList_Link_Centralized::ListWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__base)return SetClosed();
		__base->Select(y / __LineHeight);
	}
	void ComboList_Link_Centralized::ListWidget::MouseWheel(int delta) {
		if (!__base)return SetClosed();
		__base->Turn(__base->__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Link_Centralized::ListWidget::KeyDown(Cvp::KeyCode key) {
		if (!__base)return SetClosed();
		switch (key.Code()) {
		case KeyCode::RETURN:__base->Select(__base->__val); break;
		case KeyCode::LEFT:__base->Turn(__base->__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:__base->Turn(__base->__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:__base->Turn(__base->__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:__base->Turn(__base->__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Link_Centralized::ListWidget::LostFocus() {
		if (!__base)return SetClosed();
		__base->Select(__base->__val);
	}
	void ComboList_Link_Centralized::ListWidget::Draw() {
		if (!__base)return SetClosed();
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		int y = __LineHeight;
		while (y < GetH()) {
			DrawFullRect(GlobalStyle().LightColor, { 0,y,GetW(),__LineHeight - 1 });
			y += 2 * __LineHeight;
		}
		y = 0;
		for (size_t i = 0; i < __base->__buffer.size(); ++i) {
			DrawImageMid(__base->__buffer[i], { 0,y,GetW(), __LineHeight }, GlobalStyle().LineColor);
			y += __LineHeight;
		}
		DrawRect(GlobalStyle().LightLineColor, { 0,0,GetW(),GetH() });
	}
	void ComboList_Link_Centralized::ListWidget::Clean() {
		if (__base->GetClosed())SetClosed();
	}
	ComboList_Link_Centralized::ComboList_Link_Centralized(const Rect& rect, initializer_list<string_view> elements, int& link, int _default) :Widget(rect), __buffer(), __val(_default), __list(new ListWidget({ GetX(),GetY(),GetW() - __Gap, (int)elements.size() * __LineHeight }, this)), __link(link) {
		__buffer.reserve(elements.size());
		for (auto&& p : elements) __buffer.push_back(GlobalFont().MakeImage(p));
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Link_Centralized::Turn(int val) {
		__val = limit<int>(0, val, __buffer.size() - 1);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Link_Centralized::Select(int val) {
		Turn(val);
		__link = __val;
		__list->SetInvisible();
		__list->SetFocus(false);
	}
	void ComboList_Link_Centralized::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < GetW() - __Gap) return;
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
		__list->SetInvisible(false);
		__list->SetFocus();
		string a, b;
		bool c = a < b;
	}
	void ComboList_Link_Centralized::MouseWheel(int delta) {
		Turn(__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Link_Centralized::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::LEFT:Turn(__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:Turn(__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:Turn(__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:Turn(__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Link_Centralized::LostFocus() {
		if (__list->GetInvisible())__link = __val;
	}
	void ComboList_Link_Centralized::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() });
		DrawFullRect(GlobalStyle().LineColor, { GetW() - __Gap,0,__Gap, GetH() });
		DrawFullTriangle(GlobalStyle().LightColor, { (float)(GetW() - __Gap / 2 - 4),(float)(GetH() / 2 - 3) }, { (float)(GetW() - __Gap / 2),(float)(GetH() / 2 + 3) }, { (float)(GetW() - __Gap / 2 + 4),(float)(GetH() / 2 - 3) });
		DrawImageMid(__buffer[__val], { 0,0,GetW() - __Gap, GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() });
	}
	void ComboList_Link_Centralized::Clean() {
		if (__list->GetClosed())SetClosed();
	}
	ComboList_Link_Distributed::ListWidget::ListWidget(const Rect& rect, ComboList_Link_Distributed* base) :Widget(rect), __base(base) {
		AttachManager();
		SetInvisible();
	}
	void ComboList_Link_Distributed::ListWidget::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (!__base)return SetClosed();
		__base->Select(y / __LineHeight);
	}
	void ComboList_Link_Distributed::ListWidget::MouseWheel(int delta) {
		if (!__base)return SetClosed();
		__base->Turn(__base->__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Link_Distributed::ListWidget::KeyDown(Cvp::KeyCode key) {
		if (!__base)return SetClosed();
		switch (key.Code()) {
		case KeyCode::RETURN:__base->Select(__base->__val); break;
		case KeyCode::LEFT:__base->Turn(__base->__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:__base->Turn(__base->__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:__base->Turn(__base->__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:__base->Turn(__base->__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Link_Distributed::ListWidget::LostFocus() {
		if (!__base)return SetClosed();
		__base->Select(__base->__val);
	}
	void ComboList_Link_Distributed::ListWidget::Draw() {
		if (!__base)return SetClosed();
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(),GetH() });
		int y = __LineHeight;
		while (y < GetH()) {
			DrawFullRect(GlobalStyle().LightColor, { 0,y,GetW(),__LineHeight - 1 });
			y += 2 * __LineHeight;
		}
		y = 0;
		for (size_t i = 0; i < __base->__buffer.size(); ++i) {
			DrawImageMid(__base->__buffer[i], { 0,y,GetW(), __LineHeight }, GlobalStyle().LineColor);
			y += __LineHeight;
		}
		DrawRect(GlobalStyle().LightLineColor, { 0,0,GetW(),GetH() });
	}
	void ComboList_Link_Distributed::ListWidget::Clean() {
		if (__base->GetClosed())SetClosed();
	}
	ComboList_Link_Distributed::ComboList_Link_Distributed(const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default) :Widget(rect), __buffer(), __val(_default), __prevVal(_default), __list(new ListWidget({ GetX(),GetY(),GetW() - __Gap, (int)elements.size() * __LineHeight }, this)), __link() {
		__buffer.reserve(elements.size());
		__link.reserve(elements.size());
		for (auto&& p : elements) __buffer.push_back(GlobalFont().MakeImage(p.first)), __link.push_back(p.second);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Link_Distributed::Turn(int val) {
		__val = limit<int>(0, val, __buffer.size() - 1);
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
	}
	void ComboList_Link_Distributed::Select(int val) {
		Turn(val);
		*(__link[__prevVal]) = false, __prevVal = __val, * (__link[__prevVal]) = true;
		__list->SetInvisible();
		__list->SetFocus(false);
	}
	void ComboList_Link_Distributed::MouseDown(int x, int y, Cvp::MouseCode key) {
		if (key != Cvp::MouseCode::LEFT)return;
		if (x < GetW() - __Gap) return;
		__list->MoveTo(GetX(), (__Height - __LineHeight) / 2 + GetY() - __LineHeight * __val);
		__list->SetInvisible(false);
		__list->SetFocus();
	}
	void ComboList_Link_Distributed::MouseWheel(int delta) {
		Turn(__val + (WidgetManager::Shift() ? 4 * delta : delta));
	}
	void ComboList_Link_Distributed::KeyDown(Cvp::KeyCode key) {
		switch (key.Code()) {
		case KeyCode::RETURN:SetFocus(false); break;
		case KeyCode::LEFT:Turn(__val + (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::RIGHT:Turn(__val - (WidgetManager::Shift() ? 9 : 3)); break;
		case KeyCode::UP:Turn(__val + (WidgetManager::Shift() ? 3 : 1)); break;
		case KeyCode::DOWN:Turn(__val - (WidgetManager::Shift() ? 3 : 1)); break;
		}
	}
	void ComboList_Link_Distributed::LostFocus() {
		if (__list->GetInvisible())*(__link[__prevVal]) = false, __prevVal = __val, * (__link[__prevVal]) = true;
	}
	void ComboList_Link_Distributed::Draw() {
		DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() });
		DrawFullRect(GlobalStyle().LineColor, { GetW() - __Gap,0,__Gap, GetH() });
		DrawFullTriangle(GlobalStyle().LightColor, { (float)(GetW() - __Gap / 2 - 4),(float)(GetH() / 2 - 3) }, { (float)(GetW() - __Gap / 2),(float)(GetH() / 2 + 3) }, { (float)(GetW() - __Gap / 2 + 4),(float)(GetH() / 2 - 3) });
		DrawImageMid(__buffer[__val], { 0,0,GetW() - __Gap, GetH() }, GetFocus() ? GlobalStyle().SelectLineColor : GlobalStyle().LineColor);
		DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() });
	}
	void ComboList_Link_Distributed::Clean() {
		if (__list->GetClosed())SetClosed();
	}
#endif
}