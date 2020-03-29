#include <stdio.h>
#include <iostream>
#include <napi.h>

#include <boost/foreach.hpp>

#include "SilkroadSecurityJS.h"

namespace boost
{
	#ifdef BOOST_NO_EXCEPTIONS
		void throw_exception(std::exception const& e) {
			throw 11; // or whatever
		};
	#endif
}// namespace boost

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return SilkroadSecurityJS::Init(env, exports);
}


NODE_API_MODULE(addon, InitAll)