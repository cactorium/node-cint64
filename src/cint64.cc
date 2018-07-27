#include <node.h>

#include "int64-type.h"

using namespace v8;

extern "C" {
    static void Init(Handle<Object> exports, Handle<Object> module) {
        Int64Wrapper::Init(exports);
    }
}

NODE_MODULE(cint64, Init);
