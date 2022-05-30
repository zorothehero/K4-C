#pragma once

#include "../memory/il2cpp.hpp"

#include "rust.hpp"

class RaycastHit {

};


namespace unity {
	static auto set_lockstate = reinterpret_cast<void(*)(rust::classes::CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_lockState"), 1, _("value"), _("UnityEngine"))));

	static auto get_width = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_width"), 0, _(""), _("UnityEngine"))));

	static auto get_height = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_height"), 0, _(""), _("UnityEngine"))));

	static auto GetKeyDown = reinterpret_cast<bool(*)(rust::classes::KeyCode key)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyDown"), 1, _("key"), _("UnityEngine"), 1)));

	static auto get_main_camera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(_("UnityEngine.Camera::get_main()")));

	static auto IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(il2cpp::methods::resolve_icall(_("UnityEngine.Physics::IgnoreLayerCollision()")));

	static auto get_keyCode = reinterpret_cast<rust::classes::KeyCode(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_keyCode"), 0, _(""), _("UnityEngine"))));

	static auto LineOfSight = reinterpret_cast<bool(*)(Vector3, Vector3, int, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSight"), -1, _(""), _(""))));

	//static auto LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));

	static auto LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));

	static auto LineOfSightInternal = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightInternal"), -1, _(""), _(""))));

	static auto GetKey = reinterpret_cast<bool(*)(rust::classes::KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyInt"), 1, _(""), _("UnityEngine"))));

	static auto set_visible = reinterpret_cast<void(*)(bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_visible"), 1, _("value"), _("UnityEngine"))));

	static auto get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("get_shader"), 0, _(""), _("UnityEngine"))));

	static auto set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(_("UnityEngine.Material::set_shader()")));

	static auto get_realtimesincestartup = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_realtimeSinceStartup"), 0, _(""), _("UnityEngine"))));

	static auto Raycast = reinterpret_cast<bool (*)(Ray, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("Raycast"), 0, _(""), _("UnityEngine"))));
	
	static auto CheckCapsule = reinterpret_cast<bool (*)(Vector3, Vector3, float, int, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("CheckCapsule"), 0, _(""), _(""))));



	//static auto Spherecast = reinterpret_cast<bool (*)(Vector3, float, Vector3, RaycastHit*, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("SphereCast"), 6, _("origin"), _("UnityEngine"), 1)));
	//static auto Spherecast = reinterpret_cast<bool (*)(Ray, float, float, int)>(mem::game_assembly_base + 35705904);

	void init_unity() {
		get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("get_shader"), 0, _(""), _("UnityEngine"))));

		set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(_("UnityEngine.Material::set_shader()")));

		set_lockstate = reinterpret_cast<void(*)(rust::classes::CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_lockState"), 1, _("value"), _("UnityEngine"))));

		set_visible = reinterpret_cast<void(*)(bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_visible"), 1, _("value"), _("UnityEngine"))));

		get_width = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_width"), 0, _(""), _("UnityEngine"))));

		get_height = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_height"), 0, _(""), _("UnityEngine"))));

		GetKeyDown = reinterpret_cast<bool(*)(rust::classes::KeyCode key)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyDown"), 1, _("key"), _("UnityEngine"), 1)));

		get_main_camera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(_("UnityEngine.Camera::get_main()")));

		IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(il2cpp::methods::resolve_icall(_("UnityEngine.Physics::IgnoreLayerCollision()")));

		get_keyCode = reinterpret_cast<rust::classes::KeyCode(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_keyCode"), 0, _(""), _("UnityEngine"))));

		LineOfSight = reinterpret_cast<bool(*)(Vector3, Vector3, int, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSight"), -1, _(""), _(""))));

		LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));

		GetKey = reinterpret_cast<bool(*)(rust::classes::KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyInt"), 1, _(""), _("UnityEngine"))));

		get_realtimesincestartup = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_realtimeSinceStartup"), 0, _(""), _("UnityEngine"))));

		Raycast = reinterpret_cast<bool (*)(Ray, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("Raycast"), 0, _(""), _("UnityEngine"))));

		LineOfSightInternal = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightInternal"), -1, _(""), _(""))));
		//Spherecast = reinterpret_cast<bool (*)(Vector3, float, Vector3, RaycastHit*, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("SphereCast"), 6, _("origin"), _("UnityEngine"), 1)));
		//Spherecast = reinterpret_cast<bool (*)(Ray, float, float, int)>(/*instead of il2cpp because seems to hate me use static offset*/ mem::game_assembly_base + 35705904);
	}

	uintptr_t bundle;
	uintptr_t bundle_font;
	uintptr_t chams_shader;
	uintptr_t font_ptr;

	/*
	bool is_visible(Vector3 source, Vector3 destination, base_player* entity, float radius = .5f) {
		//auto layer = (int)rust::classes::Layers::ProjectileLineOfSightCheck | (int)rust::classes::Layers::Terrain;

		return LineOfSightRadius(source, destination, rust::classes::Layers(10551296), radius, 0, entity) && LineOfSightRadius(destination, source, rust::classes::Layers(10551296), radius, 0, entity);
	}
*/
	bool is_visible(Vector3 source, Vector3 destination, uintptr_t player, float p1 = 0.f) {
		return LineOfSightRadius(source, destination, 1503731969, 0.5f, p1, (uintptr_t)player)
			&& LineOfSightRadius(destination, source, 1503731969, 0.5f, p1, (uintptr_t)player)
			&& LineOfSightRadius(source, destination, 10551296, 0.5f, p1, (uintptr_t)player)
			&& LineOfSightRadius(destination, source, 10551296, 0.5f, p1, (uintptr_t)player);
	}

	auto camera = unity::get_main_camera();

	VMatrix get_view_matrix() {
		if (!camera) {
			camera = unity::get_main_camera();
		}

		auto camera_ = mem::read<uintptr_t>(camera + 0x10);
		if (!camera_) {
			camera = unity::get_main_camera();
			return {};
		}

		auto matrix = mem::read<VMatrix>(camera_ + 0x2E4);
		if (!matrix.m) {
			camera = unity::get_main_camera();
			return {};
		}

		return matrix;
	}

	Vector3 get_camera_pos() {
		if (!camera) {
			camera = unity::get_main_camera();
		}

		auto camera_ = mem::read<uintptr_t>(camera + 0x10);
		if (!camera_) {
			camera = unity::get_main_camera();
			return {};
		}

		auto matrix = mem::read<Vector3>(camera_ + 0x42C);
		if (!matrix.x || !matrix.y) {
			camera = unity::get_main_camera();
			return {};
		}


		return matrix;
	}
	float get_fov(Vector3 Pos);
}