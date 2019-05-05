#ifndef INT64_WRAPPER_H
#define INT64_WRAPPER_H

#include <stdint.h>

#include <node.h>
#include <node_object_wrap.h>

namespace node_cint64 {

class Int64Wrapper : public node::ObjectWrap {
public:
    static v8::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object> exports);

private:
    static v8::Persistent<v8::Value> prototype;
    explicit Int64Wrapper(int64_t v);
    ~Int64Wrapper();

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

    template <typename F> static void wrapBinaryOp(
            F f, const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        if (args.Length() < 1) {
          v8::MaybeLocal<v8::String> maybe_string = v8::String::NewFromUtf8(
              isolate,
              "wrong number of arguments",
              v8::NewStringType::kNormal);
            isolate->ThrowException(v8::Exception::TypeError(maybe_string.ToLocalChecked()));
            return;
        }
        const Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
        const Int64Wrapper* other = nullptr;
        bool isAllocated = false;

        auto context = isolate->GetCurrentContext();

        auto throw_exception = [&]() {
          v8::MaybeLocal<v8::String> maybe_string = v8::String::NewFromUtf8(
              isolate,
              "argument must be a number or a int64 object",
              v8::NewStringType::kNormal);
            isolate->ThrowException(v8::Exception::TypeError(maybe_string.ToLocalChecked()));
        };

        if (args[0]->IsObject()) {
            auto maybe_other = args[0]->ToObject(context);
            v8::Local<v8::Object> local_other;
            if (maybe_other.ToLocal(&local_other) && local_other->GetPrototype() == prototype) {
              other = ObjectWrap::Unwrap<Int64Wrapper>(local_other);
            } else {
              throw_exception();
              return;
            }
        } else if (args[0]->IsNumber()) {
            auto maybe_other = args[0]->ToInteger(context);
            v8::Local<v8::Integer> local_other;
            if (maybe_other.ToLocal(&local_other)) {
              other = new Int64Wrapper(local_other->Value());
              isAllocated = true;
            } else {
              throw_exception();
              return;
            }
        } else {
            throw_exception();
            return;
        }

        const int64_t result = f(*self, *other);
        if (isAllocated) {
          delete other;
        }
        
        constexpr unsigned argc = 1;
        v8::Local<v8::Value> argv[argc] = { v8::Number::New(isolate, 0) };

        auto cons = v8::Local<v8::Function>::New(isolate, constructor);
        auto ret = cons->NewInstance(context, argc, argv).ToLocalChecked();

        Int64Wrapper* retInner = ObjectWrap::Unwrap<Int64Wrapper>(ret);
        retInner->val = result;
        args.GetReturnValue().Set(ret);
    }

    template <typename F> static void wrapUnaryOp(
            F f, const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        const Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
        const int64_t result = f(*self);
        
        constexpr unsigned argc = 1;
        v8::Local<v8::Value> argv[argc] = { v8::Number::New(isolate, 0) };

        auto cons = v8::Local<v8::Function>::New(isolate, constructor);
        auto context = isolate->GetCurrentContext();
        auto ret = cons->NewInstance(context, argc, argv).ToLocalChecked();

        Int64Wrapper* retInner = ObjectWrap::Unwrap<Int64Wrapper>(ret);
        retInner->val = result;
        args.GetReturnValue().Set(ret);
    }

    template <typename F> static void wrapBoolOp(
            F f, const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);
        auto context = isolate->GetCurrentContext();

        const Int64Wrapper* self = ObjectWrap::Unwrap<Int64Wrapper>(args.Holder());
        const Int64Wrapper* other;
        bool isAllocated = false;

        auto throw_exception = [&]() {
          v8::MaybeLocal<v8::String> maybe_string = v8::String::NewFromUtf8(
              isolate,
              "argument must be a number or a int64 object",
              v8::NewStringType::kNormal);
            isolate->ThrowException(v8::Exception::TypeError(maybe_string.ToLocalChecked()));
        };

        if (args[0]->IsObject()) {
            auto maybe_other = args[0]->ToObject(context);

            v8::Local<v8::Object> local_other;
            if (maybe_other.ToLocal(&local_other) && local_other->GetPrototype() == prototype) {
              other = ObjectWrap::Unwrap<Int64Wrapper>(local_other);
            } else {
              throw_exception();
              return;
            }
        } else if (args[0]->IsNumber()) {
            auto maybe_other = args[0]->ToInteger(context);

            v8::Local<v8::Integer> local_other;
            if (maybe_other.ToLocal(&local_other)) {
              other = new Int64Wrapper(local_other->Value());
              isAllocated = true;
            } else {
              throw_exception();
              return;
            }
        } else {
            throw_exception();
            return;
        }

        const bool result = f(*self, *other);
        if (isAllocated) {
          delete other;
        }
        args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
    }

    static void Add(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Subtract(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Multiply(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Divide(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Modulo(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ShiftLeft(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ShiftRight(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Xor(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Or(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void And(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void Not(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Abs(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Negate(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void GreaterThan(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void GreaterOrEqual(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void LessThan(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void LessOrEqual(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Equals(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void NotEquals(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void ToNumber(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ToString(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void IntoBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);

    int64_t val;
};

}

#endif
