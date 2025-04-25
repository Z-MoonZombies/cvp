#pragma once
#include "pvzStatic.h"
#include <ImageLib.h>
#pragma comment(lib,"ImageLib.lib")
namespace Ui {
	inline Pvz::D3DInterface* __d3dinterface() { return Pvz::gGameApp && Pvz::gGameApp->mDDInterface && Pvz::gGameApp->mDDInterface->mD3DInterface ? Pvz::gGameApp->mDDInterface->mD3DInterface : nullptr; }
	class SharedImage {
		friend class Font;
		class ref {
			Pvz::DDImage __img;
			int __num;
		public:
			ref() :__img(Pvz::gGameApp->mDDInterface), __num(1) {}
			~ref() { __img.Kill(false); }
			Pvz::DDImage& Image() { return __img; }
			int& Num() { return __num; }
		};
		ref* __p;
		static SharedImage __makeAlphaImage(int w, int h, DWORD* bits);
		static SharedImage __makeEmptyImage();
	public:
		SharedImage();
		SharedImage(int w, int h, DWORD* bits);
		SharedImage(int w, int h, DWORD* bits, Rect rect);
		SharedImage(Pvz::DDImage* img);
		SharedImage(const SharedImage& that);
		SharedImage(SharedImage&& that)noexcept;
		SharedImage& operator=(const SharedImage& that);
		SharedImage& operator=(SharedImage&& that)noexcept;
		~SharedImage();
		SharedImage MakeBranch()const;
		SharedImage& Branch();
		Pvz::DDImage* Image()const;
		Pvz::DDImage* operator->()const;
		Pvz::DDImage& operator*()const;
		operator Pvz::DDImage* ()const;
		void Draw(DWORD theColor, const Rect& theSrcRect, const Matrix3& theTransform, bool mix = false, const Rect& theDestRect = { 0,0,0x3ffffffful,0x3ffffffful })const;
		SharedImage(const string& path);
		bool Write(const string& path)const;
		static SharedImage TakeScreenShot();
		static SharedImage GetClipBoard();
		void SetClipBoard()const;
	};
	class Geo {
		static constexpr DWORD D3DFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	public:
		using Vertex = BasicVertex;
#define DrawVertex(name,type)																																					\
			static void name(const Vertex* vertex,size_t num){																													\
			IDirect3DDevice7* p = __d3dinterface()->mD3DDevice;																													\
				if (p) {																																						\
					p->SetTexture(0, nullptr);																																	\
					p->DrawPrimitive(type, D3DFVF, (void*)vertex, num, 0);																										\
				}																																								\
			}																																									\
			static void name(DWORD color,const Point<float>* vertex,size_t num){																								\
				Vertex* _list =(Vertex*)_malloca(num * sizeof(Vertex));																											\
				for(size_t i = 0; i < num; ++i)new(_list + i)Vertex(vertex[i].mX,vertex[i].mY,color);																			\
				name(_list,num);																																				\
				_freea(_list);																																					\
			}																																									\
			static void name(const function<DWORD(float,float)>& color,const Point<float>* vertex,size_t num){																	\
				Vertex* _list =(Vertex*)_malloca(num * sizeof(Vertex));																											\
				for(size_t i = 0; i < num; ++i)new(_list + i)Vertex(vertex[i].mX,vertex[i].mY,color(vertex[i].mX,vertex[i].mY));												\
				name(_list,num);																																				\
				_freea(_list);																																					\
			}																																									\
			static void name(vector<Vertex> vertex){ name(&vertex[0],vertex.size()); }																							\
			static void name(DWORD color,vector<Point<float> > vertex){ name(color,&vertex[0],vertex.size()); }																	\
			static void name(const function<DWORD(float,float)>& color,vector<Point<float> > vertex){ name(color,&vertex[0],vertex.size()); }									\
			static void name(initializer_list<Vertex> vertex){ name(vertex.begin(),vertex.size()); }																			\
			static void name(DWORD color,initializer_list<Point<float> > vertex){ name(color,vertex.begin(),vertex.size()); }													\
			static void name(const function<DWORD(float,float)>& color,initializer_list<Point<float> > vertex){ name(color,vertex.begin(),vertex.size()); }						\
			template<size_t len> static void name(array<Vertex, len> vertex) { name(vertex.begin(), vertex.size()); }															\
			template<size_t len> static void name(DWORD color, array<Point<float>, len> vertex) { name(color, vertex.begin(), vertex.size()); }									\
			template<size_t len> static void name(const function<DWORD(float, float)>& color, array<Point<float>, len> vertex) { name(color, vertex.begin(), vertex.size()); }
		DrawVertex(PointList, D3DPT_POINTLIST);
		DrawVertex(LineList, D3DPT_LINELIST);
		DrawVertex(LineTrip, D3DPT_LINESTRIP);
		DrawVertex(TriangleList, D3DPT_TRIANGLELIST);
		DrawVertex(TriangleTrip, D3DPT_TRIANGLESTRIP);
		DrawVertex(TriangleFan, D3DPT_TRIANGLEFAN);
#undef DrawVertex
		static void DrawLine(DWORD color, const Point<float>* point, size_t pointNum = 2);
		static void DrawLine(DWORD color, initializer_list<Point<float> > point);
		static void DrawTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate);
		static void DrawFullTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate);
		static void DrawTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3);
		static void DrawFullTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3);
		static void DrawRect(DWORD color, const Rect& rect, float roundR = 0.0f);
		static void DrawFullRect(DWORD color, const Rect& rect, float roundR = 0.0f);
		static void DrawCircle(DWORD color, const Point<float>& mid, float radius);
		static void DrawFullCircle(DWORD color, const Point<float>& mid, float radius);
		static void DrawPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate);
		static void DrawFullPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate);
		static void DrawPolygon(DWORD color, const Point<float>* point, size_t edgeNum);
		static void DrawFullPolygon(DWORD color, const Point<float>* point, size_t edgeNum);
		static void DrawPolygon(DWORD color, initializer_list<Point<float> > point);
		static void DrawFullPolygon(DWORD color, initializer_list<Point<float> > point);
		static inline constexpr DWORD ARGB(DWORD r, DWORD g, DWORD b, DWORD a = 0xffu) { return a << 24 | (r & 0xffu) << 16 | (g & 0xffu) << 8 | (b & 0xffu); }
		static inline constexpr DWORD Mix(DWORD color1, DWORD color2, float rate = 0.5f) {
			const float rate2 = 1.0f - rate;
			return
				(((DWORD)((color1 & 0xff000000ul) * rate) + (DWORD)((color2 & 0xff000000ul) * rate2)) & 0xff000000ul) |
				(((DWORD)((color1 & 0x00ff0000ul) * rate) + (DWORD)((color2 & 0x00ff0000ul) * rate2)) & 0x00ff0000ul) |
				(((DWORD)((color1 & 0x0000ff00ul) * rate) + (DWORD)((color2 & 0x0000ff00ul) * rate2)) & 0x0000ff00ul) |
				(((DWORD)((color1 & 0x000000fful) * rate) + (DWORD)((color2 & 0x000000fful) * rate2)) & 0x000000fful);
		}
		static inline constexpr DWORD Dark(DWORD color, float rate = 0.5f) { return Mix(color & 0xff000000ul, color, rate); }
		static inline constexpr DWORD Light(DWORD color, float rate = 0.5f) { return Mix(color | 0xfffffful, color, rate); }
		static inline constexpr DWORD Transp(DWORD color, float rate = 0.5f) { return Mix(color & 0xfffffful, color, rate); }
		static inline constexpr DWORD Opaque(DWORD color, float rate = 0.5f) { return Mix(color | 0xff000000ul, color, rate); }
		static inline constexpr DWORD Dirty(DWORD color, float rate = 0.5f) {
			const DWORD avg = ((color & 0xffu) + (color >> 8 & 0xffu) + (color >> 16 & 0xffu)) / 3;
			return Mix((color & 0xff000000ul) | (0x10101ul * avg), color, rate);
		}
		static inline constexpr DWORD Pure(DWORD color, float rate = 0.5f) {
			const DWORD avg = ((color & 0xffu) + (color >> 8 & 0xffu) + (color >> 16 & 0xffu)) / 3;
			return Mix((color & 0xff000000ul) | ((color & 0xffu) > avg ? 0xffu : 0) | ((color >> 8 & 0xffu) > avg ? 0xff00u : 0) | ((color >> 16 & 0xffu) > avg ? 0xff0000ul : 0), color, rate);
		}
	};
	class __declspec(novtable) Font {
	protected:
		SharedImage* __buffer;
		int __w;
		int __h;
		int __g;
		Font();
		static SharedImage __makeAlphaImage(int w, int h, DWORD* bits) { return SharedImage::__makeAlphaImage(w, h, bits); }
		static SharedImage __makeEmptyImage() { return SharedImage::__makeEmptyImage(); }
	public:
		virtual const SharedImage& MakeImage(wchar_t chr)const = 0;
		virtual SharedImage MakeImage(wstring_view str, int w = 0x3ffffffful)const = 0;
		virtual ~Font();
		void DrawString(int x, int y, wstring_view str, DWORD color = 0xff000000ul, int w = 0x3ffffffful, int h = 0x3ffffffful)const;
		int GetStringWidth(wstring_view str)const;
		int GetStringHeight(wstring_view str, int w)const;
		int GetStringLine(wstring_view str, int w)const;
		SharedImage MakeImage(string_view str, int w = 0x3ffffffful)const;
		void DrawString(int x, int y, string_view str, DWORD color = 0xff000000ul, int w = 0x3ffffffful, int h = 0x3ffffffful)const;
		int GetStringWidth(string_view str)const;
		int GetStringHeight(string_view str, int w)const;
		int GetStringLine(string_view str, int w)const;
		void DrawStringA(int x, int y, string_view str, DWORD color = 0xff000000ul, int w = 0x3ffffffful, int h = 0x3ffffffful)const;
	};
	class SysFont :public Font {
		HFONT mHFont;
	public:
		const SharedImage& MakeImage(wchar_t chr)const override;
		SharedImage MakeImage(wstring_view str, int w = 0x3ffffffful)const override;
		~SysFont()override = default;
		SysFont(const char* name = u8"Ubuntu Mono", int pointSize = 16, int lineGap = 2, int script = ANSI_CHARSET, int weight = 100, bool italics = false, bool underline = false, bool useDevCaps = false);
	};
	struct Style {
		const DWORD BaseColor;
		const DWORD LineColor;
		const DWORD LightColor;
		const DWORD LightLineColor;
		const DWORD SelectColor;
		const DWORD SelectLineColor;
		const float MixRate;
		Style(
			DWORD base = Geo::ARGB(32, 32, 32),
			DWORD line = Geo::ARGB(192, 192, 192),
			DWORD light = Geo::ARGB(48, 48, 48),
			DWORD lightline = Geo::ARGB(128, 128, 128),
			DWORD select = Geo::ARGB(96, 0, 0),
			DWORD selectline = Geo::ARGB(128, 128, 255),
			float mixrate = 0.75f
		) :
			BaseColor(base),
			LineColor(line),
			LightColor(light),
			LightLineColor(lightline),
			SelectColor(select),
			SelectLineColor(selectline),
			MixRate(mixrate) {
		}
	};
	CVP_OBJECT(Font*, __GlobalFont, = new SysFont());
	inline Font& GlobalFont() { return *__GlobalFont(); }
	CVP_OBJECT(Style, GlobalStyle, );
	CVP_OBJECT(Cvp::UPCommand, __GlobalCmd, (u8""));
	inline string CallCmd(string_view cmd) { return __GlobalCmd().Call(cmd); }
	class Widget {
		friend class WidgetManager;
		friend class Widget;
		Rect __rect;
		Widget* __parent;
		Widget* __modal;
		vector<Widget*> __children;
		bool __invisible;
		bool __inactive;
		bool __modaled;
		bool __closed;
		bool __over;
		bool __down;
		bool __focus;
	public:
		Widget(const Rect& rect, initializer_list<Widget*> children = {});
		virtual ~Widget();

		void Move(int dx, int dy);
		void MoveTo(int x, int y);
		void SetParent(Widget* p);
		void DoModal(Widget* widget);
		size_t AddChild(Widget* child);
		size_t AddChildren(initializer_list<Widget*> _list);
		void SetInvisible(bool a = true);
		void SetInactive(bool a = true);
		void SetModaled(bool a = true);
		void SetClosed();
		void SetFocus(bool a = true);
		void AttachManager();
		void AttachTab(string_view label);

		int GetX()const;
		int GetY()const;
		int GetW()const;
		int GetH()const;
		Widget* GetParent()const;
		Widget* GetModal()const;
		const vector<Widget*>& GetChildren()const;
		bool GetInvisible()const;
		bool GetInactive()const;
		bool GetClosed()const;
		bool GetOver()const;
		bool GetDown()const;
		bool GetFocus()const;
	protected:
		void DrawImage(const SharedImage& theImage, int x, int y, DWORD theColor = 0xfffffffful)const;
		void DrawImage(const SharedImage& theImage, const Rect& theDstRect, DWORD theColor = 0xfffffffful)const;
		void DrawImageMid(const SharedImage& theImage, const Rect& theDstRect, DWORD theColor = 0xfffffffful)const;
		void DrawString(string_view str, int x, int y, DWORD theColor = 0xfffffffful)const;
		void DrawString(string_view str, const Rect& theDstRect, DWORD theColor = 0xfffffffful)const;
		void DrawString(wstring_view str, int x, int y, DWORD theColor = 0xfffffffful)const;
		void DrawString(wstring_view str, const Rect& theDstRect, DWORD theColor = 0xfffffffful)const;
		void DrawLine(DWORD color, const Point<float>* point, size_t pointNum = 2)const;
		void DrawLine(DWORD color, initializer_list<Point<float> > point)const;
		void DrawTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate)const;
		void DrawFullTriangle(DWORD color, const Point<float>& mid, float height, float width, float rotate)const;
		void DrawTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3)const;
		void DrawFullTriangle(DWORD color, const Point<float>& point1, const Point<float>& point2, const Point<float>& point3)const;
		void DrawRect(DWORD color, const Rect& rect, float roundR = 0.0f)const;
		void DrawFullRect(DWORD color, const Rect& rect, float roundR = 0.0f)const;
		void DrawCircle(DWORD color, const Point<float>& mid, float radius)const;
		void DrawFullCircle(DWORD color, const Point<float>& mid, float radius)const;
		void DrawPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate)const;
		void DrawFullPolygon(DWORD color, size_t edgeNum, const Point<float>& mid, float radius, float rotate)const;
		void DrawPolygon(DWORD color, const Point<float>* point, size_t edgeNum)const;
		void DrawFullPolygon(DWORD color, const Point<float>* point, size_t edgeNum)const;
		void DrawPolygon(DWORD color, initializer_list<Point<float> > point)const;
		void DrawFullPolygon(DWORD color, initializer_list<Point<float> > point)const;


		virtual void MouseDown(int x, int y, Cvp::MouseCode key) {}
		virtual void MouseUp(int x, int y, Cvp::MouseCode key) {}
		virtual void MouseEnter() {}
		virtual void MouseLeave() {}
		virtual void MouseWheel(int delta) {}
		virtual void MouseMove(int x, int y) {}
		virtual void MouseDrag(int x, int y) {}
		virtual void KeyDown(Cvp::KeyCode key) {}
		virtual void KeyUp(Cvp::KeyCode key) {}
		virtual void KeyChar(char key) {}
		virtual void GotFocus() {}
		virtual void LostFocus() {}
		virtual void Update() {}
		virtual void Draw() { DrawFullRect(GlobalStyle().BaseColor, { 0,0,GetW(), GetH() }); DrawRect(GlobalStyle().LineColor, { 0,0,GetW(), GetH() }); }
		virtual void DrawOver() {}
		virtual void Clean() {}
	};
	class Invisible final :public Widget {
	public:
		Invisible(Widget* child) : Widget({ child->GetX(), child->GetY(), child->GetW(), child->GetH(), }, { child }) { child->MoveTo(0, 0); }
		void Draw()override final {}
	};
