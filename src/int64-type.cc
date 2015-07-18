#include "int64-type.h"

using namespace v8;

Persistent<Function> Int64Wrapper::constructor;
v8::Persistent<v8::Value> Int64Wrapper::prototype;

void Int64Wrapper::Init(Handle<Object> exports) {
	// FIXME: GetCurrent() may be deprecated soonish
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, Int64Wrapper::New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "Int64"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// add methods here
	NODE_SET_PROTOTYPE_METHOD(tpl, "add", Int64Wrapper::Add);
	NODE_SET_PROTOTYPE_METHOD(tpl, "sub", Int64Wrapper::Subtract);
	NODE_SET_PROTOTYPE_METHOD(tpl, "mul", Int64Wrapper::Multiply);
	NODE_SET_PROTOTYPE_METHOD(tpl, "div", Int64Wrapper::Divide);
	NODE_SET_PROTOTYPE_METHOD(tpl, "shiftLeft", Int64Wrapper::ShiftLeft);
	NODE_SET_PROTOTYPE_METHOD(tpl, "shiftRight", Int64Wrapper::ShiftRight);
	NODE_SET_PROTOTYPE_METHOD(tpl, "xor", Int64Wrapper::Xor);
	NODE_SET_PROTOTYPE_METHOD(tpl, "or", Int64Wrapper::Or);
	NODE_SET_PROTOTYPE_METHOD(tpl, "and", Int64Wrapper::And);
	NODE_SET_PROTOTYPE_METHOD(tpl, "not", Int64Wrapper::Not);
	NODE_SET_PROTOTYPE_METHOD(tpl, "toNumber", Int64Wrapper::ToNumber);

	// set the constructor so we can use it
	constructor.Reset(isolate, tpl->GetFunction());

	// set the prototype so it can be used for typechecking
	Local<Object> obj = tpl->GetFunction()->NewInstance();
	prototype.Reset(isolate, obj->GetPrototype());

	exports->Set(String::NewFromUtf8(isolate, "Int64"), tpl->GetFunction());
}

Int64Wrapper::Int64Wrapper(int v) : val(v) {}
Int64Wrapper::~Int64Wrapper() {}

void Int64Wrapper::New(const FunctionCallbackInfo<Value> &args) {
	Isolate* isolate = args.GetIsolate();
	HandleScope scope(isolate);

	if (!args.IsConstructCall()) {
		isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate,
					"Use the new operator to create instances of this object."))
			);
		return;
	}

	uint64_t val = 0;
	if (args.Length() > 0) {
		val = args[0]->IsUndefined()? 0 : args[0]->NumberValue();
	}

	Int64Wrapper* obj = new Int64Wrapper(val);
	obj->Wrap(args.This());

	args.GetReturnValue().Set(args.This());
}

void Int64Wrapper::Add(const FunctionCallbackInfo<Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val + other.val;
	}, args);
}
void Int64Wrapper::Subtract(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val - other.val;
	}, args);
}
void Int64Wrapper::Multiply(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val * other.val;
	}, args);
}
void Int64Wrapper::Divide(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val / other.val;
	}, args);
}
void Int64Wrapper::ShiftLeft(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val << other.val;
	}, args);
}
void Int64Wrapper::ShiftRight(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val >> other.val;
	}, args);
}
void Int64Wrapper::Xor(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val ^ other.val;
	}, args);
}
void Int64Wrapper::Or(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val | other.val;
	}, args);
}
void Int64Wrapper::And(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapBinaryOp([](const Int64Wrapper& self, const Int64Wrapper& other) -> uint64_t {
		return self.val & other.val;
	}, args);
}

void Int64Wrapper::Not(const v8::FunctionCallbackInfo<v8::Value>& args) {
	wrapUnaryOp([](const Int64Wrapper& self) -> uint64_t {
		return !self.val;
	}, args);
}

void Int64Wrapper::ToNumber(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	HandleScope scope(isolate);

	Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
	args.GetReturnValue().Set(Number::New(isolate, (double) self->val));
}
