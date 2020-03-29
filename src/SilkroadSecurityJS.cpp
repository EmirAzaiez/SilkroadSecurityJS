#include <iostream>
#include <string>
#include "SilkroadSecurityJS.h"

#include <stdio.h>
#include <napi.h>

#include <boost/foreach.hpp>

#include "SilkroadSecurity/silkroad_security.h"
#include "SilkroadSecurity/stream_utility.h"

Napi::FunctionReference SilkroadSecurityJS::constructor;

Napi::Object SilkroadSecurityJS::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "SilkroadSecurityJS",
                  {
					  InstanceMethod("GenerateHandshake", &SilkroadSecurityJS::GenerateHandshake),
            InstanceMethod("Recv", &SilkroadSecurityJS::Recv),
            InstanceMethod("GetPacketToRecv", &SilkroadSecurityJS::GetPacketToRecv),
            InstanceMethod("GetPacketToSend", &SilkroadSecurityJS::GetPacketToSend),
            InstanceMethod("Send", &SilkroadSecurityJS::Send),
            InstanceMethod("ChangeIdentity", &SilkroadSecurityJS::ChangeIdentity)

				   });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("SilkroadSecurityJS", func);
  return exports;
}

SilkroadSecurityJS::SilkroadSecurityJS(const Napi::CallbackInfo& info) : Napi::ObjectWrap<SilkroadSecurityJS>(info) {
	//INIT

	const std::string name = info[0].As<Napi::String>().Utf8Value();
	const uint8_t flag = static_cast<uint8_t>(info[1].As<Napi::Number>().Uint32Value());

	this->sec.ChangeIdentity(name, flag);

}

Napi::Value SilkroadSecurityJS::Recv(const Napi::CallbackInfo& info) {
  	
  const Napi::Array inputArray = info[0].As<Napi::Array>();

		std::vector<uint8_t> converted;

		size_t size = inputArray.Length();
		converted.resize(size);

		for(size_t x = 0; x < size; ++x) {
      
      converted[x] = static_cast<uint8_t>(inputArray[x].As<Napi::Number>().Uint32Value());
    }
  
  
	this->sec.Recv(converted);

	return Napi::Object();


}

Napi::Value SilkroadSecurityJS::GetPacketToRecv(const Napi::CallbackInfo& info) {
  	
	  Napi::Env env = info.Env();

		Napi::Array result = Napi::Array::New(env, 0);

		std::list<PacketContainer> packets = this->sec.GetPacketToRecv();

		int y = 0;


		BOOST_FOREACH(PacketContainer & container, packets)
		{
			Napi::Object processed = Napi::Object::New(env);

			processed.Set("opcode", container.opcode);
			processed.Set("encrypted", container.encrypted);
			processed.Set("massive", container.massive);

			const std::vector<uint8_t> & temp = container.data.GetStreamVector();

			Napi::Array converted = Napi::Array::New(env, 0);

			int i = 0;

			BOOST_FOREACH(const uint8_t & x, temp)
			{
				converted[i] = x;
				i++;
				// converted.append(x);
			}

			processed.Set("data", converted);
			// result.append(processed);
			result[y] = processed;
			y++;
		}

		return packets.empty() ? Napi::Object() : result;


}

Napi::Value SilkroadSecurityJS::GetPacketToSend(const Napi::CallbackInfo& info) {
  	
	  Napi::Env env = info.Env();

		Napi::Array result = Napi::Array::New(env, 0);

		std::list<std::vector<uint8_t> > packets = this->sec.GetPacketToSend();

		int y = 0;

		BOOST_FOREACH(std::vector<uint8_t> & p, packets)
		{
			Napi::Array converted = Napi::Array::New(env, 0);

			int i = 0;

			BOOST_FOREACH(const uint8_t & x, p)
			{
				converted[i] = x;
				i++;
				// converted.append(x);
			}

			// result.append(processed);
			result[y] = converted;
			y++;

		}

		return packets.empty() ? Napi::Object() : result;

}

Napi::Value SilkroadSecurityJS::Send(const Napi::CallbackInfo& info) {
  	
	  Napi::Env env = info.Env();

		const uint16_t opcode = info[0].As<Napi::Number>().Uint32Value();
		const Napi::Array data = info[1].As<Napi::Array>();
		const bool encrypted = info[2].As<Napi::Boolean>().Value();
		const bool massive = info[3].As<Napi::Boolean>().Value();

		std::vector<uint8_t> converted;
		size_t size = data.Length();
		converted.resize(size);

		for(size_t x = 0; x < size; ++x)
			converted[x] = static_cast<uint8_t>((data[x]).As<Napi::Number>().Uint32Value());

		this->sec.Send(opcode, (const uint8_t*)&converted[0], size, encrypted, massive);

		return Napi::Object();

}


Napi::Value SilkroadSecurityJS::GenerateHandshake(const Napi::CallbackInfo& info) {
  	
	const bool blowfish = info[0].As<Napi::Boolean>().Value();
	const bool security_bytes = info[1].As<Napi::Boolean>().Value();
	const bool handshake = info[2].As<Napi::Boolean>().Value();
	this->sec.GenerateHandshake(blowfish, security_bytes, handshake);

	return Napi::Object();
}

Napi::Value SilkroadSecurityJS::ChangeIdentity(const Napi::CallbackInfo& info) {
  	
	const std::string name = info[0].As<Napi::String>().Utf8Value();
	const uint8_t flag = static_cast<uint8_t>(info[1].As<Napi::Number>().Uint32Value());

  	this->sec.ChangeIdentity(name, flag);

	

	return Napi::Object();
}