#include "intrinsics.h"

#define makeMethod(dst, name, body) { \
	setMethod(dst, L#name, [](const v8::FunctionCallbackInfo<v8::Value>& info) { \
		body; \
	}); \
}

#define makeMethodRet(dst, name, body) { \
	setMethod(dst, L#name, [](const v8::FunctionCallbackInfo<v8::Value>& info) { \
		info.GetReturnValue().Set(body); \
	}); \
}

#define makeMethodPtr(dst, name, body) { \
	setMethod(dst, L#name, [](const v8::FunctionCallbackInfo<v8::Value>& info) { \
		info.GetReturnValue().Set(static_cast<double_t>(reinterpret_cast<int64_t>(body))); \
	}); \
}

#define makeMethod_i64(dst, name, body) { \
	setMethod(dst, L#name, [](const v8::FunctionCallbackInfo<v8::Value>& info) { \
		info.GetReturnValue().Set(static_cast<double_t>(reinterpret_cast<int64_t>(body))); \
	}); \
}

#define makeMethod_u64(dst, name, body) { \
	setMethod(dst, L#name, [](const v8::FunctionCallbackInfo<v8::Value>& info) { \
		info.GetReturnValue().Set(static_cast<double_t>(body)); \
	}); \
}

namespace {
	void init(v8::Handle<v8::Object> target) {
		v8::Isolate* isolate = v8::Isolate::GetCurrent(); v8::HandleScope scope(isolate);

		class_EternalWrapper::Init(target);

		//unsigned char _addcarry_u32(unsigned char c_in,unsigned int src1,unsigned int src2,unsigned int *sum)
		//unsigned char _addcarry_u64(unsigned char c_in,unsigned __int64 src1,unsigned __int64 src2,unsigned __int64 *sum)
		//unsigned char _addcarry_u8(unsigned char c_in,unsigned char src1,unsigned char src2,unsigned char *sum)
		//unsigned char _addcarryx_u32(unsigned char c_in,unsigned int src1,unsigned int src2,unsigned int *sum)
		//unsigned char _addcarryx_u64(unsigned char c_in,unsigned __int64 src1,unsigned __int64 src2,unsigned __int64 *sum)

		//void __addgsbyte(unsigned long,unsigned char)
		makeMethod(target, __addgsbyte, __addgsbyte(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __addgsword(unsigned long, unsigned short)
		makeMethod(target, __addgsword, __addgsword(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __addgsdword(unsigned long, unsigned int)
		makeMethod(target, __addgsdword, __addgsdword(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __addgsqword(unsigned long, unsigned __int64)
		makeMethod(target, __addgsqword, __addgsqword(info[0]->Uint32Value(), static_cast<uint64_t>(info[1]->NumberValue())));

		//void * _AddressOfReturnAddress(void)
		makeMethodPtr(target, _AddressOfReturnAddress, _AddressOfReturnAddress());

		//unsigned int _andn_u32(unsigned int,unsigned int)
		//unsigned __int64 _andn_u64(unsigned __int64,unsigned __int64)

		//unsigned int _bextr_u32(unsigned int, unsigned int, unsigned int)
		makeMethodRet(target, _bextr_u32, _bextr_u32(info[0]->Uint32Value(), info[1]->Uint32Value(), info[2]->Uint32Value()));

		//unsigned __int64 _bextr_u64(unsigned __int64, unsigned int, unsigned int)
		makeMethod_u64(target, _bextr_u64, _bextr_u64(static_cast<uint64_t>(info[0]->NumberValue()), info[1]->Uint32Value(), info[2]->Uint32Value()));

		//unsigned int _bextri_u32(unsigned int,unsigned int)
		//unsigned __int64 _bextri_u64(unsigned __int64,unsigned int)
		//BOOLEAN _BitScanForward(OUT ULONG* Index,IN ULONG Mask)
		//BOOLEAN _BitScanForward64(OUT ULONG* Index,IN ULONG64 Mask)
		//BOOLEAN _BitScanReverse(OUT ULONG* Index,IN ULONG Mask)
		//BOOLEAN _BitScanReverse64(OUT ULONG* Index,IN ULONG64 Mask)
		//unsigned char _bittest(long const *a,long b)
		//unsigned char _bittest64(__int64 const *a,__int64 b)
		//unsigned char _bittestandcomplement(long *a,long b)
		//unsigned char _bittestandcomplement64(__int64 *a,__int64 b)
		//unsigned char _bittestandreset(long *a,long b)
		//unsigned char _bittestandreset64(__int64 *a,__int64 b)
		//unsigned char _bittestandset(long *a,long b)
		//unsigned char _bittestandset64(__int64 *a,__int64 b)
		//unsigned int _blcfill_u32(unsigned int)
		//unsigned __int64 _blcfill_u64(unsigned __int64)
		//unsigned int _blci_u32(unsigned int)
		//unsigned __int64 _blci_u64(unsigned __int64)
		//unsigned int _blcic_u32(unsigned int)
		//unsigned __int64 _blcic_u64(unsigned __int64)
		//unsigned int _blcmsk_u32(unsigned int)
		//unsigned __int64 _blcmsk_u64(unsigned __int64)
		//unsigned int _blcs_u32(unsigned int)
		//unsigned __int64 _blcs_u64(unsigned __int64)
		//unsigned int _blsfill_u32(unsigned int)
		//unsigned __int64 _blsfill_u64(unsigned __int64)

		//unsigned int _blsi_u32(unsigned int)
		//unsigned __int64 _blsi_u64(unsigned __int64)

		//unsigned int _blsic_u32(unsigned int)
		//unsigned __int64 _blsic_u64(unsigned __int64)

		//unsigned int _blsmsk_u32(unsigned int)
		//unsigned __int64 _blsmsk_u64(unsigned __int64)
		//unsigned int _blsr_u32(unsigned int)
		//unsigned __int64 _blsr_u64(unsigned __int64)
		//unsigned int _bzhi_u32(unsigned int,unsigned int)
		//unsigned __int64 _bzhi_u64(unsigned __int64,unsigned int)

		//void _clac(void)

		//void __cpuid(int *a,int b)
		makeMethod(target, __cpuid, __cpuid(reinterpret_cast<int *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//void __cpuidex(int *a,int b,int c)
		makeMethod(target, __cpuidex, __cpuidex(reinterpret_cast<int *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//void __debugbreak(void)
		makeMethod(target, __debugbreak, __debugbreak());

		//void _disable(void)
		//__int64 [pascal/cdecl] __emul(int,int)
		//unsigned __int64 [pascal/cdecl]__emulu(unsigned int,unsigned int)
		//void _enable(void)

		//void __fastfail(unsigned int)
		makeMethod(target, __fastfail, __fastfail(info[0]->Uint32Value()));

		//void __faststorefence(void)
		makeMethod(target, __faststorefence, __faststorefence());

		//void _fxrstor(void const*)
		//void _fxrstor64(void const*)
		//void _fxsave(void*)
		//void _fxsave64(void*)

		//(unsigned int __getcallerseflags())
		makeMethodRet(target, __getcallerseflags, __getcallerseflags());

		//void __halt(void)
		makeMethod(target, __halt, __halt());

		//unsigned char __inbyte(unsigned short Port)
		//void __inbytestring(unsigned short Port,unsigned char *Buffer,unsigned long Count)

		//void __incgsbyte(unsigned long)
		makeMethod(target, __incgsbyte, __incgsbyte(info[0]->Uint32Value()));

		//void __incgsdword(unsigned long)
		makeMethod(target, __incgsdword, __incgsdword(info[0]->Uint32Value()));

		//void __incgsqword(unsigned long)
		makeMethod(target, __incgsqword, __incgsqword(info[0]->Uint32Value()));

		//void __incgsword(unsigned long)
		makeMethod(target, __incgsword, __incgsword(info[0]->Uint32Value()));

		//unsigned long __indword(unsigned short Port)
		//void __indwordstring(unsigned short Port,unsigned long *Buffer,unsigned long Count)

		//void __int2c(void)
		makeMethod(target, __int2c, __int2c());

		//long _InterlockedAnd(long volatile *, long)
		makeMethodRet(target, _InterlockedAnd, _InterlockedAnd(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedAnd_HLEAcquire(long volatile *, long)
		makeMethodRet(target, _InterlockedAnd_HLEAcquire, _InterlockedAnd_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedAnd_HLERelease(long volatile *, long)
		makeMethodRet(target, _InterlockedAnd_HLERelease, _InterlockedAnd_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedAnd_np(long *, long)
		makeMethodRet(target, _InterlockedAnd_np, _InterlockedAnd_np(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedAnd16(short volatile *, short)
		makeMethodRet(target, _InterlockedAnd16, _InterlockedAnd16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedAnd16_np(short *, short)
		makeMethodRet(target, _InterlockedAnd16_np, _InterlockedAnd16_np(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//__int64 _InterlockedAnd64(__int64 volatile *, __int64)
		//__int64 _InterlockedAnd64_HLEAcquire(__int64 volatile *, __int64)
		//__int64 _InterlockedAnd64_HLERelease(__int64 volatile *, __int64)
		//__int64 _InterlockedAnd64_np(__int64 *, __int64)

		//char _InterlockedAnd8(char volatile *, char)
		makeMethodRet(target, _InterlockedAnd8, _InterlockedAnd8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//char _InterlockedAnd8_np(char *, char)
		makeMethodRet(target, _InterlockedAnd8_np, _InterlockedAnd8_np(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandreset(long *a, long b)
		makeMethodRet(target, _interlockedbittestandreset, _interlockedbittestandreset(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandreset_HLEAcquire(long *a, long b)
		makeMethodRet(target, _interlockedbittestandreset_HLEAcquire, _interlockedbittestandreset_HLEAcquire(reinterpret_cast<long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandreset_HLERelease(long *a, long b)
		makeMethodRet(target, _interlockedbittestandreset_HLERelease, _interlockedbittestandreset_HLERelease(reinterpret_cast<long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandreset64(__int64 *a, __int64 b)
		//unsigned char _interlockedbittestandreset64_HLEAcquire(__int64 *a, __int64 b)
		//unsigned char _interlockedbittestandreset64_HLERelease(__int64 *a, __int64 b)

		//unsigned char _interlockedbittestandset(long *a, long b)
		makeMethodRet(target, _interlockedbittestandset, _interlockedbittestandset(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandset_HLEAcquire(long *a, long b)
		makeMethodRet(target, _interlockedbittestandset_HLEAcquire, _interlockedbittestandset_HLEAcquire(reinterpret_cast<long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandset_HLERelease(long *a, long b)
		makeMethodRet(target, _interlockedbittestandset_HLERelease, _interlockedbittestandset_HLERelease(reinterpret_cast<long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//unsigned char _interlockedbittestandset64(__int64 *a, __int64 b)
		//unsigned char _interlockedbittestandset64_HLEAcquire(__int64 *a, __int64 b)
		//unsigned char _interlockedbittestandset64_HLERelease(__int64 *a, __int64 b)

		//long _InterlockedCompareExchange(long volatile *, long, long)
		makeMethodRet(target, _InterlockedCompareExchange, _InterlockedCompareExchange(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//long _InterlockedCompareExchange_HLEAcquire(long volatile *, long, long)
		makeMethodRet(target, _InterlockedCompareExchange_HLEAcquire, _InterlockedCompareExchange_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//long _InterlockedCompareExchange_HLERelease(long volatile *, long, long)
		makeMethodRet(target, _InterlockedCompareExchange_HLERelease, _InterlockedCompareExchange_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//long _InterlockedCompareExchange_np(long *, long, long)
		makeMethodRet(target, _InterlockedCompareExchange_np, _InterlockedCompareExchange_np(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//unsigned char _InterlockedCompareExchange128(__int64 volatile *, __int64, __int64, __int64*)
		//unsigned char _InterlockedCompareExchange128(__int64 volatile *, __int64, __int64, __int64*)

		//short _InterlockedCompareExchange16(short volatile *Destination, short Exchange, short Comparand)
		makeMethodRet(target, _InterlockedCompareExchange16, _InterlockedCompareExchange16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//short _InterlockedCompareExchange16_np(short volatile *Destination, short Exchange, short Comparand)
		makeMethodRet(target, _InterlockedCompareExchange16_np, _InterlockedCompareExchange16_np(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//__int64 _InterlockedCompareExchange64(__int64 volatile *, __int64, __int64)
		//__int64 _InterlockedCompareExchange64_HLEAcquire(__int64 volatile *, __int64, __int64)
		//__int64 _InterlockedCompareExchange64_HLERelease(__int64 volatile *, __int64, __int64)
		//__int64 _InterlockedCompareExchange64_np(__int64 *, __int64, __int64)

		//char _InterlockedCompareExchange8(char volatile *Destination, char Exchange, char Comparand)
		makeMethodRet(target, _InterlockedCompareExchange8, _InterlockedCompareExchange8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value(), info[2]->Int32Value()));

		//void *_InterlockedCompareExchangePointer(void *volatile *, void *, void *)
		//void *_InterlockedCompareExchangePointer_HLEAcquire(void *volatile *, void *, void *)
		//void *_InterlockedCompareExchangePointer_HLERelease(void *volatile *, void *, void *)
		//void *_InterlockedCompareExchangePointer_np(void **, void *, void *)

		//long _InterlockedDecrement(long volatile *)
		makeMethodRet(target, _InterlockedDecrement, _InterlockedDecrement(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0]))));

		//short _InterlockedDecrement16(short volatile *Addend)
		makeMethodRet(target, _InterlockedDecrement16, _InterlockedDecrement16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0]))));

		//__int64 _InterlockedDecrement64(__int64 volatile *)
		makeMethodRet(target, _InterlockedDecrement64, static_cast<double_t>(_InterlockedDecrement64(reinterpret_cast<volatile __int64 *>(node::Buffer::Data(info[0])))));

		//long _InterlockedExchange(long volatile *, long)
		makeMethodRet(target, _InterlockedExchange, _InterlockedExchange(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedExchange_HLEAcquire(long volatile *, long)
		makeMethodRet(target, _InterlockedExchange_HLEAcquire, _InterlockedExchange_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedExchange_HLERelease(long volatile *, long)
		makeMethodRet(target, _InterlockedExchange_HLERelease, _InterlockedExchange_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedExchange16(short volatile *, short)
		makeMethodRet(target, _InterlockedExchange16, _InterlockedExchange16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//__int64 _InterlockedExchange64(__int64 volatile *, __int64)
		//__int64 _InterlockedExchange64_HLEAcquire(__int64 volatile *, __int64)
		//__int64 _InterlockedExchange64_HLERelease(__int64 volatile *, __int64)

		//char _InterlockedExchange8(char volatile *, char)
		makeMethodRet(target, _InterlockedExchange8, _InterlockedExchange8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedExchangeAdd(long volatile *, long)
		makeMethodRet(target, _InterlockedExchangeAdd, _InterlockedExchangeAdd(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedExchangeAdd_HLEAcquire(long volatile *, long)
		makeMethodRet(target, _InterlockedExchangeAdd_HLEAcquire, _InterlockedExchangeAdd_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedExchangeAdd_HLERelease(long volatile *, long)
		makeMethodRet(target, _InterlockedExchangeAdd_HLERelease, _InterlockedExchangeAdd_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedExchangeAdd16(short volatile *, short)
		makeMethodRet(target, _InterlockedExchangeAdd16, _InterlockedExchangeAdd16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//__int64 _InterlockedExchangeAdd64(__int64 volatile *, __int64)
		//__int64 _InterlockedExchangeAdd64_HLEAcquire(__int64 volatile *, __int64)
		//__int64 _InterlockedExchangeAdd64_HLERelease(__int64 volatile *, __int64)

		//char _InterlockedExchangeAdd8(char volatile *, char)
		makeMethodRet(target, _InterlockedExchangeAdd8, _InterlockedExchangeAdd8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//void * _InterlockedExchangePointer(void *volatile *, void *)
		//void * _InterlockedExchangePointer_HLEAcquire(void *volatile *, void *)
		//void * _InterlockedExchangePointer_HLERelease(void *volatile *, void *)

		//long _InterlockedIncrement(long volatile *)
		makeMethodRet(target, _InterlockedIncrement, _InterlockedIncrement(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0]))));

		//short _InterlockedIncrement16(short volatile *Addend)
		makeMethodRet(target, _InterlockedIncrement16, _InterlockedIncrement16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0]))));

		//__int64 _InterlockedIncrement64(__int64 volatile *)
		makeMethodRet(target, _InterlockedIncrement64, static_cast<double_t>(_InterlockedIncrement64(reinterpret_cast<volatile __int64 *>(node::Buffer::Data(info[0])))));

		//long _InterlockedOr(long volatile *, long)
		makeMethodRet(target, _InterlockedOr, _InterlockedOr(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedOr_HLEAcquire(long volatile *, long)
		makeMethodRet(target, _InterlockedOr_HLEAcquire, _InterlockedOr_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedOr_HLERelease(long volatile *, long)
		makeMethodRet(target, _InterlockedOr_HLERelease, _InterlockedOr_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedOr_np(long *, long)
		makeMethodRet(target, _InterlockedOr_np, _InterlockedOr_np(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedOr16(short volatile *, short)
		makeMethodRet(target, _InterlockedOr16, _InterlockedOr16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedOr16_np(short *, short)
		makeMethodRet(target, _InterlockedOr16_np, _InterlockedOr16_np(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//__int64 _InterlockedOr64(__int64 volatile *, __int64)
		//__int64 _InterlockedOr64_HLEAcquire(__int64 volatile *, __int64)
		//__int64 _InterlockedOr64_HLERelease(__int64 volatile *, __int64)
		//__int64 _InterlockedOr64_np(__int64 *, __int64)

		//char _InterlockedOr8(char volatile *, char)
		makeMethodRet(target, _InterlockedOr8, _InterlockedOr8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//char _InterlockedOr8_np(char *, char)
		makeMethodRet(target, _InterlockedOr8_np, _InterlockedOr8_np(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedXor(long volatile *, long)
		makeMethodRet(target, _InterlockedXor, _InterlockedXor(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedXor_HLEAcquire(long volatile *, long)
		makeMethodRet(target, _InterlockedXor_HLEAcquire, _InterlockedXor_HLEAcquire(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedXor_HLERelease(long volatile *, long)
		makeMethodRet(target, _InterlockedXor_HLERelease, _InterlockedXor_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//long _InterlockedXor_np(long *, long)
		makeMethodRet(target, _InterlockedXor_np, _InterlockedXor_np(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedXor16(short volatile *, short)
		makeMethodRet(target, _InterlockedXor16, _InterlockedXor16(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//short _InterlockedXor16_np(short *, short)
		makeMethodRet(target, _InterlockedXor16_np, _InterlockedXor16_np(reinterpret_cast<volatile short *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//__int64 _InterlockedXor64(__int64 volatile *, __int64)
		//__int64 _InterlockedXor64_HLEAcquire(__int64 volatile *, __int64)
		//__int64 _InterlockedXor64_HLERelease(__int64 volatile *, __int64)
		//__int64 _InterlockedXor64_np(__int64 *, __int64)

		//char _InterlockedXor8(char volatile *, char)
		makeMethodRet(target, _InterlockedXor8, _InterlockedXor8(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//char _InterlockedXor8_np(char *, char)
		makeMethodRet(target, _InterlockedXor8_np, _InterlockedXor8_np(reinterpret_cast<volatile char *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//void __invlpg(void*)
		//void _invpcid(unsigned int,void *)
		//unsigned short __inword(unsigned short Port)
		//void __inwordstring(unsigned short Port,unsigned short *Buffer,unsigned long Count)
		//void _lgdt(void*)
		//void __lidt(void*)

		//unsigned __int64 [pascal/cdecl] __ll_lshift(unsigned __int64,int)

		//__int64 [pascal/cdecl] __ll_rshift(__int64,int)

		//void __llwpcb(void *)
		//"unsigned short _load_be_u16(void const*);
		//short _loadbe_i16(void const*); [3]"
		//"unsigned int _load_be_u32(void const*);
		//int _loadbe_i32(void const*); [3]"
		//"unsigned __int64 _load_be_u64(void const*);
		//__int64 _loadbe_i64(void const*); [3]"
		//unsigned char __lwpins32(unsigned int,unsigned int,unsigned int)
		//unsigned char __lwpins64(unsigned __int64,unsigned int,unsigned int)
		//void __lwpval32(unsigned int,unsigned int,unsigned int)
		//void __lwpval64(unsigned __int64,unsigned int,unsigned int)

		//unsigned int __lzcnt(unsigned int)
		makeMethodRet(target, __lzcnt, __lzcnt(info[0]->Uint32Value()));

		//unsigned int _lzcnt_u32(unsigned int)
		makeMethodRet(target, _lzcnt_u32, _lzcnt_u32(info[0]->Uint32Value()));

		//unsigned __int64 _lzcnt_u64(unsigned __int64)
		makeMethodRet(target, _lzcnt_u64, static_cast<double_t>(_lzcnt_u64(static_cast<uint64_t>(info[0]->NumberValue()))));

		//unsigned short __lzcnt16(unsigned short)
		makeMethodRet(target, __lzcnt16, __lzcnt16(info[0]->Uint32Value()));

		//unsigned __int64 __lzcnt64(unsigned __int64)
		makeMethodRet(target, __lzcnt64, static_cast<double_t>(__lzcnt64(static_cast<uint64_t>(info[0]->NumberValue()))));

		//void _m_prefetch(void*)
		makeMethod(target, _m_prefetch, _m_prefetch(reinterpret_cast<void *>(node::Buffer::Data(info[0]))));

		//void _m_prefetchw(void*)
		makeMethod(target, _m_prefetchw, _m_prefetchw(reinterpret_cast<void *>(node::Buffer::Data(info[0]))));

		//__m128i _mm_abs_epi16(__m128i)
		//__m128i _mm_abs_epi32(__m128i)
		//__m128i _mm_abs_epi8(__m128i)
		//__m128i _mm_add_epi16(__m128i,__m128i)
		//__m128i _mm_add_epi32(__m128i,__m128i)
		//__m128i _mm_add_epi64(__m128i,__m128i)
		//__m128i _mm_add_epi8(__m128i,__m128i)
		//__m128d _mm_add_pd(__m128d,__m128d)
		//__m128 _mm_add_ps(__m128,__m128)
		//__m128d _mm_add_sd(__m128d,__m128d)
		//__m128 _mm_add_ss(__m128,__m128)
		//__m128i _mm_adds_epi16(__m128i,__m128i)
		//__m128i _mm_adds_epi8(__m128i,__m128i)
		//__m128i _mm_adds_epu16(__m128i,__m128i)
		//__m128i _mm_adds_epu8(__m128i,__m128i)
		//__m128d _mm_addsub_pd(__m128d,__m128d)
		//__m128 _mm_addsub_ps(__m128,__m128)
		//__m128i _mm_aesdec_si128( __m128i,__m128i )
		//__m128i _mm_aesdeclast_si128( __m128i,__m128i )
		//__m128i _mm_aesenc_si128( __m128i,__m128i )
		//__m128i _mm_aesenclast_si128( __m128i,__m128i )
		//__m128i _mm_aesimc_si128 (__m128i )
		//__m128i _mm_aeskeygenassist_si128 (__m128i,const int )
		//__m128i _mm_alignr_epi8(__m128i,__m128i,int)
		//__m128d _mm_and_pd(__m128d,__m128d)
		//__m128 _mm_and_ps(__m128,__m128)
		//__m128i _mm_and_si128(__m128i,__m128i)
		//__m128d _mm_andnot_pd(__m128d,__m128d)
		//__m128 _mm_andnot_ps(__m128,__m128)
		//__m128i _mm_andnot_si128(__m128i,__m128i)
		//__m128i _mm_avg_epu16(__m128i,__m128i)
		//__m128i _mm_avg_epu8(__m128i,__m128i)
		//__m128i _mm_blend_epi16 (__m128i,__m128i,const int )
		//__m128i _mm_blend_epi32(__m128i,__m128i,const int)
		//__m128d _mm_blend_pd (__m128d,__m128d,const int )
		//__m128 _mm_blend_ps (__m128,__m128,const int )
		//__m128i _mm_blendv_epi8 (__m128i,__m128i,__m128i )
		//__m128d _mm_blendv_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_blendv_ps(__m128,__m128,__m128 )
		//__m128 _mm_broadcast_ss(float const *)
		//__m128i _mm_broadcastb_epi8(__m128i)
		//__m128i _mm_broadcastd_epi32(__m128i)
		//__m128i _mm_broadcastq_epi64(__m128i)
		//__m128d _mm_broadcastsd_pd(__m128d)
		//__m128 _mm_broadcastss_ps(__m128)
		//__m128i _mm_broadcastw_epi16(__m128i)
		//__m128 _mm_castpd_ps(__m128d)
		//__m128i _mm_castpd_si128(__m128d)
		//__m128d _mm_castps_pd(__m128)
		//__m128i _mm_castps_si128(__m128)
		//__m128d _mm_castsi128_pd(__m128i)
		//__m128 _mm_castsi128_ps(__m128i)

		//void _mm_clflush(void const *)
		makeMethod(target, _mm_clflush, _mm_clflush(reinterpret_cast<void *>(node::Buffer::Data(info[0]))));

		//__m128i _mm_clmulepi64_si128 (__m128i,__m128i,const int )
		//__m128i _mm_cmov_si128(__m128i,__m128i,__m128i)
		//__m128d _mm_cmp_pd(__m128d,__m128d,const int)
		//__m128 _mm_cmp_ps(__m128,__m128,const int)
		//__m128d _mm_cmp_sd(__m128d,__m128d,const int)
		//__m128 _mm_cmp_ss(__m128,__m128,const int)
		//__m128i _mm_cmpeq_epi16(__m128i,__m128i)
		//__m128i _mm_cmpeq_epi32(__m128i,__m128i)
		//__m128i _mm_cmpeq_epi64(__m128i,__m128i )
		//__m128i _mm_cmpeq_epi8(__m128i,__m128i)
		//__m128d _mm_cmpeq_pd(__m128d,__m128d)
		//__m128 _mm_cmpeq_ps(__m128,__m128)
		//__m128d _mm_cmpeq_sd(__m128d,__m128d)
		//__m128 _mm_cmpeq_ss(__m128,__m128)
		//int _mm_cmpestra(__m128i,int,__m128i,int,const int)
		//int _mm_cmpestrc(__m128i,int,__m128i,int,const int)
		//int _mm_cmpestri(__m128i,int,__m128i,int,const int)
		//__m128i _mm_cmpestrm(__m128i,int,__m128i,int,const int)
		//int _mm_cmpestro(__m128i,int,__m128i,int,const int)
		//int _mm_cmpestrs(__m128i,int,__m128i,int,const int)
		//int _mm_cmpestrz(__m128i,int,__m128i,int,const int)
		//__m128d _mm_cmpge_pd(__m128d,__m128d)
		//__m128 _mm_cmpge_ps(__m128,__m128)
		//__m128d _mm_cmpge_sd(__m128d,__m128d)
		//__m128 _mm_cmpge_ss(__m128,__m128)
		//__m128i _mm_cmpgt_epi16(__m128i,__m128i)
		//__m128i _mm_cmpgt_epi32(__m128i,__m128i)
		//__m128i _mm_cmpgt_epi64(__m128i,__m128i )
		//__m128i _mm_cmpgt_epi8(__m128i,__m128i)
		//__m128d _mm_cmpgt_pd(__m128d,__m128d)
		//__m128 _mm_cmpgt_ps(__m128,__m128)
		//__m128d _mm_cmpgt_sd(__m128d,__m128d)
		//__m128 _mm_cmpgt_ss(__m128,__m128)
		//int _mm_cmpistra(__m128i,__m128i,const int)
		//int _mm_cmpistrc(__m128i,__m128i,const int)
		//int _mm_cmpistri(__m128i,__m128i,const int)
		//__m128i _mm_cmpistrm(__m128i,__m128i,const int)
		//int _mm_cmpistro(__m128i,__m128i,const int)
		//int _mm_cmpistrs(__m128i,__m128i,const int)
		//int _mm_cmpistrz(__m128i,__m128i,const int)
		//__m128d _mm_cmple_pd(__m128d,__m128d)
		//__m128 _mm_cmple_ps(__m128,__m128)
		//__m128d _mm_cmple_sd(__m128d,__m128d)
		//__m128 _mm_cmple_ss(__m128,__m128)
		//__m128i _mm_cmplt_epi16(__m128i,__m128i)
		//__m128i _mm_cmplt_epi32(__m128i,__m128i)
		//__m128i _mm_cmplt_epi8(__m128i,__m128i)
		//__m128d _mm_cmplt_pd(__m128d,__m128d)
		//__m128 _mm_cmplt_ps(__m128,__m128)
		//__m128d _mm_cmplt_sd(__m128d,__m128d)
		//__m128 _mm_cmplt_ss(__m128,__m128)
		//__m128d _mm_cmpneq_pd(__m128d,__m128d)
		//__m128 _mm_cmpneq_ps(__m128,__m128)
		//__m128d _mm_cmpneq_sd(__m128d,__m128d)
		//__m128 _mm_cmpneq_ss(__m128,__m128)
		//__m128d _mm_cmpnge_pd(__m128d,__m128d)
		//__m128 _mm_cmpnge_ps(__m128,__m128)
		//__m128d _mm_cmpnge_sd(__m128d,__m128d)
		//__m128 _mm_cmpnge_ss(__m128,__m128)
		//__m128d _mm_cmpngt_pd(__m128d,__m128d)
		//__m128 _mm_cmpngt_ps(__m128,__m128)
		//__m128d _mm_cmpngt_sd(__m128d,__m128d)
		//__m128 _mm_cmpngt_ss(__m128,__m128)
		//__m128d _mm_cmpnle_pd(__m128d,__m128d)
		//__m128 _mm_cmpnle_ps(__m128,__m128)
		//__m128d _mm_cmpnle_sd(__m128d,__m128d)
		//__m128 _mm_cmpnle_ss(__m128,__m128)
		//__m128d _mm_cmpnlt_pd(__m128d,__m128d)
		//__m128 _mm_cmpnlt_ps(__m128,__m128)
		//__m128d _mm_cmpnlt_sd(__m128d,__m128d)
		//__m128 _mm_cmpnlt_ss(__m128,__m128)
		//__m128d _mm_cmpord_pd(__m128d,__m128d)
		//__m128 _mm_cmpord_ps(__m128,__m128)
		//__m128d _mm_cmpord_sd(__m128d,__m128d)
		//__m128 _mm_cmpord_ss(__m128,__m128)
		//__m128d _mm_cmpunord_pd(__m128d,__m128d)
		//__m128 _mm_cmpunord_ps(__m128,__m128)
		//__m128d _mm_cmpunord_sd(__m128d,__m128d)
		//__m128 _mm_cmpunord_ss(__m128,__m128)
		//__m128i _mm_com_epi16(__m128i,__m128i,int)
		//__m128i _mm_com_epi32(__m128i,__m128i,int)
		//__m128i _mm_com_epi32(__m128i,__m128i,int)
		//__m128i _mm_com_epi8(__m128i,__m128i,int)
		//__m128i _mm_com_epu16(__m128i,__m128i,int)
		//__m128i _mm_com_epu32(__m128i,__m128i,int)
		//__m128i _mm_com_epu32(__m128i,__m128i,int)
		//__m128i _mm_com_epu8(__m128i,__m128i,int)
		//int _mm_comieq_sd(__m128d,__m128d)
		//int _mm_comieq_ss(__m128,__m128)
		//int _mm_comige_sd(__m128d,__m128d)
		//int _mm_comige_ss(__m128,__m128)
		//int _mm_comigt_sd(__m128d,__m128d)
		//int _mm_comigt_ss(__m128,__m128)
		//int _mm_comile_sd(__m128d,__m128d)
		//int _mm_comile_ss(__m128,__m128)
		//int _mm_comilt_sd(__m128d,__m128d)
		//int _mm_comilt_ss(__m128,__m128)
		//int _mm_comineq_sd(__m128d,__m128d)
		//int _mm_comineq_ss(__m128,__m128)

		//unsigned int _mm_crc32_u16(unsigned int,unsigned short)
		makeMethodRet(target, _mm_crc32_u16, _mm_crc32_u16(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//unsigned int _mm_crc32_u32(unsigned int,unsigned int)
		makeMethodRet(target, _mm_crc32_u32, _mm_crc32_u32(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//unsigned __int64 _mm_crc32_u64(unsigned __int64,unsigned __int64)
		makeMethodRet(target, _mm_crc32_u64, static_cast<double_t>(_mm_crc32_u64(static_cast<uint64_t>(info[0]->NumberValue()), static_cast<uint64_t>(info[1]->NumberValue()))));

		//unsigned int _mm_crc32_u8(unsigned int,unsigned char)
		makeMethodRet(target, _mm_crc32_u8, _mm_crc32_u8(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//__m128 _mm_cvt_si2ss(__m128,int)
		//int _mm_cvt_ss2si(__m128)
		//__m128i _mm_cvtepi16_epi32(__m128i )
		//__m128i _mm_cvtepi16_epi64(__m128i )
		//__m128i _mm_cvtepi32_epi64(__m128i )
		//__m128d _mm_cvtepi32_pd(__m128i)
		//__m128 _mm_cvtepi32_ps(__m128i)
		//__m128i _mm_cvtepi8_epi16 (__m128i )
		//__m128i _mm_cvtepi8_epi32 (__m128i )
		//__m128i _mm_cvtepi8_epi64 (__m128i )
		//__m128i _mm_cvtepu16_epi32(__m128i )
		//__m128i _mm_cvtepu16_epi64(__m128i )
		//__m128i _mm_cvtepu32_epi64(__m128i )
		//__m128i _mm_cvtepu8_epi16 (__m128i )
		//__m128i _mm_cvtepu8_epi32 (__m128i )
		//__m128i _mm_cvtepu8_epi64 (__m128i )
		//__m128i _mm_cvtpd_epi32(__m128d)
		//__m128 _mm_cvtpd_ps(__m128d)
		//__m128 _mm_cvtph_ps(__m128i)
		//__m128i _mm_cvtps_epi32(__m128)
		//__m128d _mm_cvtps_pd(__m128)
		//__m128i _mm_cvtps_ph(__m128,const int)
		//double _mm_cvtsd_f64(__m128d)
		//int _mm_cvtsd_si32(__m128d)
		//__int64 _mm_cvtsd_si64(__m128d)
		//__int64 _mm_cvtsd_si64x(__m128d a)
		//__m128 _mm_cvtsd_ss(__m128,__m128d)
		//int _mm_cvtsi128_si32(__m128i)
		//__int64 _mm_cvtsi128_si64(__m128i)
		//__int64 _mm_cvtsi128_si64x(__m128i a)
		//__m128d _mm_cvtsi32_sd(__m128d,int)
		//__m128i _mm_cvtsi32_si128(int)
		//__m128d _mm_cvtsi64_sd(__m128d,__int64)
		//__m128i _mm_cvtsi64_si128(__int64)
		//__m128 _mm_cvtsi64_ss(__m128,__int64)
		//__m128d _mm_cvtsi64x_sd(__m128d a,__int64 b)
		//__m128i _mm_cvtsi64x_si128(__int64 a)
		//__m128 _mm_cvtsi64x_ss(__m128 a,__int64 b)
		//float _mm_cvtss_f32(__m128)
		//__m128d _mm_cvtss_sd(__m128d,__m128)
		//__int64 _mm_cvtss_si64(__m128)
		//__int64 _mm_cvtss_si64x(__m128 a)
		//int _mm_cvtt_ss2si(__m128)
		//__m128i _mm_cvttpd_epi32(__m128d)
		//__m128i _mm_cvttps_epi32(__m128)
		//int _mm_cvttsd_si32(__m128d)
		//__int64 _mm_cvttsd_si64(__m128d)
		//__int64 _mm_cvttsd_si64x(__m128d a)
		//__int64 _mm_cvttss_si64(__m128)
		//__int64 _mm_cvttss_si64x(__m128 a)
		//__m128d _mm_div_pd(__m128d,__m128d)
		//__m128 _mm_div_ps(__m128,__m128)
		//__m128d _mm_div_sd(__m128d,__m128d)
		//__m128 _mm_div_ss(__m128,__m128)
		//__m128d _mm_dp_pd(__m128d,__m128d,const int )
		//__m128 _mm_dp_ps(__m128,__m128,const int )
		//int _mm_extract_epi16(__m128i,int)
		//int _mm_extract_epi32(__m128i,const int )
		//__int64 _mm_extract_epi64(__m128i,const int )
		//int _mm_extract_epi8 (__m128i,const int )
		//int _mm_extract_ps(__m128,const int )
		//__m128i _mm_extract_si64(__m128i,__m128i)
		//__m128i _mm_extracti_si64(__m128i,int,int)
		//__m128d _mm_fmadd_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmadd_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fmadd_sd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmadd_ss (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fmaddsub_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmaddsub_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fmsub_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmsub_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fmsub_sd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmsub_ss (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fmsubadd_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fmsubadd_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fnmadd_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fnmadd_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fnmadd_sd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fnmadd_ss (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fnmsub_pd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fnmsub_ps (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_fnmsub_sd (__m128d a,__m128d b,__m128d c)
		//__m128 _mm_fnmsub_ss (__m128 a,__m128 b,__m128 c)
		//__m128d _mm_frcz_pd(__m128d)
		//__m128 _mm_frcz_ps(__m128)
		//__m128d _mm_frcz_sd(__m128d,__m128d)
		//__m128 _mm_frcz_ss(__m128,__m128)
		//unsigned int _mm_getcsr(void)
		//__m128i _mm_hadd_epi16(__m128i,__m128i)
		//__m128i _mm_hadd_epi32(__m128i,__m128i)
		//__m128d _mm_hadd_pd(__m128d,__m128d)
		//__m128 _mm_hadd_ps(__m128,__m128)
		//__m128i _mm_haddd_epi16(__m128i)
		//__m128i _mm_haddd_epi8(__m128i)
		//__m128i _mm_haddd_epu16(__m128i)
		//__m128i _mm_haddd_epu8(__m128i)
		//__m128i _mm_haddq_epi16(__m128i)
		//__m128i _mm_haddq_epi32(__m128i)
		//__m128i _mm_haddq_epi8(__m128i)
		//__m128i _mm_haddq_epu16(__m128i)
		//__m128i _mm_haddq_epu32(__m128i)
		//__m128i _mm_haddq_epu8(__m128i)
		//__m128i _mm_hadds_epi16(__m128i,__m128i)
		//__m128i _mm_haddw_epi8(__m128i)
		//__m128i _mm_haddw_epu8(__m128i)
		//__m128i _mm_hsub_epi16(__m128i,__m128i)
		//__m128i _mm_hsub_epi32(__m128i,__m128i)
		//__m128d _mm_hsub_pd(__m128d,__m128d)
		//__m128 _mm_hsub_ps(__m128,__m128)
		//__m128i _mm_hsubd_epi16(__m128i)
		//__m128i _mm_hsubq_epi32(__m128i)
		//__m128i _mm_hsubs_epi16(__m128i,__m128i)
		//__m128i _mm_hsubw_epi8(__m128i)
		//__m128i _mm_i32gather_epi32(int const *base,__m128i index,const int scale)
		//__m128i _mm_i32gather_epi64(__int64 const *base,__m128i index,const int scale)
		//__m128d _mm_i32gather_pd(double const *base,__m128i index,const int scale)
		//__m128 _mm_i32gather_ps(float const *base,__m128i index,const int scale)
		//__m128i _mm_i64gather_epi32(int const *base,__m128i index,const int scale)
		//__m128i _mm_i64gather_epi64(__int64 const *base,__m128i index,const int scale)
		//__m128d _mm_i64gather_pd(double const *base,__m128i index,const int scale)
		//__m128 _mm_i64gather_ps(float const *base,__m128i index,const int scale)
		//__m128i _mm_insert_epi16(__m128i,int,int)
		//__m128i _mm_insert_epi32(__m128i,int,const int )
		//__m128i _mm_insert_epi64(__m128i,__int64,const int )
		//__m128i _mm_insert_epi8 (__m128i,int,const int )
		//__m128 _mm_insert_ps(__m128,__m128,const int )
		//__m128i _mm_insert_si64(__m128i,__m128i)
		//__m128i _mm_inserti_si64(__m128i,__m128i,int,int)
		//__m128i _mm_lddqu_si128(__m128i const*)

		//void _mm_lfence(void)
		makeMethod(target, _mm_lfence, _mm_lfence());

		//__m128d _mm_load_pd(double*)
		//__m128 _mm_load_ps(float*)
		//__m128 _mm_load_ps1(float*)
		//__m128d _mm_load_sd(double*)
		//__m128i _mm_load_si128(__m128i*)
		//__m128 _mm_load_ss(float*)
		//__m128d _mm_load1_pd(double*)
		//__m128d _mm_loaddup_pd(double const*)
		//__m128d _mm_loadh_pd(__m128d,double*)
		//__m128 _mm_loadh_pi(__m128,__m64*)
		//__m128i _mm_loadl_epi64(__m128i*)
		//__m128d _mm_loadl_pd(__m128d,double*)
		//__m128 _mm_loadl_pi(__m128,__m64*)
		//__m128d _mm_loadr_pd(double*)
		//__m128 _mm_loadr_ps(float*)
		//__m128d _mm_loadu_pd(double*)
		//__m128 _mm_loadu_ps(float*)
		//__m128i _mm_loadu_si128(__m128i*)
		//__m128i _mm_macc_epi16(__m128i,__m128i,__m128i)
		//__m128i _mm_macc_epi32(__m128i,__m128i,__m128i)
		//__m128d _mm_macc_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_macc_ps(__m128,__m128,__m128)
		//__m128d _mm_macc_sd(__m128d,__m128d,__m128d)
		//__m128 _mm_macc_ss(__m128,__m128,__m128)
		//__m128i _mm_maccd_epi16(__m128i,__m128i,__m128i)
		//__m128i _mm_macchi_epi32(__m128i,__m128i,__m128i)
		//__m128i _mm_macclo_epi32(__m128i,__m128i,__m128i)
		//__m128i _mm_maccs_epi16(__m128i,__m128i,__m128i)
		//__m128i _mm_maccs_epi32(__m128i,__m128i,__m128i)
		//__m128i _mm_maccsd_epi16(__m128i,__m128i,__m128i)
		//__m128i _mm_maccshi_epi32(__m128i,__m128i,__m128i)
		//__m128i _mm_maccslo_epi32(__m128i,__m128i,__m128i)
		//__m128i _mm_madd_epi16(__m128i,__m128i)
		//__m128i _mm_maddd_epi16(__m128i,__m128i,__m128i)
		//__m128i _mm_maddsd_epi16(__m128i,__m128i,__m128i)
		//__m128d _mm_maddsub_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_maddsub_ps(__m128,__m128,__m128)
		//__m128i _mm_maddubs_epi16(__m128i,__m128i)
		//__m128i _mm_mask_i32gather_epi32(__m128i src,int const *base,__m128i index,__m128i mask,const int scale)
		//__m128i _mm_mask_i32gather_epi64(__m128i src,__int64 const *base,__m128i index,__m128i mask,const int scale)
		//__m128d _mm_mask_i32gather_pd(__m128d src,double const *base,__m128i index,__m128d mask,const int scale)
		//__m128 _mm_mask_i32gather_ps(__m128 src,float const *base,__m128i index,__m128 mask,const int scale)
		//__m128i _mm_mask_i64gather_epi32(__m128i src,int const *base,__m128i index,__m128i mask,const int scale)
		//__m128i _mm_mask_i64gather_epi64(__m128i src,__int64 const *base,__m128i index,__m128i mask,const int scale)
		//__m128d _mm_mask_i64gather_pd(__m128d src,double const *base,__m128i index,__m128d mask,const int scale)
		//__m128 _mm_mask_i64gather_ps(__m128 src,float const *base,__m128i index,__m128 mask,const int scale)
		//__m128i _mm_maskload_epi32(int const *,__m128i)
		//__m128i _mm_maskload_epi64( __int64 const *,__m128i)
		//__m128d _mm_maskload_pd(double const *,__m128i)
		//__m128 _mm_maskload_ps(float const *,__m128i)
		//void _mm_maskmoveu_si128(__m128i,__m128i,char*)
		//void _mm_maskstore_epi32(int *,__m128i,__m128i)
		//void _mm_maskstore_epi64(__int64 *,__m128i,__m128i)
		//void _mm_maskstore_pd(double *,__m128i,__m128d)
		//void _mm_maskstore_ps(float *,__m128i,__m128)
		//__m128i _mm_max_epi16(__m128i,__m128i)
		//__m128i _mm_max_epi32(__m128i,__m128i )
		//__m128i _mm_max_epi8 (__m128i,__m128i )
		//__m128i _mm_max_epu16(__m128i,__m128i )
		//__m128i _mm_max_epu32(__m128i,__m128i )
		//__m128i _mm_max_epu8(__m128i,__m128i)
		//__m128d _mm_max_pd(__m128d,__m128d)
		//__m128 _mm_max_ps(__m128,__m128)
		//__m128d _mm_max_sd(__m128d,__m128d)
		//__m128 _mm_max_ss(__m128,__m128)

		//void _mm_mfence(void)
		makeMethod(target, _mm_mfence, _mm_mfence());

		//__m128i _mm_min_epi16(__m128i,__m128i)
		//__m128i _mm_min_epi32(__m128i,__m128i )
		//__m128i _mm_min_epi8 (__m128i,__m128i )
		//__m128i _mm_min_epu16(__m128i,__m128i )
		//__m128i _mm_min_epu32(__m128i,__m128i )
		//__m128i _mm_min_epu8(__m128i,__m128i)
		//__m128d _mm_min_pd(__m128d,__m128d)
		//__m128 _mm_min_ps(__m128,__m128)
		//__m128d _mm_min_sd(__m128d,__m128d)
		//__m128 _mm_min_ss(__m128,__m128)
		//__m128i _mm_minpos_epu16(__m128i )
		//void _mm_monitor(void const*,unsigned int,unsigned int)
		//__m128i _mm_move_epi64(__m128i)
		//__m128d _mm_move_sd(__m128d,__m128d)
		//__m128 _mm_move_ss(__m128,__m128)
		//__m128d _mm_movedup_pd(__m128d)
		//__m128 _mm_movehdup_ps(__m128)
		//__m128 _mm_movehl_ps(__m128,__m128)
		//__m128 _mm_moveldup_ps(__m128)
		//__m128 _mm_movelh_ps(__m128,__m128)
		//int _mm_movemask_epi8(__m128i)
		//int _mm_movemask_pd(__m128d)
		//int _mm_movemask_ps(__m128)
		//__m128i _mm_mpsadbw_epu8(__m128i s1,__m128i,const int)
		//__m128d _mm_msub_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_msub_ps(__m128,__m128,__m128)
		//__m128d _mm_msub_sd(__m128d,__m128d,__m128d)
		//__m128 _mm_msub_ss(__m128,__m128,__m128)
		//__m128d _mm_msubadd_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_msubadd_ps(__m128,__m128,__m128)
		//__m128i _mm_mul_epi32(__m128i,__m128i )
		//__m128i _mm_mul_epu32(__m128i,__m128i)
		//__m128d _mm_mul_pd(__m128d,__m128d)
		//__m128 _mm_mul_ps(__m128,__m128)
		//__m128d _mm_mul_sd(__m128d,__m128d)
		//__m128 _mm_mul_ss(__m128,__m128)
		//__m128i _mm_mulhi_epi16(__m128i,__m128i)
		//__m128i _mm_mulhi_epu16(__m128i,__m128i)
		//__m128i _mm_mulhrs_epi16(__m128i,__m128i)
		//__m128i _mm_mullo_epi16(__m128i,__m128i)
		//__m128i _mm_mullo_epi32(__m128i,__m128i )
		//void _mm_mwait(unsigned int,unsigned int)
		//__m128d _mm_nmacc_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_nmacc_ps(__m128,__m128,__m128)
		//__m128d _mm_nmacc_sd(__m128d,__m128d,__m128d)
		//__m128 _mm_nmacc_ss(__m128,__m128,__m128)
		//__m128d _mm_nmsub_pd(__m128d,__m128d,__m128d)
		//__m128 _mm_nmsub_ps(__m128,__m128,__m128)
		//__m128d _mm_nmsub_sd(__m128d,__m128d,__m128d)
		//__m128 _mm_nmsub_ss(__m128,__m128,__m128)
		//__m128d _mm_or_pd(__m128d,__m128d)
		//__m128 _mm_or_ps(__m128,__m128)
		//__m128i _mm_or_si128(__m128i,__m128i)
		//__m128i _mm_packs_epi16(__m128i,__m128i)
		//__m128i _mm_packs_epi32(__m128i,__m128i)
		//__m128i _mm_packus_epi16(__m128i,__m128i)
		//__m128i _mm_packus_epi32(__m128i,__m128i )
		//void _mm_pause(void)
		//__m128i _mm_perm_epi8(__m128i,__m128i,__m128i)
		//__m128d _mm_permute_pd(__m128d,int)
		//__m128 _mm_permute_ps(__m128,int)
		//__m128d _mm_permute2_pd(__m128d,__m128d,__m128i,int)
		//__m128 _mm_permute2_ps(__m128,__m128,__m128i,int)
		//__m128d _mm_permutevar_pd(__m128d,__m128i)
		//__m128 _mm_permutevar_ps(__m128,__m128i)
		//int _mm_popcnt_u32(unsigned int)
		//__int64 _mm_popcnt_u64(unsigned __int64)
		//void _mm_prefetch(char*,int)
		//__m128 _mm_rcp_ps(__m128)
		//__m128 _mm_rcp_ss(__m128)
		//__m128i _mm_rot_epi16(__m128i,__m128i)
		//__m128i _mm_rot_epi32(__m128i,__m128i)
		//__m128i _mm_rot_epi64(__m128i,__m128i)
		//__m128i _mm_rot_epi8(__m128i,__m128i)
		//__m128i _mm_rot_epi16(__m128i,int)
		//__m128i _mm_rot_epi32(__m128i,int)
		//__m128i _mm_rot_epi64(__m128i,int)
		//__m128i _mm_rot_epi8(__m128i,int)
		//__m128d _mm_round_pd(__m128d,const int )
		//__m128 _mm_round_ps(__m128,const int )
		//__m128d _mm_round_sd(__m128d,__m128d,const int )
		//__m128 _mm_round_ss(__m128,__m128,const int )
		//__m128 _mm_rsqrt_ps(__m128)
		//__m128 _mm_rsqrt_ss(__m128)
		//__m128i _mm_sad_epu8(__m128i,__m128i)
		//__m128i _mm_set_epi16(short,short,short,short,short,short,short,short)
		//__m128i _mm_set_epi32(int,int,int,int)
		//__m128i _mm_set_epi64x(__int64 i1,__int64 i0)
		//__m128i _mm_set_epi8(char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char)
		//__m128d _mm_set_pd(double,double)
		//__m128 _mm_set_ps(float,float,float,float)
		//__m128 _mm_set_ps1(float)
		//__m128d _mm_set_sd(double)
		//__m128 _mm_set_ss(float)
		//__m128i _mm_set1_epi16(short)
		//__m128i _mm_set1_epi32(int)
		//__m128i _mm_set1_epi64x(__int64 i)
		//__m128i _mm_set1_epi8(char)
		//__m128d _mm_set1_pd(double)
		//void _mm_setcsr(unsigned int)
		//__m128i _mm_setl_epi64(__m128i)
		//__m128i _mm_setr_epi16(short,short,short,short,short,short,short,short)
		//__m128i _mm_setr_epi32(int,int,int,int)
		//__m128i _mm_setr_epi8(char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char)
		//__m128d _mm_setr_pd(double,double)
		//__m128 _mm_setr_ps(float,float,float,float)
		//__m128d _mm_setzero_pd(void)
		//__m128 _mm_setzero_ps(void)
		//__m128i _mm_setzero_si128(void)

		//void _mm_sfence(void)
		makeMethod(target, _mm_sfence, _mm_sfence());

		//__m128i _mm_sha_epi16(__m128i,__m128i)
		//__m128i _mm_sha_epi32(__m128i,__m128i)
		//__m128i _mm_sha_epi64(__m128i,__m128i)
		//__m128i _mm_sha_epi8(__m128i,__m128i)
		//__m128i _mm_shl_epi16(__m128i,__m128i)
		//__m128i _mm_shl_epi32(__m128i,__m128i)
		//__m128i _mm_shl_epi64(__m128i,__m128i)
		//__m128i _mm_shl_epi8(__m128i,__m128i)
		//__m128i _mm_shuffle_epi32(__m128i,int)
		//__m128i _mm_shuffle_epi8(__m128i,__m128i)
		//__m128d _mm_shuffle_pd(__m128d,__m128d,int)
		//__m128 _mm_shuffle_ps(__m128,__m128,unsigned int)
		//__m128i _mm_shufflehi_epi16(__m128i,int)
		//__m128i _mm_shufflelo_epi16(__m128i,int)
		//__m128i _mm_sign_epi16(__m128i,__m128i)
		//__m128i _mm_sign_epi32(__m128i,__m128i)
		//__m128i _mm_sign_epi8(__m128i,__m128i)
		//__m128i _mm_sll_epi16(__m128i,__m128i)
		//__m128i _mm_sll_epi32(__m128i,__m128i)
		//__m128i _mm_sll_epi64(__m128i,__m128i)
		//__m128i _mm_slli_epi16(__m128i,int)
		//__m128i _mm_slli_epi32(__m128i,int)
		//__m128i _mm_slli_epi64(__m128i,int)
		//__m128i _mm_slli_si128(__m128i,int)
		//__m128i _mm_sllv_epi32(__m128i,__m128i)
		//__m128i _mm_sllv_epi64(__m128i,__m128i)
		//__m128d _mm_sqrt_pd(__m128d)
		//__m128 _mm_sqrt_ps(__m128)
		//__m128d _mm_sqrt_sd(__m128d,__m128d)
		//__m128 _mm_sqrt_ss(__m128)
		//__m128i _mm_sra_epi16(__m128i,__m128i)
		//__m128i _mm_sra_epi32(__m128i,__m128i)
		//__m128i _mm_srai_epi16(__m128i,int)
		//__m128i _mm_srai_epi32(__m128i,int)
		//__m128i _mm_srav_epi32(__m128i,__m128i)
		//__m128i _mm_srl_epi16(__m128i,__m128i)
		//__m128i _mm_srl_epi32(__m128i,__m128i)
		//__m128i _mm_srl_epi64(__m128i,__m128i)
		//__m128i _mm_srli_epi16(__m128i,int)
		//__m128i _mm_srli_epi32(__m128i,int)
		//__m128i _mm_srli_epi64(__m128i,int)
		//__m128i _mm_srli_si128(__m128i,int)
		//__m128i _mm_srlv_epi32(__m128i,__m128i)
		//__m128i _mm_srlv_epi64(__m128i,__m128i)
		//void _mm_store_pd(double*,__m128d)
		//void _mm_store_ps(float*,__m128)
		//void _mm_store_ps1(float*,__m128)
		//void _mm_store_sd(double*,__m128d)
		//void _mm_store_si128(__m128i*,__m128i)
		//void _mm_store_ss(float*,__m128)
		//void _mm_store1_pd(double*,__m128d)
		//void _mm_storeh_pd(double*,__m128d)
		//void _mm_storeh_pi(__m64*,__m128)
		//void _mm_storel_epi64(__m128i*,__m128i)
		//void _mm_storel_pd(double*,__m128d)
		//void _mm_storel_pi(__m64*,__m128)
		//void _mm_storer_pd(double*,__m128d)
		//void _mm_storer_ps(float*,__m128)
		//void _mm_storeu_pd(double*,__m128d)
		//void _mm_storeu_ps(float*,__m128)
		//void _mm_storeu_si128(__m128i*,__m128i)
		//__m128i _mm_stream_load_si128(__m128i* )
		//void _mm_stream_pd(double*,__m128d)
		//void _mm_stream_ps(float*,__m128)
		//void _mm_stream_sd(double*,__m128d)
		//void _mm_stream_si128(__m128i*,__m128i)
		//void _mm_stream_si32(int*,int)
		//void _mm_stream_si64x(__int64 *,__int64)
		//void _mm_stream_ss(float*,__m128)
		//__m128i _mm_sub_epi16(__m128i,__m128i)
		//__m128i _mm_sub_epi32(__m128i,__m128i)
		//__m128i _mm_sub_epi64(__m128i,__m128i)
		//__m128i _mm_sub_epi8(__m128i,__m128i)
		//__m128d _mm_sub_pd(__m128d,__m128d)
		//__m128 _mm_sub_ps(__m128,__m128)
		//__m128d _mm_sub_sd(__m128d,__m128d)
		//__m128 _mm_sub_ss(__m128,__m128)
		//__m128i _mm_subs_epi16(__m128i,__m128i)
		//__m128i _mm_subs_epi8(__m128i,__m128i)
		//__m128i _mm_subs_epu16(__m128i,__m128i)
		//__m128i _mm_subs_epu8(__m128i,__m128i)
		//int _mm_testc_pd(__m128d,__m128d)
		//int _mm_testc_ps(__m128,__m128)
		//int _mm_testc_si128(__m128i,__m128i )
		//int _mm_testnzc_pd(__m128d,__m128d)
		//int _mm_testnzc_ps(__m128,__m128)
		//int _mm_testnzc_si128(__m128i,__m128i )
		//int _mm_testz_pd(__m128d,__m128d)
		//int _mm_testz_ps(__m128,__m128)
		//int _mm_testz_si128(__m128i,__m128i )
		//int _mm_ucomieq_sd(__m128d,__m128d)
		//int _mm_ucomieq_ss(__m128,__m128)
		//int _mm_ucomige_sd(__m128d,__m128d)
		//int _mm_ucomige_ss(__m128,__m128)
		//int _mm_ucomigt_sd(__m128d,__m128d)
		//int _mm_ucomigt_ss(__m128,__m128)
		//int _mm_ucomile_sd(__m128d,__m128d)
		//int _mm_ucomile_ss(__m128,__m128)
		//int _mm_ucomilt_sd(__m128d,__m128d)
		//int _mm_ucomilt_ss(__m128,__m128)
		//int _mm_ucomineq_sd(__m128d,__m128d)
		//int _mm_ucomineq_ss(__m128,__m128)
		//__m128i _mm_unpackhi_epi16(__m128i,__m128i)
		//__m128i _mm_unpackhi_epi32(__m128i,__m128i)
		//__m128i _mm_unpackhi_epi64(__m128i,__m128i)
		//__m128i _mm_unpackhi_epi8(__m128i,__m128i)
		//__m128d _mm_unpackhi_pd(__m128d,__m128d)
		//__m128 _mm_unpackhi_ps(__m128,__m128)
		//__m128i _mm_unpacklo_epi16(__m128i,__m128i)
		//__m128i _mm_unpacklo_epi32(__m128i,__m128i)
		//__m128i _mm_unpacklo_epi64(__m128i,__m128i)
		//__m128i _mm_unpacklo_epi8(__m128i,__m128i)
		//__m128d _mm_unpacklo_pd(__m128d,__m128d)
		//__m128 _mm_unpacklo_ps(__m128,__m128)
		//__m128d _mm_xor_pd(__m128d,__m128d)
		//__m128 _mm_xor_ps(__m128,__m128)
		//__m128i _mm_xor_si128(__m128i,__m128i)
		//__m256i _mm256_abs_epi16(__m256i)
		//__m256i _mm256_abs_epi32(__m256i)
		//__m256i _mm256_abs_epi8(__m256i)
		//__m256i _mm256_add_epi16(__m256i,__m256i)
		//__m256i _mm256_add_epi32(__m256i,__m256i)
		//__m256i _mm256_add_epi64(__m256i,__m256i)
		//__m256i _mm256_add_epi8(__m256i,__m256i)
		//__m256d _mm256_add_pd(__m256d,__m256d)
		//__m256 _mm256_add_ps(__m256,__m256)
		//__m256i _mm256_adds_epi16(__m256i,__m256i)
		//__m256i _mm256_adds_epi8(__m256i,__m256i)
		//__m256i _mm256_adds_epu16(__m256i,__m256i)
		//__m256i _mm256_adds_epu8(__m256i,__m256i)
		//__m256d _mm256_addsub_pd(__m256d,__m256d)
		//__m256 _mm256_addsub_ps(__m256,__m256)
		//__m256i _mm256_alignr_epi8(__m256i,__m256i,const int)
		//__m256d _mm256_and_pd(__m256d,__m256d)
		//__m256 _mm256_and_ps(__m256,__m256)
		//__m256i _mm256_and_si256(__m256i,__m256i)
		//__m256d _mm256_andnot_pd(__m256d,__m256d)
		//__m256 _mm256_andnot_ps(__m256,__m256)
		//__m256i _mm256_andnot_si256(__m256i,__m256i)
		//__m256i _mm256_avg_epu16(__m256i,__m256i)
		//__m256i _mm256_avg_epu8(__m256i,__m256i)
		//__m256i _mm256_blend_epi16(__m256i,__m256i,const int)
		//__m256i _mm256_blend_epi32(__m256i,__m256i,const int)
		//__m256d _mm256_blend_pd(__m256d,__m256d,const int)
		//__m256 _mm256_blend_ps(__m256,__m256,const int)
		//__m256i _mm256_blendv_epi8(__m256i,__m256i,__m256i)
		//__m256d _mm256_blendv_pd(__m256d,__m256d,__m256d)
		//__m256 _mm256_blendv_ps(__m256,__m256,__m256)
		//__m256d _mm256_broadcast_pd(__m128d const *)
		//__m256 _mm256_broadcast_ps(__m128 const *)
		//__m256d _mm256_broadcast_sd(double const *)
		//__m256 _mm256_broadcast_ss(float const *)
		//__m256i _mm256_broadcastb_epi8 (__m128i)
		//__m256i _mm256_broadcastd_epi32(__m128i)
		//__m256i _mm256_broadcastq_epi64(__m128i)
		//__m256d _mm256_broadcastsd_pd(__m128d)
		//__m256i _mm256_broadcastsi128_si256(__m128i)
		//__m256 _mm256_broadcastss_ps(__m128)
		//__m256i _mm256_broadcastw_epi16(__m128i)
		//__m256 _mm256_castpd_ps(__m256d)
		//__m256i _mm256_castpd_si256(__m256d)
		//__m256d _mm256_castpd128_pd256(__m128d)
		//__m128d _mm256_castpd256_pd128(__m256d)
		//__m256d _mm256_castps_pd(__m256)
		//__m256i _mm256_castps_si256(__m256)
		//__m256 _mm256_castps128_ps256(__m128)
		//__m128 _mm256_castps256_ps128(__m256)
		//__m256i _mm256_castsi128_si256(__m128i)
		//__m256d _mm256_castsi256_pd(__m256i)
		//__m256 _mm256_castsi256_ps(__m256i)
		//__m128i _mm256_castsi256_si128(__m256i)
		//__m256i _mm256_cmov_si256(__m256i,__m256i,__m256i)
		//__m256d _mm256_cmp_pd(__m256d,__m256d,const int)
		//__m256 _mm256_cmp_ps(__m256,__m256,const int)
		//__m256i _mm256_cmpeq_epi16(__m256i,__m256i)
		//__m256i _mm256_cmpeq_epi32(__m256i,__m256i)
		//__m256i _mm256_cmpeq_epi64(__m256i,__m256i)
		//__m256i _mm256_cmpeq_epi8(__m256i,__m256i)
		//__m256i _mm256_cmpgt_epi16(__m256i,__m256i)
		//__m256i _mm256_cmpgt_epi32(__m256i,__m256i)
		//__m256i _mm256_cmpgt_epi64(__m256i,__m256i)
		//__m256i _mm256_cmpgt_epi8(__m256i,__m256i)
		//__m256i _mm256_cvtepi16_epi32(__m128i)
		//__m256i _mm256_cvtepi16_epi64(__m128i)
		//__m256i _mm256_cvtepi32_epi64(__m128i)
		//__m256d _mm256_cvtepi32_pd(__m128i)
		//__m256 _mm256_cvtepi32_ps(__m256i)
		//__m256i _mm256_cvtepi8_epi16(__m128i)
		//__m256i _mm256_cvtepi8_epi32(__m128i)
		//__m256i _mm256_cvtepi8_epi64(__m128i)
		//__m256i _mm256_cvtepu16_epi32(__m128i)
		//__m256i _mm256_cvtepu16_epi64(__m128i)
		//__m256i _mm256_cvtepu32_epi64(__m128i)
		//__m256i _mm256_cvtepu8_epi16(__m128i)
		//__m256i _mm256_cvtepu8_epi32(__m128i)
		//__m256i _mm256_cvtepu8_epi64(__m128i)
		//__m128i _mm256_cvtpd_epi32(__m256d)
		//__m128 _mm256_cvtpd_ps(__m256d)
		//__m256 _mm256_cvtph_ps(__m128i)
		//__m256i _mm256_cvtps_epi32(__m256)
		//__m256d _mm256_cvtps_pd(__m128)
		//__m128i _mm256_cvtps_ph(__m256,const int)
		//__m128i _mm256_cvttpd_epi32(__m256d)
		//__m256i _mm256_cvttps_epi32(__m256)
		//__m256d _mm256_div_pd(__m256d,__m256d)
		//__m256 _mm256_div_ps(__m256,__m256)
		//__m256 _mm256_dp_ps(__m256,__m256,const int)
		//__m128d _mm256_extractf128_pd(__m256d,const int)
		//__m128 _mm256_extractf128_ps(__m256,const int)
		//__m128i _mm256_extractf128_si256(__m256i,const int)
		//__m128i _mm256_extracti128_si256(__m256i a,int offset)
		//__m256d _mm256_fmadd_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fmadd_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_fmaddsub_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fmaddsub_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_fmsub_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fmsub_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_fmsubadd_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fmsubadd_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_fnmadd_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fnmadd_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_fnmsub_pd (__m256d a,__m256d b,__m256d c)
		//__m256 _mm256_fnmsub_ps (__m256 a,__m256 b,__m256 c)
		//__m256d _mm256_frcz_pd(__m256d)
		//__m256 _mm256_frcz_ps(__m256)
		//__m256i _mm256_hadd_epi16(__m256i,__m256i)
		//__m256i _mm256_hadd_epi32(__m256i,__m256i)
		//__m256d _mm256_hadd_pd(__m256d,__m256d)
		//__m256 _mm256_hadd_ps(__m256,__m256)
		//__m256i _mm256_hadds_epi16(__m256i,__m256i)
		//__m256i _mm256_hsub_epi16(__m256i,__m256i)
		//__m256i _mm256_hsub_epi32(__m256i,__m256i)
		//__m256d _mm256_hsub_pd(__m256d,__m256d)
		//__m256 _mm256_hsub_ps(__m256,__m256)
		//__m256i _mm256_hsubs_epi16(__m256i,__m256i)
		//__m256i _mm256_i32gather_epi32(int const *base,__m256i index,const int scale)
		//__m256i _mm256_i32gather_epi64(__int64 const *base,__m128i index,const int scale)
		//__m256d _mm256_i32gather_pd(double const *base,__m128i index,const int scale)
		//__m256 _mm256_i32gather_ps(float const *base,__m256i index,const int scale)
		//__m256i _mm256_i64gather_epi32(int const *base,__m256i index,const int scale)
		//__m256i _mm256_i64gather_epi64(__int64 const *base,__m256i index,const int scale)
		//__m256d _mm256_i64gather_pd(double const *base,__m256i index,const int scale)
		//__m128 _mm256_i64gather_ps(float const *base,__m256i index,const int scale)
		//__m256d _mm256_insertf128_pd(__m256d,__m128d,int )
		//__m256 _mm256_insertf128_ps(__m256,__m128,int )
		//__m256i _mm256_insertf128_si256(__m256i,__m128i,int )
		//__m256i _mm256_inserti128_si256(__m256i,__m128i,int)
		//__m256i _mm256_lddqu_si256(__m256i *)
		//__m256d _mm256_load_pd(double const *)
		//__m256 _mm256_load_ps(float const *)
		//__m256i _mm256_load_si256(__m256i *)
		//__m256d _mm256_loadu_pd(double const *)
		//__m256 _mm256_loadu_ps(float const *)
		//__m256i _mm256_loadu_si256(__m256i *)
		//__m256d _mm_macc_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_macc_ps(__m256,__m256,__m256)
		//__m256i _mm256_madd_epi16(__m256i,__m256i)
		//__m256d _mm_maddsub_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_maddsub_ps(__m256,__m256,__m256)
		//__m256i _mm256_maddubs_epi16(__m256i,__m256i)
		//__m256i _mm256_mask_i32gather_epi32(__m256i src,int const *base,__m256i index,__m256i mask,const int scale)
		//__m256i _mm256_mask_i32gather_epi64(__m256i src,__int64 const *base,__m128i index,__m256i mask,const int scale)
		//__m256d _mm256_mask_i32gather_pd(__m256d src,double const *base,__m128i index,__m256d mask,const int scale)
		//__m256 _mm256_mask_i32gather_ps(__m256 src,float const *base,__m256i index,__m256 mask,const int scale)
		//__m128i _mm256_mask_i64gather_epi32(__m128i src,int const *base,__m256i index,__m128i mask,const int scale)
		//__m256i _mm256_mask_i64gather_epi64(__m256i src,__int64 const *base,__m256i index,__m256i mask,const int scale)
		//__m256d _mm256_mask_i64gather_pd(__m256d src,double const *base,__m256i index,__m256d mask,const int scale)
		//__m128 _mm256_mask_i64gather_ps(__m128 src,float const *base,__m256i index,__m128 mask,const int scale)
		//__m256i _mm256_maskload_epi32(int const *,__m256i)
		//__m256i _mm256_maskload_epi64( __int64 const *,__m256i)
		//__m256d _mm256_maskload_pd(double const *,__m256i)
		//__m256 _mm256_maskload_ps(float const *,__m256i)
		//void _mm256_maskstore_epi32(int *,__m256i,__m256i)
		//void _mm256_maskstore_epi64(__int64 *,__m256i,__m256i)
		//void _mm256_maskstore_pd(double *,__m256i,__m256d)
		//void _mm256_maskstore_ps(float *,__m256i,__m256)
		//__m256i _mm256_max_epi16(__m256i,__m256i)
		//__m256i _mm256_max_epi32(__m256i,__m256i)
		//__m256i _mm256_max_epi8(__m256i,__m256i)
		//__m256i _mm256_max_epu16(__m256i,__m256i)
		//__m256i _mm256_max_epu32(__m256i,__m256i)
		//__m256i _mm256_max_epu8(__m256i,__m256i)
		//__m256d _mm256_max_pd(__m256d,__m256d)
		//__m256 _mm256_max_ps(__m256,__m256)
		//__m256i _mm256_min_epi16(__m256i,__m256i)
		//__m256i _mm256_min_epi32(__m256i,__m256i)
		//__m256i _mm256_min_epi8(__m256i,__m256i)
		//__m256i _mm256_min_epu16(__m256i,__m256i)
		//__m256i _mm256_min_epu32(__m256i,__m256i)
		//__m256i _mm256_min_epu8(__m256i,__m256i)
		//__m256d _mm256_min_pd(__m256d,__m256d)
		//__m256 _mm256_min_ps(__m256,__m256)
		//__m256d _mm256_movedup_pd(__m256d)
		//__m256 _mm256_movehdup_ps(__m256)
		//__m256 _mm256_moveldup_ps(__m256)
		//int _mm256_movemask_epi8(__m256i)
		//int _mm256_movemask_pd(__m256d)
		//int _mm256_movemask_ps(__m256)
		//__m256i _mm256_mpsadbw_epu8(__m256i,__m256i,const int)
		//__m256d _mm_msub_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_msub_ps(__m256,__m256,__m256)
		//__m256d _mm_msubadd_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_msubadd_ps(__m256,__m256,__m256)
		//__m256i _mm256_mul_epi32(__m256i,__m256i)
		//__m256i _mm256_mul_epu32(__m256i,__m256i)
		//__m256d _mm256_mul_pd(__m256d,__m256d)
		//__m256 _mm256_mul_ps(__m256,__m256)
		//__m256i _mm256_mulhi_epi16(__m256i,__m256i)
		//__m256i _mm256_mulhi_epu16(__m256i,__m256i)
		//__m256i _mm256_mulhrs_epi16(__m256i,__m256i)
		//__m256i _mm256_mullo_epi16(__m256i,__m256i)
		//__m256i _mm256_mullo_epi32(__m256i,__m256i)
		//__m256d _mm_nmacc_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_nmacc_ps(__m256,__m256,__m256)
		//__m256d _mm_nmsub_pd(__m256d,__m256d,__m256d)
		//__m256 _mm_nmsub_ps(__m256,__m256,__m256)
		//__m256d _mm256_or_pd(__m256d,__m256d)
		//__m256 _mm256_or_ps(__m256,__m256)
		//__m256i _mm256_or_si256(__m256i,__m256i)
		//__m256i _mm256_packs_epi16(__m256i,__m256i)
		//__m256i _mm256_packs_epi32(__m256i,__m256i)
		//__m256i _mm256_packus_epi16(__m256i,__m256i)
		//__m256i _mm256_packus_epi32(__m256i,__m256i)
		//__m256d _mm256_permute_pd(__m256d,int)
		//__m256 _mm256_permute_ps(__m256,int)
		//__m256d _mm256_permute2_pd(__m256d,__m256d,__m256i,int)
		//__m256 _mm256_permute2_ps(__m256,__m256,__m256i,int)
		//__m256d _mm256_permute2f128_pd(__m256d,__m256d,int)
		//__m256 _mm256_permute2f128_ps(__m256,__m256,int)
		//__m256i _mm256_permute2f128_si256(__m256i,__m256i,int)
		//__m256i _mm256_permute2x128_si256(__m256i,__m256i,const int)
		//__m256i _mm256_permute4x64_epi64 (__m256i,const int)
		//__m256d _mm256_permute4x64_pd(__m256d,const int)
		//__m256d _mm256_permutevar_pd(__m256d,__m256i)
		//__m256 _mm256_permutevar_ps(__m256,__m256i)
		//__m256i _mm256_permutevar8x32_epi32(__m256i,__m256i)
		//__m256 _mm256_permutevar8x32_ps (__m256,__m256i)
		//__m256 _mm256_rcp_ps(__m256)
		//__m256d _mm256_round_pd(__m256d,int)
		//__m256 _mm256_round_ps(__m256,int)
		//__m256 _mm256_rsqrt_ps(__m256)
		//__m256i _mm256_sad_epu8(__m256i,__m256i)
		//(__m256i _mm256_set_epi16(short
		//__m256i _mm256_set_epi32(int,int,int,int,int,int,int,int)
		//__m256i _mm256_set_epi64x(long long,long long,long long,long long)
		//__m256i _mm256_set_epi8(char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char)
		//__m256d _mm256_set_pd(double,double,double,double)
		//__m256 _mm256_set_ps(float,float,float,float,float,float,float,float)
		//__m256i _mm256_set1_epi16(short)
		//__m256i _mm256_set1_epi32(int)
		//__m256i _mm256_set1_epi64x(long long)
		//__m256i _mm256_set1_epi8(char)
		//__m256d _mm256_set1_pd(double)
		//__m256 _mm256_set1_ps(float)
		//(__m256i _mm256_setr_epi16(short
		//__m256i _mm256_setr_epi32(int,int,int,int,int,int,int,int)
		//__m256i _mm256_setr_epi64x(long long,long long,long long,long long)
		//(__m256i _mm256_setr_epi8(char
		//__m256d _mm256_setr_pd(double,double,double,double)
		//__m256 _mm256_setr_ps(float,float,float,float,float,float,float,float)
		//__m256d _mm256_setzero_pd(void)
		//__m256 _mm256_setzero_ps(void)
		//__m256i _mm256_setzero_si256(void)
		//__m256i _mm256_shuffle_epi32(__m256i,const int)
		//__m256i _mm256_shuffle_epi8(__m256i,__m256i)
		//__m256d _mm256_shuffle_pd(__m256d,__m256d,const int)
		//__m256 _mm256_shuffle_ps(__m256,__m256,const int)
		//__m256i _mm256_shufflehi_epi16(__m256i,const int)
		//__m256i _mm256_shufflelo_epi16(__m256i,const int)
		//__m256i _mm256_sign_epi16(__m256i,__m256i)
		//__m256i _mm256_sign_epi32(__m256i,__m256i)
		//__m256i _mm256_sign_epi8(__m256i,__m256i)
		//__m256i _mm256_sll_epi16(__m256i,__m128i)
		//__m256i _mm256_sll_epi32(__m256i,__m128i)
		//__m256i _mm256_sll_epi64(__m256i,__m128i)
		//__m256i _mm256_slli_epi16(__m256i,int)
		//__m256i _mm256_slli_epi32(__m256i,int)
		//__m256i _mm256_slli_epi64(__m256i,int)
		//__m256i _mm256_slli_si256(__m256i,int)
		//__m256i _mm256_sllv_epi32(__m256i,__m256i)
		//__m256i _mm256_sllv_epi64(__m256i,__m256i)
		//__m256d _mm256_sqrt_pd(__m256d)
		//__m256 _mm256_sqrt_ps(__m256)
		//__m256i _mm256_sra_epi16(__m256i,__m128i)
		//__m256i _mm256_sra_epi32(__m256i,__m128i)
		//__m256i _mm256_srai_epi16(__m256i,int)
		//__m256i _mm256_srai_epi32(__m256i,int)
		//__m256i _mm256_srav_epi32(__m256i,__m256i)
		//__m256i _mm256_srl_epi16(__m256i,__m128i)
		//__m256i _mm256_srl_epi32(__m256i,__m128i)
		//__m256i _mm256_srl_epi64(__m256i,__m128i)
		//__m256i _mm256_srli_epi16(__m256i,int)
		//__m256i _mm256_srli_epi32(__m256i,int)
		//__m256i _mm256_srli_epi64(__m256i,int)
		//__m256i _mm256_srli_si256(__m256i,int)
		//__m256i _mm256_srlv_epi32(__m256i,__m256i)
		//__m256i _mm256_srlv_epi64(__m256i,__m256i)
		//void _mm256_store_pd(double *,__m256d)
		//void _mm256_store_ps(float *,__m256)
		//void _mm256_store_si256(__m256i *,__m256i)
		//void _mm256_storeu_pd(double *,__m256d)
		//void _mm256_storeu_ps(float *,__m256)
		//void _mm256_storeu_si256(__m256i *,__m256i)
		//__m256i _mm256_stream_load_si256(__m256i const *)
		//void __mm256_stream_pd(double *,__m256d)
		//void _mm256_stream_ps(float *p,__m256 a)
		//void __mm256_stream_si256(__m256i *,__m256i)
		//__m256i _mm256_sub_epi16(__m256i,__m256i)
		//__m256i _mm256_sub_epi32(__m256i,__m256i)
		//__m256i _mm256_sub_epi64(__m256i,__m256i)
		//__m256i _mm256_sub_epi8(__m256i,__m256i)
		//__m256d _mm256_sub_pd(__m256d,__m256d)
		//__m256 _mm256_sub_ps(__m256,__m256)
		//__m256i _mm256_subs_epi16(__m256i,__m256i)
		//__m256i _mm256_subs_epi8(__m256i,__m256i)
		//__m256i _mm256_subs_epu16(__m256i,__m256i)
		//__m256i _mm256_subs_epu8(__m256i,__m256i)
		//int _mm256_testc_pd(__m256d,__m256d)
		//int _mm256_testc_ps(__m256,__m256)
		//int _mm256_testc_si256(__m256i,__m256i)
		//int _mm256_testnzc_pd(__m256d,__m256d)
		//int _mm256_testnzc_ps(__m256,__m256)
		//int _mm256_testnzc_si256(__m256i,__m256i)
		//int _mm256_testz_pd(__m256d,__m256d)
		//int _mm256_testz_ps(__m256,__m256)
		//int _mm256_testz_si256(__m256i,__m256i)
		//__m256i _mm256_unpackhi_epi16(__m256i,__m256i)
		//__m256i _mm256_unpackhi_epi32(__m256i,__m256i)
		//__m256i _mm256_unpackhi_epi64(__m256i,__m256i)
		//__m256i _mm256_unpackhi_epi8(__m256i,__m256i)
		//__m256d _mm256_unpackhi_pd(__m256d,__m256d)
		//__m256 _mm256_unpackhi_ps(__m256,__m256)
		//__m256i _mm256_unpacklo_epi16(__m256i,__m256i)
		//__m256i _mm256_unpacklo_epi32(__m256i,__m256i)
		//__m256i _mm256_unpacklo_epi64(__m256i,__m256i)
		//__m256i _mm256_unpacklo_epi8(__m256i,__m256i)
		//__m256d _mm256_unpacklo_pd(__m256d,__m256d)
		//__m256 _mm256_unpacklo_ps(__m256,__m256)
		//__m256d _mm256_xor_pd(__m256d,__m256d)
		//__m256 _mm256_xor_ps(__m256,__m256)
		//__m256i _mm256_xor_si256(__m256i,__m256i)
		//void _mm256_zeroall(void)
		//void _mm256_zeroupper(void)
		//VOID __movsb(IN PBYTE,IN BYTE const *,IN SIZE_T)
		//VOID __movsd(IN PDWORD,IN DWORD const *,IN SIZE_T)
		//VOID __movsq(IN PDWORD64,IN DWORD64 const *,IN SIZE_T)
		//VOID __movsw(IN PWORD,IN WORD const *,IN SIZE_T)
		//__int64 _mul128(__int64 multiplier,__int64 multiplicand,__int64 *highproduct)
		//__int64 __mulh(__int64,__int64)
		//unsigned int _mulx_u32(unsigned int,unsigned int,unsigned int*)
		//unsigned __int64 _mulx_u64(unsigned __int64,unsigned __int64,unsigned __int64*)

		//void __nop(void)
		makeMethod(target, __nop, __nop());

		//void __nvreg_restore_fence(void)
		//void __nvreg_save_fence(void)
		//void __outbyte(unsigned short Port,unsigned char Data)
		//void __outbytestring(unsigned short Port,unsigned char *Buffer,unsigned long Count)
		//void __outdword(unsigned short Port,unsigned long Data)
		//void __outdwordstring(unsigned short Port,unsigned long *Buffer,unsigned long Count)
		//void __outword(unsigned short Port,unsigned short Data)
		//void __outwordstring(unsigned short Port,unsigned short *Buffer,unsigned long Count)
		//unsigned int _pdep_u32(unsigned int,unsigned int)
		//unsigned __int64 _pdep_u64(unsigned __int64,unsigned __int64)
		//unsigned int _pext_u32(unsigned int,unsigned int)
		//unsigned __int64 _pext_u64(unsigned __int64,unsigned __int64)

		//unsigned short __popcnt16(unsigned short)
		makeMethodRet(target, __popcnt16, __popcnt16(info[0]->Uint32Value()));

		//unsigned int __popcnt(unsigned int)
		makeMethodRet(target, __popcnt, __popcnt(info[0]->Uint32Value()));

		//unsigned __int64 __popcnt64(unsigned __int64)
		makeMethod_u64(target, __popcnt64, __popcnt64(static_cast<DWORD64>(info[0]->NumberValue())));

		//int _rdrand16_step(unsigned short *)
		makeMethod_u64(target, _rdrand16_step, _rdrand16_step(reinterpret_cast<uint16_t *>(node::Buffer::Data(info[0]))));

		//int _rdrand32_step(unsigned int *)
		makeMethod_u64(target, _rdrand32_step, _rdrand32_step(reinterpret_cast<uint32_t *>(node::Buffer::Data(info[0]))));

		//int _rdrand64_step(unsigned __int64 *)
		makeMethod_u64(target, _rdrand64_step, _rdrand64_step(reinterpret_cast<uint64_t *>(node::Buffer::Data(info[0]))));

		//int _rdseed16_step(unsigned short *)
		makeMethod_u64(target, _rdseed16_step, _rdseed16_step(reinterpret_cast<uint16_t *>(node::Buffer::Data(info[0]))));

		//int _rdseed32_step(unsigned int *)
		makeMethod_u64(target, _rdseed32_step, _rdseed32_step(reinterpret_cast<uint32_t *>(node::Buffer::Data(info[0]))));

		//int _rdseed64_step(unsigned __int64 *)
		makeMethod_u64(target, _rdseed64_step, _rdseed64_step(reinterpret_cast<uint64_t *>(node::Buffer::Data(info[0]))));

		//unsigned __int64 __rdtsc(void)
		makeMethod_u64(target, __rdtsc, __rdtsc());

		//unsigned __int64 __rdtscp(unsigned int*)
		makeMethod_u64(target, __rdtscp, __rdtscp(reinterpret_cast<uint32_t *>(node::Buffer::Data(info[0]))));

		//void _ReadBarrier(void)
		makeMethod(target, _ReadBarrier, _ReadBarrier());

		//unsigned __int64 __readcr0(void)
		makeMethod_u64(target, __readcr0, __readcr0());

		//unsigned __int64 __readcr2(void)
		makeMethod_u64(target, __readcr2, __readcr2());

		//unsigned __int64 __readcr3(void)
		makeMethod_u64(target, __readcr3, __readcr3());

		//unsigned __int64 __readcr4(void)
		makeMethod_u64(target, __readcr4, __readcr4());

		//unsigned __int64 __readcr8(void)
		makeMethod_u64(target, __readcr8, __readcr8());

		//unsigned __int64 __readdr(unsigned)
		makeMethod(target, __readdr, {
			switch (info[0]->Uint32Value()) {
				case 0: info.GetReturnValue().Set(static_cast<double_t>(__readdr(0))); return;
				case 1: info.GetReturnValue().Set(static_cast<double_t>(__readdr(1))); return;
				case 2: info.GetReturnValue().Set(static_cast<double_t>(__readdr(2))); return;
				case 3: info.GetReturnValue().Set(static_cast<double_t>(__readdr(3))); return;
				case 4: info.GetReturnValue().Set(static_cast<double_t>(__readdr(4))); return;
				case 5: info.GetReturnValue().Set(static_cast<double_t>(__readdr(5))); return;
				case 6: info.GetReturnValue().Set(static_cast<double_t>(__readdr(6))); return;
				case 7: info.GetReturnValue().Set(static_cast<double_t>(__readdr(7))); return;
			}
		});

		//unsigned __int64 __readeflags(void)
		makeMethod_u64(target, __readeflags, __readeflags());

		//unsigned int _readfsbase_u32(void)
		makeMethodRet(target, _readfsbase_u32, _readfsbase_u32());

		//unsigned __int64 _readfsbase_u64(void)
		makeMethod_u64(target, _readfsbase_u64, _readfsbase_u64());

		//unsigned int _readgsbase_u32(void)
		makeMethodRet(target, _readgsbase_u32, _readgsbase_u32());

		//unsigned __int64 _readgsbase_u64(void)
		makeMethod_u64(target, _readgsbase_u64, _readgsbase_u64());

		//unsigned char __readgsbyte(unsigned long Offset)
		makeMethodRet(target, __readgsbyte, __readgsbyte(info[0]->Uint32Value()));

		//unsigned long __readgsdword(unsigned long Offset)
		makeMethodRet(target, __readgsdword, static_cast<uint32_t>(__readgsdword(info[0]->Uint32Value())));

		//unsigned __int64 __readgsqword(unsigned long Offset)
		makeMethodRet(target, __readgsqword, static_cast<double_t>(__readgsqword(info[0]->Uint32Value())));

		//unsigned short __readgsword(unsigned long Offset)
		makeMethodRet(target, __readgsword, __readgsword(info[0]->Uint32Value()));

		//unsigned __int64 __readmsr(unsigned long)
		//unsigned __int64 __readpmc(unsigned long a)

		//void _ReadWriteBarrier(void)
		makeMethod(target, _ReadWriteBarrier, _ReturnAddress());

		//void * _ReturnAddress(void)
		makeMethodPtr(target, _ReturnAddress, _ReturnAddress());

		//unsigned int _rorx_u32(unsigned int,const unsigned int)
		//unsigned __int64 _rorx_u64(unsigned __int64,const unsigned int)
		//unsigned short _rotl16(unsigned short value,unsigned char shift)
		//unsigned char _rotl8(unsigned char value,unsigned char shift)
		//unsigned short _rotr16(unsigned short value,unsigned char shift)
		//unsigned char _rotr8(unsigned char value,unsigned char shift)
		//void _rsm(void)
		//int _sarx_i32(int,unsigned int)
		//__int64 _sarx_i64(__int64,unsigned int)
		//unsigned long __segmentlimit(unsigned long a)
		//void _sgdt(void*)
		//unsigned __int64 __shiftleft128(unsigned __int64 LowPart,unsigned __int64 HighPart,unsigned char Shift)
		//unsigned __int64 __shiftright128(unsigned __int64 LowPart,unsigned __int64 HighPart,unsigned char Shift)
		//unsigned int _shlx_u32(unsigned int,unsigned int)
		//unsigned __int64 _shlx_u64(unsigned __int64,unsigned int)
		//unsigned int _shrx_u32(unsigned int,unsigned int)
		//unsigned __int64 _shrx_u64(unsigned __int64,unsigned int)
		//void __sidt(void*)
		//void *__slwpcb(void)
		//void _stac(void)
		//"void _store_be_u16(void *, unsigned short);
		//void _storebe_i16(void *, short); [3]"
		//"void _store_be_u32(void *, unsigned int);
		//void _storebe_i32(void *, int); [3]"
		//"void _store_be_u64(void *, unsigned __int64);
		//void _storebe_i64(void *, __int64); [3]"

		//void _Store_HLERelease(long volatile *,long)
		makeMethod(target, _Store_HLERelease, _Store_HLERelease(reinterpret_cast<volatile long *>(node::Buffer::Data(info[0])), info[1]->Int32Value()));

		//void _Store64_HLERelease(__int64 volatile *,__int64)
		makeMethod(target, _Store64_HLERelease, _Store64_HLERelease(reinterpret_cast<volatile __int64 *>(node::Buffer::Data(info[0])), static_cast<__int64>(info[1]->NumberValue())));

		//void _StorePointer_HLERelease(void * volatile *,void *)
		makeMethod(target, _StorePointer_HLERelease, _StorePointer_HLERelease(reinterpret_cast<void * volatile *>(node::Buffer::Data(info[0])), reinterpret_cast<void *>(node::Buffer::Data(info[1]))));

		//void __stosb(IN PBYTE,IN BYTE,IN SIZE_T)
		makeMethod(target, __stosb, __stosb(reinterpret_cast<PBYTE>(node::Buffer::Data(info[0])), static_cast<BYTE>(info[1]->NumberValue()), static_cast<SIZE_T>(info[2]->NumberValue())));

		//void __stosd(IN PDWORD,IN DWORD,IN SIZE_T)
		makeMethod(target, __stosd, __stosd(reinterpret_cast<PDWORD>(node::Buffer::Data(info[0])), static_cast<DWORD>(info[1]->NumberValue()), static_cast<SIZE_T>(info[2]->NumberValue())));

		//void __stosq(IN PDWORD64,IN DWORD64,IN SIZE_T)
		makeMethod(target, __stosq, __stosq(reinterpret_cast<PDWORD64>(node::Buffer::Data(info[0])), static_cast<DWORD64>(info[1]->NumberValue()), static_cast<SIZE_T>(info[2]->NumberValue())));

		//void __stosw(IN PWORD,IN WORD,IN SIZE_T)
		makeMethod(target, __stosw, __stosw(reinterpret_cast<PWORD>(node::Buffer::Data(info[0])), static_cast<WORD>(info[1]->NumberValue()), static_cast<SIZE_T>(info[2]->NumberValue())));


		//unsigned char _subborrow_u16(unsigned char b_in,unsigned short src1,unsigned short src2,unsigned short *diff)
		//unsigned char _subborrow_u32(unsigned char b_in,unsigned int src1,unsigned int src2,unsigned int *diff)
		//unsigned char _subborrow_u64(unsigned char b_in,unsigned __int64 src1,unsigned __int64 src2,unsigned __int64 *diff)
		//unsigned char _subborrow_u8(unsigned char b_in,unsigned char src1,unsigned char src2,unsigned char *diff)
		//void __svm_clgi(void)
		//void __svm_invlpga(void*,int)
		//void __svm_skinit(int)
		//void __svm_stgi(void)
		//void __svm_vmload(size_t)
		//void __svm_vmrun(size_t)
		//void __svm_vmsave(size_t)

		//unsigned int _t1mskc_u32(unsigned int)
		makeMethodRet(target, _t1mskc_u32, _t1mskc_u32(info[0]->Uint32Value()));

		//unsigned __int64 _t1mskc_u64(unsigned __int64)
		makeMethod_u64(target, _t1mskc_u64, _t1mskc_u64(static_cast<uint64_t>(info[0]->NumberValue())));

		//unsigned int _tzcnt_u32(unsigned int)
		makeMethodRet(target, _tzcnt_u32, _tzcnt_u32(info[0]->Uint32Value()));

		//unsigned __int64 _tzcnt_u64(unsigned __int64)
		makeMethod_u64(target, _tzcnt_u64, _tzcnt_u64(static_cast<uint64_t>(info[0]->NumberValue())));

		//unsigned int _tzmsk_u32(unsigned int)
		makeMethodRet(target, _tzmsk_u32, _tzmsk_u32(info[0]->Uint32Value()));

		//unsigned __int64 _tzmsk_u64(unsigned __int64)
		makeMethod_u64(target, _tzmsk_u64, _tzmsk_u64(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __ud2(void)
		makeMethod(target, __ud2, __ud2());

		//unsigned __int64 [pascal/cdecl] __ull_rshift(unsigned __int64,int)
		//unsigned __int64 _umul128(unsigned __int64 multiplier,unsigned __int64 multiplicand,unsigned __int64 *highproduct)
		//unsigned __int64 __umulh(unsigned __int64,unsigned __int64)
		//void __vmx_off(void)
		//unsigned char __vmx_on(unsigned __int64*)
		//unsigned char __vmx_vmclear(unsigned __int64*)
		//unsigned char __vmx_vmlaunch(void)
		//unsigned char __vmx_vmptrld(unsigned __int64*)
		//void __vmx_vmptrst(unsigned __int64 *)
		//unsigned char __vmx_vmread(size_t,size_t*)
		//unsigned char __vmx_vmresume(void)
		//unsigned char __vmx_vmwrite(size_t,size_t)

		//void __wbinvd(void)
		makeMethod(target, __wbinvd, __wbinvd());

		//void _WriteBarrier(void)
		makeMethod(target, _WriteBarrier, _WriteBarrier());

		//void __writecr0(unsigned __int64)
		makeMethod(target, __writecr0, __writecr0(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __writecr3(unsigned __int64)
		makeMethod(target, __writecr3, __writecr3(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __writecr4(unsigned __int64)
		makeMethod(target, __writecr4, __writecr4(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __writecr8(unsigned __int64)
		makeMethod(target, __writecr8, __writecr8(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __writedr(unsigned,unsigned __int64)
		makeMethod(target, __writedr, {
			switch (info[0]->Uint32Value()) {
			case 0: __writedr(0, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 1: __writedr(1, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 2: __writedr(2, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 3: __writedr(3, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 4: __writedr(4, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 5: __writedr(5, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 6: __writedr(6, static_cast<uint64_t>(info[1]->NumberValue())); return;
			case 7: __writedr(7, static_cast<uint64_t>(info[1]->NumberValue())); return;
			}
		});

		//void __writeeflags(unsigned __int64)
		makeMethod(target, __writeeflags, __writeeflags(static_cast<uint64_t>(info[0]->NumberValue())));

		//void _writefsbase_u32(unsigned int)
		makeMethod(target, _writefsbase_u32, _writefsbase_u32(info[0]->Uint32Value()));

		//void _writefsbase_u64(unsigned __int64)
		makeMethod(target, _writefsbase_u64, _writefsbase_u64(static_cast<uint64_t>(info[0]->NumberValue())));

		//void _writegsbase_u32(unsigned int)
		makeMethod(target, _writegsbase_u32, _writegsbase_u32(info[0]->Uint32Value()));

		//void _writegsbase_u64(unsigned __int64)
		makeMethod(target, _writegsbase_u64, _writegsbase_u64(static_cast<uint64_t>(info[0]->NumberValue())));

		//void __writegsbyte(unsigned long Offset,unsigned char Data)
		makeMethod(target, __writegsbyte, __writegsbyte(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __writegsdword(unsigned long Offset,unsigned long Data)
		makeMethod(target, __writegsdword, __writegsdword(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __writegsqword(unsigned long Offset,unsigned __int64 Data)
		makeMethod(target, __writegsqword, __writegsqword(info[0]->Uint32Value(), static_cast<uint64_t>(info[1]->NumberValue())));

		//void __writegsword(unsigned long Offset,unsigned short Data)
		makeMethod(target, __writegsword, __writegsword(info[0]->Uint32Value(), info[1]->Uint32Value()));

		//void __writemsr(unsigned long,unsigned __int64)
		makeMethod(target, __writemsr, __writemsr(info[0]->Uint32Value(), static_cast<uint64_t>(info[1]->NumberValue())));

		//void _xabort(unsigned int)
		makeMethod(target, _xabort, {
			switch (static_cast<uint8_t>(info[0]->Uint32Value())) {
			case 0x00: _xabort(0x00); return;
			case 0x01: _xabort(0x01); return;
			case 0x02: _xabort(0x02); return;
			case 0x03: _xabort(0x03); return;
			case 0x04: _xabort(0x04); return;
			case 0x05: _xabort(0x05); return;
			case 0x06: _xabort(0x06); return;
			case 0x07: _xabort(0x07); return;
			case 0x08: _xabort(0x08); return;
			case 0x09: _xabort(0x09); return;
			case 0x0A: _xabort(0x0A); return;
			case 0x0B: _xabort(0x0B); return;
			case 0x0C: _xabort(0x0C); return;
			case 0x0D: _xabort(0x0D); return;
			case 0x0E: _xabort(0x0E); return;
			case 0x0F: _xabort(0x0F); return;

			case 0x10: _xabort(0x10); return;
			case 0x11: _xabort(0x11); return;
			case 0x12: _xabort(0x12); return;
			case 0x13: _xabort(0x13); return;
			case 0x14: _xabort(0x14); return;
			case 0x15: _xabort(0x15); return;
			case 0x16: _xabort(0x16); return;
			case 0x17: _xabort(0x17); return;
			case 0x18: _xabort(0x18); return;
			case 0x19: _xabort(0x19); return;
			case 0x1A: _xabort(0x1A); return;
			case 0x1B: _xabort(0x1B); return;
			case 0x1C: _xabort(0x1C); return;
			case 0x1D: _xabort(0x1D); return;
			case 0x1E: _xabort(0x1E); return;
			case 0x1F: _xabort(0x1F); return;


			case 0x20: _xabort(0x20); return;
			case 0x21: _xabort(0x21); return;
			case 0x22: _xabort(0x22); return;
			case 0x23: _xabort(0x23); return;
			case 0x24: _xabort(0x24); return;
			case 0x25: _xabort(0x25); return;
			case 0x26: _xabort(0x26); return;
			case 0x27: _xabort(0x27); return;
			case 0x28: _xabort(0x28); return;
			case 0x29: _xabort(0x29); return;
			case 0x2A: _xabort(0x2A); return;
			case 0x2B: _xabort(0x2B); return;
			case 0x2C: _xabort(0x2C); return;
			case 0x2D: _xabort(0x2D); return;
			case 0x2E: _xabort(0x2E); return;
			case 0x2F: _xabort(0x2F); return;


			case 0x30: _xabort(0x30); return;
			case 0x31: _xabort(0x31); return;
			case 0x32: _xabort(0x32); return;
			case 0x33: _xabort(0x33); return;
			case 0x34: _xabort(0x34); return;
			case 0x35: _xabort(0x35); return;
			case 0x36: _xabort(0x36); return;
			case 0x37: _xabort(0x37); return;
			case 0x38: _xabort(0x38); return;
			case 0x39: _xabort(0x39); return;
			case 0x3A: _xabort(0x3A); return;
			case 0x3B: _xabort(0x3B); return;
			case 0x3C: _xabort(0x3C); return;
			case 0x3D: _xabort(0x3D); return;
			case 0x3E: _xabort(0x3E); return;
			case 0x3F: _xabort(0x3F); return;


			case 0x40: _xabort(0x40); return;
			case 0x41: _xabort(0x41); return;
			case 0x42: _xabort(0x42); return;
			case 0x43: _xabort(0x43); return;
			case 0x44: _xabort(0x44); return;
			case 0x45: _xabort(0x45); return;
			case 0x46: _xabort(0x46); return;
			case 0x47: _xabort(0x47); return;
			case 0x48: _xabort(0x48); return;
			case 0x49: _xabort(0x49); return;
			case 0x4A: _xabort(0x4A); return;
			case 0x4B: _xabort(0x4B); return;
			case 0x4C: _xabort(0x4C); return;
			case 0x4D: _xabort(0x4D); return;
			case 0x4E: _xabort(0x4E); return;
			case 0x4F: _xabort(0x4F); return;


			case 0x50: _xabort(0x50); return;
			case 0x51: _xabort(0x51); return;
			case 0x52: _xabort(0x52); return;
			case 0x53: _xabort(0x53); return;
			case 0x54: _xabort(0x54); return;
			case 0x55: _xabort(0x55); return;
			case 0x56: _xabort(0x56); return;
			case 0x57: _xabort(0x57); return;
			case 0x58: _xabort(0x58); return;
			case 0x59: _xabort(0x59); return;
			case 0x5A: _xabort(0x5A); return;
			case 0x5B: _xabort(0x5B); return;
			case 0x5C: _xabort(0x5C); return;
			case 0x5D: _xabort(0x5D); return;
			case 0x5E: _xabort(0x5E); return;
			case 0x5F: _xabort(0x5F); return;


			case 0x60: _xabort(0x60); return;
			case 0x61: _xabort(0x61); return;
			case 0x62: _xabort(0x62); return;
			case 0x63: _xabort(0x63); return;
			case 0x64: _xabort(0x64); return;
			case 0x65: _xabort(0x65); return;
			case 0x66: _xabort(0x66); return;
			case 0x67: _xabort(0x67); return;
			case 0x68: _xabort(0x68); return;
			case 0x69: _xabort(0x69); return;
			case 0x6A: _xabort(0x6A); return;
			case 0x6B: _xabort(0x6B); return;
			case 0x6C: _xabort(0x6C); return;
			case 0x6D: _xabort(0x6D); return;
			case 0x6E: _xabort(0x6E); return;
			case 0x6F: _xabort(0x6F); return;


			case 0x70: _xabort(0x70); return;
			case 0x71: _xabort(0x71); return;
			case 0x72: _xabort(0x72); return;
			case 0x73: _xabort(0x73); return;
			case 0x74: _xabort(0x74); return;
			case 0x75: _xabort(0x75); return;
			case 0x76: _xabort(0x76); return;
			case 0x77: _xabort(0x77); return;
			case 0x78: _xabort(0x78); return;
			case 0x79: _xabort(0x79); return;
			case 0x7A: _xabort(0x7A); return;
			case 0x7B: _xabort(0x7B); return;
			case 0x7C: _xabort(0x7C); return;
			case 0x7D: _xabort(0x7D); return;
			case 0x7E: _xabort(0x7E); return;
			case 0x7F: _xabort(0x7F); return;


			case 0x80: _xabort(0x80); return;
			case 0x81: _xabort(0x81); return;
			case 0x82: _xabort(0x82); return;
			case 0x83: _xabort(0x83); return;
			case 0x84: _xabort(0x84); return;
			case 0x85: _xabort(0x85); return;
			case 0x86: _xabort(0x86); return;
			case 0x87: _xabort(0x87); return;
			case 0x88: _xabort(0x88); return;
			case 0x89: _xabort(0x89); return;
			case 0x8A: _xabort(0x8A); return;
			case 0x8B: _xabort(0x8B); return;
			case 0x8C: _xabort(0x8C); return;
			case 0x8D: _xabort(0x8D); return;
			case 0x8E: _xabort(0x8E); return;
			case 0x8F: _xabort(0x8F); return;


			case 0x90: _xabort(0x90); return;
			case 0x91: _xabort(0x91); return;
			case 0x92: _xabort(0x92); return;
			case 0x93: _xabort(0x93); return;
			case 0x94: _xabort(0x94); return;
			case 0x95: _xabort(0x95); return;
			case 0x96: _xabort(0x96); return;
			case 0x97: _xabort(0x97); return;
			case 0x98: _xabort(0x98); return;
			case 0x99: _xabort(0x99); return;
			case 0x9A: _xabort(0x9A); return;
			case 0x9B: _xabort(0x9B); return;
			case 0x9C: _xabort(0x9C); return;
			case 0x9D: _xabort(0x9D); return;
			case 0x9E: _xabort(0x9E); return;
			case 0x9F: _xabort(0x9F); return;


			case 0xA0: _xabort(0xA0); return;
			case 0xA1: _xabort(0xA1); return;
			case 0xA2: _xabort(0xA2); return;
			case 0xA3: _xabort(0xA3); return;
			case 0xA4: _xabort(0xA4); return;
			case 0xA5: _xabort(0xA5); return;
			case 0xA6: _xabort(0xA6); return;
			case 0xA7: _xabort(0xA7); return;
			case 0xA8: _xabort(0xA8); return;
			case 0xA9: _xabort(0xA9); return;
			case 0xAA: _xabort(0xAA); return;
			case 0xAB: _xabort(0xAB); return;
			case 0xAC: _xabort(0xAC); return;
			case 0xAD: _xabort(0xAD); return;
			case 0xAE: _xabort(0xAE); return;
			case 0xAF: _xabort(0xAF); return;


			case 0xB0: _xabort(0xB0); return;
			case 0xB1: _xabort(0xB1); return;
			case 0xB2: _xabort(0xB2); return;
			case 0xB3: _xabort(0xB3); return;
			case 0xB4: _xabort(0xB4); return;
			case 0xB5: _xabort(0xB5); return;
			case 0xB6: _xabort(0xB6); return;
			case 0xB7: _xabort(0xB7); return;
			case 0xB8: _xabort(0xB8); return;
			case 0xB9: _xabort(0xB9); return;
			case 0xBA: _xabort(0xBA); return;
			case 0xBB: _xabort(0xBB); return;
			case 0xBC: _xabort(0xBC); return;
			case 0xBD: _xabort(0xBD); return;
			case 0xBE: _xabort(0xBE); return;
			case 0xBF: _xabort(0xBF); return;


			case 0xC0: _xabort(0xC0); return;
			case 0xC1: _xabort(0xC1); return;
			case 0xC2: _xabort(0xC2); return;
			case 0xC3: _xabort(0xC3); return;
			case 0xC4: _xabort(0xC4); return;
			case 0xC5: _xabort(0xC5); return;
			case 0xC6: _xabort(0xC6); return;
			case 0xC7: _xabort(0xC7); return;
			case 0xC8: _xabort(0xC8); return;
			case 0xC9: _xabort(0xC9); return;
			case 0xCA: _xabort(0xCA); return;
			case 0xCB: _xabort(0xCB); return;
			case 0xCC: _xabort(0xCC); return;
			case 0xCD: _xabort(0xCD); return;
			case 0xCE: _xabort(0xCE); return;
			case 0xCF: _xabort(0xCF); return;


			case 0xD0: _xabort(0xD0); return;
			case 0xD1: _xabort(0xD1); return;
			case 0xD2: _xabort(0xD2); return;
			case 0xD3: _xabort(0xD3); return;
			case 0xD4: _xabort(0xD4); return;
			case 0xD5: _xabort(0xD5); return;
			case 0xD6: _xabort(0xD6); return;
			case 0xD7: _xabort(0xD7); return;
			case 0xD8: _xabort(0xD8); return;
			case 0xD9: _xabort(0xD9); return;
			case 0xDA: _xabort(0xDA); return;
			case 0xDB: _xabort(0xDB); return;
			case 0xDC: _xabort(0xDC); return;
			case 0xDD: _xabort(0xDD); return;
			case 0xDE: _xabort(0xDE); return;
			case 0xDF: _xabort(0xDF); return;


			case 0xE0: _xabort(0xE0); return;
			case 0xE1: _xabort(0xE1); return;
			case 0xE2: _xabort(0xE2); return;
			case 0xE3: _xabort(0xE3); return;
			case 0xE4: _xabort(0xE4); return;
			case 0xE5: _xabort(0xE5); return;
			case 0xE6: _xabort(0xE6); return;
			case 0xE7: _xabort(0xE7); return;
			case 0xE8: _xabort(0xE8); return;
			case 0xE9: _xabort(0xE9); return;
			case 0xEA: _xabort(0xEA); return;
			case 0xEB: _xabort(0xEB); return;
			case 0xEC: _xabort(0xEC); return;
			case 0xED: _xabort(0xED); return;
			case 0xEE: _xabort(0xEE); return;
			case 0xEF: _xabort(0xEF); return;


			case 0xF0: _xabort(0xF0); return;
			case 0xF1: _xabort(0xF1); return;
			case 0xF2: _xabort(0xF2); return;
			case 0xF3: _xabort(0xF3); return;
			case 0xF4: _xabort(0xF4); return;
			case 0xF5: _xabort(0xF5); return;
			case 0xF6: _xabort(0xF6); return;
			case 0xF7: _xabort(0xF7); return;
			case 0xF8: _xabort(0xF8); return;
			case 0xF9: _xabort(0xF9); return;
			case 0xFA: _xabort(0xFA); return;
			case 0xFB: _xabort(0xFB); return;
			case 0xFC: _xabort(0xFC); return;
			case 0xFD: _xabort(0xFD); return;
			case 0xFE: _xabort(0xFE); return;
			case 0xFF: _xabort(0xFF); return;


				//fixme add more later, need all 256 options
			default: _xabort(0x00);
			}
		});

		//unsigned _xbegin(void)
		makeMethodRet(target, _xbegin, _xbegin());

		//makeMethod(target, _xbegin_retry, {
		setMethod(target, L"_xbegin_retry", [](const v8::FunctionCallbackInfo<v8::Value>& info) {
			v8::Isolate* isolate = v8::Isolate::GetCurrent();
			v8::HandleScope scope(isolate);

			const int32_t retryCount = info[0]->Int32Value();
			Local<Function> cb(Local<Function>::Cast(info[1]));
			auto nullValue = Null(isolate);
			std::array<Local<Value>, 1> argvInit{v8::True(isolate)};
			std::array<Local<Value>, 1> argvActual{ v8::True(isolate) };

		//Local<Value> retA =
			cb->Call(nullValue, 1, argvInit.data());
		//cb->Call(nullValue, 0, nullptr);
			argvInit[0] = v8::False(isolate);

			for (int32_t i = 0; i < retryCount; i++) {
				const auto xVal = _xbegin();

				if (0xFFFFFFFF == xVal) {
					Local<Value> ret = cb->Call(nullValue, 1, argvInit.data());
				//Local<Value> ret = cb->Call(nullValue, 1, argvActual.data());
					_xend();
					info.GetReturnValue().Set(ret);
					return;
				}
				//if (xVal == 0) {
				//
				//}
				//else {
				//printf("ret: %08x\n", xVal);
				//}
			}
		});

		//void _xend(void)
		makeMethod(target, _xend, _xend());

		//unsigned __int64 _xgetbv(unsigned int)
		//void _xrstor(void const*,unsigned __int64)
		//void _xrstor64(void const*,unsigned __int64)
		//void _xsave(void*,unsigned __int64)
		//void _xsave64(void*,unsigned __int64)
		//void _xsaveopt(void*,unsigned __int64)
		//void _xsaveopt64(void*,unsigned __int64)
		//void _xsetbv(unsigned int,unsigned __int64)

		//unsigned char _xtest(void)
		makeMethodRet(target, _xtest, _xtest());

	}

	NODE_MODULE(intrinsics, init);

};