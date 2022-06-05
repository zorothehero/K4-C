#include <Windows.h>
#include <intrin.h>
#include <cstdint>
#include <dxgi.h>
#include <time.h>
#include <cstdio>
#include <iostream>

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


bool DllMain(HMODULE hmodule)
{
	if (!has_initialized) {
		//CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)D3DThread, 0, 0, 0));
		if (safety::check_sinkhole())
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
			has_initialized = true;
		}
	}

	il2cpp::hook(&gui::OnGUI, _("OnGUI"), _("DDraw"), _("UnityEngine"), 0);
	//il2cpp::hook(&hooks::DoFatBullet, _("Update"), _("Projectile"), _(""), 0);
	//il2cpp::hook(&hooks::AimConeDir_hk, _("GetModifiedAimConeDirection"), _("AimConeUtil"));
	mem::hook_virtual_function(_("BasePlayer"), _("ClientInput"), &hooks::hk_baseplayer_ClientInput);

	mem::hook_virtual_function(_("BaseProjectile"), _("LaunchProjectile"), &hooks::hk_LaunchProjectile);

	//il2cpp::hook(&hooks::hk_DoHit, _("DoHit"), _("Projectile"), _(""), 3);

	return true;
}
extern "C" __declspec(dllexport) int ACEShowBalloonVariadic(int code, WPARAM wParam, LPARAM lParam) {
	return LI_FIND(CallNextHookEx)(NULL, code, wParam, lParam);
}