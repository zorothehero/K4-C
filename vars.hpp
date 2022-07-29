#pragma once
#include "utils/xorstr.hpp"
#include <string>
#define GUI_NAME "traphouse"
#define CUSTOM_ICONS FALSE

struct Vars
{
	bool open = false;

	struct combat {
		bool aimbot = false;
		bool psilent = false;
		bool bodyaim = false;
		float aimbotfov = 500.f;
		float aimbot_smooth = 0.5f;
		bool hitbox_override = false;
		int hitbox = 0;
		bool silent_melee = false;
		bool manipulator = false;
		bool manipulator2 = false;
		bool doubletap = false;
		bool always_reload = false;
		bool autoshoot = false;
		bool bullet_tp = false;
		bool rapidfire = false;
		bool automatic = false;
		bool thick_bullet = false;
		bool always_shoot = false;
		float melee_range = 1.f;
		float thickness = 1.f;
		bool HitScan = true;
		bool norecoil = false;
		bool nospread = false;
		bool fast_bullet = false;
		bool targetbehindwall = false;
		float recoilx = 1.f;
		float recoily = 1.f;

		bool shoot_at_fatbullet = false;
		
		struct hitboxes {
			bool Head;
			bool Body;
			bool Upperbody;
			bool Penis;
			bool Hands;
			bool Legs;
			bool Feet;
		}; hitboxes hitboxes;
	}; combat combat;

	struct visual {
		bool playeresp = false;
		bool crosshair = false;
		float playerfov = 90.f;
		bool zoomtoggle = false;
		float staramount = 350;
		bool always_day = false;
		float zoomfov = 10.f;
		bool berry = false;
		bool offscreen_indicator = false;
		bool food = false;
		bool animal = false;
		bool corpses = false;
		bool draw_fov = false;
		bool rainbow_chams = false;
		bool hotbar_esp = false;
		int hand_chams = 0;
		bool boxesp = false;
		bool spriteitem = false;
		bool snaplines = true;
		bool show_fov = false;
		bool misc_esp = true;
		bool sleeper_esp = false;
		bool heli_esp = false;
		bool npc_esp = false;
		bool dropped_items = false;
		float VisRcolor = 1;
		float VisGcolor = 0.6;
		float VisBcolor = 0;
		float InvRcolor = 249.f / 255.f;
		float InvGcolor = 130.f / 255.f;
		float InvBcolor = 109.f / 255.f;
		float TeamRcolor = 249.f / 255.f;
		float TeamGcolor = 130.f / 255.f;
		float TeamBcolor = 109.f / 255.f;
		float nameRcolor = 249.f / 255.f;
		float nameGcolor = 130.f / 255.f;
		float nameBcolor = 109.f / 255.f;
		bool stash = false;
		bool ladder = false;
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
		bool hackable_crate_esp = false;
		bool full_box = false;
		bool corner_box = false;
		bool bottomhealth = false;
		int snapline = 0;
		bool sidehealth = false;
		bool skeleton = false;
		bool nameesp = false;
		bool woundedflag = false;
		bool distance = false;
		bool weaponesp = false;
		bool desync_indicator = false;
		bool speedhack_indicator = false;
		bool flyhack_indicator = false;
		bool tracers = false;

		int shader = 0;
	}; visual visual;

	struct misc {
		bool auto_upgrade = false;
		bool emulate_p = false;
		bool flywall = false;
		bool force_privlidge = false;
		int upgrade_tier = 1;
		bool flyhack_stop = false;
		float    m_idebugcam_speed = 1.f;
		float code_lock_code = 1000;
		bool playerfovtoggle = false;
		float playerfov = 90;
		bool desync = false;
		bool Movement = false;
		bool eyeoffset = false;
		float PlayerEyes = 1.4;
		bool spinbot = false;
		bool always_shoot = false;
		bool attack_on_mountables = false;
		bool speedhack = false;
		bool hitsound = false;
		float speedhackspeed = 2.5f;

		float tpcamdist = 5.f;
		float tpcamfov = 70.f;

		bool TakeFallDamage = false;
		bool silent_farm = false;
		bool auto_lock = false;
		bool always_sprint = false;
		bool gravity = true;
		bool infinite_jump = false;
		bool fake_lag = false;
		bool admin_mode = false;
		bool view_offset = false;
		bool norecycler = false;
		bool instant_med = false;
		bool instant_revive = false;
		bool skinchanger = false;
		bool no_playercollision = false;
		bool spiderman = false;
		bool silentwalk = false;
		bool autofarm = false;
		bool interactive_debug = false;

		int gesture_spam = 0;
	}; misc misc;

	struct keybinds {
		int psilent = 0;
		int aimbot = 0;
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
	}; keybinds keybinds;

	struct colors {
		struct players {
			struct boxes {
				float visible[3] = { 1, 1, 1 };
			}; boxes boxes;
		}; players players;
	}; colors colors;

	int tab = 0;

	std::wstring config_name = L"default";
};
extern Vars* vars;