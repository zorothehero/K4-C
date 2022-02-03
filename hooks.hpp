#pragma once
#include "memory/il2cpp.hpp"
#include "settings.hpp"
#include "offsets.h"
#include <math.h>
#include "Keybind.h"

#include <vector>
namespace misc
{
	Vector3 best_lean{};

	void get_cyl(float radius, unsigned int sectors, std::vector<Vector3>& re, float max = 1.6f)
	{
		for (float y = -1.6f; y < 1.6f; y += 0.1f) {
			int points = sectors;
			float step = (M_PI_2) / points;
			float x, z, current = 0;
			for (size_t i = 0; i < points; i++)
			{
				x = Vector3::my_sin(current) * radius;
				z = Vector3::my_cos(current) * radius;

				re.push_back(Vector3(x, y, z));
				re.push_back(Vector3(-x, y, z));
				re.push_back(Vector3(x, y, -z));
				re.push_back(Vector3(-x, y, -z));

				current += step;
			}
		}
	}

	Vector3 manipulate(base_player* ply, float mm_eye)
	{
		Vector3 choice = Vector3(0, 0, 0);
		Vector3 v = *reinterpret_cast<Vector3*>((uintptr_t)ply + eyes);
		Vector3 re_p = ply->get_bone_transform(47)->get_bone_position() + ply->get_bone_transform(47)->up() * (ply->get_player_eyes()->get_view_offset().y + v.y);

		if (ply->is_visible(re_p, esp::best_target.pos))
			return choice;

		std::vector<Vector3> ar{};

		get_cyl(mm_eye, 50, ar);

		for (auto a : ar)
		{
			Vector3 p = re_p + a;

			if (!ply->is_visible(p, re_p))
				continue;

			//validate eye pos

			choice = a;
			break;
		}
		best_lean = choice;
		return choice;
	}

	bool just_shot = false;
	bool did_reload = false;
	float time_since_last_shot = 0.0f;
	float fixed_time_last_shot = 0.0f;
}

namespace hooks {
	namespace orig {
		static auto baseplayer_client_input = reinterpret_cast<void (*)(base_player*, input_state*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		static auto BaseProjectile_OnSignal = reinterpret_cast<void (*)(base_projectile*, int, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		static auto playerwalkmovement_client_input = reinterpret_cast<void (*)(playerwalkmovement*, uintptr_t, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		static auto DoFixedUpdate = reinterpret_cast<void (*)(playerwalkmovement*, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		static auto blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		static auto OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		static auto IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		static auto Run = reinterpret_cast<rust::classes::string (*)(uintptr_t, uintptr_t, rust::classes::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 3, _(""), _(""))));


		static auto get_bodyleanoffset = reinterpret_cast<Vector3 (*)(playereyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));
		static auto EyePositionForPlayer = reinterpret_cast<Vector3 (*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));
		static auto isdown = reinterpret_cast<bool(*)(input_state*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));
		static auto eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));
		static auto baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		uintptr_t playerprojectileattack;
		uintptr_t serverrpc_projectileshoot;
		uintptr_t serverrpc_processattack;
	}

	static auto serverrpc_projecileshoot = rb::pattern::find_rel(//
		_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

	static auto serverrpc_uint = rb::pattern::find_rel(
		_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

	static auto set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

	static auto draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

	static auto set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

	static auto GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

	static auto get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

	static auto IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

	static auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

	static auto OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

	static auto change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address); //BaseEntity$$ServerRPC<string, bool> Address

	static auto ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

	static auto DoHit = reinterpret_cast<bool (*)(base_projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), 4, _(""), _(""))));

	void init_hooks() {
		orig::IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		orig::OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		orig::BaseProjectile_OnSignal = reinterpret_cast<void (*)(base_projectile*, int, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		orig::baseplayer_client_input = reinterpret_cast<void (*)(base_player*, input_state*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		orig::playerwalkmovement_client_input = reinterpret_cast<void (*)(playerwalkmovement*, uintptr_t, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		orig::DoFixedUpdate = reinterpret_cast<void (*)(playerwalkmovement*, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		orig::blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));

		orig::get_bodyleanoffset = reinterpret_cast<Vector3(*)(playereyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));

		orig::isdown = reinterpret_cast<bool(*)(input_state*,int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));

		orig::EyePositionForPlayer = reinterpret_cast<Vector3(*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));

		orig::eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));

		orig::baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		serverrpc_projecileshoot = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

		serverrpc_uint = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

		ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

		change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address);

		set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

		draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

		set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

		GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

		get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

		IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

		ServerRPC = ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

		OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

		DoHit = reinterpret_cast<bool (*)(base_projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), 4, _(""), _(""))));
	}

	double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
		double pitch = (Vector3::my_atan2(height, DepthPlayerTarget));
		double BulletVelocityXY = velocity * Vector3::my_cos(pitch);
		double Time = DepthPlayerTarget / BulletVelocityXY;
		double TotalVerticalDrop = (0.5f * gravity * Time * Time);
		return TotalVerticalDrop * 10;
	}

	void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {
		float Dist = local.get_3d_dist(target);
		float BulletTime = Dist / bulletspeed;

		Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;

		Vector3 PredictVel = vel * BulletTime;

		target += PredictVel;

		double height = target.y - local.y;
		Vector3 dir = target - local;
		float DepthPlayerTarget = Vector3::my_sqrt(powFFFFFFFFFFFFFFFFFFFFFF(dir.x) + powFFFFFFFFFFFFFFFFFFFFFF(dir.z));

		float drop = CalcBulletDrop(height, DepthPlayerTarget, bulletspeed, gravity);

		target.y += drop;
	}

