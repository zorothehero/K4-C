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

bool DllMain(uintptr_t hmodule)
{

	if (!has_initialized) {
		mem::game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
		mem::unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));

		//mem::try_pattern(_("53 C3"));

		il2cpp::init();
		/*
		mem::hook_virtual_function(_("PlayerEyes"), _("get_BodyLeanOffset"), &hooks::hk_bodylean);
		mem::hook_virtual_function(_("BaseMountable"), _("EyePositionForPlayer"), &hooks::hk_EyePositionForPlayer);
		mem::hook_virtual_function(_("InputState"), _("IsDown"), &hooks::hk_IsDown);
		*/

		unity::init_unity();
		gui::init_gui();
		hooks::init_hooks();


		init_bp();
		init_projectile();
		has_initialized = true;
	}

	il2cpp::hook(&gui::OnGUI, _("OnGUI"), _("DDraw"), _("UnityEngine"), 0);
	il2cpp::hook(&hooks::hk_OnNetworkMessage, _("OnNetworkMessage"), _("Client"), _(""), 1);



	il2cpp::hook(&hooks::DoFatBullet, _("Update"), _("Projectile"), _(""), 0);

	//il2cpp::hook(&hooks::hk_bodylean, _("get_BodyLeanOffset"), _("PlayerEyes"), _(""), 0);
	//il2cpp::hook(&hooks::hk_IsDown, _("IsDown"), _("InputState"), _(""), 1);
	il2cpp::hook(&hooks::EokaDoAttack_hk, _("DoAttack"), _("FlintStrikeWeapon"), _(""), 1);

	mem::hook_virtual_function(_("BasePlayer"), _("ClientInput"), &hooks::hk_baseplayer_ClientInput);
	mem::hook_virtual_function(_("BasePlayer"), _("BlockSprint"), &hooks::hk_blocksprint);
	mem::hook_virtual_function(_("BaseProjectile"), _("LaunchProjectile"), &hooks::hk_LaunchProjectile);
	//mem::hook_virtual_function(_("Client"), _("IsConnected"), &hooks::is_connected_hk, _("Network"));

	return true;
}
