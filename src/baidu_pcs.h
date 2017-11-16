#ifndef SRC_BAIDU_PCS_H
#define SRC_BAIDU_PCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nan.h>
#include <string>
#include "../BaiduPCS/pcs/pcs.h"


using namespace v8;


class BaiDuPCS : public Nan::ObjectWrap {
 public:
  static void Init(Local<Object> exports, Local<Object> module);

 private:
  explicit BaiDuPCS(double value = 0);
  ~BaiDuPCS();

  static void New(const Nan::FunctionCallbackInfo<Value>& info);
  static void clearErrorMSg(const Nan::FunctionCallbackInfo<Value>& info);
  static void setErrorMSg(const Nan::FunctionCallbackInfo<Value>& info);
  static void appendErrorMSg(const Nan::FunctionCallbackInfo<Value>& info);
  static void getVersion(const Nan::FunctionCallbackInfo<Value>& info);
  static void createPcsHandle(const Nan::FunctionCallbackInfo<Value>& info);
  static void destroyPcsHandle(const Nan::FunctionCallbackInfo<Value>& info);
  static void userUID(const Nan::FunctionCallbackInfo<Value>& info);
  static Nan::Persistent<Function> constructor;
  double value_;
  Pcs pcsHandle;
};


#endif // SRC_BAIDU_PCS_H