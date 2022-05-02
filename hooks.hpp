#pragma once
#include "memory/il2cpp.hpp"
#include "settings.hpp"
#include "offsets.h"
#include <math.h>
#include "Keybind.h"

//#include <vector>
namespace misc
{
	bool manual = false;
	bool autoshot = false;
	bool manipulate_vis = false;
	Vector3 cLastTickPos{};
	Vector3 best_lean{};

	double fabs(double x)
	{
		union { double f; uint64_t i; } u = { x };
		u.i &= -1ULL / 2;
		return u.f;
	}

	bool TestNoClipping(base_player* ply = esp::local_player,
		Vector3 oldPos = Vector3(0, 0, 0),
		Vector3 newPos = Vector3(0, 0, 0))
	{
		float radius = ply->get_radius() - 0.21f;
		Vector3 normalized = (newPos - oldPos).Normalized();
		Vector3 vector = oldPos - normalized * 0.01f;
		float magnitude = (newPos - vector).Length();
		Ray z = Ray(vector, normalized);
		bool flag = unity::Raycast(z, magnitude + radius, 429990145);
		//if (!flag)
		//{
		//	flag = unity::Spherecast(z, radius, magnitude, 429990145);
		//}
		return flag;
	}

	bool ValidateEyePos(Vector3 pos, Vector3 offset = Vector3(0, 0, 0))
	{
		bool flag = false;
		auto loco = esp::local_player;
		auto eyepos = loco->get_player_eyes()->get_position() + offset;
		float num = 1.5f;
		float num2 = 2.f / 60.f;
		float deltatime = get_deltaTime();
		//float smooth_deltatime = get_smoothdeltaTime();
		//float fixed_deltatime = get_fixeddeltaTime();
		float num3 = 2.f * deltatime;
		float num4 = (1.f + num2 + num3) * num;
		float num5 = loco->max_velocity() + GetParentVelocity(loco).Length();
		float num6 = loco->boundspadding() + num4 * num5;
		float num7 = eyepos.distance(pos);
		float num8 = fabs(GetParentVelocity(loco).y);
		float num9 = loco->boundspadding() + num4 + num8 + loco->get_jump_height();
		float num10 = fabs(eyepos.y - pos.y);

		if (num10 > num9)
		{
			flag = true;
		}

		auto t = get_transform(loco);
		Vector3 position2 = t->get_bone_position();

		if (position2.distance(loco->get_player_eyes()->get_position()) > 0.01f
			&& TestNoClipping(loco, cLastTickPos, position2))
		{
			flag = true;
		}

		return flag;
	}

