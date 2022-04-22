#pragma once
#include "stb_sprintf.h"

#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#pragma comment(lib, "Ws2_32.lib")
//#include "utils/xorstr.hpp"
//#pragma comment(lib, "ntdll.lib")

//extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrThread, PBOOLEAN StatusPointer);
//extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG Unless1, ULONG Unless2, PULONG_PTR Unless3, ULONG ValidResponseOption, PULONG ResponsePointer1, PULONG_PTR Unless3, ULONG ValidResponseOption2, PULONG ResponsePointer, PULONG_PTR Unless3, ULONG ValidResponseOption, PULONG ResponsePointer);

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

namespace safety
{
	bool check_sinkhole()
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
				exit(-1);
				return false;
			}
			return true;
		}
		return false;
	}
}