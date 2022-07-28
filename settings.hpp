#pragma once

#include <fstream>

#include "vars.hpp"
Vars* vars = new Vars();

void load_config() {
	auto s = LI_FIND(getenv)(_("APPDATA"));
	auto p = s + std::string(_("\\trap\\configs\\")) + std::string(vars->config_name.begin(), vars->config_name.end()) + _(".t");
	std::ifstream cFile(p, std::ios::in);


	std::string line;
	while (getline(cFile, line))
	{
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		if (line[0] == '#' || line.empty()) continue;

		auto delimiterPos = line.find("=");
		auto name = line.substr(0, delimiterPos);
		auto value = line.substr(delimiterPos + 1);

		if (name == _("psilent")) vars->combat.psilent = std::stoi(value);
		else if (name == _("aimbotfov")) vars->combat.aimbotfov = std::stoi(value);
		else if (name == _("hitbox_override")) vars->combat.hitbox_override = std::stoi(value);
		else if (name == _("hitbox")) vars->combat.hitbox = std::stoi(value);
		else if (name == _("silent_melee")) vars->combat.silent_melee = std::stoi(value);
		else if (name == _("manipulator")) vars->combat.manipulator = std::stoi(value);
		else if (name == _("doubletap")) vars->combat.doubletap = std::stoi(value);
		else if (name == _("always_reload")) vars->combat.always_reload = std::stoi(value);
		else if (name == _("autoshoot")) vars->combat.autoshoot = std::stoi(value);
		else if (name == _("bullet_tp")) vars->combat.bullet_tp = std::stoi(value);
		else if (name == _("rapidfire")) vars->combat.rapidfire = std::stoi(value);
		else if (name == _("automatic")) vars->combat.automatic = std::stoi(value);
		else if (name == _("thick_bullet")) vars->combat.thick_bullet = std::stoi(value);
		else if (name == _("always_shoot")) vars->combat.always_shoot = std::stoi(value);
		else if (name == _("melee_range")) vars->combat.melee_range = std::stof(value);
		else if (name == _("thickness")) vars->combat.thickness = std::stof(value);
		else if (name == _("norecoil")) vars->combat.norecoil = std::stoi(value);
		else if (name == _("nospread")) vars->combat.nospread = std::stoi(value);
		else if (name == _("fast_bullet")) vars->combat.fast_bullet = std::stoi(value);

		else if (name == _("playeresp")) vars->visual.playeresp = std::stoi(value);
		else if (name == _("crosshair")) vars->visual.crosshair = std::stoi(value);
		else if (name == _("playerfov")) vars->visual.playerfov = std::stof(value);
		else if (name == _("zoomtoggle")) vars->visual.zoomtoggle = std::stoi(value);
		else if (name == _("staramount")) vars->visual.staramount = std::stof(value);
		else if (name == _("always_day")) vars->visual.always_day = std::stoi(value);
		else if (name == _("zoomfov")) vars->visual.zoomfov = std::stof(value);
		else if (name == _("berry")) vars->visual.berry = std::stoi(value);
		else if (name == _("offscreen_indicator")) vars->visual.offscreen_indicator = std::stoi(value);
		else if (name == _("food")) vars->visual.food = std::stoi(value);
		else if (name == _("animal")) vars->visual.animal = std::stoi(value);
		else if (name == _("corpses")) vars->visual.corpses = std::stoi(value);
		else if (name == _("draw_fov")) vars->visual.draw_fov = std::stoi(value);
		else if (name == _("rainbow_chams")) vars->visual.rainbow_chams = std::stoi(value);
		else if (name == _("hotbar_esp")) vars->visual.hotbar_esp = std::stoi(value);
		else if (name == _("hand_chams")) vars->visual.hand_chams = std::stoi(value);
		//else if (name == _("chams")) vars->visual.shader = std::stoi(value);
		else if (name == _("boxesp")) vars->visual.boxesp = std::stoi(value);
		else if (name == _("spriteitem")) vars->visual.spriteitem = std::stoi(value);
		else if (name == _("snapline")) vars->visual.snaplines = std::stoi(value);
		else if (name == _("show_fov")) vars->visual.show_fov = std::stoi(value);
		else if (name == _("misc_esp")) vars->visual.misc_esp = std::stoi(value);
		else if (name == _("sleeper_esp")) vars->visual.sleeper_esp = std::stoi(value);
		else if (name == _("heli_esp")) vars->visual.heli_esp = std::stoi(value);
		else if (name == _("npc_esp")) vars->visual.npc_esp = std::stoi(value);
		else if (name == _("dropped_items")) vars->visual.dropped_items = std::stoi(value);
		else if (name == _("VisRcolor")) vars->visual.VisRcolor = std::stof(value);
		else if (name == _("VisGcolor")) vars->visual.VisGcolor = std::stof(value);
		else if (name == _("VisBcolor")) vars->visual.VisBcolor = std::stof(value);
		else if (name == _("InvRcolor")) vars->visual.InvRcolor = std::stof(value);
		else if (name == _("InvGcolor")) vars->visual.InvGcolor = std::stof(value);
		else if (name == _("InvBcolor")) vars->visual.InvBcolor = std::stof(value);
		else if (name == _("TeamRcolor")) vars->visual.TeamRcolor = std::stof(value);
		else if (name == _("TeamGcolor")) vars->visual.TeamGcolor = std::stof(value);
		else if (name == _("TeamBcolor")) vars->visual.TeamBcolor = std::stof(value);
		else if (name == _("nameRcolor")) vars->visual.nameRcolor = std::stof(value);
		else if (name == _("nameGcolor")) vars->visual.nameGcolor = std::stof(value);
		else if (name == _("nameBcolor")) vars->visual.nameBcolor = std::stof(value);
		else if (name == _("stash")) vars->visual.stash = std::stoi(value);
		else if (name == _("sulfur_ore")) vars->visual.sulfur_ore = std::stoi(value);
		else if (name == _("stone_ore")) vars->visual.stone_ore = std::stoi(value);
		else if (name == _("metal_ore")) vars->visual.metal_ore = std::stoi(value);
		else if (name == _("weapon")) vars->visual.weapon = std::stoi(value);
		else if (name == _("midhealth")) vars->visual.midhealth = std::stoi(value);
		else if (name == _("midname")) vars->visual.midname = std::stoi(value);
		else if (name == _("traps")) vars->visual.traps = std::stoi(value);
		else if (name == _("vehicles")) vars->visual.vehicles = std::stoi(value);
		else if (name == _("airdrops")) vars->visual.airdrops = std::stoi(value);
		else if (name == _("cloth")) vars->visual.cloth = std::stoi(value);
		else if (name == _("barrels")) vars->visual.barrels = std::stoi(value);
		else if (name == _("tc_esp")) vars->visual.tc_esp = std::stoi(value);
		else if (name == _("angles")) vars->visual.angles = std::stoi(value);
		else if (name == _("hackable_crate_esp")) vars->visual.hackable_crate_esp = std::stoi(value);
		else if (name == _("full_box")) vars->visual.full_box = std::stoi(value);
		else if (name == _("corner_box")) vars->visual.corner_box = std::stoi(value);
		else if (name == _("bottomhealth")) vars->visual.bottomhealth = std::stoi(value);
		else if (name == _("snapline")) vars->visual.snapline = std::stoi(value);
		else if (name == _("sidehealth")) vars->visual.sidehealth = std::stoi(value);
		else if (name == _("skeleton")) vars->visual.skeleton = std::stoi(value);
		else if (name == _("nameesp")) vars->visual.nameesp = std::stoi(value);
		else if (name == _("woundedflag")) vars->visual.woundedflag = std::stoi(value);
		else if (name == _("distance")) vars->visual.distance = std::stoi(value);
		else if (name == _("weaponesp")) vars->visual.weaponesp = std::stoi(value);
		else if (name == _("desync_indicator")) vars->visual.desync_indicator = std::stoi(value);
		else if (name == _("flyhack_indicator")) vars->visual.flyhack_indicator = std::stoi(value);
		else if (name == _("tracers")) vars->visual.tracers = std::stoi(value);
		//else if (name == _("shader")) vars->visual.shader = std::stoi(value);

		else if (name == _("auto_upgrade")) vars->misc.auto_upgrade = std::stoi(value);
		else if (name == _("flywall")) vars->misc.flywall = std::stoi(value);
		else if (name == _("force_privlidge")) vars->misc.force_privlidge = std::stoi(value);
		else if (name == _("upgrade_tier")) vars->misc.upgrade_tier = std::stoi(value);
		else if (name == _("flyhack_stop")) vars->misc.flyhack_stop = std::stoi(value);
		else if (name == _("playerfovtoggle")) vars->misc.playerfovtoggle = std::stoi(value);
		else if (name == _("playerfov")) vars->misc.playerfov = std::stof(value);
		else if (name == _("desync")) vars->misc.desync = std::stoi(value);
		else if (name == _("Movement")) vars->misc.Movement = std::stoi(value);
		else if (name == _("eyeoffset")) vars->misc.eyeoffset = std::stoi(value);
		else if (name == _("playereyes")) vars->misc.playereyes = std::stof(value);
		else if (name == _("spinbot")) vars->misc.spinbot = std::stoi(value);
		else if (name == _("always_shoot")) vars->misc.always_shoot = std::stoi(value);
		else if (name == _("attack_on_mountables")) vars->misc.attack_on_mountables = std::stoi(value);
		else if (name == _("speedhack")) vars->misc.speedhack = std::stoi(value);
		else if (name == _("hitsound")) vars->misc.hitsound = std::stoi(value);
		else if (name == _("speedhackspeed")) vars->misc.speedhackspeed = std::stof(value);
		else if (name == _("tpcamdist")) vars->misc.tpcamdist = std::stof(value);
		else if (name == _("tpcamfov")) vars->misc.tpcamfov = std::stof(value);
		else if (name == _("TakeFallDamage")) vars->misc.TakeFallDamage = std::stoi(value);
		else if (name == _("silent_farm")) vars->misc.silent_farm = std::stoi(value);
		else if (name == _("auto_lock")) vars->misc.auto_lock = std::stoi(value);
		else if (name == _("always_sprint")) vars->misc.always_sprint = std::stoi(value);
		else if (name == _("gravity")) vars->misc.gravity = std::stoi(value);
		else if (name == _("infinite_jump")) vars->misc.infinite_jump = std::stoi(value);
		else if (name == _("fake_lag")) vars->misc.fake_lag = std::stoi(value);
		else if (name == _("admin_mode")) vars->misc.admin_mode = std::stoi(value);
		else if (name == _("view_offset")) vars->misc.view_offset = std::stoi(value);
		else if (name == _("norecycler")) vars->misc.norecycler = std::stoi(value);
		else if (name == _("instant_med")) vars->misc.instant_med = std::stoi(value);
		else if (name == _("instant_revive")) vars->misc.instant_revive = std::stoi(value);
		else if (name == _("no_playercollision")) vars->misc.no_playercollision = std::stoi(value);
		else if (name == _("spiderman")) vars->misc.spiderman = std::stoi(value);
		else if (name == _("silentwalk")) vars->misc.silentwalk = std::stoi(value);
		else if (name == _("autofarm")) vars->misc.autofarm = std::stoi(value);
		else if (name == _("interactive_debug")) vars->misc.interactive_debug = std::stoi(value);
		//else if (name == _("gesture_spam")) vars->misc.gesture_spam = std::stoi(value);
	}
}

