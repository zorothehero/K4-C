#pragma once
#include "nine_meter_poggers.hpp"

namespace hooks {
	namespace orig {
		static auto baseplayer_client_input = reinterpret_cast<void (*)(BasePlayer*, InputState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		static auto BaseProjectile_OnSignal = reinterpret_cast<void (*)(BaseProjectile*, int, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		static auto playerwalkmovement_client_input = reinterpret_cast<void (*)(PlayerWalkMovement*, uintptr_t, ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		static auto DoFixedUpdate = reinterpret_cast<void (*)(PlayerWalkMovement*, ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		static auto UpdateVelocity = reinterpret_cast<void (*)(PlayerWalkMovement*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("UpdateVelocity"), -1, _(""), _(""))));
		static auto blocksprint = reinterpret_cast<void (*)(BasePlayer*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		static auto OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		static auto IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		static auto Run = reinterpret_cast<System::string(*)(uintptr_t, System::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 0, _(""), _(""))));


		static auto get_bodyleanoffset = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));
		static auto EyePositionForPlayer = reinterpret_cast<Vector3(*)(BaseMountable*, BasePlayer*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));
		static auto isdown = reinterpret_cast<bool(*)(InputState*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));
		static auto eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));
		static auto baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));
		static auto attackent_addpunch = reinterpret_cast<void(*)(uintptr_t, Vector3, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HeldEntity"), _("AddPunch"), 0, _(""), _(""))));
		static auto baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(BaseProjectile*, System::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));
		static auto DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

		static auto _update = reinterpret_cast<void (*)(Projectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Update"), 0, _(""), _(""))));

		uintptr_t playerprojectileattack;
		uintptr_t createbuilding;
		uintptr_t playerprojectilericochet;
		uintptr_t playerprojectileupdate;
		uintptr_t baseprojectilecreateprojectile;
		uintptr_t serverrpc_projectileshoot;
		uintptr_t serverrpc_processattack;
	}

