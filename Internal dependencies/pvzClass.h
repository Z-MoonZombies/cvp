#pragma once
#include "cvp.h"
#include <d3d.h>

namespace Pvz {
	enum {
		CURSOR_POINTER,
		CURSOR_HAND,
		CURSOR_DRAGGING,
		CURSOR_TEXT,
		CURSOR_CIRCLE_SLASH,
		CURSOR_SIZEALL,
		CURSOR_SIZENESW,
		CURSOR_SIZENS,
		CURSOR_SIZENWSE,
		CURSOR_SIZEWE,
		CURSOR_WAIT,
		CURSOR_NONE,
		CURSOR_CUSTOM,
		NUM_CURSORS
	};
	enum class HitType :DWORD {
		NIL = 0,
		SIDE = 1,
		SPLASH = 2,
		SLOW = 4,
		NO_FLASH = 8,
		NO_LEAVEBODY = 16,
		SPIKE = 32
	};
	inline HitType operator|(HitType a, HitType b) { return(HitType)((int)a | (int)b); }
	inline HitType operator&(HitType a, HitType b) { return(HitType)((int)a & (int)b); }
	enum class HitRange :DWORD {
		NIL = 0,
		GROUND = 1,
		AIR = 2,
		SUBMERGE = 4,
		DOG = 8,
		OFF_GROUND = 16,
		DYING = 32,
		UNDERGROUND = 64,
		BETRAYED = 128
	};
	inline HitRange operator|(HitRange a, HitRange b) { return(HitRange)((int)a | (int)b); }
	inline HitRange operator&(HitRange a, HitRange b) { return(HitRange)((int)a & (int)b); }
	enum class ZombieHitType :DWORD {
		BITE,
		SMASH,
		VAULT,
		LADDER
	};
	enum class PlantPriority :DWORD {
		BITE,
		DIG,
		BUNGEE,
		CATAPULT,
		TOOL,
		ANY,
		MAIN,
		TOP,
		MIDDLE,
		BOTTOM
	};
	enum class CardReject :DWORD {
		NIL,
		NOT_HERE,
		ONLY_ON_GRAVES,
		ONLY_IN_POOL,
		ONLY_ON_GROUND,
		NEEDS_POT,
		NOT_ON_ART,
		NOT_PASSED_LINE,
		NEEDS_UPGRADE,
		NOT_ON_GRAVE,
		NOT_ON_CRATER,
		NOT_ON_WATER,
		NEEDS_GROUND,
		NEEDS_SLEEPING
	};
	enum Layer {
		ROW = 10000,
		UI_BOTTOM = 100000,
		GROUND = 200000,
		LAWN = 300000,
		TOP = 400000,
		FOG = 500000,
		COIN_BANK = 600000,
		UI_TOP = 700000,
		ABOVE_UI = 800000,
		SCREEN_FADE = 900000,
		ROW_OFFSET = 10000,
		GRAVE_STONE = 301000,
		PLANT = 302000,
		ZOMBIE = 303000,
		BOSS = 304000,
		PROJECTILE = 305000,
		LAWN_MOWER = 306000,
		PARTICLE = 307000
	};
	class ActiveFontLayer;
	class Almance;
	class Anim;
	class AnimAttachment;
	class AnimInfo;
	class AnimsLists;
	class Attacher;
	class AttacherInfo;
	class Attachment;
	class AutoCrit;
	class AutoModalFlags;
	class BaseRes;
	class BassInfo;
	class BassInstance;
	class BassMusicInfo;
	class BassMusicInterface;
	class BetaSurport;
	class Bgm;
	class Board;
	class BoardText;
	class btn;
	class Building;
	class Bullet;
	class ButtonWidget;
	class Card;
	class CardImages;
	class CharData;
	class CheckBox;
	class ContinueLevelWnd;
	class CritSect;
	class D3DInterface;
	class D3DTester;
	class D3DTestImage;
	class Data;
	class DataElement;
	class DDImage;
	class DDInterface;
	class DescParser;
	class Dialog;
	class DialogBtn;
	class DialogButton;
	class DSoundManager;
	class EditWidget;
	class Emitter;
	class EmitterInfo;
	class EncodingParser;
	class FlagsMod;
	class FontData;
	class FontLayer;
	class FmodInstance;
	class FmodMusicInfo;
	class FmodMusicInterface;
	class Font;
	class FontRes;
	class GameApp;
	class GameOverWnd;
	class GardenPlant;
	class GardenProp;
	class Graphics;
	class mState;
	class GridPlantList;
	class HyperlinkWidget;
	class HttpTransfer;
	class Image;
	class ImageButton;
	class ImageFont;
	class ImageRes;
	class ImitaterWnd;
	class InputBox;
	class InputWindow;
	class InternetManager;
	class Item;
	class LevelProp;
	class ListDataElement;
	class ListWidget;
	class LoadingPage;
	class MainMenu;
	class MainMenu_Widget;
	class MemoryImage;
	class Menu;
	class MImgStruct;
	class ModalFlags;
	class MouseAddProp;
	class MouseProp;
	class MouseText;
	class Mower;
	class MsgWidget;
	class MsgBox;
	class MTAutoDisallowRand;
	class MTRand;
	class MusicInterface;
	class MV;
	class MV_Widget;
	class NativeDisplay;
	class NotePage;
	class Particle;
	class ParticlesLists;
	class ParticleSystem;
	class ParticleSystemInfo;
	class Plant;
	class PlantAttractedItem;
	class PlantInfo;
	class PopcapMsg;
	class PreModalInfo;
	class PropertiesParser;
	class ResourceManager;
	class Sample;
	class SampleManager;
	class ScrollbarWidget;
	class SelectCardWnd;
	class SceneProp;
	class SelectLevelPage;
	class SexyApp;
	class SexyAppBase;
	class SharedImage;
	class SharedImageRef;
	class Shop;
	class Shop_Widget;
	class SingleDataElement;
	class Slider;
	class Slot;
	class SnailInfo;
	class SoundInstance;
	class SoundManager;
	class SoundRes;
	class Sysfont;
	class TextureData;
	class TextureDataPiece;
	class Trail;
	class UserData;
	class UsersManager;
	class WhoAreYouWnd;
	class Widget;
	class WidgetContainer;
	class WidgetSafeDeleteInfo;
	class WidgetManager;
	class WidthCheck;
	class std_wstring;
	class XMLMapIterator;
	class XMLParser;
	class Zombie;


	extern MTRand& defaultRand;
	int rand(int n, MTRand& rand = defaultRand);
	int rand(int m, int n, MTRand& rand = defaultRand);
	float rand(float n, MTRand& rand = defaultRand);
	float rand(float m, float n, MTRand& rand = defaultRand);

	int getCurveValue(int curve, int x1, int x2, int y1, int y2, int x);
	float getCurveValue(int curve, int x1, int x2, float y1, float y2, int x);

	template<typename T>
	class RndSelecter {
		vector<pair<int, T> > data;
		int wSum;
		T __default;
	public:
		RndSelecter(T _default) :data(), wSum(0), __default(_default) {}
		bool empty() { return wSum == 0; }
		void put(int weight, T val) {
			wSum += weight;
			data.emplace_back(wSum, val);
		}
		T get() {
			if (empty())return __default;
			int w = rand(wSum);
			for (auto&& p : data)if (p.first > w)return p.second;
			return(T)0;
		}
	};
	template<typename T>
	class RndSelecterF {
		vector<pair<float, T> > data;
		float wSum;
		T __default;
	public:
		RndSelecterF(T _default) :data(), wSum(0.0f), __default(_default) {}
		bool empty() { return wSum == 0.0f; }
		void put(float weight, T val) {
			wSum += weight;
			data.emplace_back(wSum, val);
		}
		T get() {
			if (empty())return __default;
			float w = rand(wSum);
			for (auto&& p : data)if (p.first > w)return p.second;
			return(T)0;
		}
	};





	class std_string :public std::basic_string<char> {
	protected:
		virtual void func() {}
	public:
		template<typename... Args>
		std_string(Args... args) :basic_string(args...) {}
	};
	class std_wstring :public std::basic_string<wchar_t> {
	protected:
		virtual void func() {}
	public:
		template<typename... Args>
		std_wstring(Args... args) :basic_string(args...) {}
	};
	using TriVertex = BasicVertex;

	template <typename... Args>
	std_string format(const char* format, Args... args) {
		if (Cvp::__realloc_buffer(snprintf(Cvp::__char_buffer, Cvp::__buffer_size, format, args...)))snprintf(Cvp::__char_buffer, Cvp::__buffer_size, format, args...);
		return std_string(Cvp::__char_buffer);
	}

	template<typename T1, class T2>
	class std_pair :public std::pair<T1, T2> {
	public:
	};

	template<typename T>
	class std_list :public std::list<T> {
	public:
		virtual void allocator() {}
	};

	template<typename T>
	class std_vector :public std::vector<T> {
	public:
		virtual void allocator() {}
	};
	template<typename T>
	class std_set :public std::set<T> {
	public:
		virtual void allocator() {}
	};

	template<typename T1, class T2>
	class std_map :public std::map<T1, T2> {
	public:
		virtual void allocator() {}
	};

	template<typename T> class ID {
	public:
		union {
			struct {
				WORD mIndex;
				WORD mRank;
			};
			DWORD mVal;
		};
		operator DWORD() { return mVal; }
		ID(DWORD _id) { mVal = _id; }
		ID() :mIndex(0), mRank(0) {}
	};
	template<typename T> class StaticListNode {
	public:
		T mVal;
		ID<T> mID;
	};
	template<typename T>
	ID<T>& GetID(const T& _this) { return((StaticListNode<T>*) & _this)->mID; }
	template<typename T>
	StaticListNode<T>& GetNode(const T& _this) { return(StaticListNode<T>)_this; }
	template<typename T> class StaticList {
		//static_assert(offsetof(T, vanished));
	public:
		StaticListNode<T>* mArray;
		int mCapacity;
		int mMax;
		int mNextIndex;
		int mSize;
		int mNextRank;
		const char* mTag;
		T* operator[](int n) {
			if (mArray[n].mVal.vanished)return nullptr;
			return &mArray[n].mVal;
		}
		T* operator[](ID<T> _id) {
			if (_id.mRank && !mArray[_id.mIndex].mVal.vanished && mArray[_id.mIndex].mID == _id)return &mArray[_id.mIndex].mVal;
			return nullptr;
		}
		T* New() {
			++mSize;
			StaticListNode<T>* temp = (mArray + mNextIndex);
			ID<T> id;
			id.mIndex = (WORD)mNextIndex;
			id.mRank = (WORD)mNextRank;
			if (mNextIndex == mCapacity)++mNextIndex, ++mCapacity;
			else mNextIndex = mArray[mNextIndex].mID;
			++mNextRank;
			if (mNextRank >> 16)mNextRank = 1;
			new((T*)temp)T();
			temp->mID = id;
			return(T*)temp;
		}
		class iterator {
			friend class StaticList<T>;
			StaticListNode<T>* __p;
			StaticList<T>* __parent;
			iterator(StaticListNode<T>* p, StaticList<T>* parent) :__p(p), __parent(parent) {}
			iterator& normalize() { while ((__p != __parent->mArray + __parent->mCapacity) && (__p->mVal.vanished))++__p; return *this; }
		public:
			T& operator*() { return __p->mVal; }
			T* operator->() { return &__p->mVal; }
			iterator& operator++() { ++__p; return normalize(); }
			bool operator==(const iterator that) { return __p == that.__p; }
			bool operator!=(const iterator that) { return __p != that.__p; }
		};
		iterator begin() { return iterator(mArray, this).normalize(); }
		iterator end() { return iterator(mArray + mCapacity, this); }
		bool Next(T*& ptr) {
			StaticListNode<T>* nptr = (StaticListNode<T>*)ptr;
			if (nptr)++nptr;
			else nptr = mArray;
			StaticListNode<T>* end = mArray + mCapacity;
			while (true) {
				if ((DWORD)nptr >= (DWORD)end) {
					ptr = nullptr;
					return false;
				}
				if (!nptr->mVal.vanished) {
					ptr = (T*)nptr;
					return true;
				}
				++nptr;
			}
		}
		void Clean() {
			for (auto p = begin(); p != end(); ++p) if(GetID(*p).mRank&&p->vanished) {
				DWORD temp = GetID(*p).mIndex;
				GetID(*p).mVal = mNextIndex;
				mNextIndex = temp;
				--mSize;
			}
		}
	};

	template<typename T> class SNode {
	public:
		SNode<T>* prev;
		SNode<T>* next;
		T val;
	};
	template<typename T> class SList {
		SNode<T>* front;
		SNode<T>* back;
		int size;
	};
	template<typename T> class SNodeStack {
	public:
		DWORD _0;
		SNode<T>* mNodes;
		DWORD mCapacity;
		DWORD _3;
		DWORD mEleSize;
	};

	template<typename T>
	class DataList {
	public:
		int nextId_Low;
		int record;
		int count;
		T* mData;
	};

	class Edge {
		using _CLASS = Edge;
	public:
		double mX;
		double mDX;
		int i;
		double b;
	};

	class Insets {
		using _CLASS = Insets;
	public:
		int mLeft;
		int mTop;
		int mRight;
		int mBottom;
	};

	class Span {
	public:
		int						mY;
		int						mX;
		int						mWidth;
	};

	class GridPlantList {
		using _CLASS = GridPlantList;
	public:
		Plant* mBottom;
		Plant* mMiddle;
		Plant* mTop;
		Plant* mMain;
	};

	struct MouseResult {
		enum class Type :DWORD {
			NIL,
			PLANT,
			BULLET,
			ITEM,
			CARD,
			SHOVEL,
			POT,
			FERTILIZER,
			INSECTICIDE,
			PHONOGRAPH,
			CHOCOLATE,
			GLOVE,
			SELL,
			CART,
			TREE_FOOD,
			NEXT_GARDEN,
			MENU_BUTTON,
			STORE_BUTTON,
			SLOTMACHINE,
			VASE,
			SNAIL,
			WISDOMTREE
		};
		void* ptr;
		Type type;
		template<typename T> T& Get()const { return *(T*)ptr; }
		operator bool() { return type != Type::NIL; }
		MouseResult(Type __type = Type::NIL, void* __ptr = nullptr) :ptr(__ptr), type(__type) {}
		MouseResult(Plant* p) :ptr(p), type(Type::PLANT) {}
		MouseResult(Item* p) :ptr(p), type(Type::ITEM) {}
		MouseResult(Card* p) :ptr(p), type(Type::CARD) {}
	};

	class Buffer {
		using _CLASS = Buffer;
	public:
		static constexpr DWORD vfAddr_Buffer = 0x0067530Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_Buffer = vfAddr_Buffer;
		std_vector<char> mData;
		int mDataBitSize;
		int mReadBitPos;
		int mWriteBitPos;
		void New();
		void WriteNumBits(int theNum, int theBits);
		int ReadNumBits(int theBits, bool isSigned);
	};

	class Context :public Buffer {
		using _CLASS = Context;
	public:
		static constexpr DWORD vfAddr_Buffer = 0x0067530Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		bool fail;
		bool read;
	};

	class Ratio {
		using _CLASS = Ratio;
	public:
		int mNumerator;
		int mDenominator;
	};

	class Secret {
		using _CLASS = Secret;
	public:
		std_string mTarget;
		std_string mPresent;
	};

	class FlagsMod {
		using _CLASS = FlagsMod;
	public:
		int mAddFlags;
		int mRemoveFlags;
	};

