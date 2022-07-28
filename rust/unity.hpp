#pragma once

#include "../memory/il2cpp.hpp"

#include "rust.hpp"

class RaycastHit {

};

uintptr_t skymask_material = il2cpp::value(_("TOD_Scattering"), _("skyMaskMaterial"));

namespace unity {
	static auto set_lockstate = reinterpret_cast<void(*)(rust::classes::CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_lockState"), 1, _("value"), _("UnityEngine"))));

	static auto get_width = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_width"), 0, _(""), _("UnityEngine"))));

	static auto get_height = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Screen"), _("get_height"), 0, _(""), _("UnityEngine"))));

	static auto GetKeyDown = reinterpret_cast<bool(*)(rust::classes::KeyCode key)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyDown"), 1, _("key"), _("UnityEngine"), 1)));

	static auto GetMouseButtonDown = reinterpret_cast<bool(*)(rust::classes::KeyCode button)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetMouseButton"), 1, _("button"), _("UnityEngine"), 1)));

	static auto get_main_camera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(_("UnityEngine.Camera::get_main()")));

	static auto IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(il2cpp::methods::resolve_icall(_("UnityEngine.Physics::IgnoreLayerCollision()")));

	static auto get_keyCode = reinterpret_cast<rust::classes::KeyCode(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_keyCode"), 0, _(""), _("UnityEngine"))));

	static auto LineOfSight = reinterpret_cast<bool(*)(Vector3, Vector3, int, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSight"), -1, _(""), _(""))));

	//static auto LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));

	static auto LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));
	//static auto LineOfSightRadius = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightRadius"), -1, _(""), _(""))));

	static auto LineOfSightInternal = reinterpret_cast<bool(*)(Vector3, Vector3, int, float, float, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("LineOfSightInternal"), -1, _(""), _(""))));

	static auto GetKey = reinterpret_cast<bool(*)(rust::classes::KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyInt"), 1, _(""), _("UnityEngine"))));

	static auto set_visible = reinterpret_cast<void(*)(bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Cursor"), _("set_visible"), 1, _("value"), _("UnityEngine"))));

	static auto get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("get_shader"), 0, _(""), _("UnityEngine"))));

	static auto set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(_("UnityEngine.Material::set_shader()")));

	static auto get_realtimesincestartup = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_realtimeSinceStartup"), 0, _(""), _("UnityEngine"))));

	static auto Raycast = reinterpret_cast<bool (*)(Ray, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("Raycast"), 0, _(""), _("UnityEngine"))));
	
	static auto CheckCapsule = reinterpret_cast<bool (*)(Vector3, Vector3, float, int, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("CheckCapsule"), 0, _(""), _(""))));
	
	static auto LoadAllAssets = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAllAssets"), 1, _("type"), _("UnityEngine"), 1)));

	static auto LoadFromFile = reinterpret_cast<uintptr_t(*)(rust::classes::string path)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile"), 1, _("path"), _("UnityEngine"), 1)));

	static auto LoadAsset = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, rust::classes::string path, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset_Internal"), 2, _("name"), _("UnityEngine"), 1)));

	static auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

	static auto get_Scattering = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_Scattering"), 0, _(""), _(""))));
	
	static auto get_SpaceMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_SpaceMaterial"), 0, _(""), _(""))));
	static auto get_StarMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_StarMaterial"), 0, _(""), _(""))));
	static auto get_SunMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_SunMaterial"), 0, _(""), _(""))));
	static auto get_MoonMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_MoonMaterial"), 0, _(""), _(""))));
	static auto get_AtmosphereMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_AtmosphereMaterial"), 0, _(""), _(""))));
	static auto get_ClearMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_ClearMaterial"), 0, _(""), _(""))));
	static auto get_CloudMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_CloudMaterial"), 0, _(""), _(""))));

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

		LoadAllAssets = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAllAssets"), 1, _("type"), _("UnityEngine"), 1)));

		LoadFromFile = reinterpret_cast<uintptr_t(*)(rust::classes::string path)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile"), 1, _("path"), _("UnityEngine"), 1)));

		LoadAsset = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, rust::classes::string path, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset"), 2, _("name"), _("UnityEngine"), 1)));

		GetMouseButtonDown = reinterpret_cast<bool(*)(rust::classes::KeyCode button)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetMouseButton"), 1, _("button"), _("UnityEngine"), 1)));

		ServerRPC = reinterpret_cast<void (*)(uintptr_t, rust::classes::string funcName)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));

		CheckCapsule = reinterpret_cast<bool (*)(Vector3, Vector3, float, int, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GamePhysics"), _("CheckCapsule"), 0, _(""), _(""))));
		
		get_Scattering = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_Scattering"), 0, _(""), _(""))));

		get_SpaceMaterial = reinterpret_cast<uintptr_t (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_SpaceMaterial"), 0, _(""), _(""))));
		get_StarMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_StarMaterial"), 0, _(""), _(""))));
		get_SunMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_SunMaterial"), 0, _(""), _(""))));
		get_MoonMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_MoonMaterial"), 0, _(""), _(""))));
		get_AtmosphereMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_AtmosphereMaterial"), 0, _(""), _(""))));
		get_ClearMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_ClearMaterial"), 0, _(""), _(""))));
		get_CloudMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("get_CloudMaterial"), 0, _(""), _(""))));
		//Spherecast = reinterpret_cast<bool (*)(Vector3, float, Vector3, RaycastHit*, float, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("SphereCast"), 6, _("origin"), _("UnityEngine"), 1)));
		//Spherecast = reinterpret_cast<bool (*)(Ray, float, float, int)>(/*instead of il2cpp because seems to hate me use static offset*/ mem::game_assembly_base + 35705904);
	}

	uintptr_t bundle;
	uintptr_t galaxy_bundle;
	uintptr_t bundle_font;
	uintptr_t chams_shader_normal;
	uintptr_t chams_shader_seethru;
	uintptr_t chams_shader_wireframe;
	uintptr_t chams_shader_lit;
	uintptr_t font_ptr;

	uintptr_t galaxy_material;
	/*
	bool is_visible(Vector3 source, Vector3 destination, base_player* entity, float radius = .5f) {
		//auto layer = (int)rust::classes::Layers::ProjectileLineOfSightCheck | (int)rust::classes::Layers::Terrain;

		return LineOfSightRadius(source, destination, rust::classes::Layers(10551296), radius, 0, entity) && LineOfSightRadius(destination, source, rust::classes::Layers(10551296), radius, 0, entity);
	}
*/
	uintptr_t GetType(const char* space, const char* name) {
		return il2cpp::type_object(space, name);
	}

	bool is_visible(Vector3 source, Vector3 destination, uintptr_t player, float p1 = 0.18f) {
		auto layer = (int)rust::classes::Layers::ProjectileLineOfSightCheck | (int)rust::classes::Layers::Terrain | (int)rust::classes::Layers::z;
		typedef bool (*AAA)(Vector3, Vector3, rust::classes::Layers, float, uintptr_t);//real rust 0x50F790         //cracked 0x50ED80

		//real rust 0x52D200
		//alkad rust 0x50E9A0

		return ((AAA)(mem::game_assembly_base + 0x52D200))(source, destination, rust::classes::Layers(layer), p1, player)
			&& ((AAA)(mem::game_assembly_base + 0x52D200))(destination, source, rust::classes::Layers(layer), p1, player);
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