#ifndef CVP
	inline const SharedImage& __KeyTag(KeyCode key) {
		static SharedImage list[] = {
			GlobalFont().MakeImage(u8"nil"),//0x00u
			GlobalFont().MakeImage(u8"mouse1"),//0x01u
			GlobalFont().MakeImage(u8"mouse2"),//0x02u
			GlobalFont().MakeImage(u8"ctrlbreak"),//0x03u
			GlobalFont().MakeImage(u8"mouse3"),//0x04u
			SharedImage(),//0x05u
			SharedImage(),//0x06u
			SharedImage(),//0x07u
			GlobalFont().MakeImage(u8"backspace"),//0x08u
			GlobalFont().MakeImage(u8"tab"),//0x09u
			SharedImage(),//0x0Au
			SharedImage(),//0x0Bu
			GlobalFont().MakeImage(u8"clear"),//0x0Cu
			GlobalFont().MakeImage(u8"return"),//0x0Du
			SharedImage(),//0x0Eu
			SharedImage(),//0x0Fu
			GlobalFont().MakeImage(u8"shift"),//0x10u
			GlobalFont().MakeImage(u8"ctrl"),//0x11u
			GlobalFont().MakeImage(u8"alt"),//0x12u
			GlobalFont().MakeImage(u8"pause"),//0x13u
			GlobalFont().MakeImage(u8"capital"),//0x14u
			GlobalFont().MakeImage(u8"hangeul"),//0x15u
			SharedImage(),//0x16u
			GlobalFont().MakeImage(u8"junja"),//0x17u
			GlobalFont().MakeImage(u8"final"),//0x18u
			GlobalFont().MakeImage(u8"hanja"),//0x19u
			SharedImage(),//0x1Au
			GlobalFont().MakeImage(u8"esc"),//0x1Bu
			GlobalFont().MakeImage(u8"convert"),//0x1Cu
			GlobalFont().MakeImage(u8"nonconvert"),//0x1Du
			GlobalFont().MakeImage(u8"accept"),//0x1Eu
			GlobalFont().MakeImage(u8"modechange"),//0x1Fu
			GlobalFont().MakeImage(u8"space"),//0x20u
			GlobalFont().MakeImage(u8"prior"),//0x21u
			GlobalFont().MakeImage(u8"next"),//0x22u
			GlobalFont().MakeImage(u8"end"),//0x23u
			GlobalFont().MakeImage(u8"home"),//0x24u
			GlobalFont().MakeImage(u8"left"),//0x25u
			GlobalFont().MakeImage(u8"up"),//0x26u
			GlobalFont().MakeImage(u8"right"),//0x27u
			GlobalFont().MakeImage(u8"down"),//0x28u
			GlobalFont().MakeImage(u8"select"),//0x29u
			GlobalFont().MakeImage(u8"print"),//0x2Au
			GlobalFont().MakeImage(u8"execute"),//0x2Bu
			GlobalFont().MakeImage(u8"snapshot"),//0x2Cu
			GlobalFont().MakeImage(u8"insert"),//0x2Du
			GlobalFont().MakeImage(u8"delete"),//0x2Eu
			GlobalFont().MakeImage(u8"help"),//0x2Fu
			GlobalFont().MakeImage(u8"0"),//0x30u
			GlobalFont().MakeImage(u8"1"),//0x31u
			GlobalFont().MakeImage(u8"2"),//0x32u
			GlobalFont().MakeImage(u8"3"),//0x33u
			GlobalFont().MakeImage(u8"4"),//0x34u
			GlobalFont().MakeImage(u8"5"),//0x35u
			GlobalFont().MakeImage(u8"6"),//0x36u
			GlobalFont().MakeImage(u8"7"),//0x37u
			GlobalFont().MakeImage(u8"8"),//0x38u
			GlobalFont().MakeImage(u8"9"),//0x39u
			SharedImage(),//0x3Au
			SharedImage(),//0x3Bu
			SharedImage(),//0x3Cu
			SharedImage(),//0x3Du
			SharedImage(),//0x3Eu
			SharedImage(),//0x3Fu
			SharedImage(),//0x40u
			GlobalFont().MakeImage(u8"A"),//0x41u
			GlobalFont().MakeImage(u8"B"),//0x42u
			GlobalFont().MakeImage(u8"C"),//0x43u
			GlobalFont().MakeImage(u8"D"),//0x44u
			GlobalFont().MakeImage(u8"E"),//0x45u
			GlobalFont().MakeImage(u8"F"),//0x46u
			GlobalFont().MakeImage(u8"G"),//0x47u
			GlobalFont().MakeImage(u8"H"),//0x48u
			GlobalFont().MakeImage(u8"I"),//0x49u
			GlobalFont().MakeImage(u8"J"),//0x4Au
			GlobalFont().MakeImage(u8"K"),//0x4Bu
			GlobalFont().MakeImage(u8"L"),//0x4Cu
			GlobalFont().MakeImage(u8"M"),//0x4Du
			GlobalFont().MakeImage(u8"N"),//0x4Eu
			GlobalFont().MakeImage(u8"O"),//0x4Fu
			GlobalFont().MakeImage(u8"P"),//0x50u
			GlobalFont().MakeImage(u8"Q"),//0x51u
			GlobalFont().MakeImage(u8"R"),//0x52u
			GlobalFont().MakeImage(u8"S"),//0x53u
			GlobalFont().MakeImage(u8"T"),//0x54u
			GlobalFont().MakeImage(u8"U"),//0x55u
			GlobalFont().MakeImage(u8"V"),//0x56u
			GlobalFont().MakeImage(u8"W"),//0x57u
			GlobalFont().MakeImage(u8"X"),//0x58u
			GlobalFont().MakeImage(u8"Y"),//0x59u
			GlobalFont().MakeImage(u8"Z"),//0x5Au
			GlobalFont().MakeImage(u8"Lwin"),//0x5Bu
			GlobalFont().MakeImage(u8"Rwin"),//0x5Cu
			GlobalFont().MakeImage(u8"apps"),//0x5Du
			SharedImage(),//0x5Eu
			GlobalFont().MakeImage(u8"sleep"),//0x5Fu
			GlobalFont().MakeImage(u8"numpad0"),//0x60u
			GlobalFont().MakeImage(u8"numpad1"),//0x61u
			GlobalFont().MakeImage(u8"numpad2"),//0x62u
			GlobalFont().MakeImage(u8"numpad3"),//0x63u
			GlobalFont().MakeImage(u8"numpad4"),//0x64u
			GlobalFont().MakeImage(u8"numpad5"),//0x65u
			GlobalFont().MakeImage(u8"numpad6"),//0x66u
			GlobalFont().MakeImage(u8"numpad7"),//0x67u
			GlobalFont().MakeImage(u8"numpad8"),//0x68u
			GlobalFont().MakeImage(u8"numpad9"),//0x69u
			GlobalFont().MakeImage(u8"multiply"),//0x6Au
			GlobalFont().MakeImage(u8"add"),//0x6Bu
			GlobalFont().MakeImage(u8"separator"),//0x6Cu
			GlobalFont().MakeImage(u8"subtract"),//0x6Du
			GlobalFont().MakeImage(u8"decimal"),//0x6Eu
			GlobalFont().MakeImage(u8"divide"),//0x6Fu
			GlobalFont().MakeImage(u8"F1"),//0x70u
			GlobalFont().MakeImage(u8"F2"),//0x71u
			GlobalFont().MakeImage(u8"F3"),//0x72u
			GlobalFont().MakeImage(u8"F4"),//0x73u
			GlobalFont().MakeImage(u8"F5"),//0x74u
			GlobalFont().MakeImage(u8"F6"),//0x75u
			GlobalFont().MakeImage(u8"F7"),//0x76u
			GlobalFont().MakeImage(u8"F8"),//0x77u
			GlobalFont().MakeImage(u8"F9"),//0x78u
			GlobalFont().MakeImage(u8"F10"),//0x79u
			GlobalFont().MakeImage(u8"F11"),//0x7Au
			GlobalFont().MakeImage(u8"F12"),//0x7Bu
			GlobalFont().MakeImage(u8"F13"),//0x7Cu
			GlobalFont().MakeImage(u8"F14"),//0x7Du
			GlobalFont().MakeImage(u8"F15"),//0x7Eu
			GlobalFont().MakeImage(u8"F16"),//0x7Fu
			GlobalFont().MakeImage(u8"F17"),//0x80u
			GlobalFont().MakeImage(u8"F18"),//0x81u
			GlobalFont().MakeImage(u8"F19"),//0x82u
			GlobalFont().MakeImage(u8"F20"),//0x83u
			GlobalFont().MakeImage(u8"F21"),//0x84u
			GlobalFont().MakeImage(u8"F22"),//0x85u
			GlobalFont().MakeImage(u8"F23"),//0x86u
			GlobalFont().MakeImage(u8"F24"),//0x87u
			SharedImage(),//0x88u
			SharedImage(),//0x89u
			SharedImage(),//0x8Au
			SharedImage(),//0x8Bu
			SharedImage(),//0x8Cu
			SharedImage(),//0x8Du
			SharedImage(),//0x8Eu
			SharedImage(),//0x8Fu
			GlobalFont().MakeImage(u8"numlock"),//0x90u
			GlobalFont().MakeImage(u8"scroll"),//0x91u
			SharedImage(),//0x92u
			SharedImage(),//0x93u
			SharedImage(),//0x94u
			SharedImage(),//0x95u
			SharedImage(),//0x96u
			SharedImage(),//0x97u
			SharedImage(),//0x98u
			SharedImage(),//0x99u
			SharedImage(),//0x9Au
			SharedImage(),//0x9Bu
			SharedImage(),//0x9Cu
			SharedImage(),//0x9Du
			SharedImage(),//0x9Eu
			SharedImage(),//0x9Fu
			SharedImage(),//0xA0u
			SharedImage(),//0xA1u
			SharedImage(),//0xA2u
			SharedImage(),//0xA3u
			SharedImage(),//0xA4u
			SharedImage(),//0xA5u
			SharedImage(),//0xA6u
			SharedImage(),//0xA7u
			SharedImage(),//0xA8u
			SharedImage(),//0xA9u
			SharedImage(),//0xAAu
			SharedImage(),//0xABu
			SharedImage(),//0xACu
			SharedImage(),//0xADu
			SharedImage(),//0xAEu
			SharedImage(),//0xAFu
			SharedImage(),//0xB0u
			SharedImage(),//0xB1u
			SharedImage(),//0xB2u
			SharedImage(),//0xB3u
			SharedImage(),//0xB4u
			SharedImage(),//0xB5u
			SharedImage(),//0xB6u
			SharedImage(),//0xB7u
			SharedImage(),//0xB8u
			SharedImage(),//0xB9u
			GlobalFont().MakeImage(u8";"),// 0xBAu,
			GlobalFont().MakeImage(u8"+"),// 0xBBu,
			GlobalFont().MakeImage(u8","),// 0xBCu,
			GlobalFont().MakeImage(u8"-"),//0xBDu,
			GlobalFont().MakeImage(u8"."),// 0xBEu,
			GlobalFont().MakeImage(u8"/"),// 0xBFu,
			GlobalFont().MakeImage(u8"~"),// 0xC0u,
			SharedImage(),//0xC1u
			SharedImage(),//0xC2u
			SharedImage(),//0xC3u
			SharedImage(),//0xC4u
			SharedImage(),//0xC5u
			SharedImage(),//0xC6u
			SharedImage(),//0xC7u
			SharedImage(),//0xC8u
			SharedImage(),//0xC9u
			SharedImage(),//0xCAu
			SharedImage(),//0xCBu
			SharedImage(),//0xCCu
			SharedImage(),//0xCDu
			SharedImage(),//0xCEu
			SharedImage(),//0xCFu
			SharedImage(),//0xD0u
			SharedImage(),//0xD1u
			SharedImage(),//0xD2u
			SharedImage(),//0xD3u
			SharedImage(),//0xD4u
			SharedImage(),//0xD5u
			SharedImage(),//0xD6u
			SharedImage(),//0xD7u
			SharedImage(),//0xD8u
			SharedImage(),//0xD9u
			SharedImage(),//0xDAu
			GlobalFont().MakeImage(u8"["),// 0xDBu,
			GlobalFont().MakeImage(u8"\\"),// 0xDCu,
			GlobalFont().MakeImage(u8"]"),// 0xDDu,
			GlobalFont().MakeImage(u8"'"),// 0xDEu,
			SharedImage(),//0xDFu
			SharedImage(),//0xE0u
			SharedImage(),//0xE1u
			SharedImage(),//0xE2u
			SharedImage(),//0xE3u
			SharedImage(),//0xE4u
			SharedImage(),//0xE5u
			SharedImage(),//0xE6u
			SharedImage(),//0xE7u
			SharedImage(),//0xE8u
			SharedImage(),//0xE9u
			SharedImage(),//0xEAu
			SharedImage(),//0xEBu
			SharedImage(),//0xECu
			SharedImage(),//0xEDu
			SharedImage(),//0xEEu
			SharedImage(),//0xEFu
			SharedImage(),//0xF0u
			SharedImage(),//0xF1u
			SharedImage(),//0xF2u
			SharedImage(),//0xF3u
			SharedImage(),//0xF4u
			SharedImage(),//0xF5u
			SharedImage(),//0xF6u
			SharedImage(),//0xF7u
			SharedImage(),//0xF8u
			SharedImage(),//0xF9u
			SharedImage(),//0xFAu
			SharedImage(),//0xFBu
			SharedImage(),//0xFCu
			SharedImage(),//0xFDu
			SharedImage()//0xFEu
		};
		return list[(int)key];
	}
	class TabWidget final :public Widget {
		static constexpr int __TitleHeight = 30;
		static constexpr int __TitleWeightMax = 112;
		static constexpr int __Gap = 16;
		static constexpr int __GapEnd = 23;
		vector<SharedImage> __titleList;
		size_t __nowIndex;
		size_t __shownIndex;
		int __mousex;
		int __mousey;
	public:
		TabWidget(initializer_list<pair<string_view, Widget*>> page);
		void AddPage(initializer_list<pair<string_view, Widget*>> page);
		void SetIndex(size_t index);
		void MovePos(int delta);

		void MouseDown(int x, int y, Cvp::MouseCode key) override final;
		void MouseLeave() override final;
		void MouseWheel(int delta) override final;
		void MouseMove(int x, int y)override final;
		void KeyDown(Cvp::KeyCode key) override final;
		void Draw() override final;
		void DrawOver() override final;
	};
	class CmdWidget final :public Widget {
		static constexpr int __LineHeight = 20;
		static constexpr size_t __LineMax = 5;
		string __buffer;
		vector<string> __log;
		size_t __logShownIndex;
		vector<string> __lineList;
		vector<string> __lineListFormat;
		vector<string> __lineListTab;
		size_t __shownIndex;
		size_t __selectIndex;
		bool __input;
	public:
		CmdWidget();
		void MovePos(int delta);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Title final :public Widget {
		static constexpr int __titleHeight = 30;
		SharedImage __image;
		SharedImage __icon;
	public:
		Title(string_view title, Widget* body, SharedImage icon = SharedImage());
		void MouseDown(int x, int y, Cvp::MouseCode key) override final;
		void MouseDrag(int x, int y) override final;
		void Draw() override final;
		void Clean() override final;
	};
	class Label final :public Widget {
		static constexpr int __Height = 24;
		SharedImage __image;
	public:
		Label(const Rect& rect, string_view label);
		void Draw()override final;
	};
	class StringOutput final :public Widget {
		static constexpr int __Height = 24;
		string& __buffer;
		const int __r;
	public:
		StringOutput(const Rect& rect, string& str);
		void Draw()override final;
	};
	class WstringOutput final :public Widget {
		static constexpr int __Height = 24;
		wstring& __buffer;
		const int __r;
	public:
		WstringOutput(const Rect& rect, wstring& str);
		void Draw()override final;
	};
	class KeySelector_Event final :public Widget {
		static constexpr int __Height = 24;
		static constexpr int __Width = 80;
		Cvp::KeyCode __key;
		SharedImage __image;
		const function<void(Cvp::KeyCode)> __func;
		DWORD __specialColor;
	public:
		KeySelector_Event(Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default = Cvp::KeyCode(KeyCode::NIL));
		void KeyDown(Cvp::KeyCode key)override final;
		void Draw()override final;
	};
	class StringInput_Event final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		const function<void(string_view)> __func;
	public:
		StringInput_Event(const Rect& rect, const function<void(string_view)>& func, string_view _default = u8"");
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class IntegerInput_Event final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		const function<void(int)> __func;
	public:
		IntegerInput_Event(const Rect& rect, const function<void(int)>& func, int _default = 0);
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class FloatInput_Event final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		const function<void(float)> __func;
	public:
		FloatInput_Event(const Rect& rect, const function<void(float)>& func, float _default = 0.0f);
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Slider_Event_H final :public Widget {
		const int __default;
		const float __defaultval;
		const int __gap;
		const float __Min;
		const float __Max;
		int __pos;
		bool __holding;
		const function<void(float)> __func;
	public:
		Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		Slider_Event_H(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		void MovePos(int delta);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseUp(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void MouseMove(int x, int y)override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Slider_Event_V final :public Widget {
		const int __default;
		const float __defaultval;
		const int __gap;
		const float __Min;
		const float __Max;
		int __pos;
		bool __holding;
		const function<void(float)> __func;
	public:
		Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		Slider_Event_V(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		void MovePos(int delta);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseUp(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void MouseMove(int x, int y)override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Check_Event final :public Widget {
		static constexpr int __Height = 24;
		static constexpr int __Height1 = 14;
		static constexpr int __Height2 = 8;
		SharedImage __label;
		bool __buffer;
		const function<void(bool)> __func;
	public:
		Check_Event(const Rect& rect, const function<void(bool)>& func, string_view label, bool _default = false);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void Draw()override final;
	};
	class Radio_Event_Centralized final :public Widget {
		class RadioButton final :public Widget {
			friend class Radio_Event_Centralized;
			static constexpr int __Height = 24;
			static constexpr int __Height1 = 14;
			static constexpr int __Height2 = 10;
			SharedImage __label;
			bool __buffer;
		public:
			RadioButton(const Rect& rect, string_view label);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void Draw()override final;
		};
		static constexpr int __TitleHeight = 33;
		SharedImage __label;
		RadioButton* __buffer;
		const function<void(int)> __func;
	public:
		Radio_Event_Centralized(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default = 0, string_view label = u8"");
		void Select(RadioButton* child);
		void Select(int child);
		void Draw()override final;
	};
	class Radio_Event_Distributed final :public Widget {
		class RadioButton final :public Widget {
			friend class Radio_Event_Distributed;
			static constexpr int __Height = 24;
			static constexpr int __Height1 = 14;
			static constexpr int __Height2 = 8;
			SharedImage __label;
			bool __buffer;
			const function<void(bool)> __func;
		public:
			RadioButton(const Rect& rect, const function<void(bool)>& func, string_view label);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void Draw()override final;
		};
		static constexpr int __TitleHeight = 33;
		SharedImage __label;
		RadioButton* __buffer;
	public:
		Radio_Event_Distributed(const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default = 0, string_view label = u8"");
		void Select(RadioButton* child);
		void Select(int child);
		void Draw()override final;
	};
	class ComboList_Event_Centralized final :public Widget {
		class ListWidget final :public Widget {
			ComboList_Event_Centralized* __base;
		public:
			ListWidget(const Rect& rect, ComboList_Event_Centralized* base);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void MouseWheel(int delta) override final;
			void KeyDown(Cvp::KeyCode key)override final;
			void LostFocus()override final;
			void Draw()override final;
			void Clean()override final;
		};
		static constexpr int __Height = 24;
		static constexpr int __LineHeight = 20;
		static constexpr int __Gap = 16;
		vector<SharedImage> __buffer;
		int __val;
		ListWidget* __list;
		const function<void(int)> __func;
	public:
		ComboList_Event_Centralized(const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default = 0);
		void Turn(int val);
		void Select(int val);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
		void Clean()override final;
	};
	class ComboList_Event_Distributed final :public Widget {
		class ListWidget final :public Widget {
			ComboList_Event_Distributed* __base;
		public:
			ListWidget(const Rect& rect, ComboList_Event_Distributed* base);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void MouseWheel(int delta) override final;
			void KeyDown(Cvp::KeyCode key)override final;
			void LostFocus()override final;
			void Draw()override final;
			void Clean()override final;
		};
		static constexpr int __Height = 24;
		static constexpr int __LineHeight = 20;
		static constexpr int __Gap = 16;
		vector<SharedImage> __buffer;
		int __val;
		int __prevVal;
		ListWidget* __list;
		vector <function<void(bool)>> __func;
	public:
		ComboList_Event_Distributed(const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default = 0);
		void Turn(int val);
		void Select(int val);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
		void Clean()override final;
	};
	class Button final :public Widget {
		static constexpr int __Height = 24;
		SharedImage __label;
		Point<int> __mouse;
		const function<void(void)> __func;
	public:
		Button(const Rect& rect, const function<void(void)>& func, string_view label = u8"");
		void MouseMove(int x, int y)override final;
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void Draw()override final;
	};
	class KeySelector_Link final :public Widget {
		static constexpr int __Height = 24;
		static constexpr int __Width = 80;
		Cvp::KeyCode& __link;
		SharedImage __image;
		DWORD __specialColor;
	public:
		KeySelector_Link(Point<int> pos, Cvp::KeyCode& link);
		void KeyDown(Cvp::KeyCode key)override final;
		void Draw()override final;
	};
	class StringInput_Link final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		string& __link;
	public:
		StringInput_Link(const Rect& rect, string& link);
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class IntegerInput_Link final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		int& __link;
	public:
		IntegerInput_Link(const Rect& rect, int& link);
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class FloatInput_Link final :public Widget {
		static constexpr int __Height = 24;
		string __buffer;
		float& __link;
	public:
		FloatInput_Link(const Rect& rect, float& link);
		void KeyDown(Cvp::KeyCode key)override final;
		void KeyChar(char key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Slider_Link_H final :public Widget {
		const int __default;
		const float __defaultval;
		const int __gap;
		const float __Min;
		const float __Max;
		int __pos;
		bool __holding;
		float& __link;
	public:
		Slider_Link_H(const Rect& rect, float& link, int gap, float Min, float Max);
		Slider_Link_H(const Rect& rect, float& link, int gap, float Max);
		void MovePos(int delta);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseUp(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void MouseMove(int x, int y)override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Slider_Link_V final :public Widget {
		const int __default;
		const float __defaultval;
		const int __gap;
		const float __Min;
		const float __Max;
		int __pos;
		bool __holding;
		float& __link;
	public:
		Slider_Link_V(const Rect& rect, float& link, int gap, float Min, float Max);
		Slider_Link_V(const Rect& rect, float& link, int gap, float Max);
		void MovePos(int delta);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseUp(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void MouseMove(int x, int y)override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
	};
	class Check_Link final :public Widget {
		static constexpr int __Height = 24;
		static constexpr int __Height1 = 14;
		static constexpr int __Height2 = 8;
		SharedImage __label;
		bool& __link;
	public:
		Check_Link(const Rect& rect, bool& link, string_view label);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void Draw()override final;
	};
	class Radio_Link_Centralized final :public Widget {
		class RadioButton final :public Widget {
			friend class Radio_Link_Centralized;
			static constexpr int __Height = 24;
			static constexpr int __Height1 = 14;
			static constexpr int __Height2 = 8;
			SharedImage __label;
			bool __buffer;
		public:
			RadioButton(const Rect& rect, string_view label);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void Draw()override final;
		};
		static constexpr int __TitleHeight = 33;
		SharedImage __label;
		RadioButton* __buffer;
		int& __link;
	public:
		Radio_Link_Centralized(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default = 0, string_view label = u8"");
		void Select(RadioButton* child);
		void Select(int child);
		void Draw()override final;
	};
	class Radio_Link_Distributed final :public Widget {
		class RadioButton final :public Widget {
			friend class Radio_Link_Distributed;
			static constexpr int __Height = 24;
			static constexpr int __Height1 = 14;
			static constexpr int __Height2 = 8;
			SharedImage __label;
			bool& __link;
		public:
			RadioButton(const Rect& rect, bool& link, string_view label);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void Draw()override final;
		};
		static constexpr int __TitleHeight = 33;
		SharedImage __label;
		RadioButton* __buffer;
	public:
		Radio_Link_Distributed(const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default = 0, string_view label = u8"");
		void Select(RadioButton* child);
		void Select(int child);
		void Draw()override final;
	};
	class ComboList_Link_Centralized final :public Widget {
		class ListWidget final :public Widget {
			ComboList_Link_Centralized* __base;
		public:
			ListWidget(const Rect& rect, ComboList_Link_Centralized* base);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void MouseWheel(int delta) override final;
			void KeyDown(Cvp::KeyCode key)override final;
			void LostFocus()override final;
			void Draw()override final;
			void Clean()override final;
		};
		static constexpr int __Height = 24;
		static constexpr int __LineHeight = 20;
		static constexpr int __Gap = 16;
		vector<SharedImage> __buffer;
		int __val;
		ListWidget* __list;
		int& __link;
	public:
		ComboList_Link_Centralized(const Rect& rect, initializer_list<string_view> elements, int& link, int _default = 0);
		void Turn(int val);
		void Select(int val);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
		void Clean()override final;
	};
	class ComboList_Link_Distributed final :public Widget {
		class ListWidget final :public Widget {
			ComboList_Link_Distributed* __base;
		public:
			ListWidget(const Rect& rect, ComboList_Link_Distributed* base);
			void MouseDown(int x, int y, Cvp::MouseCode key)override final;
			void MouseWheel(int delta) override final;
			void KeyDown(Cvp::KeyCode key)override final;
			void LostFocus()override final;
			void Draw()override final;
			void Clean()override final;
		};
		static constexpr int __Height = 24;
		static constexpr int __LineHeight = 20;
		static constexpr int __Gap = 16;
		vector<SharedImage> __buffer;
		int __val;
		int __prevVal;
		ListWidget* __list;
		vector<bool*> __link;
	public:
		ComboList_Link_Distributed(const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default = 0);
		void Turn(int val);
		void Select(int val);
		void MouseDown(int x, int y, Cvp::MouseCode key)override final;
		void MouseWheel(int delta) override final;
		void KeyDown(Cvp::KeyCode key)override final;
		void LostFocus()override final;
		void Draw()override final;
		void Clean()override final;
	};
	class WidgetManager {
		static list<Widget*> __widgets;
		static TabWidget* __tabWidget;
		static CmdWidget* __cmdWidget;
		static Widget* __over;
		static Widget* __down;
		static Widget* __focus;
		static int __mouseX;
		static int __mouseY;
		static bool __mouse[4];//right/left/mid/reserve
		static bool __shift;
		static bool __ctrl;
		static bool __alt;
		static const Cvp::MouseCode __mousecode[3];
		static void __setover(Widget* widget);
		static void __setdown(Widget* widget);
		static void __setfocus(Widget* widget);
		static void __regulate();
		static Widget* __getWidget(int x, int y);
		static void __reMouse(int x, int y);
		static void __clean(Widget* widget);
		static void __update(Widget* widget);
		static void __draw(Widget* widget);
	public:
		static inline Widget* MakeWidget(const Rect& rect, initializer_list<Widget*> children = {});
		static inline Widget* MakeTabPage(initializer_list<Widget*> children = {});
		static inline Widget* MakeTitle(string_view title, Widget* body, SharedImage icon = SharedImage());
		static inline Widget* MakeLabel(const Rect& rect, string_view label);
		static inline Widget* MakeOutput(const Rect& rect, string& str);
		static inline Widget* MakeOutput(const Rect& rect, wstring& str);
		static inline Widget* MakeKeySelector(Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default = Cvp::KeyCode(KeyCode::NIL));
		static inline Widget* MakeInput(const Rect& rect, const function<void(string_view)>& func, string_view _default = u8"");
		static inline Widget* MakeInput(const Rect& rect, const function<void(int)>& func, int _default = 0);
		static inline Widget* MakeInput(const Rect& rect, const function<void(float)>& func, float _default = 0.0f);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		static inline Widget* MakeCheck(const Rect& rect, const function<void(bool)>& func, string_view label, bool _default = false);
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default = 0, string_view label = u8"");
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default = 0, string_view label = u8"");
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default = 0);
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default = 0);
		static inline Widget* MakeButton(const Rect& rect, const function<void(void)>& func, string_view label = u8"");
		static inline Widget* MakeKeySelector(Point<int> pos, Cvp::KeyCode& link);
		static inline Widget* MakeInput(const Rect& rect, string& link);
		static inline Widget* MakeInput(const Rect& rect, int& link);
		static inline Widget* MakeInput(const Rect& rect, float& link);
		static inline Widget* MakeSlider_H(const Rect& rect, float& link, int gap, float Min, float Max);
		static inline Widget* MakeSlider_H(const Rect& rect, float& link, int gap, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, float& link, int gap, float Min, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, float& link, int gap, float Max);
		static inline Widget* MakeCheck(const Rect& rect, bool& link, string_view label);
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default = 0, string_view label = u8"");
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default = 0, string_view label = u8"");
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<string_view> elements, int& link, int _default = 0);
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default = 0);

		static bool MouseWheel(int delta);
		static bool KeyDown(KeyCode key);
		static bool KeyUp(KeyCode key);
		static bool KeyChar(char key);
		static void Update();
		static void Draw();
		static bool MouseDown(int x, int y, int key);
		static bool MouseUp(int x, int y, int key);
		static bool MouseMove(int x, int y);

		static void AddWidget(Widget* widget);
		static void FocusWidget(Widget* widget);
		static void ReleaseWidget(Widget* widget);
		static void SetTab(initializer_list<pair<string_view, Widget*>> page);
		static void SetCmd(initializer_list <Cvp::UPCommand> cmd);
		static bool Shift();
		static bool Ctrl();
		static bool Alt();
	};
#endif
	class CustomControlBase :public Widget {
		function<void(void* _this, int x, int y, Cvp::MouseCode key)> __MouseDown;
		function<void(void* _this, int x, int y, Cvp::MouseCode key)> __MouseUp;
		function<void(void* _this)> __MouseEnter;
		function<void(void* _this)> __MouseLeave;
		function<void(void* _this, int delta)> __MouseWheel;
		function<void(void* _this, int x, int y)> __MouseMove;
		function<void(void* _this, int x, int y)> __MouseDrag;
		function<void(void* _this, Cvp::KeyCode key)> __KeyDown;
		function<void(void* _this, Cvp::KeyCode key)> __KeyUp;
		function<void(void* _this, char key)> __KeyChar;
		function<void(void* _this)> __GotFocus;
		function<void(void* _this)> __LostFocus;
		function<void(void* _this)> __Update;
		function<void(void* _this)> __Draw;
		function<void(void* _this)> __DrawOver;
		function<void(void* _this)> __Clean;
	protected:
		CustomControlBase(const Rect& rect) :
			Widget(rect),
			__MouseDown([](void* _this, int, int, Cvp::MouseCode){}),
			__MouseUp([](void* _this, int, int, Cvp::MouseCode){}),
			__MouseEnter([](void* _this){}),
			__MouseLeave([](void* _this){}),
			__MouseWheel([](void* _this, int){}),
			__MouseMove([](void* _this, int, int){}),
			__MouseDrag([](void* _this, int, int){}),
			__KeyDown([](void* _this, Cvp::KeyCode){}),
			__KeyUp([](void* _this, Cvp::KeyCode){}),
			__KeyChar([](void* _this, char){}),
			__GotFocus([](void* _this){}),
			__LostFocus([](void* _this){}),
			__Update([](void* _this){}),
			__Draw([](void* _this){}),
			__DrawOver([](void* _this){}),
			__Clean([](void* _this){}) {
		}
		void SetMouseDown(function<void(void* _this, int x, int y, Cvp::MouseCode key)> func) { __MouseDown = func; }
		void SetMouseUp(function<void(void* _this, int x, int y, Cvp::MouseCode key)> func) { __MouseUp = func; }
		void SetMouseEnter(function<void(void* _this)> func) { __MouseEnter = func; }
		void SetMouseLeave(function<void(void* _this)> func) { __MouseLeave = func; }
		void SetMouseWheel(function<void(void* _this, int delta)> func) { __MouseWheel = func; }
		void SetMouseMove(function<void(void* _this, int x, int y)> func) { __MouseMove = func; }
		void SetMouseDrag(function<void(void* _this, int x, int y)> func) { __MouseDrag = func; }
		void SetKeyDown(function<void(void* _this, Cvp::KeyCode key)> func) { __KeyDown = func; }
		void SetKeyUp(function<void(void* _this, Cvp::KeyCode key)> func) { __KeyUp = func; }
		void SetKeyChar(function<void(void* _this, char key)> func) { __KeyChar = func; }
		void SetGotFocus(function<void(void* _this)> func) { __GotFocus = func; }
		void SetLostFocus(function<void(void* _this)> func) { __LostFocus = func; }
		void SetUpdate(function<void(void* _this)> func) { __Update = func; }
		void SetDraw(function<void(void* _this)> func) { __Draw = func; }
		void SetDrawOver(function<void(void* _this)> func) { __DrawOver = func; }
		void SetClean(function<void(void* _this)> func) { __Clean = func; }
		void MouseDown(int x, int y, Cvp::MouseCode key)override final { __MouseDown(this + 1 + 1, x, y, key); }
		void MouseUp(int x, int y, Cvp::MouseCode key)override final { __MouseUp(this + 1, x, y, key); }
		void MouseEnter()override final { __MouseEnter(this + 1); }
		void MouseLeave() override final { __MouseLeave(this + 1); }
		void MouseWheel(int delta) override final { __MouseWheel(this + 1, delta); }
		void MouseMove(int x, int y)override final { __MouseMove(this + 1, x, y); }
		void MouseDrag(int x, int y)override final { __MouseDrag(this + 1, x, y); }
		void KeyDown(Cvp::KeyCode key)override final { __KeyDown(this + 1, key); }
		void KeyUp(Cvp::KeyCode key)override final { __KeyUp(this + 1, key); }
		void KeyChar(char key)override final { __KeyChar(this + 1, key); }
		void GotFocus()override final { __GotFocus(this + 1); }
		void LostFocus()override final { __LostFocus(this + 1); }
		void Update()override final { __Update(this + 1); }
		void Draw()override final { __Draw(this + 1); }
		void DrawOver()override final { __DrawOver(this + 1); }
		void Clean()override final { __Clean(this + 1); }
	};
	template<typename DataStruct>
	class CustomControl final :public CustomControlBase {
		DataStruct __data;
		template<typename ...Args>
		CustomControl(const Rect& rect, Args&&... args) :CustomControlBase(rect), __data(forward<Args>(args)...) {}
		void SetMouseDown(function<void(DataStruct* _this, int x, int y, Cvp::MouseCode key)> func) { CustomControlBase::SetMouseDown((function<void(void* _this, int x, int y, Cvp::MouseCode key)>)func); }
		void SetMouseUp(function<void(DataStruct* _this, int x, int y, Cvp::MouseCode key)> func) { CustomControlBase::SetMouseUp((function<void(void* _this, int x, int y, Cvp::MouseCode key)>)func); }
		void SetMouseEnter(function<void(DataStruct* _this)> func) { CustomControlBase::SetMouseEnter((function<void(void* _this)>)func); }
		void SetMouseLeave(function<void(DataStruct* _this)> func) { CustomControlBase::SetMouseLeave((function<void(void* _this)>)func); }
		void SetMouseWheel(function<void(DataStruct* _this, int delta)> func) { CustomControlBase::SetMouseWheel((function<void(void* _this, int delta)>)func); }
		void SetMouseMove(function<void(DataStruct* _this, int x, int y)> func) { CustomControlBase::SetMouseMove((function<void(void* _this, int x, int y)>)func); }
		void SetMouseDrag(function<void(DataStruct* _this, int x, int y)> func) { CustomControlBase::SetMouseDrag((function<void(void* _this, int x, int y)>)func); }
		void SetKeyDown(function<void(DataStruct* _this, KeyCode key)> func) { CustomControlBase::SetKeyDown((function<void(void* _this, KeyCode key)>)func); }
		void SetKeyUp(function<void(DataStruct* _this, KeyCode key)> func) { CustomControlBase::SetKeyUp((function<void(void* _this, KeyCode key)>)func); }
		void SetKeyChar(function<void(DataStruct* _this, char key)> func) { CustomControlBase::SetKeyChar((function<void(void* _this, char key)>)func); }
		void SetGotFocus(function<void(DataStruct* _this)> func) { CustomControlBase::SetGotFocus((function<void(void* _this)>)func); }
		void SetLostFocus(function<void(DataStruct* _this)> func) { CustomControlBase::SetLostFocus((function<void(void* _this)>)func); }
		void SetUpdate(function<void(DataStruct* _this)> func) { CustomControlBase::SetUpdate((function<void(void* _this)>)func); }
		void SetDraw(function<void(DataStruct* _this)> func) { CustomControlBase::SetDraw((function<void(void* _this)>)func); }
		void SetDrawOver(function<void(DataStruct* _this)> func) { CustomControlBase::SetDrawOver((function<void(void* _this)>)func); }
		void SetClean(function<void(DataStruct* _this)> func) { CustomControlBase::SetClean((function<void(void* _this)>)func); }
	};
	template<>
	class CustomControl<void> final :public CustomControlBase {
		CustomControl(const Rect& rect) :CustomControlBase(rect) {}
		void SetMouseDown(function<void(void* _this, int x, int y, Cvp::MouseCode key)> func) { CustomControlBase::SetMouseDown(func); }
		void SetMouseUp(function<void(void* _this, int x, int y, Cvp::MouseCode key)> func) { CustomControlBase::SetMouseUp(func); }
		void SetMouseEnter(function<void(void* _this)> func) { CustomControlBase::SetMouseEnter(func); }
		void SetMouseLeave(function<void(void* _this)> func) { CustomControlBase::SetMouseLeave(func); }
		void SetMouseWheel(function<void(void* _this, int delta)> func) { CustomControlBase::SetMouseWheel(func); }
		void SetMouseMove(function<void(void* _this, int x, int y)> func) { CustomControlBase::SetMouseMove(func); }
		void SetMouseDrag(function<void(void* _this, int x, int y)> func) { CustomControlBase::SetMouseDrag(func); }
		void SetKeyDown(function<void(void* _this, Cvp::KeyCode key)> func) { CustomControlBase::SetKeyDown(func); }
		void SetKeyUp(function<void(void* _this, Cvp::KeyCode key)> func) { CustomControlBase::SetKeyUp(func); }
		void SetKeyChar(function<void(void* _this, char key)> func) { CustomControlBase::SetKeyChar(func); }
		void SetGotFocus(function<void(void* _this)> func) { CustomControlBase::SetGotFocus(func); }
		void SetLostFocus(function<void(void* _this)> func) { CustomControlBase::SetLostFocus(func); }
		void SetUpdate(function<void(void* _this)> func) { CustomControlBase::SetUpdate(func); }
		void SetDraw(function<void(void* _this)> func) { CustomControlBase::SetDraw(func); }
		void SetDrawOver(function<void(void* _this)> func) { CustomControlBase::SetDrawOver(func); }
		void SetClean(function<void(void* _this)> func) { CustomControlBase::SetClean(func); }
	};


	template<typename...Args>Cvp::UPCommand MakeCmd(Args...args) { return Cvp::UPCommand(forward<Args>(args)...); }



	inline Rect MakeRect_Button(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8 + 16, 24); }
	inline Rect MakeRect_Label(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8, 24); }
	inline Rect MakeRect_Output(int col, int row, int strlen, int linenum) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8 + 24, linenum * 33 - 9); }
	inline Rect MakeRect_Input(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8 + 16, 24); }
	inline Rect MakeRect_Slider_H(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 23, strlen * 8, 16); }
	inline Rect MakeRect_Slider_V(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, 16, strlen * 33); }
	inline Rect MakeRect_Check(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8 + 24, 24); }
	inline Rect MakeRect_RadioBox(int col, int row, int strlen, int linenum) { return Rect(col * 8 + 16, row * 33 + 15, strlen * 8 + 16, linenum * 33 - 1); }
	inline Rect MakeRect_Radio(int col, int row, int strlen) { return Rect(col * 8 + 6, row * 33 + 0, strlen * 8 + 24, 24); }
	inline Rect MakeRect_Combo(int col, int row, int strlen) { return Rect(col * 8 + 16, row * 33 + 19, strlen * 8 + 32, 24); }
	inline Point<int> MakePos(int col, int row) { return Point<int>(col * 8 + 16, row * 33 + 19); }


	CVP_FUNC(void, __WidgetManager_AddWidget, (Widget* widget), (widget), { WidgetManager::AddWidget(widget); });
	CVP_FUNC(void, __WidgetManager_FocusWidget, (Widget* widget), (widget), { WidgetManager::FocusWidget(widget); });
	CVP_FUNC(void, __WidgetManager_ReleaseWidget, (Widget* widget), (widget), { WidgetManager::ReleaseWidget(widget); });
	CVP_FUNC(void, __WidgetManager_SetTab, (initializer_list<pair<string_view, Widget*>> page), (page), { WidgetManager::SetTab(page); });
	CVP_FUNC(void, __WidgetManager_SetCmd, (initializer_list <Cvp::UPCommand> cmd), (cmd), { WidgetManager::SetCmd(cmd); });
	CVP_FUNC(bool, __WidgetManager_Shift, (), (), { return WidgetManager::Shift(); });
	CVP_FUNC(bool, __WidgetManager_Ctrl, (), (), { return WidgetManager::Ctrl(); });
	CVP_FUNC(bool, __WidgetManager_Alt, (), (), { return WidgetManager::Alt(); });


