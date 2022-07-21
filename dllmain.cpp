#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024
#include <intrin.h>
#include <cstdint>
#include <dxgi.h>
#include <time.h>
#include <cstdio>
#include <iostream>
#include <filesystem>
#include <KnownFolders.h>

#include "rust/rust.hpp"

#include "projectile.hpp"

#include "memory/memory.hpp"
#include "memory/lazy_importer.hpp"
#include "memory/il2cpp.hpp"

#include "utils/no_crt.hpp"
#include "utils/xorstr.hpp"
#include "utils/pattern/pattern.hpp"

#include "gui/OnGUI.hpp"

#include "assets/assets.hpp"

#include "rust/unity.hpp"
#include "rust/features/player_esp.hpp"

#include "hooks.hpp"

bool has_initialized = false;

extern DWORD D3DThread();



bool DllMain(HMODULE hmodule)
{
	if (!has_initialized) {
        //if (driva::test_driver())
        //{
        //    CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)D3DThread, 0, 0, 0));
        //    //HANDLE h = driva::create_thread(&D3DThread);
        //}
		//CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)D3DThread, 0, 0, 0));
        //add auth pls omg
		if (safety::check_sinkhole())
		//if (true)
		{
			mem::game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
			mem::unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));

			//mem::try_pattern(_("53 C3"));

			il2cpp::init();

			unity::init_unity();	
			gui::init_gui();
			hooks::init_hooks();

			init_bp();

			init_projectile();
            
            typedef rust::list<uintptr_t>* (*AAA)();//real rust 36204160 ALKAD 36223520 "Name": "ConsoleSystem.Index$$get_All",
            rust::list<uintptr_t>* command_list = ((AAA)(mem::game_assembly_base + 36223520))();

            if (command_list) {
                auto sz = *reinterpret_cast<int*>(command_list + 0x18);
                for (size_t i = 0; i < sz; i++)
                { 
                    auto cmd = *reinterpret_cast<uintptr_t*>(command_list + 0x20 + i * 0x8);
                    if (!cmd) continue;
                    auto name = (rust::classes::string*)*reinterpret_cast<uintptr_t*>((uintptr_t)cmd + 0x10);
                    if (!LI_FIND(wcscmp)(name->str, _(L"noclip")) ||
                        !LI_FIND(wcscmp)(name->str, _(L"debugcamera")) ||
                        !LI_FIND(wcscmp)(name->str, _(L"debug.debugcamera")) ||
                        !LI_FIND(wcscmp)(name->str, _(L"camspeed")) ||
                        !LI_FIND(wcscmp)(name->str, _(L"camlerp")))
                    {
                        bool r = false;
                        mem::write<bool>((uintptr_t)cmd + 0x58, r);
                    }
                }
            }

			has_initialized = true;
		}
	}
    il2cpp::hook(&hooks::hk_performance_update, _("Update"), _("PerformanceUI"), _("Facepunch"), 0);
    il2cpp::hook(&gui::OnGUI, _("OnGUI"), _("DevControls"), _(""), 0);
    mem::hook_virtual_function(_("BasePlayer"), _("ClientInput"), &hooks::hk_baseplayer_ClientInput);
    mem::hook_virtual_function(_("BaseProjectile"), _("LaunchProjectile"), &hooks::hk_LaunchProjectile);
    

	//il2cpp::hook(&hooks::hk_DoHit, _("DoHit"), _("Projectile"), _(""), 3);

	return true;
}
extern "C" __declspec(dllexport) int ACEShowBalloonVariadic(int code, WPARAM wParam, LPARAM lParam) {
	return LI_FIND(CallNextHookEx)(NULL, code, wParam, lParam);
}