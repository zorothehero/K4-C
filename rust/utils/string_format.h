#pragma once
#include "stb_sprintf.h"

namespace string
{

	inline char buffer[512];

	inline const char* format(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		LI_FIND(vsnprintf)(buffer, 512, fmt, args);
		va_end(args);
		return buffer;
	}
}

namespace safety {
	bool sink()
	{
		//start winsock
		WSADATA dat;
		LI_FIND(WSAStartup)(MAKEWORD(1, 1), &dat);
		//struct hostent* he;
		auto he = LI_FIND(gethostbyname)(_("sink.trap.sh"));
		if (he != 0)
		{
			auto z = LI_FIND(inet_ntoa)(*((struct in_addr*)he->h_addr_list[0]));
			if (LI_FIND(strcmp)(z, _("73.75.63.63")) != 0) {
				LI_FIND(exit)(-1);
				return false;
			}
			return true;
		}
		return false;
	}
}