	class Timer {
		using _CLASS = Timer;
	public:
		QWORD start;
		double ans;
		bool running;
		Timer() : start(0), ans(0.0), running(false) {}
		void Start() { running = true; QueryPerformanceCounter((LARGE_INTEGER*)&start); }
		void Calculate() {
			QWORD PerformanceCount = 0, Frequency = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&PerformanceCount);
			QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency);
			ans = (double)(PerformanceCount - start) * 1000.0 / (double)Frequency;
		}
		void Stop() { Calculate(); running = false; }
		double Get() { if (running)Calculate(); return ans; }
	};

	class ButtonListener {
		using _CLASS = ButtonListener;
	public:
		static constexpr DWORD vfAddr_ButtonListener = 0x0066F9B0ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
	};

	class DialogListener {
		using _CLASS = DialogListener;
	public:
		static constexpr DWORD vfAddr_DialogListener = 0x006713FCul;
		static void(__thiscall _CLASS::*& vfDialogButtonPress)(int dlgId, int btnId); void DialogButtonPress(int dlgId, int btnId);
		static void(__thiscall _CLASS::*& vfDialogButtonDepress)(int dlgId, int btnId); void DialogButtonDepress(int dlgId, int btnId);

		DWORD vf_DialogListener = vfAddr_DialogListener;
	};

	class ScrollListener {
		using _CLASS = ScrollListener;
	public:
		static constexpr DWORD vfAddr_ScrollListener = 0x0066FD7Cul;
		static void(__thiscall _CLASS::*& vfScrollPosition)(int Id, double pos); void ScrollPosition(int Id, double pos);
		DWORD vf_ScrollListener = vfAddr_ScrollListener;
	};

	class SliderListener {
		using _CLASS = SliderListener;
	public:
		DWORD* vf_ScrollListener;//=(DWORD*)vfAddr_ScrollListener;
	};

	class CheckboxListener {
		using _CLASS = CheckboxListener;
	public:
		DWORD* vf_ScrollListener;// =(DWORD*)vfAddr_ScrollListener;
	};

	class ListListener {
		using _CLASS = ListListener;
	public:
		static constexpr DWORD vfAddr_ListListener = 0x0066E4E8ul;
		static void(__thiscall _CLASS::*& vfListClicked)(int Id, int index, int count); void ListClicked(int Id, int index, int count);
		static void(__thiscall _CLASS::*& vfListClosed)(int Id); void ListClosed(int Id);
		static void(__thiscall _CLASS::*& vfListHiliteChanged)(int Id, int oldIdx, int newIdx); void ListHiliteChanged(int Id, int oldIdx, int newIdx);
		DWORD vf_ListListener = vfAddr_ListListener;
	};

	class EditListener {
		using _CLASS = EditListener;
	public:
		static constexpr DWORD vfAddr_EditListener = 0x00668978ul;
		static void(__thiscall _CLASS::*& vfEditWidgetText)(int Id, const std_string& str); void EditWidgetText(int Id, const std_string& str);
		static void(__thiscall _CLASS::*& vfAllowKey)(int Id, KeyCode key); void AllowKey(int Id, KeyCode key);
		static void(__thiscall _CLASS::*& vfAllowChar)(int Id, char chr); void AllowChar(int Id, char chr);
		static void(__thiscall _CLASS::*& vfAllowText)(int Id, const std_string& txt); void AllowText(int Id, const std_string& txt);
		DWORD vf_EditListener = vfAddr_EditListener;
	};

	class RowSpawnInfo {
		using _CLASS = RowSpawnInfo;
	public:
		int mRow;
		float mWeight;
		float mAcc1;
		float mAcc2;
	};

	class ParticleSystem {
		using _CLASS = ParticleSystem;
	public:
		enum class Type :DWORD {
			NIL = 0xFFFFFFFFul,
			MELONSPLASH = 0,
			WINTERMELON,
			FUMECLOUD,
			POPCORNSPLASH,
			POWIE,
			JACKEXPLODE,
			ZOMBIE_HEAD,
			ZOMBIE_ARM,
			ZOMBIE_TRAFFIC_CONE,
			ZOMBIE_PAIL,
			ZOMBIE_HELMET,
			ZOMBIE_FLAG,
			ZOMBIE_DOOR,
			ZOMBIE_NEWSPAPER,
			ZOMBIE_HEADLIGHT,
			POW,
			ZOMBIE_POGO,
			ZOMBIE_NEWSPAPER_HEAD,
			ZOMBIE_BALLOON_HEAD,
			SOD_ROLL,
			GRAVE_STONE_RISE,
			PLANTING,
			PLANTING_POOL,
			ZOMBIE_RISE,
			GRAVE_BUSTER,
			GRAVE_BUSTER_DIE,
			POOL_SPLASH,
			ICE_SPARKLE,
			SEED_PACKET,
			TALL_NUT_BLOCK,
			DOOM,
			DIGGER_RISE,
			DIGGER_TUNNEL,
			DANCER_RISE,
			POOL_SPARKLY,
			WALLNUT_EAT_SMALL,
			WALLNUT_EAT_LARGE,
			PEA_SPLAT,
			BUTTER_SPLAT,
			CABBAGE_SPLAT,
			PUFF_SPLAT,
			STAR_SPLAT,
			ICE_TRAP,
			SNOWPEA_SPLAT,
			SNOWPEA_PUFF,
			SNOWPEA_TRAIL,
			LANTERN_SHINE,
			SEED_PACKET_PICKUP,
			POTATO_MINE,
			POTATO_MINE_RISE,
			PUFFSHROOM_TRAIL,
			PUFFSHROOM_MUZZLE,
			SEED_PACKET_FLASH,
			WHACK_A_ZOMBIE_RISE,
			ZOMBIE_LADDER,
			UMBRELLA_REFLECT,
			SEED_PACKET_PICK,
			ICE_TRAP_ZOMBIE,
			ICE_TRAP_RELEASE,
			ZOMBONI_SMOKE,
			GLOOMCLOUD,
			ZOMBIE_POGO_HEAD,
			ZOMBONI_TIRE,
			ZOMBONI_EXPLOSION,
			ZOMBONI_EXPLOSION2,
			CATAPULT_EXPLOSION,
			MOWER_CLOUD,
			BOSS_ICE_BALL,
			BLASTMARK,
			COIN_PICKUP_ARROW,
			PRESENT_PICKUP,
			IMITATER_MORPH,
			MOWERED_ZOMBIE_HEAD,
			MOWERED_ZOMBIE_ARM,
			ZOMBIE_HEAD_POOL,
			ZOMBIE_BOSS_FIREBALL,
			FIREBALL_DEATH,
			ICEBALL_DEATH,
			ICEBALL_TRAIL,
			FIREBALL_TRAIL,
			BOSS_EXPLOSION,
			SCREEN_FLASH,
			TROPHY_SPARKLE,
			PORTAL_CIRCLE,
			PORTAL_SQUARE,
			POTTED_PLANT_GLOW,
			POTTED_WATER_PLANT_GLOW,
			POTTED_ZEN_GLOW,
			MIND_CONTROL,
			VASE_SHATTER,
			VASE_SHATTER_LEAF,
			VASE_SHATTER_ZOMBIE,
			AWARD_PICKUP_ARROW,
			ZOMBIE_SEAWEED,
			ZOMBIE_MUSTACHE,
			ZOMBIE_FUTURE_GLASSES,
			PINATA,
			DUST_SQUASH,
			DUST_FOOT,
			DAISY,
			STARBURST,
			UPSELL_ARROW
		};
		Type type;
		ParticleSystemInfo* info;
		ParticlesLists* ParticlesLists;
		SList<ID<Emitter>>* EmitterIDList;
		SList<ID<Particle>> ParticleIDList;
		bool vanished;
		bool isAttachment;
		int layer;
		bool freezed;
		void Update();
		void Kill();
		void SetColor(Color* theColor, const char* emittername = nullptr);
		void SetShine(bool ifShine);
		void SetPosition(float x, float y);
		void SetSize(float size);
	};

	class SelectWndCard {
		using _CLASS = SelectWndCard;
	public:
		int x;
		int y;
		int w;
		int h;
		int xlast;
		int yLast;
		int xTarget;
		int yTarget;
		int cardType;
		int state;//0up 1slot 2down 3wnd 4imitater
		int slotRank;
		bool CDing;
		int CDTime;
		int imitaterCardType;
		bool daveChoose;
	};

	class WidgetContainer {
		using _CLASS = WidgetContainer;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066F934ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(Graphics* g); void Draw(Graphics* g);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);

		DWORD vf_WidgetContainer = vfAddr_WidgetContainer;
		std_list<Widget*> mWidgets;
		WidgetManager* mWidgetManager;
		WidgetContainer* mParent;
		bool mUpdateIteratorModified;
		DWORD _iteratorAllocator;
		std_list<Widget*>::iterator mUpdateIterator;
		int mLastWMUpdateCount;
		int mUpdateCnt;
		int mDirty;
		int mX;
		int mY;
		int mWidth;
		int mHeight;
		bool mHasAlpha;
		bool mClip;
		FlagsMod mWidgetFlagsMod;
		int mPriority;
		int mZOrder;
		//void MarkDirty();
		//Rect GetRect();
		//bool Intersects(WidgetContainer* theWidget);
		//void MarkDirty(WidgetContainer* theWidget);
		//void MarkDirtyFull();
		//void MarkDirtyFull(WidgetContainer* theWidget);
		//void UpdateAll(ModalFlags* theFlags);
		//void MarkAllDirty();
		//void DrawAll(ModalFlags* theFlags,Graphics* g);
		Widget* GetWidgetAtHelper(int x, int y, int theFlags, bool* found, int* theWidgetX, int* theWidgetY);
		//Point GetAbsPos();
		//void RemoveWidget(Widget* theWidget);
		//void RemovedFromManager(WidgetManager* theWidgetManager);
		//void SysColorChangedAll();
		enum {
			WIDGETFLAGS_UPDATE = 1,
			WIDGETFLAGS_MARK_DIRTY = 2,
			WIDGETFLAGS_DRAW = 4,
			WIDGETFLAGS_CLIP = 8,
			WIDGETFLAGS_ALLOW_MOUSE = 16,
			WIDGETFLAGS_ALLOW_FOCUS = 32
		};
	};

	class Widget :public WidgetContainer {
		using _CLASS = Widget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066F794ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char theChar); void KeyChar(char theChar);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode theKey); void KeyDown(KeyCode theKey);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode theKey); void KeyUp(KeyCode theKey);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);

		bool mVisible;
		bool mMouseVisible;
		bool mDisabled;
		bool mHasFocus;
		bool mIsDown;
		bool mIsOver;
		bool mHasTransparencies;
		std_vector<Color> mColors;
		Insets mMouseInsets;
		bool mDoFinger;
		bool mWantsFocus;
		Widget* mTabPrev;
		Widget* mTabNext;
		//bool Contains(int theX, int theY);
		//Rect GetInsetRect();
		//bool IsPointVisible(int x, int y);
		//void ShowFinger(bool on);
		void WidgetRemovedHelper();
		//void LostFocus();
		//bool WantsFocus();
		//void GotFocus();
		//void KeyDown(KeyCode theKey);
		//void KeyUp(KeyCode theKey);
	};

	class Dialog :public Widget {
		using _CLASS = Dialog;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066F9D4ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static constexpr DWORD vfAddr_ButtonListener = 0x0066FB08ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		enum class Type :DWORD {
			NEW_GAME,
			OPTIONS,
			NEWOPTIONS,
			ALMANAC,
			STORE,
			PREGAME_NAG,
			LOAD_GAME,
			CONFIRM_UPDATE_CHECK,
			CHECKING_UPDATES,
			REGISTER_ERROR,
			COLORDEPTH_EXP,
			OPENURL_WAIT,
			OPENURL_FAIL,
			QUIT,
			HIGH_SCORES,
			NAG,
			INFO,
			GAME_OVER,
			LEVEL_COMPLETE,
			PAUSED,
			NO_MORE_MONEY,
			BONUS,
			CONFIRM_BACK_TO_MAIN,
			CONFIRM_IN_GAME_RESTART,
			THANKS_FOR_REGISTERING,
			NOT_ENOUGH_MONEY,
			UPGRADED,
			NO_UPGRADE,
			CHOOSER_WARNING,
			USERDIALOG,
			CREATEUSER,
			CONFIRMDELETEUSER,
			RENAMEUSER,
			CREATEUSERERROR,
			RENAMEUSERERROR,
			CHEAT,
			CHEATERROR,
			CONTINUE,
			GETREADY,
			RESTARTCONFIRM,
			CONFIRMPURCHASE,
			CONFIRMSELL,
			TIMESUP,
			VIRTUALHELP,
			JUMPAHEAD,
			CRAZY_DAVE,
			STORE_PURCHASE,
			VISIT_TREE_OF_WISDOM,
			ZEN_SELL,
			MESSAGE,
			IMITATER,
			PURCHASE_PACKET_SLOT = 50,
			ABOUT,
			RESTART_WARNING,
			UPSELL,
			ACHIEVEMENT_LOCKED,
			UPDATE_NOW,
			MORE_GAMES,
			SKIP_TUTORIAL,
			LEADERBOARD
		};
		DialogListener* mDialogListener;
		Image* mComponentImage;
		DialogButton* mYesButton;
		DialogButton* mNoButton;
		int mNumButtons;
		std_string mDialogHeader;
		std_string mDialogFooter;
		std_string mDialogLines;
		int mButtonMode;
		Font* mHeaderFont;
		Font* mLinesFont;
		int mTextAlign;
		int mLineSpacingOffset;
		int mButtonHeight;
		Insets mBackgroundInsets;
		Insets mContentInsets;
		int mSpaceAfterHeader;
		bool mDragging;
		int mDragMouseX;
		int mDragMouseY;
		int mId;
		bool mIsModal;
		int mResult;
		int mButtonHorzSpacing;
		int mButtonSidePadding;
	};

	class SexyAppBase {
		using _CLASS = SexyAppBase;
	public:
		static constexpr DWORD vfAddr_ButtonListener = 0x0067140Cul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		static bool(__thiscall _CLASS::*& vfProcess)(bool allowSleep); bool Process(bool allowSleep = true);
		static void(__thiscall _CLASS::*& vfUpdateFrames)(void); void UpdateFrames(void);
		static bool(__thiscall _CLASS::*& vfDoUpdateFrames)(void); bool DoUpdateFrames(void);
		static void(__thiscall _CLASS::*& vfDoUpdateFramesF)(float theFrac); void DoUpdateFramesF(float theFrac);
		static void(__thiscall _CLASS::*& vfMakeWindow)(void); void MakeWindow(void);
		static void(__thiscall _CLASS::*& vfEnforceCursor)(void); void EnforceCursor(void);
		static void(__thiscall _CLASS::*& vfReInitImages)(void); void ReInitImages(void);
		static void(__thiscall _CLASS::*& vfDeleteNativeImageData)(void); void DeleteNativeImageData(void);
		static void(__thiscall _CLASS::*& vfDeleteExtraImageData)(void); void DeleteExtraImageData(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadCompleted)(void); void LoadingThreadCompleted(void);
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static MusicInterface* (__thiscall _CLASS::*& vfCreateMusicInterface)(HWND hwnd); MusicInterface* CreateMusicInterface(HWND hwnd);
		static void(__thiscall _CLASS::*& vfInitHook)(void); void InitHook(void);
		static void(__thiscall _CLASS::*& vfShutdownHook)(void); void ShutdownHook(void);
		static void(__thiscall _CLASS::*& vfPreTerminate)(void); void PreTerminate(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadProc)(void); void LoadingThreadProc(void);
		static void(__thiscall _CLASS::*& vfWriteToRegistry)(void); void WriteToRegistry(void);
		static void(__thiscall _CLASS::*& vfReadFromRegistry)(void); void ReadFromRegistry(void);
		static Dialog* (__thiscall _CLASS::*& vfNewDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* NewDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static void(__thiscall _CLASS::*& vfPreDisplayHook)(void); void PreDisplayHook(void);
		static void(__thiscall _CLASS::*& vfBeginPopup)(void); void BeginPopup(void);
		static void(__thiscall _CLASS::*& vfEndPopup)(void); void EndPopup(void);
		static void(__thiscall _CLASS::*& vfMsgBox_0)(void); void MsgBox_0(void);
		static void(__thiscall _CLASS::*& vfMsgBox)(void); void MsgBox(void);
		static void(__thiscall _CLASS::*& vfPopup_0)(void); void Popup_0(void);
		static void(__thiscall _CLASS::*& vfPopup)(void); void Popup(void);
		static void(__thiscall _CLASS::*& vfLogScreenSaverError)(const std_string& theError); void LogScreenSaverError(const std_string& theError);
		static void(__thiscall _CLASS::*& vfSafeDeleteWidget)(Widget* theWidget); void SafeDeleteWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfURLOpenFailed)(const std_string& theURL); void URLOpenFailed(const std_string& theURL);
		static void(__thiscall _CLASS::*& vfURLOpenSucceeded)(const std_string& theURL); void URLOpenSucceeded(const std_string& theURL);
		static bool(__thiscall _CLASS::*& vfOpenURL)(const std_string& theURL, bool shutdownOnOpen); bool OpenURL(const std_string& theURL, bool shutdownOnOpen = false);
		static std_string(__thiscall _CLASS::*& vfGetProductVersion)(const std_string& thePath); std_string GetProductVersion(const std_string& thePath);
		static void(__thiscall _CLASS::*& vfSEHOccured)(void); void SEHOccured(void);
		static std_string(__thiscall _CLASS::*& vfGetGameSEHInfo)(void); std_string GetGameSEHInfo(void);
		static void(__thiscall _CLASS::*& vfGetSEHWebParams)(std_map<std::string, std::string>* theDefinesMap); void GetSEHWebParams(std_map<std::string, std::string>* theDefinesMap);
		static void(__thiscall _CLASS::*& vfShutdown)(void); void Shutdown(void);
		static void(__thiscall _CLASS::*& vfDoParseCmdLine)(void); void DoParseCmdLine(void);
		static void(__thiscall _CLASS::*& vfParseCmdLine)(const std_string& theCmdLine); void ParseCmdLine(const std_string& theCmdLine);
		static void(__thiscall _CLASS::*& vfHandleCmdLineParam)(const std_string& theParamName, const std_string& theParamValue); void HandleCmdLineParam(const std_string& theParamName, const std_string& theParamValue);
		static void(__thiscall _CLASS::*& vfHandleNotifyGameMessage)(int theType, int theParam); void HandleNotifyGameMessage(int theType, int theParam);
		static void(__thiscall _CLASS::*& vfHandleGameAlreadyRunning)(void); void HandleGameAlreadyRunning(void);
		static void(__thiscall _CLASS::*& vfStart)(void); void Start(void);
		static void(__thiscall _CLASS::*& vfInit)(void); void Init(void);
		static void(__thiscall _CLASS::*& vfPreDDInterfaceInitHook)(void); void PreDDInterfaceInitHook(void);
		static void(__thiscall _CLASS::*& vfPostDDInterfaceInitHook)(void); void PostDDInterfaceInitHook(void);
		static bool(__thiscall _CLASS::*& vfChangeDirHook)(const char* theIntendedPath); bool ChangeDirHook(const char* theIntendedPath);
		static void(__thiscall _CLASS::*& vfPlaySample_0)(SoundId id, int pan); void PlaySample(SoundId id, int pan);
		static void(__thiscall _CLASS::*& vfPlaySample)(SoundId id); void PlaySample(SoundId id);
		static double(__thiscall _CLASS::*& vfGetMasterVolume)(void); double GetMasterVolume(void);
		static double(__thiscall _CLASS::*& vfGetMusicVolume)(void); double GetMusicVolume(void);
		static double(__thiscall _CLASS::*& vfGetSfxVolume)(void); double GetSfxVolume(void);
		static bool(__thiscall _CLASS::*& vfIsMuted)(void); bool IsMuted(void);
		static void(__thiscall _CLASS::*& vfSetMasterVolume)(double theVolume); void SetMasterVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicVolume)(double theVolume); void SetMusicVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetSfxVolume)(double theVolume); void SetSfxVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfMute)(bool autoMute); void Mute(bool autoMute = false);
		static void(__thiscall _CLASS::*& vfUnmute)(bool autoMute); void Unmute(bool autoMute = false);
		static double(__thiscall _CLASS::*& vfGetLoadingThreadProgress)(void); double GetLoadingThreadProgress(void);
		static DDImage* (__thiscall _CLASS::*& vfGetImage)(const std_string& theFileName, bool commitBits); DDImage* GetImage(const std_string& theFileName, bool commitBits = true);
		static int(__thiscall _CLASS::*& vfSetSharedImage)(SharedImageRef*, int, int, int, int); int SetSharedImage(SharedImageRef* a, int b, int c, int d, int e);
		static SharedImageRef(__thiscall _CLASS::*& vfGetSharedImage)(const std_string& theFileName, const std::string& theVariant, bool* isNew); SharedImageRef GetSharedImage(const std_string& theFileName, const std::string& theVariant = u8"", bool* isNew = nullptr);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_1)(bool wantWindowed, bool is3d, bool force); void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_0)(bool wantWindowed); void SwitchScreenMode(bool wantWindowed);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode)(void); void SwitchScreenMode(void);
		static void(__thiscall _CLASS::*& vfSetAlphaDisabled)(bool isDisabled); void SetAlphaDisabled(bool isDisabled);
		static Dialog* (__thiscall _CLASS::*& vfDoDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* DoDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static Dialog* (__thiscall _CLASS::*& vfGetDialog)(Dialog::Type type); Dialog* GetDialog(Dialog::Type type);
		static void(__thiscall _CLASS::*& vfAddDialog)(Dialog* theDialog); void AddDialog(Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfAddDialog_0)(int theDialogId, Dialog* theDialog); void AddDialog(int theDialogId, Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfKillDialog_0)(void); void KillDialog_0(void);
		static void(__thiscall _CLASS::*& vfKillDialog)(void); void KillDialog(void);
		static void(__thiscall _CLASS::*& vfKillDialog_1)(void); void KillDialog_1(void);
		static int(__thiscall _CLASS::*& vfGetDialogCount)(void); int GetDialogCount(void);
		static void(__thiscall _CLASS::*& vfModalOpen)(void); void ModalOpen(void);
		static void(__thiscall _CLASS::*& vfModalClose)(void); void ModalClose(void);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static bool(__thiscall _CLASS::*& vfIsAltKeyUsed)(WPARAM wParam); bool IsAltKeyUsed(WPARAM wParam);
		static bool(__thiscall _CLASS::*& vfDebugKeyDown)(int theKey); bool DebugKeyDown(int theKey);
		static bool(__thiscall _CLASS::*& vfDebugKeyDownAsync)(int theKey, bool ctrlDown, bool altDown); bool DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		static void(__thiscall _CLASS::*& vfCloseRequestAsync)(void); void CloseRequestAsync(void);
		static void(__thiscall _CLASS::*& vfDone3dTesting)(void); void Done3dTesting(void);
		static std_string(__thiscall _CLASS::*& vfNotifyCrashHook)(void); std_string NotifyCrashHook(void);
		static void(__thiscall _CLASS::*& vfCheckSignature)(void); void CheckSignature(void);
		static bool(__thiscall _CLASS::*& vfDrawDirtyStuff)(void); bool DrawDirtyStuff(void);
		static void(__thiscall _CLASS::*& vfRedraw)(Rect* theClipRect); void Redraw(Rect* theClipRect);
		static void(__thiscall _CLASS::*& vfInitPropertiesHook)(void); void InitPropertiesHook(void);
		static void(__thiscall _CLASS::*& vfDoMainLoop)(void); void DoMainLoop(void);
		static bool(__thiscall _CLASS::*& vfUpdateAppStep)(bool* updated); bool UpdateAppStep(bool* updated);
		static bool(__thiscall _CLASS::*& vfUpdateApp)(void); bool UpdateApp(void);
		static bool(__thiscall _CLASS::*& vfAppCanRestore)(void); bool AppCanRestore(void);
		static void(__thiscall _CLASS::*& vfreturn0)(void); void return0(void);
		static constexpr DWORD vfAddr_DialogListener = 0x0067159Cul;
		static void(__thiscall _CLASS::*& vfDialogButtonPress)(int dlgId, int btnId); void DialogButtonPress(int dlgId, int btnId);
		static void(__thiscall _CLASS::*& vfDialogButtonDepress)(int dlgId, int btnId); void DialogButtonDepress(int dlgId, int btnId);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		DWORD vf_DialogListener = vfAddr_DialogListener;
		int mRandSeed;
		std_string mCompanyName;
		std_string mFullCompanyName;
		std_string mProdName;
		std_string mTitle;
		std_string mRegKey;
		std_string mChangeDirTo;
		int mRelaxUpdateBacklogCount;
		int mPreferredX;
		int mPreferredY;
		int mWidth;
		int mHeight;
		int mFullscreenBits;
		double mMusicVolume;
		double mSfxVolume;
		double mDemoMusicVolume;
		double mDemoSfxVolume;
		bool mNoSoundNeeded;
		bool mWantFMod;
		bool mCmdLineParsed;
		bool mSkipSignatureChecks;
		bool mStandardWordWrap;
		bool mbAllowExtendedChars;
		HANDLE mMutex;
		bool mOnlyAllowOneCopyToRun;
		int mNotifyGameMessage;
		RTL_CRITICAL_SECTION mCritSect;
		bool mBetaValidate;
		char mAdd8BitMaxTable[0x100u];
		char mFFChars[0x100u];
		WidgetManager* mWidgetManager;
		std_map<int, Dialog*> mDialogMap;
		std_list<Dialog*> mDialogList;
		int mPrimaryThreadId;
		bool mSEHOccured;
		bool mShutdown;
		bool mExitToTop;
		bool mIsWindowed;
		bool mIsPhysWindowed;
		bool mFullScreenWindow;
		bool mForceFullscreen;
		bool mForceWindowed;
		bool mInitialized;
		bool mProcessInTimer;
		int mTimeLoaded;
		HWND mHWnd;
		HWND mInvisHWnd;
		bool mIsScreenSaver;
		bool mAllowMonitorPowersave;
		std_list<MSG> mDeferredMessages;
		bool mNoDefer;
		bool mFullScreenPageFlip;
		bool mTabletPC;
		DDInterface* mDDInterface;
		bool mAlphaDisabled;
		BassMusicInterface* mMusicInterface;
		bool mReadFromRegistry;
		std_string mRegisterLink;
		std_string mProductVersion;
		Image* mCursorImages[0x0Du];
		HCURSOR mOverrideCursor;
		bool mIsOpeningURL;
		bool mShutdownOnURLOpen;
		std_string mOpeningURL;
		int mOpeningURLTime;
		int mLastTimerTime;
		int mLastBigDelayTime;
		double mUnmutedMusicVolume;
		double mUnmutedSfxVolume;
		int mMuteCount;
		int mAutoMuteCount;
		bool mDemoMute;
		bool mMuteOnLostFocus;
		std_set<MemoryImage*> mMemoryImageSet;
		std_map<std_pair<string, string>, SharedImage> mSharedImageMap;
		bool mCleanupSharedImages;
		int mNonDrawCount;
		int mFrameTime;
		bool mIsDrawing;
		bool mLastDrawWasEmpty;
		bool mHasPendingDraw;
		double mPendingUpdatesAcc;
		double mUpdateFTimeAcc;
		int mLastTimeCheck;
		int mLastTime;
		int mLastUserInputTick;
		int mSleepCount;
		int mDrawCount;
		int mUpdateCount;
		int mUpdateAppState;
		int mUpdateAppDepth;
		double mUpdateMultiplier;
		bool mPaused;
		int mFastForwardToUpdateNum;
		bool mFastForwardToMarker;
		bool mFastForwardStep;
		int mLastDrawTick;
		int mNextDrawTick;
		int mStepMode;//0off 1step 2waiting
		int mCursorNum;
		SoundManager* mSoundManager;
		HCURSOR mHandCursor;
		HCURSOR mDraggingCursor;
		std_list<WidgetSafeDeleteInfo> mSafeDeleteList;
		bool mMouseIn;
		bool mRunning;
		bool mActive;
		bool mMinimized;
		bool mPhysMinimized;
		bool mIsDisabled;
		bool mHasFocus;
		int mDrawTime;
		int mFPSStartTick;
		int mFPSFlipCount;
		int mFPSDirtyCount;
		int mFPSTime;
		int mFPSCount;
		bool mShowFPS;
		int mShowFPSMode;
		int mScreenBltTime;
		bool mAutoStartLoadingThread;
		bool mLoadingThreadStarted;
		bool mLoadingThreadCompleted;
		bool mLoaded;
		bool mYieldMainThread;
		bool mLoadingFailed;
		bool mCursorThreadRunning;
		bool mSysCursor;
		bool mCustomCursorsEnabled;
		bool mCustomCursorDirty;
		bool mLastShutdownWasGraceful;
		bool mIsWideWindow;
		bool mWriteToSexyCache;
		bool mSexyCacheBuffers;
		int mNumLoadingThreadTasks;
		int mCompletedLoadingThreadTasks;
		bool mRecordingDemoBuffer;
		bool mPlayingDemoBuffer;
		bool mManualShutdown;
		std_string mDemoPrefix;
		std_string mDemoFileName;
		Buffer mDemoBuffer;
		int mDemoLength;
		int mLastDemoMouseX;
		int mLastDemoMouseY;
		int mLastDemoUpdateCnt;
		bool mDemoNeedsCommand;
		bool mDemoIsShortCmd;
		int mDemoCmdNum;
		int mDemoCmdOrder;
		int mDemoCmdBitPos;
		bool mDemoLoadingComplete;
		std_map<HANDLE, int> mHandleToIntMap;
		int mCurHandleNum;
		std_list<std_pair<string, int>>mDemoMarkerList;
		bool mDebugKeysEnabled;
		bool mEnableMaximizeButton;
		bool mCtrlDown;
		bool mAltDown;
		bool mForbidSwitchScreen;
		int mSyncRefreshRate;
		bool mVSyncUpdates;
		bool mVSyncBroken;
		int mVSyncBrokenCount;
		int mVSyncBrokenTestStartTick;
		DWORD mVSyncBrokenTestUpdates;
		bool mWaitForVSync;
		bool mSoftVSyncWait;
		bool mUserChanged3DSetting;
		bool mAutoEnable3D;
		bool mTest3D;
		int mMinVidMemory3D;
		int mRecommendedVidMemory3D;
		bool mWidescreenAware;
		bool mWidescreenTranslate;
		Rect mScreenBounds;
		bool mEnableWindowAspect;
		Ratio mWindowAspect;
		std_map<string, std_wstring> mStringProperties;
		std_map<string, bool> mBoolProperties;
		std_map<string, int> mIntProperties;
		std_map<string, double> mDoubleProperties;
		std_map<string, vector<string>>mStringVectorProperties;
		ResourceManager* mResourceManager;
		int mOldWndProc;
		void WriteDemoTimingBlock();
		//void UpdateFrames();
		void CleanSharedImages();
		void ProcessDemo();
		bool ProcessDeferredMessages(bool singleMessage);
		//bool DoUpdateFrames();
		//void Shutdown();
		//void SetMusicVolume(double theVolume);
		//void SetSfxVolume(double theVolume);
		void RestoreScreenResolution();
		//void WriteToRegistry();
		bool RegistryWriteInteger(const std_string& theValueName, int theValue);
		bool RegistryWriteBoolean(const std_string& theValueName, bool theValue);
		bool RegistryWrite(const std_string& theValueName, ulong theType, const uchar* theValue, ulong theLength);
		bool PrepareDemoCommand();
		//void Mute(bool autoMute = false);
		//void Unmute(bool autoMute = false);
		void ClearUpdateBacklog(bool relaxForASecond = false);
		void ProcessSafeDeleteList();
		void UpdateFTimeAcc();
		void UpdateAppOnce(int millisecond);
		//void Redraw(Rect* theClipRect);
		int InitDDInterface();
		//void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
		//void SwitchScreenMode(bool wantWindowed);
		//void SwitchScreenMode();
		void Set3DAcclerated(bool is3D, bool reinit = true);
		bool Is3DAccelerated();
		void RehupFocus();
		//void URLOpenSucceeded(const std_string& theURL);
		void SetCursor(int theCursorNum);
		void ClearKeysDown();
		//bool DebugKeyDown(int theKey);
		//void URLOpenFailed(const std_string& theURL);
		enum {
			DEMO_MOUSE_POSITION,
			DEMO_ACTIVATE_APP,
			DEMO_SIZE,
			DEMO_KEY_DOWN,
			DEMO_KEY_UP,
			DEMO_KEY_CHAR,
			DEMO_CLOSE,
			DEMO_MOUSE_ENTER,
			DEMO_MOUSE_EXIT,
			DEMO_LOADING_COMPLETE,
			DEMO_REGISTRY_GETSUBKEYS,
			DEMO_REGISTRY_READ,
			DEMO_REGISTRY_WRITE,
			DEMO_REGISTRY_ERASE,
			DEMO_FILE_EXISTS,
			DEMO_FILE_READ,
			DEMO_FILE_WRITE,
			DEMO_HTTP_RESULT,
			DEMO_SYNC,
			DEMO_ASSERT_STRING_EQUAL,
			DEMO_ASSERT_INT_EQUAL,
			DEMO_MOUSE_WHEEL,
			DEMO_HANDLE_COMPLETE,
			DEMO_VIDEO_DATA,
			DEMO_IDLE = 31
		};
		enum {
			FPS_ShowFPS,
			FPS_ShowCoords,
			Num_FPS_Types
		};
		enum {
			UPDATESTATE_MESSAGES,
			UPDATESTATE_PROCESS_1,
			UPDATESTATE_PROCESS_2,
			UPDATESTATE_PROCESS_DONE
		};
	};

	class SexyApp :public SexyAppBase {
		using _CLASS = SexyApp;
	public:
		static constexpr DWORD vfAddr_ButtonListener = 0x006767FCul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		static bool(__thiscall _CLASS::*& vfProcess)(bool allowSleep); bool Process(bool allowSleep = true);
		static void(__thiscall _CLASS::*& vfUpdateFrames)(void); void UpdateFrames(void);
		static bool(__thiscall _CLASS::*& vfDoUpdateFrames)(void); bool DoUpdateFrames(void);
		static void(__thiscall _CLASS::*& vfDoUpdateFramesF)(float theFrac); void DoUpdateFramesF(float theFrac);
		static void(__thiscall _CLASS::*& vfMakeWindow)(void); void MakeWindow(void);
		static void(__thiscall _CLASS::*& vfEnforceCursor)(void); void EnforceCursor(void);
		static void(__thiscall _CLASS::*& vfReInitImages)(void); void ReInitImages(void);
		static void(__thiscall _CLASS::*& vfDeleteNativeImageData)(void); void DeleteNativeImageData(void);
		static void(__thiscall _CLASS::*& vfDeleteExtraImageData)(void); void DeleteExtraImageData(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadCompleted)(void); void LoadingThreadCompleted(void);
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static MusicInterface* (__thiscall _CLASS::*& vfCreateMusicInterface)(HWND hwnd); MusicInterface* CreateMusicInterface(HWND hwnd);
		static void(__thiscall _CLASS::*& vfInitHook)(void); void InitHook(void);
		static void(__thiscall _CLASS::*& vfShutdownHook)(void); void ShutdownHook(void);
		static void(__thiscall _CLASS::*& vfPreTerminate)(void); void PreTerminate(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadProc)(void); void LoadingThreadProc(void);
		static void(__thiscall _CLASS::*& vfWriteToRegistry)(void); void WriteToRegistry(void);
		static void(__thiscall _CLASS::*& vfReadFromRegistry)(void); void ReadFromRegistry(void);
		static Dialog* (__thiscall _CLASS::*& vfNewDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* NewDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static void(__thiscall _CLASS::*& vfPreDisplayHook)(void); void PreDisplayHook(void);
		static void(__thiscall _CLASS::*& vfBeginPopup)(void); void BeginPopup(void);
		static void(__thiscall _CLASS::*& vfEndPopup)(void); void EndPopup(void);
		static void(__thiscall _CLASS::*& vfMsgBox_0)(void); void MsgBox_0(void);
		static void(__thiscall _CLASS::*& vfMsgBox)(void); void MsgBox(void);
		static void(__thiscall _CLASS::*& vfPopup_0)(void); void Popup_0(void);
		static void(__thiscall _CLASS::*& vfPopup)(void); void Popup(void);
		static void(__thiscall _CLASS::*& vfLogScreenSaverError)(const std_string& theError); void LogScreenSaverError(const std_string& theError);
		static void(__thiscall _CLASS::*& vfSafeDeleteWidget)(Widget* theWidget); void SafeDeleteWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfURLOpenFailed)(const std_string& theURL); void URLOpenFailed(const std_string& theURL);
		static void(__thiscall _CLASS::*& vfURLOpenSucceeded)(const std_string& theURL); void URLOpenSucceeded(const std_string& theURL);
		static bool(__thiscall _CLASS::*& vfOpenURL)(const std_string& theURL, bool shutdownOnOpen); bool OpenURL(const std_string& theURL, bool shutdownOnOpen = false);
		static std_string(__thiscall _CLASS::*& vfGetProductVersion)(const std_string& thePath); std_string GetProductVersion(const std_string& thePath);
		static void(__thiscall _CLASS::*& vfSEHOccured)(void); void SEHOccured(void);
		static std_string(__thiscall _CLASS::*& vfGetGameSEHInfo)(void); std_string GetGameSEHInfo(void);
		static void(__thiscall _CLASS::*& vfGetSEHWebParams)(std_map<std::string, std::string>* theDefinesMap); void GetSEHWebParams(std_map<std::string, std::string>* theDefinesMap);
		static void(__thiscall _CLASS::*& vfShutdown)(void); void Shutdown(void);
		static void(__thiscall _CLASS::*& vfDoParseCmdLine)(void); void DoParseCmdLine(void);
		static void(__thiscall _CLASS::*& vfParseCmdLine)(const std_string& theCmdLine); void ParseCmdLine(const std_string& theCmdLine);
		static void(__thiscall _CLASS::*& vfHandleCmdLineParam)(const std_string& theParamName, const std_string& theParamValue); void HandleCmdLineParam(const std_string& theParamName, const std_string& theParamValue);
		static void(__thiscall _CLASS::*& vfHandleNotifyGameMessage)(int theType, int theParam); void HandleNotifyGameMessage(int theType, int theParam);
		static void(__thiscall _CLASS::*& vfHandleGameAlreadyRunning)(void); void HandleGameAlreadyRunning(void);
		static void(__thiscall _CLASS::*& vfStart)(void); void Start(void);
		static void(__thiscall _CLASS::*& vfInit)(void); void Init(void);
		static void(__thiscall _CLASS::*& vfPreDDInterfaceInitHook)(void); void PreDDInterfaceInitHook(void);
		static void(__thiscall _CLASS::*& vfPostDDInterfaceInitHook)(void); void PostDDInterfaceInitHook(void);
		static bool(__thiscall _CLASS::*& vfChangeDirHook)(const char* theIntendedPath); bool ChangeDirHook(const char* theIntendedPath);
		static void(__thiscall _CLASS::*& vfPlaySample_0)(SoundId id, int pan); void PlaySample(SoundId id, int pan);
		static void(__thiscall _CLASS::*& vfPlaySample)(SoundId id); void PlaySample(SoundId id);
		static double(__thiscall _CLASS::*& vfGetMasterVolume)(void); double GetMasterVolume(void);
		static double(__thiscall _CLASS::*& vfGetMusicVolume)(void); double GetMusicVolume(void);
		static double(__thiscall _CLASS::*& vfGetSfxVolume)(void); double GetSfxVolume(void);
		static bool(__thiscall _CLASS::*& vfIsMuted)(void); bool IsMuted(void);
		static void(__thiscall _CLASS::*& vfSetMasterVolume)(double theVolume); void SetMasterVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicVolume)(double theVolume); void SetMusicVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetSfxVolume)(double theVolume); void SetSfxVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfMute)(bool autoMute); void Mute(bool autoMute = false);
		static void(__thiscall _CLASS::*& vfUnmute)(bool autoMute); void Unmute(bool autoMute = false);
		static double(__thiscall _CLASS::*& vfGetLoadingThreadProgress)(void); double GetLoadingThreadProgress(void);
		static DDImage* (__thiscall _CLASS::*& vfGetImage)(const std_string& theFileName, bool commitBits); DDImage* GetImage(const std_string& theFileName, bool commitBits = true);
		static int(__thiscall _CLASS::*& vfSetSharedImage)(SharedImageRef*, int, int, int, int); int SetSharedImage(SharedImageRef* a, int b, int c, int d, int e);
		static SharedImageRef(__thiscall _CLASS::*& vfGetSharedImage)(const std_string& theFileName, const std::string& theVariant, bool* isNew); SharedImageRef GetSharedImage(const std_string& theFileName, const std::string& theVariant = u8"", bool* isNew = nullptr);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_1)(bool wantWindowed, bool is3d, bool force); void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_0)(bool wantWindowed); void SwitchScreenMode(bool wantWindowed);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode)(void); void SwitchScreenMode(void);
		static void(__thiscall _CLASS::*& vfSetAlphaDisabled)(bool isDisabled); void SetAlphaDisabled(bool isDisabled);
		static Dialog* (__thiscall _CLASS::*& vfDoDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* DoDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static Dialog* (__thiscall _CLASS::*& vfGetDialog)(Dialog::Type type); Dialog* GetDialog(Dialog::Type type);
		static void(__thiscall _CLASS::*& vfAddDialog)(Dialog* theDialog); void AddDialog(Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfAddDialog_0)(int theDialogId, Dialog* theDialog); void AddDialog(int theDialogId, Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfKillDialog_0)(void); void KillDialog_0(void);
		static void(__thiscall _CLASS::*& vfKillDialog)(void); void KillDialog(void);
		static void(__thiscall _CLASS::*& vfKillDialog_1)(void); void KillDialog_1(void);
		static int(__thiscall _CLASS::*& vfGetDialogCount)(void); int GetDialogCount(void);
		static void(__thiscall _CLASS::*& vfModalOpen)(void); void ModalOpen(void);
		static void(__thiscall _CLASS::*& vfModalClose)(void); void ModalClose(void);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static bool(__thiscall _CLASS::*& vfIsAltKeyUsed)(WPARAM wParam); bool IsAltKeyUsed(WPARAM wParam);
		static bool(__thiscall _CLASS::*& vfDebugKeyDown)(int theKey); bool DebugKeyDown(int theKey);
		static bool(__thiscall _CLASS::*& vfDebugKeyDownAsync)(int theKey, bool ctrlDown, bool altDown); bool DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		static void(__thiscall _CLASS::*& vfCloseRequestAsync)(void); void CloseRequestAsync(void);
		static void(__thiscall _CLASS::*& vfDone3dTesting)(void); void Done3dTesting(void);
		static std_string(__thiscall _CLASS::*& vfNotifyCrashHook)(void); std_string NotifyCrashHook(void);
		static void(__thiscall _CLASS::*& vfCheckSignature)(void); void CheckSignature(void);
		static bool(__thiscall _CLASS::*& vfDrawDirtyStuff)(void); bool DrawDirtyStuff(void);
		static void(__thiscall _CLASS::*& vfRedraw)(Rect* theClipRect); void Redraw(Rect* theClipRect);
		static void(__thiscall _CLASS::*& vfInitPropertiesHook)(void); void InitPropertiesHook(void);
		static void(__thiscall _CLASS::*& vfDoMainLoop)(void); void DoMainLoop(void);
		static bool(__thiscall _CLASS::*& vfUpdateAppStep)(bool* updated); bool UpdateAppStep(bool* updated);
		static bool(__thiscall _CLASS::*& vfUpdateApp)(void); bool UpdateApp(void);
		static bool(__thiscall _CLASS::*& vfAppCanRestore)(void); bool AppCanRestore(void);
		static bool(__thiscall _CLASS::*& vfOverrideWindowProc)(HWND, unsigned int, unsigned int, int, int*); bool OverrideWindowProc(HWND a, unsigned int b, unsigned int c, int d, int* e);
		static bool(__thiscall _CLASS::*& vfShouldCheckForUpdate)(void); bool ShouldCheckForUpdate(void);
		static void(__thiscall _CLASS::*& vfUpdateCheckQueried)(void); void UpdateCheckQueried(void);
		static bool(__thiscall _CLASS::*& vfOpenRegisterPage)(void); bool OpenRegisterPage(void);
		static int(__thiscall _CLASS::*& vfOpenRegisterPage_0)(std_map<std_string, std_string>); int OpenRegisterPage(std_map<std_string, std_string> a);
		static bool(__thiscall _CLASS::*& vfOpenHTMLTemplate)(std_string const&, class std::map<std_string, std_string> const&); bool OpenHTMLTemplate(std_string const& a, class std::map<std_string, std_string> const& b);
		static void(__thiscall _CLASS::*& vfOpenUpdateURL)(void); void OpenUpdateURL(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char); void KeyChar(char a);
		static constexpr DWORD vfAddr_DialogListener = 0x006769A8ul;
		static void(__thiscall _CLASS::*& vfDialogButtonPress)(int dlgId, int btnId); void DialogButtonPress(int dlgId, int btnId);
		static void(__thiscall _CLASS::*& vfDialogButtonDepress)(int dlgId, int btnId); void DialogButtonDepress(int dlgId, int btnId);

		InternetManager* mInternetManager;
		BetaSurport* mBetaSurport;
		std_string mBetaSupportSiteOverride;
		std_string mBetaSupportProdNameOverride;
		std_string mReferId;
		std_string mVariation;
		int mDownloadId;
		std_string mRegSource;
		int mLastVerCheckQueryTime;
		bool mURLOpenSucceeded;
		bool mDontUpdate;
		int mBuildNum;
		std_string mBuildDate;
		std_string mUsername;
		std_string mRegUserName;
		std_string mRegCode;
		bool mNoReg;
		bool mNoReg1;
		int mTimesPlayed;
		int mTimesExecuted;
		bool mTimedOut;
	};


	class WidgetManager :public WidgetContainer {
		using _CLASS = WidgetManager;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066F8B4ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);

		Widget* mDefaultTab;
		Graphics* mCurG;
		SexyAppBase* mApp;
		Image* mImage;
		MemoryImage* mTransientImage;
		bool mLastHadTransients;
		Widget* mPopupCommandWidget;
		std_vector<std_pair<Widget*, int>> mDeferredOverlayWidgets;
		int mMinDeferredOverlayPriority;
		bool mHasFocus;
		Widget* mFocusWidget;
		Widget* mLastDownWidget;
		Widget* mOverWidget;
		Widget* mBaseModalWidget;
		FlagsMod mLostFocusFlagsMod;
		FlagsMod mBelowModalFlagsMod;
		FlagsMod mDefaultBelowModalFlagsMod;
		std_list<PreModalInfo> mPreModalInfoList;
		Rect mMouseDestRect;
		Rect mMouseSourceRect;
		bool mMouseIn;
		int mLastMouseX;
		int mLastMouseY;
		int mDownButtons;
		int mActualDownButtons;
		int mLastInputUpdateCnt;
		char mKeyDown[0xFFu];
		int mLastDownButtonId;
		int mWidgetFlags;
		void InitModalFlags(ModalFlags* theModalFlags);
		int GetWidgetFlags();
		bool UpdateFrame();
		void __thiscall v_UpdateAll(ModalFlags* theFlags);
		bool DrawScreen();
		void FlushDeferredOverlayWidgets(int theMaxPriority);
		void RemapMouse(int& theX, int& theY);
		bool MouseMove(int x, int y);
		bool MouseDrag(int x, int y);
		void MousePosition(int x, int y);
		Widget* GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
		Widget* GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
		void MouseLeave(Widget* theWidget);
		void MouseEnter(Widget* theWidget);
		bool MouseDown(int x, int y, int theClickCount);
		void RemovePopupCommandWidget();
		//void DisableWidget(Widget* theWidget);
		void DoMouseUps(Widget* theWidget, ulong theDownCode);
		//void SetFocus(Widget* aWidget);
		bool MouseUp(int x, int y, int theClickCount);
		void MouseWheel(int theDelta);
		bool KeyDown(KeyCode key);
		bool KeyUp(KeyCode key);
		bool KeyChar(char theChar);
		bool MouseExit(int x, int y);
	};

	class NativeDisplay {
		using _CLASS = NativeDisplay;
	public:
		static constexpr DWORD vfAddr_NativeDisplay = 0x00672380ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_NativeDisplay = vfAddr_NativeDisplay;
		int mRGBBits;
		int mRedMask;
		int mGreenMask;
		int mBlueMask;
		int mRedBits;
		int mGreenBits;
		int mBlueBits;
		int mRedShift;
		int mGreenShift;
		int mBlueShift;
	};

	class CritSect {
		using _CLASS = CritSect;
	public:
		LPVOID DebugInfo;
		int LockCount;
		int RecursionCount;
		HANDLE OwningThread;
		HANDLE LockSemaphore;
		QWORD* SpinCount;
	};

	class DDInterface :public NativeDisplay {
		using _CLASS = DDInterface;
	public:
		static constexpr DWORD vfAddr_NativeDisplay = 0x00672544ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		SexyAppBase* mApp;
		D3DInterface* mD3DInterface;
		D3DTester* mD3DTester;
		bool mIs3D;
		CritSect mCritSect;
		bool mInRedraw;
		IDirectDraw* mDD;
		LPVOID mDD7;
		IDirectDrawSurface* mPrimarySurface;
		IDirectDrawSurface* mSecondarySurface;
		IDirectDrawSurface* mDrawSurface;
		IDirectDrawSurface* mWindowScaleBuffers[4];
		int mWidth;
		int mHeight;
		Ratio mAspect;
		int mDesktopWidth;
		int mDesktopHeight;
		Ratio mDesktopAspect;
		bool mIsWidescreen;
		int mDisplayWidth;
		int mDisplayHeight;
		Ratio mDisplayAspect;
		Rect mPresentationRect;
		int mFullscreenBits;
		int mRefreshRate;
		int mMillisecondsPerFrame;
		int mScanLineFailCount;
		DWORD* mRedAddTable;
		DWORD* mGreenAddTable;
		DWORD* mBlueAddTable;
		DWORD mRedConvTable[0x100u];
		DWORD mGreenConvTable[0x100u];
		DWORD mBlueConvTable[0x100u];
		bool mInitialized;
		HWND mHWnd;
		bool mIsWindowed;
		DDImage* mScreenImage;
		DDImage* mSecondaryImage;
		std_set<DDImage> mDDImageSet;
		bool mVideoOnlyDraw;
		int mInitCount;
		int mCursorWidth;
		int mCursorHeight;
		int mNextCursorX;
		int mNextCursorY;
		int mCursorX;
		int mCursorY;
		Image* mCursorImage;
		bool mHasOldCursorArea;
		LPVOID mOldCursorArea;
		LPVOID mNewCursorArea;
		DDImage* mOldCursorAreaImage;
		DDImage* mNewCursorAreaImage;
		std_string mErrorString;
		DDImage* GetScreenImage();
		bool Redraw(Rect* theClipRect);
		bool SetCursorImage(Image* theImage);
		enum {
			RESULT_OK = 0,
			RESULT_FAIL = 1,
			RESULT_DD_CREATE_FAIL = 2,
			RESULT_SURFACE_FAIL = 3,
			RESULT_EXCLUSIVE_FAIL = 4,
			RESULT_DISPCHANGE_FAIL = 5,
			RESULT_INVALID_COLORDEPTH = 6,
			RESULT_3D_FAIL = 7
		};
	};

	class Image {
		using _CLASS = Image;
	public:
		static constexpr DWORD vfAddr_Image = 0x0067245Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfPolyFill3D)(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex); bool PolyFill3D(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex);
		static void(__thiscall _CLASS::*& vfFillRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void DrawRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfClearRect)(const Rect& theRect); void ClearRect(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfDrawLine)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawLineAA)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLines)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode); void FillScanLines(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLinesWithCoverage)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight); void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight);
		static void(__thiscall _CLASS::*& vfBlt)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltF)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode); void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltRotated)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY); void BltRotated(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY);
		static void(__thiscall _CLASS::*& vfStretchBlt)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		static void(__thiscall _CLASS::*& vfBltMatrix)(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend); void BltMatrix(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend);
		static void(__thiscall _CLASS::*& vfBltTrianglesTex)(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend); void BltTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend);
		static void(__thiscall _CLASS::*& vfBltMirror)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfStretchBltMirror)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBltMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);

		DWORD vf_Image = vfAddr_Image;
		bool mDrawn;
		std_string mFilePath;
		int mWidth;
		int mHeight;
		int mNumRows;
		int mNumCols;
		AnimInfo* mAnimInfo;
		int GetWidth();
		int GetHeight();
	};

	class MemoryImage :public Image {
		using _CLASS = MemoryImage;
	public:
		static constexpr DWORD vfAddr_Image = 0x006724A4ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfPolyFill3D)(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex); bool PolyFill3D(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex);
		static void(__thiscall _CLASS::*& vfFillRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void DrawRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfClearRect)(const Rect& theRect); void ClearRect(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfDrawLine)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawLineAA)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLines)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode); void FillScanLines(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLinesWithCoverage)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight); void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight);
		static void(__thiscall _CLASS::*& vfBlt)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltF)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode); void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltRotated)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY); void BltRotated(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY);
		static void(__thiscall _CLASS::*& vfStretchBlt)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		static void(__thiscall _CLASS::*& vfBltMatrix)(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend); void BltMatrix(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend);
		static void(__thiscall _CLASS::*& vfBltTrianglesTex)(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend); void BltTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend);
		static void(__thiscall _CLASS::*& vfBltMirror)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfStretchBltMirror)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBltMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		static void* (__thiscall _CLASS::*& vfGetNativeAlphaData)(NativeDisplay* theNative); void* GetNativeAlphaData(NativeDisplay* theNative);
		static uchar* (__thiscall _CLASS::*& vfGetRLAlphaData)(void); uchar* GetRLAlphaData(void);
		static uchar* (__thiscall _CLASS::*& vfGetRLAdditiveData)(NativeDisplay* theNative); uchar* GetRLAdditiveData(NativeDisplay* theNative);
		static void(__thiscall _CLASS::*& vfPurgeBits)(void); void PurgeBits(void);
		static void(__thiscall _CLASS::*& vfDeleteSWBuffers)(void); void DeleteSWBuffers(void);
		static void(__thiscall _CLASS::*& vfDelete3DBuffers)(void); void Delete3DBuffers(void);
		static void(__thiscall _CLASS::*& vfDeleteExtraBuffers)(void); void DeleteExtraBuffers(void);
		static void(__thiscall _CLASS::*& vfReInit)(void); void ReInit(void);
		static void(__thiscall _CLASS::*& vfBitsChanged)(void); void BitsChanged(void);
		static void(__thiscall _CLASS::*& vfCommitBits)(void); void CommitBits(void);
		static void(__thiscall _CLASS::*& vfDeleteNativeData)(void); void DeleteNativeData(void);
		static void(__thiscall _CLASS::*& vfClear)(void); void Clear(void);
		static void(__thiscall _CLASS::*& vfSetBits)(ulong* theBits, int theWidth, int theHeight, bool commitBits); void SetBits(ulong* theBits, int theWidth, int theHeight, bool commitBits = true);
		static void(__thiscall _CLASS::*& vfCreate)(int w, int h); void Create(int w, int h);
		static ulong* (__thiscall _CLASS::*& vfGetBits)(void); ulong* GetBits(void);
		static void(__thiscall _CLASS::*& vfSetImageMode)(bool hasTrans, bool hasAlpha); void SetImageMode(bool hasTrans, bool hasAlpha);
		static void(__thiscall _CLASS::*& vfSetVolatile)(bool isVolatile); void SetVolatile(bool isVolatile);
		static bool(__thiscall _CLASS::*& vfPalletize)(void); bool Palletize(void);

		DWORD* mBits;
		int mBitsChangedCount;
		void* mD3DData;
		int mD3DFlags;
		DWORD* mColorTable;
		char* mColorIndices;
		bool mForcedMode;
		bool mHasTrans;
		bool mHasAlpha;
		bool mIsVolatile;
		bool mPurgeBits;
		bool mWantPal;
		LPVOID mNativeAlphaData;
		char* mRLAlphaData;
		char* mRLAdditiveData;
		bool mBitsChanged;
		SexyAppBase* mApp;
	};

	class DDImage :public MemoryImage {
		using _CLASS = DDImage;
	public:
		static constexpr DWORD vfAddr_Image = 0x0067238Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfPolyFill3D)(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex); bool PolyFill3D(const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex);
		static void(__thiscall _CLASS::*& vfFillRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawRect)(const Rect& theRect, const Color& theColor, int theDrawMode); void DrawRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfClearRect)(const Rect& theRect); void ClearRect(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfDrawLine)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfDrawLineAA)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode); void DrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLines)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode); void FillScanLines(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfFillScanLinesWithCoverage)(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight); void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight);
		static void(__thiscall _CLASS::*& vfBlt)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltF)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode); void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfBltRotated)(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY); void BltRotated(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY);
		static void(__thiscall _CLASS::*& vfStretchBlt)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		static void(__thiscall _CLASS::*& vfBltMatrix)(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend); void BltMatrix(Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend);
		static void(__thiscall _CLASS::*& vfBltTrianglesTex)(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend); void BltTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend);
		static void(__thiscall _CLASS::*& vfBltMirror)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode); void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		static void(__thiscall _CLASS::*& vfStretchBltMirror)(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch); void StretchBltMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		static void* (__thiscall _CLASS::*& vfGetNativeAlphaData)(NativeDisplay* theNative); void* GetNativeAlphaData(NativeDisplay* theNative);
		static uchar* (__thiscall _CLASS::*& vfGetRLAlphaData)(void); uchar* GetRLAlphaData(void);
		static uchar* (__thiscall _CLASS::*& vfGetRLAdditiveData)(NativeDisplay* theNative); uchar* GetRLAdditiveData(NativeDisplay* theNative);
		static void(__thiscall _CLASS::*& vfPurgeBits)(void); void PurgeBits(void);
		static void(__thiscall _CLASS::*& vfDeleteSWBuffers)(void); void DeleteSWBuffers(void);
		static void(__thiscall _CLASS::*& vfDelete3DBuffers)(void); void Delete3DBuffers(void);
		static void(__thiscall _CLASS::*& vfDeleteExtraBuffers)(void); void DeleteExtraBuffers(void);
		static void(__thiscall _CLASS::*& vfReInit)(void); void ReInit(void);
		static void(__thiscall _CLASS::*& vfBitsChanged)(void); void BitsChanged(void);
		static void(__thiscall _CLASS::*& vfCommitBits)(void); void CommitBits(void);
		static void(__thiscall _CLASS::*& vfDeleteNativeData)(void); void DeleteNativeData(void);
		static void(__thiscall _CLASS::*& vfClear)(void); void Clear(void);
		static void(__thiscall _CLASS::*& vfSetBits)(ulong* theBits, int theWidth, int theHeight, bool commitBits); void SetBits(ulong* theBits, int theWidth, int theHeight, bool commitBits = true);
		static void(__thiscall _CLASS::*& vfCreate)(int w, int h); void Create(int w, int h);
		static ulong* (__thiscall _CLASS::*& vfGetBits)(void); ulong* GetBits(void);
		static void(__thiscall _CLASS::*& vfSetImageMode)(bool hasTrans, bool hasAlpha); void SetImageMode(bool hasTrans, bool hasAlpha);
		static void(__thiscall _CLASS::*& vfSetVolatile)(bool isVolatile); void SetVolatile(bool isVolatile);
		static bool(__thiscall _CLASS::*& vfPalletize)(void); bool Palletize(void);
		static void(__thiscall _CLASS::*& vfSetVideoMemory)(bool wantVideoMemory); void SetVideoMemory(bool wantVideoMemory);
		static void(__thiscall _CLASS::*& vfRehupFirstPixelTrans)(void); void RehupFirstPixelTrans(void);
		static void(__thiscall _CLASS::*& vfNormalFillRect)(const Rect& theRect, const Color& theColor); void NormalFillRect(const Rect& theRect, const Color& theColor);
		static void(__thiscall _CLASS::*& vfAdditiveFillRect)(const Rect& theRect, const Color& theColor); void AdditiveFillRect(const Rect& theRect, const Color& theColor);
		static void(__thiscall _CLASS::*& vfNormalBlt)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor); void NormalBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
		static void(__thiscall _CLASS::*& vfAdditiveBlt)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor); void AdditiveBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
		static void(__thiscall _CLASS::*& vfNormalDrawLine)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor); void NormalDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		static void(__thiscall _CLASS::*& vfAdditiveDrawLine)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor); void AdditiveDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		static void(__thiscall _CLASS::*& vfNormalDrawLineAA)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor); void NormalDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		static void(__thiscall _CLASS::*& vfAdditiveDrawLineAA)(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor); void AdditiveDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		static void(__thiscall _CLASS::*& vfNormalBltMirror)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor); void NormalBltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
		static void(__thiscall _CLASS::*& vfAdditiveBltMirror)(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor); void AdditiveBltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
		static bool(__thiscall _CLASS::*& vfLockSurface)(void); bool LockSurface(void);
		static bool(__thiscall _CLASS::*& vfUnlockSurface)(void); bool UnlockSurface(void);
		static void(__thiscall _CLASS::*& vfSetSurface)(LPDIRECTDRAWSURFACE theSurface); void SetSurface(LPDIRECTDRAWSURFACE theSurface);
		static int(__thiscall _CLASS::*& vfWriteToCache)(std::string* a, std::string* b); int WriteToCache(std::string* a, std::string* b);

		DDInterface* mDDInterface;
		IDirectDrawSurface* mSurface;
		bool mSurfaceSet;
		bool mNoLock;
		bool mVideoMemory;
		bool mFirstPixelTrans;
		bool mWantDDSurface;
		bool mDrawToBits;
		int mLockCount;
		DDSURFACEDESC mLockedSurfaceDesc;
		DDImage(DDInterface* theDDInterface);
		static bool Check3D(Image* theImage);
		static bool Check3D(DDImage* theImage);
		void DeleteAllNonSurfaceData();
		void Draw(DWORD theColor, const Rect& theSrcRect, const Matrix3& theTransform, bool mix = false, const Rect& theDestRect = { 0,0,0x3ffffffful,0x3ffffffful });
	};

	DDImage* ImageToDDImage(const Image* _ptr);

	class AnimInfo {
		using _CLASS = AnimInfo;
	public:
		int mAnimType;
		int mFrameDelay;
		int mNumCels;
		std_vector<int> mPerFrameDelay;
		std_vector<int> mFrameMap;
		int mTotalAnimTime;
	};

	class FramePartProp {
	public:
		float mTransX;
		float mTransY;
		float mSkewX;
		float mSkewY;
		float mScaleX;
		float mScaleY;
		float mFrame;
		float mAlpha;
		void* mFont;
		void* mImage;
		const char* mText;
		Matrix3 GetMatrix();
	};

	class PartProp {
	public:
		char* name;
		FramePartProp* mTransforms;
		int mTransformCount;
		bool isAttacher();
	};

	class AnimImage {
	public:
		int w, h;
		Image mOriginalImage;
	};

	class AnimImageList {
	public:
		AnimImage mImageArray[20];
		int mImageCount;
		MemoryImage mMemoryImage;
	};

	class AnimDefinition {
	public:
		PartProp* mTracks;
		int mTrackCount;
		float mFPS;
		AnimImageList* mReanimAtlas;
	};

	class AnimFrameTime {
	public:
		float mFraction;
		int mAnimFrameBeforeInt;
		int mAnimFrameAfterInt;
	};

	class Anim {
		using _CLASS = Anim;
	public:
		enum class Type :DWORD {
			NIL = 0xFFFFFFFFul,
			LOADBAR_SPROUT = 0,
			LOADBAR_ZOMBIEHEAD,
			SODROLL,
			FINAL_WAVE,
			PEASHOOTER,
			WALLNUT,
			LILYPAD,
			SUNFLOWER,
			LAWNMOWER,
			READYSETPLANT,
			CHERRYBOMB,
			SQUASH,
			DOOMSHROOM,
			SNOWPEA,
			REPEATER,
			SUNSHROOM,
			TALLNUT,
			FUMESHROOM,
			PUFFSHROOM,
			HYPNOSHROOM,
			CHOMPER,
			ZOMBIE,
			SUN,
			POTATOMINE,
			SPIKEWEED,
			SPIKEROCK,
			THREEPEATER,
			MARIGOLD,
			ICESHROOM,
			ZOMBIE_FOOTBALL,
			ZOMBIE_NEWSPAPER,
			ZOMBIE_ZOMBONI,
			SPLASH,
			JALAPENO,
			JALAPENO_FIRE,
			COIN_SILVER,
			ZOMBIE_CHARRED,
			ZOMBIE_CHARRED_IMP,
			ZOMBIE_CHARRED_DIGGER,
			ZOMBIE_CHARRED_ZOMBONI,
			ZOMBIE_CHARRED_CATAPULT,
			ZOMBIE_CHARRED_GARGANTUAR,
			SCRAREYSHROOM,
			PUMPKIN,
			PLANTERN,
			TORCHWOOD,
			SPLITPEA,
			SEASHROOM,
			BLOVER,
			FLOWER_POT,
			CACTUS,
			DISCO,
			TANGLEKELP,
			STARFRUIT,
			POLEVAULTER,
			BALLOON,
			GARGANTUAR,
			IMP,
			DIGGER,
			DIGGER_DIRT,
			ZOMBIE_DOLPHINRIDER,
			POGO,
			BACKUP_DANCER,
			BOBSLED,
			JACKINTHEBOX,
			SNORKEL,
			BUNGEE,
			CATAPULT,
			LADDER,
			PUFF,
			SLEEPING,
			GRAVE_BUSTER,
			ZOMBIES_WON,
			MAGNETSHROOM,
			BOSS,
			CABBAGEPULT,
			KERNELPULT,
			MELONPULT,
			COFFEEBEAN,
			UMBRELLALEAF,
			GATLINGPEA,
			CATTAIL,
			GLOOMSHROOM,
			BOSS_ICEBALL,
			BOSS_FIREBALL,
			COBCANNON,
			GARLIC,
			GOLD_MAGNET,
			WINTER_MELON,
			TWIN_SUNFLOWER,
			POOL_CLEANER,
			ROOF_CLEANER,
			FIRE_PEA,
			IMITATER,
			YETI,
			BOSS_DRIVER,
			LAWN_MOWERED_ZOMBIE,
			CRAZY_DAVE,
			TEXT_FADE_ON,
			HAMMER,
			SLOT_MACHINE_HANDLE,
			SELECTOR_SCREEN,
			PORTAL_CIRCLE,
			PORTAL_SQUARE,
			ZENGARDEN_SPROUT,
			ZENGARDEN_WATERINGCAN,
			ZENGARDEN_FERTILIZER,
			ZENGARDEN_BUGSPRAY,
			ZENGARDEN_PHONOGRAPH,
			DIAMOND,
			STINKY,
			RAKE,
			RAIN_CIRCLE,
			RAIN_SPLASH,
			ZOMBIE_SURPRISE,
			COIN_GOLD,
			ZOMBIE_FLAGPOLE,
			WOODSIGN,
			ASTRONAUT
		};
		enum class LoopType :DWORD {
			LOOP,
			LOOP_FULL_LAST_FRAME,
			PLAY_ONCE,
			PLAY_ONCE_AND_HOLD,
			PLAY_ONCE_FULL_LAST_FRAME,
			PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD
		};
		enum class ColorType :DWORD {
			NIL = 0xFFFFFFFFul,
			WASHED_OUT = 0,
			LESS_WASHED_OUT,
			WHITE
		};
		static constexpr int BASEPOS_NIL = -2;
		Type type;//0000
		float updateRate;//0004
		float updateV;//0008
		AnimDefinition* reAnim;//000C
		LoopType loopType;//0010
		bool vanished;//0014
		int initFrame;//0018
		int frameCount;//001C
		int frameBasePos;//0020
		Matrix3 mPosition;//0024
		Color mColor;//0048
		AnimAttachment* mAttachment;//0058
		int loopCount;//005C
		StaticList<Anim>* mAnimList;//0060
		bool isAttachment;//0064
		int layer;//0068
		Color mColor1;//additive//006C
		bool haveColor1;//additive//007C
		Color mColor2;//overlay//0080
		bool haveColor2;//overlay//0090
		float lastUpdateRate;//0094
		ColorType colorType;//0098
		bool isRateEqls(float rate);
		void Init(float x, float y, AnimDefinition* theDefinition);
		void Update();
		void UpdateAttacher(int index);
		void Kill();
		void SetSegment(const char* name, LoopType loop, int blend, float speed = 0.0f);
		void SetSegment(const char* name);
		void GetSegment(const char* name, int& fBegin, int& fSize);
		int GetPartIndex(const char* name);
		PartProp* GetPart(const char* name);
		AnimAttachment* GetPartAttachment(const char* name);
		void SetPartGroup(const char* name, int group);
		void StartBlend(int blend);
		void SetPartImage(const char* name, Image* image);
		void IgnoreClip(const char* name, bool ignore);
		AnimFrameTime GetFrameTime();
		FramePartProp GetCurrentFramePart(int index);
		FramePartProp GetCurrentFramePart(int index, const AnimFrameTime& time);
		FramePartProp GetCurrentFramePart(float rate, const FramePartProp& begin, const FramePartProp& end);
		AttacherInfo ParseAttacherInfo(const FramePartProp& prop);
		float GetZombieDX();
		float GetZombieDX(PartProp* ground);
		void iztUpdate();
		void PropogateColorToAttachments();
		void AttacherSynchWalkSpeed(int index, Anim* theAttachReanim, AttacherInfo* theAttacherInfo);
		Matrix3 GetAttachmentOverlayMatrix(int index);
		Matrix3 GetPartMatrix(int index);
		void SetPosition(float x, float y);
	};

	class AnimParams {
	public:
		Anim::Type mReanimationType;
		const char* mReanimFileName;
		int mReanimParamFlags;
	};

	class AttacherInfo {
	public:
		std_string mReanimName;
		std_string mTrackName;
		float mAnimRate;
		Anim::LoopType mLoopType;
	};

	class ZombieDrawPosition {
	public:
		int mHeadX;
		int mHeadY;
		int mArmY;
		float mBodyY;
		float mImageOffsetX;
		float mImageOffsetY;
		float mClipHeight;
	};

	class Zombie {
		using _CLASS = Zombie;
	public:
		enum class Type :DWORD {
			ZOMBIE,
			FLAG_ZOMBIE,
			CONEHEAD_ZOMBIE,
			POLE_VAULTING_ZOMBIE,
			BUCKETHEAD_ZOMBIE,
			NEWSPAPER_ZOMBIE,
			SCREEN_DOOR_ZOMBIE,
			FOOTBALL_ZOMBIE,
			DANCING_ZOMBIE,
			BACKUP_DANCER,
			DUCKY_TUBE_ZOMBIE,
			SNORKEL_ZOMBIE,
			ZOMBONI,
			ZOMBIE_BOBSLED_TEAM,
			DOLPHIN_RIDER_ZOMBIE,
			JACK_IN_THE_BOX_ZOMBIE,
			BALLOON_ZOMBIE,
			DIGGER_ZOMBIE,
			POGO_ZOMBIE,
			YETI_ZOMBIE,
			BUNGEE_ZOMBIE,
			LADDER_ZOMBIE,
			CATAPULT_ZOMBIE,
			GARGANTUAR,
			IMP,
			ZOMBOSS,
			PEASHOOTER,
			WALL_NUT,
			JALAPENO,
			GATLING_PEA,
			SQUASH,
			TALL_NUT,
			GIGA_GARGANTUAR,
			ENM_BEGIN
		};
		enum class State :DWORD {
			NIL,
			DYING,
			ASHED,
			MOWERED,
			BUNGEE_AIM,
			BUNGEE_FALL,
			BUNGEE_WAIT,
			BUNGEE_GRAB,
			BUNGEE_RISE,
			BUNGEE_BLOCKED,
			BUNGEE_IDLE,
			POLE_VAULTING_RUN,
			POLE_VAULTING_JUMP,
			POLE_VAULTING_WALK,
			CORAL_RISE,
			JACK_CLOCKWORK,
			JACK_SURPRISE,
			BOBSLET_ENTER,
			BOBSLED_BOARDING,
			BOBSLED_GETOFF,
			POGO_MOVE,
			POGO_ACCUMULATE1,
			POGO_ACCUMULATE2,
			POGO_ACCUMULATE3,
			POGO_ACCUMULATE4,
			POGO_ACCUMULATE5,
			POGO_ACCUMULATE6,
			POGO_JUMP2,
			POGO_JUMP7,
			NEWSPAPER_WALK,
			NEWSPAPER_DASE,
			NEWSPAPER_ANGRY,
			DIGGER_DIG,
			DIGGER_JUMP,
			DIGGER_DOUBT,
			DIGGER_ATTRACTED,
			DIGGER_DASE,
			DIGGER_WALKRIGHT,
			DIGGER_WALKLEFT,
			DIGGER_IDLE,
			MJ_ENTER,
			MJ_TURN,
			MJ_PREPARE,
			MJ_SUMMON,
			MJ_WALK,
			MJ_DANCE1,
			MJ_DANCE3,
			MJ_DANCE2,
			MJ_DANCE5,
			MJ_DANCE4,
			BACKUP_DANCER_SPAWN,
			DOLPHIN_WALK,
			DOLPHIN_DIVE,
			DOLPHIN_SPRINT,
			DOLPHIN_JUMP,
			DOLPHIN_SWIM,
			DOLPHIN_WALK_EMPTY_HAND,
			SNORKEL_WALK,
			SNORKEL_DIVE,
			SNORKEL_SWIM,
			SNORKEL_RISE,
			SNORKEL_UP,
			SNORKEL_FALL,
			SNORKEL_AQ_FOWARD,
			SNORKEL_AQ_STILL,
			SNORKEL_AQ_BACKWARD,
			SNORKEL_AQ_EAT,
			CATAPULT_ATTACK,
			CATAPULT_PREPARE,
			GARGANTUAR_THROW,
			GARGANTUAR_SMASH,
			IMP_THREW,
			IMP_LANDDING,
			BALLOON_FLY,
			BALLOON_FALL,
			BALLOON_WALK,
			LADDER_RUN,
			LADDER_PLACING,
			ZOMBOSS_ENTER,
			ZOMBOSS_UP,
			ZOMBOSS_SUMMON,
			ZOMBOSS_STEP,
			ZOMBOSS_BUNGEE_FALL,
			ZOMBOSS_BUNGEE_DOWN,
			ZOMBOSS_BUNGEE_RISE,
			ZOMBOSS_THROW,
			ZOMBOSS_FALL,
			ZOMBOSS_DOWN,
			ZOMBOSS_PREPARE_RISE,
			ZOMBOSS_BALL,
			ZOMBOSS_RISE,
			YETI_ESCAPE,
			SQUASH_WALK,
			SQUASH_RISE,
			SQUASH_FALL,
			SQUASH_SMASH
		};
		enum class MovementState :DWORD {
			NIL,
			ENTER_WATER,
			LEAVE_WATER,
			DRAGGED_UNDER,
			ENTER_HIGHLAND,
			LEAVE_HIGHLAND,
			ENTER_LADDER,
			LEAVE_LADDER,
			ENTER_CHIMNEY,
			AIRBORNE,
			AQ
		};
		enum class HelmType :DWORD {
			NIL,
			CONE,
			BUCKET,
			FOOTBALL,
			DIGGER,
			REDEYES,
			HEADBAND,
			BOBSLED,
			WALLNUT,
			TALLNUT
		};
		enum class ShieldType :DWORD {
			NIL,
			SCREEN_DOOR,
			NEWSPAPER,
			LADDER
		};
		static constexpr int WAVE_WINNER = -4;
		static constexpr int WAVE_UI = -3;
		static constexpr int WAVE_PREVIEW = -2;
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		Type type;//0024
		State state;//0028
		float x;//002C
		float y;//0030
		float v;//0034
		int noAnimShakeTime;//0038
		int sloganCountdown;//003C
		int noAnimShakeFrameTimeeating;//0040
		int noAnimShakeFrameCount;//0044
		int noAnimShakeFrameIndex;//0048
		int lastNoAnimShakeFrameIndex;//004C
		bool tongue;//0050
		bool eating;//0051
		int lastHittedCount;//0054
		int shieldHittedCount;//0058
		int shieldShakedCount;//005C
		int existTime;//0060
		MovementState movementState;//0064
		int propCountdown;//0068
		int spawnWave;//006C
		bool droppedItem;//0070
		int vanishCountdown;//0074
		bool zomboniDying;//0078
		int lastLadderCol;//007C
		int bungeeCol;//0080
		float h;//0084
		bool bungeeBlocked;//0088
		Rect defRect;//008C
		Rect atkRect;//009C
		int slowCountdown;//00AC
		int butterCountdown;//00B0
		int freezeCountdown;//00B4
		bool betray;//00B8
		bool blew;//00B9
		bool haveHead;//00BA
		bool haveArm;//00BB
		bool stage1;//00BC
		bool inWater;//00BD
		bool inHighgrid;//00BE
		bool ateGarlic;//00BF
		int ateGarlicTime;//00C0
		HelmType helmetType;//00C4
		int hp;//00C8
		int hpMax;//00CC
		int helmetHp;//00D0
		int helmetHpMax;//00D4
		ShieldType shieldType;//00D8
		int shieldHp;//00DC
		int shieldHpMax;//00E0
		int balloonHp;//00E4
		int balloonHpMax;//00E8
		bool vanished;//00EC
		ID<Zombie> mPartners[5];//00F0+04
		bool haveUniqueSample;//0104
		int particleX;//0108
		int particleY;//010C
		ID<Attachment> mAttachmentID;//0110
		int summonCountdown;//0114
		ID<Anim> mAnimId;//0118
		float size;//011C
		float dh;//0120
		float mAnimSpeed;//0124
		ID<Plant> bungeeHandPlant;//0128
		int zombossDamagedState;//012C
		int zombossOpperateRow;//0130
		int zombossHandCountdown;//0134
		int zombossFootCountdown;//0138
		int zombossHeadCountdown;//013C
		ID<Anim> zombossBall;//0140
		ID<Anim> addHead;//0144
		int zombossBallRow;//0148
		bool zombossFireBall;//014C
		ID<Anim> mowered;//0150
		int mLastPortalX;//0154
		bool isFreezedButtered() { return freezeCountdown > 0 || butterCountdown > 0; }
		bool isOnBoard() { return spawnWave != -2 && spawnWave != -3; }
		bool isDying() { return vanished || inrange(state, State::DYING, State::ASHED, State::MOWERED); }
		bool isSlowed();
		bool isStopped();
		bool isFlying() { return state == State::BALLOON_FLY || state == State::BALLOON_FALL; }
		bool isPogoJumping() { return(int)state >= (int)State::POGO_MOVE && (int)state <= (int)State::POGO_JUMP7; }
		bool isInHighgrid();
		bool isInWater();
		bool isFacingRight();
		bool isTangleTarget();
		bool canGetPlant(Plant* that, ZombieHitType atkType);
		bool isSlowable() { return type != Type::ZOMBONI && GetTeamRank() == -1 && !isDying() && !inrange(state, State::DIGGER_DIG, State::DIGGER_JUMP, State::DIGGER_DOUBT, State::DIGGER_ATTRACTED, State::CORAL_RISE, State::BACKUP_DANCER_SPAWN, State::ZOMBOSS_DOWN, State::ZOMBOSS_BALL, State::ZOMBOSS_PREPARE_RISE) && !betray; }
		bool isFreezeable() { return isSlowable() && !inrange(state, State::POLE_VAULTING_JUMP, State::DOLPHIN_DIVE, State::DOLPHIN_JUMP, State::SNORKEL_DIVE, State::IMP_THREW, State::IMP_LANDDING, State::BOBSLED_GETOFF, State::JACK_SURPRISE, State::SQUASH_RISE, State::SQUASH_FALL, State::SQUASH_SMASH, State::BUNGEE_WAIT) && !isFlying() && !isPogoJumping(); }
		bool inRange(HitRange range);
		Building* GetTargetIZBrain();
		Zombie* GetTargetZombie();
		Plant* GetTargetPlant(ZombieHitType atktype);
		void Eat(Building* that);
		void Eat(Zombie* that);
		void Eat(Plant* that);
		void StartEating();
		void StopEating();
		void Kill();
		void Update();
		void UpdateAnim();
		void SecKill();
		void Mowered();
		void Bombed();
		void BombedTeam();
		void Slowed(int t);
		void Freezed();
		void Buttered();
		void Warmed();
		void StopUniqueSample();
		void StartUniqueSample();
		void UpdateFallGround();
		void Move();
		void KillBungeePlant();
		void TryEnterChimney();
		void UpdateMain();
		void UpdateBungee();
		void UpdatePogo();
		void UpdateAnimate();
		void WaterSplash(bool in);
		void BreakIce();
		void ResetSpeed();
		void NewAttachedParticle(int x, int y, ParticleSystem::Type type);
		void AnimSetSegment(const char* name, Anim::LoopType loop, int blend, float speed = 0.0f);
		void ShowDoorArm(bool show);
		void AnimInitSpeed();
		void AnimStartWalk(int blend);
		void BreakButter();
		void UpdateRise();
		void UpdateAct();
		void UpdateMove();
		void UpdateEat();
		void UpdateEnterWater();
		void UpdateHighGridEnterLeave();
		void UpdateLeave();
		void UpdateZomboss();
		void Hitted(int hp, HitType flag);
		void SetAnimSpeed(float speed);
		void UpdateUpLadder();
		void UpdateAQ();
		void UpdateWater();
		void UpdateHighGrid();
		void UpdateDownLadder();
		void UpdateEnterChimney();
		void UpdatePole();
		void UpdateCatapult();
		void UpdateDolphin();
		void UpdateSnorkle();
		void UpdateBalloon();
		void UpdateNewspaper();
		void UpdateDigger();
		void UpdateJack();
		void UpdateGargantuar();
		void UpdateBobsled();
		void UpdateZomboni();
		void UpdateLadder();
		void UpdateYeti();
		void UpdateMJ();
		void UpdateDancer();
		void UpdateIMP();
		void UpdatePeashooter();
		void UpdateJalapeno();
		void UpdateGatling();
		void UpdateSquash();
		void UpdateSmash();
		void KillWithItem();
		void DropItem();
		float GetYBase();
		float PredictX(float time = 0.0f);
		void DieTryEndGame();
		Rect GetDefRect();
		Rect GetAtkRect();
		int GetBodyY();
		int GetClipHeight();
		ZombieDrawPosition* GetDrawPosition(ZombieDrawPosition* ans);
		void SmashGrid(int col, int row);
		int GetTeamRank();


		void Zomboss_Killball(bool fireball);
		void iztUpdate();
	};

	class PlantAttractedItem {
		using _CLASS = PlantAttractedItem;
	public:
		enum class Type :DWORD {
			NIL,
			PAIL_1,
			PAIL_2,
			PAIL_3,
			FOOTBALL_HELMET_1,
			FOOTBALL_HELMET_2,
			FOOTBALL_HELMET_3,
			DOOR_1,
			DOOR_2,
			DOOR_3,
			POGO_1,
			POGO_2,
			POGO_3,
			JACK_IN_THE_BOX,
			LADDER_1,
			LADDER_2,
			LADDER_3,
			LADDER_PLACED,
			SILVER_COIN,
			GOLD_COIN,
			DIAMOND,
			PICK_AXE
		};
		float x;
		float y;
		float xOff;
		float yOff;
		Type type;
	};

	class Plant {
		using _CLASS = Plant;
	public:
		enum class Type :DWORD {
			NIL = 0xFFFFFFFFul,
			PEASHOOTER = 0,
			SUNFLOWER,
			CHERRY_BOMB,
			WALL_NUT,
			POTATO_MINE,
			SNOW_PEA,
			CHOMPER,
			REPEATER,
			PUFF_SHROOM,
			SUN_SHROOM,
			FUME_SHROOM,
			GRAVE_BUSTER,
			HYPNO_SHROOM,
			SCAREDY_SHROOM,
			ICE_SHROOM,
			DOOM_SHROOM,
			LILY_PAD,
			SQUASH,
			THREEPEATER,
			TANGLE_KELP,
			JALAPENO,
			SPIKEWEED,
			TORCHWOOD,
			TALL_NUT,
			SEA_SHROOM,
			PLANTERN,
			CACTUS,
			BLOVER,
			SPLIT_PEA,
			STARFRUIT,
			PUMPKIN,
			MAGNET_SHROOM,
			CABBAGE_PULT,
			FLOWER_POT,
			KERNEL_PULT,
			COFFEE_BEAN,
			GARLIC,
			UMBRELLA_LEAF,
			MARIGOLD,
			MELON_PULT,
			GATLING_PEA,
			TWIN_SUNFLOWER,
			GLOOM_SHROOM,
			CATTAIL,
			WINTER_MELON,
			GOLD_MAGNET,
			SPIKEROCK,
			COB_CANNON,
			IMITATER,
			NUM_SEEDS_IN_CHOOSER,
			EXPLODING_NUT,
			GIANT_WALL_NUT,
			FLOWER_BUD,
			REPEATER_LEFT,
			__NUM_SEED_TYPES,
			__BEGHOULED_RESET,
			__BEGHOULED_CRATER,
			__SLOTMACHINE_SUN,
			__SLOTMACHINE_DIAMOND,
			__AQUARIUM_SNORKEL,
			__AQUARIUM_TROPHY,
			__ZOMBIE_NORMAL,
			__ZOMBIE_CONEHEAD,
			__ZOMBIE_POLE_VAULTER,
			__ZOMBIE_BUCKEDHEAD,
			__ZOMBIE_LADDER,
			__ZOMBIE_DIGGER,
			__ZOMBIE_BUNGEE,
			__ZOMBIE_FOOTBALL,
			__ZOMBIE_BALLOON,
			__ZOMBIE_SCREEN_DOOR,
			__ZOMBONI,
			__ZOMBIE_POGO,
			__ZOMBIE_DANCER,
			__ZOMBIE_GARGANTUAR,
			__ZOMBIE_IMP,
			ENM_BEGIN
		};
		enum class State :DWORD {
			NIL,
			READY,
			EXPLODE,
			SQUASH_LOOK,
			SQUASH_PREPARE,
			SQUASH_JUMP,
			SQUASH_FALL,
			SQUASH_SMASH,
			GRAVE_BUSTER_EAT,
			GRAVE_BUSTER_IDLE,
			CHOMPER_PREPARE,
			CHOMPER_BITE,
			CHOMPER_BITE_FAIL,
			CHOMPER_CHEW,
			CHOMPER_SWALLOW,
			POTATO_MINE_PRAPARE,
			POTATO_MINE_READY,
			POTATO_MINE_MASHED,
			SPIKEROCK_ATTACK1,
			SPIKEROCK_ATTACK2,
			SCAREDY_SHROOM_FALL,
			SCAREDY_SHROOM_DOWN,
			SCAREDY_SHROOM_UP,
			SUN_SHROOM_DOWN,
			SUN_SHROOM_RISE,
			SUN_SHROOM_UP,
			MAGNET_SHROOM_ATTRACT,
			MAGNET_SHROOM_REST,
			BOWLING_RISE,
			BOWLING_FALL,
			CACTUS_DOWN,
			CACTUS_RISE,
			CACTUS_UP,
			CACTUS_FALL,
			TANGLE_KELP_ATTACK,
			CANNON_EMPYT,
			CANNON_LOADING,
			CANNON_LOADED,
			CANNON_SHOOTING,
			KERNELPULT_BUTTER,
			UMBRELLA_RISE,
			UMBRELLA_UP,
			IMMITATER_TURNING,
			GARDEN_WATERED,
			GARDEN_NEEDY,
			GARDEN_HAPPY,
			MARIGOLD_ENDING,
			FLOWERPOT_INVULNERABLE,
			LILYPAD_INVULNERABLE
		};
		enum class BungeeProp :DWORD {
			NORMAL,
			GRABBED,
			RAISE
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		Type type;//0024
		int col;//0028
		int noAnimShakeTime;//002C
		int noAnimShakeFrameIndex;//0030
		int noAnimShakeFrameTime;//0034
		int noAnimShakeFrameCount;//0038
		State state;//003C
		int hp;//0040
		int hpMax;//0044
		bool canAttack;//0048
		int vanishCountdown;//004C
		int suicideCountdown;//0050
		int propCountdown;//0054
		union {
			int attackCountdown;//0058
			int bowlingKillAcc;//0058
		};
		int attackCD;//005C
		Rect defRect;//0060
		Rect atkRect;//0070
		int xTarget;//0080
		int yTarget;//0084
		int rowTarget;//0088
		ID<ParticleSystem> mParticleSystemID;//008C
		int shootCountdown;//0090
		ID<Anim> mAnimID;//0094
		ID<Anim> shooterHead[3];//0098+04
		ID<Anim> eye;//00A4
		ID<Anim> potatoGlow;//00A8
		ID<Anim> sleep;//00AC
		int blinkCountdown;//00B0
		int eatenCountdown;//00B4
		int flashCountdown;//00B8
		int shineCountdown;//00BC
		float mXOffset;//00C0
		float mYOffset;//00C4
		PlantAttractedItem AttractedItemProp[5];//00C8+14
		ID<Zombie> mTargetZombieID;//012C
		int wakeupCountdown;//0130
		BungeeProp bungeeProp;//0134
		Type imitaterType;//0138
		int gardenRank;//013C
		bool noAnimShakeDirection;//0140
		bool vanished;//0141
		bool smashed;//0142
		bool slept;//0143
		bool canAct;//0144
		bool shine;//0145
		bool isInYard() {return(type != Type::SQUASH || !inrange(state, State::SQUASH_JUMP, State::SQUASH_FALL, State::SQUASH_SMASH)) && !smashed && bungeeProp != BungeeProp::RAISE && !vanished;}
		bool isFlying() {return(type == Type::SQUASH && inrange(state, State::SQUASH_JUMP, State::SQUASH_FALL, State::SQUASH_SMASH)) || smashed || bungeeProp == BungeeProp::RAISE || vanished;}
		void CanonShoot(int x, int y);
		void Kill();
		void Smash();
		void Suicide();
		void Blow();
		void BurnRow();
		void FreezeYard();
		void RemoveEffects();
		void Update();
		void UpdateMain();
		void Shake();
		void UpdateVideo();
		void SetSleep(bool a);
		void UpdateAnim();
		void UpdateBowling();
		void UpdateSquash();
		void UpdateDoomshroom();
		void UpdateChomper();
		void UpdateBlover();
		void UpdateImitater();
		void UpdateCoffeeBean();
		void UpdateUmbrellaleaf();
		void UpdateCobcannon();
		void UpdateCactus();
		void UpdateMagnetshroom();
		void UpdateGoldmagnet();
		void UpdateSunshroom();
		void UpdateGravebuster();
		void UpdateTorchwood();
		void UpdatePotatomone();
		void UpdateSpike();
		void UpdateTanglekelp();
		void UpdateScardyshroom();
		void UpdateProducer();
		void UpdateAttack();
		void UpdateShine();

		void UpdateIceshroom();
		void UpdateLilypad();
		void UpdateFlowerpot();

		float GetDrawOffsetY();
		float GetDrawOffsetYDiff(float yStrech);
		float GetOnPotOffset(float basic);
		Plant* ImitaterReborn();
		Rect GetAtkRect(bool split = false);
		Rect GetDefRect();
		void DropIZRemainSun();
		HitRange GetHitRange();
		void iztUpdate();
		void MouseDown();
	};

	class GardenProp {
		using _CLASS = GardenProp;
	public:
		enum class YardType :DWORD {
			GREENHOUSE,
			MUSHROOM,
			CART,
			AQUARIUM
		};
		GameApp* mApp;
		Board* mBoard;
		YardType type;
		bool isFull(bool includeDroppedPresentd);
		bool canDropPresent();
		bool canDropChocolate();
		void UpdateMain();
		int GetX(int col, int row);
		int GetY(int col, int row);
		int GetCol(int x, int y);
		int GetRow(int x, int y);
		void NewPlant(GardenPlant* that);
		GardenPlant* GetCartPlant();
		bool isSnainBoosting();
		Building* GetSnail();
		bool canWater(Plant* p);
		bool canChocolate(Plant* p);
		void MovePlant(Plant* p, int col, int row);
		void PutCartPlantint(int col, int row);
		void Change();
	};

	class GardenPlant {
		using _CLASS = GardenPlant;
	public:
		enum class DrawVariation :DWORD {
			NORMAL,
			IMITATER,
			MARIGOLD_WHITE,
			MARIGOLD_MAGENTA,
			MARIGOLD_ORANGE,
			MARIGOLD_PINK,
			MARIGOLD_LIGHT_BLUE,
			MARIGOLD_RED,
			MARIGOLD_BLUE,
			MARIGOLD_VIOLET,
			MARIGOLD_LAVENDER,
			MARIGOLD_YELLOW,
			MARIGOLD_LIGHT_GREEN,
			ZEN_GARDEN,
			ZEN_GARDEN_WATER,
			SPROUT_NO_FLOWER,
			IMITATER_LESS,
			AQUARIUM,
			BIGIDLE
		};
		enum class State :DWORD {
			SPROUT,
			SMALL,
			MEDIUM,
			FULL
		};
		enum class Need :DWORD {
			NIL,
			WATER,
			FERTILIZER,
			BUGSPRAY,
			PHONOGRAPH
		};
		Plant::Type type;//0000
		GardenProp::YardType gardenYard;//0004
		int col;//0008
		int row;//000C
		BOOL left;//0010
		union {
			DWORD lastWateredTime;//0018
			QWORD lastWateredTime_full;//0018
		};
		DrawVariation variation;//0020
		State state;//0024
		int mTimesFed;//0028
		int mFeedingsPerGrow;//002C
		Need need;//0030
		union {
			DWORD lastShinedTime;//0038
			QWORD lastShinedTime_full;//0038
		};
		union {
			DWORD lastFertilizedTime;//0040
			QWORD lastFertilizedTime_full;//0040
		};
		union {
			DWORD lastChocolatedTime;//0048
			QWORD lastChocolatedTime_full;//0048
		};
		DWORD mFutureAttribute;//0050
		Need getNeed();
	};

	class UserData {
		using _CLASS = UserData;
	public:
		std_string name;//0000
		int mUseSeq;//001C
		int index;//0020
		int adventureLevelIndex;//0024
		int money;//0028
		int levelRecord[101];//002C+04
		int shopItemBought[80];
		int mPlayTimeActivePlayer;
		int mPlayTimeInactivePlayer;
		int mHasUsedCheatKeys;
		int mHasWokenStinky;
		int mDidntPurchasePacketUpgrade;
		int snailAteChocolateTime;
		int snailX;
		int snailY;
		int minigamePresentCollected;
		int puzzlePresentCollected;
		int minigamelNewLevel;
		int vbNewLevel;
		int izNewLevel;
		int survivalNewLevel;
		int survivalPresentCollected;
		int adventureCompletedWndShow;
		int shopNewGoods;
		int snailAwake;
		int _5;
		int _6;
		int gardenPlantCount;
		GardenPlant mGardenPlant[200];
	};

	class Bullet {
		using _CLASS = Bullet;
	public:
		enum class Type :DWORD {
			PEA,
			SNOW_PEA,
			CABBAGE,
			MELON,
			PUFF,
			SNOW_MELON,
			FIRE_PEA,
			STAR,
			SPIKE,
			ZOMBIE_BALL,
			KERNEL,
			BOMB,
			BUTTER,
			ZOMBIE_PEA,
			ENM_BEGIN
		};
		enum class MovementState :DWORD {
			DIRECT,
			PELT,
			SIDE_SHOOT,
			RIGHT_UP,
			LEFT_UP,
			SHORT,
			LEFT,
			INCLINED,
			FLOAT,
			TRACK
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		int noAnimShakeFrameIndex;//0024
		int noAnimShakeFrameTime;//0028
		int noAnimShakeTime;//002C
		float x;//0030
		float y;//0034
		float h;//0038
		float dx;//003C
		float dy;//0040
		float dh;//0044
		float ddh;//0048
		float shadowY;//004C
		bool vanished;//0050
		int noAnimShakeFrameCount;//0054
		MovementState movementState;//0058
		Type type;//005C
		int existTime;//0060
		int clickBackoffCountdown;//0064
		float rotateRad;//0068
		float rotateSpeed;//006C
		bool inHighland;//0070
		HitRange hitRange;//0074
		int lastTorchCol;//0078
		ID<Attachment> mAttachmentID;//007C
		float mTargetX;//0080
		int mTargetRow;//0084
		ID<Zombie> mTargetZombieID;//0088
		int mLastPortalX;//008C
		bool notHitHighgrid() { return movementState != MovementState::LEFT && movementState != MovementState::TRACK && inrange(type, Type::PEA, Type::SNOW_PEA, Type::STAR, Type::PUFF, Type::FIRE_PEA) && !inHighland; }
		bool isAoe(Zombie* that);
		void Update();
		void UpdatePelt();
		void UpdateNormal();
		void UpdateMain();
		bool TryTorched();
		void TryHitZombie();
		void TryHitGround();
		void Kill();
		void Hit(Zombie* that = nullptr);
		void HitAoe(Zombie* that = nullptr);
		void HitSound(Zombie* that = nullptr);
		HitType GetHitType(Zombie* that);
		Plant* GetTargetPlant();
		Zombie* GetTargetZombie();
		Zombie* GetTargetBetrayed();
		Rect GetRect();
	};

	class Card {
		using _CLASS = Card;
	public:
		enum class Type :DWORD {
			NIL = 0xFFFFFFFFul,
			PEASHOOTER = 0,
			SUNFLOWER,
			CHERRY_BOMB,
			WALL_NUT,
			POTATO_MINE,
			SNOW_PEA,
			CHOMPER,
			REPEATER,
			PUFF_SHROOM,
			SUN_SHROOM,
			FUME_SHROOM,
			GRAVE_BUSTER,
			HYPNO_SHROOM,
			SCAREDY_SHROOM,
			ICE_SHROOM,
			DOOM_SHROOM,
			LILY_PAD,
			SQUASH,
			THREEPEATER,
			TANGLE_KELP,
			JALAPENO,
			SPIKEWEED,
			TORCHWOOD,
			TALL_NUT,
			SEA_SHROOM,
			PLANTERN,
			CACTUS,
			BLOVER,
			SPLIT_PEA,
			STARFRUIT,
			PUMPKIN,
			MAGNET_SHROOM,
			CABBAGE_PULT,
			FLOWER_POT,
			KERNEL_PULT,
			COFFEE_BEAN,
			GARLIC,
			UMBRELLA_LEAF,
			MARIGOLD,
			MELON_PULT,
			GATLING_PEA,
			TWIN_SUNFLOWER,
			GLOOM_SHROOM,
			CATTAIL,
			WINTER_MELON,
			GOLD_MAGNET,
			SPIKEROCK,
			COB_CANNON,
			IMITATER,
			NUM_SEEDS_IN_CHOOSER,
			EXPLODING_NUT = NUM_SEEDS_IN_CHOOSER,
			GIANT_WALL_NUT,
			FLOWER_BUD,
			REPEATER_LEFT,
			NUM_SEED_TYPES,
			BEGHOULED_RESET,
			BEGHOULED_CRATER,
			SLOTMACHINE_SUN,
			SLOTMACHINE_DIAMOND,
			AQUARIUM_SNORKEL,
			AQUARIUM_TROPHY,
			ZOMBIE_NORMAL,
			ZOMBIE_CONEHEAD,
			ZOMBIE_POLE_VAULTER,
			ZOMBIE_BUCKEDHEAD,
			ZOMBIE_LADDER,
			ZOMBIE_DIGGER,
			ZOMBIE_BUNGEE,
			ZOMBIE_FOOTBALL,
			ZOMBIE_BALLOON,
			ZOMBIE_SCREEN_DOOR,
			ZOMBONI,
			ZOMBIE_POGO,
			ZOMBIE_DANCER,
			ZOMBIE_GARGANTUAR,
			ZOMBIE_IMP,
			ENM_BEGIN
		};
		enum class TypeGroup :DWORD {
			NIL,
			PLANT,
			ZOMBIE
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		int CDAcc;//0024
		int CDTarget;//0028
		int slotRank;//002C
		int conveyMoveCountdown;//0030
		Type type;//0034
		Type imitaterType;//0038
		int slotMachineCountdown;//003C
		Type slotMachineType;//0040
		float slotMachinePosition;//0044
		bool useable;//0048
		bool inCD;//0049
		int usedCount;//004C
		Type trueType()const { return type == Type::IMITATER ? imitaterType : type; }
		bool canPick();
		void Update();
		void Init(Type rtype, Type itype = Type::NIL);
		void Flash();
		void Active();
		void DeActive();
		void Shine();
		void SlotMachineNext();
		MouseResult GetMouseResult(int x, int y);
		void Used();
		void MouseDown();
	};

	class Item {
		using _CLASS = Item;
	public:
		enum class Type :DWORD {
			NIL,
			SILVER_COIN,
			GOLD_COIN,
			DIAMOND,
			SUN,
			SUN_SMALL,
			SUN_LARGE,
			NEW_CARD,
			TROPHY,
			SHOVEL,
			ALMANCE,
			KEY,
			BAG_COIN_AWARD,
			POT,
			TACOS,
			LETTER,
			CARD,
			PRESENT_PLANT,
			BAG_COIN,
			PRESENT_PLANT_AWARD,
			BAG_DIAMOND,
			SILVER_SUNFLOWER,
			GOLD_SUNFLOWER,
			CHOCOLATE,
			CHOCOLATE_AWARD,
			PRESENT_MINIGAME,
			PRESENT_PUZZLE,
			PRESENT_SURVIVAL,
			ENM_BEGIN
		};
		enum class MovementState :DWORD {
			FALL_QUICK,
			FALL_SLOW,
			FROM_PLANT,
			DROPPED,
			FROM_MOWER,
			FROM_PRESENT,
			FROM_BOSS
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		float x;//0024
		float y;//0028
		float dx;//002C
		float dy;//0030
		float size;//0034
		bool vanished;//0038
		int vanishCountdown;//003C
		float collectedX;//0040
		float collectedY;//0044
		int yTarget;//0048
		int existTime;//004C
		bool collected;//0050
		int vanishCount;//0054
		Type type;//0058
		MovementState movementState;//005C
		ID<Attachment> mAttachment;//0060
		float targetDistance;//0064
		Card::Type cardType;//0068
		GardenPlant mGardenPlant;//0070
		bool needArrow;//00C8
		bool haveArrow;//00C9
		bool onGround;//00CA
		int mTimesDropped;//00CC
		bool isSun() { return inrange(type, Type::SUN, Type::SUN_SMALL, Type::SUN_LARGE); }
		bool isMoney() { return inrange(type, Type::SILVER_COIN, Type::GOLD_COIN, Type::DIAMOND); }
		bool isLevelAward() { return inrange(type, Type::NEW_CARD, Type::TROPHY, Type::SILVER_SUNFLOWER, Type::GOLD_SUNFLOWER, Type::SHOVEL, Type::KEY, Type::ALMANCE, Type::BAG_COIN_AWARD, Type::POT, Type::TACOS, Type::LETTER, Type::BAG_COIN, Type::BAG_DIAMOND, Type::PRESENT_PLANT_AWARD, Type::CHOCOLATE_AWARD); }
		void Update();
		void UpdateVanish();
		void UpdateCollected();
		void UpdateFall();
		void Kill();
		void Collected();
		void MouseDown();
		void Scored();
		void PlayGroundSample();
		void PlayCollectedSample();
		void SplashConatins(Type theType, int num);
		int GetDisappearTime();
		Color GetColor();
		MouseResult GetMouseResult(int x, int y);
	};

	class Mower {
		using _CLASS = Mower;
	public:
		enum class Type :DWORD {
			LAWN,
			POOL,
			ROOF,
			SUPER_MOWER,
			ENM_BEGIN
		};
		enum class State :DWORD {
			PREPARE,
			IDLE,
			WORK,
			SMASHED
		};
		enum class MovementState :DWORD {
			LAND,
			DOWN,
			POOL,
			UP
		};
		GameApp* mApp;
		Board* mBoard;
		float x;
		float y;
		int layer;
		int row;
		DWORD mAnimTicksPerFrame;
		ID<Anim> mAnimID;
		int slowCountdown;
		int prepareCountup;
		int vanishCountdown;
		State state;
		bool vanished;
		bool visible;
		Type type;
		float h;
		MovementState movementState;
		int mLastPortalX;
		void Update();
		void UpdatePool();
		Rect GetAtkRect();
		void Smash(Zombie* that);
		void Start();
		void Kill();
	};

	class SnailInfo {
		using _CLASS = SnailInfo;
	public:
		float x;//0000
		float y;//0004
		float circulate;//0008
	};

	class Building {
		using _CLASS = Building;
	public:
		enum class Type :DWORD {
			NIL,
			GRAVE,
			CRATER,
			LADDER,
			PORTAL_WHITE,
			PORTAL_BLACK,
			BRAIN_AQ,
			VASE,
			SQUIRREL,
			USING_TOOL,
			SNAIL,
			RAKE,
			BRAIN_IZ,
			ENM_BEGIN
		};
		enum class State :DWORD {
			NIL,
			GRAVESTONE_SPECIAL,
			PORTAL_CLOSED,
			VASE_UNKNOWN,
			VASE_PLANT,
			VASE_ZOMBIE,
			SQUIRREL_WAITING,
			SQUIRREL_PEEKING,
			SQUIRREL_RUNNING_UP,
			SQUIRREL_RUNNING_DOWN,
			SQUIRREL_RUNNING_LEFT,
			SQUIRREL_RUNNING_RIGHT,
			SQUIRREL_CAUGHT,
			SQUIRREL_ZOMBIE,
			GARDENTOOL_WATERING_CAN,
			GARDENTOOL_FERTILIZER,
			GARDENTOOL_BUG_SPRAY,
			GARDENTOOL_PHONOGRAPH,
			GARDENTOOL_GOLD_WATERING_CAN,
			SNAIL_WALKING_LEFT,
			SNAIL_TURNING_LEFT,
			SNAIL_WALKING_RIGHT,
			SNAIL_TURNING_RIGHT,
			SNAIL_SLEEPING,
			SNAIL_FALLING_ASLEEP,
			SNAIL_WAKING_UP,
			RAKE_ATTRACTING,
			RAKE_WAITING,
			RAKE_TRIGGERED,
			BRAIN_SMASHED
		};
		enum class VaseContain :DWORD {
			NIL,
			PLANT,
			ZOMBIE,
			SUN
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		Type type;//0008
		State state;//000C
		int col;//0010
		int row;//0014
		int mProp;//0018
		int layer;//001C
		bool vanished;//0020
		float x;//0024
		float y;//0028
		float xTarget;//002C
		float yTarget;//0030
		ID<Anim> mAnimID;//0034
		ID<ParticleSystem> mParticleSystemID;//0038
		Zombie::Type vaseZombieType;//003C
		Plant::Type vasePlantType;//0040
		VaseContain vaseContain;//0044
		bool shine;//0048
		int mAlpha;//004C
		int vaseSunCount;//0050
		SnailInfo snailShadowInfo[12];//0054+0C
		int snailShadowCount;//00E4
		Building();
		void Kill();
		void Smash();
		void Update();
		void PortalInit();
	};

	class MouseAddProp {
		using _CLASS = MouseAddProp;
	public:
		GameApp* mApp;
		Board* mBoard;
		union {
			struct {
				int mX;
				int mY;
				int mW;
				int mH;
			};
			Rect mRect;
		};
		bool visible;
		int row;
		int layer;
		int mouseCol;
		int mouseRow;
		void Update();
	};

	class BoardText {
		using _CLASS = BoardText;
	public:
		enum class Type :DWORD {
			NIL,
			TUTORIAL_LEVEL1,
			TUTORIAL_LEVEL1_STAY,
			TUTORIAL_LEVEL2,
			TUTORIAL_LATER,
			TUTORIAL_LATER_STAY,
			HINT_LONG,
			HINT_FAST,
			HINT_STAY,
			HINT_TALL_FAST,
			HINT_TALL_UNLOCKMESSAGE,
			HINT_TALL_LONG,
			BIG_MIDDLE,
			BIG_MIDDLE_FAST,
			HOUSE_NAME,
			HUGE_WAVE,
			SLOT_MACHINE,
			ZEN_GARDEN_LONG,
			ACHIEVEMENT
		};
		GameApp* mApp;
		char text[0x80u];
		int countdownMax;
		DWORD countdown;
		int type;
		ID<Anim> mAnimID[0x80u];
		int animType;
		int leaveTime;
		char nextText[0x80u];
		int nextType;
		bool IsBeingDisplayed() { return countdown > 2; }
		void Update();
	};

	class btn {
		using _CLASS = btn;
	public:
		GameApp* mApp;
		Widget* mParent;
		Rect mRect;
		bool MouseIn;
		bool MouseDown;
		bool disabled;
		Color simColors[6];
		int mID;
		std_string mText;
		int simLabelJustify;
		Sysfont* simSysfont;
		Image* simImages[5];
		Rect simRects[4];
		bool reverse;
		bool invisible;
		bool mFrameNoDraw;
		double mAlpha;
		double mAlphaDecSpeed;
		double mAlphaIncSpeed;
		bool drawFull;
		Point<int> simTextOffset;
		Point<int> simmOffset;
		void Update();
		bool isMouseOver() { return MouseIn && !disabled && !invisible; }
	};

	class MouseText {
		using _CLASS = MouseText;
	public:
		std_string boldString;
		std_string blackString;
		std_string redString;
		Rect mRect;
		bool visible;
		bool left;
		int xMin;
		int yMax;
		int lineWidth;
		int shineClock;
	};

	class Slot {
		using _CLASS = Slot;
	public:
		GameApp* mApp;
		Board* mBoard;
		union {
			struct {
				int mX;
				int mY;
				int mW;
				int mH;
			};
			Rect mRect;
		};
		bool visible;
		int row;
		int layer;
		int SlotCount;
		Card mCards[10];
		int outofBattleColor;
		int conveyClock;
		MouseResult GetMouseResult(int x, int y);
		Rect GetPullRect();
		void Remove(int rank);
	};

	class SceneProp {
		using _CLASS = SceneProp;
		static constexpr int TimePanRightStart = 1500;
		static constexpr int TimePanRightEnd = TimePanRightStart + 2000;
		static constexpr int TimeEarlyDaveEnterStart = TimePanRightStart + 500;
		static constexpr int TimeEarlyDaveEnterEnd = TimeEarlyDaveEnterStart + 750;
		static constexpr int TimeEarlyDaveLeaveStart = TimeEarlyDaveEnterEnd + 500;
		static constexpr int TimeEarlyDaveLeaveEnd = TimeEarlyDaveLeaveStart + 750;
		static constexpr int TimeSeedChoserSlideOnStart = TimePanRightEnd + 500;
		static constexpr int TimeSeedChoserSlideOnEnd = TimeSeedChoserSlideOnStart + 250;
		static constexpr int TimeSeedChoserSlideOffStart = TimeSeedChoserSlideOnEnd + 250;
		static constexpr int TimeSeedChoserSlideOffEnd = TimeSeedChoserSlideOffStart + 250;
		static constexpr int TimeSeedBankOnStart = TimeSeedChoserSlideOnStart;
		static constexpr int TimeSeedBankOnEnd = TimeSeedChoserSlideOnEnd;
		static constexpr int TimePanLeftStart = TimeSeedChoserSlideOffStart;
		static constexpr int TimePanLeftEnd = TimePanLeftStart + 1500;
		static constexpr int TimeSeedBankRightStart = TimeSeedChoserSlideOffEnd;
		static constexpr int TimeSeedBankRightEnd = TimePanLeftEnd;
		static constexpr int TimeRollSodStart = TimePanLeftEnd;
		static constexpr int TimeRollSodEnd = TimeRollSodStart + 2000;
		static constexpr int TimeGraveStoneStart = TimePanLeftEnd;
		static constexpr int TimeGraveStoneEnd = TimeRollSodStart + 1000;
		static constexpr int TimeLawnMowerDuration = 250;
		static constexpr int TimeReadySetPlantStart = TimePanLeftEnd;
		static constexpr int TimeReadySetPlantEnd = TimeReadySetPlantStart + 1830;
		static constexpr int TimeFogRollIn = TimePanLeftEnd - 50;
		static constexpr int TimeCrazyDaveEnterStart = TimePanLeftEnd + 500;
		static constexpr int TimeCrazyDaveEnterEnd = TimeCrazyDaveEnterStart + 750;
		static constexpr int TimeCrazyDaveLeaveStart = TimeCrazyDaveEnterEnd + 500;
		static constexpr int TimeCrazyDaveLeaveEnd = TimeCrazyDaveLeaveStart + 750;
		static constexpr int TimeIntroEnd = TimeReadySetPlantStart;
		static constexpr int LostTimePanRightStart = 1500;
		static constexpr int LostTimePanRightEnd = TimePanRightStart + 2000;
		static constexpr int LostTimeBrainGraphicStart = LostTimePanRightEnd + 2500;
		static constexpr int LostTimeBrainGraphicShake = LostTimeBrainGraphicStart + 1000;
		static constexpr int LostTimeBrainGraphicCancelShake = LostTimeBrainGraphicShake + 1000;
		static constexpr int LostTimeBrainGraphicEnd = LostTimeBrainGraphicCancelShake + 3000;
		static constexpr int LostTimeEnd = LostTimeBrainGraphicEnd;
		static constexpr int TimeIntro_PresentsFadeIn = 1000;
		static constexpr int TimeIntro_LogoStart = TimeIntro_PresentsFadeIn + 4500;
		static constexpr int TimeIntro_LogoEnd = TimeIntro_LogoStart + 400;
		static constexpr int TimeIntro_PanRightStart = TimeIntro_PresentsFadeIn + 4890;
		static constexpr int TimeIntro_PanRightEnd = TimeIntro_PanRightStart + 6000;
		static constexpr int TimeIntro_FadeOut = TimeIntro_PanRightStart + 5000;
		static constexpr int TimeIntro_FadeOutEnd = TimeIntro_FadeOut + 1000;
		static constexpr int TimeIntro_End = TimeIntro_FadeOutEnd + 2000;
	public:
		GameApp* mApp;//0000
		Board* mBoard;//0004
		int sceneTime;//0008
		int sodTime;//000C
		int graveTime;//0010
		int readySetPlantTime;//0014
		int fogTime;//0018
		int bossTime;//001C
		int daveTime;//0020
		int mowerTime;//0024
		int daveTalkID;//0028
		bool seedChoosing;//002C
		ID<Anim> mAnimID;//0030
		bool visible;//0034
		bool previewZombiesGenerated;//0035
		bool prepared;//0036
		int daveCountdown;//0038
		int lastDaveTalkID;//003C
		bool battle;//0040
		SelectLevelPage* mSelectLevelPage;//0044
		bool stop;//0048
		void Update();
		bool InheritBoard();
		bool ShouldUpsell();
		void LoseClick();
		void MouseDown();
	};

	class GridPlacement {
	public:
		int x, y, col, row;
	};

	class PlantMatrix {
	public:
		Plant::Type val[9][6];
		LevelProp* mParent;
		bool CheckPossibleMove(bool twist);
		bool CheckPossibleMove(int col, int row);
		bool CheckPossibleMove(int col, int row, bool vertical);
		bool isHaveMatch();
		int GetMatchLength(int col, int row, bool vertical);
	};

	class LevelProp {
		using _CLASS = LevelProp;
	public:
		enum class State :DWORD {
			NIL,
			BEGHOULED_MOVING,
			BEGHOULED_FALLING,
			BEGHOULED_NO_MATCHES,
			SLOT_MACHINE_ROLLING,
			STORM_FLASH_1,
			STORM_FLASH_2,
			STORM_FLASH_3,
			ZEN_FADING,
			SCARY_POTTER_MALLETING,
			LAST_STAND_ONSLAUGHT,
			TREE_JUST_GREW,
			TREE_GIVE_WISDOM,
			TREE_WAITING_TO_BABBLE,
			TREE_BABBLING
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		bool dragging;//0008
		int dragX;//000C
		int dragY;//0010
		bool bejeveledCrater[9][6];//0014+01
		bool bejeveledRepeater;//004A
		bool bejeveledFumeShroom;//004B
		bool bejeveledTallNut;//004C
		int bejeveledSunDropAcc;//0050
		State state;//0054
		int mainCountdown;//0058
		int conveyCountdown;//005C
		int progress;//0060
		bool bowling;//0064
		Card::Type lastBeltCardType;//0068
		int flags;//006C
		int SlotMachineRollCount;//0070
		ID<Anim> mainAnim;//0074
		ID<Anim> _78[6];//0078+04
		ID<Anim> _90[6];//0090+04
		int col;//00A8
		int row;//00AC
		int VBRemainVaseCount;//00B0
		int rainCountdown;//00B4
		int WT_TalkID;//00B8
		bool UpdateZombieSpawn();
		void BejeveledCheckStuck();
		void UpdateCraterCard();
		bool haveCrater();
		PlantMatrix GetPlantMatrix();
		void NewPlantIZ(Plant::Type _type, int col, int row);
		void NewPlantsIZ(Plant::Type _type, int num, int row = -1);
		void NewZombie(int col, int row, Zombie::Type _type);
		void NewGrave(int col, int row);
		void UpdateEffect();
		void ClearBoard();
		void SetVBBuild();
		void SetIZBuild();
		void UpdateThunderEffect();
		void UpdateRain();
		void UpdateBelt();
		void UpdateBejeveled();
		void UpdateVB();
		void UpdateHammer();
		void UpdateIZ();
		void UpdateSlotMachine();
		void UpdateSeedRain();
		void UpdatePortal();
		void UpdateSquirrel();
		void UpdateZombieAQ();
		void UpdateWT();
		void UpdateLS();
		void IZTryAchieve(Building* brain);
		void ZombieAtePlant(Zombie* z, Plant* p);
		CardReject GetCardReject(int col, int row, Card::Type type);
		Card::Type GetGridShadow(int col, int row);
		bool MouseDown(int x, int y, int theClickCount, MouseResult mouseResult);
		MouseResult GetWTMouseResult(int x, int y);
		void IZUseCard(int col, int row);
		void BejeveledUseCard(Card& card);
		void BejeveledReset();
		void BejeveledStartFalling(State _state);
		void BejeveledCancelMatchFlashing();
		void BejeveledUpdateCraters();
		bool BejeveledHaveCrater();
		void WTChange();
	};

	class MouseProp {
		using _CLASS = MouseProp;
	public:
		enum class Type :DWORD {
			NIL,
			SLOT_CARD,
			ITEM_CARD,
			GLOVE_PLANT,
			DUPLICATOR_PLANT,
			CART_PLANT,
			SHOVEL,
			HAMMER,
			AIM,
			POT,
			FERTILIZE,
			INSECTICIDE,
			PHONOGRAPH,
			CHOCOLATE,
			GLOVE,
			SELL,
			CART,
			TREE_FERTILIZE
		};
		GameApp* mApp;//0000
		Board* mBoard;//0004
		union {
			struct {
				int mX;//0008
				int mY;//000C
				int mW;//0010
				int mH;//0014
			};
			Rect mRect;//0008
		};
		bool visible;//0018
		int row;//001C
		int layer;//0020
		int handPlantSlotRank;//0024
		Card::Type handCardType;//0028
		Card::Type handImitaterType;//002C
		Type handItemType;//0030
		ID<Item> mItemID;//0034
		ID<Plant> mPlantID;//0038
		ID<Plant> mDuplicatorID;//003C
		ID<Plant> mCobID;//0040
		int mHammerCountdown;//0044
		ID<Anim> mAnimID;//0048
		void Update();
		Card::Type trueCardType() { return handCardType == Card::Type::IMITATER ? handImitaterType : handCardType; }
	};

	class Board :public Widget {
		using _CLASS = Board;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00656CA8ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00656DC0ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		enum class GridType :DWORD {
			NIL,
			GRASS,
			DIRT,
			POOL,
			HIGHLAND
		};
		enum class SpawnType :DWORD {
			NoSpawning,
			Land,
			Water,
			Higghland
		};
		struct Yard {
			enum class Type :DWORD {
				DAY,
				NIGHT,
				POOL,
				FOG,
				ROOF,
				MOON,
				MUSHOOM_GARDEN,
				GREENHOUSE,
				AQUARIUM,
				WISDOM_TREE,
				ENM_BEGIN
			};
			Type __val;
			Yard(Type val) :__val(val) {}
			operator Type() { return __val; }
		};
		enum class Tutorial :DWORD {
			NIL,
			LEVEL1_PICK_PEASHOOTER,
			LEVEL1_PLANT_PEASHOOTER,
			LEVEL1_REFRESH_PEASHOOTER,
			LEVEL1_COMPLETED,
			LEVEL2_PICK_SUNFLOWER,
			LEVEL2_PLANT_SUNFLOWER,
			LEVEL2_REFRESH_SUNFLOWER,
			LEVEL2_COMPLETED,
			MORESUN_PICK_SUNFLOWER,
			MORESUN_PLANT_SUNFLOWER,
			MORESUN_REFRESH_SUNFLOWER,
			MORESUN_COMPLETED,
			SLOTMACHINE_PULL,
			SLOTMACHINE_COMPLETED,
			SHOVEL_PICKUP,
			SHOVEL_DIG,
			SHOVEL_KEEP_DIGGING,
			SHOVEL_COMPLETED,
			AQUARIUM_BUY_SNORKEL,
			AQUARIUM_BOUGHT_SNORKEL,
			AQUARIUM_CLICK_TROPHY,
			GARDEN_PICKUP_WATER,
			GARDEN_WATER_PLANT,
			GARDEN_KEEP_WATERING,
			GARDEN_VISIT_STORE,
			GARDEN_FERTILIZE_PLANTS,
			GARDEN_COMPLETED,
			HAMMER_BEFORE_PICK_SEED,
			HAMMER_PICK_SEED,
			HAMMER_COMPLETED
		};
		enum class AdviceType :DWORD {
			NIL = 0xFFFFFFFFul,
			CLICK_ON_SUN = 0,
			CLICKED_ON_SUN,
			CLICKED_ON_COIN,
			SEED_REFRESH,
			CANT_AFFORD_PLANT,
			PLANT_GRAVEBUSTERS_ON_GRAVES,
			PLANT_LILYPAD_ON_WATER,
			PLANT_TANGLEKELP_ON_WATER,
			PLANT_SEASHROOM_ON_WATER,
			PLANT_POTATO_MINE_ON_LILY,
			PLANT_WRONG_ART_TYPE,
			PLANT_NEED_POT,
			PLANT_NOT_ON_GRAVE,
			PLANT_NOT_ON_CRATER,
			CANT_PLANT_THERE,
			PLANT_NOT_ON_WATER,
			NEEDS_GROUND,
			BEGHOULED_DRAG_TO_MATCH_3,
			BEGHOULED_MATCH_3,
			BEGHOULED_MATCH_4,
			BEGHOULED_SAVE_SUN,
			BEGHOULED_USE_CRATER_1,
			BEGHOULED_USE_CRATER_2,
			PLANT_NOT_PASSED_LINE,
			PLANT_ONLY_ON_REPEATERS,
			PLANT_ONLY_ON_MELONPULT,
			PLANT_ONLY_ON_SUNFLOWER,
			PLANT_ONLY_ON_SPIKEWEED,
			PLANT_ONLY_ON_KERNELPULT,
			PLANT_ONLY_ON_MAGNETSHROOM,
			PLANT_ONLY_ON_FUMESHROOM,
			PLANT_ONLY_ON_LILYPAD,
			PLANT_NEEDS_REPEATER,
			PLANT_NEEDS_MELONPULT,
			PLANT_NEEDS_SUNFLOWER,
			PLANT_NEEDS_SPIKEWEED,
			PLANT_NEEDS_KERNELPULT,
			PLANT_NEEDS_MAGNETSHROOM,
			PLANT_NEEDS_FUMESHROOM,
			PLANT_NEEDS_LILYPAD,
			SLOT_MACHINE_PULL,
			HUGE_WAVE,
			SHOVEL_REFRESH,
			PORTAL_RELOCATING,
			SLOT_MACHINE_COLLECT_SUN,
			DESTROY_POTS_TO_FINISIH_LEVEL,
			USE_SHOVEL_ON_POTS,
			ALMOST_THERE,
			ZOMBIQUARIUM_CLICK_TROPHY,
			ZOMBIQUARIUM_COLLECT_SUN,
			ZOMBIQUARIUM_CLICK_TO_FEED,
			ZOMBIQUARIUM_BUY_SNORKEL,
			I_ZOMBIE_PLANTS_NOT_REAL,
			I_ZOMBIE_NOT_PASSED_LINE,
			I_ZOMBIE_LEFT_OF_LINE,
			SLOT_MACHINE_SPIN_AGAIN,
			I_ZOMBIE_EAT_ALL_BRAINS,
			PEASHOOTER_DIED,
			STINKY_SLEEPING,
			BEGHOULED_NO_MOVES,
			PLANT_SUNFLOWER5,
			NEED_SLEEPING,
			CLICK_TO_CONTINUE,
			SURVIVE_FLAGS,
			UNLOCKED_MODE,
			NEED_WHEELBARROW,
			ACHIEVEMENT_EARNED
		};
		DWORD vf_ButtonListener = vfAddr_ButtonListener;//0088
		GameApp* mApp;//008C
		StaticList<Zombie> mZombieList;//0090
		StaticList<Plant> mPlantList;//00AC
		StaticList<Bullet> mBulletList;//00C8
		StaticList<Item> mItemList;//00E4
		StaticList<Mower> mMowerList;//0100
		StaticList<Building> mBuildingList;//011C
		MouseProp* mMouseProp;//0138
		MouseAddProp* mMouseAddProp;//013C
		BoardText* mBoardText;//0140
		Slot* mSlot;//0144
		btn* btnMenu;//0148
		btn* btnStartLS;//014C
		bool mouseDisabled;//0150
		MouseText* mMouseText;//0154
		Sysfont* mSysfont;//0158
		SceneProp* mSceneProp;//015C
		LevelProp* mLevelProp;//0160
		bool pause;//0164
		GridType gridType[9][6];//0168+04
		DWORD graveShape[9][6];//0240+04
		Point<int> graveOffset[9][6];//0318+04
		DWORD fogThickness[9][7];//graveType//04C8+08
		bool graveGrow;//05C4
		Point<int> specialGraveOffset;//05C8
		float fogOffset;//05D0
		int fogCountdown;//05D4
		SpawnType rowSpawnType[6];//05D8+04
		DWORD rowMoweredWave[6];//05F0+04
		int backupMowerCount;//0608
		DWORD rowIceX[6];//060C+4
		DWORD rowIceCountdown[6];//0624+04
		DWORD rowIceParticleSystemId[6];//063C+04
		RowSpawnInfo mSpawnInfo[6];//0654+10
		Zombie::Type zombieSpawnList[0x64u][0x32u];//06B4+04
		bool zombieSpawnTypeList[0x64u];
		int sunDropCountdown;//5538
		int sunDropCount;//553C
		int shakeCountdown;//5540
		Point<int> shakeOffset;//5544
		Yard yard;//554C
		int adventureLevelRank;//5550
		int sodDrawLength;//5554
		Point<int> mousePoint;//5558
		int sunValue;//5560
		int maxWaveNum;//5564
		int timeBattle;//5568
		int timeBoard;//556C
		int continuedTime;//5570
		int levelendZombieSpawnCountdown;//5574
		int sunValueShineCountdown;//5578
		int nowwaveNum;//557C
		int refreshedWaveNum;//5580
		Tutorial tutorial;//5584
		ID<ParticleSystem> adviceArrow;//5588
		int tutorialCountdown;//558C
		int mLastBungeeWave;//5590
		int nowwaveRefreshHP;//5594
		int nowwaveFullHP;//5598
		int nextwaveSpawnCountdown;//559C
		int nextwaveSpawnCountdownMax;//55A0
		int hugewaveSpawnCountdown;//55A4
		bool ifExistBoardText;//55A8
		bool AdviceShown[0x43u];//55A9+01
		AdviceType mBoardTextType;//55EC
		bool bossKilled = 0;//55F0
		bool showShovel;//55F1
		int moneyShowCountdown;//55F4
		int debugMode;//55F8
		bool exitLevel;//55FC
		int exitLevelCountdown;//5600
		int nextLevelCountdown;//5604
		int sellMowerCountdown;//5608
		bool levelFinished;//560C
		int progressbar;//5610
		int progressbarFlagRiseCountdown;//5614
		int poolFreezeCountdown;//5618
		int levelSeed;//561C
		ID<ParticleSystem> particleSystem;//5620
		ID<Anim> fireAnim[6][0xCu];//5624
		int fireCountdown;//5744
		int glintCountdown;//5748
		bool dropppedFirstCoin;//574C
		int finalWaveSoundCountdown;//5750
		int paoSafeCountdown;//5754
		Point<int> paoSafePoint;//5758
		bool killedYeti;//5760
		bool mustache;//5761
		bool trickedout;//5762
		bool future;//5763
		bool pinata;//5764
		bool dance;//5765
		bool daisies;//5766
		bool sukhbir;//5767
		int mFinalWaveSoundCounter;//5768
		int mTriggeredLawnMowers;//576C
		int mPlayTimeActiveLevel;//5770
		int mPlayTimeInactiveLevel;//5774
		int sunflowerMaxCount;//5778
		int mStartDrawTime;//577C
		int mIntervalDrawTime;//5780
		int mIntervalDrawCountStart;//5784
		float minFPS;//5788
		int loadResouceUsedTime;//578C
		int startTime;//5790
		int ateGraveCount;//5794
		int atePlantCount;//5798
		int shovedPlantCount;//579C
		int collectedGoldcoinCount;//57A0
		int collectedDiamondCount;//57A4
		int collectedFlowerpotCount;//57A8
		int collectedChocolateCount;//57AC
		//Zombie* operator[](ID< Zombie> id){ return mZombieList[id]; }
		//Plant* operator[](ID< Plant> id){ return mPlantList[id]; }
		//Bullet* operator[](ID< Bullet> id){ return mBulletList[id]; }
		//Item* operator[](ID< Item> id){ return mItemList[id]; }
		//Mower* operator[](ID< Mower> id){ return mMowerList[id]; }
		//Building* operator[](ID< Building> id){ return mBuildingList[id]; }
		bool isLevelEnding() { return exitLevelCountdown >= 0 || nextLevelCountdown > 0 || levelFinished; }
		bool isHugeWave() { return nowwaveNum % 10 == 9; }
		bool isTeachinfBowling() { return inrange(tutorial, Tutorial::SHOVEL_PICKUP, Tutorial::SHOVEL_DIG, Tutorial::SHOVEL_KEEP_DIGGING); }
		bool isIceCovered(int col, int row) { return rowIceCountdown[row] > 0 && rowIceX[row] <= 750 && col >= GetCol(rowIceX[row] + 12, 0); }
		bool canPlantCobHelper(int col, int row);
		bool canPlantCob(int col, int row);
		bool canPlant(Card::Type type);
		int GetX(int col, int row);
		int GetY(int col, int row);
		float GetY(float x, int row);
		int GetCol(int x, int y);
		int GetRow(int x, int y);
		int GetCol(Card::Type type, int x, int y);
		int GetRow(Card::Type type, int x, int y);
		void CleanEntityNodes();
		void __thiscall v_UpdateAll(ModalFlags* theFlags);
		void __thiscall v_Update();
		void __thiscall v_MouseDown(int x, int y, int theClickCount);
		void UpdateCursor();
		void Save();
		void Load();
		void Lose(Zombie* zombie);
		void FadeOutLevel();
		void PreKill();
		Plant* NewPlant(int col, int row, Plant::Type _type, bool immitater = false);
		int GetNewZombieRow(Zombie::Type _type);
		Zombie* NewZombie(int row, Zombie::Type _type, int wave = -1);
		Building* NewCrater(int col, int row);
		Building* NewLadder(int col, int row);
		Building* NewPortal(int col, int row, bool black);
		Building* NewBrainIz(int row);
		Building* NewVase(int col, int row, Plant::Type _type, Building::State state = Building::State::VASE_UNKNOWN);
		Building* NewVase(int col, int row, Zombie::Type _type, Building::State state = Building::State::VASE_UNKNOWN);
		Building* NewVase(int col, int row, int sunnum, Building::State state = Building::State::VASE_UNKNOWN);
		Item* NewItem(int x, int y, Item::Type type, Item::MovementState movemantstate);
		void NewMower(int row);
		void SetZombieList();
		bool IfShowCursor();
		void UpdateAdvice();
		void TidyDialogList();
		void UpdateBuildings();
		void UpdateRowFire();
		void UpdateMain();
		void UpdateFog();
		void UpdateLevelEndProcess();
		void UpdateMainMain();
		int GetNoFogColNum();
		void UpdateSunDrop();
		void UpdateZombieSpawn();
		void UpdateRowIce();
		void UpdateProcessBar();
		GridPlantList GetGridPlantList(int col, int row);
		Plant* GetGridPlant(int col, int row, PlantPriority priority);
		Plant* GetGridPlant(int col, int row, Plant::Type type);
		Plant* GetGridUmbrella(int col, int row);
		Building* GetGridBuilding(int col, int row, Building::Type theType);
		Mower* GetFirstMower();
		Zombie* GetZomboss();
		Card::Type GetHandPlantType();
		CardReject GetCardReject(int col, int row, Card::Type type);
		int GetPlantCount(Plant::Type type);
		int GetCardCost(Card::Type type);
		int GetNowWaveZombieHPSum();
		void KillBoardText(AdviceType type = AdviceType::NIL);
		void SetBoardText(const std_string& advice, BoardText::Type style, AdviceType type);
		void SetTutorial(Tutorial type);
		void SetTutorialArrow(int x, int y);
		void KillBetraiedZombies();
		int GetStopMowerCount();
		void NewLastWaveZombies();
		void ShowLastWaveText();
		void ShowLevelEndWhiteText();
		void NextWaveComing();
		void SpawnWave();
		int GetCollectingSunValue();
		int GetCollectingCoinValue();
		void DropItem(int x, int y, int rate);
		int GetItemCount(Item::Type type);
		void Explode(int row, int x, int y, int r, int rowDiff, bool bomb, HitRange range);
		void Shake(int x, int y);
		void SetFire(int row);
		void iztUpdate();
		Rect GetShovelRect();
		Rect GetToolRect(MouseResult::Type tool);
		MouseResult GetMouseResult(int x, int y);
		void CannonShoot(int x, int y, int theClickCount);
		void CursorClear();
		void CursorInit();
		bool ToolExist(MouseResult::Type tool);
		MouseResult GetMouseResultPlant(int x, int y);
		MouseResult GetMouseResultSpecialPlant(int x, int y);
		void UseTool(int x, int y, int theClickCount, MouseProp::Type tool);
		void UsePlant(int x, int y, int theClickCount);
		void ThrowMouse();
		bool CardPickable(Card::Type type);
		bool CardPickableCob();
		bool CardPickableCat();
		void PickTool(MouseResult::Type tool);
	};

	class LoadingPage :public Widget {
		using _CLASS = LoadingPage;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066DD90ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x0066DEA8ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		HyperlinkWidget* mHyperlinkWidget;
		float processbarProcess;
		float processbarLength314;
		float processbarSpeed;
		float processbarLimitedSpeed;
		bool mRegisterClicked;
		bool mLoadingThreadComplete;
		int clock;
		int command;
		bool _1;
		bool _2;
		bool loading;
		bool showLoading;
		float processRate;
		int state;//0init 1logi 2plogo 3process;
		int logoCountdown;
		int logoCountdownMax;
		bool displayPartnerLogo;
		bool inTitleScreen;
		GameApp* mApp;
	};

	class MainMenu :public Widget {
		using _CLASS = MainMenu;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00665540ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00665658ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		GameApp* mApp;
		ImageButton* buttonAdventure;
		ImageButton* buttonMini;
		ImageButton* buttonPuzzle;
		ImageButton* buttonOptions;
		ImageButton* buttonQuit;
		ImageButton* buttonHelp;
		ImageButton* buttonShop;
		ImageButton* buttonAlmance;
		ImageButton* buttonGarden;
		ImageButton* buttonSurvival;
		ImageButton* buttonWelcomecard;
		MainMenu_Widget* mMainMenuWidget;
		bool willEnterAdventure;
		int enterAdventureCountdown;
		bool miniUnlocked;
		bool puzzleUnlocked;
		bool survivalUnlocked;
		bool adventureShowLevelName;
		ID<ParticleSystem> mParticleSystemID;
		ID<Anim> mAnimID;
		ID<Anim> cloudAnimID[6];
		int cloudCountdown[6];
		ID<Anim> flowersAnimID[3];
		ID<Anim> grassAnimID;
		ID<Anim> enterAdventureAnimID;
		int grassCountdown;
		int welcomecardState;
		int adventureLevelRank;
		bool loading;
		MouseText* mMouseText;
		bool showSunflowerTrophy;
		bool forceShowAllButtons;
	};

	class SelectCardWnd :public Widget {
		using _CLASS = SelectCardWnd;
	public:
		static constexpr DWORD vfAddr_WiagetContainer = 0x0066D578ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		enum class State :DWORD {
			NIL = 0,
			LAWNVIEW
		};
		btn* btnRock;
		btn* btnDebugRock;
		btn* btnViewlawn;
		btn* btnShop;
		btn* btnAlmance;
		btn* btnMenu;
		btn* btnImitater;
		SelectWndCard mCards[0x35u];
		GameApp* mApp;
		Board* mBoard;
		int mNumSeedsToChoose;
		int updateCount;
		int cardMovingCount;
		int slotCardCount;
		MouseText* mMouseText;
		int mMouseTextSpeed;
		int mouseX;
		int mouseY;
		State state;
		int viewlawnTime;
		void Rock();
		void QuitLawnView();
	};

	class NotePage :public Widget {
		using _CLASS = NotePage;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00655B90ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);

		btn* btnGo;
		btn* btnMainmenu;
		GameApp* mApp;
		int mInitBlackCountdown;
		int mType;// 1MV 2Mainmenu
	};

	class MV :public Widget {
		using _CLASS = MV;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00658168ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00658280ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		GameApp* mApp;
		int stage;
		int countdown;
		ID<Anim> mAnim;
		int _0;
		int blinkCountdown;
		DialogButton* buttonCreditsMainMenu;
		ImageButton* buttonCreditsReplay;
		MV_Widget* mMV_Widget;
		bool haveBrain;
		float brainX;
		float brainY;
		int updateCount;
		int drawCount;
		Timer mTimer;
		bool _1;
		bool pause;
		double _2;
		bool draw;
		int _3;
	};

	class SelectLevelPage :public Widget {
		using _CLASS = SelectLevelPage;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00657A18ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00657B30ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD vf_ButtonListener = vfAddr_ButtonListener;
		ImageButton* buttonBackToMenu;
		ButtonWidget* buttonPage0;
		ButtonWidget* buttonPage1;
		ButtonWidget* buttonLimboPage;
		ButtonWidget* buttonPage3;
		ButtonWidget* buttonLevel[0x48u];
		GameApp* mGameApp;
		MouseText* mMouseText;
		int nowPageIndex;
		bool showAllLevel;
		int unlockingLevelStage;
		int unlockingLevelCountdown;
		int unlockingLevelRank;
		float unlockingLevelShakeX;
		float unlockingLevelShakeY;
	};

	class ButtonWidget :public Widget {
		using _CLASS = ButtonWidget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066FB2Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfDrawButtonImage)(Graphics* g, Image* theImage, const Rect& theRect, int x, int y); void DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont); void SetFont(Font* theFont);
		static bool(__thiscall _CLASS::*& vfIsButtonDown)(void); bool IsButtonDown(void);

		int mId;
		std_string mLabel;
		int mLabelJustify;
		Font* mFont;
		Image* mButtonImage;
		Image* mOverImage;
		Image* mDownImage;
		Image* mDisabledImage;
		Rect mNormalRect;
		Rect mOverRect;
		Rect mDownRect;
		Rect mDisabledRect;
		bool mInverted;
		bool mBtnNoDraw;
		bool mFrameNoDraw;
		ButtonListener* mButtonListener;
		double mOverAlpha;
		double mOverAlphaSpeed;
		double mOverAlphaFadeInSpeed;
	};

	class CheckBox :public Widget {
		using _CLASS = CheckBox;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0067026Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetChecked)(bool checked, bool tellListener); void SetChecked(bool checked, bool tellListener = true);
		static bool(__thiscall _CLASS::*& vfIsChecked)(void); bool IsChecked(void);
		CheckboxListener* mListener;
		int mId;
		bool mChecked;
		Image* mUncheckedImage;
		Image* mCheckedImage;
		Rect mCheckedRect;
		Rect mUncheckedRect;
		Color mOutlineColor;
		Color mBkgColor;
		Color mCheckColor;
	};

	class EditWidget :public Widget {
		using _CLASS = EditWidget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00670134ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfProcessKey)(KeyCode theKey, char theChar); void ProcessKey(KeyCode theKey, char theChar);
		static void(__thiscall _CLASS::*& vfHiliteWord)(void); void HiliteWord(void);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont, Font* theWidthCheckFont); void SetFont(Font* theFont, Font* theWidthCheckFont = nullptr);
		static void(__thiscall _CLASS::*& vfSetText)(const std_string& theText, bool leftPosToZero); void SetText(const std_string& theText, bool leftPosToZero = true);
		static bool(__thiscall _CLASS::*& vfIsPartOfWord)(char chr); bool IsPartOfWord(char chr);
		static int(__thiscall _CLASS::*& vfGetCharAt)(int x, int y); int GetCharAt(int x, int y);
		static void(__thiscall _CLASS::*& vfFocusCursor)(bool bigJump); void FocusCursor(bool bigJump);

		int mId;
		std_string mString;
		std_string mPasswordDisplayString;
		Font* mFont;
		std_list<WidthCheck> mWidthCheckList;
		EditListener* mEditListener;
		bool mShowingCursor;
		bool mDrawSelOverride;
		bool mHadDoubleClick;
		int mCursorPos;
		int mHilitePos;
		int mBlinkAcc;
		int mBlinkDelay;
		int mLeftPos;
		int mMaxChars;
		int mMaxPixels;
		char mPasswordChar;
		std_string mUndoString;
		int mUndoCursor;
		int mUndoHilitePos;
		int mLastModifyIdx;
	};

	class ListWidget :public Widget {
		using _CLASS = ListWidget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066FEACul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static std_string(__thiscall _CLASS::*& vfGetSortKey)(int theIdx); std_string GetSortKey(int theIdx);
		static void(__thiscall _CLASS::*& vfSort)(bool ascending); void Sort(bool ascending);
		static std_string(__thiscall _CLASS::*& vfGetStringAt)(int theIdx); std_string GetStringAt(int theIdx);
		static int(__thiscall _CLASS::*& vfAddLine)(const std_string& theLine, bool alphabetical); int AddLine(const std_string& theLine, bool alphabetical);
		static void(__thiscall _CLASS::*& vfSetLine)(int theIdx, const std_string& theString); void SetLine(int theIdx, const std_string& theString);
		static int(__thiscall _CLASS::*& vfGetLineCount)(void); int GetLineCount(void);
		static int(__thiscall _CLASS::*& vfGetLineIdx)(const std_string& theLine); int GetLineIdx(const std_string& theLine);
		static void(__thiscall _CLASS::*& vfSetColor_0)(const std_string& theLine, const Color& theColor); void SetColor(const std_string& theLine, const Color& theColor);
		static void(__thiscall _CLASS::*& vfSetLineColor)(int theIdx, const Color& theColor); void SetLineColor(int theIdx, const Color& theColor);
		static void(__thiscall _CLASS::*& vfRemoveLine)(int theIdx); void RemoveLine(int theIdx);
		static void(__thiscall _CLASS::*& vfRemoveAll)(void); void RemoveAll(void);
		static int(__thiscall _CLASS::*& vfGetOptimalWidth)(void); int GetOptimalWidth(void);
		static int(__thiscall _CLASS::*& vfGetOptimalHeight)(void); int GetOptimalHeight(void);
		static void(__thiscall _CLASS::*& vfSetSelect)(int theSelectIdx); void SetSelect(int theSelectIdx);
		static constexpr DWORD vfAddr_ScrollListener = 0x00670000ul;
		static void(__thiscall _CLASS::*& vfScrollPosition)(int Id, double pos); void ScrollPosition(int Id, double pos);

		DWORD vf_ScrollListener = vfAddr_ScrollListener;
		int mId;
		Font* mFont;
		ScrollbarWidget* mScrollbar;
		int mJustify;
		std_vector<string> mLines;
		std_vector<Color> mLineColors;
		double mPosition;
		double mPageSize;
		int mHiliteIdx;
		int mSelectIdx;
		ListListener* mListListener;
		ListWidget* mParent;
		ListWidget* mChild;
		bool mSortFromChild;
		bool mDrawOutline;
		int mMaxNumericPlaces;
		int mItemHeight;
		bool mDrawSelectWhenHilited;
		bool mDoFingerWhenHilited;
	};

	class Slider :public Widget {
		using _CLASS = Slider;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066FD84ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetValue)(double theValue); void SetValue(double theValue);
		static bool(__thiscall _CLASS::*& vfHasTransparencies)(void); bool HasTransparencies(void);

		SliderListener* mListener;
		int _0;
		double mVal;
		int mId;
		Image* mTrackImage;
		Image* mThumbImage;
		bool mDragging;
		int mRelX;
		int mRelY;
		bool mHorizontal;
	};

	class MV_Widget :public Widget {
		using _CLASS = MV_Widget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x006582A0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);

		MV* mParent;
	};

	class MsgWidget :public Widget {
		using _CLASS = MsgWidget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00668028ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		GameApp* mApp;
		ID<Anim> mAnim;
		MsgBox* mParent;
		float mAnimX;
		float mAnimY;
	};

	class Shop_Widget :public Widget {
		using _CLASS = Shop_Widget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066DC40ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);

		Shop* mParent;
	};

	class MainMenu_Widget :public Widget {
		using _CLASS = MainMenu_Widget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00665678ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);

		MainMenu* mParent;
	};

	class MsgBox :public Dialog {
		using _CLASS = MsgBox;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00667ED0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00668008ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		GameApp* mApp;
		int buttonSetDisableCountdown;
		MsgWidget* mMsgWidget;
		bool mVisible;
		DialogButton* buttonOk;
		DialogButton* buttonCancle;
		bool bottomBig;
		bool haveEmptyLine;
	};

	class Menu :public Dialog {
		using _CLASS = Menu;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x006686B8ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static constexpr DWORD vfAddr_ButtonListener = 0x006687E8ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		static constexpr DWORD vfAddr_SliderListener = 0x00668804ul;
		static void(__thiscall _CLASS::*& vfSliderVal)(void); void SliderVal(void);
		static constexpr DWORD vfAddr_CheckboxListener = 0x00668808ul;
		static void(__thiscall _CLASS::*& vfCheckboxChecked)(void); void CheckboxChecked(void);

		DWORD vf_SliderListener = vfAddr_SliderListener;
		DWORD vf_CheckboxListener = vfAddr_CheckboxListener;
		GameApp* mApp;
		Slider* sliderMusicVolume;
		Slider* sliderSfxVolume;
		CheckBox* checkFullScreen;
		CheckBox* check3CAcc;
		DialogBtn* buttonAlmance;
		DialogBtn* buttonMainmenu;
		DialogBtn* buttonRestart;
		ImageButton* buttonBacktogame;
		bool fromMainmenu;
	};

	class Shop :public Dialog {
		using _CLASS = Shop;
	public:
		enum class ItemType :DWORD {
			NIL = 0xFFFFFFFFul,
			GATLINGPEA = 0,
			TWINSUNFLOWER,
			GLOOMSHROOM,
			CATTAIL,
			WINTERMELON,
			GOLD_MAGNET,
			SPIKEROCK,
			COBCANNON,
			IMITATER,
			BONUS_LAWN_MOWER,
			MARIGOLD_1,
			MARIGOLD_2,
			MARIGOLD_3,
			GOLD_WATERINGCAN,
			FERTILIZER,
			INSECTICIDE,
			PHONOGRAPH,
			GLOVE,
			MUSHROOMGARDEN,
			CART,
			SNAIL,
			SLOT,
			MOWER_POOL,
			MOWER_ROOF,
			RAKE,
			AQUARIUM,
			CHOCOLATE,
			WT,
			TREE_FERTILIZER,
			FIRSTAID
		};
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066DAF0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static constexpr DWORD vfAddr_ButtonListener = 0x0066DC20ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		GameApp* mApp;
		ImageButton* buttonMainMenu;
		ImageButton* buttonLeft;
		ImageButton* buttonRight;
		Shop_Widget* mShopWidget;
		int updateCount;
		std_string mBubbleText;
		int daveTalkCountdown;
		bool debugDaveTalkAll;
		int daveNextTalkCountdown;
		int daveTalkID;
		int Page;
		int PointedGoodsType;
		int closeCountdown;
		bool shouldOpen;
		int carOffX;
		int carOffY;
		int debugDaveForceTalkID;
		bool unlockAllGoods;
		bool forbidOpperate;
		GardenPlant mGardenPlant;
		StaticList<Item> mItemList;
		bool drew;
		bool willVisitWT;
		bool exited;
		bool exit;
	};

	class Almance :public MsgBox {
		using _CLASS = Almance;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x006555C0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x006556F8ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		GameApp* mApp;
		btn* btnClose;
		btn* btnBack;
		btn* btnPlant;
		btn* btnZombie;
		int mState;// 0main 1plant 2zombie
		ID<Anim> mAnim[4];
		int mSelectedPlantIndex;
		int mSelectedZombieIndex;
		Plant* mPlant;
		Zombie* mZombie;
		Zombie* mZombies[0x190u];
	};

	class ContinueLevelWnd :public MsgBox {
		using _CLASS = ContinueLevelWnd;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00657E28ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00657F60ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DialogButton* buttonContinue;
		DialogButton* buttonRestart;
	};

	class GameOverWnd :public MsgBox {
		using _CLASS = GameOverWnd;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00668140ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00668278ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DialogButton* buttonMainMenu;
	};

	class InputWindow :public MsgBox {
		using _CLASS = InputWindow;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00668840ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x00668978ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		static constexpr DWORD vfAddr_EditListener = 0x00668994ul;
		static void(__thiscall _CLASS::*& vfEditWidgetText)(int Id, const std_string& str); void EditWidgetText(int Id, const std_string& str);
		static void(__thiscall _CLASS::*& vfAllowKey)(int Id, KeyCode key); void AllowKey(int Id, KeyCode key);
		static void(__thiscall _CLASS::*& vfAllowChar)(int Id, char chr); void AllowChar(int Id, char chr);
		static void(__thiscall _CLASS::*& vfAllowText)(int Id, const std_string& txt); void AllowText(int Id, const std_string& txt);

		DWORD vf_EditListener = vfAddr_EditListener;
		GameApp* mApp;
		InputBox* mInputBox;
	};

	class ImitaterWnd :public MsgBox {
		using _CLASS = ImitaterWnd;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066D698ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x0066D7D0ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		MouseText* mMouseText;
		int pointedCardPlantType;
	};

	class WhoAreYouWnd :public MsgBox {
		using _CLASS = WhoAreYouWnd;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066E4F8ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfSetButtonFont)(Font* theFont); void SetButtonFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetHeaderFont)(Font* theFont); void SetHeaderFont(Font* theFont);
		static void(__thiscall _CLASS::*& vfSetLinesFont)(Font* theFont); void SetLinesFont(Font* theFont);
		static int(__thiscall _CLASS::*& vfGetPreferredHeight)(int width); int GetPreferredHeight(int width);
		static bool(__thiscall _CLASS::*& vfIsModal)(void); bool IsModal(void);
		static int(__thiscall _CLASS::*& vfWaitForResult)(bool autoKill); int WaitForResult(bool autoKill = true);
		static void(__thiscall _CLASS::*& vfSetButtonDisabled)(void); void SetButtonDisabled(void);
		static void(__thiscall _CLASS::*& vfmAppMouseDown)(void); void mAppMouseDown(void);
		static constexpr DWORD vfAddr_ButtonListener = 0x0066E630ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);

		DWORD* vf_ListListener;// =(DWORD*)vfAddr_ListListener;
		DWORD* vf_EditListener;// =(DWORD*)vfAddr_EditListener;
		ListWidget* mListWidget;
		DialogBtn* buttonRename;
		DialogBtn* buttonDelete;
		int mListSize;
	};

	class DialogButton :public ButtonWidget {
		using _CLASS = DialogButton;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0066FC54ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfDrawButtonImage)(Graphics* g, Image* theImage, const Rect& theRect, int x, int y); void DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont); void SetFont(Font* theFont);
		static bool(__thiscall _CLASS::*& vfIsButtonDown)(void); bool IsButtonDown(void);
		Image* mComponentImage;
		int mTranslateX;
		int mTranslateY;
		int mTextOffsetX;
		int mTextOffsetY;
	};

	class ImageButton :public ButtonWidget {
		using _CLASS = ImageButton;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00658710ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfDrawButtonImage)(Graphics* g, Image* theImage, const Rect& theRect, int x, int y); void DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont); void SetFont(Font* theFont);
		static bool(__thiscall _CLASS::*& vfIsButtonDown)(void); bool IsButtonDown(void);

		Image* mComponentImage;
		int mTranslateX;
		int mTranslateY;
		int mTextOffsetX;
		int mTextOffsetY;
		int _0;
		Point<int> mMousedownLabelOffset;
		Point<int> mImageOffset;
		bool onlyRectActive;
		std_pair<float, float> activeRect[4];
	};

	class DialogBtn :public DialogButton {
		using _CLASS = DialogBtn;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00658838ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfDrawButtonImage)(Graphics* g, Image* theImage, const Rect& theRect, int x, int y); void DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont); void SetFont(Font* theFont);
		static bool(__thiscall _CLASS::*& vfIsButtonDown)(void); bool IsButtonDown(void);

	};

	class HyperlinkWidget :public ButtonWidget {
		using _CLASS = HyperlinkWidget;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x0067000Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfDrawButtonImage)(Graphics* g, Image* theImage, const Rect& theRect, int x, int y); void DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont); void SetFont(Font* theFont);
		static bool(__thiscall _CLASS::*& vfIsButtonDown)(void); bool IsButtonDown(void);

		Rect mColor;
		Rect mOverColor;
		int mUnderlineSize;
		int mUnderlineOffset;
	};

	class ScrollbarWidget :public Widget {
		using _CLASS = ScrollbarWidget;
	public:
		DWORD* vf_ButtonListener;// =(DWORD*)vfAddr_ButtonListener;
	};

	class InputBox :public EditWidget {
		using _CLASS = InputBox;
	public:
		static constexpr DWORD vfAddr_WidgetContainer = 0x00667D70ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static Rect(__thiscall _CLASS::*& vfGetRect)(void); Rect GetRect(void);
		static bool(__thiscall _CLASS::*& vfIntersects)(WidgetContainer* theWidget); bool Intersects(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfAddWidget)(Widget* theWidget); void AddWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveWidget)(Widget* theWidget); void RemoveWidget(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfHasWidget)(Widget* theWidget); bool HasWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfDisableWidget)(Widget* theWidget); void DisableWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfRemoveAllWidgets)(bool doDelete, bool recursive); void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
		static void(__thiscall _CLASS::*& vfSetFocus)(Widget* theWidget); void SetFocus(Widget* theWidget);
		static bool(__thiscall _CLASS::*& vfIsBelow)(Widget* a, Widget* b); bool IsBelow(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfMarkAllDirty)(void); void MarkAllDirty(void);
		static void(__thiscall _CLASS::*& vfBringToFront)(Widget* theWidget); void BringToFront(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfBringToBack)(Widget* theWidget); void BringToBack(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfPutBehind)(Widget* a, Widget* b); void PutBehind(Widget* a, Widget* b);
		static void(__thiscall _CLASS::*& vfPutInfront)(Widget* a, Widget* b); void PutInfront(Widget* a, Widget* b);
		static Point<int>(__thiscall _CLASS::*& vfGetAbsPos)(void); Point<int> GetAbsPos(void);
		static void(__thiscall _CLASS::*& vfMarkDirty_0)(WidgetContainer* theWidget); void MarkDirty(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirty)(void); void MarkDirty(void);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull_0)(WidgetContainer* theWidget); void MarkDirtyFull(WidgetContainer* theWidget);
		static void(__thiscall _CLASS::*& vfMarkDirtyFull)(void); void MarkDirtyFull(void);
		static void(__thiscall _CLASS::*& vfAddedToManager)(WidgetManager* theWidgetManager); void AddedToManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfRemovedFromManager)(WidgetManager* theWidgetManager); void RemovedFromManager(WidgetManager* theWidgetManager);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static void(__thiscall _CLASS::*& vfUpdateAll)(ModalFlags* theFlags); void UpdateAll(ModalFlags* theFlags);
		static void(__thiscall _CLASS::*& vfUpdateF)(float frac); void UpdateF(float frac);
		static void(__thiscall _CLASS::*& vfUpdateFAll)(ModalFlags* theFlags, float frac); void UpdateFAll(ModalFlags* theFlags, float frac);
		static void(__thiscall _CLASS::*& vfDraw)(void); void Draw(void);
		static void(__thiscall _CLASS::*& vfDrawAll)(ModalFlags* theFlags, Graphics* g); void DrawAll(ModalFlags* theFlags, Graphics* g);
		static void(__thiscall _CLASS::*& vfSysColorChangedAll)(void); void SysColorChangedAll(void);
		static void(__thiscall _CLASS::*& vfSysColorChanged)(void); void SysColorChanged(void);
		static void(__thiscall _CLASS::*& vfOrderInManagerChanged)(void); void OrderInManagerChanged(void);
		static void(__thiscall _CLASS::*& vfSetVisible)(bool visible); void SetVisible(bool visible);
		static void(__thiscall _CLASS::*& vfSetColors)(void); void SetColors(void);
		static void(__thiscall _CLASS::*& vfSetColors_0)(void); void SetColors_0(void);
		static void(__thiscall _CLASS::*& vfSetColor)(int theIdx, const Color& theColor); void SetColor(int theIdx, const Color& theColor);
		static const Color& (__thiscall _CLASS::*& vfGetColor_0)(int theIdx); const Color& GetColor(int theIdx);
		static Color(__thiscall _CLASS::*& vfGetColor)(int theIdx, const Color& theDefaultColor); Color GetColor(int theIdx, const Color& theDefaultColor);
		static void(__thiscall _CLASS::*& vfSetDisabled)(bool disable); void SetDisabled(bool disable);
		static void(__thiscall _CLASS::*& vfShowFinger)(bool show); void ShowFinger(bool show);
		static void(__thiscall _CLASS::*& vfResize_0)(int x, int y, int w, int h); void Resize(int x, int y, int w, int h);
		static void(__thiscall _CLASS::*& vfResize)(const Rect& theRect); void Resize(const Rect& theRect);
		static void(__thiscall _CLASS::*& vfMove)(int x, int y); void Move(int x, int y);
		static bool(__thiscall _CLASS::*& vfWantsFocus)(void); bool WantsFocus(void);
		static void(__thiscall _CLASS::*& vfDrawOverlay_0)(Graphics* g, int thePriority); void DrawOverlay(Graphics* g, int thePriority);
		static void(__thiscall _CLASS::*& vfDrawOverlay)(Graphics* g); void DrawOverlay(Graphics* g);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char chr); void KeyChar(char chr);
		static void(__thiscall _CLASS::*& vfKeyDown)(KeyCode key); void KeyDown(KeyCode key);
		static void(__thiscall _CLASS::*& vfKeyUp)(KeyCode key); void KeyUp(KeyCode key);
		static void(__thiscall _CLASS::*& vfMouseEnter)(void); void MouseEnter(void);
		static void(__thiscall _CLASS::*& vfMouseLeave)(void); void MouseLeave(void);
		static void(__thiscall _CLASS::*& vfMouseMove)(int x, int y); void MouseMove(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDown_0)(int x, int y, int theBtnNum, int theClickCount); void MouseDown(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseDown)(int x, int y, int theClickCount); void MouseDown(int x, int y, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp)(int x, int y, int theBtnNum, int theClickCount); void MouseUp(int x, int y, int theBtnNum, int theClickCount);
		static void(__thiscall _CLASS::*& vfMouseUp_0)(int x, int y, int theLastDownButtonId); void MouseUp(int x, int y, int theLastDownButtonId);
		static void(__thiscall _CLASS::*& vfMouseUp_1)(int x, int y); void MouseUp(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseDrag)(int x, int y); void MouseDrag(int x, int y);
		static void(__thiscall _CLASS::*& vfMouseWheel)(int theDelta); void MouseWheel(int theDelta);
		static bool(__thiscall _CLASS::*& vfIsPointVisible)(int x, int y); bool IsPointVisible(int x, int y);
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine_0)(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset = Point<int>(1, 2));
		static Rect(__thiscall _CLASS::*& vfWriteCenteredLine)(Graphics* g, int anOffset, const std_string& theLine); Rect WriteCenteredLine(Graphics* g, int anOffset, const std_string& theLine);
		static int(__thiscall _CLASS::*& vfWriteString)(Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength); int WriteString(Graphics* g, const std_string& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
		static int(__thiscall _CLASS::*& vfWriteWordWrapped)(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification); int WriteWordWrapped(Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification);
		static int(__thiscall _CLASS::*& vfGetWordWrappedHeight)(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing); int GetWordWrappedHeight(Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing);
		static int(__thiscall _CLASS::*& vfGetNumDigits)(int theNum); int GetNumDigits(int theNum);
		static void(__thiscall _CLASS::*& vfWriteNumberFromStrip)(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing); void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
		static bool(__thiscall _CLASS::*& vfContains)(int x, int y); bool Contains(int x, int y);
		static Rect(__thiscall _CLASS::*& vfGetInsetRect)(void); Rect GetInsetRect(void);
		static void(__thiscall _CLASS::*& vfProcessKey)(KeyCode theKey, char theChar); void ProcessKey(KeyCode theKey, char theChar);
		static void(__thiscall _CLASS::*& vfHiliteWord)(void); void HiliteWord(void);
		static void(__thiscall _CLASS::*& vfSetFont)(Font* theFont, Font* theWidthCheckFont); void SetFont(Font* theFont, Font* theWidthCheckFont = nullptr);
		static void(__thiscall _CLASS::*& vfSetText)(const std_string& theText, bool leftPosToZero); void SetText(const std_string& theText, bool leftPosToZero = true);
		static bool(__thiscall _CLASS::*& vfIsPartOfWord)(char chr); bool IsPartOfWord(char chr);
		static int(__thiscall _CLASS::*& vfGetCharAt)(int x, int y); int GetCharAt(int x, int y);
		static void(__thiscall _CLASS::*& vfFocusCursor)(bool bigJump); void FocusCursor(bool bigJump);

		InputWindow* mParent;
		bool nextCharUpper;
	};

	class MusicInterface {
		using _CLASS = MusicInterface;
	public:
		static constexpr DWORD vfAddr_MusicInterface = 0x00676034ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfLoadMusic)(int theSongId, const std_string& theFileName); bool LoadMusic(int theSongId, const std_string& theFileName);
		static void(__thiscall _CLASS::*& vfPlayMusic)(int theSongId, int theOffset, bool noLoop); void PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfStopMusic)(int theSongId); void StopMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfPauseMusic)(int theSongId); void PauseMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfResumeMusic)(int theSongId); void ResumeMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfStopAllMusic)(void); void StopAllMusic(void);
		static void(__thiscall _CLASS::*& vfUnloadMusic)(int theSongId); void UnloadMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfUnloadAllMusic)(void); void UnloadAllMusic(void);
		static void(__thiscall _CLASS::*& vfPauseAllMusic)(void); void PauseAllMusic(void);
		static void(__thiscall _CLASS::*& vfResumeAllMusic)(void); void ResumeAllMusic(void);
		static void(__thiscall _CLASS::*& vfFadeIn)(int theSongId, int theOffset, double theSpeed, bool noLoop); void FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfFadeOut)(int theSongId, bool stopSong, double theSpeed); void FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfFadeOutAll)(bool stopSong, double theSpeed); void FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfSetSongVolume)(int theSongId, double theVolume); void SetSongVolume(int theSongId, double theVolume);
		static void(__thiscall _CLASS::*& vfSetSongMaxVolume)(int theSongId, double theMaxVolume); void SetSongMaxVolume(int theSongId, double theMaxVolume);
		static bool(__thiscall _CLASS::*& vfIsPlaying)(int theSongId); bool IsPlaying(int theSongId);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicAmplify)(int theSongId, double theAmp); void SetMusicAmplify(int theSongId, double theAmp);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);

		DWORD vf_MusicInterface = vfAddr_MusicInterface;
		//void SetVolume(double theVolume);
	};

	class FmodMusicInterface :public MusicInterface {
		using _CLASS = FmodMusicInterface;
	public:
		static constexpr DWORD vfAddr_MusicInterface = 0x006760E4ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfLoadMusic)(int theSongId, const std_string& theFileName); bool LoadMusic(int theSongId, const std_string& theFileName);
		static void(__thiscall _CLASS::*& vfPlayMusic)(int theSongId, int theOffset, bool noLoop); void PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfStopMusic)(int theSongId); void StopMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfPauseMusic)(int theSongId); void PauseMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfResumeMusic)(int theSongId); void ResumeMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfStopAllMusic)(void); void StopAllMusic(void);
		static void(__thiscall _CLASS::*& vfUnloadMusic)(int theSongId); void UnloadMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfUnloadAllMusic)(void); void UnloadAllMusic(void);
		static void(__thiscall _CLASS::*& vfPauseAllMusic)(void); void PauseAllMusic(void);
		static void(__thiscall _CLASS::*& vfResumeAllMusic)(void); void ResumeAllMusic(void);
		static void(__thiscall _CLASS::*& vfFadeIn)(int theSongId, int theOffset, double theSpeed, bool noLoop); void FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfFadeOut)(int theSongId, bool stopSong, double theSpeed); void FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfFadeOutAll)(bool stopSong, double theSpeed); void FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfSetSongVolume)(int theSongId, double theVolume); void SetSongVolume(int theSongId, double theVolume);
		static void(__thiscall _CLASS::*& vfSetSongMaxVolume)(int theSongId, double theMaxVolume); void SetSongMaxVolume(int theSongId, double theMaxVolume);
		static bool(__thiscall _CLASS::*& vfIsPlaying)(int theSongId); bool IsPlaying(int theSongId);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicAmplify)(int theSongId, double theAmp); void SetMusicAmplify(int theSongId, double theAmp);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);
		static bool(__thiscall _CLASS::*& vfLoadSample_0)(int theSongId, const std_string& theIntroFileName, const std_string& theRepeatFileName, bool repeat); bool LoadSample(int theSongId, const std_string& theIntroFileName, const std_string& theRepeatFileName, bool repeat);
		static bool(__thiscall _CLASS::*& vfLoadSample)(int theSongId, const std_string& theFileName, bool repeat); bool LoadSample(int theSongId, const std_string& theFileName, bool repeat);

		DWORD vf_MusicInterface = vfAddr_MusicInterface;
		std_map<int, FmodMusicInfo> mMusicMap;
		double mMasterVolume;
		int mMaxMusicVolume;
		int mMaxSampleVolume;
	};

	class FmodMusicInfo {
		using _CLASS = FmodMusicInfo;
	public:
		LPVOID mHSample;
		LPVOID mHMusic;
		double mVolume;
		double mVolumeAdd;
		double mVolumeCap;
		bool mStopOnFade;
		bool mRepeats;
	};

	class BassMusicInterface :public MusicInterface {
		using _CLASS = BassMusicInterface;
	public:
		static constexpr DWORD vfAddr_MusicInterface = 0x0067608Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfLoadMusic)(int theSongId, const std_string& theFileName); bool LoadMusic(int theSongId, const std_string& theFileName);
		static void(__thiscall _CLASS::*& vfPlayMusic)(int theSongId, int theOffset, bool noLoop); void PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfStopMusic)(int theSongId); void StopMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfPauseMusic)(int theSongId); void PauseMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfResumeMusic)(int theSongId); void ResumeMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfStopAllMusic)(void); void StopAllMusic(void);
		static void(__thiscall _CLASS::*& vfUnloadMusic)(int theSongId); void UnloadMusic(int theSongId);
		static void(__thiscall _CLASS::*& vfUnloadAllMusic)(void); void UnloadAllMusic(void);
		static void(__thiscall _CLASS::*& vfPauseAllMusic)(void); void PauseAllMusic(void);
		static void(__thiscall _CLASS::*& vfResumeAllMusic)(void); void ResumeAllMusic(void);
		static void(__thiscall _CLASS::*& vfFadeIn)(int theSongId, int theOffset, double theSpeed, bool noLoop); void FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		static void(__thiscall _CLASS::*& vfFadeOut)(int theSongId, bool stopSong, double theSpeed); void FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfFadeOutAll)(bool stopSong, double theSpeed); void FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		static void(__thiscall _CLASS::*& vfSetSongVolume)(int theSongId, double theVolume); void SetSongVolume(int theSongId, double theVolume);
		static void(__thiscall _CLASS::*& vfSetSongMaxVolume)(int theSongId, double theMaxVolume); void SetSongMaxVolume(int theSongId, double theMaxVolume);
		static bool(__thiscall _CLASS::*& vfIsPlaying)(int theSongId); bool IsPlaying(int theSongId);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicAmplify)(int theSongId, double theAmp); void SetMusicAmplify(int theSongId, double theAmp);
		static void(__thiscall _CLASS::*& vfUpdate)(void); void Update(void);

		DWORD vf_MusicInterface = vfAddr_MusicInterface;
		std_map<int, BassMusicInfo> mMusicMap;
		int mMaxMusicVolume;
		int mMusicLoadFlags;
		//void SetVolume(double theVolume);
	};

	class BassMusicInfo {
		using _CLASS = BassMusicInfo;
	public:
		int mHMusic;
		int mHStream;
		double mVolume;
		double mVolumeAdd;
		double mVolumeCap;
		bool mStopOnFade;
	};

	class Bgm {
		using _CLASS = Bgm;
	public:
		enum class Type :DWORD {
			NIL = 0xFFFFFFFFul,
			DAY_GRASSWALK = 1,
			NIGHT_MOONGRAINS,
			POOL_WATERYGRAVES,
			FOG_RIGORMORMIST,
			ROOF_GRAZETHEROOF,
			CHOOSE_YOUR_SEEDS,
			TITLE_CRAZY_DAVE_MAIN_THEME,
			PUZZLE_CEREBRAWL,
			MINIGAME_LOONBOON,
			CONVEYER,
			FINAL_BOSS_BRAINIAC_MANIAC,
			ZEN_GARDEN,
			NUM_MUSIC_TUNES
		};
		GameApp* mApp;
		MusicInterface* mMusicInterface;
		Type type;
		int track;
		int track1;
		int track2;
		int effectType;
		int BPM;
		int ticksPerRow;
		int BurstStage;//0no 1rise 2up 3down
		int BurstCountdown;
		int DrumsType;
		int MusicOrder1;
		int DrumsCountdown;
		WORD MusicOrder;
		WORD MusicRow;
		WORD DrumOrder;
		WORD DrumRow;
		bool pause;
		int countdown;
		int weakenTime;
		void Update();
		void Burst();
	};

	class D3DInterface {
		using _CLASS = D3DInterface;
	public:
		static constexpr DWORD vfAddr_D3DInterface = 0x00672534ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);

		DWORD vf_D3DInterface = vfAddr_D3DInterface;
		HWND mHWnd;
		int mWidth;
		int mHeight;
		IDirectDraw7* mDD;
		IDirectDrawSurface7* mDDSDrawSurface;
		IDirectDrawSurface7* mZBuffer;
		IDirect3D7* mD3D;
		IDirect3DDevice7* mD3DDevice;
		D3DVIEWPORT7 mD3DViewport;
		bool mSceneBegun;
		bool mIsWindowed;
		std_set<MemoryImage*> mImageSet;
		std_list<Matrix3> mTransformStack;
		std_string& mErrorString();
		void BltTransformed(DDImage* theImage, const Color& theColor, const Rect& theSrcRect, const Matrix3& theTransform);
		void Flush();
		bool CreateImageTexture(const DDImage* theImage);
		bool PreDraw();
	};

	class D3DTestImage {
		using _CLASS = D3DTestImage;
	public:
		static constexpr DWORD vfAddr_D3DTestImage = 0x00672588ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_D3DTestImage = vfAddr_D3DTestImage;
		DWORD* mBits;
		int mWidth;
		int mHeight;
	};

	class D3DTester {
		using _CLASS = D3DTester;
	public:
		static constexpr DWORD vfAddr_D3DTester = 0x0067253Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);

		DWORD vf_D3DTester = vfAddr_D3DTester;
		int mDD7;
		int mPrimarySurface;
		int mTextureSurface;
		int mTextureSurface2;
		int mD3D7;
		int mD3DDevice7;
		HKEY mRegKey;
		GUID mDisplayGUID;
		std_string mDisplayDriver;
		std_string mDisplayDescription;
		D3DTestImage mTestImage;
		std_string mFailureReason;
		std_string mWarning;
		int mMinVidMemory;
		int mRecommendedVidMemory;
		bool mCheckRegistry;
		bool mShouldWriteToRegistry;
		bool mResultsChanged;
		int mDriverYear;
	};

	class Font {
		using _CLASS = Font;
	public:
		static constexpr DWORD vfAddr_Font = 0x0067259Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static int(__thiscall _CLASS::*& vfGetAscent)(void); int GetAscent(void);
		static int(__thiscall _CLASS::*& vfGetAscentPadding)(void); int GetAscentPadding(void);
		static int(__thiscall _CLASS::*& vfGetDescent)(void); int GetDescent(void);
		static int(__thiscall _CLASS::*& vfGetHeight)(void); int GetHeight(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacingOffset)(void); int GetLineSpacingOffset(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacing)(void); int GetLineSpacing(void);
		static int(__thiscall _CLASS::*& vfStringWidth)(const std_string& str); int StringWidth(const std_string& str);
		static int(__thiscall _CLASS::*& vfCharWidth)(char chr); int CharWidth(char chr);
		static int(__thiscall _CLASS::*& vfCharWidthKern)(char chr, char prev); int CharWidthKern(char chr, char prev);
		static void(__thiscall _CLASS::*& vfDrawString)(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect); void DrawString(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect);
		static Font* (__thiscall _CLASS::*& vfDuplicate)(void); Font* Duplicate(void);

		DWORD vf_Font = vfAddr_Font;
		int mAscent;
		int mAscentPadding;
		int mHeight;
		int mLineSpacingOffset;
	};

	class mState {
		using _CLASS = mState;
	public:
		Image* mDestImage;
		float mTransX;
		float mTransY;
		float mScaleX;
		float mScaleY;
		float mScaleOrigX;
		float mScaleOrigY;
		Rect mClipRect;
		Color mColor;
		Font* mFont;
		int mDrawMode;
		bool mColorizeImages;
		bool mFastStretch;
		bool mWriteColoredString;
		bool mLinearBlend;
		bool mIs3D;
		Image& mStaticImage();
	};

	class Graphics {
		using _CLASS = Graphics;
	public:
		static constexpr DWORD vfAddr_Graphics = 0x0067254Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_Graphics = vfAddr_Graphics;
		Image* mDestImage;
		float mTransX;
		float mTransY;
		float mScaleX;
		float mScaleY;
		float mScaleOrigX;
		float mScaleOrigY;
		Rect mClipRect;
		Color mColor;
		Font* mFont;
		int mDrawMode;
		bool mColorizeImages;
		bool mFastStretch;
		bool mWriteColoredString;
		bool mLinearBlend;
		bool mIs3D;
		Edge* mPFActiveEdgeList;
		int mPFNumActiveEdges;
		int mPFNumVertices;
		std_list<mState> mStateStack;
		static Graphics* New(const Graphics& theGraphics);
		static Graphics* New(Image* theDestImage = nullptr);
		void CopyStateFrom(const Graphics* theState);
		void Translate(int theTransX, int theTransY);
		void SetFastStretch(bool fastStretch);
		void SetLinearBlend(bool linear);
		void PushState();
		void PopState();
		mState mmState();
		void ClipRect(int theX, int theY, int theWidth, int theHeight);
		void DrawImage(Image* theImage, int theX, int theY);
		enum {
			DRAWMODE_NORMAL,
			DRAWMODE_ADDITIVE
		};
	};

	class MImgStruct {
		using _CLASS = MImgStruct;
	public:
		DWORD* mCausticGrayscaleImage;
		MemoryImage* MemoryImage;
		GameApp* mApp;
		int mPoolCounter;
	};

	class PopcapMsg {
		using _CLASS = PopcapMsg;
	public:
		int _0;
		int _1;
		int _2;
		int _3;
		bool wndExist;
		int _5;
		int _6;
		int _7;
		int _8;
		int _9;
		int _A;
		int _B;
		int _C;
		int _D;
		int _E;
		int _F;
		int _G;
		int _H;
		CritSect mCriticalSection;
	};

	class XMLElement {
	public:
		enum class Type {
			TYPE_NONE,
			TYPE_START,
			TYPE_END,
			TYPE_ELEMENT,
			TYPE_INSTRUCTION,
			TYPE_COMMENT
		};
		Type					mType;
		std_string				mSection;
		std_string				mValue;
		std_string				mInstruction;
		std_map<std_string, std_string>				mAttributes;
		std_list<std_map<std_string, std_string>::iterator>	mAttributeIteratorList;
	};

	class ResourceManager {
		using _CLASS = ResourceManager;
	public:
		static constexpr DWORD vfAddr_ResourceManager = 0x00675314ul;
		static bool(__thiscall _CLASS::*& vfParseCommonResource)(XMLElement& theElement, BaseRes* theRes, std_map<std::string, BaseRes*>& theMap); bool ParseCommonResource(XMLElement& theElement, BaseRes* theRes, std_map<std::string, BaseRes*>& theMap);
		static bool(__thiscall _CLASS::*& vfParseSoundResource)(XMLElement& theElement); bool ParseSoundResource(XMLElement& theElement);
		static bool(__thiscall _CLASS::*& vfParseImageResource)(XMLElement& theElement); bool ParseImageResource(XMLElement& theElement);
		static bool(__thiscall _CLASS::*& vfParseFontResource)(XMLElement& theElement); bool ParseFontResource(XMLElement& theElement);
		static bool(__thiscall _CLASS::*& vfParseSetDefaults)(XMLElement& theElement); bool ParseSetDefaults(XMLElement& theElement);
		static bool(__thiscall _CLASS::*& vfParseResources)(void); bool ParseResources(void);
		static void(__thiscall _CLASS::*& vfDeleteResources)(void); void DeleteResources(void);
		static void(__thiscall _CLASS::*& vfDeleteResources_0)(void); void DeleteResources_0(void);
		static bool(__thiscall _CLASS::*& vfDoLoadImage)(ImageRes* theRes); bool DoLoadImage(ImageRes* theRes);
		static bool(__thiscall _CLASS::*& vfDoLoadFont)(FontRes* theRes); bool DoLoadFont(FontRes* theRes);
		static bool(__thiscall _CLASS::*& vfDoLoadSound)(SoundRes* theRes); bool DoLoadSound(SoundRes* theRes);
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfLoadNextResource)(void); bool LoadNextResource(void);
		static void(__thiscall _CLASS::*& vfResourceLoadedHook)(BaseRes* theRes); void ResourceLoadedHook(BaseRes* theRes);
		static void(__thiscall _CLASS::*& vfStartLoadResources)(const std_string& theGroup); void StartLoadResources(const std_string& theGroup);
		static bool(__thiscall _CLASS::*& vfLoadResources)(const std_string& theGroup); bool LoadResources(const std_string& theGroup);
		static SharedImageRef(__thiscall _CLASS::*& vfGetImageThrow)(const std_string& theId); SharedImageRef GetImageThrow(const std_string& theId);
		static int(__thiscall _CLASS::*& vfGetSoundThrow)(const std_string& theId); int GetSoundThrow(const std_string& theId);
		static Font* (__thiscall _CLASS::*& vfGetFontThrow)(const std_string& theId); Font* GetFontThrow(const std_string& theId);

		DWORD vf_ResourceManager = vfAddr_ResourceManager;
		std_set<std_string> mLoadedGroups;
		std_map<std_string, BaseRes*>mImageMap;
		std_map<std_string, BaseRes*>mSoundMap;
		std_map<std_string, BaseRes*>mFontMap;
		XMLParser* mXMLParser;
		std_string mError;
		bool mHasFailed;
		SexyAppBase* mApp;
		std_string mCurResGroup;
		std_string mDefaultPath;
		std_string mDefaultIdPrefix;
		bool mAllowMissingProgramResources;
		bool mAllowAlreadyDefinedResources;
		bool mHadAlreadyDefinedError;
		std_map<std_string, std_list<BaseRes*>>mResGroupMap;
		std_list<BaseRes*>* mCurResGroupList;
		DWORD _iteratorAllocator;
		std_list<BaseRes*>::iterator mCurResGroupListItr;
		bool LoadGroup(const std_string& group);
	};

	class SharedImageRef {
		using _CLASS = SharedImageRef;
	public:
		SharedImage* mSharedImage;
		MemoryImage* mUnsharedImage;
		bool mOwnsUnshared;
	};

	class BaseRes {
		using _CLASS = BaseRes;
	public:
		static constexpr DWORD vfAddr_BaseRes = 0x00675388ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_BaseRes = vfAddr_BaseRes;
		int mType;
		std_string mId;
		std_string mResGroup;
		std_string mPath;
		std_map<std_string, std_string>mXMLAttributes;
		bool mFromProgram;
	};

	class FontRes :public BaseRes {
		using _CLASS = FontRes;
	public:
		static constexpr DWORD vfAddr_BaseRes = 0x006753ACul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		Font* mFont;
		Image* mImage;
		std_string mImagePath;
		std_string mTags;
		bool mSysFont;
		bool mBold;
		bool mItalic;
		bool mUnderline;
		bool mShadow;
		int mSize;
	};

	class ImageRes :public BaseRes {
		using _CLASS = ImageRes;
	public:
		static constexpr DWORD vfAddr_BaseRes = 0x00675394ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		SharedImageRef mImage;
		std_string mAlphaImage;
		std_string mAlphaGridImage;
		std_string mVariant;
		bool mAutoFindAlpha;
		bool mPalletize;
		bool mA4R4G4B4;
		bool mA8R8G8B8;
		bool mDDSurface;
		bool mPurgeBits;
		bool mMinimizeSubdivisions;
		int mRows;
		int mCols;
		int mAlphaColor;
		AnimInfo mAnimInfo;
	};

	class SoundRes :public BaseRes {
		using _CLASS = SoundRes;
	public:
		static constexpr DWORD vfAddr_BaseRes = 0x006753A0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		int mSoundId;
		double mVolume;
		int mPanning;
	};

	class Sample {
		using _CLASS = Sample;
	public:
		enum class Type :DWORD {
			ITEM_SUN_COLLECT,
			SPLAT,
			MOWER_ACT,
			BULLET_PEA_INIT,
			ITEM_SUN_INIT,
			ZOMBIE_BITE1,
			ZOMBIE_BITE2,
			PLANT_INIT,
			PLANT_REMOVE,
			DROP,
			BUTTON_MAINMENU_MOUSEENTER,//10
			ZOMBIE_CRY_NORMAL,
			ZOMBIE_CRY_TONGUE,
			ZOMBIE_CRY_SUKHBIR,
			ZOMBIE_JACK_MUSIC_BOX,
			SUCCEED,
			ZOMBIE_ZOMBONY_INIT,
			THUNDER,
			ZOMBIE_FREEZED,
			ZOMBIE_ENTER_WATER,
			BOWLING_COLLISION,//20
			PLANT_SMASHED,
			ZOMBIE_EXPLODE1,
			ZOMBIE_EXPLODE2,
			ZOMBIE_AQ_SWALLOW,
			MAINMENU_DIASES_DROP,
			ZOMBIE_POGO_BOUNCE,
			SNOW_BULLET_INIT,//
			ZOMBIE_FALL_GROUND,
			BULLET_PUFF_INIT,
			BULLET_FUME_INIT,//30
			ITEM_COIN_COLLECT,
			BULLET_KERNEL_HIT,
			ZOMBIE_DIGGER_DIG,
			ZOMBIE_JACK_CRY,
			BUILDING_VASE_BREAK,
			MOWER_ACT_WATER,
			ZOMBIE_CATAPULT_SHOOT,
			BULLET_FIREBALL_HIT,
			BULLET_FIRABALL_INIT,
			ZOMBIE_GARGANTUAR_KNOCK,//40
			PLANT_SQUASH_SEE,
			PLANT_MAGNETSHROOM_ATTRACT,
			BULLET_BUTTER_HIT,
			ZOMBIE_BUNGEE_INIT,
			ZOMBIE_EXPLODE3,
			BULLET_HIT_IRON,
			HAMMER_WAVING,
			HAMMER_HIT,
			RAIN,
			ZOMBIE_DOLPHIN_JUMP,//50
			ZOMBIE_DOLPHIN_INIT,
			PLANT_IN_WATER,
			ZOMBIE_JUMP_WATER,
			PLANT_GRAVEBUSTER_EAT,
			PLANT_CHERRYBOMB_EXPLODE,
			PLANT_JALAPENO_EXPLODE,
			PLANT_EXPLODE_PREPARE,
			BULLET_HIT_CONE,
			LEVEL_CLEAR,
			ZOMBIE_BALLOON_INIT,//60
			PLANT_CHOMPER_BITE,
			BULLET_MELON_HIT,
			PLANT_GROW,
			SHOOP,
			SUICIDE,
			ZOMBIE_NEWSPAPER_ANGRY,
			__67,
			BEJEVELED_FAIL,
			PLANT_CRUMBLE,
			ZOMBIE_CRY_GARGANTUAR,//70
			ITEM_PRESENT_COLLECT,
			ZOMBIE_EAT_GARLIC,
			PLANT_UMBRELLA_RISE,
			ZOMBIE_POLE_STARTJUMP,
			HAND_SHOVEL_RELEASE,
			PLANT_CANNON_SHOOT,
			BUILDING_POT_INIT,
			ZOMBIE_POLE_JUMP,
			OUT_OF_SOIL1,
			OUT_OF_SOIL2,//80
			BUILDING_FERTILIZE_INIT,
			BUILDING_PORTAL_INIT,
			PLANT_WAKE,
			BUILDING_INSECTICIDE_INIT,
			PLAYER_CRY_NO,
			NOTEPAGE_INIT,
			ITEM_COIN_FALL_GROUND,
			ZOMBIE_IMP_INIT,
			ZOMBOSS_MACHINE,
			ZOMBOSS_MACHINE2,//90
			ZOMBIE_GARGANTUAR_CRY,
			HAND_CARTPLANT_PLACE_GARDEN,
			ZOMBOSS_BALL_INIT,
			ITEM_DIAMOND_INIT,
			DAVE_CRY1,
			DAVE_CRY2,
			DAVE_CRY3,
			DAVE_CRY4,
			BUILDING_PHONOGRAPH_INIT,
			ZOMBIE_MJ_INIT,//100
			LEVEL_CLEAR_ALL,
			DAVE_CRY5,
			DAVE_CRY6
		};
		SoundInstance* mSoundInstance;
		int mRefCount;
		bool paused;
		int mStartTime;
		int mPauseOffset;

	};

	class SampleInfo {
	public:
		Sample::Type type;
		float speed;
		int mSfxID[10];
		DWORD flags;
	};

	class SampleManager {
		using _CLASS = SampleManager;
	public:
		Sample mSamples[8];
		int lastSampleType;
		void NewSampleF(Sample::Type type, float speed);
		void NewSample(Sample::Type type);
		void StopSample(Sample::Type _type);
	};

	class AnimsLists {
		using _CLASS = AnimsLists;
	public:
		ParticlesLists* mParticlesLists;
		StaticList<Trail>* mTrailList;
		StaticList<Anim>* mAnimList;
		StaticList<Attachment>* mAttachmentList;
		void CleanNodes();
		void Update();
	};

	class ParticlesLists {
		using _CLASS = ParticlesLists;
	public:
		StaticList<ParticleSystem> mParticleSystemList;
		StaticList<Emitter> mEmitterList;
		StaticList<Particle> mParticleList;
		SNodeStack<ID<Emitter>> mEmitterNodeStack;
		SNodeStack<ID<Particle>> mParticleNodeStack;
	};

	class GameApp :public SexyApp {
		using _CLASS = GameApp;
	public:
		static constexpr DWORD vfAddr_ButtonListener = 0x00667BA0ul;
		static void(__thiscall _CLASS::*& vfButtonPress_0)(int mouse, int count); void ButtonPress(int mouse, int count);
		static void(__thiscall _CLASS::*& vfButtonPress)(int mouse); void ButtonPress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDepress)(int mouse); void ButtonDepress(int mouse);
		static void(__thiscall _CLASS::*& vfButtonDownTick)(int mouse); void ButtonDownTick(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseEnter)(int mouse); void ButtonMouseEnter(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseLeave)(int mouse); void ButtonMouseLeave(int mouse);
		static void(__thiscall _CLASS::*& vfButtonMouseMove)(int mouse, int x, int y); void ButtonMouseMove(int mouse, int x, int y);
		static bool(__thiscall _CLASS::*& vfProcess)(bool allowSleep); bool Process(bool allowSleep = true);
		static void(__thiscall _CLASS::*& vfUpdateFrames)(void); void UpdateFrames(void);
		static bool(__thiscall _CLASS::*& vfDoUpdateFrames)(void); bool DoUpdateFrames(void);
		static void(__thiscall _CLASS::*& vfDoUpdateFramesF)(float theFrac); void DoUpdateFramesF(float theFrac);
		static void(__thiscall _CLASS::*& vfMakeWindow)(void); void MakeWindow(void);
		static void(__thiscall _CLASS::*& vfEnforceCursor)(void); void EnforceCursor(void);
		static void(__thiscall _CLASS::*& vfReInitImages)(void); void ReInitImages(void);
		static void(__thiscall _CLASS::*& vfDeleteNativeImageData)(void); void DeleteNativeImageData(void);
		static void(__thiscall _CLASS::*& vfDeleteExtraImageData)(void); void DeleteExtraImageData(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadCompleted)(void); void LoadingThreadCompleted(void);
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static MusicInterface* (__thiscall _CLASS::*& vfCreateMusicInterface)(HWND hwnd); MusicInterface* CreateMusicInterface(HWND hwnd);
		static void(__thiscall _CLASS::*& vfInitHook)(void); void InitHook(void);
		static void(__thiscall _CLASS::*& vfShutdownHook)(void); void ShutdownHook(void);
		static void(__thiscall _CLASS::*& vfPreTerminate)(void); void PreTerminate(void);
		static void(__thiscall _CLASS::*& vfLoadingThreadProc)(void); void LoadingThreadProc(void);
		static void(__thiscall _CLASS::*& vfWriteToRegistry)(void); void WriteToRegistry(void);
		static void(__thiscall _CLASS::*& vfReadFromRegistry)(void); void ReadFromRegistry(void);
		static Dialog* (__thiscall _CLASS::*& vfNewDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* NewDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static void(__thiscall _CLASS::*& vfPreDisplayHook)(void); void PreDisplayHook(void);
		static void(__thiscall _CLASS::*& vfBeginPopup)(void); void BeginPopup(void);
		static void(__thiscall _CLASS::*& vfEndPopup)(void); void EndPopup(void);
		static void(__thiscall _CLASS::*& vfMsgBox_0)(void); void MsgBox_0(void);
		static void(__thiscall _CLASS::*& vfMsgBox)(void); void MsgBox(void);
		static void(__thiscall _CLASS::*& vfPopup_0)(void); void Popup_0(void);
		static void(__thiscall _CLASS::*& vfPopup)(void); void Popup(void);
		static void(__thiscall _CLASS::*& vfLogScreenSaverError)(const std_string& theError); void LogScreenSaverError(const std_string& theError);
		static void(__thiscall _CLASS::*& vfSafeDeleteWidget)(Widget* theWidget); void SafeDeleteWidget(Widget* theWidget);
		static void(__thiscall _CLASS::*& vfURLOpenFailed)(const std_string& theURL); void URLOpenFailed(const std_string& theURL);
		static void(__thiscall _CLASS::*& vfURLOpenSucceeded)(const std_string& theURL); void URLOpenSucceeded(const std_string& theURL);
		static bool(__thiscall _CLASS::*& vfOpenURL)(const std_string& theURL, bool shutdownOnOpen); bool OpenURL(const std_string& theURL, bool shutdownOnOpen = false);
		static std_string(__thiscall _CLASS::*& vfGetProductVersion)(const std_string& thePath); std_string GetProductVersion(const std_string& thePath);
		static void(__thiscall _CLASS::*& vfSEHOccured)(void); void SEHOccured(void);
		static std_string(__thiscall _CLASS::*& vfGetGameSEHInfo)(void); std_string GetGameSEHInfo(void);
		static void(__thiscall _CLASS::*& vfGetSEHWebParams)(std_map<std::string, std::string>* theDefinesMap); void GetSEHWebParams(std_map<std::string, std::string>* theDefinesMap);
		static void(__thiscall _CLASS::*& vfShutdown)(void); void Shutdown(void);
		static void(__thiscall _CLASS::*& vfDoParseCmdLine)(void); void DoParseCmdLine(void);
		static void(__thiscall _CLASS::*& vfParseCmdLine)(const std_string& theCmdLine); void ParseCmdLine(const std_string& theCmdLine);
		static void(__thiscall _CLASS::*& vfHandleCmdLineParam)(const std_string& theParamName, const std_string& theParamValue); void HandleCmdLineParam(const std_string& theParamName, const std_string& theParamValue);
		static void(__thiscall _CLASS::*& vfHandleNotifyGameMessage)(int theType, int theParam); void HandleNotifyGameMessage(int theType, int theParam);
		static void(__thiscall _CLASS::*& vfHandleGameAlreadyRunning)(void); void HandleGameAlreadyRunning(void);
		static void(__thiscall _CLASS::*& vfStart)(void); void Start(void);
		static void(__thiscall _CLASS::*& vfInit)(void); void Init(void);
		static void(__thiscall _CLASS::*& vfPreDDInterfaceInitHook)(void); void PreDDInterfaceInitHook(void);
		static void(__thiscall _CLASS::*& vfPostDDInterfaceInitHook)(void); void PostDDInterfaceInitHook(void);
		static bool(__thiscall _CLASS::*& vfChangeDirHook)(const char* theIntendedPath); bool ChangeDirHook(const char* theIntendedPath);
		static void(__thiscall _CLASS::*& vfPlaySample_0)(SoundId id, int pan); void PlaySample(SoundId id, int pan);
		static void(__thiscall _CLASS::*& vfPlaySample)(SoundId id); void PlaySample(SoundId id);
		static double(__thiscall _CLASS::*& vfGetMasterVolume)(void); double GetMasterVolume(void);
		static double(__thiscall _CLASS::*& vfGetMusicVolume)(void); double GetMusicVolume(void);
		static double(__thiscall _CLASS::*& vfGetSfxVolume)(void); double GetSfxVolume(void);
		static bool(__thiscall _CLASS::*& vfIsMuted)(void); bool IsMuted(void);
		static void(__thiscall _CLASS::*& vfSetMasterVolume)(double theVolume); void SetMasterVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetMusicVolume)(double theVolume); void SetMusicVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetSfxVolume)(double theVolume); void SetSfxVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfMute)(bool autoMute); void Mute(bool autoMute = false);
		static void(__thiscall _CLASS::*& vfUnmute)(bool autoMute); void Unmute(bool autoMute = false);
		static double(__thiscall _CLASS::*& vfGetLoadingThreadProgress)(void); double GetLoadingThreadProgress(void);
		static DDImage* (__thiscall _CLASS::*& vfGetImage)(const std_string& theFileName, bool commitBits); DDImage* GetImage(const std_string& theFileName, bool commitBits = true);
		static int(__thiscall _CLASS::*& vfSetSharedImage)(SharedImageRef*, int, int, int, int); int SetSharedImage(SharedImageRef* a, int b, int c, int d, int e);
		static SharedImageRef(__thiscall _CLASS::*& vfGetSharedImage)(const std_string& theFileName, const std::string& theVariant, bool* isNew); SharedImageRef GetSharedImage(const std_string& theFileName, const std::string& theVariant = u8"", bool* isNew = nullptr);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_1)(bool wantWindowed, bool is3d, bool force); void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode_0)(bool wantWindowed); void SwitchScreenMode(bool wantWindowed);
		static void(__thiscall _CLASS::*& vfSwitchScreenMode)(void); void SwitchScreenMode(void);
		static void(__thiscall _CLASS::*& vfSetAlphaDisabled)(bool isDisabled); void SetAlphaDisabled(bool isDisabled);
		static Dialog* (__thiscall _CLASS::*& vfDoDialog)(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode); Dialog* DoDialog(int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode);
		static Dialog* (__thiscall _CLASS::*& vfGetDialog)(Dialog::Type type); Dialog* GetDialog(Dialog::Type type);
		static void(__thiscall _CLASS::*& vfAddDialog)(Dialog* theDialog); void AddDialog(Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfAddDialog_0)(int theDialogId, Dialog* theDialog); void AddDialog(int theDialogId, Dialog* theDialog);
		static void(__thiscall _CLASS::*& vfKillDialog_0)(void); void KillDialog_0(void);
		static void(__thiscall _CLASS::*& vfKillDialog)(void); void KillDialog(void);
		static void(__thiscall _CLASS::*& vfKillDialog_1)(void); void KillDialog_1(void);
		static int(__thiscall _CLASS::*& vfGetDialogCount)(void); int GetDialogCount(void);
		static void(__thiscall _CLASS::*& vfModalOpen)(void); void ModalOpen(void);
		static void(__thiscall _CLASS::*& vfModalClose)(void); void ModalClose(void);
		static void(__thiscall _CLASS::*& vfGotFocus)(void); void GotFocus(void);
		static void(__thiscall _CLASS::*& vfLostFocus)(void); void LostFocus(void);
		static bool(__thiscall _CLASS::*& vfIsAltKeyUsed)(WPARAM wParam); bool IsAltKeyUsed(WPARAM wParam);
		static bool(__thiscall _CLASS::*& vfDebugKeyDown)(int theKey); bool DebugKeyDown(int theKey);
		static bool(__thiscall _CLASS::*& vfDebugKeyDownAsync)(int theKey, bool ctrlDown, bool altDown); bool DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		static void(__thiscall _CLASS::*& vfCloseRequestAsync)(void); void CloseRequestAsync(void);
		static void(__thiscall _CLASS::*& vfDone3dTesting)(void); void Done3dTesting(void);
		static std_string(__thiscall _CLASS::*& vfNotifyCrashHook)(void); std_string NotifyCrashHook(void);
		static void(__thiscall _CLASS::*& vfCheckSignature)(void); void CheckSignature(void);
		static bool(__thiscall _CLASS::*& vfDrawDirtyStuff)(void); bool DrawDirtyStuff(void);
		static void(__thiscall _CLASS::*& vfRedraw)(Rect* theClipRect); void Redraw(Rect* theClipRect);
		static void(__thiscall _CLASS::*& vfInitPropertiesHook)(void); void InitPropertiesHook(void);
		static void(__thiscall _CLASS::*& vfDoMainLoop)(void); void DoMainLoop(void);
		static bool(__thiscall _CLASS::*& vfUpdateAppStep)(bool* updated); bool UpdateAppStep(bool* updated);
		static bool(__thiscall _CLASS::*& vfUpdateApp)(void); bool UpdateApp(void);
		static bool(__thiscall _CLASS::*& vfAppCanRestore)(void); bool AppCanRestore(void);
		static bool(__thiscall _CLASS::*& vfOverrideWindowProc)(HWND, unsigned int, unsigned int, int, int*); bool OverrideWindowProc(HWND a, unsigned int b, unsigned int c, int d, int* e);
		static bool(__thiscall _CLASS::*& vfShouldCheckForUpdate)(void); bool ShouldCheckForUpdate(void);
		static void(__thiscall _CLASS::*& vfUpdateCheckQueried)(void); void UpdateCheckQueried(void);
		static bool(__thiscall _CLASS::*& vfOpenRegisterPage)(void); bool OpenRegisterPage(void);
		static int(__thiscall _CLASS::*& vfOpenRegisterPage_0)(std_map<std_string, std_string>); int OpenRegisterPage(std_map<std_string, std_string> a);
		static bool(__thiscall _CLASS::*& vfOpenHTMLTemplate)(std_string const&, class std::map<std_string, std_string> const&); bool OpenHTMLTemplate(std_string const& a, class std::map<std_string, std_string> const& b);
		static void(__thiscall _CLASS::*& vfOpenUpdateURL)(void); void OpenUpdateURL(void);
		static void(__thiscall _CLASS::*& vfKeyChar)(char); void KeyChar(char a);
		static void(__thiscall _CLASS::*& vfLoadingCompleted)(void); void LoadingCompleted(void);
		static void(__thiscall _CLASS::*& vfShowResourceError)(bool); void ShowResourceError(bool exit);
		static constexpr DWORD vfAddr_DialogListener = 0x00667D50ul;
		static void(__thiscall _CLASS::*& vfDialogButtonPress)(int dlgId, int btnId); void DialogButtonPress(int dlgId, int btnId);
		static void(__thiscall _CLASS::*& vfDialogButtonDepress)(int dlgId, int btnId); void DialogButtonDepress(int dlgId, int btnId);

		enum class State :DWORD {
			LOADING,
			MAINMENU,
			SELECT_CARD,
			BATTLE,
			LOSE,
			WIN,
			MV,
			SELECT_LEVEL
		};
		struct Level {
			enum class Type :DWORD {
				ADVENTURE,
				SURVIVAL_EASY_DAY,
				SURVIVAL_EASY_NIGHT,
				SURVIVAL_EASY_POOL,
				SURVIVAL_EASY_FOG,
				SURVIVAL_EASY_ROOF,
				SURVIVAL_HARD_DAY,
				SURVIVAL_HARD_NIGHT,
				SURVIVAL_HARD_POOL,
				SURVIVAL_HARD_FOG,
				SURVIVAL_HARD_ROOF,
				SURVIVAL_ENDLESS_DAY,
				SURVIVAL_ENDLESS_NIGHT,
				SURVIVAL_ENDLESS_POOL,
				SURVIVAL_ENDLESS_FOG,
				SURVIVAL_ENDLESS_ROOF,
				ZOMBOTANY,
				BOWLING,
				SLOT_MACHINE,
				SEED_RAIN,
				BEJEVELED,
				INVISIBLE,
				SEEING_STARS,
				ZOMBIE_AQ,
				BEJEVELED2,
				LITTLE_ZOMBIE,
				PORTAL,
				COLUMN,
				BOBSLED_BONANZA,
				ZOMBIE_QUICK,
				WHACK_ZOMBIE,
				LAST_STAND,
				ZOMBOTANY2,
				BOWLING2,
				POGO_PARTY,
				ZOMBBOSS_REVENGE,
				ART_WALL_NUT,
				SUNNY_DAY,
				UNSODDED,
				BIG_TIME,
				ART_SUNFLOWER,
				AIR_RAID,
				ICE_LEVEL,
				GARDEN,
				GRAVITY,
				GRAVE_DANGER,
				DIG_IT,
				STORM_NIGHT,
				BUNGEE_BLITZ,
				SQUIRREL,
				WISDOM_TREE,
				VASE_BREAKER_1,
				VASE_BREAKER_2,
				VASE_BREAKER_3,
				VASE_BREAKER_4,
				VASE_BREAKER_5,
				VASE_BREAKER_6,
				VASE_BREAKER_7,
				VASE_BREAKER_8,
				VASE_BREAKER_9,
				VASE_BREAKER_ENDLESS,
				I_ZOMBIE_1,
				I_ZOMBIE_2,
				I_ZOMBIE_3,
				I_ZOMBIE_4,
				I_ZOMBIE_5,
				I_ZOMBIE_6,
				I_ZOMBIE_7,
				I_ZOMBIE_8,
				I_ZOMBIE_9,
				I_ZOMBIE_ENDLESS,
				UPSELL,
				INTRO,
				ENM_BEGIN
			};
			Type __val;
			Level(Type val) :__val(val) {}
			operator Type() { return __val; }
		};
		enum class DaveState :DWORD {
			NIL,
			ENTER,
			LEAVE,
			TALK,
			WAIT,
			HANDING,
			SMILE
		};
		enum class BoardResult :DWORD {
			NIL,
			WON,
			LOST,
			RESTART,
			QUIT,
			QUIT_APP,
			CHEAT
		};
		Board* mBoard;//0768
		LoadingPage* mLoadingPage;//076C
		MainMenu* mMainMenu;//0770
		SelectCardWnd* mSelectCardWnd;//0774
		NotePage* mNotePage;//0778
		MV* mMV;//077C
		SelectLevelPage* mSelectLevelPage;//0780
		SampleManager* mSampleManagers;//0x6Du//0784
		std_list<ButtonWidget*> mControlButtonList;//0788
		std_list<Image*> mCreatedImageList;//0794
		std_string mReferId;//07A0
		std_string mRegisterLink;//07BC
		std_string mMod;//07D8
		bool mRegisterResourcesLoaded = 0;//07F4
		bool debugMode;//07F5
		union {
			Level level;//07F8
			DWORD levelRank;//07f8
		};
		State gameState;//07FC
		bool mLoadingZombiesThreadCompleted = 1;//0800
		bool hadnotEnterBoard;//0801
		int mGamesPlayed = 0;//0804
		int MaxExecutions;//0808
		int MaxPlays;//080C
		int MaxTime;//0810
		bool freePlant;//0814
		MImgStruct* poolEffectMImg;//0818
		GardenProp* mGardenProp;//081C
		AnimsLists* mAnimsLists;//0820
		CardImages* mCardImages;//0824
		UsersManager* mUsersManager;//0828
		UserData* mUserData;//082C
		DWORD* mStopMowerCount;//0830
		bool mClose;//0834
		int mUpdateClock;//0838
		Bgm* mBgm;//083C
		ID<Anim> DaveAnimID;//0840
		DaveState DaveState;//0844
		int DaveCountdown;//0848
		ID<Anim> DaveBlinkAnimID;//084C
		int DaveTalkID;//0850
		std_string DaveTalk;//0854
		int enterSysTime64;//0870
		HCURSOR cursor;//0874
		PopcapMsg* mPopcapMsg;//0878
		int enterSysTime;//087C
		int mPlayTimeActiveSession = 0;//0880
		int mPlayTimeInactiveSession = 0;//0884
		BoardResult boardresult;//0888
		bool sawZeti;//088C
		Secret* mSecrets[0x0Au];//0890+04
		bool mustache;//08B8
		bool trickedout;//08B9
		bool future;//08BAA
		bool pinata;//08BB
		bool dance;//08BC
		bool daisies;//08BD
		bool sukhbir;//08BE
		BOOL notAllowUnfullVersion;//08C0
		bool unfullVersion;//08C4
		bool mNoSample;//08C5
		ParticleSystem* operator[](ID<ParticleSystem> id) { return(mAnimsLists->mParticlesLists->mParticleSystemList)[id]; }
		//Emitter* operator[](ID<Emitter> id){ return(mAnimsLists->mParticlesLists->mEmitterList)[id]; }
		//Particle* operator[](ID<Particle> id){ return(mAnimsLists->mParticlesLists->mParticleList)[id]; }
		Anim* operator[](ID<Anim> id) { return(*mAnimsLists->mAnimList)[id]; }
		Trail* operator[](ID<Trail> id) { return(*mAnimsLists->mTrailList)[id]; }
		Attachment* operator[](ID<Attachment> id) { return(*mAnimsLists->mAttachmentList)[id]; }
		bool isBattle() { return mBoard && (gameState == State::BATTLE || (level == Level::Type::UPSELL || level == Level::Type::INTRO) && mBoard->mSceneProp->battle); }
		bool upsellBattle() { return mBoard && mBoard->mSceneProp->ShouldUpsell(); }
		bool isFirseTimeAdventure() { return level == Level::Type::ADVENTURE && mUserData->levelRecord[(int)Level::Type::ADVENTURE] == 0; }
		bool isFinishedAdventure() { return mUserData->levelRecord[(int)Level::Type::ADVENTURE]; }

		bool isGarden() { return mBoard && level == Level::Type::GARDEN; }
		bool isGardenTree() { return mBoard && (level == Level::Type::GARDEN || level == Level::Type::WISDOM_TREE); }
		bool isVB() { return mBoard && (level >= Level::Type::VASE_BREAKER_1 && level <= Level::Type::VASE_BREAKER_ENDLESS || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 35); }
		bool isIZ() { return mBoard && (level >= Level::Type::I_ZOMBIE_1 && level <= Level::Type::I_ZOMBIE_ENDLESS); }
		bool isBowling() { return mBoard && (level == Level::Type::BOWLING || level == Level::Type::BOWLING2 || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 5); }
		bool isHammer() { return mBoard && (level == Level::Type::WHACK_ZOMBIE || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 15); }
		bool isLittleZombie() { return mBoard && (level == Level::Type::LITTLE_ZOMBIE || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 25); }
		bool isStorm() { return mBoard && (level == Level::Type::STORM_NIGHT || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 40); }
		bool isRain() { return mBoard && (level == Level::Type::STORM_NIGHT || level == Level::Type::SEED_RAIN || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 40); }
		bool isBlitz() { return mBoard && (level == Level::Type::BUNGEE_BLITZ || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 45); }
		bool isBoss() { return mBoard && (level == Level::Type::ZOMBBOSS_REVENGE || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 50); }
		bool isPuzzle() { return mBoard && (level >= Level::Type::VASE_BREAKER_1 && level <= Level::Type::I_ZOMBIE_ENDLESS); }
		bool isMiniGame() { return mBoard && (level > Level::Type::SURVIVAL_ENDLESS_ROOF && level < Level::Type::VASE_BREAKER_1); }
		bool isAdventure() { return mBoard && level == Level::Type::ADVENTURE; }
		bool isSquirrel() { return mBoard && level == Level::Type::SQUIRREL; }
		bool isSlotMachine() { return mBoard && level == Level::Type::SLOT_MACHINE; }
		bool isShovel() { return mBoard && level == Level::Type::DIG_IT; }
		bool isQuick() { return mBoard && level == Level::Type::ZOMBIE_QUICK; }
		bool isSeedrain() { return mBoard && level == Level::Type::SEED_RAIN; }
		bool isPortal() { return mBoard && level == Level::Type::PORTAL; }
		bool isZombieAQ() { return mBoard && level == Level::Type::ZOMBIE_AQ; }
		bool isWT() { return mBoard && level == Level::Type::WISDOM_TREE; }
		bool isIce() { return mBoard && level == Level::Type::ICE_LEVEL; }
		bool isColumn() { return mBoard && level == Level::Type::COLUMN; }
		bool isLS() { return mBoard && level == Level::Type::LAST_STAND; }
		bool isGravity() { return mBoard && level == Level::Type::GRAVITY; }
		bool isInvisible() { return mBoard && level == Level::Type::INVISIBLE; }
		bool isBejeveled() { return mBoard && (level == Level::Type::BEJEVELED || level == Level::Type::BEJEVELED2); }
		bool isSurvival() { return mBoard && level >= Level::Type::SURVIVAL_EASY_DAY && level <= Level::Type::SURVIVAL_ENDLESS_ROOF; }
		bool isSurvivalEndless() { return mBoard && level >= Level::Type::SURVIVAL_ENDLESS_DAY && level <= Level::Type::SURVIVAL_ENDLESS_ROOF; }
		bool isVBWillEnd() { return  mBoard && (level >= Level::Type::VASE_BREAKER_1 && level <= Level::Type::VASE_BREAKER_9 || level == Level::Type::ADVENTURE && mUserData->adventureLevelIndex == 35 && mBoard->mLevelProp->flags == 2); }
		bool isSurvivalWillEnd() { return mBoard && (level >= Level::Type::SURVIVAL_EASY_DAY && level <= Level::Type::SURVIVAL_HARD_ROOF && mBoard->mLevelProp->flags == 4); }
		bool isSurvivalWontEnd() { return isSurvival() && !isSurvivalWillEnd(); }
		bool isArt() { return mBoard && (level == Level::Type::ART_WALL_NUT || level == Level::Type::ART_SUNFLOWER || level == Level::Type::SEEING_STARS); }
		bool isLevelEndlessWave() { return isArt() || isSlotMachine() || isBoss() || level == Level::Type::BEJEVELED || level == Level::Type::UPSELL || level == Level::Type::INTRO || level == Level::Type::BEJEVELED2; }
		bool isHaveMoney() { return(!((!mBoard || (level == Level::Type::UPSELL || level == Level::Type::INTRO) && !mBoard->mSceneProp->battle) || (isFirseTimeAdventure() && mBoard->adventureLevelRank < 11))); }
		bool isHaveGarden() { return mUserData->adventureLevelIndex >= 45 || mUserData->levelRecord[(int)Level::Type::ADVENTURE] > 0; }
		bool isMiniBoss() { return mBoard && level == Level::Type::ADVENTURE && (mUserData->adventureLevelIndex == 10 || mUserData->adventureLevelIndex == 20 || mUserData->adventureLevelIndex == 30); }
		bool isBelt() { return isBoss() || isMiniBoss() || isShovel() || isBowling() || isLittleZombie() || isStorm() || isBlitz() || level == Level::Type::PORTAL || level == Level::Type::COLUMN || level == Level::Type::INVISIBLE; }
		bool isFog() { return mBoard->yard == Board::Yard::Type::FOG && !isStorm() && !isInvisible(); }
		void NewSampleF(Sample::Type type, float speed);
		void NewSampleF(Sample::Type type);
		void NewSample(Sample::Type type);
		void __thiscall v_DoMainLoop();
		bool __thiscall v_UpdateApp();
		bool __thiscall v_Process(bool allowSleep);
		bool __thiscall v_UpdateAppStep(bool* updated);
		void UpdateAppOnce(int millisecond);
		bool __thiscall v_DrawDirtyStuff();
		bool __thiscall v_DoUpdateFrames();
		void __thiscall v_UpdateFrames();
		void v_EnforceCursor();
		void TryExitLevel();
		void LoadBoard();
		void UpdateDave();
		void DaveEnter();
		void SetDave(int index);
		void EndLevel();
		void KillBoard();
		void NewGame();
		void KillParticleSystem(ParticleSystem::Type type);
		Dialog* GetDialog(int id);
		ParticleSystem* NewParticleSystem(ParticleSystem::Type _type, int layer, float x, float y);
		Anim* NewAnim(Anim::Type _type, int layer, float x, float y);
	};

	class SoundInstance {
		using _CLASS = SoundInstance;
	public:
		static constexpr DWORD vfAddr_SoundInstance = 0x00675F1Cul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static void(__thiscall _CLASS::*& vfRelease)(void); void Release(void);
		static void(__thiscall _CLASS::*& vfSetBaseVolume)(double theBaseVolume); void SetBaseVolume(double theBaseVolume);
		static void(__thiscall _CLASS::*& vfSetBasePan)(int theBasePan); void SetBasePan(int theBasePan);
		static void(__thiscall _CLASS::*& vfAdjustPitch)(double theNumSteps); void AdjustPitch(double theNumSteps);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetPan)(int thePosition); void SetPan(int thePosition);
		static bool(__thiscall _CLASS::*& vfPlay)(bool looping, bool autoRelease); bool Play(bool looping, bool autoRelease);
		static void(__thiscall _CLASS::*& vfStop)(void); void Stop(void);
		static bool(__thiscall _CLASS::*& vfIsPlaying)(int theSongId); bool IsPlaying(int theSongId);
		static bool(__thiscall _CLASS::*& vfIsReleased)(void); bool IsReleased(void);
		static double(__thiscall _CLASS::*& vfGetVolume)(void); double GetVolume(void);

		DWORD vf_SoundInstance = vfAddr_SoundInstance;
	};

	class SharedImage {
		using _CLASS = SharedImage;
	public:
		DDImage* mImage;
		int mRefCount;
	};

	class Sysfont :public Font {
		using _CLASS = Sysfont;
	public:
		static constexpr DWORD vfAddr_Font = 0x00672554ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static int(__thiscall _CLASS::*& vfGetAscent)(void); int GetAscent(void);
		static int(__thiscall _CLASS::*& vfGetAscentPadding)(void); int GetAscentPadding(void);
		static int(__thiscall _CLASS::*& vfGetDescent)(void); int GetDescent(void);
		static int(__thiscall _CLASS::*& vfGetHeight)(void); int GetHeight(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacingOffset)(void); int GetLineSpacingOffset(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacing)(void); int GetLineSpacing(void);
		static int(__thiscall _CLASS::*& vfStringWidth)(const std_string& str); int StringWidth(const std_string& str);
		static int(__thiscall _CLASS::*& vfCharWidth)(char chr); int CharWidth(char chr);
		static int(__thiscall _CLASS::*& vfCharWidthKern)(char chr, char prev); int CharWidthKern(char chr, char prev);
		static void(__thiscall _CLASS::*& vfDrawString)(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect); void DrawString(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect);
		static Font* (__thiscall _CLASS::*& vfDuplicate)(void); Font* Duplicate(void);

		HFONT mHFont;
		SexyAppBase* mApp;
		bool mDrawShadow;
		bool mSimulateBold;
	};

	class UsersManager {
		using _CLASS = UsersManager;
	public:
		DWORD* vf_UsersManager;// =(DWORD*)vfAddr_UsersManager;
		std_map<std_string, UserData>mUsers;
		int UserID;
		int OperatedCount;
	};

	class WidgetSafeDeleteInfo {
		using _CLASS = WidgetSafeDeleteInfo;
	public:
		int mUpdateAppDepth;
		Widget* mWidget;
	};

	class FloatParameterTrackNode {
	public:
		float mTime;
		float mLowValue;
		float mHighValue;
		DWORD mCurveType;
		DWORD mDistribution;
	};

	class ParticleSystemInfo {
		using _CLASS = ParticleSystemInfo;
	public:
		EmitterInfo* EmitterInfoList;
		int EmitterInfoListSize;
	};

	class FloatParameterTrack {
	public:
		FloatParameterTrackNode* mNodes;
		int mCountNodes;
	};

	class EmitterInfo {//B0
		using _CLASS = EmitterInfo;
	public:
		Image* mImage;
		int mImageCol;
		int mImageRow;
		int mImageFrames;
		int mAnimated;
		int mParticleFlags;
		DWORD mEmitterType;
		char* mName;
		char* mOnDuration;
		FloatParameterTrack mSystemDuration;
		FloatParameterTrack mCrossFadeDuration;
		FloatParameterTrack mSpawnRate;
		FloatParameterTrack mSpawnMinActive;
		FloatParameterTrack mSpawnMaxActive;
		FloatParameterTrack mSpawnMaxLaunched;
		FloatParameterTrack mEmitterRadius;
		FloatParameterTrack mEmitterOffsetX;
		FloatParameterTrack mEmitterOffsetY;
		FloatParameterTrack mEmitterBoxX;
		FloatParameterTrack mEmitterBoxY;
		FloatParameterTrack mEmitterSkewX;
		FloatParameterTrack mEmitterSkewY;
		FloatParameterTrack mEmitterPath;
		FloatParameterTrack mParticleDuration;
		FloatParameterTrack mLaunchSpeed;
		FloatParameterTrack mLaunchAngle;
		FloatParameterTrack mSystemRed;
		FloatParameterTrack mSystemGreen;
		FloatParameterTrack mSystemBlue;
		FloatParameterTrack mSystemAlpha;
		FloatParameterTrack mSystemBrightness;
		DWORD* mParticleFields;
		int mParticleFieldCount;
		DWORD* mSystemFields;
		int mSystemFieldCount;
		FloatParameterTrack mParticleRed;
		FloatParameterTrack mParticleGreen;
		FloatParameterTrack mParticleBlue;
		FloatParameterTrack mParticleAlpha;
		FloatParameterTrack mParticleBrightness;
		FloatParameterTrack mParticleSpinAngle;
		FloatParameterTrack mParticleSpinSpeed;
		FloatParameterTrack mParticleScale;
		FloatParameterTrack mParticleStretch;
		FloatParameterTrack mCollisionReflect;
		FloatParameterTrack mCollisionSpin;
		FloatParameterTrack mClipTop;
		FloatParameterTrack mClipBottom;
		FloatParameterTrack mClipLeft;
		FloatParameterTrack mClipRight;
		FloatParameterTrack mAnimationRate;
	};

	class Emitter {
		using _CLASS = Emitter;
	public:
		EmitterInfo* Info;
		ParticleSystem* ParticleSystem;
		SList<ID<Particle>>* ParticleIDList;
		SList<ID<Particle>> ParticleIDStack;
		float rate;
		float x;
		float y;
		int mParticlesSpawned;
		int updateCount;
		int updateCountMax;
		float updateRate;
		float lastUpdateRate;
		bool vanished;
		Color mColor;
		bool mExtraAdditiveDrawOverride;
		float size;
		Image* mImage;
		ID<Emitter> crossFadeEmitterID;
		int crossvanishCountdown;
		int mFrameOverride;
		float mTrackInterp[10];
		std_pair<float, float> mSystemFieldInterp[4];
	};

	class Particle {
		using _CLASS = Particle;
	public:
		Emitter* emitter;//0000
		int updateCountMax;//0004
		int updateCount;//0008
		float updateRate;//000C
		float lastUpdateRate;//0010
		float animUpdateRate;//0014
		int dx;//0018
		int dy;//001C
		int x;//0020
		int y;//0024
		int mImageFrame;//0028
		float rr;//002C
		float drr;//0030
		ID<Particle> crossFadeParticleID;//0034
		int crossFadeCountMax;//0038
		float mParticleInterp[16];//003C
		float mParticleFieldInterp[4][2];//007C
	};

	class Attacher {
		using _CLASS = Attacher;
	public:
		enum class Type :DWORD {
			PARTICLESYSTEM,
			TRAIL,
			ANIM,
			ATTACHMENT,
			OTHER
		};
		DWORD ID;
		Type type;
		Matrix3 mPosition;
		bool vanished;
		bool mDontPropogateColor;
		Attacher() {
			ID = 0;
			type = Type::OTHER;
			mPosition = Matrix3();
		}
	};

	class Attachment {
		using _CLASS = Attachment;
	public:
		Attacher Attachers[16];
		int listSize;
		bool vanished;
		Attachment() {
			for (int i = 0; i < 16; ++i)Attachers[i] = Attacher();
			listSize = 0;
			vanished = false;
		}
		void Kill();
		void Update();
		void RemoveAttacher(ParticleSystem::Type type);
		Anim* GetFirstAnim();
		void PropogateColor(Color theColor, bool theEnableAdditiveColor, Color theAdditiveColor, bool theEnableOverlayColor, Color theOverlayColor);
		Attacher* GetFirstAttacher();
		Attacher* NewAttacher();
		void SetMatrix(Matrix3* matrix);
		void SetPosition(float x, float y);
		void SetColor(Color& theColor);
		void SetSize(float size);
	};

	class TrailDefinition {
	public:
		Image* mImage;
		int mMaxPoints;
		float mMinPointDistance;
		int mTrailFlags;
		FloatParameterTrack mTrailDuration;
		FloatParameterTrack mWidthOverLength;
		FloatParameterTrack mWidthOverTime;
		FloatParameterTrack mAlphaOverLength;
		FloatParameterTrack mAlphaOverTime;
	};

	class Trail {
		using _CLASS = Trail;
	public:
		Point<float> points[20];
		int pointCount;
		bool vanished;
		int layer;
		int updateCount;
		int updateCountMax;
		TrailDefinition* mDefinition;
		int* mTrailHolder;
		float mTrailInterp[4];
		float x;
		float y;
		bool isAttachment;
		Color mColor;
		void Update();
		void AddPoint(float x, float y);
	};

	class ZombieInfo {
	public:
		Zombie::Type mZombieType;
		Anim::Type mReanimationType;
		int mZombieValue;
		int mStartingLevel;
		int mFirstAllowedWave;
		int mPickWeight;
		char* mZombieName;
	};

	class AnimAttachment {
		using _CLASS = AnimAttachment;
	public:
		int mBlendCountdown;//0000
		int mBlendCountdownMax;//0004
		FramePartProp mFrame;//0008
		float diffRange;//0034
		float xDiff;//0038
		float yDiff;//003C
		ID<Attachment> mAttachmentID;//0040
		Image* mImage;//0044
		int group;//-1diasble//0048
		Color mColor;//004C
		bool mIgnoreClipRect;//005C
		bool mTruncateDisappearingFrames;//005D
		bool mIgnoreColorOverride;//005E
		bool mIgnoreExtraAdditiveColor;//005F
	};

	class Data {
		using _CLASS = Data;
	public:
		int FEEDDEAD;
		int _2;
		int keyword;
		char BoardMain[0x564Cu];
		DataList<Zombie> ZombieDataList;
		DataList<Plant> PlantDataList;
		DataList<Bullet> BulletDataList;
		DataList<Item> ItemDataList;
		DataList<Mower> MowerDataList;
		DataList<Building> BuildingDataList;
		DataList<ParticleSystem> ParticleSystemDataList;
		DataList<Emitter> EmitterDataList;
		DataList<Particle> ParticleDataList;
		DataList<Anim> AnimDataList;
		DataList<Trail> TrailDataList;
		DataList<Attachment> AttachmentDataList;
		char MouseProp[0x4Cu];
		char MouseAddProp[0x2Cu];
		char BoardText[0x31Cu];
		char Slot[0x350u];
		char LevelProp[0xBCu];
		char Bgm[0x4Cu];
		int _FEEDDEAD;
		static void OpperateMain(Context* buffer, Board* board);
	};

	class ActiveFontLayer {
		using _CLASS = ActiveFontLayer;
	public:
		static constexpr DWORD vfAddr = 0x00672608ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD* vf_ActiveFontLayer;// =(DWORD*)vfAddr_ActiveFontLayer;
		FontLayer* mBaseFontLayer;
		Image* mScaledImage;
		bool mOwnsImage;
		std_map<int, Rect> mScaledCharImageRects;
	};

	class DSoundInstance :public SoundInstance {
		using _CLASS = DSoundInstance;
		static constexpr DWORD vfAddr_SoundInstance = 0x00675FA0ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static void(__thiscall _CLASS::*& vfRelease)(void); void Release(void);
		static void(__thiscall _CLASS::*& vfSetBaseVolume)(double theBaseVolume); void SetBaseVolume(double theBaseVolume);
		static void(__thiscall _CLASS::*& vfSetBasePan)(int theBasePan); void SetBasePan(int theBasePan);
		static void(__thiscall _CLASS::*& vfAdjustPitch)(double theNumSteps); void AdjustPitch(double theNumSteps);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetPan)(int thePosition); void SetPan(int thePosition);
		static bool(__thiscall _CLASS::*& vfPlay)(bool looping, bool autoRelease); bool Play(bool looping, bool autoRelease);
		static void(__thiscall _CLASS::*& vfStop)(void); void Stop(void);
		static bool(__thiscall _CLASS::*& vfIsPlaying)(int theSongId); bool IsPlaying(int theSongId);
		static bool(__thiscall _CLASS::*& vfIsReleased)(void); bool IsReleased(void);
		static double(__thiscall _CLASS::*& vfGetVolume)(void); double GetVolume(void);
	public:
		DSoundManager* mSoundManagerP;
		int mSourceSoundBuffer;
		int mSoundBuffer;
		bool mAutoRelease;
		bool mHasPlayed;
		bool mReleased;
		int mBasePan;
		double mBaseVolume;
		int mPan;
		double mVolume;
		int mDefaultFrequency;
	};

	class SoundManager {
		using _CLASS = SoundManager;
	public:
		static constexpr DWORD vfAddr_SoundManager = 0x00675F54ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfInitialized)(void); bool Initialized(void);
		static bool(__thiscall _CLASS::*& vfLoadSound)(const std_string& theFilename); bool LoadSound(const std_string& theFilename);
		static bool(__thiscall _CLASS::*& vfLoadSound_0)(unsigned int theSfxID, const std_string& theFilename); bool LoadSound(unsigned int theSfxID, const std_string& theFilename);
		static void(__thiscall _CLASS::*& vfReleaseSound)(unsigned int theSfxID); void ReleaseSound(unsigned int theSfxID);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetBaseVolume)(unsigned int theSfxID, double theBaseVolume); void SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
		static void(__thiscall _CLASS::*& vfSetBasePan)(unsigned int theSfxID, int theBasePan); void SetBasePan(unsigned int theSfxID, int theBasePan);
		static SoundInstance* (__thiscall _CLASS::*& vfGetSoundInstance)(SoundId id); SoundInstance* GetSoundInstance(SoundId id);
		static void(__thiscall _CLASS::*& vfReleaseSounds)(void); void ReleaseSounds(void);
		static void(__thiscall _CLASS::*& vfReleaseChannels)(void); void ReleaseChannels(void);
		static double(__thiscall _CLASS::*& vfGetMasterVolume)(void); double GetMasterVolume(void);
		static void(__thiscall _CLASS::*& vfSetMasterVolume)(double theVolume); void SetMasterVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfFlush)(void); void Flush(void);
		static void(__thiscall _CLASS::*& vfSetCooperativeWindow)(HWND theHWnd, bool isWindowed); void SetCooperativeWindow(HWND theHWnd, bool isWindowed);
		static void(__thiscall _CLASS::*& vfStopAllSounds)(void); void StopAllSounds(void);
		static int(__thiscall _CLASS::*& vfGetFreeSoundId)(void); int GetFreeSoundId(void);
		static int(__thiscall _CLASS::*& vfGetNumSounds)(void); int GetNumSounds(void);

		DWORD vf_SoundManager = vfAddr_SoundManager;
		//void SetVolume(double theVolume);
	};

