#include <nan.h>
#include "PyBlock.h"

NAN_MODULE_INIT(InitModule) {
  PyBlock::Init(target);
}

NODE_MODULE(pblock, InitModule);