#ifdef CVP
	class Title :public Widget {};
	class Label :public Widget {};
	class StringOutput :public Widget {};
	class WstringOutput :public Widget {};
	class KeySelector_Event :public Widget {};
	class StringInput_Event :public Widget {};
	class IntegerInput_Event :public Widget {};
	class FloatInput_Event :public Widget {};
	class Slider_Event_H :public Widget {};
	class Slider_Event_V :public Widget {};
	class Check_Event :public Widget {};
	class Radio_Event_Centralized :public Widget {};
	class Radio_Event_Distributed :public Widget {};
	class ComboList_Event_Centralized :public Widget {};
	class ComboList_Event_Distributed :public Widget {};
	class Button :public Widget {};
	class KeySelector_Link :public Widget {};
	class StringInput_Link :public Widget {};
	class IntegerInput_Link :public Widget {};
	class FloatInput_Link :public Widget {};
	class Slider_Link_H :public Widget {};
	class Slider_Link_V :public Widget {};
	class Check_Link :public Widget {};
	class Radio_Link_Centralized :public Widget {};
	class Radio_Link_Distributed :public Widget {};
	class ComboList_Link_Centralized :public Widget {};
	class ComboList_Link_Distributed :public Widget {};
#endif
	CVP_FUNC(Widget*, __Make__Widget, (const Rect& rect, initializer_list<Widget*> children), (rect, children), { return new Widget(rect, children); });
	CVP_FUNC(Title*, __Make__Title, (string_view title, Widget* body, SharedImage icon), (title, body, icon), { return new Title(title, body, icon); });
	CVP_FUNC(Label*, __Make__Label, (const Rect& rect, string_view label), (rect, label), { return new Label(rect, label); });
	CVP_FUNC(StringOutput*, __Make__StringOutput, (const Rect& rect, string& str), (rect, str), { return new StringOutput(rect, str); });
	CVP_FUNC(WstringOutput*, __Make__WstringOutput, (const Rect& rect, wstring& str), (rect, str), { return new WstringOutput(rect, str); });
	CVP_FUNC(KeySelector_Event*, __Make__KeySelector_Event, (Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default), (pos, func, _default), { return new KeySelector_Event(pos, func, _default); });
	CVP_FUNC(StringInput_Event*, __Make__StringInput_Event, (const Rect& rect, const function<void(string_view)>& func, string_view _default), (rect, func, _default), { return new StringInput_Event(rect, func, _default); });
	CVP_FUNC(IntegerInput_Event*, __Make__IntegerInput_Event, (const Rect& rect, const function<void(int)>& func, int _default), (rect, func, _default), { return new IntegerInput_Event(rect, func, _default); });
	CVP_FUNC(FloatInput_Event*, __Make__FloatInput_Event, (const Rect& rect, const function<void(float)>& func, float _default), (rect, func, _default), { return new FloatInput_Event(rect, func, _default); });
	CVP_FUNC(Slider_Event_H*, __Make__Slider_Event_H, (const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default), (rect, func, gap, Min, Max, _default), { return new Slider_Event_H(rect, func, gap, Min, Max, _default); });
	CVP_FUNC(Slider_Event_H*, __Make__Slider_Event_H_, (const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max), (rect, func, gap, Min, Max), { return new Slider_Event_H(rect, func, gap, Min, Max); });
	CVP_FUNC(Slider_Event_H*, __Make__Slider_Event_H__, (const Rect& rect, const function<void(float)>& func, int gap, float Max), (rect, func, gap, Max), { return new Slider_Event_H(rect, func, gap, Max); });
	CVP_FUNC(Slider_Event_V*, __Make__Slider_Event_V, (const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default), (rect, func, gap, Min, Max, _default), { return new Slider_Event_V(rect, func, gap, Min, Max, _default); });
	CVP_FUNC(Slider_Event_V*, __Make__Slider_Event_V_, (const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max), (rect, func, gap, Min, Max), { return new Slider_Event_V(rect, func, gap, Min, Max); });
	CVP_FUNC(Slider_Event_V*, __Make__Slider_Event_V__, (const Rect& rect, const function<void(float)>& func, int gap, float Max), (rect, func, gap, Max), { return new Slider_Event_V(rect, func, gap, Max); });
	CVP_FUNC(Check_Event*, __Make__Check_Event, (const Rect& rect, const function<void(bool)>& func, string_view label, bool _default), (rect, func, label, _default), { return new Check_Event(rect, func, label, _default); });
	CVP_FUNC(Radio_Event_Centralized*, __Make__Radio_Event_Centralized, (const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default, string_view label), (rect, children, func, _default, label), { return new Radio_Event_Centralized(rect, children,func, _default , label); });
	CVP_FUNC(Radio_Event_Distributed*, __Make__Radio_Event_Distributed, (const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default, string_view label), (rect, children, _default, label), { return new Radio_Event_Distributed(rect, children, _default , label); });
	CVP_FUNC(ComboList_Event_Centralized*, __Make__ComboList_Event_Centralized, (const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default), (rect, elements, func, _default), { return new ComboList_Event_Centralized(rect, elements, func, _default); });
	CVP_FUNC(ComboList_Event_Distributed*, __Make__ComboList_Event_Distributed, (const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default), (rect, elements, _default), { return new ComboList_Event_Distributed(rect, elements, _default); });
	CVP_FUNC(Button*, __Make__Button, (const Rect& rect, const function<void(void)>& func, string_view label), (rect, func, label), { return new Button(rect, func, label); });
	CVP_FUNC(KeySelector_Link*, __Make__KeySelector_Link, (Point<int> pos, Cvp::KeyCode& link), (pos, link), { return new KeySelector_Link(pos, link); });
	CVP_FUNC(StringInput_Link*, __Make__StringInput_Link, (const Rect& rect, string& link), (rect, link), { return new StringInput_Link(rect, link); });
	CVP_FUNC(IntegerInput_Link*, __Make__IntegerInput_Link, (const Rect& rect, int& link), (rect, link), { return new IntegerInput_Link(rect, link); });
	CVP_FUNC(FloatInput_Link*, __Make__FloatInput_Link, (const Rect& rect, float& link), (rect, link), { return new FloatInput_Link(rect, link); });
	CVP_FUNC(Slider_Link_H*, __Make__Slider_Link_H, (const Rect& rect, float& link, int gap, float Min, float Max), (rect, link, gap, Min, Max), { return new Slider_Link_H(rect, link, gap, Min, Max); });
	CVP_FUNC(Slider_Link_H*, __Make__Slider_Link_H_, (const Rect& rect, float& link, int gap, float Max), (rect, link, gap, Max), { return new Slider_Link_H(rect, link, gap, Max); });
	CVP_FUNC(Slider_Link_V*, __Make__Slider_Link_V, (const Rect& rect, float& link, int gap, float Min, float Max), (rect, link, gap, Min, Max), { return new Slider_Link_V(rect, link, gap, Min, Max); });
	CVP_FUNC(Slider_Link_V*, __Make__Slider_Link_V_, (const Rect& rect, float& link, int gap, float Max), (rect, link, gap, Max), { return new Slider_Link_V(rect, link, gap, Max); });
	CVP_FUNC(Check_Link*, __Make__Check_Link, (const Rect& rect, bool& link, string_view label), (rect, link, label), { return new Check_Link(rect, link, label); });
	CVP_FUNC(Radio_Link_Centralized*, __Make__Radio_Link_Centralized, (const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default, string_view label), (rect, children, link, _default, label), { return new Radio_Link_Centralized(rect, children, link, _default , label); });
	CVP_FUNC(Radio_Link_Distributed*, __Make__Radio_Link_Distributed, (const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default, string_view label), (rect, children, _default, label), { return new Radio_Link_Distributed(rect, children, _default , label); });
	CVP_FUNC(ComboList_Link_Centralized*, __Make__ComboList_Link_Centralized, (const Rect& rect, initializer_list<string_view> elements, int& link, int _default), (rect, elements, link, _default), { return new ComboList_Link_Centralized(rect,elements, link, _default); });
	CVP_FUNC(ComboList_Link_Distributed*, __Make__ComboList_Link_Distributed, (const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default), (rect, elements, _default), { return new ComboList_Link_Distributed(rect, elements, _default); });
