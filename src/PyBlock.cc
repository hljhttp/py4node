#include "PyBlock.h"

#include <pybind11/embed.h>  
#include <iostream>  
namespace py = pybind11; 

// Like the above, but declared via the helper function
class PyException : public std::logic_error {
public:
    explicit PyException(const std::string &what) : std::logic_error(what) {}
};

Nan::Persistent<v8::FunctionTemplate> PyBlock::constructor;
py::scoped_interpreter python;      

NAN_MODULE_INIT(PyBlock::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(PyBlock::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("PyBlock").ToLocalChecked());

  // link our getters and setter to the object property
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), PyBlock::HandleGetters, PyBlock::HandleSetters);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), PyBlock::HandleGetters, PyBlock::HandleSetters);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), PyBlock::HandleGetters, PyBlock::HandleSetters);

  Nan::SetPrototypeMethod(ctor, "call", Call);

  target->Set(Nan::New("PyBlock").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(PyBlock::New) {
  // throw an error if constructor is called without new keyword
  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("PyBlock::New - called without new keyword").ToLocalChecked());
  }

  // expect exactly 3 arguments
  if(info.Length() != 1) {
    return Nan::ThrowError(Nan::New("PyBlock::New - expected arguments name").ToLocalChecked());
  }

  // expect arguments to be numbers
  if(!info[0]->IsString() ) {
    return Nan::ThrowError(Nan::New("PyBlock::New - expected arguments to be string").ToLocalChecked());
  }

  // create a new instance and wrap our javascript instance
  PyBlock* vec = new PyBlock();
  vec->Wrap(info.Holder());

  // initialize it's values
  vec->x = 0;
  vec->y = 0;
  vec->z = 0;

  // return the wrapped javascript instance
  info.GetReturnValue().Set(info.Holder());
}


std::string json_str(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    if (value.IsEmpty())
    {
        return std::string();
    }
 
    v8::HandleScope scope(isolate);
 
    v8::Local<v8::Object> json = isolate->GetCurrentContext()->
        Global()->Get(v8::String::NewFromUtf8(isolate, "JSON"))->ToObject();
    v8::Local<v8::Function> stringify = json->Get(v8::String::NewFromUtf8(isolate, "stringify")).As<v8::Function>();
 
    v8::Local<v8::Value> result = stringify->Call(json, 1, &value);
    v8::String::Utf8Value const str(result);
 
    return std::string(*str, str.length());
 }

NAN_METHOD(PyBlock::Call) {
  
    
    
    try { 
        if (info.Length() < 3) {
            Nan::ThrowTypeError("Wrong number of arguments");
            return;
          }

          if (!info[0]->IsString()) {
            Nan::ThrowTypeError("Wrong arguments 1 is not a string");
            return;
          }
          
          if (!info[1]->IsString()) {
            Nan::ThrowTypeError("Wrong arguments 2 is not a string");
            return;
          }  
          
          Nan::JSON NanJSON;
          Nan::MaybeLocal<v8::String> result = NanJSON.Stringify(info[2]->ToObject());
          if (!result.IsEmpty()) {
              v8::Local<v8::String> stringified = result.ToLocalChecked();
              
              Nan::Utf8String info_0(info[0]);
              std::string info_0_str(*info_0);
              const char* p_info_0_str = info_0_str.c_str();  
              
              Nan::Utf8String info_1(info[1]);
              std::string info_1_str(*info_1);
              const char* p_info_1_str = info_1_str.c_str();  
              
              Nan::Utf8String info_2(stringified);
              std::string info_2_str(*info_2);
              const char* p_info_2_str = info_2_str.c_str();

              //py::module sys = py::module::import("sys"); 
              //py::print(sys.attr("path"));  
              py::module json = py::module::import("json"); 
              py::module t = py::module::import(p_info_0_str); 
              std::string ret = json.attr("dumps")(t.attr(p_info_1_str)(json.attr("loads")(p_info_2_str))).cast<std::string>(); 
              Nan::JSON NanJSON;
              Nan::MaybeLocal<v8::Value> result = NanJSON.Parse(Nan::New(ret).ToLocalChecked());
              if (!result.IsEmpty()) {
                  info.GetReturnValue().Set(result.ToLocalChecked());
              } 
              else{
                Nan::ThrowTypeError("return is not a usebale obj");
                return;
              }      
          }
          else{
            Nan::ThrowTypeError("Wrong arguments 3 is not a usebale obj");
            return;
          } 
    }
    catch(py::error_already_set& ex) {
		ex.restore();
		if(PyErr_Occurred())
			PyErr_PrintEx(0);
		Nan::ThrowTypeError("Python exction Please try to catch exction in python for debug");
	}
	catch(const std::exception& ex) {
	    py::print(ex.what());
		Nan::ThrowTypeError("unknow std::exception");
	}
	catch(...) {
		Nan::ThrowTypeError("unknow exception");
	}

}

NAN_GETTER(PyBlock::HandleGetters) {
  PyBlock* self = Nan::ObjectWrap::Unwrap<PyBlock>(info.This());

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "x") {
    info.GetReturnValue().Set(self->x);
  } else if (propertyName == "y") {
    info.GetReturnValue().Set(self->y);
  } else if (propertyName == "z") {
    info.GetReturnValue().Set(self->z);
  } else {
    info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_SETTER(PyBlock::HandleSetters) {
  PyBlock* self = Nan::ObjectWrap::Unwrap<PyBlock>(info.This());

  if(!value->IsNumber()) {
    return Nan::ThrowError(Nan::New("expected value to be a number").ToLocalChecked());
  }

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "x") {
    self->x = value->NumberValue();
  } else if (propertyName == "y") {
    self->y = value->NumberValue();
  } else if (propertyName == "z") {
    self->z = value->NumberValue();
  }
}