#pragma optimize("", off)
#pragma code_seg(".text")
	inline int64_t get_rbx_value()
	{
		static __declspec(allocate(".text")) char fn_stub[] = {
			0x48,
			0x89,
			0xD8, // mov    rax,rbx
			0xc3 // ret
		};

		return ((int64_t(*)())(&fn_stub))();
	}
#pragma code_seg(pop)
#pragma optimize("", on)

	//////////////////////////
	///////// PSILENT ////////
	//////////////////////////
	void hk_serverrpc_projectileshoot(int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5) {
		do {
			if (!esp::local_player)
				break;

			auto weapon = esp::local_player->get_active_weapon();

			if (!weapon)
				break;

			auto baseprojectile = esp::local_player->get_active_weapon()->get_base_projectile();
			if (!baseprojectile)
				break;

			auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);
			if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name) == 'ddaP')
				break;

			base_projectile* projectile_list = *reinterpret_cast<base_projectile**>(
				*reinterpret_cast<uintptr_t*>((uintptr_t)baseprojectile + 0x358) + 0x10); //createdProjectiles;

			esp::matrix = unity::get_view_matrix();
			auto camera_pos = unity::get_camera_pos();

			aim_target target = esp::local_player->get_aimbot_target(camera_pos);

			uintptr_t shoot_list = *(uintptr_t*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x10);

			auto size = *(int*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x18);

			Vector3 aimbot_velocity;

			const auto stats = baseprojectile->get_stats(weapon->get_item_definition_id());

			Vector3 aim_angle;
			Vector3 rpc_position;

			

			for (int i = 0; i < size; i++) {
				auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

				rpc_position = *reinterpret_cast<Vector3*>(projectile + 0x18);
				auto original_vel = *reinterpret_cast<Vector3*>(projectile + 0x24);
				
				if (target.player && target.visible && !target.teammate) {
					Prediction(rpc_position, target.pos, target.velocity, original_vel.Length(), stats.gravity_modifier);

					aim_angle = /*get_aim_angle(rpc_position, target.pos, target.velocity, false, stats)*/target.pos - rpc_position;

					aimbot_velocity = (aim_angle).Normalized() * original_vel.Length();

					*reinterpret_cast<Vector3*>(projectile + 0x24) = aimbot_velocity;
				}
			}

			for (int i = 0; i < projectile_list->get_size(); i++) {
				auto projectile = *(base_projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

				if (!projectile)
					continue;
				if (!keybinds::psilentb || unity::GetKey(keybinds::psilentk)) {
					if (settings::weapon::psilent) {
						if (target.player && !target.teammate) {
							if (!settings::weapon::psilentvis || target.visible) {
								projectile->set_current_velocity(aimbot_velocity);
							}
						}
					}
				}

				if (settings::weapon::thick_bullet)
					projectile->set_projectile_thickness(settings::weapon::thickness);
				else
					projectile->set_projectile_thickness(projectile->thickness);



				/////////////////////////////
				////////DOESNT WORK//////////
				/////////////////////////////

				//if (!projectile->first) {
				//	projectile->thickness = projectile->get_projectile_thickness();
				//	projectile->first = true;
				//}
			}
		} while (0);

		reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(hooks::orig::serverrpc_projectileshoot)(rcx, rdx, r9, projectileShoot, arg5);

		if (settings::weapon::always_reload)
		{
			misc::fixed_time_last_shot = get_fixedTime();
			misc::just_shot = true;
			misc::did_reload = false;
		}
	}

	bool is_lagging;

	bool flying = false, is_speeding = false;

	bool has_intialized_methods = false;

	float nextActionTime = 0, period = 1.4721;


	void hk_serverrpc_playerprojectileattack(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		auto        projectile = reinterpret_cast<base_projectile*>(get_rbx_value());
		auto  ppa = reinterpret_cast<rust::classes::PlayerProjectileAttack*>(_ppa);
		auto& attack = ppa->playerAttack->attack;

		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::playerprojectileattack);

		auto camera_pos = unity::get_camera_pos();
		if (camera_pos.is_empty())
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		do {
			if (!esp::local_player)
				break;

			auto hit_test = projectile->get_hit_test();
			if (!hit_test)
				break;

			if (!hit_test->get_gameobject())
				break;

			auto layer = hit_test->get_gameobject()->get_layer();
			auto prefab_name = hit_test->get_gameobject()->get_prefab_name();

			aim_target target = esp::local_player->get_aimbot_target(camera_pos);

			if (!target.player || !target.network_id)
				break;

			auto& hit_entity = hit_test->get_hit_entity();
			if (layer == rust::classes::layer::Player_Server) {
				if (hit_entity->is_teammate(esp::local_player)) {
					hit_test->set_ignore_entity(hit_entity);
					return;
				}
			}

			if (!settings::weapon::hitbox_override && !settings::weapon::random_hitbox)
				break;


			if (!target.is_heli && settings::weapon::hitbox_override) {
				attack->hitBone = 698017942;
				attack->hitPartID = 2173623152;
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else if (!target.is_heli && settings::weapon::random_hitbox) {
				switch (my_rand() % 4) {
				case 0: // Head
					attack->hitBone = 698017942;
					attack->hitPartID = 2173623152;
					break;
				case 1: // Chest
					attack->hitBone = 1031402764;
					attack->hitPartID = 1750816991;
					break;
				case 2: // LHand
					attack->hitBone = 182688154;
					attack->hitPartID = 1750816991;
					break;
				case 3: // RHand
					attack->hitBone = 102231371;
					attack->hitPartID = 1750816991;
					break;
				}
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else {
				auto weakspots = target.player->get_weakspots();
				if (!weakspots)
					break;

				auto size = *reinterpret_cast<uintptr_t*>(weakspots + 0x18);

				bool tail_alive = false;
				bool main_alive = false;
				for (int i = 0; i < size; i++) {
					auto weakspot = *(uintptr_t*)(weakspots + 0x20 + i * 0x8);
					if (!weakspot)
						continue;
					auto health = *reinterpret_cast<float*>(weakspot + 0x24);
					if (health > 0) {
						if (i == 0) {
							main_alive = true;
						}
						else {
							tail_alive = true;
						}
					}
				}

				if (tail_alive) {
					attack->hitBone = 2699525250;
					attack->hitPartID = 2306822461;
					attack->hitPositionLocal = { .9f, -.4f, .1f };
					attack->hitNormalLocal = { .9f, -.4f, .1f };
				}
				else if (main_alive) {
					attack->hitBone = 224139191;
					attack->hitPartID = 2306822461;
					attack->hitPositionLocal = { .9f, -.4f, .1f };
					attack->hitNormalLocal = { .9f, -.4f, .1f };
				}
			}
		} while (0);

		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

//
//void hk_baseprojectile_OnSignal(base_projectile* baseprojectile, int signal , rust::classes::string string) {
//	orig::BaseProjectile_OnSignal(baseprojectile, signal, string);
//
//	if (settings::visuals::raid_esp) {
//		auto reusableInstace = il2cpp::value(_("Effect"), _("reusableInstace"), false);
//
//		auto draw_explosion = [&](const char* explosion_name) {
//			auto world_position = *reinterpret_cast<Vector3*>(reusableInstace + 0x5C);
//			vector2 w2s_position = {};
//			if (esp::out_w2s(world_position, w2s_position)) {
//				esp::draw_item(w2s_position, il2cpp::methods::new_string(_("Rocket Explosion")), { 255,0,0,255 });
//			}
//		};
//
//		if (reusableInstace) {
//			auto world_position = *reinterpret_cast<transform**>(reusableInstace + 0x78);
//
//			auto esp_name = (str)(*reinterpret_cast<uintptr_t*>(reusableInstace + 0x88));
//			auto name = esp_name->str;
//
//			LOG("Prefab names: %ls", name);
//
//			if (m_wcsicmp(name, _(L"assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"))) {
//				draw_explosion(_("Rocket Explosion"));
//			}
//			else if (m_wcsicmp(name, _(L"assets/prefabs/tools/c4/effects/c4_explosion.prefab"))) {
//				draw_explosion(_("C4 Explosion"));
//			}
//		}
//	}
//}

#define ptr_assert(val) \
    if(val == 0)        \
    return
	uintptr_t client_entities;

	void hk_dofixedupdate(playerwalkmovement* base_movement, modelstate* modelstate) {
		if (esp::local_player && settings::misc::always_sprint && settings::misc::Movement) {
			bool is_busy = get_ducked(modelstate) | IsSwimming(esp::local_player);

			float speed = GetSpeed(esp::local_player, 1, is_busy);

			Vector3 vel = *reinterpret_cast<Vector3*>(base_movement + 0x34); // private Vector3 <TargetMovement>k__BackingField;
			Vector3 xz = Vector3(vel.x, 0, vel.z).normalize() * speed;
			vel = Vector3(xz.x, vel.y, xz.z);

			if (!flying) {
				*reinterpret_cast<Vector3*>(base_movement + 0x34) = vel;

				set_sprinting(modelstate, true);
			}
		}

		orig::DoFixedUpdate(base_movement, modelstate);
	}

	void hk_blocksprint(base_player* player, float duration) {
		if (!settings::weapon::always_shoot && settings::misc::Movement)
			return hooks::orig::blocksprint(player, duration);

		return;
	}

	void DoFatBullet(uintptr_t projectile)
	{

	}

	void draw_raid()
	{
		auto effect_network = il2cpp::init_class(_("EffectNetwork"));
		if (!effect_network)
			return;

		auto effect = *reinterpret_cast<uintptr_t*>(effect_network + 0xB8);
		if (!effect)
		{
			LOG("Effect null...");
			return;
		}

		effect = *reinterpret_cast<uintptr_t*>(effect);
		if (!effect)
		{
			LOG("Effect1 null...");
			return;
		}

		auto world_pos = *reinterpret_cast<Vector3*>(effect + 0x5C);
		if (world_pos.is_empty())
		{
			LOG("world_pos.is_empty()");
			return;
		}

		auto pooled_str = (str)(*reinterpret_cast<uintptr_t*>(effect + 0x88));
		auto pooledString = pooled_str->str;

		uintptr_t m_szTranslated;

		//assets/prefabs/ammo/rifle/riflebullet_explosive.prefab

		LOG("pooledString: %ls", pooled_str);
	}

	void hk_OnNetworkMessage(uintptr_t client, uintptr_t packet)
	{
		draw_raid();
		orig::OnNetworkMessage(client, packet);
	}

	void get_skydome()
	{
		uintptr_t m_skydome = NULL;
		uintptr_t m_camera = NULL;
		uintptr_t last_object = NULL;
		{
			auto gom = mem::read<uintptr_t>(mem::unity_player_base + 0x17C1F18);
			auto current_tagged_base = mem::read<uintptr_t>(gom + 0x08	);
			auto current_tagged_obj = mem::read<uintptr_t>(current_tagged_base + 0x10);

			while (current_tagged_obj &&
				current_tagged_obj != last_object &&
				(!m_skydome || !m_camera)) {
				INT16 tag = mem::read<uintptr_t>(current_tagged_obj + 0x54);

				if (!m_camera) {
					if (tag == 5) {
						uintptr_t objClass = mem::read<uintptr_t>(current_tagged_obj + 0x30);

						uintptr_t ent = mem::read<uintptr_t>(objClass + 0x18);

						m_camera = mem::read<uintptr_t>(current_tagged_obj + 0x18);
					}
				}


				if (!m_skydome)
				{
					if (tag == 20011) {
						uint64_t p = mem::read<uint64_t>(current_tagged_obj + 0x30);
						uint64_t p1 = mem::read<uint64_t>(p + 0x18);
						uint64_t p2 = mem::read<uint64_t>(p1 + 0x28);

						const auto TOD_Day = *reinterpret_cast<uintptr_t*>(p2 + 0x50);
						const auto TOD_Night = *reinterpret_cast<uintptr_t*>(p2 + 0x58);
						const auto TOD_Stars = *reinterpret_cast<uintptr_t*>(p2 + 0x70);
						if (settings::misc::brightnight) {
							*(float*)(TOD_Night + 0x50) = 4.f;
							*(float*)(TOD_Night + 0x54) = 1.f;
							*(float*)(TOD_Day + 0x50) = 1.f;
							*(float*)(TOD_Day + 0x54) = 1.f;
							*(float*)(TOD_Stars + 0x14) = settings::misc::staramount;
						}


						m_skydome = mem::read<uintptr_t>(current_tagged_obj + 0x18);
					}
				}
				last_object = current_tagged_obj;
				current_tagged_base = mem::read<uintptr_t>(current_tagged_base + 0x8);
				current_tagged_obj = mem::read<uintptr_t>(current_tagged_base + 0x10);
			}
		}
	}

	Vector3 m_debugcam_toggle_pos;
	Vector3 m_debugcam_pos;

	void hk_playerwalkmovement_ClientInput(playerwalkmovement* player_walk_movement, uintptr_t inputstate, modelstate* model_state) {
		orig::playerwalkmovement_client_input(player_walk_movement, inputstate, model_state);

		set_sprinting(model_state, true);

		flying = player_walk_movement->get_flying();

		if (!keybinds::silentwalkb || unity::GetKey(keybinds::silentwalkk)) {
			if (settings::misc::silentwalk) {
				set_onLadder(model_state, true);
			}
		}
		model_state->remove_flag(rust::classes::ModelState_Flag::Flying);
	}

	uintptr_t do_fixed_update_ptr, client_input_ptr, bodylean_ptr, mounteyepos_ptr, isdown_ptr;

	Vector3 hk_bodylean(playereyes* e)
	{
		if (settings::weapon::manipulator
			&& (unity::GetKey(keybinds::manipulate_key)))
		{
			if (esp::best_target.player != nullptr)
				if (misc::best_lean != Vector3(0, 0, 0))
					return misc::best_lean;
		}
		return orig::get_bodyleanoffset(e);
	}

	Vector3 hk_EyePositionForPlayer(basemountable* m, base_player* self, Vector4 q)
	{
		if (self->get_steam_id() == esp::local_player->get_steam_id())
			if (settings::weapon::manipulator
				&& (unity::GetKey(keybinds::manipulate_key)))
				return orig::EyePositionForPlayer(m, self, q) + misc::best_lean;
		return orig::EyePositionForPlayer(m, self, q);
	}

	bool hk_IsDown(input_state* self, rust::classes::BUTTON button)
	{
		if ((settings::weapon::autoshoot)
			&& (esp::best_target.visible)
			&& esp::local_player->get_active_weapon()->is_weapon()
			&& button == rust::classes::BUTTON::FIRE_PRIMARY)
			if (esp::local_player->get_active_weapon()->GetAmount() > 0)
				return true;

		return orig::isdown(self, button);
	}

	void EokaDoAttack_hk(uintptr_t w)
	{
		/*void set_did_hit(bool did_hit) {
		*reinterpret_cast<bool*>((uintptr_t)this + 0x66) = did_hit;
	}*/
		if (settings::weapon::weapon_removals)
			*reinterpret_cast<bool*>((uintptr_t)w + 0x370) = true;
		return orig::eokadoattack(w);
	}

	void hk_LaunchProjectile(base_projectile* p)
	{
		if (settings::weapon::doubletap)
		{
			auto held = esp::local_player->get_active_weapon();
			auto m = held->get_base_projectile()->get_repeat_delay();

			int r =((unity::get_realtimesincestartup() - esp::local_player->get_last_sent_ticket_time()) - 0.03125 * 3) / m;

			if (r <= 0)
				orig::baseprojectile_launchprojectile((uintptr_t)p);
			else
				for (size_t i = 0; i < r; i++)
				{
					orig::baseprojectile_launchprojectile((uintptr_t)p);

					auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)p + primaryMagazine);
					auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
					*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);

					updateammodisplay((uintptr_t)p);
					shot_fired((uintptr_t)p);
					did_attack_client_side((uintptr_t)p);
				}
			return;
		}
		return orig::baseprojectile_launchprojectile((uintptr_t)p);
	}

	void hk_DoFirstPersonCamera(playereyes* eyes, uintptr_t cam)
	{

	}

	void hk_UpdateVelocity(playerwalkmovement* self)
	{

	}

	void hk_HandleJumping(playerwalkmovement* self, modelstate* state, bool jump, bool in_dir = false) 
	{

	}

	void hk_DoMovement(Projectile* p, float deltaTime)
	{

	}

	void hk_DoHitNotify(uintptr_t basecombatentity, uintptr_t hitinfo)
	{

	}

	Projectile* hk_CreateProjectile(base_projectile* self, rust::classes::string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity)
	{
		return nullptr; //only for build
	}

	void hk_SendClientTick(base_player* self)
	{

	}

	void hk_baseplayer_ClientInput(base_player* baseplayer, input_state* state) {

		if(!do_fixed_update_ptr)
			do_fixed_update_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("DoFixedUpdate"), &hk_dofixedupdate);
		
		if(!client_input_ptr)
			client_input_ptr	= mem::hook_virtual_function(_("PlayerWalkMovement"), _("ClientInput"), &hk_playerwalkmovement_ClientInput);

		if(!mounteyepos_ptr)
			mounteyepos_ptr		= mem::hook_virtual_function(_("BaseMountable"), _("EyePositionForPlayer"), &hooks::hk_EyePositionForPlayer);

		if (!has_intialized_methods) {
			auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(il2cpp::methods::intialize_method);
			//56229 for real rust or 56204 for cracked rust
			for (int i = 0; i <
				56204//56204 //56229 = real rust
				; i++) {
				il2cpp_codegen_initialize_method(i);
			}
			has_intialized_methods = true;
		}

