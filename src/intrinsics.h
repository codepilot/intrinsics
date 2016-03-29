#pragma once

#include <windows.h>
#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_buffer.h>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <safeint.h>

namespace {
	using v8::Eternal;
	using v8::Function;
	using v8::FunctionCallback;
	using v8::FunctionCallbackInfo;
	using v8::FunctionTemplate;
	using v8::Handle;
	using v8::HandleScope;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using std::array;
	using std::wstring;
	using msl::utilities::SafeInt;

	Eternal<String> es_EternalWrapper;

	template<class T>
	void setMethod(Handle<Object>& classObj, wstring&& funcName, const T&& callback) {
		Isolate* isolate = Isolate::GetCurrent(); HandleScope scope(isolate);
		auto funcTemplate = FunctionTemplate::New(isolate, static_cast<FunctionCallback>(callback));
		Eternal<String> es_temp;//keep string forever
		es_temp.Set(isolate, String::NewFromTwoByte(isolate, reinterpret_cast<const uint16_t *>(funcName.data()), String::kInternalizedString, SafeInt<int>(funcName.size())));
		funcTemplate->SetClassName(es_temp.Get(isolate));
		auto func = funcTemplate->GetFunction();
		func->SetName(es_temp.Get(isolate));
		classObj->Set(es_temp.Get(isolate), func);
	}

	template<typename T = Function>
	class EternalV2 {
	private:
		Isolate *isolate{ nullptr };
	public:
		Eternal<T> funcCB;
		EternalV2() { }

		EternalV2(Handle<T> localFuncCB) :isolate{ Isolate::GetCurrent() }, funcCB{ isolate , localFuncCB } { }

		Local<Value> Call(Local<Value> recv, int argc, Local<Value> argv[]) {
			return funcCB.Get(isolate)->Call(recv, argc, argv);
		}

	};

	class class_EternalWrapper: public node::ObjectWrap {
	public:
		volatile char *lockPtr;
		EternalV2<Function> funcCB;

		static void Init(Handle<Object> target) {
			Isolate* isolate = target->GetIsolate();
			HandleScope scope(isolate);

			es_EternalWrapper.Set(isolate, String::NewFromUtf8(isolate, "EternalWrapper", String::kInternalizedString));

			Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
			tpl->SetClassName(es_EternalWrapper.Get(isolate));
			tpl->InstanceTemplate()->SetInternalFieldCount(1);

			NODE_SET_PROTOTYPE_METHOD(tpl, "xbegin", xbegin);

			target->Set(es_EternalWrapper.Get(isolate), tpl->GetFunction());
		}

		class_EternalWrapper(volatile char *_lockPtr, Handle<Function> localFuncCB) : lockPtr{ _lockPtr }, funcCB { localFuncCB } {
			Isolate* isolate = Isolate::GetCurrent();
			HandleScope scope(isolate);

			auto nullValue = Null(isolate);
			std::array<Local<Value>, 1> argvInit{ v8::True(isolate) };
			funcCB.Call(nullValue, 1, argvInit.data());
		}

		static void xbegin(const FunctionCallbackInfo<Value>& info) {
#if 0
			Isolate* isolate = Isolate::GetCurrent();
			HandleScope scope(isolate);

			array<Local<Value>, 1> argv{ v8::True(isolate) };
			node::ObjectWrap::Unwrap<class_EternalWrapper>(info.This())->funcCB.Call(Null(isolate), SafeInt<int>(argv.size()), argv.data());
#else



			v8::Isolate* isolate = v8::Isolate::GetCurrent();
			v8::HandleScope scope(isolate);

			const int32_t retryCount = info[0]->Int32Value();
		//Local<Function> cb(Local<Function>::Cast(info[1]));
			auto nullValue = Null(isolate);
			std::array<Local<Value>, 1> argvInit{ v8::True(isolate) };
			std::array<Local<Value>, 1> argvActual{ v8::True(isolate) };

			//Local<Value> retA =
		//cb->Call(nullValue, 1, argvInit.data());
			class_EternalWrapper *that = node::ObjectWrap::Unwrap<class_EternalWrapper>(info.This());

			//cb->Call(nullValue, 0, nullptr);
			argvInit[0] = v8::False(isolate);
			auto localCB = that->funcCB.funcCB.Get(isolate);

			*that->lockPtr = 0;
			localCB->Call(nullValue, 0, nullptr);
			*that->lockPtr = 1;
			for (int32_t i = 0; i < retryCount; i++) {
				const auto xVal = _xbegin();
				if (0xFFFFFFFF == xVal) {
					localCB->Call(nullValue, 0, nullptr);
					//Local<Value> ret = cb->Call(nullValue, 1, argvInit.data());
					//Local<Value> ret = cb->Call(nullValue, 1, argvActual.data());
					_xend();
					//info.GetReturnValue().Set(ret);

					return;
				}
				else {
					localCB->Call(nullValue, 0, nullptr);
				}
				//if (xVal == 0) {
				//
				//}
				//else {
				//printf("ret: %08x\n", xVal);
				//}
			}

#endif
		}

		static void New(const FunctionCallbackInfo<Value>& info) {
			if (!info.IsConstructCall()) {
				return;
			}
			Isolate* isolate = info.GetIsolate();
			if (info.Length() == 2 && node::Buffer::HasInstance(info[0]) && info[1]->IsFunction()) {
				auto obj = new class_EternalWrapper(node::Buffer::Data(info[0]), Handle<Function>::Cast(info[1]));
				obj->Wrap(info.This());
				info.GetReturnValue().Set(info.This());
			}
		}
	};

};