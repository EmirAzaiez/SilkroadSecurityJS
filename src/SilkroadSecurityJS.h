#include <napi.h>

#include "SilkroadSecurity/silkroad_security.h"
#include "SilkroadSecurity/stream_utility.h"

class SilkroadSecurityJS : public Napi::ObjectWrap<SilkroadSecurityJS> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  SilkroadSecurityJS(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;

  Napi::Value GenerateHandshake(const Napi::CallbackInfo& info);
  Napi::Value Recv(const Napi::CallbackInfo& info);
  Napi::Value GetPacketToRecv(const Napi::CallbackInfo& info);
  Napi::Value GetPacketToSend(const Napi::CallbackInfo& info);
  Napi::Value Send(const Napi::CallbackInfo& info);
  Napi::Value ChangeIdentity(const Napi::CallbackInfo& info);




  SilkroadSecurity sec;
};
