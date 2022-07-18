#pragma once
#include "lazy_importer.hpp"

#include "../utils/xorstr.hpp"

#include "../utils/pattern/pattern.hpp"


typedef struct _COPY_MEMORY {
	void* bufferAddress;      // Buffer address   
	UINT_PTR	address;			// Target address
	ULONGLONG	size;				// Buffer size
	ULONG		pid;				// Target process id
	BOOLEAN		alloc;				// TRUE if alloc operation
	BOOLEAN		free;				// TRUE if free operation
	BOOLEAN		write;				// TRUE if write operation, FALSE if read
	BOOLEAN		createthread;		// TRUE if thread operation, FALSE if read
	BOOLEAN		ReqBase;			// TRUE if request base address, FALSE if not.
	ULONG64		BaseAddress;		// Base address of the game
	void* Output;
	void* ThreadStartAddr;
	void* ThreadHandleOut;
	BOOLEAN		ClearPIDCache;
	BOOLEAN		PIDCacheCleared;
	BOOLEAN		Read;
	BOOLEAN		ReadString;
	BOOLEAN		WriteString;
	const char* moduleName;
	ULONG		pid_ofSource;

	//UINT_PTR	process_id; already here 
	//PVOID		address; already here
	//SIZE_T		size;  already here

	BOOLEAN		change_protection;
	ULONG		protection;
	ULONG		protection_old;
} _CM, * PCOPY_MEMORY;

namespace driva
{
	template<typename ... Arg>
	uint64_t call_hook(const Arg ... args) {
		void* user_32 = LoadLibrary(_(L"user32.dll"));
		void* func_address = GetProcAddress(LoadLibrary(_(L"win32u.dll")),
			_("NtQueryCompositionSurfaceStatistics"));
		auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(func_address);
		return func(args ...);
	}

	bool test_driver() {
		__try {
			bool old = false;
			bool ov = true;
			_CM m = {};
			m.write = 1;
			m.address = reinterpret_cast<UINT_PTR>(&old);
			m.bufferAddress = &ov;
			m.size = sizeof(bool);
			m.pid = GetCurrentProcessId();
			call_hook(&m);
			return old;
		}
		__except (true) {
			return false;
		}
	}

	PVOID create_thread(void* func) {
		__try {
			_CM m = {};
			m.createthread = 1;
			m.pid = GetCurrentProcessId();;
			m.ThreadStartAddr = func;
			call_hook(&m);
			return m.ThreadHandleOut;
		}
		__except (true) {
			return 0;
		}
	}

	PVOID alloc(PVOID buffer, ULONGLONG size, ULONG protect) {
		__try {
			_CM m = {};
			m.alloc = 1;
			m.pid = GetCurrentProcessId();
			m.bufferAddress = buffer;
			m.size = size;
			m.protection = protect;
			call_hook(&m);
			return m.bufferAddress;
		}
		__except (true) {
			return 0;
		}
	}

	bool free(PVOID address, ULONGLONG size, ULONG type) {
		__try {
			_CM m = {};
			m.free = 1;
			m.pid = GetCurrentProcessId();
			m.address = reinterpret_cast<UINT_PTR>(address);
			m.size = size;
			m.protection = type;
			call_hook(&m);
			return true;
		}
		__except (true) {
			return false;
		}
	}

	bool protect(PVOID address, ULONGLONG size, ULONG protection, ULONG protection_old) {
		__try {
			_CM m = {};
			m.change_protection = 1;
			m.pid = GetCurrentProcessId();
			m.address = reinterpret_cast<UINT_PTR>(address);
			m.size = size;
			m.protection = protection;
			m.protection_old = protection_old;
			call_hook(&m);
			return true;
		}
		__except (true) {
			return false;
		}
	}

	ULONG64 base(const char* moduleName) {
		__try {
			_CM m = {};
			m.ReqBase = 1;
			m.pid = GetCurrentProcessId();
			m.moduleName = moduleName;
			call_hook(&m);
			return m.BaseAddress;
		}
		__except (true) {
			return false;
		}
	}

	bool write(UINT_PTR address, ULONGLONG size, void* buffer) {
		__try {
			_CM m = {};
			m.write = 1;
			m.Read = 0;
			m.pid = GetCurrentProcessId();
			m.address = address;
			m.size = size;
			m.bufferAddress = buffer;
			call_hook(&m);
			return true;
		}
		__except (true) {
			return false;
		}
	}

	bool read(UINT_PTR address, void* buffer, ULONGLONG size) {
		__try {
			_CM m = {};
			m.Read = 1;
			m.write = 0;
			m.pid = GetCurrentProcessId();
			m.address = address;
			m.size = size;
			m.Output = buffer;
			call_hook(&m);
			return true;
		}
		__except (true) {
			return false;
		}
	}

	bool clearpid() {
		__try {
			_CM m = {};
			m.ClearPIDCache = 1;
			call_hook(&m);
			return m.PIDCacheCleared;
		}
		__except (true) {
			return false;
		}
	}

	bool readstring(UINT_PTR address, ULONGLONG size, char* buffer) {
		__try {
			_CM m = {};
			m.ReadString = 1;
			m.pid = GetCurrentProcessId();
			m.address = address;
			m.size = size;
			call_hook(&m);
			strcpy(buffer, reinterpret_cast<const char*>(m.bufferAddress));
			return true;
		}
		__except (true) {
			return false;
		}
	}

	bool writestring(UINT_PTR address, ULONGLONG size, void* buffer) {
		__try {
			_CM m = {};
			m.WriteString = 1;
			m.pid = GetCurrentProcessId();
			m.address = address;
			m.size = size;
			m.bufferAddress = buffer;
			call_hook(&m);
			return true;
		}
		__except (true) {
			return false;
		}
	}
}

namespace mem {
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		return true;
	}
	uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space);
}