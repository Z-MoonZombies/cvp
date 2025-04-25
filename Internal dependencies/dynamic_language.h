#pragma once
#include "cvp.h"


#ifndef CVP
namespace Pvz { extern void reVirtual(); }
	inline DWORD  __loaderInit() {
		if (!__inPvz())return 0xFEEDDEADul;
		DWORD temp;
		VirtualProtect((LPVOID)0x400000ul, 0x75E000ul - 0x400000ul, PAGE_EXECUTE_READWRITE, &temp);
		if (PvzHeapHandle) HeapDestroy(PvzHeapHandle);
		PvzHeapHandle = GetProcessHeap();
		Pvz::reVirtual();
		return 0xFEEDDEADul;
	}
	__declspec(selectany)__declspec(dllexport)DWORD __run__loaderInit = __loaderInit();
#endif
#ifdef CVP
	using _f_apinotfound = CTformat<CTformat_buffer<void>, MakeCTstr(u8"API not found: "), const char*>;
	__declspec(selectany)HMODULE cvpMain = Cvp::RegRead<HMODULE>(u8"cvpMain");
#define CVP_OBJECT(type,name,...)																\
	__declspec(selectany)type& __object__helper__ ## name = []()->type&{						\
		type& (*__func)(void) = (type& (__cdecl*)(void))GetProcAddress(cvpMain, #name);			\
		if (__func)return __func();																\
		Cvp::error(_f_apinotfound::format(u8## #name));											\
	}();																						\
	inline type& name(){ return __object__helper__ ## name; }

#define CVP_FUNC(ret,name,param,args,...)														\
	__declspec(selectany)ret(__cdecl*__func__helper__ ## name)param=[]()->ret(__cdecl*)param{	\
		ret(*__func)param = (ret(__cdecl*)param)GetProcAddress(cvpMain,u8## #name);				\
		if (__func)return __func;																\
		Cvp::error(_f_apinotfound::format(u8## #name));											\
	}();																						\
	inline ret name param{return __func__helper__ ## name args;	}

#define CVP_STATIC(type,name,addr)																\
	__declspec(selectany) type* __static__helper__ ## name=[]()->type*{							\
		type* (*__func)(void) = (type* (__cdecl*)(void))GetProcAddress(cvpMain, #name);			\
		if (__func)return __func();																\
		Cvp::error(_f_apinotfound::format(u8## #name));											\
	}();																						\
	inline type* name() {return __static__helper__ ## name;	}

#else

#define CVP_OBJECT(type,name,...)																\
	__declspec(selectany)type __object__helper__ ## name __VA_ARGS__;							\
	extern"C" inline __declspec(dllexport)type& __cdecl name(){	return __object__helper__ ## name;}

#define CVP_FUNC(ret,name,param,args,...)														\
	extern"C" inline __declspec(dllexport)ret __cdecl name param __VA_ARGS__

#define CVP_STATIC(type,name,addr)																\
	extern"C" inline __declspec(dllexport)type* __cdecl name(){	return addr; }

#endif
namespace Cvp {


	CVP_OBJECT(vector<function<void(void)>>, __cvpinit_ereg_base, {});//标签注册器构造
	CVP_OBJECT(vector<function<void(void)>>, __cvpinit_enum_base, {});//标签同步
	CVP_OBJECT(vector<function<void(void)>>, __cvpinit_base_base, {});//数据库构造
	CVP_OBJECT(vector<function<void(void)>>, __cvpinit_cach_base, {});//数据库同步
	CVP_OBJECT(vector<function<void(void)>>, __cvpinit_data_base, {});//数据同步
	CVP_OBJECT(vector<void(__cdecl*)(void)>, __cvpinit_fnal_base, {});//插件初始化
	CVP_OBJECT(vector<function<void(void)>>, __cvpdestroy_base, {});//插件初始化
	template<typename F>void __cvpinit_ereg(F&& f) { __cvpinit_ereg_base().emplace_back(forward<F>(f)); }
	template<typename F>void __cvpinit_enum(F&& f) { __cvpinit_enum_base().emplace_back(forward<F>(f)); }
	template<typename F>void __cvpinit_base(F&& f) { __cvpinit_base_base().emplace_back(forward<F>(f)); }
	template<typename F>void __cvpinit_cach(F&& f) { __cvpinit_cach_base().emplace_back(forward<F>(f)); }
	template<typename F>void __cvpinit_data(F&& f) { __cvpinit_data_base().emplace_back(forward<F>(f)); }
	inline void __cvpinit_fnal(void(__cdecl* f)(void)) { __cvpinit_fnal_base().emplace_back(f); }
	template<typename F>void __cvpdestroy(F&& f) { __cvpdestroy_base().emplace_back(forward<F>(f)); }
	CVP_OBJECT(void*, __funcswap, =nullptr);
	CVP_OBJECT(bool, __cvpinited, =false);


	template<typename _Ret, typename... Args>
	class _FunctorBase {
		_FunctorBase<_Ret, Args...>* __prev;
		function<_Ret(Args...)> __func;
		static _FunctorBase<_Ret, Args...>*& __get_swap() { return(_FunctorBase<_Ret, Args...>*&)__funcswap(); }
	public:
		using Ret = _Ret;
		_FunctorBase(function<Ret(Args...)>&& in) : __prev(nullptr), __func(move(in)) {}
		_FunctorBase(const function<Ret(Args...)>& in) : __prev(nullptr), __func(in) {}
		_FunctorBase(Ret&& ret) :__prev(nullptr), __func([ret = move(ret)](Args...)->Ret{return ret; }) {}
		_FunctorBase(const Ret& ret) :__prev(nullptr), __func([ret](Args...)->Ret {return ret; }) {}
		_FunctorBase(const _FunctorBase<Ret, Args...>& that) : __prev(nullptr), __func(that.__func) { if (that.__prev)__prev = new _FunctorBase<Ret, Args...>(*that.__prev); }
		~_FunctorBase() { delete __prev; }
		_FunctorBase<Ret, Args...>& operator=(const _FunctorBase<Ret, Args...>& that) {
			if (this == &that) return *this;
			delete __prev;
			__func = that.__func;
			if (that.__prev)__prev = new _FunctorBase<Ret, Args...>(*that.__prev);
			return *this;
		}
		template<typename F>
		_FunctorBase<Ret, Args...>& operator+=(F&& that) {
			__prev = new _FunctorBase<Ret, Args...>(move(*this));
			__func = forward<F>(that);
			return *this;
		}
		Ret operator()(Args... args)const {
			_FunctorBase<Ret, Args...>* temp = __get_swap();
			__get_swap() = __prev;
			Ret ans = __func(args...);
			__get_swap() = temp;
			return ans;
		}
		static Ret Recur(Args... args) {
			if (__get_swap())return(*__get_swap())(args...);
			return Ret();
		}
	};
	template<typename ...Args>
	class _FunctorBase<void, Args...> {
		_FunctorBase<void, Args...>* __prev;
		function<void(Args...)> __func;
		static _FunctorBase<void, Args...>*& __get_swap() { return(_FunctorBase<void, Args...>*&)__funcswap(); }
	public:
		using Ret = void;
		_FunctorBase(function<Ret(Args...)>&& in) : __prev(nullptr), __func(move(in)) {}
		_FunctorBase(const function<Ret(Args...)>& in) : __prev(nullptr), __func(in) {}
		_FunctorBase() :__prev(nullptr), __func([](Args...)->Ret {return; }) {}
		_FunctorBase(const _FunctorBase<Ret, Args...>& that) : __prev(nullptr), __func(that.__func) { if (that.__prev)__prev = new _FunctorBase<Ret, Args...>(*that.__prev); }
		~_FunctorBase() { delete __prev; }
		_FunctorBase<Ret, Args...>& operator=(const _FunctorBase<Ret, Args...>& that) {
			if (this == &that) return *this;
			delete __prev;
			__func = that.__func;
			if (that.__prev)__prev = new _FunctorBase<Ret, Args...>(*that.__prev);
			return *this;
		}
		template<typename F>
		_FunctorBase<Ret, Args...>& operator+=(F&& that) {
			__prev = new _FunctorBase<Ret, Args...>(move(*this));
			__func = forward<F>(that);
			return *this;
		}
		Ret operator()(Args... args)const {
			_FunctorBase<Ret, Args...>* temp = __get_swap();
			__get_swap() = __prev;
			__func(args...);
			__get_swap() = temp;
			return;
		}
		static Ret Recur(Args... args) {
			if (__get_swap())return(*__get_swap())(args...);
		}
	};
	template <class _Fty> struct _Get_FunctorBase;
#define _Get_FunctorBase(CALL_OPT,X1,X2,X3)\
 template <class _Ret,class... _Types> struct _Get_FunctorBase<_Ret CALL_OPT(_Types...)> { using type = typename _FunctorBase<_Ret,_Types...>; };
	_NON_MEMBER_CALL(_Get_FunctorBase, X1, X2, X3)
#undef _Get_FunctorBase
		template<typename _Fty>
	class Functor {
		using Ret = typename _Get_FunctorBase<_Fty>::type::Ret;
		using FunctorTy = typename _Get_FunctorBase<_Fty>::type;
		struct ref {
			FunctorTy __func;
			int __num;
		public:
			template<typename...Args> ref(Args...args) :__func(forward<Args>(args)...), __num(1) {}
			FunctorTy& Func() { return __func; }
			int& Num() { return __num; }
		};
		ref* __p;
	public:
		template<typename ...Args> Functor(Args&&... args) :__p(new ref(forward<Args>(args)...)) {}
		Functor(const Functor<_Fty>& that) :__p(that.__p) { if (__p)++__p->Num(); }
		Functor(Functor<_Fty>&& that) :__p(that.__p) { that.__p = nullptr; }
		Functor<_Fty>& operator=(const Functor<_Fty>& that) { if (this == &that) return *this; if (__p && --__p->Num() == 0)delete __p; __p = new ref(move(that.__p->Func())); return *this; }
		Functor<_Fty>& operator=(Functor<_Fty>&& that)noexcept { if (__p && --__p->Num() == 0)delete __p; __p = that.__p; that.__p = nullptr; return *this; }
		~Functor() { if (__p && --__p->Num() == 0)delete __p; }
		template<typename ...Args> Ret operator()(Args&&... args)const { return __p->Func()(forward<Args>(args)...); }
		template<typename ...Args> static Ret Recur(Args&&... args) { return FunctorTy::Recur(forward<Args>(args)...); }
		template<typename T>Functor<_Fty>& operator+=(T&& that) { __p->Func() += forward<T>(that); return *this; }
		Functor<_Fty> MakeBranch()const { return Functor<_Fty>(__p->Func()); }
		Functor<_Fty>& Branch() { Functor<_Fty> temp(__p->Func()); *this = temp; return *this; }
	};


	template<typename T>
	struct TypeTrait {
		static_assert(sizeof(typename T::Type) == sizeof(DWORD), u8"TypeTrait only support enum class with size of 4 bytes");
		using type = typename T::Type;
		enum class prop :DWORD { CONSTRUCT = sizeof(Functor<void(void)>) * 0, DESTRUCT = sizeof(Functor<void(void)>) * 1, SERIALIZE = sizeof(Functor<void(void)>) * 2, DESERIALIZE = sizeof(Functor<void(void)>) * 3, PROP_BEGIN = sizeof(Functor<void(void)>) * 4 };
		enum class pool :DWORD { DEFAULT, POOL_BEGIN };
		enum class member :DWORD;
	};
	template<typename T> using __type = typename TypeTrait<T>::type;
	template<typename T> using __prop = typename TypeTrait<T>::prop;
	template<typename T> using __pool = typename TypeTrait<T>::pool;
	template<typename T> using __member = typename TypeTrait<T>::member;


	class _OffsetRegisterBase {
		hash32 __buffer;
		DWORD __begin;
		DWORD __end;
	public:
		_OffsetRegisterBase() : __buffer(), __begin(0), __end(0) {}
		template<typename T>
		DWORD AllocateAlignment() {
			DWORD ans = alignof(T) + ((__end - 1) & ~(alignof(T) - 1));
			__end = ans + sizeof(T);
			return ans;
		}
		pair<DWORD, string>& EnumReg(string&& label) {
			auto&& p = *(pair<DWORD, string>**) & __buffer[label];
			if (!p) p = new pair<DWORD, string>(__end++, move(label));
			return *p;
		}
		pair<DWORD, string>* EnumReg(string&& label, DWORD val) {
			if (val >= __begin)return nullptr;
			auto&& p = *(pair<DWORD, string>**) & __buffer[label];
			if (!p) p = new pair<DWORD, string>(val, move(label));
			return p;
		}
		template<typename FieldT>
		pair<DWORD, string>& FieldReg(string&& label) {
			auto&& p = *(pair<DWORD, string>**) & __buffer[label];
			if (!p)p = new pair<DWORD, string>(AllocateAlignment<FieldT>(), move(label));
			return *p;
		}
		pair<DWORD, string>* Query(DWORD hash) {
			return (pair<DWORD, string>*)__buffer.find(hash);
		}
		pair<DWORD, string>* Query(string_view label) {
			return (pair<DWORD, string>*)__buffer.find(label);
		}
		DWORD Reserve(DWORD addr = 0) {
			if (addr > __begin && __begin == __end)__begin = __end = addr;
			return __begin;
		}
		DWORD Next() {
			return __end;
		}
		hash32* Container() { return &__buffer; }
	};

	class _DeriveManagerBase {
	public:
		template<typename PropT>
		class _PropBuffer {
			BYTE* __buffer;
		public:
			_PropBuffer() :__buffer(nullptr) {}
			_PropBuffer(BYTE* buffer) :__buffer(buffer) {}
			template<typename FieldT>
			FieldT& Get(PropT prop)const { return *(FieldT*)(__buffer + (DWORD)prop); }
		};
		template<typename TypeT, typename FieldT>
		class _TypeBuffer {
			DWORD __gap;
			BYTE* __buffer;
		public:
			_TypeBuffer() :__gap(0), __buffer(nullptr) {}
			_TypeBuffer(DWORD gap, BYTE* buffer) :__gap(gap), __buffer(buffer) {}
			_TypeBuffer(const _TypeBuffer& that) :__gap(that.__gap), __buffer(that.__buffer) {}
			_TypeBuffer& operator=(const _TypeBuffer& that) { __gap = that.__gap; __buffer = that.__buffer; return *this; }
			FieldT& Get(TypeT type = (TypeT)0xfffffffful)const { return *(FieldT*)(__buffer + __gap * (DWORD)type); }
		};
	private:
		const DWORD __propSize;
		BYTE* __buffer;
		BYTE* __default;
	public:
		_DeriveManagerBase(DWORD typesize, DWORD propsize) :__propSize(propsize) {
			__default = valloc(typesize * propsize + propsize);
			__buffer = __default + propsize;
		}
		template<typename T>
		void __initbasicfunc(DWORD typesize) {
			for (DWORD i = 0; i <= typesize; ++i) {
				new (__default + 0 * sizeof(Functor<void(void)>) + i * __propSize) Functor<void(typename ObjectInterface<T>::Object*)>();
				new (__default + 1 * sizeof(Functor<void(void)>) + i * __propSize) Functor<void(typename ObjectInterface<T>::Object*)>();
				new (__default + 2 * sizeof(Functor<void(void)>) + i * __propSize) Functor<void(typename ObjectInterface<T>::Object*, DataMap*)>();
				new (__default + 3 * sizeof(Functor<void(void)>) + i * __propSize) Functor<void(typename ObjectInterface<T>::Object*, DataMap*)>();
			}
		}
		template<typename PropT>
		const _PropBuffer<PropT> GetPropBuffer(DWORD type)const { return _PropBuffer<PropT>(__buffer + type * __propSize); }
		template<typename TypeT, typename FieldT>
		const _TypeBuffer<TypeT, FieldT> GetTypeBuffer(DWORD prop)const { return _TypeBuffer<TypeT, FieldT>(__propSize, __buffer + prop); }
		template<typename FieldT>
		FieldT& Get(DWORD prop, DWORD type)const { return *(FieldT*)(__buffer + type * __propSize + prop); }
	};
	class _ObjectManagerBase {
	public:
		struct _ObjectIDBase {
			WORD __index;
			WORD __rank;
		};
		class _ObjectHeadBase {
			friend class _ObjectManagerBase;
			_ObjectIDBase __id;
			_ObjectManagerBase* __base;
			mutable DWORD __type;
			mutable _DeriveManagerBase::_PropBuffer<DWORD> __prop;
			BYTE* operator[](DWORD offset)const { return(BYTE*)(this + 1) + offset; }
			_ObjectHeadBase() = delete;
			_ObjectHeadBase(const _ObjectHeadBase&) = delete;
			_ObjectHeadBase(_ObjectHeadBase&&) = delete;
			_ObjectHeadBase& operator =(const _ObjectHeadBase&) = delete;
			_ObjectHeadBase& operator =(_ObjectHeadBase&&) = delete;
		public:
			template<typename FieldT>
			FieldT& _GetMember(DWORD offset)const { return *(FieldT*)((BYTE*)(this + 1) + offset); }
			template<typename FieldT>
			FieldT& _GetProp(DWORD offset)const { return __prop.Get<FieldT>(offset); }
			_ObjectIDBase _ID()const { return __id; }
			_ObjectManagerBase* _Base()const { return __base; }
			DWORD& _Type()const { return __type; }
			_DeriveManagerBase::_PropBuffer<DWORD>& _Prop()const { return __prop; }
		};
	private:
		const DWORD __memberSize;
		const DWORD __objectsize;
		WORD __nextindex;
		WORD __nextrank;
		WORD __capacity;
		mutable WORD __bucketsize;
		int __size;
		mutable BYTE* __buffer[0x100u];
		_ObjectHeadBase& __alloc(WORD index)const {
			while ((index >> 8) >= __bucketsize) __buffer[__bucketsize] = valloc(__objectsize << 8), ++__bucketsize;
			return *(_ObjectHeadBase*)(__buffer[index >> 8] + (index & 0xffu) * __objectsize);
		}
		bool __check(WORD index)const {
			if (index >> 8 >= __bucketsize)return false;
			return ((_ObjectHeadBase*)(__buffer[index >> 8] + (index & 0xffu) * __objectsize))->__id.__rank;
		}
		bool __check(WORD index, WORD rank)const {
			if (index >> 8 >= __bucketsize)return false;
			return rank == ((_ObjectHeadBase*)(__buffer[index >> 8] + (index & 0xffu) * __objectsize))->__id.__rank;
		}
		bool __check(_ObjectIDBase id)const {
			if (id.__index >> 8 >= __bucketsize)return false;
			return id.__rank == ((_ObjectHeadBase*)(__buffer[id.__index >> 8] + (id.__index & 0xffu) * __objectsize))->__id.__rank;
		}
	public:
		_ObjectManagerBase(DWORD memberSize) :__memberSize(memberSize), __objectsize(sizeof(_ObjectHeadBase) + memberSize), __nextindex(0), __nextrank(1), __capacity(0), __bucketsize(0), __size(0), __buffer() {}
		_ObjectHeadBase& Alloc(DWORD type, _DeriveManagerBase::_PropBuffer<DWORD> prop) {
			WORD index = __nextindex;
			++__size;
			if (__nextindex >= __capacity) {
				_ObjectHeadBase& ans = __alloc(index);
				++__nextindex;
				++__capacity;
				ans.__base = this;
				ans.__type = type;
				ans.__prop = prop;
				ans.__id.__index = index;
				ans.__id.__rank = __nextrank++;
				if (!__nextrank)__nextrank = 1;
				return ans;
			} else {
				_ObjectHeadBase& ans = __alloc(index);
				__nextindex = ans.__id.__index;
				ans.__base = this;
				ans.__type = type;
				ans.__prop = prop;
				ans.__id.__index = index;
				ans.__id.__rank = __nextrank++;
				if (!__nextrank)__nextrank = 1;
				return ans;
			}
		}
		void Free(_ObjectHeadBase& head) {
			--__size;
			WORD temp = head.__id.__index;
			memset(head[0], 0, __memberSize);
			head.__id.__index = __nextindex;
			head.__id.__rank = 0;
			__nextindex = temp;
		}
		void Free(_ObjectIDBase id) {
			--__size;
			if (!__check(id))return;
			_ObjectHeadBase& next = __alloc(id.__index);
			memset(next[0], 0, __memberSize);
			next.__id.__index = __nextindex;
			next.__id.__rank = 0;
			__nextindex = id.__index;
		}
		_ObjectHeadBase* Get(_ObjectIDBase id)const {
			if (__check(id))return &__alloc(id.__index);
			return nullptr;
		}
		class iterator {
			friend class _ObjectManagerBase;
			_ObjectHeadBase* __p;
			const _ObjectManagerBase* __base;
			WORD __index;
			iterator(const _ObjectManagerBase* base, WORD index) :__p(&base->__alloc(index)), __base(base), __index(index) {}
			iterator& fallback() {
				do {
					if (__p->__id.__rank)break;
					if (++__index & 0xffu)__p = (_ObjectHeadBase*)((BYTE*)__p + __base->__objectsize);
					else __p = &__base->__alloc(__index);
				} while (*this != __base->end());
				return *this;
			}
		public:
			const _ObjectHeadBase& operator*()const { return *__p; }
			_ObjectHeadBase* const& operator->()const { return __p; }
			iterator& operator++() {
				do {
					if (++__index & 0xffu)__p = (_ObjectHeadBase*)((BYTE*)__p + __base->__objectsize);
					else __p = &__base->__alloc(__index);
				} while (*this != __base->end() && !__p->__id.__rank);
				return *this;
			}
			iterator& operator--() {
				do {
					if (__index & 0xffu)--__index, __p = (_ObjectHeadBase*)((BYTE*)__p - __base->__objectsize);
					else __p = &__base->__alloc(--__index);
				} while (*this != __base->begin() && !__p->__id.__rank);
				return *this;
			}
			bool operator==(const iterator& that)const { return __p == that.__p; }
			bool operator!=(const iterator& that)const { return __p != that.__p; }
		};
		iterator begin()const { return iterator(this, 0).fallback(); }
		iterator end()const { return iterator(this, __capacity); }
		int __serializeN()const { return offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex) + __capacity * (sizeof(DWORD) + sizeof(_ObjectIDBase)); }
		void serialize(BYTE* buffer)const {
			memcpy(buffer, &__nextindex, (offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex)));
			buffer += (offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex));
			_ObjectIDBase* tid = new _ObjectIDBase[__capacity];
			DWORD* ttype = new DWORD[__capacity];
			for (WORD i = 0; i < __capacity; ++i) tid[i] = __alloc(i).__id, ttype[i] = __alloc(i).__type;
			memcpy(buffer, tid, __capacity * sizeof(_ObjectIDBase));
			memcpy(buffer + __capacity * sizeof(_ObjectIDBase), ttype, __capacity * sizeof(DWORD));
			delete[] tid;
			delete[] ttype;
		}
		void deserialize(BYTE* buffer, int len) {
			for (WORD i = 0; i < __bucketsize; ++i)vfree(__buffer[i]);
			memcpy(&__nextindex, buffer, (offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex)));
			buffer += (offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex));
			if (len != offsetof(_ObjectManagerBase, __buffer[0]) - offsetof(_ObjectManagerBase, __nextindex) + __capacity * (sizeof(DWORD) + sizeof(_ObjectIDBase)))error(u8"pool deserialize failed: broken data");
			for (WORD i = 0; i < __bucketsize; ++i)__buffer[i] = valloc(__objectsize << 8);
			_ObjectIDBase* tid = new _ObjectIDBase[__capacity];
			DWORD* ttype = new DWORD[__capacity];
			memcpy(tid, buffer, __capacity * sizeof(_ObjectIDBase));
			memcpy(ttype, buffer + __capacity * sizeof(_ObjectIDBase), __capacity * sizeof(DWORD));
			for (WORD i = 0; i < __capacity; ++i) __alloc(i).__id = tid[i], __alloc(i).__type = ttype[i], __alloc(i).__base = this;
			delete[] tid;
			delete[] ttype;
		}
	};
}
namespace Template {
	template<>inline int serializeN(const Cvp::_ObjectManagerBase* _this) { if (_this) return _this->__serializeN(); else return 0; }
	template<>inline void serialize(const Cvp::_ObjectManagerBase& _this, BYTE* buffer) { _this.serialize(buffer); }
	template<>inline void deserialize(Cvp::_ObjectManagerBase& _this, BYTE* buffer, int len) { _this.deserialize(buffer, len); }
}
namespace Cvp {


	CVP_OBJECT(hash32, __cvpdynamicclasslibrary, );
	template<typename T> class TypeInterface;
	template<typename T, typename FieldT> class PropInterface;
	template<typename T> class ObjectInterface;
	template<typename T, typename FieldT> class MemberInterface;

	template<typename T>
	class DynamicClassManager {
		using DynamicBase = tuple<_OffsetRegisterBase*, vector<DWORD>*, _DeriveManagerBase*, _ObjectManagerBase*>;
		using DeriveType = typename __type<T>;
		using PropType = typename __prop<T>;
		using PoolType = typename __pool<T>;
		using MemberType = typename __member<T>;
		static hash32& __library() { return __cvpdynamicclasslibrary(); }
		static inline _DeriveManagerBase* __derivebase = nullptr;
		static inline _ObjectManagerBase* __objectbase = nullptr;
		using _f_invalidreg = CTformat<CTformat_buffer<void>, MakeCTstr(u8"invalid "), const char*, MakeCTstr(u8" reg : label = "), const char*, MakeCTstr(u8":: "), const char*, MakeCTstr(u8", val = "), DWORD>;
		using _f_regconflicted = CTformat<CTformat_buffer<void>, const char*, MakeCTstr(u8" reg conflicted: label = "), const char*, MakeCTstr(u8"::"), const char*, MakeCTstr(u8",old = "), DWORD, MakeCTstr(u8",new = "), DWORD>;
	public:
		class TypeRegister {
			friend class DynamicClassManager;
			static inline _OffsetRegisterBase* __base = nullptr;
			static inline vector<DWORD>* __rebuffer = nullptr;
		public:
			static DeriveType Reg(string&& label) {
				DWORD ans= __base->EnumReg(move(label)).first;
				__rebuffer->reserve(ans);
				__rebuffer[0][ans] = hash32::hash(label);
				return (DeriveType)ans;
			}
			static DeriveType Reg(string&& label, DeriveType val) {
				if ((DWORD)val == 0xfffffffful)return Reg(move(label));
				string label2 = label;
				DWORD hash = hash32::hash(label);
				auto p = __base->EnumReg(move(label2), (DWORD)val);
				if (!p)error(_f_invalidreg::format(u8"Type", typeid(T).name(), label.data(), (DWORD)val));
				if (p->first != (DWORD)val)error(_f_regconflicted::format(u8"Type", typeid(T).name(), label.data(), p->first, (DWORD)val));
				__rebuffer[0][(DWORD)val] = hash;
				return val;
			}
			static DeriveType Query(string_view label) {
				auto p = __base->Query(label);
				if (p)return (DeriveType)p->first;
				return (DeriveType)0xfffffffful;
			}
			static DeriveType Query(DWORD hash) {
				auto p = __base->Query(hash);
				if (p)return (DeriveType)p->first;
				return (DeriveType)0xfffffffful;
			}
			static DWORD Query(DeriveType key, DWORD _default = 0x0ul) {
				if ((DWORD)key >= __rebuffer->size())return _default;
				return __rebuffer[0][(DWORD)key];
			}
			static DWORD Size() { return __base->Next(); }
		};
		class PropRegister {
			friend class DynamicClassManager;
			static inline _OffsetRegisterBase* __base = nullptr;
		public:
			template<typename FieldT>
			static PropType Reg(string&& label) {
				return (PropType)__base->FieldReg<FieldT>(move(label)).first;
			}
			static DWORD Size() { return ((__base->Next() - 1) | 0xf) + 1; }
		};
		class PoolRegister {
			friend class DynamicClassManager;
			static inline _OffsetRegisterBase* __base = nullptr;
		public:
			static PoolType Reg(string&& label) {
				DWORD ans = __base->EnumReg(move(label)).first;
				return (PoolType)ans;
			}
			static PoolType Reg(string&& label, PoolType val) {
				if ((DWORD)val == 0xfffffffful)return Reg(move(label));
				string label2 = label;
				auto p = __base->EnumReg(move(label2), (DWORD)val);
				if (!p)error(_f_invalidreg::format(u8"Pool", typeid(T).name(), label.data(), (DWORD)val));
				if (p->first != (DWORD)val)error(_f_regconflicted::format(u8"Pool", typeid(T).name(), label.data(), p->first, (DWORD)val));
				return val;
			}
			static PoolType Query(string_view label) {
				auto p = __base->Query(label);
				if (p)return (PoolType)p->first;
				return (PoolType)0xfffffffful;
			}
			static PoolType Query(DWORD hash) {
				auto p = __base->Query(hash);
				if (p)return (PoolType)p->first;
				return (PoolType)0xfffffffful;
			}
			static DWORD Size() { return __base->Next(); }
		};
		class MemberRegister {
			friend class DynamicClassManager;
			static inline _OffsetRegisterBase* __base = nullptr;
		public:
			template<typename FieldT>
			static MemberType Reg(string&& label) {
				return (MemberType)__base->FieldReg<FieldT>(move(label)).first;
			}
			static DWORD Size() { return ((__base->Next() - 1) | 0xf) + 1; }
		};
		static void __init() {
			static bool finished = false;
			if (finished)return;
			finished = true;
			__cvpinit_ereg(
				[]() {
					auto&& p = (DynamicBase*&)__library()[typeid(T).name()];
					if (!p)p = new DynamicBase(new _OffsetRegisterBase[4](), new vector<DWORD>{}, nullptr, nullptr);
					TypeRegister::__base = get<0>(*p);
					PropRegister::__base = get<0>(*p) + 1;
					PoolRegister::__base = get<0>(*p) + 2;
					MemberRegister::__base = get<0>(*p) + 3;
					using _f_regreserveconflicted = CTformat<CTformat_buffer<void>, const char*, MakeCTstr(u8"Register reserve confilcted: typebase = "), const char*, MakeCTstr(u8",reserve = "), DWORD, MakeCTstr(u8",occupied = "), DWORD>;
					if (TypeRegister::__base->Reserve((DWORD)DeriveType::ENM_BEGIN) < (DWORD)DeriveType::ENM_BEGIN)error(_f_regreserveconflicted::format(u8"Type", typeid(T).name(), (DWORD)DeriveType::ENM_BEGIN, TypeRegister::__base->Reserve((DWORD)DeriveType::ENM_BEGIN)));
					if (PropRegister::__base->Reserve((DWORD)PropType::PROP_BEGIN) < (DWORD)PropType::PROP_BEGIN)error(_f_regreserveconflicted::format(u8"Prop", typeid(T).name(), (DWORD)PropType::PROP_BEGIN, PropRegister::__base->Reserve((DWORD)PropType::PROP_BEGIN)));
					if (PoolRegister::__base->Reserve((DWORD)PoolType::POOL_BEGIN) < (DWORD)PoolType::POOL_BEGIN)error(_f_regreserveconflicted::format(u8"Pool", typeid(T).name(), (DWORD)PoolType::POOL_BEGIN, PoolRegister::__base->Reserve((DWORD)PoolType::POOL_BEGIN)));
					TypeRegister::__rebuffer = get<1>(*p);
					if (TypeRegister::__rebuffer->size() < (DWORD)DeriveType::ENM_BEGIN)TypeRegister::__rebuffer->resize((DWORD)DeriveType::ENM_BEGIN, 0xfffffffful);
				});
			__cvpinit_base(
				[]() {
					auto&& p = *(DynamicBase*)__library()[typeid(T).name()];
					if (!get<2>(p)) {
						get<2>(p) = new _DeriveManagerBase(TypeRegister::Size(), PropRegister::Size());
						get<2>(p)->__initbasicfunc<T>(TypeRegister::Size());
						get<3>(p) = (_ObjectManagerBase*)new BYTE[PoolRegister::Size() * sizeof(_ObjectManagerBase)];
						for (DWORD i = 0; i < PoolRegister::Size(); ++i)new(get<3>(p) + i)_ObjectManagerBase(MemberRegister::Size());
					}
					__derivebase = get<2>(p);
					__objectbase = get<3>(p);
				}
			);
			__cvpdestroy(
				[]() {
					return;
				}
			);
		}
		static _DeriveManagerBase::_PropBuffer<__prop<T>> GetPropBuffer(DeriveType type) { return __derivebase->GetPropBuffer<__prop<T>>((DWORD)type); }
		template<typename FieldT>
		static _DeriveManagerBase::_TypeBuffer<__type<T>, FieldT> GetTypeBuffer(PropType prop) { return __derivebase->GetTypeBuffer<__type<T>, FieldT>((DWORD)prop); }
		template<typename FieldT>
		static FieldT& Get(PropType prop, DeriveType type = (DeriveType)0xfffffffful) { return __derivebase->Get<FieldT>((DWORD)prop, (DWORD)type); }
		static _ObjectManagerBase* GetPool(PoolType pool) { return __objectbase + (DWORD)pool; }
	};


	using _f_needstaticconstruct = CTformat<CTformat_buffer<void>, const char*, MakeCTstr(u8"Interface shoule be constructed statically: "), const char*, MakeCTstr(u8"Interface<"), const char*, MakeCTstr(u8">:: "), const char*>;


	template<typename T>
	class TypeInterface {
		using DeriveType = typename __type<T>;
		using PropType = typename __prop<T>;
		using Manager = typename DynamicClassManager<T>;
		using Register = typename Manager::TypeRegister;
		DeriveType __type;
		_DeriveManagerBase::_PropBuffer<PropType> __buffer;
		DWORD __hash;
		TypeInterface(DeriveType type, _DeriveManagerBase::_PropBuffer<PropType> buffer, DWORD hash) :__type(type), __buffer(buffer), __hash(hash) {}
	public:
		TypeInterface(string&& name, function<void(Cvp::TypeInterface<T>*)>&& datainit, DeriveType _default = (DeriveType)0xfffffffful) :__type(_default), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited())error(_f_needstaticconstruct::format(u8"Type", u8"Type", typeid(T).name(), name.data()));
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__type = Register::Reg(move(name), this->__type); });
			__cvpinit_cach([this]() {this->__buffer = Manager::GetPropBuffer(this->__type); });
			__cvpinit_data([this, datainit = move(datainit)]()->void{ datainit(this); });
			__cvpdestroy([]() {	return;	});
		}
		TypeInterface(string&& name, DeriveType _default = (DeriveType)0xfffffffful) :__type(_default), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited()) {
				if (_default != (DeriveType)0xfffffffful)error(_f_needstaticconstruct::format(u8"Type", u8"Type", typeid(T).name(), name.data()));
				__type = Register::Query(__hash);
				__buffer = Manager::GetPropBuffer(__type);
				return;
			}
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__type = Register::Reg(move(name), this->__type); });
			__cvpinit_cach([this]() {this->__buffer = Manager::GetPropBuffer(this->__type); });
			__cvpdestroy([]() {	return;	});
		}
		static TypeInterface MakeGuest(string_view name) {
			auto hash = Cvp::hash32::hash(name);
			auto type = Register::Query(hash);
			return TypeInterface(type, Manager::GetPropBuffer(type), hash);
		}
		DeriveType Type()const { return __type; }
		_DeriveManagerBase::_PropBuffer<PropType> Proper()const { return __buffer; }
		bool operator==(const TypeInterface<T>& that)const { return Type() == that.Type(); }
		bool operator!=(const TypeInterface<T>& that)const { return Type() != that.Type(); }
		template<typename FieldT>
		FieldT& operator[](const PropInterface<T, FieldT>& prop)const { return __buffer.Get<FieldT>(prop.Prop()); }
		template<typename FieldT>
		FieldT& Get(const PropInterface<T, FieldT>& prop)const { return __buffer.Get<FieldT>(prop.Prop()); }
		template<typename FieldT, typename... Args>
		FieldT& Set(const PropInterface<T, FieldT>& prop, Args&&... args)const { return __buffer.Get<FieldT>(prop.Prop()) = FieldT(forward<Args>(args)...); }
	};


	template<typename T, typename FieldT>
	class PropInterface {
		using DeriveType = typename __type<T>;
		using PropType = typename __prop<T>;
		using Manager = typename DynamicClassManager<T>;
		using Register = typename Manager::PropRegister;
		PropType __prop;
		typename _DeriveManagerBase::_TypeBuffer<DeriveType, FieldT> __buffer;
		DWORD __hash;
	public:
		PropInterface(string&& name, function<void(Cvp::PropInterface<T, FieldT>*)>&& datainit, FieldT&& datadefault = FieldT()) :__prop((PropType)0xfffffffful), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited())error(_f_needstaticconstruct::format(u8"Prop", u8"Prop", typeid(T).name(), name.data()));
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__prop = Register::Reg<FieldT>(move(name)); });
			__cvpinit_cach([this]() {this->__buffer = Manager::GetTypeBuffer<FieldT>(this->__prop); });
			__cvpinit_data([this, datadefault = move(datadefault), datainit = move(datainit)](){ new(&this->Get())FieldT(datadefault); for (auto&& p = this->begin(); p != this->end(); ++p)new(&*p)FieldT(datadefault);  datainit(this); });
			__cvpdestroy([]() {	return;	});
		}
		PropInterface(string&& name) :__prop((PropType)0xfffffffful), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited()) {
				return;
			}
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__prop = Register::Reg<FieldT>(move(name)); });
			__cvpinit_cach([this]() {this->__buffer = Manager::GetTypeBuffer<FieldT>(this->__prop); });
			__cvpdestroy([]() {	return;	});
		}
		PropType Prop()const { return __prop; }
		bool operator==(const PropInterface<T, FieldT>& that)const { return Prop() == that.Prop(); }
		bool operator!=(const PropInterface<T, FieldT>& that)const { return Prop() != that.Prop(); }
		class iterator {
			DWORD __index;
			const typename _DeriveManagerBase::_TypeBuffer<DeriveType, FieldT>* __base;
		public:
			iterator(DWORD index, const typename _DeriveManagerBase::_TypeBuffer<DeriveType, FieldT>* base) :__index(index), __base(base) {}
			FieldT& operator*()const { return __base->Get((DeriveType)__index); }
			FieldT* const operator->()const { return &__base->Get((DeriveType)__index); }
			iterator& operator++() { ++__index; return *this; }
			iterator& operator--() { --__index; return *this; }
			bool operator==(const iterator& that)const { return __index == that.__index; }
			bool operator!=(const iterator& that)const { return __index != that.__index; }
		};
		iterator begin()const { return iterator(0, &__buffer); }
		iterator end()const { return iterator(typename Manager::TypeRegister::Size(), &__buffer); }
		template<typename... Args>
		void SetAll(const Args&... args)const { Get() = FieldT(args...); for (auto&& p = begin(); p != end(); ++p)*p = FieldT(args...); }
		template<typename... Args>
		FieldT& SetDefault(Args&&... args)const { return Get() = FieldT(forward<Args>(args)...); }
		FieldT& operator[](DeriveType type)const { return __buffer.Get(type); }
		FieldT& operator[](const TypeInterface<T>& type)const { return Get(type.Type()); }
		FieldT& Get(DeriveType type = (DeriveType)0xfffffffful)const { return __buffer.Get(type); }
		FieldT& Get(const TypeInterface<T>& type)const { return Get(type.Type()); }
		template<typename... Args>
		FieldT& Set(DeriveType type, Args&&... args)const { return Get(type) = FieldT(forward<Args>(args)...); }
		template<typename... Args>
		FieldT& Set(const TypeInterface<T>& type, Args&&... args)const { return Get(type) = FieldT(forward< Args>(args)...); }
	};

	template<typename T>
	class ObjectInterface {
		using DeriveType = typename __type<T>;
		using PropType = typename __prop<T>;
		using MemberType = typename __member<T>;
		using PoolType = typename __pool<T>;
		using Manager = typename DynamicClassManager<T>;
		using Register = typename Manager::PoolRegister;
	public:
		class ID {
			friend class ObjectInterface;
			friend class ObjectInterface::Object;
			const typename _ObjectManagerBase::_ObjectIDBase __val;
			ID(typename _ObjectManagerBase::_ObjectIDBase val) :__val(val) {}
		};
		class Object {
			friend class ObjectInterface;
			friend class ObjectInterface::ID;
			typename _ObjectManagerBase::_ObjectHeadBase __head;
			Object() = delete;
			Object(const Object&) = delete;
			Object(Object&&) = delete;
			Object& operator=(const Object&) = delete;
			Object& operator=(Object&&) = delete;
		public:
			template<typename FieldT>
			FieldT& operator[](const MemberInterface<T, FieldT>& member)const {
				return __head._GetMember<FieldT>((DWORD)member.Member());
			}
			template<typename FieldT>
			FieldT& operator[](const PropInterface<T, FieldT>& prop)const {
				return __head._GetProp<FieldT>((DWORD)prop.Prop());
			}
			template<typename FieldT>
			FieldT& Get(MemberType member)const { return __head._Get<FieldT>((DWORD)member); }
			ID GetID()const { return ID(__head._ID()); }
			DeriveType& GetType()const { return(DeriveType&)__head._Type(); }
			_DeriveManagerBase::_PropBuffer<PropType>& GetProper()const { return(_DeriveManagerBase::_PropBuffer<PropType>&)__head._Prop(); }
			void Free() {
				__head._Base()->Free(__head);
			}
			void Delete() {
				ObjectInterface<T>::Destruct(*this);
				Free();
			}
			DataMap Serialize() {
				return ObjectInterface<T>::Serialize(*this);
			}
			void Deserialize(DataMap& buffer) {
				ObjectInterface<T>::Deserialize(*this, buffer);
			}
		};
		class iterator {
			friend class ObjectInterface<T>;
			_ObjectManagerBase::iterator __base;
			iterator(_ObjectManagerBase::iterator val) :__base(val) {}
		public:
			Object* const operator->()const { return(Object*)__base.operator->(); }
			Object& operator*()const { return *(Object*)__base.operator->(); }
			iterator& operator++() { return(iterator&)++__base; }
			iterator& operator--() { return(iterator&)--__base; }
			bool operator==(const iterator& that) { return __base == that.__base; }
			bool operator!=(const iterator& that) { return __base != that.__base; }
		};
	private:
		PoolType __pool;
		_ObjectManagerBase* __buffer;
		DWORD __hash;
		ObjectInterface(PoolType pool, _ObjectManagerBase* buffer, DWORD hash) :__pool(pool), __buffer(buffer), __hash(hash) {}
	public:
		ObjectInterface(string&& name, PoolType _default = (PoolType)0xfffffffful) : __pool(_default), __buffer(nullptr), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited()) {
				return;
			}
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__pool = Register::Reg(move(name), this->__pool); });
			__cvpinit_cach([this]() {this->__buffer = Manager::GetPool(this->__pool); });
			__cvpdestroy([]() {	return;	});
		}
		static ObjectInterface MakeGuest(string_view name) {
			auto hash = Cvp::hash32::hash(name);
			auto type = Register::Query(hash);
			return ObjectInterface(type, Manager::GetPool(type), hash);
		}
		PoolType Pool()const { return __pool; }
		bool operator==(const ObjectInterface<T>& that)const { return Pool() == that.Pool(); }
		bool operator!=(const ObjectInterface<T>& that)const { return Pool() != that.Pool(); }
		Object& Alloc(typename TypeInterface<T> type) { return (Object&)__buffer->Alloc((DWORD)type.Type(), *(_DeriveManagerBase::_PropBuffer<DWORD>*)&type.Proper()); }
		void Free(Object&& obj) { obj.Free(); }
		void Free(ID id) { __buffer->Free(id.__val); }
		static Object& Construct(Object& obj) {
			obj.GetProper().Get<Functor<void(const Object*)>>(PropType::CONSTRUCT)(&obj);
			return obj;
		}
		void Construct(ID id) {
			Object* object = Get(id);
			if (object) Construct(*object);
		}
		Object& New(const TypeInterface<T>& type) {
			return Construct(Alloc(type));
		}
		static void Destruct(Object& obj) {
			obj.GetProper().Get<Functor<void(const Object*)>>(PropType::DESTRUCT)(&obj);
		}
		void Destruct(ID id) {
			Object* object = Get(id);
			if (object) Destruct(*object);
		}
		static void Delete(Object&& obj) {
			obj.Delete();
		}
		void Delete(ID id) {
			Object* object = Get(id);
			if (object) Delete(move(*object));
		}
		void Clear() {
			for (auto&& p : *this) p.Delete();
		}
		static DataMap Serialize(const Object& obj) {
			DataMap buffer;
			obj.GetProper().Get<Functor<void(const Object*, DataMap*)>>(PropType::SERIALIZE)(&obj, &buffer);
			buffer.Sort();
			return buffer;
		}
		DataMap Serialize(ID id)const {
			Object* object = Get(id);
			if (object) return Serialize(object, buffer);
			return DataMap();
		}
		static void Deserialize(Object& obj, DataMap& buffer) {
			obj.GetProper().Get<Functor<void(const Object*, DataMap*)>>(PropType::DESERIALIZE)(&obj, &buffer);
		}
		void Deserialize(ID id, DataMap& buffer) {
			Object* object = Get(id);
			if (object) Deserialize(*object, buffer);
		}
		DataMap Serialize()const {
			DataMap ans;
			Data buffer;
			vector<DWORD> typebuffer;
			typebuffer.reserve(typename Manager::TypeRegister::Size());
			for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i) typebuffer.emplace_back(typename Manager::TypeRegister::Query((DeriveType)i));
			buffer.Push(typebuffer);
			ans.Set(0x00000001ul, move(buffer));
			buffer.Push(*__buffer);
			ans.Set(0x00000000ul, move(buffer));
			for (auto&& p : *this) {
				buffer.SetChild(Serialize(p));
				ans.Set(*(DWORD*)&p.GetID(), move(buffer));
			}
			return ans;
		}
		void Deserialize(DataMap& data) {
			Clear();
			string label;
			vector<DWORD> typebuffer;
			for (auto&& p : data) {
				if (p.first == 0x00000000ul)p.second.Pop(*__buffer);
				else if (p.first == 0x00000001ul)p.second.Pop(typebuffer);
				else {
					Object* o = Get(*(ID*)&p.first);
					if (!o) error(u8"Deserialize failed: broken data");
					o->GetType() = Manager::TypeRegister::Query(typebuffer[(DWORD)o->GetType()]);
					o->GetProper() = Manager::GetPropBuffer(o->GetType());
					Construct(*o);
					Deserialize(*o, p.second.GetChild());
				}
			}
		}
		Object* Get(ID id)const { return (Object*)__buffer->Get(id.__val); }
		iterator begin()const { return(iterator)__buffer->begin(); }
		iterator end()const { return(iterator)__buffer->end(); }
	};
	template<typename T>
	__declspec(selectany)auto defaultPool = ObjectInterface<T>(u8"__defaultPool", __pool<T>::DEFAULT);

	template<typename T, typename FieldT>
	class MemberInterface {
		using DeriveType = typename __type<T>;
		using PropType = typename __prop<T>;
		using MemberType = typename __member<T>;
		using PoolType = typename __pool<T>;
		using Manager = typename DynamicClassManager<T>;
		using Register = typename Manager::MemberRegister;
		using Object = typename ObjectInterface<T>::Object;
		using ID = typename ObjectInterface<T>::ID;
		MemberType __member;
		DWORD __hash;
	public:
		MemberInterface(string&& name, function<void(Cvp::MemberInterface<T, FieldT>*)>&& staticinit) :__member((MemberType)0xfffffffful), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited())error(_f_needstaticconstruct::format(u8"Member", u8"Member", typeid(T).name(), name.data()));
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__member = Register::Reg<FieldT>(move(name)); });
			__cvpinit_data([this, datainit = move(staticinit)]()->void{ datainit(this); });
			__cvpdestroy([]() {	return;	});
		}
		MemberInterface(string&& name) :__member((MemberType)0xfffffffful), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			if (__cvpinited()) {
				return;
			}
			Manager::__init();
			__cvpinit_enum([this, name = move(name)]()mutable {this->__member = Register::Reg<FieldT>(move(name)); });
			__cvpdestroy([]() {	return;	});
		}
		MemberType Member()const { return __member; }
		bool operator==(const MemberInterface<T, FieldT>& that)const { return Member() == that.Member(); }
		bool operator!=(const MemberInterface<T, FieldT>& that)const { return Member() != that.Member(); }
		void Set_Constructor(DeriveType type, const function<void(FieldT&)>& func) {
			Manager::Get<Functor<void(Object*)>>(PropType::CONSTRUCT, type) += [func, this](Object* _this) {Functor<void(Object*)>::Recur(_this); func((*_this)[*this]); };
		}
		void Set_Destructor(DeriveType type, const function<void(FieldT&)>& func) {
			Manager::Get<Functor<void(Object*)>>(PropType::DESTRUCT, type) += [func, this](Object* _this) { func((*_this)[*this]); Functor<void(Object*)>::Recur(_this); };
		}
		void Set_Serializer(DeriveType type, const function<void(FieldT&, Data&)>& func_serialize, const function<void(FieldT&, const Data&)>& func_deserialize) {
			Manager::Get<Functor<void(Object*, DataMap*)>>(PropType::SERIALIZE, type) += [func_serialize, this](Object* _this, DataMap* buffer) {
				Functor<void(Object*, DataMap*)>::Recur(_this, buffer);
				Data data;
				func_serialize((*_this)[*this], data);
				if (!data.isEmpty())buffer->Set(__hash, move(data));
			};
			Manager::Get<Functor<void(Object*, DataMap*)>>(PropType::DESERIALIZE, type) += [func_deserialize, this](Object* _this, DataMap* buffer) {
				Functor<void(Object*, DataMap*)>::Recur(_this, buffer);
				Data& data = buffer->Get(__hash);
				if (!data.isEmpty())func_deserialize((*_this)[*this], data);
			};
		}
		void Set_Serializer(DeriveType type, const function<void(FieldT&, Data&)>& func) { Set_Serializer(type, func, func); }
		void Set_Constructor(TypeInterface<T> type, const function<void(FieldT&)>& func) { Set_Constructor(type.Type(), func); }
		void Set_Destructor(TypeInterface<T> type, const function<void(FieldT&)>& func) { Set_Destructor(type.Type(), func); }
		void Set_Serializer(TypeInterface<T> type, const function<void(FieldT&, Data&)>& func_serialize, const function<void(FieldT&, const Data&)>& func_deserialize) { Set_Serializer(type.Type(), func_serialize, func_deserialize); }
		void Set_Serializer(TypeInterface<T> type, const function<void(FieldT&, Data&)>& func) { Set_Serializer(type.Type(), func); }

		void Set_Constructor(const function<void(FieldT&)>& func, const function<bool(DeriveType)>& range) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)if (range((DeriveType)i))Set_Constructor((DeriveType)i, func); }
		void Set_Destructor(const function<void(FieldT&)>& func, const function<bool(DeriveType)>& range) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)if (range((DeriveType)i))Set_Destructor((DeriveType)i, func); }
		void Set_Serializer(const function<void(FieldT&, Data&)>& func_serialize, const function<void(FieldT&, const Data&)>& func_deserialize, const function<bool(DeriveType)>& range) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)if (range((DeriveType)i))Set_Serializer((DeriveType)i, func_serialize, func_deserialize); }
		void Set_Serializer(const function<void(FieldT&, Data&)>& func, const function<bool(DeriveType)>& range) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)if (range((DeriveType)i))Set_Serializer((DeriveType)i, func); }

		void Set_Constructor(const function<function<void(FieldT&)>(DeriveType)>& func_factory) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Constructor((DeriveType)i, func_factory((DeriveType)i)); }
		void Set_Destructor(const function<function<void(FieldT&)>(DeriveType)>& func_factory) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Destructor((DeriveType)i, func_factory((DeriveType)i)); }
		void Set_Serializer(const function<function<void(FieldT&, Data&)>(DeriveType)>& func_factory_serialize, const function<function<void(FieldT&, Data&)>(DeriveType)>& func_factory_deserialize) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Serializer((DeriveType)i, func_factory_serialize((DeriveType)i), func_factory_deserialize((DeriveType)i)); }
		void Set_Serializer(const function<function<void(FieldT&, Data&)>(DeriveType)>& func_factory) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Serializer((DeriveType)i, func_factory((DeriveType)i)); }

		void Set_Constructor(const function<void(FieldT&)>& func) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Constructor((DeriveType)i, func); }
		void Set_Destructor(const function<void(FieldT&)>& func) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Destructor((DeriveType)i, func); }
		void Set_Serializer(const function<void(FieldT&, Data&)>& func_serialize, const function<void(FieldT&, const Data&)>& func_deserialize) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Serializer((DeriveType)i, func_serialize, func_deserialize); }
		void Set_Serializer(const function<void(FieldT&, Data&)>& func) { for (DWORD i = 0; i < typename Manager::TypeRegister::Size(); ++i)Set_Serializer((DeriveType)i, func); }
		void Set_Constructor() { Set_Constructor([](FieldT& data) {new(&data)FieldT(); }); }
		void Set_Destructor() { Set_Destructor([](FieldT& data) {data.~FieldT(); }); }
		void Set_Serializer() { Set_Serializer([](FieldT& data, Data& buffer) {buffer.Push(data); }, [](FieldT& data, const Data& buffer) {buffer.Pop(data); }); }
	};

	CVP_OBJECT(hash32, GlobalManager, );
	template<typename FieldT>
	class GlobalInterface {
		FieldT* __p;
		DWORD __hash;
	public:
		template<typename...Args>
		GlobalInterface(string&& name, Args&&...args) :__p(nullptr), __hash(hash32::hash(name)) {
			if (!__inPvz())return;
			auto& p = GlobalManager()[__hash];
			if (p)__p = p;
			else p = new FieldT(forward<Args>(args)...), __p = p;
		}
		FieldT* Ptr()const { return __p; }
		bool operator==(const GlobalInterface<FieldT>& that)const { return __p == that.__p; }
		bool operator!=(const GlobalInterface<FieldT>& that)const { return __p != that.__p; }
		FieldT& Get() { return *__p; }
	};
}