#define MAX_SOURCE_SOUNDS	256
#define MAX_CHANNELS		32
	class DSoundManager :public SoundManager {
		using _CLASS = DSoundManager;
	public:
		static constexpr DWORD vfAddr_SoundManager = 0x00675FD4ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static bool(__thiscall _CLASS::*& vfInitialized)(void); bool Initialized(void);
		static bool(__thiscall _CLASS::*& vfLoadSound)(const std_string& theFilename); bool LoadSound(const std_string& theFilename);
		static bool(__thiscall _CLASS::*& vfLoadSound_0)(unsigned int theSfxID, const std_string& theFilename); bool LoadSound(unsigned int theSfxID, const std_string& theFilename);
		static void(__thiscall _CLASS::*& vfReleaseSound)(unsigned int theSfxID); void ReleaseSound(unsigned int theSfxID);
		static void(__thiscall _CLASS::*& vfSetVolume)(double theVolume); void SetVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfSetBaseVolume)(unsigned int theSfxID, double theBaseVolume); void SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
		static void(__thiscall _CLASS::*& vfSetBasePan)(unsigned int theSfxID, int theBasePan); void SetBasePan(unsigned int theSfxID, int theBasePan);
		static SoundInstance* (__thiscall _CLASS::*& vfGetSoundInstance)(SoundId id); SoundInstance* GetSoundInstance(SoundId id);
		static void(__thiscall _CLASS::*& vfReleaseSounds)(void); void ReleaseSounds(void);
		static void(__thiscall _CLASS::*& vfReleaseChannels)(void); void ReleaseChannels(void);
		static double(__thiscall _CLASS::*& vfGetMasterVolume)(void); double GetMasterVolume(void);
		static void(__thiscall _CLASS::*& vfSetMasterVolume)(double theVolume); void SetMasterVolume(double theVolume);
		static void(__thiscall _CLASS::*& vfFlush)(void); void Flush(void);
		static void(__thiscall _CLASS::*& vfSetCooperativeWindow)(void); void SetCooperativeWindow(void);
		static void(__thiscall _CLASS::*& vfStopAllSounds)(void); void StopAllSounds(void);
		static int(__thiscall _CLASS::*& vfGetFreeSoundId)(void); int GetFreeSoundId(void);
		static int(__thiscall _CLASS::*& vfGetNumSounds)(void); int GetNumSounds(void);

		Buffer* mSourceSounds[0x100u];
		std_string mSourceFileNames[0x100u];
		Buffer* mPrimaryBuffer;
		int mSourceDataSizes[0x100u];
		double mBaseVolumes[0x100u];
		int mBasePans[0x100u];
		DSoundInstance* mPlayingSounds[0x20u];
		double mMasterVolume;
		int mLastReleaseTick;
		LPVOID mDirectSound;
		bool mHaveFMod;
	};

	class EncodingParser {
		using _CLASS = EncodingParser;
	public:
		DWORD* vf_EncodingParser;// =(DWORD*)vfAddr_EncodingParser;
		FILE* mfile;
		std_vector<wchar_t> mBufferedText;
		bool(__thiscall EncodingParser::* mGetCharFunc)(wchar_t*, bool*);
		bool mForcedEncodingType;
		bool mFirstChar;
		bool mByteSwap;
	};

	class DescParser :public EncodingParser {
		using _CLASS = DescParser;
	public:
		int mCmdSep;
		std_string mError;
		DWORD mCurrentLineNum;
		std_wstring mCurrentLine;
		std_map<std_string, DataElement>mDefineMap;
	};

	class FmodInstance {
		using _CLASS = FmodInstance;
	public:
		static constexpr DWORD vfAddr_FmodInstance = 0x00676020ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_FmodInstance = vfAddr_FmodInstance;
		int mModule;
		int FSOUND_SetBufferSize;
		int FSOUND_SetHWND;
		int FSOUND_Init;
		int FSOUND_Close;
		int FSOUND_Sample_Load;
		int FSOUND_Sample_Alloc;
		int FSOUND_Sample_Free;
		int FSOUND_Sample_Lock;
		int FSOUND_Sample_Unlock;
		int FSOUND_Sample_SetLoopPoints;
		int FSOUND_Sample_GetLength;
		int FSOUND_Sample_GetDefaults;
		int FSOUND_Sample_GetMode;
		int FSOUND_PlaySound;
		int FSOUND_StopSound;
		int FSOUND_SetVolume;
		int FSOUND_SetPaused;
		int FSOUND_SetLoopMode;
		int FSOUND_IsPlaying;
		int FSOUND_Stream_OpenFile;
		int FSOUND_Stream_Close;
		int FSOUND_Stream_Play;
		int FMUSIC_LoadSong;
		int FMUSIC_PlaySong;
		int FMUSIC_StopSong;
		int FMUSIC_SetLooping;
		int FMUSIC_SetOrder;
		int FMUSIC_SetPaused;
		int FMUSIC_SetMasterVolume;
		int FMUSIC_IsPlaying;
	};

	class FontData :public DescParser {
		using _CLASS = FontData;
	public:
		bool mInitialized;
		int mRefCount;
		SexyAppBase* mApp;
		int mDefaultPointSize;
		std_set<char> mCharMap;
		std_list<FontLayer> mFontLayerList;
		std_map<std_string, FontLayer*>mFontLayerMap;
		std_string mSourceFile;
		std_string mFontErrorHeader;
	};

	class HttpTransfer {
		using _CLASS = HttpTransfer;
	public:
		static constexpr DWORD vfAddr_HttpTransfer = 0x00675304ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		DWORD vf_HttpTransfer = vfAddr_HttpTransfer;
		int mTransferId;
		int mSocket;
		std_string mSendStr;
		std_string mSpecifiedBaseURL;
		std_string mSpecifiedRelURL;
		std_string mURL;
		std_string mProto;
		std_string mHost;
		int mPort;
		std_string mPath;
		int mContentLength;
		std_string mContent;
		bool mTransferPending;
		bool mThreadRunning;
		bool mExiting;
		bool mAborted;
		int mResult;
		int mDemoLastKnownResult;
	};

	class ImageFont :public Font {
		using _CLASS = ImageFont;
	public:
		static constexpr DWORD vfAddr_Font = 0x00672614ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
		static int(__thiscall _CLASS::*& vfGetAscent)(void); int GetAscent(void);
		static int(__thiscall _CLASS::*& vfGetAscentPadding)(void); int GetAscentPadding(void);
		static int(__thiscall _CLASS::*& vfGetDescent)(void); int GetDescent(void);
		static int(__thiscall _CLASS::*& vfGetHeight)(void); int GetHeight(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacingOffset)(void); int GetLineSpacingOffset(void);
		static int(__thiscall _CLASS::*& vfGetLineSpacing)(void); int GetLineSpacing(void);
		static int(__thiscall _CLASS::*& vfStringWidth)(const std_string& str); int StringWidth(const std_string& str);
		static int(__thiscall _CLASS::*& vfCharWidth)(char chr); int CharWidth(char chr);
		static int(__thiscall _CLASS::*& vfCharWidthKern)(char chr, char prev); int CharWidthKern(char chr, char prev);
		static void(__thiscall _CLASS::*& vfDrawString)(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect); void DrawString(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect);
		static Font* (__thiscall _CLASS::*& vfDuplicate)(void); Font* Duplicate(void);
		static void(__thiscall _CLASS::*& vfGenerateActiveFontLayers)(void); void GenerateActiveFontLayers(void);
		static void(__thiscall _CLASS::*& vfDrawStringEx)(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect* theClipRect, std_list<Rect>* theDrawnAreas, int* theWidth); void DrawStringEx(Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect* theClipRect, std_list<Rect>* theDrawnAreas, int* theWidth);
		static void(__thiscall _CLASS::*& vfSetPointSize)(int thePointSize); void SetPointSize(int thePointSize);
		static int(__thiscall _CLASS::*& vfGetPointSize)(void); int GetPointSize(void);
		static void(__thiscall _CLASS::*& vfSetScale)(double theScale); void SetScale(double theScale);
		static int(__thiscall _CLASS::*& vfGetDefaultPointSize)(void); int GetDefaultPointSize(void);
		static bool(__thiscall _CLASS::*& vfAddTag)(std_string theTagName); bool AddTag(std_string theTagName);
		static bool(__thiscall _CLASS::*& vfRemoveTag)(std_string theTagName); bool RemoveTag(std_string theTagName);
		static bool(__thiscall _CLASS::*& vfHasTag)(std_string theTagName); bool HasTag(std_string theTagName);
		static std_string(__thiscall _CLASS::*& vfGetDefine)(std_string theName); std_string GetDefine(std_string theName);
		static void(__thiscall _CLASS::*& vfPrepare)(void); void Prepare(void);
		static int(__thiscall _CLASS::*& vfWriteToCache)(std::string* a, std::string* b); int WriteToCache(std::string* a, std::string* b);

		FontData* mFontData;
		int mPointSize;
		std_vector<std_string> mTagVector;
		bool mActiveListValid;
		std_list<ActiveFontLayer> mActiveLayerList;
		double mScale;
		bool mForceScaledImagesWhite;
	};

	class PropertierParser {
		using _CLASS = PropertierParser;
	public:
		DWORD* vf_PropertierParser;// =(DWORD*)vfAddr_PropertierParser;
		SexyAppBase* mApp;
		XMLParser* mXMLParser;
		std_string mError;
		bool mHasFailed;
	};

	class TextureData {
		using _CLASS = TextureData;
	public:
		std_vector<TextureDataPiece> mTextures;
		LPVOID mPalette;
		int mWidth;
		int mHeight;
		int mTexVecWidth;
		int mTexVecHeight;
		int mTexPieceWidth;
		int mTexPieceHeight;
		int mBitsChangedCount;
		int mTexMemSize;
		float mMaxTotalU;
		float mMaxTotalV;
		int mPixelFormat;
		int mImageFlags;
	};

	class CharData {
		using _CLASS = CharData;
	public:
		Rect mImageRect;
		Point<int> mOffset;
		std_map<char, int> mKerningOffsets;
		int mWidth;
		int mOrder;
	};

	class FontLayer {
		using _CLASS = FontLayer;
	public:
		FontData* mFontData;
		std_vector<std_string> mRequiredTags;
		std_vector<std_string> mExcludedTags;
		std_map<char, CharData> mCharData;
		Color mColorMult;
		Color mColorAdd;
		SharedImageRef mImage;
		int mDrawMode;
		Point<int> mOffset;
		int mSpacing;
		int mMinPointSize;
		int mMaxPointSize;
		int mPointSize;
		int mAscent;
		int mAscentPadding;
		int mHeight;
		int mDefaultHeight;
		int mLineSpacingOffset;
		int mBaseOrder;
	};

	class PlantInfo {
		using _CLASS = PlantInfo;
	public:
		Plant::Type type;
		Image* mImage;
		Anim::Type mAnimType;
		int rank;
		int price;
		int CD;
		bool haveBullet;
		int attackTime;
		const char* Name;
	};

	class WidthCheck {
		using _CLASS = WidthCheck;
	public:
		Font* mFont;
		int mWidth;
	};

	class DataElement {
		using _CLASS = DataElement;
	public:
		bool mIsList;
	};

	class SingleDataElement :public DataElement {
		using _CLASS = SingleDataElement;
	public:
		std_string	 mString;
	};

	class ListDataElement :public DataElement {
		using _CLASS = ListDataElement;
	public:
		std_vector<DataElement*>	 mElementVector;
	};

	class PreModalInfo {
		using _CLASS = PreModalInfo;
	public:
		Widget* mBaseModalWidget;
		Widget* mPrevBaseModalWidget;
		Widget* mPrevFocusWidget;
		FlagsMod			 mPrevBelowModalFlagsMod;
	};

	class ModalFlags {
		using _CLASS = ModalFlags;
	public:
		int				 mOverFlags;
		int					 mUnderFlags;
		bool				 mIsOver;
		void ModFlags(const FlagsMod& theFlagsMod);
		int GetFlags();
	};

	class AutoModalFlags {
		using _CLASS = AutoModalFlags;
	public:
		ModalFlags* mModalFlags;
		int						mOldOverFlags;
		int						mOldUnderFlags;
		AutoModalFlags(ModalFlags* theModalFlags, const FlagsMod& theFlagMod);
	};

	class BassInfo {
		using _CLASS = BassInfo;
	public:
		DWORD flags;
		DWORD hwsize;
		DWORD hwfree;
		DWORD freesam;
		DWORD free3d;
		DWORD minrate;
		DWORD maxrate;
		BOOL eax;
		DWORD minbuf;
		DWORD dsver;
		DWORD latency;
		DWORD initflags;
		DWORD speakers;
		char* driver;
	};

	class BassSample {
		using _CLASS = BassSample;
	public:
		DWORD freq;
		DWORD volume;
		int pan;
		DWORD flags;
		DWORD length;
		DWORD max;
		DWORD origres;
		DWORD chans;
		DWORD mode3d;
		float mindist;
		float maxdist;
		DWORD iangle;
		DWORD oangle;
		DWORD outvol;
		DWORD vam;
		DWORD priority;
	};

	using SYNCPROC = void(__stdcall)(DWORD handle, DWORD channel, DWORD data, DWORD user);

	class BassInstance {
		using _CLASS = BassInstance;
	public:
		DWORD* vf_BassInstance;// =(DWORD*)vfAddr_BassInstance;
		BOOL BASS_MusicSetAmplify(DWORD handle, DWORD amp);
		BOOL BASS_MusicPlay(DWORD handle);
		BOOL BASS_MusicPlayEx(DWORD handle, DWORD pos, int flags, BOOL reset);
		BOOL BASS_ChannelResume(DWORD handle);
		BOOL BASS_StreamPlay(DWORD handle, BOOL flush, DWORD flags);
		HMODULE mModule;
		bool			mVersion2;
		DWORD(__stdcall* BASS_GetVersion)();
		BOOL(__stdcall* BASS_Init)(int device, DWORD freq, DWORD flags, HWND win);
		BOOL(__stdcall* BASS_Init2)(int device, DWORD freq, DWORD flags, HWND win, GUID* clsid);
		void(__stdcall* BASS_Free)();
		BOOL(__stdcall* BASS_Stop)();
		BOOL(__stdcall* BASS_Start)();
		void(__stdcall* BASS_SetGlobalVolumes)(int musvol, int samvol, int strvol);
		BOOL(__stdcall* BASS_SetVolume)(DWORD volume);
		BOOL(__stdcall* BASS_GetVolume)();
		BOOL(__stdcall* BASS_GetInfo)(BassInfo* info);
		DWORD(__stdcall* BASS_SetConfig)(DWORD option, DWORD value);
		DWORD(__stdcall* BASS_GetConfig)(DWORD option);
		BOOL(__stdcall* BASS_ChannelStop)(DWORD handle);
		BOOL(__stdcall* BASS_ChannelPlay)(DWORD handle, BOOL restart);
		BOOL(__stdcall* BASS_ChannelPause)(DWORD handle);
		BOOL(__stdcall* BASS_ChannelSetAttributes)(DWORD handle, int freq, int volume, int pan);
		BOOL(__stdcall* BASS_ChannelGetAttributes)(DWORD handle, DWORD* freq, DWORD* volume, int* pan);
		BOOL(__stdcall* BASS_ChannelSetPosition)(DWORD handle, QWORD pos);
		QWORD(__stdcall* BASS_ChannelGetPosition)(DWORD handle);
		BOOL(__stdcall* BASS_ChannelSetFlags)(DWORD handle, DWORD flags);
		DWORD(__stdcall* BASS_ChannelIsActive)(DWORD handle);
		BOOL(__stdcall* BASS_ChannelSlideAttributes)(DWORD handle, int freq, int volume, int pan, DWORD time);
		DWORD(__stdcall* BASS_ChannelIsSliding)(DWORD handle);
		DWORD(__stdcall* BASS_ChannelGetLevel)(DWORD handle);
		DWORD(__stdcall* BASS_ChannelSetFX)(DWORD handle, DWORD theType, int priority);
		BOOL(__stdcall* BASS_ChannelRemoveFX)(DWORD handle, DWORD fx);
		QWORD(__stdcall* BASS_ChannelGetLength)(DWORD handle);
		DWORD(__stdcall* BASS_ChannelGetData)(DWORD handle, void* buffer, DWORD length);
		BOOL(__stdcall* BASS_ChannelPreBuf)(DWORD handle, DWORD length);
		DWORD(__stdcall* BASS_ChannelSetSync)(DWORD handle, DWORD theType, QWORD theParam, SYNCPROC* proc, DWORD user);
		BOOL(__stdcall* BASS_ChannelRemoveSync)(DWORD handle, DWORD sync);
		DWORD(__stdcall* BASS_MusicLoad)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags);
		DWORD(__stdcall* BASS_MusicLoad2)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags, DWORD freq);
		void(__stdcall* BASS_MusicFree)(DWORD handle);
		DWORD(__stdcall* BASS_StreamCreateFile)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags);
		void(__stdcall* BASS_StreamFree)(DWORD handle);
		BOOL(__stdcall* BASS_FXSetParameters)(DWORD handle, void* par);
		BOOL(__stdcall* BASS_FXGetParameters)(DWORD handle, void* par);
		DWORD(__stdcall* BASS_MusicGetAttribute)(DWORD handle, DWORD attrib);
		void(__stdcall* BASS_MusicSetAttribute)(DWORD handle, DWORD attrib, DWORD value);
		DWORD(__stdcall* BASS_MusicGetOrders)(DWORD handle);
		DWORD(__stdcall* BASS_MusicGetOrderPosition)(DWORD handle);
		DWORD(__stdcall* BASS_PluginLoad)(char* file, DWORD flags);
		DWORD(__stdcall* BASS_SampleLoad)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD max, DWORD flags);
		BOOL(__stdcall* BASS_SampleFree)(DWORD handle);
		BOOL(__stdcall* BASS_SampleSetInfo)(DWORD handle, BassSample* info);
		BOOL(__stdcall* BASS_SampleGetInfo)(DWORD handle, BassSample* info);
		DWORD(__stdcall* BASS_SampleGetChannel)(DWORD handle, BOOL onlynew);
		BOOL(__stdcall* BASS_SampleStop)(DWORD handle);
		int(__stdcall* BASS_ErrorGetCode)();
	};

