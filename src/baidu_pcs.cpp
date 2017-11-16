#include "./baidu_pcs.h"

const char* ToCString(Local<Value> str) {
  String::Utf8Value value(str);
  return *value ? *value : "<string conversion failed>";
}

Nan::Persistent<Function> BaiDuPCS::constructor;

BaiDuPCS::BaiDuPCS(double value) :
  value_(value),
  pcsHandle(NULL) {
}

BaiDuPCS::~BaiDuPCS() {
}

void BaiDuPCS::Init(Local<Object> exports, Local<Object> module) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("BaiDuPCS").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "getVersion", getVersion);
  Nan::SetPrototypeMethod(tpl, "clearError", clearErrorMSg);
  Nan::SetPrototypeMethod(tpl, "setError", setErrorMSg);
  Nan::SetPrototypeMethod(tpl, "appendError", appendErrorMSg);
  Nan::SetPrototypeMethod(tpl, "createPcsHandle", createPcsHandle);
  Nan::SetPrototypeMethod(tpl, "destroyPcsHandle", destroyPcsHandle);
  Nan::SetPrototypeMethod(tpl, "multiply", Multiply);

  constructor.Reset(tpl->GetFunction());
  module->Set(Nan::New("exports").ToLocalChecked(),  tpl->GetFunction());
}

void BaiDuPCS::New(const Nan::FunctionCallbackInfo<Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new BaiDuPCS(...)`
    double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    BaiDuPCS* obj = new BaiDuPCS(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `BaiDuPCS(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { info[0] };
    Local<Function> cons = Nan::New<Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void BaiDuPCS::clearErrorMSg(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(obj->pcsHandle){
    pcs_clear_errmsg(obj->pcsHandle);
    info.GetReturnValue().Set(Nan::New(true));
  } else {
    Nan::ThrowReferenceError("未初始化, 请先调用 pcs_create");
  }
}

void BaiDuPCS::setErrorMSg(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(obj->pcsHandle){
    pcs_set_serrmsg(obj->pcsHandle, ToCString(info[0]));
    info.GetReturnValue().Set(Nan::New(true));
  } else {
    Nan::ThrowReferenceError("未初始化, 请先调用 pcs_create");
  }
}


void BaiDuPCS::appendErrorMSg(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(obj->pcsHandle){
    pcs_cat_serrmsg(obj->pcsHandle, ToCString(info[0]));
    info.GetReturnValue().Set(Nan::New(true));
  } else {
    Nan::ThrowReferenceError("未初始化, 请先调用 pcs_create");
  }
}


void BaiDuPCS::createPcsHandle(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(!obj->pcsHandle){
    Pcs handle = pcs_create(ToCString(info[0]));
    if (handle) {
        obj->pcsHandle = handle;
    } else {
        Nan::ThrowReferenceError("创建pcs handle失败，请检查cookice是否有效");
    }
    info.GetReturnValue().Set(Nan::New(true));
  } else {
    Nan::ThrowReferenceError("请勿重复调用");
  }
}

void BaiDuPCS::destroyPcsHandle(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(obj->pcsHandle){
    pcs_destroy(obj->pcsHandle);
    obj->pcsHandle=NULL;
    info.GetReturnValue().Set(Nan::New(true));
  } else {
    Nan::ThrowReferenceError("未初始化, 请先调用 pcs_create");
  }
}


void BaiDuPCS::getVersion(const Nan::FunctionCallbackInfo<Value>& info) {
  info.GetReturnValue().Set(Nan::New(pcs_version()).ToLocalChecked());
}


void BaiDuPCS::userUID(const Nan::FunctionCallbackInfo<Value>& info) {
  BaiDuPCS* obj = ObjectWrap::Unwrap<BaiDuPCS>(info.Holder());
  if(obj->pcsHandle){
    info.GetReturnValue().Set(Nan::New(pcs_sysUID(obj-<pcsHandle)).ToLocalChecked());
  } else {
    Nan::ThrowReferenceError("未初始化, 请先调用 pcs_create");
  }
}

NODE_MODULE(baidupcs, BaiDuPCS::Init)