	bool can_manipulate(base_player* ply, Vector3 pos, float mm_eye = 7.f) //7m only check rn
	{
		Vector3 v = *reinterpret_cast<Vector3*>((uintptr_t)ply + eyes);
		Vector3 re_p = ply->get_bone_transform(47)->get_bone_position() + ply->get_bone_transform(47)->up() * (ply->get_player_eyes()->get_view_offset().y + v.y);
		//std::vector<Vector3> ar{};
		//get_cyl(mm_eye, 10, ar);

		/*
		if (ply->is_visible(re_p, pos))
		{
			misc::best_lean = Vector3(0, 0, 0);
			return true;
		}*/

		auto do_check = [&](Vector3 a) {
			Vector3 p = re_p + a;

			if (!ply->is_visible(p, re_p))
				return false;

			if (!ply->is_visible(p - Vector3(0, 0.1, 0), re_p)) //double check not too low as likes to shoot from just under the ground
				return false;

			Sphere(p, 0.05f, col(0.1, 0.3, 0.9, 1), 0.01f, 10);
			if (!ply->is_visible(p, pos))
				return false;

			if (ValidateEyePos(p))
				return false;

			misc::best_lean = a;
			return true;
		};

		for (float y = -1.5f; y < 1.5f; y += 0.2f) {
			int points = 10;
			float step = (M_PI_2) / points;
			float x, z, current = 0;
			for (size_t i = 0; i < points; i++)
			{
				x = Vector3::my_sin(current) * mm_eye;
				z = Vector3::my_cos(current) * mm_eye;

				Vector3 p1 = Vector3(x, y, z);
				Vector3 p2 = Vector3(-x, y, z);
				Vector3 p3 = Vector3(x, y, -z);
				Vector3 p4 = Vector3(-x, y, -z);

				if (do_check(p1)) return true;
				if (do_check(p2)) return true;
				if (do_check(p3)) return true;
				if (do_check(p4)) return true;

				current += step;
			}
		}

		misc::best_lean = Vector3(0, 0, 0);
		return false;
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
		static auto UpdateVelocity = reinterpret_cast<void (*)(playerwalkmovement*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("UpdateVelocity"), -1, _(""), _(""))));
		static auto blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		static auto OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		static auto IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		static auto Run = reinterpret_cast<rust::classes::string(*)(uintptr_t, uintptr_t, rust::classes::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 3, _(""), _(""))));


		static auto get_bodyleanoffset = reinterpret_cast<Vector3(*)(playereyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));
		static auto EyePositionForPlayer = reinterpret_cast<Vector3(*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));
		static auto isdown = reinterpret_cast<bool(*)(input_state*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));
		static auto eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));
		static auto baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));
		static auto baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(base_projectile*, rust::classes::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));

		uintptr_t playerprojectileattack;
		uintptr_t baseprojectilecreateprojectile;
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

		orig::isdown = reinterpret_cast<bool(*)(input_state*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));

		orig::UpdateVelocity = reinterpret_cast<void (*)(playerwalkmovement*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("UpdateVelocity"), -1, _(""), _(""))));

		orig::EyePositionForPlayer = reinterpret_cast<Vector3(*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));

		orig::eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));

		orig::baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		orig::baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(base_projectile*, rust::classes::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));

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

	bool is_lagging;

	bool flying = false, is_speeding = false;

	bool has_intialized_methods = false;

	float nextActionTime = 0, period = 1.4721;

	Vector3 m_debugcam_toggle_pos;

	Vector3 m_debugcam_pos;

	uintptr_t do_fixed_update_ptr, client_input_ptr, bodylean_ptr, mounteyepos_ptr, isdown_ptr;

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

			bool manipulated = false;

			Vector3 original_vel{};

			for (int i = 0; i < size; i++) {
				auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

				rpc_position = *reinterpret_cast<Vector3*>(projectile + 0x18);


				if (settings::weapon::manipulator
					&& (unity::GetKey((rust::classes::KeyCode)settings::keybind::manipulator)
						|| misc::manipulate_vis))
				{
					auto b = rpc_position;
					if (misc::best_lean != Vector3(0, 0, 0))
					{
						// rpc_position += misc::manipulate(esp::local_player, target.pos);
						rpc_position += (misc::best_lean);
						if (rpc_position != b)
						{
							manipulated = true;
							target.visible = true;
							*reinterpret_cast<Vector3*>(projectile + 0x18) = rpc_position;
							//Sphere(rpc_position, 0.05f, col(0.9, 0.1, 0.1, 3), 5.f, 25.f);
						}
					}
				}

				original_vel = *reinterpret_cast<Vector3*>(projectile + 0x24);


				if (target.player && (target.visible || manipulated || misc::autoshot) && !target.teammate) {
					if (!settings::weapon::bullet_tp)
						Prediction(rpc_position, target.pos, target.velocity, original_vel.Length(), stats.gravity_modifier);
					else if (settings::desyncTime < (target.distance / original_vel.Length()))
						Prediction(rpc_position, target.pos, target.velocity, original_vel.Length(), stats.gravity_modifier);

					aim_angle = /*get_aim_angle(rpc_position, target.pos, target.velocity, false, stats)*/target.pos - rpc_position;

					aimbot_velocity = (aim_angle).Normalized() * original_vel.Length();

					*reinterpret_cast<Vector3*>(projectile + 0x24) = aimbot_velocity; //startvel
				}
			}

			for (int i = 0; i < projectile_list->get_size(); i++) {
				auto projectile = *(base_projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

				if (!projectile)
					continue;

				if (settings::weapon::bullet_tp)
				{
					//check traveltime
					auto p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
					if (settings::desyncTime > (target.distance / original_vel.Length()))
						p->SetInitialDistance(target.distance);
					else p->SetInitialDistance(0);
				}

				if (settings::weapon::psilent || unity::GetKey(rust::classes::KeyCode(settings::keybind::psilent))) {
					if (target.player && !target.teammate) {
						if (target.visible)
						{
							projectile->set_current_velocity(aimbot_velocity);

							if (manipulated) {
								auto g = get_gameObject((uintptr_t)projectile);
								auto t = get_game_object_transform(g);
								set_position(t, rpc_position);
							}
						}
					}
				}

				if (settings::weapon::thick_bullet)
					projectile->set_projectile_thickness(settings::weapon::thickness);
				else
					projectile->set_projectile_thickness(projectile->thickness);
			}
		} while (0);

		if (misc::autoshot)
			misc::autoshot = false;
		reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(hooks::orig::serverrpc_projectileshoot)(rcx, rdx, r9, projectileShoot, arg5);

		misc::fixed_time_last_shot = get_fixedTime();
		misc::just_shot = true;
		misc::did_reload = false;
	}


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

			/*
StringPool::Get(xorstr_("head")) = 698017942
StringPool::Get(xorstr_("pelvis")) = 2811218643
StringPool::Get(xorstr_("r_hip")) = 2331610670
StringPool::Get(xorstr_("r_foot")) = 920055401
StringPool::Get(xorstr_("spine1")) = 3771021956
StringPool::Get(xorstr_("l_hand")) = 736328754
StringPool::Get(xorstr_("r_upperarm")) = 3901657145
StringPool::Get(xorstr_("l_knee")) = 3892428003
StringPool::Get(xorstr_("spine4")) = 827230707
*/

			if (!target.is_heli && settings::weapon::hitbox_override) {
				attack->hitBone = 698017942;
				attack->hitPartID = 2173623152;
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else if (!target.is_heli && settings::weapon::random_hitbox) {
				switch (my_rand() % 10) {
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
				case 4: // pelvis
					attack->hitBone = 2811218643;
					attack->hitPartID = 1750816991;
					break;
				case 5: // r_hip
					attack->hitBone = 2331610670;
					attack->hitPartID = 1750816991;
					break;
				case 6: // r_foot
					attack->hitBone = 920055401;
					attack->hitPartID = 1750816991;
					break;
				case 7: // spine1
					attack->hitBone = 3771021956;
					attack->hitPartID = 1750816991;
					break;
				case 8: // l_upperarm
					attack->hitBone = 3901657145;
					attack->hitPartID = 1750816991;
					break;
				case 9: // l_knee
					attack->hitBone = 3892428003;
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

	/**void hk_dofixedupdate(playerwalkmovement* base_movement, modelstate* modelstate) {
		if (esp::local_player && settings::misc::always_sprint && settings::misc::Movement) {
			bool is_busy = get_ducked(modelstate) || IsSwimming(esp::local_player);

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
	/*/

	void hk_blocksprint(base_player* player, float duration) {
		if (!settings::weapon::always_shoot && settings::misc::Movement)
			return hooks::orig::blocksprint(player, duration);

		return;
	}


	void DoFatBullet(uintptr_t projectile)
	{
		auto p = (Projectile*)projectile;


		return Update(p);
	}

	void AimConeDir_hk(float aimcone, Vector3 input, bool anywhereInside)
	{
		//return orig::getmodifiedaimcone(aimcone, input, anywhereInside);
	}


	void hk_OnNetworkMessage(uintptr_t client, uintptr_t packet)
	{
		//	draw_raid();
		orig::OnNetworkMessage(client, packet);
	}


	void get_skydome()
	{
		uintptr_t m_skydome = NULL;
		uintptr_t m_camera = NULL;
		uintptr_t last_object = NULL;
		{
			auto gom = mem::read<uintptr_t>(mem::unity_player_base + 0x17C1F18);
			auto current_tagged_base = mem::read<uintptr_t>(gom + 0x08);
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


	void hk_playerwalkmovement_ClientInput(playerwalkmovement* player_walk_movement, uintptr_t inputstate, modelstate* model_state) {

		orig::playerwalkmovement_client_input(player_walk_movement, inputstate, model_state);

		set_sprinting(model_state, true);

		flying = player_walk_movement->get_flying();

		if (!keybinds::silentwalkb || unity::GetKey(keybinds::silentwalkk)) {
			if (settings::misc::silentwalk) {
				set_onLadder(model_state, true);
			}
		}

		if (settings::misc::interactive_debug)
			model_state->set_flag(rust::classes::ModelState_Flag::Mounted);

		model_state->remove_flag(rust::classes::ModelState_Flag::Flying);

		if (settings::misc::always_sprint) {
			Vector3 vel = player_walk_movement->get_TargetMovement();
			float max_speed = (player_walk_movement->get_swimming() || player_walk_movement->get_ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				player_walk_movement->set_TargetMovement(target_vel);
			}
		}

		auto wpn = esp::local_player->get_active_weapon();
		auto held = wpn ? wpn->get_base_projectile() : nullptr;
		if (settings::weapon::always_reload
			&& held)
		{
			misc::time_since_last_shot = (get_fixedTime() - misc::fixed_time_last_shot);
			settings::time_since_last_shot = misc::time_since_last_shot;
			if (misc::just_shot && (misc::time_since_last_shot > 0.2f))
			{
				hooks::ServerRPC((uintptr_t)held, rust::classes::string(_(L"StartReload")));
				esp::local_player->SendSignalBroadcast(rust::classes::Signal::Reload); //does this cause animation?
				misc::just_shot = false;
			}
			float reloadtime = 0.f;

			auto name = wpn->get_weapon_name();
			if (LI_FIND(wcscmp)(name, _(L"Assault Rifle")) == 0)
				reloadtime = 4.4f;
			if (LI_FIND(wcscmp)(name, _(L"Assault Rifle - ICE")) == 0)
				reloadtime = 4.4f;
			//if (LI_FIND(wcscmp)(name, _(L"Bolt Action Rifle")) == 0)
			//	reloadtime = 5.f;
			if (LI_FIND(wcscmp)(name, _(L"Crossbow")) == 0)
				reloadtime = 3.6f;
			if (LI_FIND(wcscmp)(name, _(L"Custom SMG")) == 0)
				reloadtime = 4.f;
			if (LI_FIND(wcscmp)(name, _(L"Eoka Pistol")) == 0)
				reloadtime = 2.f;
			if (LI_FIND(wcscmp)(name, _(L"LR-300 Assault Rifle")) == 0)
				reloadtime = 4.f;
			if (LI_FIND(wcscmp)(name, _(L"M249")) == 0)
				reloadtime = 7.5f;
			////if (LI_FIND(wcscmp)(name, _(L"L96 Rifle")) == 0)
			////	reloadtime = 3.f;
			if (LI_FIND(wcscmp)(name, _(L"M39 Rifle")) == 0)
				reloadtime = 3.25f;
			if (LI_FIND(wcscmp)(name, _(L"M92 Pistol")) == 0)
				reloadtime = 2.2f;
			if (LI_FIND(wcscmp)(name, _(L"MP5A4")) == 0)
				reloadtime = 4.f;
			if (LI_FIND(wcscmp)(name, _(L"Nailgun")) == 0)
				reloadtime = 3.1f;
			////if (LI_FIND(wcscmp)(name, _(L"Pump Shotgun")) == 0)
			////	reloadtime = 5.5f;
			if (LI_FIND(wcscmp)(name, _(L"Python Revolver")) == 0)
				reloadtime = 3.75f;
			if (LI_FIND(wcscmp)(name, _(L"Revolver")) == 0)
				reloadtime = 3.4f;
			if (LI_FIND(wcscmp)(name, _(L"Semi-Automatic Pistol")) == 0)
				reloadtime = 2.9f;
			if (LI_FIND(wcscmp)(name, _(L"Semi-Automatic Rifle")) == 0)
				reloadtime = 4.4f;
			//if (LI_FIND(wcscmp)(name, _(L"Spas-12 Shotgun")) == 0)
			//	reloadtime = 5.8f;
			if (LI_FIND(wcscmp)(name, _(L"Thompson")) == 0)
				reloadtime = 4.f;

			esp::rl_time = reloadtime;

			if (misc::time_since_last_shot > reloadtime - 0.2f //-10% for faster reloads than normal >:)
				&& !misc::did_reload)
			{
				hooks::ServerRPC((uintptr_t)held, rust::classes::string(_(L"Reload")));
				misc::did_reload = true;
				misc::time_since_last_shot = 0;
			}
		}
	}

	Vector3 hook_test(playereyes* e)
	{
		return Vector3(0, 69, 0);
	}
	Vector3 hook_test2(playereyes* e)
	{
		return Vector3(0, 69, 0);
	}
	Vector3 hook_test3(playereyes* e)
	{
		return Vector3(0, 69, 0);
	}

	Vector3 hk_bodylean(playereyes* e)
	{
		__try
		{
			if (!esp::local_player)
				return orig::get_bodyleanoffset(e);
			if (settings::weapon::manipulator && misc::best_lean != Vector3(0, 0, 0))
				return misc::best_lean;

			return orig::get_bodyleanoffset(e);
			//return Vector3(0, 0, 0);
		}
		__except (true)
		{
			return orig::get_bodyleanoffset(e);
		}
	}


	Vector3 hk_EyePositionForPlayer(playereyes* eyes)
	{
		if (!esp::local_player)
			return eyes->get_position();
		if (misc::best_lean == Vector3(0, 0, 0))
			return eyes->get_position();
		else if (settings::weapon::manipulator
			&& (unity::GetKey(rust::classes::KeyCode(settings::keybind::manipulator))))
			return eyes->get_position() + misc::best_lean;
		return eyes->get_position();
	}


	bool hk_IsDown(input_state* self, rust::classes::BUTTON button)
	{
		if ((settings::weapon::autoshoot || unity::GetKey(rust::classes::KeyCode(settings::keybind::autoshoot)))
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

			int r = settings::desyncTime / m;

			if (r > 1)
			{
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
		}
		orig::baseprojectile_launchprojectile((uintptr_t)p);

		if (misc::manual) {
			auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)p + primaryMagazine);
			auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
			*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);
			misc::manual = false;
		}

		return;
	}


	void hk_DoFirstPersonCamera(playereyes* eyes, uintptr_t cam)
	{

	}


	bool test = true;
	void hk_UpdateVelocity(playerwalkmovement* self)
	{
		if (test)
		{
			test = false;
			MessageBoxA(0, "WORKED", "AZ", 0);
		}

		//	if (!self->flying()) {


		return orig::UpdateVelocity(self);
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

	//int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5
	uintptr_t hk_CreateProjectile(uintptr_t self, rust::classes::string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity)
	{
		//reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(hooks::orig::baseprojectilecreateprojectile)(rcx, rdx, r9, projectileShoot, arg5);
		auto p = orig::baseprojectile_createprojectile((base_projectile*)self, prefabPath, pos, forward, velocity);
		if (settings::weapon::bullet_tp)
		{
			auto p = *(Projectile**)(self);
			//check traveltime
			float time = 0;
			Vector3 pos{};
			Vector3 vel = p->Simulate(0, 0, pos, time);
			Sphere(pos, 1, col(0.5, 0.5, 0.8, 1), 60, 500);
			if (settings::desyncTime > time)
				p->SetInitialDistance(esp::local_player->get_bone_transform(47)->get_bone_position().distance(pos));
		}
		return p;
	}


	void hk_SendClientTick(uintptr_t self)
	{
		auto ply = (base_player*)(self);
		misc::cLastTickPos = ply->get_player_eyes()->get_position();
		return SendClientTick(ply);
	}


	void hk_baseplayer_ClientInput(base_player* baseplayer, input_state* state) {
		//__try {
			//if(!do_fixed_update_ptr)
			//do_fixed_update_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("DoFixedUpdate"), &hk_dofixedupdate);

			if (!client_input_ptr)
				client_input_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("ClientInput"), &hk_playerwalkmovement_ClientInput);

			if (!mounteyepos_ptr)
				mounteyepos_ptr = mem::hook_virtual_function(_("BaseMountable"), _("EyePositionForPlayer"), &hooks::hk_EyePositionForPlayer);

			if (!has_intialized_methods) {
				auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(il2cpp::methods::intialize_method);
				//56229 for real rust or 56204 for cracked rust
				for (int i = 0; i <
					56229//56204 //56229 = real rust
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

				auto tick_time = baseplayer->get_last_sent_tick_time();
				settings::desyncTime = (unity::get_realtimesincestartup() - tick_time) - 0.03125 * 3;

				if (settings::desyncTime < 0.f)
					misc::cLastTickPos = baseplayer->get_player_eyes()->get_position();

				auto wpn = baseplayer->get_active_weapon();

				auto held = wpn ? wpn->get_base_projectile() : nullptr;

				if (settings::misc::attack_on_mountables) {
					auto mountable = baseplayer->get_mountable();
					if (mountable)
						mountable->canwielditem() = true;
				}

				bool kyslol = false;

				if (settings::misc::TakeFallDamage && unity::GetKey(rust::classes::KeyCode(settings::keybind::suicide))) {

					OnLand(baseplayer, -8.0001f - 100);
				}

				bool t1 = orig::isdown(state, rust::classes::BUTTON::FIRE_PRIMARY);
				auto t2 = orig::get_bodyleanoffset(baseplayer->get_player_eyes());

				if (settings::misc::admin_mode)
					baseplayer->set_admin_flag(rust::classes::PlayerFlags::IsAdmin);

				if (settings::misc::spiderman && settings::misc::Movement) {
					baseplayer->SpiderMan();
				}

				if (settings::misc::playerfovtoggle) {
					baseplayer->fov();

				}

				float mm_eye = ((0.01f + ((settings::desyncTime + 2.f / 60.f + 0.125f) * baseplayer->max_velocity())));
				float time = get_fixedTime();
				if (esp::best_target.player && held && wpn)
				{
					Vector3 target = esp::best_target.player->get_bone_transform(48)->get_bone_position();
					Sphere(target, 0.05, col(0.8, 0.9, 0.3, 1), 0.05f, 10.f);
					
					auto getammo = [&](base_projectile* held)
					{
						__try {
							if (held)
							{
								auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)held + primaryMagazine);
								return *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
							}
						}
						__except (true) {
							return 0;
						}
					};

					auto mag_ammo = getammo(held);

					if (settings::weapon::manipulator
						&& ((unity::GetKey(rust::classes::KeyCode(settings::keybind::manipulator)))
							|| misc::manipulate_vis))
					{
						float nextshot = misc::fixed_time_last_shot + held->get_repeat_delay();
						if (misc::can_manipulate(baseplayer, target, mm_eye))
							if (nextshot < time
								&& held->get_time_since_deploy() > held->get_deploy_delay()
								&& mag_ammo > 0)
							{
								//auto b4 = baseplayer->get_player_eyes()->get_view_offset();
								//if(misc::best_lean != Vector3(0,0,0))
								//	baseplayer->get_player_eyes()->set_view_offset(misc::best_lean);
								hk_LaunchProjectile(held);
								//*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (mag_ammo - 1);
								baseplayer->send_client_tick();
								//baseplayer->get_player_eyes()->set_view_offset(b4);
							}
					}

					if ((settings::weapon::autoshoot || unity::GetKey(rust::classes::KeyCode(settings::keybind::autoshoot))))
					{
						float nextshot = misc::fixed_time_last_shot + held->get_repeat_delay();
						Sphere(target, 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
						Sphere(baseplayer->get_bone_transform(48)->get_bone_position(), 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
						if (baseplayer->is_visible(target, baseplayer->get_bone_transform(48)->get_bone_position())
							&& get_fixedTime() > nextshot
							&& held->get_time_since_deploy() > held->get_deploy_delay()
							&& mag_ammo > 0)
						{
							misc::autoshot = true;
							hk_LaunchProjectile(held);
							updateammodisplay((uintptr_t)held);
							shot_fired((uintptr_t)held);
							did_attack_client_side((uintptr_t)held);
							*reinterpret_cast<int*>((uintptr_t) * reinterpret_cast<uintptr_t*>((uintptr_t)held + primaryMagazine) + 0x1C) = (mag_ammo - 1);
							baseplayer->send_client_tick();
						}
						else if (!baseplayer->is_visible(baseplayer->get_bone_transform(48)->get_bone_position(), target)
							//&& get_fixedTime() > nextshot
							&& settings::weapon::manipulator
							&& mag_ammo > 0)
						{
							if (misc::can_manipulate(baseplayer, target, 5.f))
							{//maybe check more later idk
								misc::manipulate_vis = true;
							}
							else misc::manipulate_vis = false;
						}
					}
					else misc::manipulate_vis = false;
				}
				else misc::manipulate_vis = false;
				//desync on key
				if (unity::GetKey(rust::classes::KeyCode(settings::keybind::desync_ok))
					|| (settings::weapon::manipulator
						&& (unity::GetKey(rust::classes::KeyCode(settings::keybind::manipulator))
							|| misc::manipulate_vis)))
					baseplayer->set_client_tick_interval(0.99f);
				else if (!is_lagging && !is_speeding)
					baseplayer->set_client_tick_interval(0.05f);


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

				if (settings::misc::eyeoffset || unity::GetKey((rust::classes::KeyCode)settings::keybind::neck))
				{
					baseplayer->get_player_eyes()->set_view_offset(Vector3(0, settings::misc::playereyes, 0));
				}

				if (auto movement = baseplayer->get_movement()) {
					if (settings::misc::spiderman) {
						movement->set_ground_angles_new(-1);
					}
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

				if (settings::misc::speedhack || unity::GetKey(rust::classes::KeyCode(settings::keybind::timescale))) {
					set_timeScale(settings::misc::speedhackspeed);
					is_speeding = true;
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
											mem::write<bool>((uint64_t)baseprojectile + 0x370, true); //eoka _didSparkThisFrame
										}
										break;
									default:
										if (settings::weapon::fast_bullet)
											if (item_id != 1318558775)
												baseprojectile->SetProjectileVelocityScale(1.49f);
										if (settings::weapon::rapidfire)
											baseprojectile->set_repeat_delay(0.02f);
										//if (settings::weapon::ultraBullet)
										//	baseprojectile->projectileVelocityScale() = 10.f; //????????????????????????????
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
		//}
		//__except (true)
		//{
		//	LOG("[+] Error in func %s!", _(__FUNCTION__));
		//}
	}
}