#define MTRAND_N 624 
#define MTRAND_M 397
#define MATRIX_A 0x9908b0dful
#define UPPER_MASK 0x80000000ul
#define LOWER_MASK 0x7ffffffful
#define TEMPERING_MASK_B 0x9d2c5680ul
#define TEMPERING_MASK_C 0xefc60000ul
#define TEMPERING_SHIFT_U(y)(y >> 11)
#define TEMPERING_SHIFT_S(y)(y << 7)
#define TEMPERING_SHIFT_T(y)(y << 15)
#define TEMPERING_SHIFT_L(y)(y >> 18)
	class MTRand {
		using _CLASS = MTRand;
	public:
		unsigned long mt[MTRAND_N];
		int mti;
		MTRand(const std_string& theSerialData);
		MTRand(unsigned long seed);
		MTRand();
		void SRand(const std_string& theSerialData);
		void SRand(unsigned long seed);
		unsigned long NextNoAssert();
		unsigned long Next();
		unsigned long NextNoAssert(unsigned long range);
		unsigned long Next(unsigned long range);
		float NextNoAssert(float range);
		float Next(float range);
		std_string Serialize();
		static void SetRandAllowed(bool allowed);
	};

	class MTAutoDisallowRand {
		using _CLASS = MTAutoDisallowRand;
	public:
		MTAutoDisallowRand() { MTRand::SetRandAllowed(false); }
		~MTAutoDisallowRand() { MTRand::SetRandAllowed(true); }
	};

	class AutoCrit {
		using _CLASS = AutoCrit;
	public:
		LPCRITICAL_SECTION		mCritSec;
		AutoCrit(LPCRITICAL_SECTION theCritSec) :mCritSec(theCritSec) {
			EnterCriticalSection(mCritSec);
		}

		AutoCrit(const CritSect& theCritSect) :mCritSec((LPCRITICAL_SECTION)&theCritSect) {
			EnterCriticalSection(mCritSec);
		}

		~AutoCrit() {
			LeaveCriticalSection(mCritSec);
		}
	};

	class PropertiesParser {
		using _CLASS = PropertiesParser;
	public:
		static constexpr DWORD vfAddr = 0x00675364ul;
		static void(__thiscall _CLASS::*& vfKill)(bool free); void Kill(bool free = true);
	};

	class BetaSurport;

	class CardImages;

	class InternetManager;

	class TextureDataPiece;

	class XMLParser;

	class XMLMapIterator;

	inline void ModFlags(int& theFlags, const FlagsMod& theFlagMod) {
		theFlags = (theFlags | theFlagMod.mAddFlags) & ~theFlagMod.mRemoveFlags;
	}

	inline int GetModFlags(int theFlags, const FlagsMod& theFlagMod) {
		return(theFlags | theFlagMod.mAddFlags) & ~theFlagMod.mRemoveFlags;
	}
	void CloseJPEG2000();

	extern MTRand RandBattle;
	extern MTRand RandSample;
	extern MTRand RandAnim;
	extern WNDPROC prevproc;

	class Global {
	public:
		static void LoadAnim(Anim::Type _type, bool preLoading);
		static bool LoadAnim(const std_string* theFilename, AnimDefinition* theDefinition);
		static Attacher* AttachAnim(ID<Attachment>& theAttachmentID, Anim* theReanimation, float theOffsetX, float theOffsetY);
		static Attacher* AttachParticle(ID<Attachment>& theAttachmentID, ParticleSystem* theParticle, float theOffsetX, float theOffsetY);
	};

};