void save_config() {
	//save all settings idfk how yet
	auto s = LI_FIND(getenv)(_("APPDATA"));
	auto p = s + std::string(_("\\trap\\configs\\")) + std::string(vars->config_name.begin(), vars->config_name.end()) + _(".t");
	remove(p.c_str());
	std::ofstream f(p);
	char buffer[4];
	itoa(vars->combat.psilent, buffer, 4);
	auto str = (std::string("psilent=") + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->combat.aimbotfov);
	str = (std::string(_("aimbotfov=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa((int)vars->combat.hitbox_override, buffer, 4);
	str = (std::string(_("hitbox_override=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.hitbox, buffer, 4);
	str = (std::string(_("hitbox=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.silent_melee, buffer, 4);
	str = (std::string(_("silent_melee=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.manipulator, buffer, 4);
	str = (std::string(_("manipulator=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.doubletap, buffer, 4);
	str = (std::string(_("doubletap=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.always_reload, buffer, 4);
	str = (std::string(_("always_reload=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.autoshoot, buffer, 4);
	str = (std::string(_("autoshoot=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.bullet_tp, buffer, 4);
	str = (std::string(_("bullet_tp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.rapidfire, buffer, 4);
	str = (std::string(_("rapidfire=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.automatic, buffer, 4);
	str = (std::string(_("automatic=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.thick_bullet, buffer, 4);
	str = (std::string(_("thick_bullet=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.always_shoot, buffer, 4);
	str = (std::string(_("always_shoot=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->combat.melee_range);
	str = (std::string(_("melee_range=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->combat.thickness);
	str = (std::string(_("thickness=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.norecoil, buffer, 4);
	str = (std::string(_("norecoil=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.nospread, buffer, 4);
	str = (std::string(_("nospread=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->combat.fast_bullet, buffer, 4);
	str = (std::string(_("fast_bullet=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());

	itoa(vars->visual.playeresp, buffer, 4);
	str = (std::string(_("playeresp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.crosshair, buffer, 4);
	str = (std::string(_("crosshair=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.playerfov);
	str = (std::string(_("playerfov=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.zoomtoggle, buffer, 4);
	str = (std::string(_("zoomtoggle=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.staramount);
	str = (std::string(_("staramount=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.always_day, buffer, 4);
	str = (std::string(_("always_day=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.zoomfov);
	str = (std::string(_("zoomfov=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.berry, buffer, 4);
	str = (std::string(_("berry=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.offscreen_indicator, buffer, 4);
	str = (std::string(_("offscreen_indicator=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.food, buffer, 4);
	str = (std::string(_("food=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.animal, buffer, 4);
	str = (std::string(_("animal=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.corpses, buffer, 4);
	str = (std::string(_("corpses=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.draw_fov, buffer, 4);
	str = (std::string(_("draw_fov=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.rainbow_chams, buffer, 4);
	str = (std::string(_("rainbow_chams=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.hotbar_esp, buffer, 4);
	str = (std::string(_("hotbar_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.hand_chams, buffer, 4);
	str = (std::string(_("hand_chams=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.shader, buffer, 4);
	str = (std::string(_("chams=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.boxesp, buffer, 4);
	str = (std::string(_("boxesp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.spriteitem, buffer, 4);
	str = (std::string(_("spriteitem=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.snaplines, buffer, 4);
	str = (std::string(_("snapline=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.show_fov, buffer, 4);
	str = (std::string(_("show_fov=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.misc_esp, buffer, 4);
	str = (std::string(_("misc_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.sleeper_esp, buffer, 4);
	str = (std::string(_("sleeper_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.heli_esp, buffer, 4);
	str = (std::string(_("heli_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.npc_esp, buffer, 4);
	str = (std::string(_("npc_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.dropped_items, buffer, 4);
	str = (std::string(_("dropped_items=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.VisRcolor);
	str = (std::string(_("VisRcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.VisGcolor);
	str = (std::string(_("VisGcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.VisBcolor);
	str = (std::string(_("VisBcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.InvRcolor);
	str = (std::string(_("InvRcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.InvGcolor);
	str = (std::string(_("InvGcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.InvBcolor);
	str = (std::string(_("InvBcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.TeamRcolor);
	str = (std::string(_("TeamRcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.TeamGcolor);
	str = (std::string(_("TeamGcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.TeamBcolor);
	str = (std::string(_("TeamBcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.nameRcolor);
	str = (std::string(_("nameRcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.nameGcolor);
	str = (std::string(_("nameGcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->visual.nameBcolor);
	str = (std::string(_("nameBcolor=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.stash, buffer, 4);
	str = (std::string(_("stash=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.sulfur_ore, buffer, 4);
	str = (std::string(_("sulfur_ore=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.stone_ore, buffer, 4);
	str = (std::string(_("stone_ore=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.metal_ore, buffer, 4);
	str = (std::string(_("metal_ore=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.weapon, buffer, 4);
	str = (std::string(_("weapon=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.midhealth, buffer, 4);
	str = (std::string(_("midhealth=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.midname, buffer, 4);
	str = (std::string(_("midname=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.traps, buffer, 4);
	str = (std::string(_("traps=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.vehicles, buffer, 4);
	str = (std::string(_("vehicles=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.airdrops, buffer, 4);
	str = (std::string(_("airdrops=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.cloth, buffer, 4);
	str = (std::string(_("cloth=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.barrels, buffer, 4);
	str = (std::string(_("barrels=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.tc_esp, buffer, 4);
	str = (std::string(_("tc_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.angles, buffer, 4);
	str = (std::string(_("angles=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.hackable_crate_esp, buffer, 4);
	str = (std::string(_("hackable_crate_esp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.full_box, buffer, 4);
	str = (std::string(_("full_box=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.corner_box, buffer, 4);
	str = (std::string(_("corner_box=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.bottomhealth, buffer, 4);
	str = (std::string(_("bottomhealth=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.snapline, buffer, 4);
	str = (std::string(_("snapline=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.sidehealth, buffer, 4);
	str = (std::string(_("sidehealth=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.skeleton, buffer, 4);
	str = (std::string(_("skeleton=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.nameesp, buffer, 4);
	str = (std::string(_("nameesp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.woundedflag, buffer, 4);
	str = (std::string(_("woundedflag=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.distance, buffer, 4);
	str = (std::string(_("distance=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.weaponesp, buffer, 4);
	str = (std::string(_("weaponesp=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.desync_indicator, buffer, 4);
	str = (std::string(_("desync_indicator=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.flyhack_indicator, buffer, 4);
	str = (std::string(_("flyhack_indicator=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.shader, buffer, 4);
	str = (std::string(_("shader=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->visual.tracers, buffer, 4);
	str = (std::string(_("tracers=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());

	itoa(vars->misc.auto_upgrade, buffer, 4);
	str = (std::string(_("auto_upgrade=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.flywall, buffer, 4);
	str = (std::string(_("flywall=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.upgrade_tier, buffer, 4);
	str = (std::string(_("upgrade_tier=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.flyhack_stop, buffer, 4);
	str = (std::string(_("flyhack_stop=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.playerfovtoggle, buffer, 4);
	str = (std::string(_("playerfovtoggle=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.desync, buffer, 4);
	str = (std::string(_("desync=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.Movement, buffer, 4);
	str = (std::string(_("Movement=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.eyeoffset, buffer, 4);
	str = (std::string(_("eyeoffset=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->misc.playereyes);
	str = (std::string(_("playereyes=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.spinbot, buffer, 4);
	str = (std::string(_("spinbot=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.always_shoot, buffer, 4);
	str = (std::string(_("always_shoot=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.attack_on_mountables, buffer, 4);
	str = (std::string(_("attack_on_mountables=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.speedhack, buffer, 4);
	str = (std::string(_("speedhack=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.hitsound, buffer, 4);
	str = (std::string(_("hitsound=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	sprintf(buffer, _("%.2f"), vars->misc.speedhackspeed);
	str = (std::string(_("speedhackspeed=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.TakeFallDamage, buffer, 4);
	str = (std::string(_("TakeFallDamage=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.silent_farm, buffer, 4);
	str = (std::string(_("silent_farm=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.auto_lock, buffer, 4);
	str = (std::string(_("auto_lock=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.always_sprint, buffer, 4);
	str = (std::string(_("always_sprint=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.gravity, buffer, 4);
	str = (std::string(_("gravity=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.infinite_jump, buffer, 4);
	str = (std::string(_("infinite_jump=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.fake_lag, buffer, 4);
	str = (std::string(_("fake_lag=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.admin_mode, buffer, 4);
	str = (std::string(_("admin_mode=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.view_offset, buffer, 4);
	str = (std::string(_("view_offset=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.norecycler, buffer, 4);
	str = (std::string(_("norecycler=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.instant_med, buffer, 4);
	str = (std::string(_("instant_med=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.instant_revive, buffer, 4);
	str = (std::string(_("instant_revive=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.no_playercollision, buffer, 4);
	str = (std::string(_("no_playercollision=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.spiderman, buffer, 4);
	str = (std::string(_("spiderman=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.silentwalk, buffer, 4);
	str = (std::string(_("silentwalk=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.autofarm, buffer, 4);
	str = (std::string(_("autofarm=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.interactive_debug, buffer, 4);
	str = (std::string(_("interactive_debug=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	itoa(vars->misc.gesture_spam, buffer, 4);
	str = (std::string(_("gesture_spam=")) + std::string(buffer) + _("\n"));
	f.write(str.c_str(), str.size());
	f.close();
}

#define M_PI 3.14159265358979323846f
#define M_PI_2 1.57079632679489661923
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
namespace settings {
	float MagicBulletTimer = 0.0f;
	int HitScanBone = 48;
	bool LaunchProjectile = false;
	Vector3 FatHitPosition = {};
	Vector3 RealGangstaShit = {};
	bool CanMagicBoolet = false;
	bool targetbehindwall = false;
	float desyncTime = 0.0f;
	float speedhack = 0.0f;
	float time_since_last_shot = 0.0f;
	float hor_flyhack = 0.f;
	float vert_flyhack = 0.f;

	namespace keybind {
	}

	namespace visuals {

	}

	namespace misc {

	}
}