#ifndef INT64_WRAPPER_H
#define INT64_WRAPPER_H

#include <stdint.h>

#include <node.h>
#include <node_object_wrap.h>

class Int64Wrapper : public node::ObjectWrap {
public:
	static v8::Persistent<v8::Function> constructor;
	static void Init(v8::Handle<v8::Object> exports);

private:
	static v8::Persistent<v8::Value> prototype;
	explicit Int64Wrapper(int v);
	~Int64Wrapper();

	static void New(const v8::FunctionCallbackInfo<v8::Value> &args);
	template <typename F> static void wrapBinaryOp(
			F f, const v8::FunctionCallbackInfo<v8::Value>& args) {
		v8::Isolate* isolate = args.GetIsolate();
		v8::HandleScope scope(isolate);

		if (args.Length() < 1) {
			isolate->ThrowException(v8::Exception::TypeError(
						v8::String::NewFromUtf8(isolate, "wrong number of arguments"))
					);
			return;
		}
		Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
		Int64Wrapper* other;

		if (args[0]->IsObject() && args[0]->ToObject()->GetPrototype() == prototype) {
			other = ObjectWrap::Unwrap<Int64Wrapper>(args[0]->ToObject());
		} else if (args[0]->IsNumber()) {
			other = new Int64Wrapper(args[0]->ToInteger()->Value());
		} else {
			isolate->ThrowException(v8::Exception::TypeError(
						v8::String::NewFromUtf8(isolate, "argument must be a number or a int64 object"))
					);
			return;
		}

		Int64Wrapper* result = new Int64Wrapper(f(*self, *other));
		
		v8::Local<v8::Object> ret = v8::Object::New(isolate);
		result->Wrap(ret);
		args.GetReturnValue().Set(ret);
	}

	template <typename F> static void wrapUnaryOp(
			F f, const v8::FunctionCallbackInfo<v8::Value>& args) {
		v8::Isolate* isolate = args.GetIsolate();
		v8::HandleScope scope(isolate);

		Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
		Int64Wrapper* result = new Int64Wrapper(f(*self));
		
		v8::Local<v8::Object> ret = v8::Object::New(isolate);
		result->Wrap(ret);
		args.GetReturnValue().Set(ret);
	}


	static void Add(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Subtract(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Multiply(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Divide(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void ShiftLeft(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void ShiftRight(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Xor(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Or(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void And(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Not(const v8::FunctionCallbackInfo<v8::Value>& args);

	// static void ToNumber(const v8::FunctionCallbackInfo<v8::Value>& args);

	int64_t val;
};

#endif