#ifdef CVP
	class WidgetManager {
	public:
		static inline Widget* MakeWidget(const Rect& rect, initializer_list<Widget*> children = {});
		static inline Widget* MakeTabPage(initializer_list<Widget*> children = {});
		static inline Widget* MakeTitle(string_view title, Widget* body, SharedImage icon = SharedImage());
		static inline Widget* MakeLabel(const Rect& rect, string_view label);
		static inline Widget* MakeOutput(const Rect& rect, string& str);
		static inline Widget* MakeOutput(const Rect& rect, wstring& str);
		static inline Widget* MakeKeySelector(Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default = Cvp::KeyCode(KeyCode::NIL));
		static inline Widget* MakeInput(const Rect& rect, const function<void(string_view)>& func, string_view _default = u8"");
		static inline Widget* MakeInput(const Rect& rect, const function<void(int)>& func, int _default = 0);
		static inline Widget* MakeInput(const Rect& rect, const function<void(float)>& func, float _default = 0.0f);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		static inline Widget* MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Max);
		static inline Widget* MakeCheck(const Rect& rect, const function<void(bool)>& func, string_view label, bool _default = false);
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default = 0, string_view label = u8"");
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default = 0, string_view label = u8"");
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default = 0);
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default = 0);
		static inline Widget* MakeButton(const Rect& rect, const function<void(void)>& func, string_view label = u8"");
		static inline Widget* MakeKeySelector(Point<int> pos, Cvp::KeyCode& link);
		static inline Widget* MakeInput(const Rect& rect, string& link);
		static inline Widget* MakeInput(const Rect& rect, int& link);
		static inline Widget* MakeInput(const Rect& rect, float& link);
		static inline Widget* MakeSlider_H(const Rect& rect, float& link, int gap, float Min, float Max);
		static inline Widget* MakeSlider_H(const Rect& rect, float& link, int gap, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, float& link, int gap, float Min, float Max);
		static inline Widget* MakeSlider_V(const Rect& rect, float& link, int gap, float Max);
		static inline Widget* MakeCheck(const Rect& rect, bool& link, string_view label);
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default = 0, string_view label = u8"");
		static inline Widget* MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default = 0, string_view label = u8"");
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<string_view> elements, int& link, int _default = 0);
		static inline Widget* MakeComboList(const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default = 0);
		
		static void AddWidget(Widget* widget) { return __WidgetManager_AddWidget(widget); }
		static void FocusWidget(Widget* widget) { return __WidgetManager_FocusWidget(widget); }
		static void ReleaseWidget(Widget* widget) { return __WidgetManager_ReleaseWidget(widget); }
		static void SetTab(initializer_list<pair<string_view, Widget*>> page) { return __WidgetManager_SetTab(page); }
		static void SetCmd(initializer_list<Cvp::UPCommand> cmd) { return __WidgetManager_SetCmd(cmd); }
		static bool Shift() { return __WidgetManager_Shift(); }
		static bool Ctrl() { return __WidgetManager_Ctrl(); }
		static bool Alt() { return __WidgetManager_Alt(); }
	};