#pragma region static_method_hooks
		static uintptr_t* serverrpc_projecshoot;
		if (!serverrpc_projecshoot) {
			auto method_serverrpc_projecshoot = *reinterpret_cast<uintptr_t*>(hooks::serverrpc_projecileshoot);

			if (method_serverrpc_projecshoot) {
				serverrpc_projecshoot = **(uintptr_t***)(method_serverrpc_projecshoot + 0x30);

				hooks::orig::serverrpc_projectileshoot = *serverrpc_projecshoot;
		
				*serverrpc_projecshoot = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_projectileshoot);
			}
		}
		
		static uintptr_t* serverrpc_playerprojectileattack;
		if (!serverrpc_playerprojectileattack) {
			auto method_serverrpc_playerprojectileattack = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileAttack___);//Method$BaseEntity_ServerRPC_PlayerProjectileAttack___

			if (method_serverrpc_playerprojectileattack) {
				serverrpc_playerprojectileattack = **(uintptr_t***)(method_serverrpc_playerprojectileattack + 0x30);

				hooks::orig::playerprojectileattack = *serverrpc_playerprojectileattack;

				*serverrpc_playerprojectileattack = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_playerprojectileattack);
			}
		}
#pragma endregion

		if (baseplayer) {
			get_skydome();

			auto wpn = baseplayer->get_active_weapon();

			auto held = wpn ? wpn->get_base_projectile() : nullptr;

			if (settings::misc::attack_on_mountables) {
				auto mountable = baseplayer->get_mountable();
				if (mountable)
					mountable->canwielditem() = true;
			}

			bool kyslol = false;

			if (settings::misc::TakeFallDamage && unity::GetKey(rust::classes::KeyCode::P)) {

					OnLand(baseplayer, -8.0001f - 100);
			}

			bool t1 = orig::isdown(state, rust::classes::BUTTON::FIRE_PRIMARY);
			auto t2 = orig::get_bodyleanoffset(baseplayer->get_player_eyes());

			float mm_eye = ((0.01f + ((settings::desyncTime + 2.f / 60.f + 0.125f) * baseplayer->max_velocity())));

			if (settings::misc::admin_mode)
				baseplayer->set_admin_flag(rust::classes::PlayerFlags::IsAdmin);

			if (settings::misc::spiderman && settings::misc::Movement) {
				baseplayer->SpiderMan();
			}

			if (settings::misc::playerfovtoggle) {
				baseplayer->fov();

			}

			if (settings::weapon::manipulator
				&& (unity::GetKey(keybinds::manipulate_key)))
			{
				LOG("Manipulating!\n");
				misc::manipulate(baseplayer, mm_eye);
			}

			//desync on key
			if (keybinds::desynconb && unity::GetKey(keybinds::desynconk)
				|| (settings::weapon::manipulator
					&& (unity::GetKey(keybinds::manipulate_key)))) {
				LOG("Desync on key down!\n");
				baseplayer->set_client_tick_interval(0.99f);
			}
			else if(!is_lagging && !is_speeding)
				baseplayer->set_client_tick_interval(0.05f);

			if (settings::weapon::always_reload
				&& held)
			{
				if(!misc::did_reload)
					misc::time_since_last_shot = (get_fixedTime() - misc::fixed_time_last_shot);
				settings::time_since_last_shot = misc::time_since_last_shot;
				if (misc::just_shot && (misc::time_since_last_shot > 0.2f))
				{
					ServerRPC((uintptr_t)held, rust::classes::string(_(L"StartReload")));
					baseplayer->SendSignalBroadcast(rust::classes::Signal::Reload);
					misc::just_shot = false;
				}

				if (misc::time_since_last_shot > (held->get_reload_time() - (held->get_reload_time() / 10)) - 0.2f //-10% for faster reloads than normal >:)
					&& !misc::did_reload)
				{
					ServerRPC((uintptr_t)held, rust::classes::string(_(L"Reload")));
					misc::did_reload = true;
					misc::time_since_last_shot = 0;
				}
			}

			if (!keybinds::fakelagb || unity::GetKey(keybinds::fakelagk)) {
				if (!is_lagging && !flying && settings::misc::fake_lag && !is_speeding) {
					baseplayer->set_client_tick_interval(0.4f);
					is_lagging = true;
				}
			}
			else if (is_lagging && flying || is_lagging && is_speeding) {
				esp::local_player->set_client_tick_interval(0.03f);
				is_lagging = false;
			}
			else if (is_lagging && !settings::misc::fake_lag) {
				esp::local_player->set_client_tick_interval(0.05f);
				is_lagging = false;
			}


			if (auto movement = baseplayer->get_movement()) {
				if (settings::misc::spiderman) {
					movement->set_ground_angles_new(0);

				}

			}

			if (settings::misc::eyeoffset && unity::GetKey(rust::classes::KeyCode::Y))
			{
				baseplayer->get_player_eyes()->set_view_offset(Vector3(0, mm_eye > settings::misc::playereyes ? mm_eye : settings::misc::playereyes, 0));
			}

			if (auto movement = baseplayer->get_movement()) {
				if (settings::misc::infinite_jump && settings::misc::Movement) {
					movement->set_land_time(0);
					movement->set_jump_time(0);
					movement->set_ground_time(100000);
				}

				if (settings::misc::gravity && settings::misc::Movement)
					movement->set_gravity_multiplier(1.75f);
				else
					movement->set_gravity_multiplier(2.35f);

				if (settings::weapon::always_shoot && settings::misc::Movement) {
					if (auto modelstate = baseplayer->get_model_state()) {
						modelstate->set_flag(rust::classes::ModelState_Flag::OnGround);
						mem::write<float>((uint64_t)movement + 0x4C, 1); //private float <Grounded>k__BackingField; // 0x4C
					}
				}
			}

			auto item = baseplayer->get_active_weapon();

			if (settings::misc::auto_lock) {
				auto closest_ent = baseplayer->resolve_closest_entity(3);

				auto addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method_BaseEntity_ServerRPC_string_bool_address); //Method$BaseEntity.ServerRPC<string, bool>() address

				if (closest_ent.first.found && addr) {
					if (closest_ent.second) {
						auto code_str = string::format(_("%d"), (int)settings::misc::code_lock_code);
						change_code_rpc(closest_ent.first.player, rust::classes::string(_(L"RPC_ChangeCode")), il2cpp::methods::new_string(code_str), false, addr);
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"TryLock")));
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"RPC_Lock")));
					}
					else
						ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"RPC_Lock")));
				}
			}

			if (!keybinds::speedhackb || unity::GetKey(keybinds::speedhackk)) {
				if (settings::misc::speedhack && settings::misc::Movement) {
					set_timeScale(settings::misc::speedhackspeed);
					is_speeding = true;
				}
			}
			/*
			else if (!keybinds::speedkeyb || unity::GetKey(rust::classes::KeyCode::Mouse0)) {	-	fast bullet
				if (settings::weapon::rapidfire) {
					set_timeScale(1.2);
					is_speeding = true;
				}
			}
			*/
			else {
				set_timeScale(1);
				is_speeding = false;
			}

			if (item) {
				auto baseprojectile = item->get_base_projectile();
				if (baseprojectile) {
					auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);

					auto attack = [&](aim_target target, bool is_tree) {
						auto gathering = baseprojectile->Gathering();

						if (is_tree) {
							if (!(gathering->tree()->gatherDamage() > 1)) {
								return;
							}
						}
						else {
							if (!(gathering->ore()->gatherDamage() > 1)) {
								return;
							}
						}

						attack_melee(target, baseprojectile);
					};

					if (settings::misc::silent_farm) {
						auto entity = baseplayer->resolve_closest_entity(3, false);
						if (entity.first.found && entity.first.player) {
							if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name + 4) == 'mmah') {
								attack(entity.first, entity.second);
							}
						}
					}

					if (!(*(int*)(wep_class_name + 4) == 'eleM' && *(int*)(wep_class_name) == 'esaB')) {
						if (unity::GetKey(rust::classes::KeyCode::Mouse0) && settings::misc::instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								auto time = get_time();
								if (baseprojectile->get_time_since_deploy() > baseprojectile->get_deploy_delay() && baseprojectile->get_next_attack_time() <= get_time()) {
									if (time > nextActionTime) {
										nextActionTime = time + period;
										ServerRPC((uintptr_t)baseprojectile, rust::classes::string(_(L"UseSelf")));
									}
								}
							}
						}
						else if (unity::GetKey(rust::classes::KeyCode::Mouse1) && settings::misc::instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								esp::matrix = unity::get_view_matrix();
								auto camera_pos = unity::get_camera_pos();

								auto target = baseplayer->get_aimbot_target(camera_pos);

								if (target.player && target.distance < 5) {
									auto net = target.player->get_networkable();
									if (net) {
										auto id = net->get_id();
										if (id) {

											auto method_addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_uint);
											if (method_addr) {
												auto time = get_time();
												if (baseprojectile->get_time_since_deploy() > baseprojectile->get_deploy_delay() && baseprojectile->get_next_attack_time() <= get_time()) {
													if (time > nextActionTime) {
														nextActionTime = time + period;
														ServerRPC_int(baseprojectile, rust::classes::string(_(L"UseOther")), id, method_addr);
													}
												}
											}
										}
									}
								}
							}
						}

						//////weapon mods/////
						if (*(int*)(wep_class_name) == 'esaB' && *(int*)(wep_class_name + 4) == 'jorP' || *(int*)(wep_class_name) == 'nilF') {
							if (item->is_weapon()) {
								const auto item_id = item->get_item_definition_id();

								switch (item_id) {
								case -75944661:
									if (settings::weapon::weapon_removals) {
										mem::write<float>((uint64_t)baseprojectile + 0x360, 1.f); //eoka success fraction
									}
									break;
								default:
									if (settings::weapon::fast_bullet && !settings::weapon::ultraBullet)
									{
										if (item_id != 1318558775)
											baseprojectile->projectileVelocityScale() = 1.49f;
										else
											baseprojectile->projectileVelocityScale() = 1.2f;
									}
									if (settings::weapon::ultraBullet)
										baseprojectile->projectileVelocityScale() = 10.f;
									if (settings::weapon::automatic)
										baseprojectile->is_automatic() = true;
									if (settings::weapon::nospread)
										baseprojectile->set_no_spread();
									if (settings::weapon::norecoil)
										baseprojectile->set_recoil(0, 0, 0, 0);
									if (settings::weapon::legit_recoil)
										baseprojectile->set_recoil(1, 1, -1, 0);
									if (settings::weapon::nosway)
										baseprojectile->set_no_sway();
									break;
									
								}
							}
						}
					}
				}
			}

			if (settings::misc::instant_revive) {
				auto target = baseplayer->get_aimbot_target(unity::get_camera_pos());
				if (!target.is_heli && target.player && target.distance <= 5 && target.player->get_health() <= 4 && target.visible)
					ServerRPC((uintptr_t)target.player, rust::classes::string(_(L"RPC_Assist")));
			}

			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Water, !settings::misc::no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Tree, settings::misc::no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::AI, settings::misc::no_playercollision);

			draw_get();

			auto tick_time = baseplayer->get_last_sent_ticket_time();
			settings::desyncTime = (unity::get_realtimesincestartup() - tick_time) - 0.03125 * 3;
			if (tick_time > gui::tick_time_when_called + 10) {
				unity::camera = unity::get_main_camera();
				gui::tick_time_when_called = tick_time;
			}
		}

		orig::baseplayer_client_input(baseplayer, state);

		auto model_state = baseplayer->get_model_state();

		//model_state->set_water_level(99999);

		if (settings::misc::spinbot) {
			state->set_aim_angles(Vector3(100, my_rand() % 999 + -999, 100));
		}
	}
}