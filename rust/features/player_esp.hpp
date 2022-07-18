#pragma once
#include <array>
#include <cstdint>

#include "../../memory/il2cpp.hpp"
#include "../../settings.hpp"

#include "../classes.hpp"
#include "../rust.hpp"

namespace esp {
	unsigned int selected_entity_id;
	float time_last_upgrade = 0.f;
	float rl_time = 0.f;
	uintptr_t client_entities;
	base_player* local_player;
	VMatrix matrix;
	aim_target best_target = aim_target();
	uintptr_t closest_building_block = 0;

	struct bounds_t {
		float left, right, top, bottom;
	};

	struct rust_str
	{
		char zpad[128];
	};

	bool out_w2s(const Vector3& position, Vector2& screen_pos) {
		if (!matrix.m) {
			return false;
		}

		Vector2 out;
		const auto temp = matrix.transpose();

		auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
		auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
		auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

		float w = translation_vector.dot(position) + temp[3][3];

		if (w < 0.098f) {
			return false;
		}

		float x = up.dot(position) + temp._24;
		float y = right.dot(position) + temp._14;

		out.x = (static_cast<float>(unity::get_width()) / 2) * (1 + y / w);
		out.y = (static_cast<float>(unity::get_height()) / 2) * (1 - x / w);

		screen_pos = out;

		return true;
	}

	//struct str
	//{
	//	char buffer[128];
	//};

	void draw_heli(float x, float y, float w, float h);

	void draw_tool_cupboard(Vector2 w2s_position, uintptr_t label, Vector4 color, rust::list<PlayerNameID*>* authorizedPlayers_list);

	void draw_hackable_crate(Vector2 w2s_position, uintptr_t crate, Vector4 color);

	void draw_item(Vector2 w2s_position, uintptr_t label, Vector4 color, wchar_t* name = _(L""));

	void draw_player(base_player* player, bool is_npc);

	void do_chams(base_player* player);

	void draw_target_hotbar(aim_target target);

	void draw_name(Vector3 position, wchar_t* name);

	void draw_middle(aim_target target);

	void draw_weapon_icon(weapon* item, Vector2 w2s_position);

	void offscreen_indicator(Vector3 position);

	void draw_target_fov(col color, Vector2 o, float r);

	uintptr_t shader;

	float last_recycler = 0.f;

	void iterate_players(bool draw = true) {
		//best_target = ;
		auto get_client_entities = [&]() {
			client_entities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
		};
		if (!client_entities)
			get_client_entities();

		rust::classes::list* entity_list = (rust::classes::list*)client_entities;

		auto list_value = entity_list->get_value<uintptr_t>();
		if (!list_value) {
			get_client_entities();
			return;
		}

		auto size = entity_list->get_size();
		if (!size) {
			get_client_entities();
			return;
		}

		auto buffer = entity_list->get_buffer<uintptr_t>();
		if (!buffer) {
			get_client_entities();
			return;
		}

		for (int i = 0; i <= size; i++) {
			auto current_object = *reinterpret_cast<uintptr_t*>(buffer + 0x20 + (i * 0x8));
			if (!current_object || current_object <= 100000)
				continue;

			auto base_object = *reinterpret_cast<uintptr_t*>(current_object + 0x10);
			if (!base_object || base_object <= 100000)
				continue;

			auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
			if (!object || object <= 100000)
				continue;

			WORD tag = *reinterpret_cast<WORD*>(object + 0x54);

			bool is_looking_at_entity = false;

			auto do_melee_attack = [&](base_projectile* baseprojectile)
			{
				auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);

				auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
				auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);

				auto attack = [&](bool is_tree) {
					auto _class = *reinterpret_cast<uintptr_t*>(base_object + 0x30);

					auto game_object = *reinterpret_cast<uintptr_t*>(_class + 0x30);

					auto transform = *reinterpret_cast<uintptr_t*>(game_object + 0x8);
					auto visual_state = *reinterpret_cast<uintptr_t*>(transform + 0x38);


					auto world_position = *reinterpret_cast<Vector3*>(visual_state + 0x90);

					auto local = ClosestPoint(esp::local_player, world_position);
					if (local.get_3d_dist(world_position) >= 5)
						return;

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

					aim_target target;

					target.pos = world_position;
					target.player = (base_player*)ent;
					target.visible = true;
					attack_melee(target, baseprojectile);
				};

				auto name = *(int*)(entity_class_name);

				if (name == 'eerT') {
					attack(true);
				}
				else if (name == 'HerO') {
					attack(false);
				}
			};

			auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);
			if (!ent)
				continue;

			auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
			if (!ent_class)
				continue;

			auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);
			if (!entity_class_name)
				continue;

			Vector4 esp_color(1, 0, 1, 1);
			uintptr_t esp_name;

			auto game_object = *reinterpret_cast<uintptr_t*>(object + 0x30);
			if (!game_object)
				continue;

			auto transform = *reinterpret_cast<uintptr_t*>(game_object + 0x8);
			if (!transform)
				continue;

			auto visual_state = *reinterpret_cast<uintptr_t*>(transform + 0x38);
			if (!visual_state)
				continue;

			auto world_position = *reinterpret_cast<Vector3*>(visual_state + 0x90);
			if (world_position.is_empty())
				continue;

			uintptr_t object_name_ptr = mem::read<uintptr_t>(object + 0x60);
			if (!object_name_ptr)
				continue;

			auto object_name = *reinterpret_cast<rust_str*>(object_name_ptr);
			if (!object_name.zpad)
				continue;

			auto ent_net = *reinterpret_cast<networkable**>(ent + 0x58);
			auto ent_id = ent_net->get_id();

			if (local_player && GetAsyncKeyState(0x37))
			{
				auto look = local_player->get_lookingat_entity();
				if (look)
				{
					auto net2 = *reinterpret_cast<networkable**>(look + 0x58);
					auto look_id = net2->get_id();
					if (look_id == ent_id)
					{
						//is_looking_at_entity = true;
						selected_entity_id = ent_id;
					}
				}
			}


			if (*(int*)(entity_class_name) == 'kcaH' && *(int*)(entity_class_name + 14) == 'tarC') {
				auto flag = *reinterpret_cast<int*>(ent + 0x128);
				if (flag != 128 && flag != 256)
					continue;

				Vector2 w2s_position = {};
				if (out_w2s(world_position, w2s_position))
					esp::draw_hackable_crate(w2s_position, ent, { 0.45, 0.72, 1, 0.8 });
			}

			if (vars->misc.auto_upgrade && local_player)
			{
				if (!LI_FIND(strcmp)(entity_class_name, _("BuildingBlock")))
				{
					auto lpos = get_position((uintptr_t)get_transform(local_player));
					float dist_to_new = lpos.distance(world_position);
					if (!closest_building_block)
						closest_building_block = ent;
					else if (dist_to_new < lpos.distance(get_position((uintptr_t)get_transform((base_player*)closest_building_block))))
						closest_building_block = ent;
				}
			}


			if (vars->visual.misc_esp) {
				if (*(int*)(entity_class_name) == 'porD') {
					if (!vars->visual.dropped_items)
						continue;

					if (*(int*)(entity_class_name + 40) == 'kcab')
						continue;

					if (*(int*)(object_name.zpad) == 'orra')
						continue;

					if (*(int*)(object_name.zpad + 12) == 'ian.')
						continue;

					auto Item = *reinterpret_cast<uintptr_t*>(ent + 0x170); //public Item item; // 0x170
					if (!Item)
						continue;

					auto item = reinterpret_cast<weapon*>(Item);

					auto item_name = item->get_weapon_name();

					esp_color = Vector4(196, 124, 0, 255);

					Vector2 w2s_position = {};
					if (out_w2s(world_position, w2s_position))
						draw_weapon_icon(item, w2s_position);
					//esp::draw_item(w2s_position, 0, esp_color, item_name);

					continue;
				}

				//if (*(int*)(entity_class_name) == 'ddaL') {
				if (vars->visual.ladder && !strcmp(entity_class_name, _("BaseLadder"))) {
					esp_name = il2cpp::methods::new_string(_("Ladder"));
					esp_color = Vector4(0, 219, 58, 255);

					Vector2 w2s_position = {};
					if (out_w2s(world_position, w2s_position))
						esp::draw_item(w2s_position, esp_name, esp_color);

					w2s_position.y += 10;
					if (selected_entity_id == ent_id)
						esp::draw_item(w2s_position, il2cpp::methods::new_string(("[selected]")), esp_color);
				}

				if (vars->visual.tc_esp && *(int*)(entity_class_name) == 'liuB' && *(int*)(entity_class_name + 8) == 'virP') {

					//rpc stuf

					auto authorizedPlayers_wrapper = *reinterpret_cast<uintptr_t*>(ent + 0x598);
					if (!authorizedPlayers_wrapper)
						continue;
					const auto authorizedPlayers_list = *reinterpret_cast<rust::list<PlayerNameID*>**>(authorizedPlayers_wrapper + 0x10);
					if (!authorizedPlayers_list)
						continue;

					Vector2 w2s_position = {};
					if (out_w2s(world_position, w2s_position))
						esp::draw_tool_cupboard(w2s_position, il2cpp::methods::new_string(_("Tool Cupboard")), Vector4(255, 0, 0, 255), authorizedPlayers_list);

					w2s_position.y -= 10;
					if (selected_entity_id == ent_id)
						esp::draw_item(w2s_position, il2cpp::methods::new_string(("[selected]")), esp_color);
				}


				if (*(int*)(entity_class_name + 4) == 'ileH' && vars->visual.heli_esp) {
					auto base_heli = reinterpret_cast<base_player*>(ent);

					Vector2 rearrotor, beam, mainrotor;
					out_w2s(base_heli->get_bone_transform(22)->get_bone_position(), rearrotor);
					out_w2s(base_heli->get_bone_transform(19)->get_bone_position(), mainrotor);
					out_w2s(base_heli->get_bone_transform(56)->get_bone_position(), beam);
					esp_name = il2cpp::methods::new_string(("Heli"));
					esp_color = Vector4(232, 232, 232, 255);

					uintptr_t transform = mem::read<uintptr_t>(base_heli->get_model() + 0x48); //boneTransforms; // 0x48

					const Vector2 diff = { (beam.x + rearrotor.x) / 2, (beam.y + rearrotor.y) / 2 };

					const float h = max(beam.y, rearrotor.y) - min(beam.y, rearrotor.y);
					const float y = diff.y;
					const float w = (max(beam.x, rearrotor.x) - min(beam.x, rearrotor.x));
					float x = diff.x - h / 4;

					Vector2 w2s_position = {};
					if (out_w2s(world_position, w2s_position))
						esp::draw_item(w2s_position, esp_name, esp_color);

					draw_heli(x, y, w, h);
				}

				if (vars->visual.stash && *(int*)(object_name.zpad + 46) == '_hsa') {
					esp_name = il2cpp::methods::new_string(_("Stash"));
				}
				else if (vars->misc.norecycler && *(int*)(entity_class_name) == 'yceR' && get_fixedTime() > last_recycler + 0.35f) {
					esp_name = il2cpp::methods::new_string(_("Recycler"));
					esp_color = Vector4(232, 232, 232, 255);
					if (esp::local_player->get_bone_transform(48)->get_bone_position().distance(world_position) < 4.5f)
					{
						unity::ServerRPC(ent, _(L"SVSwitch"));
						last_recycler = get_fixedTime();
					}
				}
				else if (vars->visual.stone_ore && (*(int*)(object_name.zpad + 52) == 'nots' || *(int*)(object_name.zpad + 47) == 'nots')) {
					esp_name = il2cpp::methods::new_string(_("Stone Ore"));
					esp_color = Vector4(232, 232, 232, 255);
				}
				else if (vars->visual.sulfur_ore && (*(int*)(object_name.zpad + 52) == 'flus' || *(int*)(object_name.zpad + 47) == 'flus')) {
					esp_name = il2cpp::methods::new_string((_("Sulfur Ore")));
					esp_color = Vector4(203, 207, 0, 255);
				}
				else if (vars->visual.metal_ore && (*(int*)(object_name.zpad + 52) == 'atem' || *(int*)(object_name.zpad + 47) == 'atem')) {
					esp_name = il2cpp::methods::new_string(_("Metal Ore"));
					esp_color = Vector4(145, 145, 145, 255);
				}
				else if (vars->visual.traps && (*(int*)(object_name.zpad + 36) == 'terr' || *(int*)(object_name.zpad + 43) == 'tnug' || *(int*)(object_name.zpad + 38) == 'rtra')) {
					if (*(int*)(object_name.zpad + 36) == 'terr')
						esp_name = il2cpp::methods::new_string(_("Auto Turret*"));
					else if (*(int*)(object_name.zpad + 43) == 'tnug')
						esp_name = il2cpp::methods::new_string(_("Shotgun Trap*"));
					else if (*(int*)(object_name.zpad + 38) == 'rtra')
						esp_name = il2cpp::methods::new_string(_("Bear Trap*"));

					esp_color = Vector4(255, 166, 0, 255);
				}
				else if (vars->visual.vehicles && *(int*)(entity_class_name + 4) == 'iheV') {
					esp_name = il2cpp::methods::new_string(_("Vehicle"));
					esp_color = Vector4(0, 161, 219, 255);
				}
				else if (vars->visual.airdrops && *(int*)(object_name.zpad + 39) == 'pord') {
					esp_name = il2cpp::methods::new_string(_("Airdrop"));
					esp_color = Vector4(0, 161, 219, 255);
				}
				else if (vars->visual.cloth && *(int*)(object_name.zpad + 52) == 'c-pm') {
					esp_name = il2cpp::methods::new_string(_("Cloth"));
					esp_color = Vector4(0, 219, 58, 255);
				}
				else if (vars->visual.corpses && *(int*)(object_name.zpad + 29) == 'proc') {
					esp_name = il2cpp::methods::new_string(_("Player Corpse"));
					esp_color = Vector4(230, 230, 230, 255);
				}
				else if (tag != 6)
					continue;


				if (tag != 6) {
					if (*(int*)(entity_class_name) == 'satS') {
						auto flag = *reinterpret_cast<int*>(ent + 0x128);
						if (flag != 2048)
							continue;
					}
					//auto s = il2cpp::methods::new_string(string::format(_("[%dm]"), (int)local_player->get_player_eyes()->get_position().distance(world_position)));
					Vector2 w2s_position = {};
					if (out_w2s(world_position, w2s_position))
					{
						esp::draw_item(w2s_position, esp_name, esp_color);

						w2s_position.y += 10;
						if (selected_entity_id == ent_id)
							esp::draw_item(w2s_position, il2cpp::methods::new_string(("[selected]")), esp_color);
						//if (vars->visual.distance
						//	&& local_player)
						//	esp::draw_item(Vector2(w2s_position.x, w2s_position.y += 10), s, esp_color);
					}

					continue;
				}
			}
			else if (tag != 6)
				continue;


			esp::matrix = unity::get_view_matrix();

			//players
			if (tag == 6 && !vars->visual.playeresp)
				continue;


			auto player = reinterpret_cast<base_player*>(ent);

			auto hit_player = [&]() {
				auto weapon = esp::local_player->get_active_weapon();
				if (weapon) {
					auto baseprojectile = weapon->get_base_projectile();
					if (baseprojectile) {
						auto class_name = baseprojectile->get_class_name();
						if (*(int*)(class_name + 4) == 'eleM' || *(int*)(class_name + 4) == 'mmah') {
							auto world_position = player->get_bone_transform(48)->get_bone_position();
							auto local = ClosestPoint(esp::local_player, world_position);
							auto camera = esp::local_player->get_bone_transform(48)->get_bone_position();

							if (camera.get_3d_dist(world_position) >= 4.2f)
								return;

							aim_target target = esp::local_player->get_aimbot_target(camera);

							attack_melee(target, baseprojectile, true);
						}
					}
				}
			};

			if (!player->is_alive())
				continue;

			if (player->is_sleeping() && !vars->visual.sleeper_esp)
				continue;

			bool is_npc = false;

			if (get_IsNpc(player->get_player_model())) {
				is_npc = true;

				if (!vars->visual.npc_esp)
					continue;
			}

			if (player->is_local_player())
			{
				local_player = reinterpret_cast<base_player*>(ent);
				do_chams(local_player);
			}
			else {
				if (esp::local_player) {
					auto target = aim_target();
					target.pos = player->get_bone_transform(48)->get_bone_position();

					auto distance = esp::local_player->get_bone_transform(48)->get_bone_position().get_3d_dist(target.pos);
					target.distance = distance;

					auto fov = unity::get_fov(target.pos);
					target.fov = fov;

					target.player = player;

					auto visible = player->is_visible(esp::local_player->get_bone_transform(48)->get_bone_position(), target.pos);
					target.visible = visible;

					if (target < best_target
						|| !best_target.player->is_alive()
						|| (target.player && target.player->get_steam_id() == best_target.player->get_steam_id()))
					{
						best_target.pos = target.pos;
						best_target.distance= target.distance;
						best_target.fov = target.fov;
						best_target.player = target.player;
						best_target.visible = visible;

						auto vel = GetWorldVelocity(target.player);

						float next_frame = best_target.last_frame + get_deltaTime();
						if (get_fixedTime() > next_frame)
						{
							//new frame, record velocity, record frame
							best_target.last_frame = get_fixedTime();
							if (best_target.velocity_list.size() < 30) //0.03125 * 30 = 0.9 seconds
								best_target.velocity_list.push_back(vel);
							else
							{
								best_target.velocity_list.pop_back();
								best_target.velocity_list.insert(best_target.velocity_list.begin(), 1, vel);
							}
							float avgx = 0.f;
							float avgy = 0.f;
							float avgz = 0.f;
							int count = 0;
							for (auto v : best_target.velocity_list)
							{
								if (v.is_empty()) break;
								avgx += v.x;
								avgy += v.y;
								avgz += v.z;
								count += 1;
							}
							avgx /= count; avgy /= count; avgz /= count;
							best_target.avg_vel = Vector3(avgx, avgy, avgz);
						}
					}
					if (best_target.fov > vars->combat.aimbotfov)
						best_target = aim_target();
				}


				if (draw) {

					draw_player(player, is_npc);

					if (vars->visual.offscreen_indicator
						&& !is_npc)
					{
						offscreen_indicator(player->get_player_eyes()->get_position());
					}

					if (vars->combat.silent_melee || unity::GetKey(rust::classes::KeyCode(vars->keybinds.silentmelee)))
						hit_player();
				}
			}
		}


		if (vars->misc.auto_upgrade
			&& closest_building_block)
		{
			auto block = (BuildingBlock*)closest_building_block;
			auto tranny = get_transform((base_player*)block);
			auto pos = get_position((uintptr_t)tranny);
			auto distance = local_player->get_player_eyes()->get_position().distance(pos);

			rust::classes::BuildingGrade upgrade_tier = rust::classes::BuildingGrade::Stone;

			if (distance < 4.2f) {
				auto grade = block->grade();
				if (block && (get_fixedTime() > esp::time_last_upgrade + 0.35f))
				{
					switch ((int)upgrade_tier)
					{
					case 1:
						if (block->CanAffordUpgrade(rust::classes::BuildingGrade::Wood, local_player)
							&& block->CanChangeToGrade(rust::classes::BuildingGrade::Wood, local_player)
							&& grade != rust::classes::BuildingGrade::Wood)
						{
							block->Upgrade(rust::classes::BuildingGrade::Wood, local_player);
							esp::time_last_upgrade = get_fixedTime();
						}
					case 2:
						if (block->CanAffordUpgrade(rust::classes::BuildingGrade::Stone, local_player)
							&& block->CanChangeToGrade(rust::classes::BuildingGrade::Stone, local_player)
							&& grade != rust::classes::BuildingGrade::Stone)
						{
							block->Upgrade(rust::classes::BuildingGrade::Stone, local_player);
							esp::time_last_upgrade = get_fixedTime();
						}
					case 3:
						if (block->CanAffordUpgrade(rust::classes::BuildingGrade::Metal, local_player)
							&& block->CanChangeToGrade(rust::classes::BuildingGrade::Metal, local_player)
							&& grade != rust::classes::BuildingGrade::Metal)
						{
							block->Upgrade(rust::classes::BuildingGrade::Metal, local_player);
							esp::time_last_upgrade = get_fixedTime();
						}
					case 4:
						if (block->CanAffordUpgrade(rust::classes::BuildingGrade::TopTier, local_player)
							&& block->CanChangeToGrade(rust::classes::BuildingGrade::TopTier, local_player)
							&& grade != rust::classes::BuildingGrade::TopTier)
						{
							block->Upgrade(rust::classes::BuildingGrade::TopTier, local_player);
							esp::time_last_upgrade = get_fixedTime();
						}
					}
				}
			}
		}

		esp::draw_target_hotbar(best_target);
		esp::draw_middle(best_target);
	}

	void draw_teammates() {
		if (!esp::local_player)
			return;

		auto team = mem::read<uintptr_t>((uintptr_t)local_player + clientTeam);

		auto member = mem::read<uintptr_t>(team + 0x30);

		auto size = mem::read<int>(member + 0x18);

		auto list = mem::read<uintptr_t>(member + 0x10);

		for (int i = 0; i < size; i++) {
			auto player = mem::read<uintptr_t>(list + 0x20 + i * 0x8);

			auto online = mem::read<bool>(player + 0x38);

			if (!online && !vars->visual.sleeper_esp)
				continue;

			auto id = mem::read<unsigned long>(player + 0x20);

			if (id == esp::local_player->get_steam_id())
				continue;

			auto position = mem::read<Vector3>(player + 0x2C);
			auto distance = esp::local_player->get_bone_transform(48)->get_bone_position().distance(position);
			if (distance < 350.f)
				continue;

			auto player_name = (str)(*reinterpret_cast<uintptr_t*>(player + 0x18));
			auto name = player_name->str;
			Vector2 out;
			esp::out_w2s(position, out);
			esp::draw_name({ out.x, out.y, 0 }, name);
		}
	}

	uintptr_t find_networkable_by_id(unsigned int id_to_check) {
		auto list = (rust::classes::list*)(cliententities);
		auto value = list->get_value<uintptr_t>();
		if (!value) return uintptr_t(0);
		auto sz = list->get_size();
		if (!sz) return uintptr_t(0);
		auto buffer = list->get_buffer<uintptr_t>();

		for (size_t i = 0; i < sz; i++)
		{
			auto current = *reinterpret_cast<uintptr_t*>(buffer + 0x20 + (i * 0x8));
			if (!current)
				continue;
			auto base_object = *reinterpret_cast<uintptr_t*>(current + 0x10);
			if (!base_object)
				continue;
			auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
			if (!object)
				continue;

			WORD tag = *reinterpret_cast<WORD*>(object + 0x54);

			auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);

			auto net = *reinterpret_cast<networkable**>(ent + 0x58);

			unsigned int id = net->get_id();

			if (id == id_to_check)
				return ent;
		}
	}

	void start() {
		//esp::draw_target_snap_line();
		//draw_raid();
		draw_teammates();
		iterate_players();
	}
}