#endif
	inline Widget* WidgetManager::MakeWidget(const Rect& rect, initializer_list<Widget*> children) { return __Make__Widget(rect, children); }
	inline Widget* WidgetManager::MakeTabPage(initializer_list<Widget*> children) { return __Make__Widget({ 0,0,479,689 }, children); }
	inline Widget* WidgetManager::MakeTitle(string_view title, Widget* body, SharedImage icon) { return __Make__Title(title, body, icon); }
	inline Widget* WidgetManager::MakeLabel(const Rect& rect, string_view label) { return __Make__Label(rect, label); }
	inline Widget* WidgetManager::MakeOutput(const Rect& rect, string& str) { return __Make__StringOutput(rect, str); }
	inline Widget* WidgetManager::MakeOutput(const Rect& rect, wstring& str) { return __Make__WstringOutput(rect, str); }
	inline Widget* WidgetManager::MakeKeySelector(Point<int> pos, const function<void(Cvp::KeyCode)>& func, Cvp::KeyCode _default) { return __Make__KeySelector_Event(pos, func, _default); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, const function<void(string_view)>& func, string_view _default) { return __Make__StringInput_Event(rect, func, _default); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, const function<void(int)>& func, int _default) { return __Make__IntegerInput_Event(rect, func, _default); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, const function<void(float)>& func, float _default) { return __Make__FloatInput_Event(rect, func, _default); }
	inline Widget* WidgetManager::MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default) { return __Make__Slider_Event_H(rect, func, gap, Min, Max, _default); }
	inline Widget* WidgetManager::MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max) { return __Make__Slider_Event_H_(rect, func, gap, Min, Max); }
	inline Widget* WidgetManager::MakeSlider_H(const Rect& rect, const function<void(float)>& func, int gap, float Max) { return __Make__Slider_Event_H__(rect, func, gap, Max); }
	inline Widget* WidgetManager::MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max, float _default) { return __Make__Slider_Event_V(rect, func, gap, Min, Max, _default); }
	inline Widget* WidgetManager::MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Min, float Max) { return __Make__Slider_Event_V_(rect, func, gap, Min, Max); }
	inline Widget* WidgetManager::MakeSlider_V(const Rect& rect, const function<void(float)>& func, int gap, float Max) { return __Make__Slider_Event_V__(rect, func, gap, Max); }
	inline Widget* WidgetManager::MakeCheck(const Rect& rect, const function<void(bool)>& func, string_view label, bool _default) { return __Make__Check_Event(rect, func, label, _default); }
	inline Widget* WidgetManager::MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, const function<void(int)>& func, int _default, string_view label) { return __Make__Radio_Event_Centralized(rect, children, func, _default, label); }
	inline Widget* WidgetManager::MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, const function<void(bool)>, string_view>> children, int _default, string_view label) { return __Make__Radio_Event_Distributed(rect, children, _default, label); }
	inline Widget* WidgetManager::MakeComboList(const Rect& rect, initializer_list<string_view> elements, const function<void(int)>& func, int _default) { return __Make__ComboList_Event_Centralized(rect, elements, func, _default); }
	inline Widget* WidgetManager::MakeComboList(const Rect& rect, initializer_list<pair<string_view, const function<void(bool)>>> elements, int _default) { return __Make__ComboList_Event_Distributed(rect, elements, _default); }
	inline Widget* WidgetManager::MakeButton(const Rect& rect, const function<void(void)>& func, string_view label) { return __Make__Button(rect, func, label); }
	inline Widget* WidgetManager::MakeKeySelector(Point<int> pos, Cvp::KeyCode& link) { return __Make__KeySelector_Link(pos, link); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, string& link) { return __Make__StringInput_Link(rect, link); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, int& link) { return __Make__IntegerInput_Link(rect, link); }
	inline Widget* WidgetManager::MakeInput(const Rect& rect, float& link) { return __Make__FloatInput_Link(rect, link); }
	inline Widget* WidgetManager::MakeSlider_H(const Rect& rect, float& link, int gap, float Min, float Max) { return __Make__Slider_Link_H(rect, link, gap, Min, Max); }
	inline Widget* WidgetManager::MakeSlider_H(const Rect& rect, float& link, int gap, float Max) { return __Make__Slider_Link_H_(rect, link, gap, Max); }
	inline Widget* WidgetManager::MakeSlider_V(const Rect& rect, float& link, int gap, float Min, float Max) { return __Make__Slider_Link_V(rect, link, gap, Min, Max); }
	inline Widget* WidgetManager::MakeSlider_V(const Rect& rect, float& link, int gap, float Max) { return __Make__Slider_Link_V_(rect, link, gap, Max); }
	inline Widget* WidgetManager::MakeCheck(const Rect& rect, bool& link, string_view label) { return __Make__Check_Link(rect, link, label); }
	inline Widget* WidgetManager::MakeRadio(const Rect& rect, initializer_list<pair<const Rect, string_view>> children, int& link, int _default, string_view label) { return __Make__Radio_Link_Centralized(rect, children, link, _default, label); }
	inline Widget* WidgetManager::MakeRadio(const Rect& rect, initializer_list<tuple<const Rect, bool* const, string_view>> children, int _default, string_view label) { return __Make__Radio_Link_Distributed(rect, children, _default, label); }
	inline Widget* WidgetManager::MakeComboList(const Rect& rect, initializer_list<string_view> elements, int& link, int _default) { return __Make__ComboList_Link_Centralized(rect, elements, link, _default); }
	inline Widget* WidgetManager::MakeComboList(const Rect& rect, initializer_list<pair<string_view, bool*>> elements, int _default) { return __Make__ComboList_Link_Distributed(rect, elements, _default); }
};