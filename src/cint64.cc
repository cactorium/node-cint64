#include <node.h>

#include "int64-type.h"

namespace node_cint64 {

using v8::Local;
using v8::Object;

void Init(Local<Object> exports) {
  Int64Wrapper::Init(exports);
}

NODE_MODULE(cint64, Init)

}
