#pragma once
namespace settings {
	float desyncTime = 0.0f;
	float time_since_last_shot = 0.0f;
	float hor_flyhack = 0.f;
	float vert_flyhack = 0.f;

	namespace keybind {
		int psilent = 0;
		int flywall = 0;
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
		bool hitbox_override  = true;
		bool magic_bullet  = false;
		bool ricochet = false;
		bool pierce  = false;
		bool rapidfire = false;
		float aimbotfov = 500.f;
		float thickness = 2.2f;
		bool random_hitbox  = false;
		bool silent_melee = false;
		bool weapon_removals  = false;
		bool always_shoot  = false;
		bool psilent = true;
		bool psilentvis = false;
		bool thick_bullet = true;
		bool legit_recoil = false;
		bool fast_bullet = true;
		bool bullet_tp = true;
		bool ultraBullet = false;
		bool norecoil = false;
		bool nospread = false;
		bool nosway = false;
		bool automatic = true;
		bool mods = false;

		bool manipulator = true;
		bool doubletap = true;
		bool always_reload = true;
		bool autoshoot = false;

		namespace hitboxes {
			bool Head = true;
			bool Body = false;
			bool Upperbody = false;
			bool Penis = true;
			bool Hands = false;
			bool Legs = false;
			bool Feet = false;
		}
	}

	namespace visuals {
		bool berry = false;
		bool offscreen_indicator = false;
		bool food = false;
		bool animal = false;
		bool lootesp = false;
		bool card = false;
		bool corpses = false;
		bool player_esp = true;
		bool draw_fov = false;
		bool rainbow_chams = false;
		bool hotbar_esp = false;
		bool chams = false;
		int hand_chams = 0;
		bool boxesp = false;
		bool spriteitem = false;
		bool snaplines = true;
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
		bool materials = false;
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
		bool barrels = false;
		bool tc_esp = false;
		bool angles = false;
		bool raid_esp = false;
		bool hackable_crate_esp = false;
		bool full_box = false;
		bool corner_box = true;
		bool bottomhealth = true;
		int snapline = 0;
		bool steamid = false;
		bool sidehealth = false;
		bool skeleton = true;
		bool nameesp = true;
		bool woundedflag = false;
		bool distance = true;

		bool weaponesp = false;
		bool vehicle = false;

		bool desync_indicator = true;

		int shader = 0;
	}

	namespace misc {
		bool auto_upgrade = false;
		bool flywall = false;
		bool force_privlidge = false;
		int upgrade_tier = 1;
		bool flyhack_indicator = false;
		bool flyhack_stop = false;
		float    m_idebugcam_speed = 1.f;
		float code_lock_code = 1000;
		bool playerfovtoggle = false;
		float playerfov = 90;
		bool zoomtoggle = false;
		bool desync = true;
		float zoomfov = 10;
		bool Movement = false;
		bool eyeoffset = false;
		float playereyes = 1.4;
		bool spinbot  = false;
		bool always_shoot = false;
		bool attack_on_mountables = false;
		bool speedhack = false;
		bool hitsound = false;
		float speedhackspeed = 2.5f;
		bool TakeFallDamage = false;
		bool silent_farm = false;
		bool auto_lock = false;
		bool always_sprint = true;
		bool gravity = true;
		bool infinite_jump = false;
		bool fake_lag = false;
		bool always_day = false;
		float staramount = 350;
		bool admin_mode = false;
		bool view_offset  = false;
		bool norecycler = false;
		bool instant_med  = true;
		bool instant_revive = false;
		bool no_playercollision = true;
		bool spiderman = true;
		bool Crosshair = false;
		bool silentwalk = false;
		bool autofarm = false;
		bool interactive_debug = false;
		bool trollface = false;
		
		int gesture_spam = 0;

		wchar_t* current_config = _(L"");
	}
}