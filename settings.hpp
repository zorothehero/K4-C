#pragma once

namespace settings {
	float desyncTime = 0.0f;
	float time_since_last_shot = 0.0f;

	namespace keybind {
		int psilent = 0;
		int silentmelee = 0;
		int autoshoot = 0;
		int manipulator = 0;
		int desync_ok = 0;
		int timescale = 0;
		int silentwalk = 0;
		int suicide = 0;
		int neck = 0;
		int zoom = 0;
		int bullettp = 0;
	}

	namespace weapon {
		bool hitbox_override  = false;
		bool magic_bullet  = false;
		bool rapidfire = false;
		float aimbotfov = 500;
		float thickness = 0.5;
		bool random_hitbox  = false;
		bool silent_melee = false;
		bool weapon_removals  = true;
		bool always_shoot  = false;
		bool psilent = true;
		bool psilentvis = true;
		bool thick_bullet = false;
		bool legit_recoil = false;
		bool fast_bullet = false;
		bool bullet_tp = false;
		bool ultraBullet = false;
		bool norecoil = true;
		bool nospread = true;
		bool nosway = true;
		bool automatic = false;
		bool mods = false;

		bool manipulator = true;
		bool doubletap = true;
		bool always_reload = true;
		bool autoshoot = false;
	}

	namespace visuals {
		bool player_esp = true;
		bool rainbow_chams = true;
		bool hotbar_esp = false;
		bool chams = true;
		bool boxesp = true;
		bool spriteitem = false;
		bool snaplines = false;
		bool show_fov = false;
		bool cancer = false;
		bool misc_esp  = true;
		bool sleeper_esp  = false;
		bool heli_esp = false;
		bool outline = false;
		bool npc_esp = false;
		bool dropped_items = false;
		float VisRcolor = 1;
		float VisGcolor = 0.6;
		float VisBcolor = 0;
		float InvRcolor  = 249.f / 255.f;
		float InvGcolor  = 130.f / 255.f;
		float InvBcolor  = 109.f / 255.f;
		float TeamRcolor = 249.f / 255.f;
		float TeamGcolor = 130.f / 255.f;
		float TeamBcolor = 109.f / 255.f;
		float nameRcolor = 249.f / 255.f;
		float nameGcolor = 130.f / 255.f;
		float nameBcolor = 109.f / 255.f;
		bool stash = false;
		bool materials = true;
		bool sulfur_ore = false;
		bool stone_ore = false;
		bool metal_ore = false;
		bool weapon = false;
		bool midhealth = false;
		bool midname = false;
		bool traps = false;
		bool vehicles = false;
		bool airdrops = false;
		bool cloth = false;
		bool corpses = false;
		bool tc_esp = false;
		bool raid_esp = false;
		bool hackable_crate_esp = false;
		bool full_box = false;
		bool corner_box = true;
		bool bottomhealth = false;
		bool steamid = false;
		bool sidehealth = true;
		bool nameesp = true;
		bool woundedflag = false;
		bool distance = true;

		bool weaponesp = false;
		bool vehicle = false;

		bool desync_indicator = true;
	}

	namespace misc {
		float    m_idebugcam_speed = 1.f;
		float code_lock_code = 1000;
		bool playerfovtoggle = true;
		float playerfov = 90;
		bool zoomtoggle = false;
		bool desync = false;
		float zoomfov = 10;
		bool Movement = true;
		bool eyeoffset = false;
		float playereyes = 1.4;
		bool spinbot  = false;
		bool always_shoot = false;
		bool attack_on_mountables = false;
		bool speedhack = false;
		bool hitsound = true;
		float speedhackspeed = 5;
		bool TakeFallDamage = false;
		bool silent_farm = false;
		bool auto_lock = false;
		bool always_sprint = true;
		bool gravity = true;
		bool infinite_jump = false;
		bool fake_lag = false;
		bool brightnight = true;
		float staramount = 350;
		bool admin_mode = false;
		bool view_offset  = false;
		bool instant_med  = true;
		bool instant_revive = false;
		bool no_playercollision = false;
		bool spiderman = false;
		bool Crosshair = true;
		bool silentwalk = false;
		bool interactive_debug = false;
		bool trollface = false;

	}
}