#pragma region functions

	//static auto serverrpc_projecileshoot = rb::pattern::find_rel(
	//	_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 4C 8B 74 24"));
	static auto serverrpc_projecileshoot = rb::pattern::find_rel(
		_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

	static auto serverrpc_uint = rb::pattern::find_rel(
		_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

	static auto set_sprinting = reinterpret_cast<void (*)(ModelState*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

	static auto draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

	static auto set_flying = reinterpret_cast<void (*)(ModelState * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

	static auto get_ducked = reinterpret_cast<bool (*)(ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

	static auto OnLand = reinterpret_cast<void (*)(BasePlayer*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

	static auto change_code_rpc = reinterpret_cast<void (*)(BasePlayer*, System::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address); //BaseEntity$$ServerRPC<string, bool> Address

	static auto ServerRPC_int = reinterpret_cast<void (*)(BaseProjectile*, System::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);
	
	//static auto get_resourcePath = reinterpret_cast<System::string (*)(uintptr_t)>(mem::game_assembly_base + offsets::Method$ResourceRef_method);

	static auto DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

	static auto PerformanceUI_Update = reinterpret_cast<void (*)(void*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PerformanceUI"), _("Update"), -1, _(""), _("Facepunch"))));


	void init_hooks() {
		orig::IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		orig::OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		orig::BaseProjectile_OnSignal = reinterpret_cast<void (*)(BaseProjectile*, int, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		orig::baseplayer_client_input = reinterpret_cast<void (*)(BasePlayer*, InputState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		orig::playerwalkmovement_client_input = reinterpret_cast<void (*)(PlayerWalkMovement*, uintptr_t, ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		orig::DoFixedUpdate = reinterpret_cast<void (*)(PlayerWalkMovement*, ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		orig::blocksprint = reinterpret_cast<void (*)(BasePlayer*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		orig::Run = reinterpret_cast<System::string(*)(uintptr_t, System::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 0, _(""), _(""))));

		orig::get_bodyleanoffset = reinterpret_cast<Vector3(*)(PlayerEyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));

		orig::isdown = reinterpret_cast<bool(*)(InputState*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));

		orig::UpdateVelocity = reinterpret_cast<void (*)(PlayerWalkMovement*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("UpdateVelocity"), -1, _(""), _(""))));

		orig::EyePositionForPlayer = reinterpret_cast<Vector3(*)(BaseMountable*, BasePlayer*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));

		orig::eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));

		orig::baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		orig::baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(BaseProjectile*, System::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));

		orig::DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

		orig::attackent_addpunch = reinterpret_cast<void(*)(uintptr_t, Vector3, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HeldEntity"), _("AddPunch"), 0, _(""), _(""))));

		orig::_update = reinterpret_cast<void (*)(Projectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Update"), 0, _(""), _(""))));

		serverrpc_projecileshoot = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

		serverrpc_uint = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

		ServerRPC_int = reinterpret_cast<void (*)(BaseProjectile*, System::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

		//get_resourcePath = reinterpret_cast<System::string(*)(uintptr_t)>(mem::game_assembly_base + offsets::Method$ResourceRef_method);

		change_code_rpc = reinterpret_cast<void (*)(BasePlayer*, System::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address);

		set_sprinting = reinterpret_cast<void (*)(ModelState*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

		draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

		set_flying = reinterpret_cast<void (*)(ModelState * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

		get_ducked = reinterpret_cast<bool (*)(ModelState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

		PerformanceUI_Update = reinterpret_cast<void (*)(void*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PerformanceUI"), _("Update"), -1, _(""), _("Facepunch"))));

		OnLand = reinterpret_cast<void (*)(BasePlayer*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

		DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));
	}

#pragma endregion

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

#define ptr_assert(val) \
    if(val == 0)        \
    return
	uintptr_t client_entities;

	bool flying = false, is_speeding = false, is_lagging = false, has_intialized_methods = false, wake = true;
	float nextActionTime = 0, period = 1.4721, last_gesture_rpc = 0.f;;
	Vector3 m_debugcam_toggle_pos, m_debugcam_pos;
	uintptr_t do_fixed_update_ptr, client_input_ptr, bodylean_ptr, mounteyepos_ptr, isdown_ptr, __go;

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
						uint64_t tod_sky = mem::read<uint64_t>(p1 + 0x28);

						const auto TOD_Day = *reinterpret_cast<uintptr_t*>(tod_sky + 0x50);
						const auto TOD_Night = *reinterpret_cast<uintptr_t*>(tod_sky + 0x58);
						const auto TOD_Stars = *reinterpret_cast<uintptr_t*>(tod_sky + 0x70);
						if (vars->visual.always_day) {
							*(float*)(TOD_Night + 0x50) = 4.f;
							*(float*)(TOD_Night + 0x54) = 1.f;
							*(float*)(TOD_Day + 0x50) = 1.f;
							*(float*)(TOD_Day + 0x54) = 1.f;
							*(float*)(TOD_Stars + 0x14) = vars->visual.staramount;
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

	void hk_serverrpc_projectileshoot(int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5) {
		Projectile* p;
		Vector3 rpc_position;
		float time = get_fixedTime();
		float travel_t = 0.f;
		int simulations = 0;
		do {
			if (!esp::local_player)
				break;

			auto Item = esp::local_player->GetActiveItem();

			if (!Item)
				break;

			auto baseprojectile = esp::local_player->GetActiveItem()->GetHeldEntity<BaseProjectile>();
			if (!baseprojectile)
				break;

			auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);
			if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name) == 'ddaP')
				break;

			BaseProjectile* projectile_list = *reinterpret_cast<BaseProjectile**>(
				*reinterpret_cast<uintptr_t*>((uintptr_t)baseprojectile + 0x370) + 0x10); //createdProjectiles;

			esp::matrix = unity::get_view_matrix();
			auto camera_pos = unity::get_camera_pos();

			//aim_target target = esp::local_player->get_aimbot_target(camera_pos);
			aim_target target = esp::best_target;

			/*
				struct projectileshoot_projectile {
		bool ShouldPool; // 0x10
		bool _disposed; // 0x11
		int projectileID; // 0x14
		Vector3 startPos; // 0x18
		Vector3 startVel; // 0x24
		int seed; // 0x30
	};
	struct projectileshoot {
		bool ShouldPool; // 0x10
		bool _disposed; // 0x11
		int ammoType; // 0x14
		projectileshoot_projectile projectiles[]; //0x18
		//std::vector<projectileshoot_projectile> projectiles;
	};
			*/

			uintptr_t shoot_list = *(uintptr_t*)(*(uintptr_t*)(projectileShoot + 0x18));// + 0x10);

			if(!misc::emulated)
				shoot_list = *(uintptr_t*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x10);

			auto size = *(int*)(*(uintptr_t*)(projectileShoot + 0x18) + 0x18);

			Vector3 aimbot_velocity = Vector3(0,0,0);

			const auto stats = baseprojectile->get_stats(Item->get_item_definition_id());

			Vector3 aim_angle;

			bool manipulated = false;

			Vector3 original_vel{};

			bool vis_fat = false;
			//get position of player with velocity
			//get direction to that
			//calculate perfect Y velocity in loop to find where projectile lands

			//calc new target position with velocity
			Vector3 target_velocity, target_pos;
			if (target.ent)
			{
				target_pos = target.pos;
			}

			//new_pos = new_pos.multiply(target_velocity);

			for (int i = 0; i < size; i++) {
				uintptr_t projshoot = 0;
				if (misc::emulated)
				{
					if (i == size)
					{
						misc::emulated = false;
					}
				}
				else projshoot = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);

				original_vel = *reinterpret_cast<Vector3*>(projshoot + 0x24);
				rpc_position = *reinterpret_cast<Vector3*>(projshoot + 0x18);

				target.visible = target.ent->is_visible(rpc_position, target.pos);

				if (misc::best_target == Vector3(0, 0, 0)
					&& vars->combat.thick_bullet
					&& vars->combat.shoot_at_fatbullet
					&& !target.visible)
				{
					for (auto v : sphere1m)
					{
						if (target.ent)
						{
							if (target.ent->is_visible(target_pos, target_pos + v)
								&& target.ent->is_visible(target_pos + v, rpc_position))
								misc::best_target = target_pos + v;
						}
					}
				}

				//NEW POGCHAMP MANIPULATOR

				if (vars->combat.manipulator2
					&& (unity::GetKey((rust::classes::KeyCode)vars->keybinds.manipulator)
						&& settings::RealGangstaShit != Vector3(0, 0, 0)))
				{
					if (settings::FatHitPosition != Vector3(0, 0, 0))
					{
						target_pos = settings::FatHitPosition;
					}
					rpc_position = settings::RealGangstaShit;
					*reinterpret_cast<Vector3*>(projshoot + 0x18) = rpc_position;
					manipulated = true;
					target.visible = true;
				}
				else if (vars->combat.manipulator
					&& (unity::GetKey((rust::classes::KeyCode)vars->keybinds.manipulator)
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
							*reinterpret_cast<Vector3*>(projshoot + 0x18) = rpc_position;
							if (misc::best_target != Vector3(0, 0, 0))
							{
								target_pos = misc::best_target;
								vis_fat = true;
							}
						}
					}
				}
			}
			target_pos.y += 0.2f;

			for (int i = 0; i < projectile_list->get_size(); i++) 
			{
				auto projectile = *(BaseProjectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				Vector3 a;
				misc::get_prediction(target, rpc_position, target_pos, original_vel, aimbot_velocity, a, travel_t, p);
				break;
			}

			for (int i = 0; i < size; i++) {
				auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);
				if (target.ent && (target.visible || manipulated || misc::autoshot) && !target.teammate) {
					*reinterpret_cast<Vector3*>(projectile + 0x24) = aimbot_velocity; //startvel
				}
			}

			for (int i = 0; i < projectile_list->get_size(); i++) {
				auto projectile = *(BaseProjectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);

				if (!projectile)
					continue;

				if (vars->combat.bullet_tp)
				{
					//check traveltime
					if (settings::desyncTime > travel_t)
						p->SetInitialDistance(target.distance);
					else if (settings::desyncTime > 0.f)
					{ 
						Vector3 r = rpc_position;
						Vector3 v = aimbot_velocity;
						Vector3 n = rpc_position + (aimbot_velocity * settings::desyncTime);
						p->SetInitialDistance(r.distance(n));
					}
					else p->SetInitialDistance(0);

					esp::local_player->console_echo(string::wformat(_(L"[trap]: ProjectileShoot (bullet tp) spawned bullet at distance %d"), (int)p->initialDistance()));
				}


				if (vars->combat.psilent || unity::GetKey(rust::classes::KeyCode(vars->keybinds.psilent))) {
					if (target.ent && !target.teammate) {
						if (target.visible || vis_fat)
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

				if (vars->combat.thick_bullet)
					*reinterpret_cast<float*>(projectile + 0x2C) = vars->combat.thickness > 1.f ? 1.f : vars->combat.thickness;
				else
					*reinterpret_cast<float*>(projectile + 0x2C) = 0.01f;
				
				p->integrity(1.f);
				float t = p->traveledTime();
				
				//create and SEND FAKE copy of projectile so game only updates original
				//Projectile* fake = new Projectile(*p);
				p->initialVelocity(aimbot_velocity);
				fired_projectile f = { p, nullptr, time, 1, target };
				
				//p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				//*reinterpret_cast<uintptr_t*>((uintptr_t)projectile_list + 0x20 + i * 0x8) = (uintptr_t)fake;
				
				for (size_t i = 0; i < 32; i++)
					if (misc::fired_projectiles[i].fired_at <= 10.f) {
						misc::fired_projectiles[i] = f;
						break;
					}

				if (vars->combat.manipulator2
					&& (unity::GetKey((rust::classes::KeyCode)vars->keybinds.manipulator)
						&& settings::RealGangstaShit != Vector3(0, 0, 0)))
				{
					p->currentVelocity(aimbot_velocity);
					p->initialVelocity(aimbot_velocity);
					p->previousVelocity(aimbot_velocity);

					p->currentPosition(rpc_position);
					p->previousPosition(rpc_position);
					p->sentPosition(rpc_position);
					p->prevSentVelocity(rpc_position); //?
				}

				if (vars->combat.targetbehindwall)
				{
					//((Projectile1*)p)->Launch1();
				}				
			}
			if (vars->combat.targetbehindwall)
			{
				typedef void(*cclear)(uintptr_t);
				((cclear)(mem::game_assembly_base + 13108368))((uintptr_t)baseprojectile + 0x370); //"System.Collections.Generic.List<Projectile>$$Clear",
			}

			if (misc::autoshot)
				misc::autoshot = false;
		} while (0);

		esp::local_player->console_echo(string::wformat(_(L"[trap]: ProjectileShoot (prediction) simulated %i times before hit!"), simulations));
		reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(hooks::orig::serverrpc_projectileshoot)(rcx, rdx, r9, projectileShoot, arg5);
		
		//calls base.serverrpc<projectileshoot>("clproject", x) ^^
		//loops through created projectiles and launches with
		//projectile.launch(); - this function has a while loop
		//based upon is alive? && (traveleddist < initialdist OR time < 0.1f)
		//while loop calls only UpdateVelocity(fixedDeltaTime);
		// 
		misc::fixed_time_last_shot = get_fixedTime();
		misc::just_shot = true;
		misc::did_reload = false;
	}

	void hk_serverrpc_playerprojectileupdate(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		auto  projectile = reinterpret_cast<Projectile*>(get_rbx_value());
		auto  ppu = reinterpret_cast<protobuf::PlayerProjectileUpdate*>(_ppa);

		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::playerprojectileupdate);

		//call fake domovement? after called set current position etc
		//projectile->DoMovement(misc::tickDeltaTime, projectile);
		//return;


		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

	void hk_serverrpc_playerprojectilericochet(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		auto        projectile = reinterpret_cast<Projectile*>(get_rbx_value());
		auto  ppa = reinterpret_cast<protobuf::PlayerProjectileRicochet*>(_ppa);
		

		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::playerprojectilericochet);

		//if (vars->combat.ricochet
		//	&& projectile->authoritative())
		//{
		//	Vector3 hitpos = ppa->hitPosition;
		//	Vector3 normal = ppa->hitNormal;
		//	Vector3 invel = ppa->inVelocity;
		//	Vector3 outvel = ppa->outVelocity;
		//
		//	Vector3 direction = outvel.Normalized();
		//
		//	Vector3 targetpos = esp::best_target.player->model()->boneTransforms()->get(48)->get_bone_position();
		//	Vector3 direction_to_target = targetpos - hitpos;
		//
		//	Vector3 newVelocity = direction_to_target.Normalized() * outvel.Length();
		//
		//	safe_write((uintptr_t)_ppa + 0x30, newVelocity, Vector3);
		//	projectile->currentVelocity(newVelocity);
		//	//safe_write((uintptr_t)ppa + 0x18, targetpos, Vector3);
		//
		//	Sphere(hitpos, 0.2f, col(1, 0.1, 0.2, 1), 10, 100);
		//}
		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

	void hk_serverrpc_playerprojectileattack(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		auto        projectile = reinterpret_cast<BaseProjectile*>(get_rbx_value());
		auto  ppa = reinterpret_cast<protobuf::PlayerProjectileAttack*>(_ppa);
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
			
			//Update((Projectile*)projectile); //many invalids with fat bullet manipulator as projectile position isnt updated before the hit

			auto hit_test = projectile->get_hit_test();
			if (!hit_test)
				break;

			if (!hit_test->gameObject())
				break;

			auto layer = hit_test->gameObject()->get_layer();
			auto prefab_name = hit_test->gameObject()->get_prefab_name();

			aim_target target = esp::best_target;//esp::local_player->get_aimbot_target(camera_pos);

			if (!target.ent)
				break;

			auto hit_entity = (BasePlayer*)hit_test->HitEntity();
			if (layer == rust::classes::layer::Player_Server) {
				if (hit_entity->is_teammate(esp::local_player)) {
					hit_test->ignoreEntity() = hit_entity;
					return;
				}
			}

			if (!vars->combat.hitbox_override)
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

			if (!target.is_heli && vars->combat.hitbox_override) {

				int hitbone = 698017942;
				int hitpartid = 2173623152;

				struct hitt {
					int64_t hitbone;
					int64_t partid;
				};

				srand(time(0));
				hitt test[7] = { 
					{ 0, 0 }, 
					{ 0, 0 }, 
					{ 0, 0 }, 
					{ 0, 0 }, 
					{ 0, 0 }, 
					{ 0, 0 }, 
					{ 0, 0 }, 
				};
				
				if (vars->combat.hitboxes.Head
					 && esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						 (int)rust::classes::Bone_List::head)->get_position(), projectile->get_current_position()))
					test[0] = { 698017942, 2173623152 };
				if (vars->combat.hitboxes.Body
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::pelvis)->get_position(), projectile->get_current_position()))
					test[1] = { 1031402764, 1750816991 };
				if (vars->combat.hitboxes.Upperbody
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::spine4)->get_position(), projectile->get_current_position()))
					test[2] = { 3901657145, 1750816991 };
				if (vars->combat.hitboxes.Hands
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::r_hand)->get_position(), projectile->get_current_position()))
					test[3] = { 102231371, 1750816991 };
				if (vars->combat.hitboxes.Penis
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::penis)->get_position(), projectile->get_current_position()))
					test[4] = { 612182976, 2173623152 };
				if (vars->combat.hitboxes.Legs
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::l_hip)->get_position(), projectile->get_current_position()))
					test[5] = { 3892428003, 1750816991 };
				if (vars->combat.hitboxes.Feet
					&& esp::local_player->is_visible(target.ent->model()->boneTransforms()->get(
						(int)rust::classes::Bone_List::r_foot)->get_position(), projectile->get_current_position()))
					test[6] = { 920055401, 1750816991 };

				int d = rand() % 6;
				int t = 0;
				while (test[d].hitbone == 0)
				{
					if (t++ > 100) {
						test[d] = { 698017942, 2173623152 };
						break;
					}
					srand(time(0));
					d = rand() % 7;
				}

				attack->hitBone = test[d].hitbone;
				attack->hitPartID = test[d].partid;
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else if (!target.is_heli) {
				switch (my_rand() % 10) {
				case 0: // Head
					attack->hitBone   = 698017942;
					attack->hitPartID = 2173623152;
					break;
				case 1: // Chest
					attack->hitBone	  = 1031402764;
					attack->hitPartID = 1750816991;
					break;
				case 2: // LHand
					attack->hitBone   = 182688154;
					attack->hitPartID = 1750816991;
					break;
				case 3: // RHand
					attack->hitBone   = 102231371;
					attack->hitPartID = 1750816991;
					break;
				case 4: // pelvis
					attack->hitBone   = 2811218643;
					attack->hitPartID = 1750816991;
					break;
				case 5: // r_hip
					attack->hitBone   = 2331610670;
					attack->hitPartID = 1750816991;
					break;
				case 6: // r_foot
					attack->hitBone   = 920055401;
					attack->hitPartID = 1750816991;
					break;
				case 7: // spine1
					attack->hitBone =   3771021956;
					attack->hitPartID = 1750816991;
					break;
				case 8: // l_upperarm
					attack->hitBone   = 3901657145;
					attack->hitPartID = 1750816991;
					break;
				case 9: // l_knee
					attack->hitBone   = 3892428003;
					attack->hitPartID = 1750816991;
					break;
				}
				attack->hitPositionLocal = { -.1f, -.1f, 0 };
				attack->hitNormalLocal = { 0, -1, 0 };
			}
			else {
				auto weakspots = ((BaseHelicopter*)target.ent)->weakspots();
				if (!weakspots)
					break;

				auto size = weakspots->get_size();//*reinterpret_cast<uintptr_t*>(weakspots + 0x18);

				bool tail_alive = false;
				bool main_alive = false;
				for (int i = 0; i < size; i++) {
					auto weakspot = weakspots->get(i);//*(uintptr_t*)(weakspots + 0x20 + i * 0x8);
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

			if (layer == rust::classes::layer::Deployed) {
				hit_test->ignoreEntity() = hit_entity;
				return;
			}
			//if (layer != rust::classes::layer::Player_Server) {
			//	hit_test->ignoreEntity() = hit_entity;
			//	return;
			//}
		} while (0);



		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

	void hk_serverrpc_doplace(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		//auto  planner = *reinterpret_cast<uintptr_t*>(get_rbx_value());
		auto  ppa = reinterpret_cast<protobuf::CreateBuilding*>(_ppa);

		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::createbuilding);

		if(!esp::local_player)
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		auto held = *reinterpret_cast<uintptr_t*>(esp::local_player + heldEntity);
		if (!held)
			return orig_fn(rcx, rdx, r9, _ppa, arg5);
		
		uintptr_t guide = *reinterpret_cast<uintptr_t*>(held + 0x210);

		if(!guide)
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		if (GetAsyncKeyState(0x38)) { 
			auto lastplacement = *reinterpret_cast<uintptr_t*>(guide + 0x18);
			auto position = *reinterpret_cast<Vector3*>(lastplacement + 0x34);
			auto normal = *reinterpret_cast<Vector3*>(lastplacement + 0x40);
			
			auto ogid = *reinterpret_cast<unsigned int*>(ppa + 0x14);

			*reinterpret_cast<unsigned int*>(ppa + 0x14) = esp::selected_entity_id;


			auto build_id = *reinterpret_cast<unsigned int*>(ppa + 0x14);
			auto tranny = esp::find_transform_by_id(build_id);
			if (tranny) {
				//transform* tr = get_transform((base_player*)FindEntity);
				//transform* Traaa = get_transform//FindEntity->_get_transform();
				*reinterpret_cast<Vector3*>(ppa + 0x20) = InverseTransformPoint((Transform*)tranny,		position);
				*reinterpret_cast<Vector3*>(ppa + 0x2C) = InverseTransformDirection((Transform*)tranny, normal);

				esp::local_player->console_echo(string::wformat(_(L"[trap] DoPlace - Spoofed %d to %d with position (%d, %d, %d)"), 
					(int)ogid,
					(int)esp::selected_entity_id,
					(int)position.x,
					(int)position.y,
					(int)position.z
				));
			}
		}
		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

	void hk_playerwalkmovement_ClientInput(PlayerWalkMovement* player_walk_movement, uintptr_t inputstate, ModelState* model_state) {
		orig::playerwalkmovement_client_input(player_walk_movement, inputstate, model_state);
		Vector3 vel = player_walk_movement->get_TargetMovement();
		auto loco = esp::local_player;
		auto dont_move = false;

		if (!loco || loco->is_sleeping())
			return;
		auto time = unity::get_realtimesincestartup();//UnityEngine::Time::get_realtimeSinceStartup();
		float _timeSinceLastTick = time - loco->lastSentTickTime();
		if (loco && !loco->is_sleeping() && settings::desyncTime < 0.f) {
			if (vars->misc.flyhack_stop) {
				Vector3 curr = esp::local_player->get_transform()->get_position();
				Vector3 old = misc::cLastTickPos;
				Vector3 v4 = (curr - misc::cLastTickPos);
				Vector3 ov = Vector3(curr.x, curr.y, curr.z);

				if (settings::vert_flyhack >= 2.5f)
					ov = Vector3(ov.x, curr.y < old.y ? (curr.y - 0.3f) : old.y, ov.z);
				if (settings::hor_flyhack >= 6.f)
					ov = Vector3(old.x, ov.y, old.z);

				if (settings::vert_flyhack >= 2.5f
					|| settings::hor_flyhack >= 6.f) {
  					if (ov != curr)
						player_walk_movement->teleport_to(ov, loco);
					dont_move = true;
				}
			}

			misc::cLastTickEyePos = esp::local_player->eyes()->get_position();//get_transform(esp::local_player)->get_bone_position();//baseplayer->eyes()->get_position();
			misc::cLastTickPos = esp::local_player->get_transform()->get_position();//_get_transform(esp::local_player)->get_position();//get_transform(esp::local_player)->get_bone_position();//baseplayer->eyes()->get_position();
			misc::ticks.AddPoint(misc::cLastTickPos);
			//misc::ServerUpdate(misc::tickDeltaTime, esp::local_player);
			misc::ServerUpdate(get_deltaTime(), esp::local_player);
		}
		else if (!loco || loco->is_sleeping())
		{
			settings::vert_flyhack = 0.f; settings::hor_flyhack = 0.f;
		}

		set_sprinting(model_state, true);
		flying = player_walk_movement->get_flying();

		if (vars->misc.silentwalk && vars->keybinds.silentwalk) {
			set_onLadder(model_state, true);
		}
		else set_onLadder(model_state, false);

		if (vars->misc.interactive_debug)
			model_state->set_flag(rust::classes::ModelState_Flag::Mounted);

		model_state->remove_flag(rust::classes::ModelState_Flag::Flying);

		float max_speed = (player_walk_movement->get_swimming() || player_walk_movement->get_ducking() > 0.5) ? 1.7f : 5.5f;
		if (vars->misc.always_sprint) {
			if (vel.length() > 0.f) {
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				player_walk_movement->set_TargetMovement(target_vel);
			}
		}

		if (unity::GetKeyDown(rust::classes::KeyCode::Space)
			&& vars->misc.infinite_jump)
		{
			misc::autobot::do_jump(player_walk_movement, model_state);
		}
		
		auto wpn = esp::local_player->GetActiveItem();
		auto held = wpn ? wpn->GetHeldEntity<BaseProjectile>() : nullptr;
		if (vars->combat.always_reload
			&& held)
		{
			misc::time_since_last_shot = (get_fixedTime() - misc::fixed_time_last_shot);
			settings::time_since_last_shot = misc::time_since_last_shot;
			if (misc::just_shot && (misc::time_since_last_shot > 0.2f))
			{
				held->ServerRPC(_(L"StartReload"));
				esp::local_player->console_echo(_(L"[trap]: ClientInput - starting reload"));
				//esp::local_player->SendSignalBroadcast(rust::classes::Signal::Reload); //does this cause animation? YES
				misc::just_shot = false;
			}
			float reloadtime = held->reloadTime();
			esp::rl_time = reloadtime;

			if (misc::time_since_last_shot > reloadtime //-10% for faster reloads than normal >:)
				&& !misc::did_reload)
			{
				esp::local_player->console_echo(_(L"[trap]: ClientInput - finishing reload"));
				held->ServerRPC(_(L"Reload"));
				misc::did_reload = true;
				misc::time_since_last_shot = 0;
			}
		}
		else
		{
			misc::time_since_last_shot = 0;
		}
		if (loco)
		{
			if(!loco->is_sleeping()){
				if (vars->misc.autofarm)
				{
					if(misc::node.ent == 0)
						misc::node.ent = (BaseEntity*)loco->find_closest(_("OreResourceEntity"), (Networkable*)loco, 200.f);
					misc::autobot::auto_farm(player_walk_movement);
				}
				else
				{
					misc::node.ent = 0;
					misc::node.path.clear();
					misc::node.pos = Vector3(0, 0, 0);
					misc::node.steps = 0;
				}
			}
		}

		if(dont_move)
			player_walk_movement->set_TargetMovement(Vector3(0, 0, 0));

		if (vars->misc.flywall)
		{
			if (unity::GetKey((rust::classes::KeyCode)vars->keybinds.flywall))
			{
				set_onLadder(model_state, true);
				if (settings::vert_flyhack > 1.5f
					|| settings::hor_flyhack > 4.f)
				{
					return;
				}
				else
					player_walk_movement->set_TargetMovement(Vector3(0, 25, 0));
			}
			else
			{
				set_onLadder(model_state, false);
			}
		}
	}

	void hk_projectile_launchprojectile(BaseProjectile* p)
	{
		if (vars->combat.doubletap)
		{
			auto held = esp::local_player->GetActiveItem()->GetHeldEntity<BaseProjectile>();
			auto m = held->repeatDelay() * .75f; //we can shoot 25% faster??? more bullets?? :DDD

			int r = settings::desyncTime / m;
			if (r > 1)
			{
				esp::local_player->console_echo(string::wformat(_(L"[trap]: Launching %d projectiles!"), r));
				for (size_t i = 0; i < r; i++)
				{
					orig::baseprojectile_launchprojectile((uintptr_t)p);

					auto mag = *reinterpret_cast<uintptr_t*>(p->primaryMagazine());
					auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
					*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);

					updateammodisplay((uintptr_t)p);
					shot_fired((uintptr_t)p);
					did_attack_client_side((uintptr_t)p);
				}
				return;
			}
		}

		if (misc::manual) {
			auto mag = *reinterpret_cast<uintptr_t*>(p->primaryMagazine());
			auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
			*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);

			updateammodisplay((uintptr_t)p);
			shot_fired((uintptr_t)p);
			did_attack_client_side((uintptr_t)p);
			misc::manual = false;
		}

		return orig::baseprojectile_launchprojectile((uintptr_t)p);
	}

	void hk_projectile_update(uintptr_t pr) {
		if (vars->combat.targetbehindwall) {
			return _update((Projectile*)pr);
			//((Projectile1*)pr)->Update();
		}
		else
			return _update((Projectile*)pr);
	}

	void hk_performance_update(void* instance) {
		if (wake) {
			__go = il2cpp::methods::object_new(il2cpp::init_class(_("GameObject"), _("UnityEngine")));
			
			gui::methods::create(__go, _(L""));
			gui::methods::add_component(__go, il2cpp::type_object(_(""), _("DevControls")));
			gui::methods::dont_destroy_on_load(__go);
			wake = false;
		}
		PerformanceUI_Update(instance);
	}

	void hk_baseplayer_ClientInput(BasePlayer* baseplayer, InputState* state) {

		//if(!do_fixed_update_ptr)
		//do_fixed_update_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("DoFixedUpdate"), &hk_dofixedupdate);

		if (!client_input_ptr)
			client_input_ptr = mem::hook_virtual_function(_("PlayerWalkMovement"), _("ClientInput"), &hk_playerwalkmovement_ClientInput);

		//static uintptr_t* serverrpc_projecshoot = 0;
		//if (!serverrpc_projecshoot) {
		//	auto method_serverrpc_projecshoot = *reinterpret_cast<uintptr_t*>(hooks::serverrpc_projecileshoot); //Method$BaseEntity.ServerRPC<ProjectileShoot>()
		//	typedef void(*CALL)(uintptr_t*, int64_t);
		//	((CALL)(mem::game_assembly_base + 0x2D9300))(&method_serverrpc_projecshoot, 0);
		//	if (method_serverrpc_projecshoot) {
		//		serverrpc_projecshoot = **(uintptr_t***)(method_serverrpc_projecshoot + 0x30);
		//
		//		hooks::orig::serverrpc_projectileshoot = *serverrpc_projecshoot;
		//
		//		*serverrpc_projecshoot = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_projectileshoot);
		//	}
		//}
		//static uintptr_t* serverrpc_projecattack = 0;
		//if (!serverrpc_projecattack) {
		//	auto method_serverrpc_projecattack = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileAttack___); //Method$BaseEntity.ServerRPC<ProjectileShoot>()
		//	typedef void(*CALL)(uintptr_t*, int64_t);
		//	((CALL)(mem::game_assembly_base + 0x2D9300))(&method_serverrpc_projecattack, 0);
		//	if (method_serverrpc_projecattack) {
		//		serverrpc_projecattack = **(uintptr_t***)(method_serverrpc_projecattack + 0x30);
		//
		//		hooks::orig::playerprojectileattack = *serverrpc_projecattack;
		//
		//		*serverrpc_projecattack = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_playerprojectileattack);
		//	}
		//}
		//
		//static uintptr_t* serverrpc_projecupdate = 0;
		//if (!serverrpc_projecupdate) {
		//	auto method_serverrpc_projecupdate = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileUpdate___); //Method$BaseEntity.ServerRPC<ProjectileShoot>()
		//	typedef void(*CALL)(uintptr_t*, int64_t);
		//	((CALL)(mem::game_assembly_base + 0x2D9300))(&method_serverrpc_projecupdate, 0);
		//	if (method_serverrpc_projecupdate) {
		//		serverrpc_projecupdate = **(uintptr_t***)(method_serverrpc_projecupdate + 0x30);
		//
		//		hooks::orig::playerprojectileupdate = *serverrpc_projecupdate;
		//
		//		*serverrpc_projecupdate = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_playerprojectileupdate);
		//	}
		//}

		if (!has_intialized_methods) {
			auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(il2cpp::methods::intialize_method);
			//56229 for real rust or 56204 for cracked rust
			for (int i = 0; i <
				56229//56204 //56229 = real rust
				; i++) {
				il2cpp_codegen_initialize_method(i);
			}
			has_intialized_methods = true;

			//HERE UNTIL THEY REMOVE IT AGAIN /S

			fired_projectile placeholder = { nullptr, 0, 1 };
			for (size_t i = 0; i < 32; i++)
				misc::fired_projectiles[i] = placeholder;
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

		//static uintptr_t* serverrpc_playerprojectileupdate;
		//if (!serverrpc_playerprojectileupdate) {
		//	auto method_serverrpc_playerprojectileupdate = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileUpdate___);//Method$BaseEntity_ServerRPC_PlayerProjectileAttack___
		//
		//	if (method_serverrpc_playerprojectileupdate) {
		//		serverrpc_playerprojectileupdate = **(uintptr_t***)(method_serverrpc_playerprojectileupdate + 0x30);
		//
		//		hooks::orig::playerprojectileupdate = *serverrpc_playerprojectileupdate;
		//
		//		*serverrpc_playerprojectileupdate = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_playerprojectileupdate);
		//	}
		//}
#pragma endregion

		if (baseplayer) {
			get_skydome();

			auto fixed_time = get_fixedTime();
			auto tick_time = baseplayer->lastSentTickTime();
			settings::desyncTime = (unity::get_realtimesincestartup() - tick_time) - 0.03125 * 3;

			auto wpn = baseplayer->GetActiveItem();

			auto held = wpn ? wpn->GetHeldEntity<BaseProjectile>() : nullptr;

			if (vars->misc.attack_on_mountables) {
				auto mountable = baseplayer->mounted();
				if (mountable)
					mountable->canwielditem() = true;
			}

			bool kyslol = false;

			if (vars->misc.TakeFallDamage && unity::GetKey(rust::classes::KeyCode(vars->keybinds.suicide))) {

				OnLand(baseplayer, -8.0001f - 100);
			}

			bool t1 = orig::isdown(state, rust::classes::BUTTON::FIRE_PRIMARY);
			auto t2 = orig::get_bodyleanoffset(baseplayer->eyes());

			if (vars->misc.admin_mode)
				baseplayer->set_admin_flag(rust::classes::PlayerFlags::IsAdmin);

			if (vars->misc.spiderman) {
				baseplayer->GroundAngleNew();
			}

			baseplayer->fov();

			if (held) {
				if (!LI_FIND(strcmp)(held->get_class_name(), _("Planner"))) {
					auto planner = reinterpret_cast<Planner*>(held);
					if (unity::GetKeyDown(rust::classes::KeyCode::RightArrow))
					{
						auto v = planner->rotationoffset();
						planner->rotationoffset(Vector3(v.x, v.y += 10, v.z));
						esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - rotate building right (%d, %d, %d)"), (int)v.x, (int)v.y, (int)v.z));
					}
					else if (unity::GetKeyDown(rust::classes::KeyCode::LeftArrow))
					{
						auto v = planner->rotationoffset();
						planner->rotationoffset(Vector3(v.x, v.y -= 10, v.z));
						esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - rotate building left (%d, %d, %d)"), (int)v.x, (int)v.y, (int)v.z));
					}
				}
			}

			float mm_eye = ((0.01f + ((settings::desyncTime + 2.f / 60.f + 0.125f) * baseplayer->max_velocity())));
			float time = get_fixedTime();
			if (esp::best_target.ent && held && wpn)
			{
				Vector3 target = esp::best_target.pos;//.player->model()->boneTransforms()->get(48)->get_bone_position();
				//Sphere(target, 0.05, col(0.8, 0.9, 0.3, 1), 0.05f, 10.f);

				auto getammo = [&](BaseProjectile* held)
				{
					if (held)
					{
						auto mag = *reinterpret_cast<uintptr_t*>(held->primaryMagazine());
						if (!mag) return 0;
						return *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
					}
					return 0;
				};

				auto mag_ammo = getammo(held);


				if (vars->combat.manipulator && ((unity::GetKey(rust::classes::KeyCode(vars->keybinds.manipulator)))
					|| misc::manipulate_vis))
				{
					float nextshot = misc::fixed_time_last_shot + held->repeatDelay();
					if (misc::can_manipulate(baseplayer, target, mm_eye))
						if (nextshot < time
							&& (held->timeSinceDeploy() > held->deployDelay() ||
								!strcmp(held->get_class_name(), _("BowWeapon")) ||
								!strcmp(held->get_class_name(), _("CompoundBowWeapon")) ||
								!strcmp(held->get_class_name(), _("CrossbowWeapon")))
							&& mag_ammo > 0)
						{
							auto v = esp::local_player->eyes()->get_position() + misc::best_lean;
							esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - manipulator attempted shot from position (%d, %d, %d) with desync of %d"), (int)v.x, (int)v.y, (int)v.z, (int)(settings::desyncTime * 100.f)));

							misc::manual = true;
							hk_projectile_launchprojectile(held);
							misc::best_target = Vector3(0, 0, 0);
							baseplayer->SendClientTick();
						}
				}

				if ((vars->combat.autoshoot || unity::GetKey(rust::classes::KeyCode(vars->keybinds.autoshoot))))
				{
					float nextshot = misc::fixed_time_last_shot + held->repeatDelay();
					//Sphere(target, 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
					//Sphere(baseplayer->model()->boneTransforms()->get(48)->get_bone_position(), 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
					if (baseplayer->is_visible(target, baseplayer->model()->boneTransforms()->get(48)->get_position())
						&& get_fixedTime() > nextshot
						&& held->timeSinceDeploy() > held->deployDelay()
						&& mag_ammo > 0)
					{
						misc::autoshot = true;
						hk_projectile_launchprojectile(held);
						updateammodisplay((uintptr_t)held);
						shot_fired((uintptr_t)held);
						did_attack_client_side((uintptr_t)held);
						*reinterpret_cast<int*>((uintptr_t) * reinterpret_cast<uintptr_t*>(held->primaryMagazine()) + 0x1C) = (mag_ammo - 1);
						baseplayer->SendClientTick();
					}
					else if (!baseplayer->is_visible(baseplayer->model()->boneTransforms()->get(48)->get_position(), target)
						//&& get_fixedTime() > nextshot
						&& vars->combat.manipulator
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



			if (unity::GetKey(rust::classes::KeyCode(vars->keybinds.desync_ok))
				|| (vars->combat.manipulator
					&& (unity::GetKey(rust::classes::KeyCode(vars->keybinds.manipulator))
						|| misc::manipulate_vis)))
				baseplayer->clientTickInterval() = 0.99f;
			else if (!is_lagging && !is_speeding)
				baseplayer->clientTickInterval() = 0.05f;


			if (!keybinds::fakelagb || unity::GetKey(keybinds::fakelagk)) {
				if (!is_lagging && !flying && vars->misc.fake_lag && !is_speeding) {
					baseplayer->clientTickInterval() = 0.4f;
					is_lagging = true;
				}
			}
			else if (is_lagging && flying || is_lagging && is_speeding) {
				esp::local_player->clientTickInterval() = 0.03f;
				is_lagging = false;
			}
			else if (is_lagging && !vars->misc.fake_lag) {
				esp::local_player->clientTickInterval() = 0.05f;
				is_lagging = false;
			}

			if (vars->misc.eyeoffset || unity::GetKey((rust::classes::KeyCode)vars->keybinds.neck))
			{
				baseplayer->eyes()->set_view_offset(Vector3(0, vars->misc.PlayerEyes, 0));
			}

			if (auto movement = baseplayer->movement()) {
				if (vars->misc.spiderman) {
					movement->set_ground_angles_new(-1);
				}
				if (vars->misc.infinite_jump) {
					movement->set_land_time(0);
					movement->set_jump_time(0);
					movement->set_ground_time(100000);
				}

				if (vars->misc.gravity)
					movement->set_gravity_multiplier(1.75f);
				else
					movement->set_gravity_multiplier(2.35f);

				if (vars->combat.always_shoot) {
					if (auto ModelState = baseplayer->modelState()) {
						ModelState->set_flag(rust::classes::ModelState_Flag::OnGround);
						mem::write<float>((uint64_t)movement + 0x4C, 1); //private float <Grounded>k__BackingField; // 0x4C
					}
				}
			}

			auto item = baseplayer->GetActiveItem();


			if (vars->misc.speedhack || unity::GetKey(rust::classes::KeyCode(vars->keybinds.timescale))) {
				set_timeScale(vars->misc.speedhackspeed);
				is_speeding = true;
			}
			else {
				set_timeScale(1);
				is_speeding = false;
			}

			auto target = esp::best_target; //baseplayer->get_aimbot_target(unity::get_camera_pos());
			if (item) {
				auto baseprojectile = item->GetHeldEntity<BaseProjectile>();
				if (baseprojectile) {
					for (int i = 0; i < 32; i++) {
						auto current = misc::fired_projectiles[i];
						if (current.fired_at <= 2.f)
							continue;
						//kill original so no updates wasted by game
						//auto original = current.original;

						auto projectile = current.original;
						if (!projectile->authoritative())
							continue;

						//we will be the ones who update the projectile, not the game
						//auto delta = get_deltaTime();
						//auto updates = current.updates++;
						//auto next_update_time = current.fired_at + (updates * delta);
						//bool ret = false;
						//if (get_fixedTime() > next_update_time)
						//	if (projectile->IsAlive())
						//	{
						//		projectile->UpdateVelocity(delta, projectile);
						//	}

						float offset = 0.f;
						auto target = current.ent;
						if (vars->combat.thick_bullet
							&& projectile->authoritative()
							&& projectile->IsAlive())
							//&& vars->combat.thickness > 1.1f)//)
						{
							if (target.ent)
							{
								auto current_position = projectile->get_transform()->get_position();

								//transform* bonetrans = target.player->find_closest_bone(current_position, true
								Transform* bonetrans = target.ent->model()->boneTransforms()->get(48);

								if (bonetrans)
								{
									if (vars->combat.bodyaim)
										bonetrans = target.ent->model()->boneTransforms()->get((int)rust::classes::Bone_List::pelvis);


									Vector3 target_bone = bonetrans->get_position(); //target_bone.y -= 0.8f;
									//Sphere(target_bone, 2.2f, col(12, 150, 100, 50), 10.f, 100.f);

									if (misc::LineCircleIntersection(target_bone, vars->combat.thickness, current_position, projectile->previousPosition(), offset))
									{
										current_position = Vector3::move_towards(target_bone, current_position, vars->combat.thickness);
									}

									auto dist = target_bone.distance(current_position);


									//fuck with shit pussy wagon
									float num2 = 1.0f + 0.5f;
									float num8 = 2.0f / 60.0f;
									float num9 = 2.0f * max(max(get_deltaTime(), get_smoothdeltaTime()), get_fixeddeltaTime());
									float num11 = (settings::desyncTime + num8 + num9) * num2;
									//typedef Vector3(*gpv)(uintptr_t);
									//auto pv = ((gpv)(mem::game_assembly_base + 8331264))((uintptr_t)target.player);
									auto pv = target.ent->GetParentVelocity();
									float mag = pv.length();
									float num15 = 0.1f + num11 * mag + 0.1f;
									//dist -= num15;

									/*if (target.player->get_mountable())
									{
										Sphere(target_bone, 3.0f, col(12, 150, 100, 50), 10.f, 100.f);
										if (dist < 3.0f)
										{
											auto newpos = Vector3::move_towards(target_bone, current_position, 1.0f);
											set_position(get_transform((base_player*)projectile), newpos);

											HitTest* ht = (HitTest*)projectile->hitTest();
											ht->set_did_hit(true);
											ht->set_hit_entity(target.player);
											ht->set_hit_transform(bonetrans);
											ht->set_hit_point(InverseTransformPoint(bonetrans, newpos));
											ht->set_hit_normal(InverseTransformDirection(bonetrans, newpos));
											Ray r(get_position((uintptr_t)get_transform((base_player*)projectile)), newpos);
											safe_write(ht + 0x14, r, Ray);

											esp::local_player->console_echo(string::wformat(_(L"[trap]: Fat bullet - Called with distance: %dm"), (int)dist));
											DoHit(projectile, ht, newpos, HitNormalWorld((uintptr_t)ht));
										}
									}*/
									if (dist < 2.0f)
									{
										auto newpos = Vector3::move_towards(current_position, target_bone, 1.0f);
										set_position(projectile->get_transform(), newpos);


										HitTest* ht = (HitTest*)projectile->hitTest();
										ht->DidHit() = true;
										ht->HitEntity() = target.ent;
										ht->HitTransform() = bonetrans;
										ht->HitPoint() = InverseTransformPoint(bonetrans, newpos);
										ht->HitNormal() = InverseTransformDirection(bonetrans, newpos);
										Ray r(projectile->get_transform()->get_position(), newpos);
										safe_write(ht + 0x14, r, Ray);
										DoHit(projectile, ht, newpos, HitNormalWorld((uintptr_t)ht));
									}
								}
							}
						}
						else if (time - current.fired_at > 8.f) {
							misc::fired_projectiles[i] = { nullptr, nullptr, 1, 0 };
						}
					}

					//for (int i = 0; i < 32; i++)
					//{
					//	bool ret = false;
					//	auto current = misc::fired_projectiles[i];
					//	if (current.fired_at < 1.f)
					//		continue;
					//	auto updates = current.updates;
					//	float update_time = current.fired_at + (updates * 0.03125f);
					//	current.updates = updates + 1;
					//
					//
					//	//LI_FIND(fprintf)(stdout,
					//	//	_("Projectile [%i]:\nUpdates: %i\nUpdate time: %.2f\n"),
					//	//	i,
					//	//	updates,
					//	//	update_time);
					//
					//
					//	if (time < update_time)
					//		continue;
					//	float lifetime = time - current.fired_at;
					//	if (current.pr->IsAlive())
					//		current.pr->UpdateVelocity(0.03125f, current.pr, ret);
					//	//current.pr->UpdateVelocity(get_fixeddeltaTime(), current.pr, ret);
					//	else {
					//		//has died
					//		//Retire(current->pr);
					//		misc::fired_projectiles[i] = { nullptr, 0, 0 };
					//		continue;
					//	}
					//	if (lifetime > 8.f) {
					//		//Retire(current->pr);
					//		misc::fired_projectiles[i] = { nullptr, 0, 0 };
					//		continue;
					//	}
					//}

					auto wep_class_name = *(const char**)(*(uintptr_t*)(uintptr_t)baseprojectile + 0x10);

					auto attack = [&](aim_target target, bool is_tree) {
						auto gathering = ((BaseMelee*)baseprojectile)->gathering();

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

					if (target.ent
						&& target.visible
						&& vars->combat.aimbot
						&& unity::GetKey((rust::classes::KeyCode)vars->keybinds.aimbot))
					{
						//predict aiming direction
						//
						// normalize angles
						// smooth angles
						// set bodyangles to result
						//
						Vector3 eyes = esp::local_player->eyes()->get_position();
						Vector3 aim_dir;
						Vector3 aim_vel;

						auto m = *reinterpret_cast<uintptr_t*>((uintptr_t)baseprojectile + 0x2C0); //public BaseProjectile.Magazine primaryMagazine; // 0x2C0
						auto ammo = *reinterpret_cast<uintptr_t*>((uintptr_t)m + 0x20); //public ItemDefinition ammoType; // 0x20
						auto mod = ((Networkable*)ammo)->GetComponent(unity::GetType(_(""), _("ItemModProjectile")));
						auto projectile = (Projectile*)((Networkable*)mod)->GetComponent(unity::GetType(_(""), _("Projectile")));

						//auto v = projectile->initialVelocity();//((base_projectile*)projectile)->get_item_mod_projectile()->get_projectile_velocity();
						//auto v1 = ((base_projectile*)projectile)->projectileVelocityScale();
						//if (vars->combat.fast_bullet)
						//	v1 *= 1.49f;
						//v *= v1;
						auto vel = projectile->initialVelocity();
						//auto vel = (getmodifiedaimcone(0, eyes - target.pos, true)).Normalized() * v;

						//misc::get_prediction(target, eyes, target.pos, vel, aim_vel, aim_dir, (Projectile*)projectile, true);


						Vector3 va = baseplayer->input()->bodyAngles();
						Vector2 vb = { va.x, va.y };

						auto calc = [&](const Vector3& src, const Vector3& dst) {
							Vector3 d = src - dst;
							return Vector2(RAD2DEG(Vector3::my_asin(d.y / d.length())), RAD2DEG(-Vector3::my_atan2(d.x, -d.z)));
						};
						auto normalize = [&](float& yaw, float& pitch) {
							if (pitch < -270) pitch = -270;
							else if (pitch > 180) pitch = 180;
							if (yaw < -360) yaw = -360;
							else if (yaw > 360) yaw = 360;
							//esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - yaw: %d, pitch: %d"), (int)yaw, (int)pitch));
						};
						auto step = [&](Vector2& angles) {
							bool smooth = true;
							Vector3 v = va;
							Vector2 va = { v.x, v.y };
							Vector2 angles_step = angles - va;
							normalize(angles_step.x, angles_step.y);

							if (smooth) {
								float factor_pitch = vars->combat.aimbot_smooth;
								if (angles_step.x < 0.f) {
									if (factor_pitch > std::fabs(angles_step.x)) {
										factor_pitch = std::fabs(angles_step.x);
									}
									angles.x = va.x - factor_pitch;
								}
								else {
									if (factor_pitch > angles_step.x) {
										factor_pitch = angles_step.x;
									}
									angles.x = va.x + factor_pitch;
								}
							}
							if (smooth) {
								float factor_yaw = vars->combat.aimbot_smooth;
								if (angles_step.y < 0.f) {
									if (factor_yaw > std::fabs(angles_step.y)) {
										factor_yaw = std::fabs(angles_step.y);
									}
									angles.y = va.y - factor_yaw;
								}
								else {
									if (factor_yaw > angles_step.y) {
										factor_yaw = angles_step.y;
									}
									angles.y = va.y + factor_yaw;
								}
							}
						};

						Vector2 offset = calc(eyes, target.pos) - vb;
						Vector2 ai = vb + offset;
						step(ai);
						step(ai);
						normalize(ai.x, ai.y);
						Vector3 i = { ai.x, ai.y, 0.0f };
						baseplayer->input()->bodyAngles() = i;
					}

					if (vars->misc.silent_farm) {
						auto entity = baseplayer->resolve_closest_entity(3, false);
						if (entity.first.found && entity.first.ent) {
							if (*(int*)(wep_class_name + 4) == 'eleM' || *(int*)(wep_class_name + 4) == 'mmah') {
								attack(entity.first, entity.second);
							}
						}
					}

					if (!(*(int*)(wep_class_name + 4) == 'eleM' && *(int*)(wep_class_name) == 'esaB')) {
						if (unity::GetKey(rust::classes::KeyCode::Mouse0) && vars->misc.instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								auto time = get_time();
								if (baseprojectile->timeSinceDeploy() > baseprojectile->deployDelay() && baseprojectile->nextAttackTime() <= get_time()) {
									if (time > nextActionTime) {
										nextActionTime = time + period;
										baseprojectile->ServerRPC(_(L"UseSelf"));
									}
								}
							}
						}
						else if (unity::GetKey(rust::classes::KeyCode::Mouse1) && vars->misc.instant_med) {
							const auto item_id = item->get_item_definition_id();

							if (item_id == 1079279582 || item_id == -2072273936) {
								esp::matrix = unity::get_view_matrix();
								auto camera_pos = unity::get_camera_pos();

								auto target = esp::best_target; //baseplayer->get_aimbot_target(camera_pos);

								if (target.ent && target.distance < 5) {
									auto net = *reinterpret_cast<Networkable**>((uintptr_t)target.ent + 0x58);
									if (net) {
										auto id = net->get_id();
										if (id) {
											auto method_addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_uint);
											if (method_addr) {
												auto time = get_time();
												if (baseprojectile->timeSinceDeploy() > baseprojectile->deployDelay() && baseprojectile->nextAttackTime() <= get_time()) {
													if (time > nextActionTime) {
														nextActionTime = time + period;
														ServerRPC_int(baseprojectile, System::string(_(L"UseOther")), id, method_addr);
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
									mem::write<float>((uint64_t)baseprojectile + 0x378, 1.f); //eoka success fraction
									mem::write<bool>((uint64_t)baseprojectile + 0x388, true); //eoka _didSparkThisFrame
									break;
								default:
									if (vars->combat.fast_bullet)
										if (item_id != 1318558775)
											baseprojectile->projectileVelocityScale() = 1.49f;
									if (vars->combat.rapidfire)
										baseprojectile->repeatDelay() = 0.02f;
									if (vars->combat.automatic)
										baseprojectile->automatic() = true;
									if (vars->combat.nospread)
										baseprojectile->set_no_spread();
									baseprojectile->set_recoil();
									break;

								}
							}
						}
					}
				}
			}

			if (vars->misc.instant_revive) {

				if (target.ent)
				{
					esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - sending RPC_Assist to player %s"), ((BasePlayer*)target.ent)->_displayName()));

					if (!target.is_heli && target.ent && target.distance <= 5 && target.ent->health() <= 4 && target.visible)
						target.ent->ServerRPC(_(L"RPC_Assist"));
				}
			}

			if (vars->misc.gesture_spam > 1
				&& get_fixedTime() > last_gesture_rpc + 0.35f)
			{
				switch (vars->misc.gesture_spam) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"clap"));
					break;
				case 3:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"friendly"));
					break;
				case 4:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"thumbsdown"));
					break;
				case 5:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"thumbsup"));
					break;
				case 6:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"ok"));
					break;
				case 7:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"point"));
					break;
				case 8:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"shrug"));
					break;
				case 9:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"victory"));
					break;
				case 10:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"wave"));
					break;
				case 11:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"dance.cabbagepatch"));
					break;
				case 12:
					esp::local_player->SendSignalBroadcast(rust::classes::Signal::Gesture, _(L"dance.twist"));
					break;
				}
				last_gesture_rpc = get_fixedTime();
			}

			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Water, !vars->misc.no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Tree, vars->misc.no_playercollision);
			unity::IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::AI, vars->misc.no_playercollision);

			draw_get();
			if (tick_time > gui::tick_time_when_called + 10) {
				unity::camera = unity::get_main_camera();
				gui::tick_time_when_called = tick_time;
			}
			
			if (vars->combat.manipulator2 && ((unity::GetKey(rust::classes::KeyCode(vars->keybinds.manipulator)))
				|| misc::manipulate_vis))
			{
				if (wpn && held && esp::best_target.ent) {
					auto getammo = [&](BaseProjectile* held)
					{
						if (held)
						{
							auto mag = *reinterpret_cast<uintptr_t*>(held->primaryMagazine());
							if (!mag) return 0;
							return *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
						}
						return 0;
					};

					auto mag_ammo = getammo(held);

					float nextshot = misc::fixed_time_last_shot + held->repeatDelay();
					if (CanManipulate(held, (BasePlayer*)esp::best_target.ent, state))
						if (nextshot < time
							&& (held->timeSinceDeploy() > held->deployDelay() ||
								!strcmp(held->get_class_name(), _("BowWeapon")) ||
								!strcmp(held->get_class_name(), _("CompoundBowWeapon")) ||
								!strcmp(held->get_class_name(), _("CrossbowWeapon")))
							&& mag_ammo > 0)
						{
							auto v = settings::RealGangstaShit;//esp::local_player->eyes()->get_position() + misc::best_lean;
							esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - manipulator2 attempted shot from position (%d, %d, %d) with desync of %d"), (int)v.x, (int)v.y, (int)v.z, (int)(settings::desyncTime * 100.f)));

							misc::manual = true;
							hk_projectile_launchprojectile(held);
							baseplayer->SendClientTick();
						}
				}
			}

			orig::baseplayer_client_input(baseplayer, state);

			auto model_state = baseplayer->modelState();

			//model_state->set_water_level(99999);

			if (vars->misc.spinbot) {
				state->set_aim_angles(Vector3(100, my_rand() % 999 + -999, 100));
			}

			if (vars->misc.autofarm) {
				if (misc::node.pos != Vector3(0, 0, 0))
				{
					auto dir = (misc::node.pos - baseplayer->eyes()->get_position()).Normalized();
					state->set_aim_angles(dir);
				}
			}
		}
	}
}
