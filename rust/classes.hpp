#pragma once
#include <stdio.h>
#include "unity.hpp"
#include "../utils/xor_float.hpp"
#include <vector>
#include "../utils/string_format.h"

class default_t
{
public:
	template<typename T>
	operator T() const { return T(); }
};
default_t const defaultt = default_t();
#define NP(type) type nonptr = defaultt; if(!this) return nonptr;
#define FIELD(klass,tr,name,type) type& name() { \
	NP(type) \
	static auto off = il2cpp::value(klass, tr); \
	return *reinterpret_cast<type*>(this + off); }

template<typename T>
void pop_front(std::vector<T>& vec)
{
	if (vec.empty()) return;
	vec.front() = std::move(vec.back());
	vec.pop_back();
}

class Bounds {
public:
	Vector3 m_center;
	Vector3 m_extents;
	Vector3 center;
	Vector3 extents;
	Vector3 max;
	Vector3 min;
	Vector3 size;
};

enum BaseCombatEntity_LifeState {
	Alive = 0,
	Dead = 1
};

uintptr_t planner_rotationoffset = il2cpp::value(_("Planner"), _("rotationOffset"));
uintptr_t planner_currentconstruction = il2cpp::value(_("Planner"), _("currentConstruction"));
uintptr_t planner_guide = il2cpp::value(_("Planner"), _("guide"));

uintptr_t _displayName = il2cpp::value(_("BasePlayer"), _("_displayName"));
uintptr_t woundedlol = il2cpp::value(_("BasePlayer"), _("Wounded"));
uintptr_t movement = il2cpp::value(_("BasePlayer"), _("movement"));
uintptr_t player_inventory = il2cpp::value(_("BasePlayer"), _("inventory"));
uintptr_t clActiveItem = il2cpp::value(_("BasePlayer"), _("clActiveItem"));
uintptr_t playerModel = il2cpp::value(_("BasePlayer"), _("playerModel"));
uintptr_t clientTeam = il2cpp::value(_("BasePlayer"), _("clientTeam"));
uintptr_t playerFlags = il2cpp::value(_("BasePlayer"), _("playerFlags"));
uintptr_t eyes = il2cpp::value(_("BasePlayer"), _("eyes"));
uintptr_t _lastSentTickTime = il2cpp::value(_("BasePlayer"), _("lastSentTickTime"));
uintptr_t modelState = il2cpp::value(_("BasePlayer"), _("modelState"));
uintptr_t input = il2cpp::value(_("BasePlayer"), _("input"));
uintptr_t containerBelt = il2cpp::value(_("PlayerInventory"), _("containerBelt"));
uintptr_t containerWear = il2cpp::value(_("PlayerInventory"), _("containerWear"));
uintptr_t itemList = il2cpp::value(_("ItemContainer"), _("itemList"));

uintptr_t building_grade = il2cpp::value(_("BuildingBlock"), _("grade"));

uintptr_t numprojectiles = il2cpp::value(_("ItemModProjectile"), _("numProjectiles"));


uintptr_t newVelocity = il2cpp::value(_("PlayerModel"), _("newVelocity"));
uintptr_t isLocalPlayer = il2cpp::value(_("PlayerModel"), _("isLocalPlayer"));

uintptr_t _health = il2cpp::value(_("BaseCombatEntity"), _("_health"));
uintptr_t _maxHealth = il2cpp::value(_("BaseCombatEntity"), _("_maxHealth"));
uintptr_t lifestate = il2cpp::value(_("BaseCombatEntity"), _("lifestate"));

uintptr_t net = il2cpp::value(_("BaseNetworkable"), _("net"));

uintptr_t heldEntity = il2cpp::value(_("Item"), _("heldEntity"));

uintptr_t canWieldItems = il2cpp::value(_("BaseMountable"), _("canWieldItems"));

uintptr_t successFraction = il2cpp::value(_("FlintStrikeWeapon"), _("successFraction"));
uintptr_t didSparkThisFrame = il2cpp::value(_("FlintStrikeWeapon"), _("_didSparkThisFrame"));

uintptr_t currentVelocity = il2cpp::value(_("Projectile"), _("currentVelocity"));
uintptr_t currentPosition = il2cpp::value(_("Projectile"), _("currentPosition"));
uintptr_t thickness_addr = il2cpp::value(_("Projectile"), _("thickness"));
uintptr_t traveledTime = il2cpp::value(_("Projectile"), _("traveledTime"));
uintptr_t isAuthoritative = il2cpp::value(_("Projectile"), _("isAuthoritative")); 

uintptr_t mod = il2cpp::value(_("Projectile"), _("mod"));
uintptr_t hitTest = il2cpp::value(_("Projectile"), _("hitTest"));

uintptr_t weakspots = il2cpp::value(_("BaseHelicopter"), _("weakspots"));

uintptr_t info = il2cpp::value(_("Item"), _("info"));

uintptr_t iconSprite = il2cpp::value(_("ItemDefinition"), _("iconSprite"));
uintptr_t steamItem = il2cpp::value(_("ItemDefinition"), _("steamItem"));

uintptr_t category = il2cpp::value(_("ItemDefinition"), _("category"));
uintptr_t itemid = il2cpp::value(_("ItemDefinition"), _("itemid"));
uintptr_t displayName = il2cpp::value(_("ItemDefinition"), _("displayName"));

uintptr_t viewOffset = il2cpp::value(_("PlayerEyes"), _("viewOffset"));
uintptr_t eyepos = il2cpp::value(_("PlayerEyes"), _("position"));

uintptr_t swimming = il2cpp::value(_("PlayerWalkMovement"), _("swimming"));

uintptr_t ducking = il2cpp::value(_("BaseMovement"), _("<Ducking>k__BackingField"));

uintptr_t TargetMovement = il2cpp::value(_("BaseMovement"), _("<TargetMovement>k__BackingField"));

uintptr_t lastHitTime = il2cpp::value(_("Chainsaw"), _("lastHitTime"));
uintptr_t lastHitMaterial = il2cpp::value(_("Chainsaw"), _("lastHitMaterial"));

uintptr_t integrity = il2cpp::value(_("Projectile"), _("integrity"));

uintptr_t groundAngleNew = il2cpp::value(_("PlayerWalkMovement"), _("groundAngleNew"));
uintptr_t landTime = il2cpp::value(_("PlayerWalkMovement"), _("landTime"));
uintptr_t jumpTime = il2cpp::value(_("PlayerWalkMovement"), _("jumpTime"));
uintptr_t groundTime = il2cpp::value(_("PlayerWalkMovement"), _("groundTime"));
uintptr_t gravityMultiplier = il2cpp::value(_("PlayerWalkMovement"), _("gravityMultiplier"));
uintptr_t flying = il2cpp::value(_("PlayerWalkMovement"), _("flying"));

uintptr_t model = il2cpp::value(_("BaseEntity"), _("model"));


class BaseProjectile;
class Transform;
class BasePlayer;
class HitTest;
class ModelState;
class Transform;
class Item;
class col;

typedef struct Str
{
	char stub[0x10];
	int len;
	wchar_t str[1];
} *str;


static auto GetNormal = reinterpret_cast<Vector3 (*)(uintptr_t, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TerrainHeightMap"), _("GetNormal"), 1, _(""), _(""))));

static auto GetSpeed = reinterpret_cast<float (*)(BasePlayer * baseplayer, float running, float ducking, float crawling)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 3, _(""), _(""))));

static auto IsSwimming = reinterpret_cast<bool (*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

static auto Line = reinterpret_cast<void (*)(Vector3, Vector3, col, float, bool, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Line"), 6, _(""), _("UnityEngine"))));

static auto GetIndex = reinterpret_cast<int(*)(uintptr_t SkinSetCollection, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinSetCollection"), _("GetIndex"), 1, _(""), _(""))));

static auto set_onLadder = reinterpret_cast<void(*)(ModelState*, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_onLadder"), 1, _(""), _(""))));

static auto HasPlayerFlag = reinterpret_cast<bool(*)(BasePlayer*, rust::classes::PlayerFlags)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("HasPlayerFlag"), 1, _(""), _(""))));

static auto get_game_object_transform = reinterpret_cast<Transform * (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("get_transform"), 0, _(""), _("UnityEngine"))));

static auto get_iconSprite = reinterpret_cast<uintptr_t(*)(Item * Item)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Item"), _("get_iconSprite"), 0, _(""), _(""))));

static auto get_texture = reinterpret_cast<uintptr_t(*)(uintptr_t sprite)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Sprite"), _("get_texture"), 0, _(""), _("UnityEngine"))));

static auto get_rect = reinterpret_cast<rust::classes::Rect(*)(uintptr_t sprite)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Sprite"), _("get_rect"), 0, _(""), _("UnityEngine"))));

static auto StringPool_Get = reinterpret_cast<unsigned int(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("StringPool"), _("Get"), 1, _("str"), _(""))));

static auto set_timeScale = reinterpret_cast<void(*)(float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("set_timeScale"), 1, _(""), _("UnityEngine"))));

static auto get_frameCount = reinterpret_cast<int(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_frameCount"), 0, _(""), _("UnityEngine"))));

static auto get_timeScale = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_timeScale"), 0, _(""), _("UnityEngine"))));

static auto get_mousePosition = reinterpret_cast<Vector3(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("get_mousePosition"), 0, _(""), _("UnityEngine"))));

static auto FloorToInt = reinterpret_cast<int (*)(float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Mathf"), _("FloorToInt"), 1, _(""), _("UnityEngine"))));

static auto get_gravity = reinterpret_cast<Vector3(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("get_gravity"), 1, _(""), _("UnityEngine"))));

static auto get_isAlive = reinterpret_cast<bool (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("get_isAlive"), 0, _(""), _(""))));

static auto get_rotation = reinterpret_cast<Vector4(*)(uintptr_t Transform)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_rotation"), 0, _(""), _("UnityEngine"))));

static auto FindShader = reinterpret_cast<uintptr_t(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Shader"), _("Find"), 1, _(""), _("UnityEngine"))));

static auto set_hideFlags = reinterpret_cast<void(*)(uintptr_t material, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("set_hideFlags"), 1, _(""), _("UnityEngine"))));

static auto set_name = reinterpret_cast<void(*)(uintptr_t, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("set_name"), 1, _(""), _("UnityEngine"))));

static auto SetInt = reinterpret_cast<void(*)(uintptr_t material, System::string name, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetInt"), 1, _(""), _("UnityEngine"))));

static auto get_deltaTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_deltaTime"), 0, _(""), _("UnityEngine"))));

static auto get_smoothdeltaTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_smoothDeltaTime"), 0, _(""), _("UnityEngine"))));

static auto get_fixeddeltaTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_fixedDeltaTime"), 0, _(""), _("UnityEngine"))));

static auto get_fixedTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_fixedTime"), 0, _(""), _("UnityEngine"))));

static auto get_IsNpc = reinterpret_cast<bool(*)(uintptr_t player_model)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerModel"), _("get_IsNpc"), -1, _(""), _(""))));

static auto get_time = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_time"), 0, _(""), _("UnityEngine"))));

static auto ClosestPoint = reinterpret_cast<Vector3(*)(BasePlayer*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ClosestPoint"), 1, _("position"), _(""), 1)));

static auto InverseTransformPoint = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("InverseTransformPoint"), 1, _(""), _("UnityEngine"))));

static auto InverseTransformDirection = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("InverseTransformDirection"), 1, _(""), _("UnityEngine"))));

static auto get_localToWorldMatrix = reinterpret_cast<VMatrix(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_localToWorldMatrix"), 0, _(""), _("UnityEngine"))));

static auto get_gameObject = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("get_gameObject"), 0, _(""), _("UnityEngine"))));

static auto get_component = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("GetComponent"), 0, _(""), _("UnityEngine"))));

static auto get_components_in_children = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("GetComponentsInChildren"), 0, _(""), _("UnityEngine"))));

static auto set_position = reinterpret_cast<void(*)(Transform*, Vector3 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("set_position"), 1, _(""), _("UnityEngine"))));

static auto get_up = reinterpret_cast<Vector3(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_up"), 0, _(""), _("UnityEngine"))));

static auto LookRotation = reinterpret_cast<Vector4(*)(Vector3, Vector3 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Quaternion"), _("LookRotation"), 2, _(""), _("UnityEngine"))));

static auto set_rotation = reinterpret_cast<void(*)(Transform*, Vector4 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("set_rotation"), 1, _(""), _("UnityEngine"))));

static auto StartAttackCooldown = reinterpret_cast<void(*)(BaseProjectile*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AttackEntity"), _("StartAttackCooldown"), 1, _(""), _(""))));

static auto ProcessAttack = reinterpret_cast<void(*)(BaseProjectile*, HitTest*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMelee"), _("ProcessAttack"), 1, _(""), _(""))));

static auto GetProjectileVelocityScale = reinterpret_cast<float(*)(BaseProjectile*, bool max)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("GetProjectileVelocityScale"), 1, _("getMax"), _(""), 1)));

//static auto get_Renderers = reinterpret_cast<System::list<uintptr_t>*(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinnedMultiMesh"), _("get_Renderers"), 0, _(""), _(""))));

static auto get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("get_material"), 0, _(""), _("UnityEngine"))));

static auto set_material = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("set_material"), 0, _(""), _("UnityEngine"))));

static auto get_maxspeed = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetMaxSpeed"), 0, _(""), _(""))));

static auto SendSignal = reinterpret_cast<void(*)(uintptr_t, rust::classes::Signal, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("SendSignalBroadcast"), 2, _(""), _(""))));

static auto _BoundsPadding = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("BoundsPadding"), 2, _(""), _(""))));

static auto PEyes_get_position = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_position"), 0, _(""), _(""))));

static auto get_center = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_center"), 0, _(""), _(""))));

static auto PEyes_get_rotation = reinterpret_cast<Vector4(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_rotation"), 0, _(""), _(""))));

static auto bodyforward = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("BodyForward"), 0, _(""), _(""))));

static auto _SendClientTick = reinterpret_cast<void(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("SendClientTick"), 0, _(""), _(""))));

static auto _getjumpheight = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetJumpHeight"), 0, _(""), _(""))));

static auto _GetRadius = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetRadius"), 0, _(""), _(""))));

static auto GetHeight = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetHeight"), 0, _(""), _(""))));

static auto terrainheightmap_GetHeight = reinterpret_cast<int(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TerrainHeightMap"), _("GetHeight"), 0, _(""), _(""))));

static auto updateammodisplay = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("UpdateAmmoDisplay"), 0, _(""), _(""))));

static auto shot_fired = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("ShotFired"), 0, _(""), _(""))));

static auto did_attack_client_side = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("DidAttackClientside"), 0, _(""), _(""))));

static auto getmodifiedaimcone = reinterpret_cast<Vector3(*)(float, Vector3, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AimConeUtil"), _("GetModifiedAimConeDirection"), 0, _(""), _(""))));

static auto canaffordupgrade = reinterpret_cast<bool(*)(uintptr_t, rust::classes::BuildingGrade, BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BuildingBlock"), _("CanAffordUpgrade"), 0, _(""), _(""))));

static auto canchangetograde = reinterpret_cast<bool(*)(uintptr_t, rust::classes::BuildingGrade, BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BuildingBlock"), _("CanChangeToGrade"), 0, _(""), _(""))));

static auto upgradetograde = reinterpret_cast<void(*)(uintptr_t, rust::classes::BuildingGrade, BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BuildingBlock"), _("UpgradeToGrade"), 0, _(""), _(""))));

static auto set_jumped = reinterpret_cast<void(*)(uintptr_t, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_jumped"), 0, _(""), _(""))));

static auto do_jump = reinterpret_cast<void(*)(uintptr_t, uintptr_t, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("Jump"), 0, _(""), _(""))));

static auto set_rigidbody_velocity = reinterpret_cast<void(*)(uintptr_t, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Rigidbody"), _("set_velocity"), 0, _(""), _("UnityEngine"))));

static auto get_rigidbody_velocity = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Rigidbody"), _("get_velocity"), 0, _(""), _("UnityEngine"))));

static auto console_msg = reinterpret_cast<void(*)(uintptr_t, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ConsoleMessage"), 0, _(""), _(""))));

static auto teleportto = reinterpret_cast<void(*)(uintptr_t, Vector3, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMovement"), _("TeleportTo"), 0, _(""), _(""))));

static auto GetAimCone = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("GetAimCone"), 0, _(""), _(""))));

static auto animcurve_evaluate = reinterpret_cast<float(*)(uintptr_t, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AnimationCurve"), _("Evaluate"), 0, _(""), _("UnityEngine"))));

static auto guidtopath = reinterpret_cast<System::string(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameManifest"), _("GUIDToPath"), 0, _(""), _(""))));

static auto GetBounds = reinterpret_cast<Bounds(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetBounds"), 0, _(""), _(""))));

static auto get_mounted = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetMounted"), 0, _(""), _(""))));

static auto get_parent_entity = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseNetworkable"), _("GetParentEntity"), 0, _(""), _(""))));

static auto get_short_prefab_name = reinterpret_cast<System::string(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseNetworkable"), _("get_ShortPrefabName"), 0, _(""), _(""))));

static auto get_max_fwd_speed = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModularCar"), _("GetMaxForwardSpeed"), 0, _(""), _(""))));

static auto set_SpaceMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_SpaceMaterial"), 0, _(""), _(""))));
static auto set_StarMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_StarMaterial"), 0, _(""), _(""))));
static auto set_SunMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_SunMaterial"), 0, _(""), _(""))));
static auto set_MoonMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_MoonMaterial"), 0, _(""), _(""))));
static auto set_AtmosphereMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_AtmosphereMaterial"), 0, _(""), _(""))));
static auto set_ClearMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_ClearMaterial"), 0, _(""), _(""))));
static auto set_CloudMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TOD_Components"), _("set_CloudMaterial"), 0, _(""), _(""))));


class col {
public:
	float r;
	float g;
	float b;
	float a;
	col(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

float current_time;

void init_bp() {
	get_center = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_center"), 0, _(""), _(""))));
	get_max_fwd_speed = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModularCar"), _("GetMaxForwardSpeed"), 0, _(""), _(""))));
	get_short_prefab_name = reinterpret_cast<System::string(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseNetworkable"), _("get_ShortPrefabName"), 0, _(""), _(""))));
	get_parent_entity = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseNetworkable"), _("GetParentEntity"), 0, _(""), _(""))));
	get_mounted = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetMounted"), 0, _(""), _(""))));
	terrainheightmap_GetHeight = reinterpret_cast<int(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TerrainHeightMap"), _("GetHeight"), 0, _(""), _(""))));
	GetNormal = reinterpret_cast<Vector3(*)(uintptr_t, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("TerrainHeightMap"), _("GetNormal"), 1, _(""), _(""))));
	Line = reinterpret_cast<void (*)(Vector3, Vector3, col, float, bool, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Line"), 6, _(""), _("UnityEngine"))));
	set_onLadder = reinterpret_cast<void(*)(ModelState*, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_onLadder"), 1, _(""), _(""))));
	HasPlayerFlag = reinterpret_cast<bool(*)(BasePlayer*, rust::classes::PlayerFlags)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("HasPlayerFlag"), 1, _(""), _(""))));
	get_game_object_transform = reinterpret_cast<Transform * (*)(uintptr_t game_object)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("get_transform"), 0, _(""), _("UnityEngine"))));
	get_rect = reinterpret_cast<rust::classes::Rect(*)(uintptr_t sprite)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Sprite"), _("get_rect"), 0, _(""), _("UnityEngine"))));
	get_iconSprite = reinterpret_cast<uintptr_t(*)(Item * Item)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Item"), _("get_iconSprite"), 0, _(""), _(""))));
	steamItem = il2cpp::value(_("ItemDefinition"), _("steamItem"));
	iconSprite = il2cpp::value(_("ItemDefinition"), _("iconSprite"));
	get_texture = reinterpret_cast<uintptr_t(*)(uintptr_t sprite)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Sprite"), _("get_texture"), 0, _(""), _("UnityEngine"))));
	set_name = reinterpret_cast<void(*)(uintptr_t, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("set_name"), 1, _(""), _("UnityEngine"))));;
	get_gameObject = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("get_gameObject"), 0, _(""), _("UnityEngine"))));
	InverseTransformDirection = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("InverseTransformDirection"), 1, _(""), _("UnityEngine"))));
	LookRotation = reinterpret_cast<Vector4(*)(Vector3, Vector3 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Quaternion"), _("LookRotation"), 2, _(""), _("UnityEngine"))));
	set_rotation = reinterpret_cast<void(*)(Transform*, Vector4 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("set_rotation"), 1, _(""), _("UnityEngine"))));
	set_position = reinterpret_cast<void(*)(Transform*, Vector3 value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("set_position"), 1, _(""), _("UnityEngine"))));
	SetInt = reinterpret_cast<void(*)(uintptr_t material, System::string name, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetInt"), 1, _(""), _("UnityEngine"))));
	set_hideFlags = reinterpret_cast<void(*)(uintptr_t material, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("set_hideFlags"), 1, _(""), _("UnityEngine"))));
	FindShader = reinterpret_cast<uintptr_t(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Shader"), _("Find"), 1, _(""), _("UnityEngine"))));
	//get_Renderers = reinterpret_cast<System::list<uintptr_t> *(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinnedMultiMesh"), _("get_Renderers"), 0, _(""), _(""))));
	//get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("get_material"), 0, _(""), _("UnityEngine"))));
	StringPool_Get = reinterpret_cast<unsigned int(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("StringPool"), _("Get"), 1, _("str"), _(""))));
	set_timeScale = reinterpret_cast<void(*)(float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("set_timeScale"), 1, _(""), _("UnityEngine"))));
	get_timeScale = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_timeScale"), 0, _(""), _("UnityEngine"))));
	GetIndex = reinterpret_cast<int(*)(uintptr_t SkinSetCollection, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinSetCollection"), _("GetIndex"), 1, _(""), _(""))));
	FloorToInt = reinterpret_cast<int (*)(float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Mathf"), _("FloorToInt"), 1, _(""), _("UnityEngine"))));
	get_gravity = reinterpret_cast<Vector3(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Physics"), _("get_gravity"), 1, _(""), _("UnityEngine"))));
	get_isAlive = reinterpret_cast<bool (*)(BaseProjectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("get_isAlive"), 0, _(""), _(""))));
	get_mousePosition = reinterpret_cast<Vector3(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("get_mousePosition"), 0, _(""), _("UnityEngine"))));
	GetSpeed = reinterpret_cast<float (*)(BasePlayer * baseplayer, float running, float ducking, float crawling)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 3, _(""), _(""))));
	get_frameCount = reinterpret_cast<int(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_frameCount"), 0, _(""), _("UnityEngine"))));
	get_rotation = reinterpret_cast<Vector4(*)(uintptr_t Transform)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_rotation"), 0, _(""), _("UnityEngine"))));
	GetBounds = reinterpret_cast<Bounds(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetBounds"), 0, _(""), _(""))));

	get_components_in_children = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("GetComponentsInChildren"), 0, _(""), _("UnityEngine"))));
	get_component = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("GetComponent"), 0, _(""), _("UnityEngine"))));

	PEyes_get_position = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_position"), 0, _(""), _(""))));

	_GetRadius = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetRadius"), 0, _(""), _(""))));

	_getjumpheight = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetJumpHeight"), 0, _(""), _(""))));

	_BoundsPadding = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("BoundsPadding"), 2, _(""), _(""))));

	_SendClientTick = reinterpret_cast<void(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("SendClientTick"), 0, _(""), _(""))));

	get_maxspeed = reinterpret_cast<float(*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetMaxSpeed"), 0, _(""), _(""))));

	get_up = reinterpret_cast<Vector3(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_up"), 0, _(""), _("UnityEngine"))));

	get_fixedTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_fixedTime"), 0, _(""), _("UnityEngine"))));

	SendSignal = reinterpret_cast<void(*)(uintptr_t, rust::classes::Signal, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("SendSignalBroadcast"), 2, _(""), _(""))));

	updateammodisplay = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("UpdateAmmoDisplay"), 0, _(""), _(""))));

	shot_fired = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("ShotFired"), 0, _(""), _(""))));

	did_attack_client_side = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("DidAttackClientside"), 0, _(""), _(""))));

	bodyforward = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("BodyForward"), 0, _(""), _(""))));

	get_localToWorldMatrix = reinterpret_cast<VMatrix(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_localToWorldMatrix"), 0, _(""), _("UnityEngine"))));
	
	getmodifiedaimcone = reinterpret_cast<Vector3(*)(float, Vector3, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AimConeUtil"), _("GetModifiedAimConeDirection"), 0, _(""), _(""))));

	PEyes_get_rotation = reinterpret_cast<Vector4(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_rotation"), 0, _(""), _(""))));

	set_jumped = reinterpret_cast<void(*)(uintptr_t, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_jumped"), 0, _(""), _(""))));

	set_rigidbody_velocity = reinterpret_cast<void(*)(uintptr_t, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Rigidbody"), _("set_velocity"), 0, _(""), _("UnityEngine"))));

	get_rigidbody_velocity = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Rigidbody"), _("get_velocity"), 0, _(""), _("UnityEngine"))));

	console_msg = reinterpret_cast<void(*)(uintptr_t, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ConsoleMessage"), 0, _(""), _(""))));

	teleportto = reinterpret_cast<void(*)(uintptr_t, Vector3, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMovement"), _("TeleportTo"), 0, _(""), _(""))));

	set_material = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("set_material"), 0, _(""), _("UnityEngine"))));

	do_jump = reinterpret_cast<void(*)(uintptr_t, uintptr_t, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("Jump"), 0, _(""), _(""))));

	GetAimCone = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("GetAimCone"), 0, _(""), _(""))));

	animcurve_evaluate = reinterpret_cast<float(*)(uintptr_t, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AnimationCurve"), _("Evaluate"), 0, _(""), _("UnityEngine"))));

	guidtopath = reinterpret_cast<System::string(*)(System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameManifest"), _("GUIDToPath"), 0, _(""), _(""))));

	IsSwimming = reinterpret_cast<bool (*)(BasePlayer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));
#pragma region il2

	containerWear = il2cpp::value(_("PlayerInventory"), _("containerWear"));
	canWieldItems = il2cpp::value(_("BaseMountable"), _("canWieldItems"));
	containerBelt = il2cpp::value(_("PlayerInventory"), _("containerBelt"));
	itemList = il2cpp::value(_("ItemContainer"), _("itemList"));
	integrity = il2cpp::value(_("Projectile"), _("integrity"));

	lastHitTime = il2cpp::value(_("Chainsaw"), _("lastHitTime"));
	lastHitMaterial = il2cpp::value(_("Chainsaw"), _("lastHitMaterial"));
	landTime = il2cpp::value(_("PlayerWalkMovement"), _("landTime"));
	jumpTime = il2cpp::value(_("PlayerWalkMovement"), _("jumpTime"));
	groundTime = il2cpp::value(_("PlayerWalkMovement"), _("groundTime"));
	gravityMultiplier = il2cpp::value(_("PlayerWalkMovement"), _("gravityMultiplier"));

	movement = il2cpp::value(_("BasePlayer"), _("movement"));
	_displayName = il2cpp::value(_("BasePlayer"), _("_displayName"));
	player_inventory = il2cpp::value(_("BasePlayer"), _("inventory"));
	clActiveItem = il2cpp::value(_("BasePlayer"), _("clActiveItem"));
	playerModel = il2cpp::value(_("BasePlayer"), _("playerModel"));
	clientTeam = il2cpp::value(_("BasePlayer"), _("clientTeam"));
	playerFlags = il2cpp::value(_("BasePlayer"), _("playerFlags"));
	eyes = il2cpp::value(_("BasePlayer"), _("eyes"));
	modelState = il2cpp::value(_("BasePlayer"), _("modelState"));
	input = il2cpp::value(_("BasePlayer"), _("input"));

	newVelocity = il2cpp::value(_("PlayerModel"), _("newVelocity"));
	isLocalPlayer = il2cpp::value(_("PlayerModel"), _("isLocalPlayer"));

	_health = il2cpp::value(_("BaseCombatEntity"), _("_health"));
	_maxHealth = il2cpp::value(_("BaseCombatEntity"), _("_maxHealth"));
	lifestate = il2cpp::value(_("BaseCombatEntity"), _("lifestate"));

	net = il2cpp::value(_("BaseNetworkable"), _("net"));

	heldEntity = il2cpp::value(_("Item"), _("heldEntity"));

	currentVelocity = il2cpp::value(_("Projectile"), _("currentVelocity"));
	currentPosition = il2cpp::value(_("Projectile"), _("currentPosition"));
	thickness_addr = il2cpp::value(_("Projectile"), _("thickness"));
	isAuthoritative = il2cpp::value(_("Projectile"), _("isAuthoritative"));
	mod = il2cpp::value(_("Projectile"), _("mod"));
	hitTest = il2cpp::value(_("Projectile"), _("hitTest"));

	info = il2cpp::value(_("Item"), _("info"));

	category = il2cpp::value(_("ItemDefinition"), _("category"));
	itemid = il2cpp::value(_("ItemDefinition"), _("itemid"));
	displayName = il2cpp::value(_("ItemDefinition"), _("displayName"));

	viewOffset = il2cpp::value(_("PlayerEyes"), _("viewOffset"));

	swimming = il2cpp::value(_("PlayerWalkMovement"), _("swimming"));
	ducking = il2cpp::value(_("BaseMovement"), _("<Ducking>k__BackingField"));
	TargetMovement = il2cpp::value(_("BaseMovement"), _("<TargetMovement>k__BackingField"));
	groundAngleNew = il2cpp::value(_("PlayerWalkMovement"), _("groundAngleNew"));
	flying = il2cpp::value(_("PlayerWalkMovement"), _("flying"));

	get_deltaTime = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_deltaTime"), 0, _(""), _("UnityEngine"))));

	get_IsNpc = reinterpret_cast<bool(*)(uintptr_t player_model)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerModel"), _("get_IsNpc"), -1, _(""), _(""))));

	get_time = reinterpret_cast<float(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Time"), _("get_time"), 0, _(""), _("UnityEngine"))));

	GetProjectileVelocityScale = reinterpret_cast<float(*)(BaseProjectile*, bool max)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("GetProjectileVelocityScale"), 1, _("getMax"), _(""), 1)));

	ClosestPoint = reinterpret_cast<Vector3(*)(BasePlayer*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ClosestPoint"), 1, _("position"), _(""), 1)));

	StartAttackCooldown = reinterpret_cast<void(*)(BaseProjectile*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AttackEntity"), _("StartAttackCooldown"), 1, _(""), _(""))));

	InverseTransformPoint = reinterpret_cast<Vector3(*)(Transform*, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("InverseTransformPoint"), 1, _(""), _("UnityEngine"))));

	ProcessAttack = reinterpret_cast<void(*)(BaseProjectile*, HitTest*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMelee"), _("ProcessAttack"), 1, _(""), _(""))));

#pragma endregion
}

class Object {

};

class Component : public Object {
public:
	Transform* get_transform() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Transform* (*)(Component*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("get_transform"), 0, _(""), _("UnityEngine"))));
		return off(this);
	}
};

class GameObject : public Object {
public:
	template<typename T>
	T get_class()
	{
		return *reinterpret_cast<T*>((uintptr_t)this + 0x30);
	}

	template<typename T>
	T get_class(uint32_t second_offset)
	{
		const auto object = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x30);
		if (!object)
			return nullptr;

		return *reinterpret_cast<T*>(object + second_offset);
	}

	char* get_prefab_name() { return *reinterpret_cast<char**>((uintptr_t)this + 0x60); }

	uint32_t get_tag() { return *reinterpret_cast<uint16_t*>((uintptr_t)this + 0x54); }

	rust::classes::layer get_layer() { return *reinterpret_cast<rust::classes::layer*>(this + 0x50); }
};

class Transform : public Component {
public:
	Vector3 up()
	{
		if (!(uintptr_t)this)
			return {};
		return get_up(this);
	}

	Vector3 get_object_position()
	{
		if (!(uintptr_t)this)
			return {};

		const auto visual_state = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x38);
		if (!visual_state)
			return {};

		return *reinterpret_cast<Vector3*>(visual_state + 0x90);
	}

	Vector3* get_position_ptr()
	{
		if (!(uintptr_t)this)
			return {};

		const auto visual_state = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x38);
		if (!visual_state)
			return {};

		return reinterpret_cast<Vector3*>(visual_state + 0x90);
	}

	Vector3 get_position() {
		if (!(uintptr_t)this)
			return {};
		auto off = reinterpret_cast<Vector3(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_position"), 0, _(""), _("UnityEngine"))));
		return off(this);
	}

	Vector4 get_rotation() {
		if (!(uintptr_t)this)
			return {};
		auto off = reinterpret_cast<Vector4(*)(Transform*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Transform"), _("get_rotation"), 0, _(""), _("UnityEngine"))));
		return off(this);
	}
};

class Behaviour : public Component {

};

class FacepunchBehaviour : public Behaviour {

};

class BaseMonoBehaviour : public FacepunchBehaviour {

};

class MonoBehaviour : public Behaviour {
public:
	Transform* get_transform()
	{
		// const auto unk = *reinterpret_cast< uintptr_t* >( this + 0x30 );

		return *reinterpret_cast<Transform**>((uintptr_t)this + 0x8);
	}
};

class Model : public MonoBehaviour {
public:
	FIELD(_("Model"), _("boneTransforms"), boneTransforms, System::Array<Transform*>*);
};

class BaseNetworkable : public BaseMonoBehaviour {
public:
	//FIELD(_("BaseNetworkable"), _("net"), net, Networkable*);

};

class BaseEntity : public BaseNetworkable {
public:
	FIELD(_("BaseEntity"), _("model"), model, Model*);

	Vector3 GetWorldVelocity() {
		if (!this) return Vector3(0, 0, 0);
		auto off = reinterpret_cast<Vector3(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("GetWorldVelocity"), 0, _(""), _(""))));
		return off(this);
	}
	Vector3 GetParentVelocity() {
		if (!this) return Vector3(0, 0, 0);
		auto off = reinterpret_cast<Vector3(*)(BaseEntity*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("GetParentVelocity"), 0, _(""), _(""))));
		return off(this);
	}
	void ServerRPC(wchar_t* func) {
		if (!this) return;
		auto off = reinterpret_cast<void (*)(BaseEntity*, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("ServerRPC"), 1, _("funcName"), _(""), 1)));
		return off(this, func);
	}
	Transform* FindBone(wchar_t* bone) {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Transform * (*)(BaseEntity*, System::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseEntity"), _("FindBone"), 1, _(""), _(""))));
		return off(this, bone);
	}
	bool is_visible(Vector3 source, Vector3 destination, float p1 = 0.18f) {
		return unity::is_visible(source, destination, (uintptr_t)this, p1);
	}
};

class BaseCombatEntity : public BaseEntity {
public:
	FIELD(_("BaseCombatEntity"), _("lifestate"), lifestate, BaseCombatEntity_LifeState);
	FIELD(_("BaseCombatEntity"), _("_health"), health, float);
	FIELD(_("BaseCombatEntity"), _("_maxHealth"), maxHealth, float);

	bool is_alive() {
		if (!this) return false;
		return this->lifestate() == BaseCombatEntity_LifeState::Alive;
	}
};

class HeldEntity : public BaseEntity {

};

class BaseHelicopter_Weakspot {

};

class BaseHelicopter : public BaseCombatEntity {
public:
	FIELD(_("BaseHelicopter"), _("weakspots"), weakspots, System::list<BaseHelicopter_Weakspot*>*);
};

class ItemModProjectile : public MonoBehaviour {
public:
	FIELD(_("ItemModProjectile"), _("projectileVelocity"), projectileVelocity, float);
	FIELD(_("ItemModProjectile"), _("projectileSpread"), projectileSpread, float);
	FIELD(_("ItemModProjectile"), _("projectileVelocitySpread"), projectileVelocitySpread, float);
};

class BasePlayer;

class RecoilProperties {
	
};

class DamageProperties {

};

class HitTest {
public:
	enum HitTest_Type {
		Generic = 0,
		ProjectileEffect = 1,
		Projectile = 2,
		MeleeAttack = 3,
		Use = 4
	};

	FIELD(_("HitTest"), _("type"), type, HitTest_Type);
	FIELD(_("HitTest"), _("AttackRay"), AttackRay, Ray);
	FIELD(_("HitTest"), _("Radius"), Radius, float);
	FIELD(_("HitTest"), _("MaxDistance"), MaxDistance, float);
	FIELD(_("HitTest"), _("BestHit"), BestHit, bool);
	FIELD(_("HitTest"), _("DidHit"), DidHit, bool);
	FIELD(_("HitTest"), _("damageProperties"), damageProperties, DamageProperties*);
	FIELD(_("HitTest"), _("ignoreEntity"), ignoreEntity, BaseEntity*);
	FIELD(_("HitTest"), _("HitEntity"), HitEntity, BaseEntity*);
	FIELD(_("HitTest"), _("HitPoint"), HitPoint, Vector3);
	FIELD(_("HitTest"), _("HitNormal"), HitNormal, Vector3);
	FIELD(_("HitTest"), _("HitDistance"), HitDistance, float);
	FIELD(_("HitTest"), _("HitTransform"), HitTransform, Transform*);
	FIELD(_("HitTest"), _("HitPart"), HitPart, UINT);
	FIELD(_("HitTest"), _("HitMaterial"), HitMaterial, System::string);
	FIELD(_("HitTest"), _("gameObject"), gameObject, GameObject*);
};

class GatherPropertyEntry {
public:
	float& gatherDamage() {
		return *reinterpret_cast<float*>((uintptr_t)this + 0x10);
	}

	float& destroyFraction() {
		return *reinterpret_cast<float*>((uintptr_t)this + 0x14);
	}

	float& conditionLost() {
		return *reinterpret_cast<float*>((uintptr_t)this + 0x18);
	}
};

class ItemDefinition : public MonoBehaviour {
public:
};

class GatherProperties {
public:
	GatherPropertyEntry*& tree() {
		return *reinterpret_cast<GatherPropertyEntry**>((uintptr_t)this + 0x10);
	}

	GatherPropertyEntry*& ore() {
		return *reinterpret_cast<GatherPropertyEntry**>((uintptr_t)this + 0x18);
	}
};

class AttackEntity : public HeldEntity {
public:
	FIELD(_("AttackEntity"), _("nextAttackTime"), nextAttackTime, float);
	FIELD(_("AttackEntity"), _("timeSinceDeploy"), timeSinceDeploy, float);
	FIELD(_("AttackEntity"), _("deployDelay"), deployDelay, float);
	FIELD(_("AttackEntity"), _("repeatDelay"), repeatDelay, float);
};

class BaseMelee : public AttackEntity {
public:
	FIELD(_("BaseMelee"), _("gathering"), gathering, GatherProperties*);
	FIELD(_("BaseMelee"), _("damageProperties"), damageProperties, DamageProperties*);
};

class Magazine {
	
};

class BaseProjectile : public AttackEntity {
public:	
	FIELD(_("BaseProjectile"), _("reloadTime"), reloadTime, float);
	FIELD(_("BaseProjectile"), _("nextReloadTime"), nextReloadTime, float);
	FIELD(_("BaseProjectile"), _("recoil"), recoil, RecoilProperties*);
	FIELD(_("BaseProjectile"), _("automatic"), automatic, bool);
	FIELD(_("BaseProjectile"), _("aimSway"), aimSway, float);
	FIELD(_("BaseProjectile"), _("aimSwaySpeed"), aimSwaySpeed, float);
	FIELD(_("BaseProjectile"), _("primaryMagazine"), primaryMagazine, Magazine*);
	FIELD(_("BaseProjectile"), _("aimCone"), aimCone, float);
	FIELD(_("BaseProjectile"), _("hipAimCone"), hipAimCone, float);
	FIELD(_("BaseProjectile"), _("aimConePenaltyMax"), aimConePenaltyMax, float);
	FIELD(_("BaseProjectile"), _("aimconePenaltyPerShot"), aimconePenaltyPerShot, float);
	FIELD(_("BaseProjectile"), _("stancePenaltyScale"), stancePenaltyScale, float);
	FIELD(_("BaseProjectile"), _("projectileVelocityScale"), projectileVelocityScale, float);
	


	void set_last_hit_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + lastHitTime) = time;
	}

	void set_last_hit_material(System::string material) {
		*reinterpret_cast<System::string*>((uintptr_t)this + lastHitMaterial) = material;
	}

	char* get_class_name() {
		auto bp = *reinterpret_cast<uintptr_t*>(this);
		return (char*)*reinterpret_cast<uintptr_t*>(bp + 0x10);
	}

	HitTest* get_hit_test() {
		return *reinterpret_cast<HitTest**>((uintptr_t)this + hitTest);
	}

	void set_integrity(float to_set) {
		*reinterpret_cast<float*>((uintptr_t)this + integrity) = to_set;
	}

	ItemModProjectile* get_item_mod_projectile() {
		return *reinterpret_cast<ItemModProjectile**>((uintptr_t)this + mod);
	}

	weapon_stats_t get_stats(int32_t weapon_id) {
		const auto primary_magazine = (uintptr_t)this->primaryMagazine();//*reinterpret_cast<uintptr_t*>((uintptr_t)this + primaryMagazine);
		if (!primary_magazine)
			return weapon_stats_t{ xf(1000) };

		float velocity = xf(1000);
		float gravity_modifier = xf(1);
		float drag = xf(.001f);
		float distance = xf(0);

		auto velocity_scale = xf(1);
		bool scale_velocity = false;

		const auto ammo_definition = *reinterpret_cast<uintptr_t*>(primary_magazine + 0x20);
		if (ammo_definition) {
			// itemid
			const auto ammo_id = *reinterpret_cast<int32_t*>(ammo_definition + 0x18);

			switch (ammo_id) {
			case shotgun:
				velocity = xf(225);
				drag = xf(1);
				distance = xf(3);
				break;
			case shotgun_slug:
				velocity = xf(225);
				drag = xf(1);
				distance = xf(10);
				break;
			case shotgun_fire:
				velocity = 100;
				drag = 1;
				distance = 3;
				break;
			case shotgun_handmade:
				velocity = 100;
				drag = 1;
				distance = 0;
				break;
			case rifle_556:
				velocity = 375;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_hv:
				velocity = 450;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_fire:
				velocity = 225;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_explosive:
				velocity = 225;
				gravity_modifier = 1.25;
				drag = .6;
				distance = 15;
				break;
			case pistol:
				velocity = 300;
				drag = .7;
				distance = 15;
				break;
			case pistol_hv:
				velocity = 400;
				drag = .7;
				distance = 15;
				break;
			case pistol_fire:
				velocity = 225;
				drag = .7;
				distance = 15;
				break;
			case arrow_wooden:
				velocity = 50;
				gravity_modifier = .75;
				drag = .005;
				break;
			case arrow_hv:
				velocity = 80;
				gravity_modifier = .5;
				drag = .005;
				break;
			case arrow_fire:
				velocity = 40;
				gravity_modifier = 1;
				drag = .01;
				break;
			case arrow_bone:
				velocity = 45;
				gravity_modifier = .75;
				drag = .01;
				break;
			case nailgun_nails:
				velocity = 50;
				gravity_modifier = .75;
				drag = .005;
				break;
			}

			scale_velocity = true;
			velocity_scale =
				GetProjectileVelocityScale(this, false);
		}

		switch (weapon_id) {
		case spear_wooden:
			velocity = 25;
			scale_velocity = false;
			gravity_modifier = 2;
			drag = .1f;
			distance = .25f;
			break;
		case spear_stone:
			velocity = 30;
			scale_velocity = false;
			gravity_modifier = 2;
			drag = .1f;
			distance = .25f;
			break;
		}

		if (scale_velocity && (velocity_scale != 0))
			velocity *= velocity_scale;

		return { velocity, gravity_modifier, drag, distance };
	}

	Vector3 get_current_position() {
		return *reinterpret_cast<Vector3*>((uintptr_t)this + currentPosition);
	}

	void set_current_position(Vector3 cp) {
		*reinterpret_cast<Vector3*>((uintptr_t)this + currentPosition) = cp;
	}

	void set_travel_time(float f) {
		*reinterpret_cast<float*>((uintptr_t)this + traveledTime) = f;
	}

	void set_current_velocity(Vector3 position)
	{
		*reinterpret_cast<Vector3*>((uintptr_t)this + currentVelocity) = position;
	}

	uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

	float oyx = 0.f;
	float oyy = 0.f;
	float opx = 0.f;
	float opy = 0.f;

	void set_recoil() {
		auto recoil_properties = (uintptr_t)this->recoil();//*reinterpret_cast<uintptr_t*>((uintptr_t)this + recoil);
		
		float recoilx = vars->combat.recoilx;
		float recoily = vars->combat.recoily;

		//after update June 5th 2022
		auto new_recoil_properties = *reinterpret_cast<uintptr_t*>((uintptr_t)recoil_properties + 0x78);

		if (new_recoil_properties)
		{
			*reinterpret_cast<float*>(new_recoil_properties + 0x18) = recoily; //yaw min
			*reinterpret_cast<float*>(new_recoil_properties + 0x1C) = recoily; //yaw max
			*reinterpret_cast<float*>(new_recoil_properties + 0x20) = -recoilx; //pitch min
			*reinterpret_cast<float*>(new_recoil_properties + 0x24) = -recoilx; //pitch max
			//*reinterpret_cast<float*>(new_recoil_properties + 0x2C) = lastrecoil * recoil; //timeToTakeMax
			//*reinterpret_cast<float*>(new_recoil_properties + 0x30) = recoil; //ADSScale
		}
		else
		{
			*reinterpret_cast<float*>(recoil_properties + 0x18) = recoily; //yaw min
			*reinterpret_cast<float*>(recoil_properties + 0x1C) = recoily; //yaw max
			*reinterpret_cast<float*>(recoil_properties + 0x20) = -recoilx; //pitch min
			*reinterpret_cast<float*>(recoil_properties + 0x24) = -recoilx; //pitch max
			//*reinterpret_cast<float*>(recoil_properties + 0x2C) = lastrecoil * recoil; //timeToTakeMax
			//*reinterpret_cast<float*>(recoil_properties + 0x30) = recoil; //ADSScale
		}
	}

	void set_no_spread(float scale = 0.f) {
		auto recoil_properties = this->recoil();//*reinterpret_cast<uintptr_t*>((uintptr_t)this + recoil);
		auto new_recoil_properties = *reinterpret_cast<uintptr_t*>((uintptr_t)recoil_properties + 0x78);
		this->aimCone() = scale;
		this->hipAimCone() = scale;
		this->aimConePenaltyMax() = scale;
		this->aimconePenaltyPerShot() = scale;
		this->stancePenaltyScale() = scale;

		if(new_recoil_properties)
			*reinterpret_cast<float*>(new_recoil_properties + 0x60) = scale; //aimconeCurveScale
		else *reinterpret_cast<float*>(recoil_properties + 0x60) = scale; //aimconeCurveScale
	}

	void set_success_fraction() {
		*reinterpret_cast<float*>((uintptr_t)this + successFraction) = 1.f;
	}

	//////EOKA/////
	void set_did_spark_this_frame(bool state) {
		*reinterpret_cast<bool*>((uintptr_t)this + didSparkThisFrame) = state;
	}
};

class PlayerNameID {
public:
	wchar_t* get_username() {
		auto username = (str)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x18));

		return username->str;
	}

	unsigned long get_user_id()
	{
		return *reinterpret_cast<unsigned long*>((uintptr_t)this + 0x20);
	}
};

class Item {
public:
	FIELD(_("Item"), _("heldEntity"), heldEntity, HeldEntity*);

	uintptr_t get_icon_sprite() {
		const auto     item_definition = mem::read<uintptr_t>((uintptr_t)this + info);
		if (!item_definition)
			return 0;

		return *reinterpret_cast<uintptr_t*>(item_definition + iconSprite);
	}

	uintptr_t get_steam_icon_sprite() {
		const auto     item_definition = mem::read<uintptr_t>((uintptr_t)this + info);
		if (!item_definition)
			return 0;

		auto SteamInventoryItem = *reinterpret_cast<uintptr_t*>(item_definition + steamItem);
		if (!SteamInventoryItem)
			return 0;

		return *reinterpret_cast<uintptr_t*>(SteamInventoryItem + 0x20);
	}

	int GetAmount()
	{
		return *reinterpret_cast<int*>(this + 0x30);
	}

	wchar_t* get_weapon_name() {
		auto item_def = *reinterpret_cast<uintptr_t*>((uintptr_t)this + info);
		if (!item_def)
			return {};

		auto display_name = *reinterpret_cast<uintptr_t*>(item_def + displayName);
		if (!display_name)
			return {};

		auto weapon_name = (str)(*reinterpret_cast<uintptr_t*>(display_name + 0x18));

		return weapon_name->str;
	}

	bool is_weapon() {
		const auto     item_definition = mem::read<uintptr_t>((uintptr_t)this + info);
		if (!item_definition)
			return false;

		return mem::read<uint32_t>(item_definition + category) == 0;
	}

	int32_t get_item_definition_id()
	{
		const auto     item_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)this + info);
		if (!item_definition)
			return 0;

		return *reinterpret_cast<int32_t*>(item_definition + itemid);
	}

	template<typename T>
	T* GetHeldEntity() {
		if (!this) return nullptr;
		return ((T*)this->heldEntity());
	}
};

class ModelState {
public:
	void set_water_level(float water_level) {
		*reinterpret_cast<float*>((uintptr_t)this + 0x14) = water_level;
	}

	void setjumped(bool j) {
		if (!this) return;
		return set_jumped((uintptr_t)this, j);
	}

	void remove_flag(rust::classes::ModelState_Flag flag) {
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);
		flags &= ~(int)flag;

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags;
	}

	void set_flag(rust::classes::ModelState_Flag flag) {
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags |= (int)flag;
	}

	bool has_flag(rust::classes::ModelState_Flag f)
	{
		int& flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		return (flags & (int)f) == (int)f;
	}
};

class BaseMovement : public MonoBehaviour {
public:
};

class PlayerWalkMovement : public BaseMovement {
public:
	void set_swimming(bool flag) {
		*reinterpret_cast<bool*>((uintptr_t)this + swimming) = flag;
	}
	bool get_swimming() {
		return *reinterpret_cast<bool*>((uintptr_t)this + swimming);
	}
	float get_ducking() {
		return *reinterpret_cast<float*>((uintptr_t)this + ducking);
	}
	void set_TargetMovement(Vector3 v) {
		*reinterpret_cast<Vector3*>((uintptr_t)this + TargetMovement) = v;
	}
	Vector3 get_TargetMovement() {
		return *reinterpret_cast<Vector3*>((uintptr_t)this + TargetMovement);
	}
	bool get_admin_cheat() {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x18);
	}

	uintptr_t get_body() {
		return *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0xA0);
	}

	Vector3 get_body_velocity() {
		return get_rigidbody_velocity(get_body());
	}

	void set_body_velocity(Vector3 v) {
		set_rigidbody_velocity(get_body(), v);
	}

	void set_admin_cheat(bool admin_cheat) {
		*reinterpret_cast<bool*>((uintptr_t)this + 0x18) = admin_cheat;
	}

	bool get_flying() {
		return *reinterpret_cast<bool*>((uintptr_t)this + flying);
	}

	bool get_grounded() {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x140); //private bool grounded
	}

	bool get_climbing() {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x141); //private bool climbing
	}

	bool get_sliding() {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x142); //private bool sliding
	}

	void force_jump(ModelState* state, bool indirection = false) {
		if (!this) return;
		return do_jump((uintptr_t)this, (uintptr_t)state, indirection);
	}

	void set_flying(bool fly) {
		*reinterpret_cast<bool*>((uintptr_t)this + flying) = fly;
	}

	void set_ground_angles_new(float angle) {
		*reinterpret_cast<float*>((uintptr_t)this + groundAngleNew) = angle;
	}

	void set_land_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + landTime) = time;
	}

	void set_jump_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + jumpTime) = time;
	}

	void set_ground_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + groundTime) = time;
	}

	void set_gravity_multiplier(float multiplier) {
		*reinterpret_cast<float*>((uintptr_t)this + gravityMultiplier) = multiplier;
	}

	bool set_grounded(bool g) {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x140) = g; //private bool grounded
	}

	bool set_climbing(bool g) {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x141) = g; //private bool climbing
	}

	bool set_sliding(bool g) {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x142) = g; //private bool sliding
	}

	void teleport_to(Vector3 p, BasePlayer* ply) {
		return teleportto((uintptr_t)this, p, (uintptr_t)ply);
	}
};

auto cliententities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);

class Networkable {
public:
	unsigned int get_id() {
		return *reinterpret_cast<unsigned int*>((uintptr_t)this + 0x10);
	}

	template<typename T = uintptr_t>
	T* GetComponent(uintptr_t type) {
		if (!this || !type) return nullptr;
		return (T*)get_component((uintptr_t)this, type);
	}

	System::list<uintptr_t>* GetComponentsInChildren(uintptr_t type) {
		if (!this || !type) return nullptr;
		return reinterpret_cast<System::list<uintptr_t>*>(get_components_in_children((uintptr_t)this, type));
	}
};

class BaseNetwork {
public:
};

class Client : public BaseNetwork {
public:
	
};

class aim_target {
public:
	Vector3 pos;

	BaseCombatEntity* ent = NULL;

	float distance = 5000;
	float fov = vars->combat.aimbotfov;

	int network_id;

	bool is_heli = false;
	bool visible = false;
	bool sleeping = false;
	bool teammate = false;
	bool found = false;

	/*Velocity related shit*/
	Vector3 avg_vel = Vector3(0, 0, 0);
	std::vector<Vector3> velocity_list = {};
	float last_frame = 0.f; // overwrite every fixedtime + deltatime

	bool operator<(const aim_target& b) {
		if (fov == vars->combat.aimbotfov) {
			return distance < b.distance;
		}
		else {
			return fov < b.fov;
		}
	}
};

float get_2d_dist(const Vector2& Src, const Vector3& Dst) {
	return Vector3::my_sqrt(powFFFFFFFFFFFFFFFFFFFFFF(Src.x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(Src.y - Dst.y));
}

class PlayerEyes : public Component {
public:
	void set_view_offset(Vector3 offset) {
		*reinterpret_cast<Vector3*>((uintptr_t)this + viewOffset) = offset;
	}

	Vector3 get_view_offset() {
		return *reinterpret_cast<Vector3*>((uintptr_t)this + viewOffset);
	}

	Vector3 get_position() {
		if (!this) return Vector3(0, 0, 0);
		return PEyes_get_position((uintptr_t)this);
	}
	
	Vector4 get_rotation() {
		if (!this) return Vector4(0, 0, 0, 0);
		return PEyes_get_rotation((uintptr_t)this);
	}

	Vector3 body_forward() {
		if (!this) return Vector3(0, 0, 0);
		return bodyforward((uintptr_t)this);
	}

	Vector3 GetCenter() {
		if (!this) return Vector3(0, 0, 0);
		return get_center((uintptr_t)this);
	}
};

class InputState {
public:
	void set_aim_angles(Vector3 aim_angle) {
		auto current = mem::read<uintptr_t>((uintptr_t)this + 0x10);

		*reinterpret_cast<Vector3*>(current + 0x18) = aim_angle;
	}

};

class BaseMountable : public BaseCombatEntity {
public:
	bool& canwielditem() {
		return *reinterpret_cast<bool*>((uintptr_t)this + canWieldItems);
	}
};

class Shader : public Object {
public:

};

class Material : public Object {
public:
	Shader* GetShader() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Shader*(*)(Material*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("get_shader"), 0, _(""), _("UnityEngine"))));
		return off(this);
	}
	void SetShader(Shader* s) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material*, Shader*)>(il2cpp::methods::resolve_icall(_("UnityEngine.Material::set_shader()")));
		return off(this, s);
	}
	void SetColor(System::string s, col c) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material*, System::string, col)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetColor"), 2, _("name"), _("UnityEngine"), 1)));
		return off(this, s, c);
	}
};

class Renderer : public Component {
public:
	Material* GetMaterial() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Material*(*)(Renderer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("get_material"), 0, _(""), _("UnityEngine"))));
		return off(this);
	}
};

class SkinnedMultiMesh : public MonoBehaviour {
public:	

	System::list<Renderer*>* get_Renderers() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<System::list<Renderer*>*(*)(SkinnedMultiMesh*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinnedMultiMesh"), _("get_Renderers"), 0, _(""), _(""))));
		return off(this);
	}
};

class PlayerInput : public Component {
public:
	FIELD(_("PlayerInput"), _("state"), state, InputState*);
	FIELD(_("PlayerInput"), _("bodyAngles"), bodyAngles, Vector3);
	FIELD(_("PlayerInput"), _("recoilAngles"), recoilAngles, Vector3);
};

class PlayerModel : public Component {
public:
	FIELD(_("PlayerModel"), _("newVelocity"), newVelocity, Vector3);
	FIELD(_("PlayerModel"), _("isLocalPlayer"), isLocalPlayer, bool);
	FIELD(_("PlayerModel"), _("_multiMesh"), _multiMesh, SkinnedMultiMesh*);

	bool isnpc() {
		if (!this) return false;
		auto off = reinterpret_cast<bool(*)(PlayerModel*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerModel"), _("get_IsNpc"), -1, _(""), _(""))));
		return off(this);
	}
};

class BasePlayer : public BaseCombatEntity {
public:
	FIELD(_("BasePlayer"), _("playerModel"), playerModel, PlayerModel*);
	FIELD(_("BasePlayer"), _("input"), input, PlayerInput*);
	FIELD(_("BasePlayer"), _("movement"), movement, PlayerWalkMovement*);
	FIELD(_("BasePlayer"), _("_lookingAtEntity"), _lookingAtEntity, BaseEntity*);
	FIELD(_("BasePlayer"), _("clActiveItem"), clActiveItem, UINT);
	FIELD(_("BasePlayer"), _("modelState"), modelState, ModelState*);
	FIELD(_("BasePlayer"), _("eyes"), eyes, PlayerEyes*);
	FIELD(_("BasePlayer"), _("lastSentTickTime"), lastSentTickTime, float);
	FIELD(_("BasePlayer"), _("net"), net, Networkable*);
	FIELD(_("BasePlayer"), _("_displayName"), _displayName, str);
	FIELD(_("BasePlayer"), _("userID"), userID, ULONG);
	FIELD(_("BasePlayer"), _("clientTickInterval"), clientTickInterval, float);
	FIELD(_("BasePlayer"), _("mounted"), mounted, BaseMountable*);
	
	void GroundAngleNew() {
		*reinterpret_cast<float*>(this + 0xb0) = -1.0f;
	}
	
	float GetJumpHeight() {
		return _getjumpheight(this);
	}

	float GetRadius() {
		return _GetRadius(this);
	}

	float BoundsPadding() {
		if (!this) return 0;
		return _BoundsPadding(this);
	}

	float max_velocity() {
		if (!this) return 0.f;

		float s = get_maxspeed(this);
		auto m = this->mounted() || vars->misc.interactive_debug;
		if (m)
			return s * 4;
		return s;
	}

	void SendClientTick() {
		if (!this) return;
		return _SendClientTick(this);
	}

	protobuf::PlayerTick* lastSentTick() {
		return *reinterpret_cast<protobuf::PlayerTick**>((uintptr_t)this + 0x660);
	}

	wchar_t* get_player_name() {
		auto player_name = (str)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x6E8)); //zzzz
		return player_name->str;
	}

	void SendSignalBroadcast(rust::classes::Signal signal, wchar_t* str = _(L""))
	{
		if (!this) return;
		return SendSignal((uintptr_t)this, signal, System::string(str));
	}

	void fov() {
		bool zooming = false;


		if (vars->visual.zoomtoggle && unity::GetKey((rust::classes::KeyCode)vars->keybinds.zoom)) {
			zooming = true;
		}
		else {
			zooming = false;
		}

		if (zooming) {//0x32182E0
			//auto convar = *reinterpret_cast<uintptr_t*>((uintptr_t)mem::game_assembly_base + 52689952); //"ConVar_Graphics_c*" alkad rust
			auto convar = *reinterpret_cast<uintptr_t*>((uintptr_t)mem::game_assembly_base + 52698272); //"	" real rust
			auto unknown = *reinterpret_cast<uintptr_t*>((uintptr_t)convar + 0xb8);
			*reinterpret_cast<float*>(unknown + 0x18) = vars->visual.zoomfov;
		}

		if (!zooming) {
			auto convar = *reinterpret_cast<uintptr_t*>((uintptr_t)mem::game_assembly_base + 52698272); //"ConVar_Graphics_c*" real rust
			//auto convar = *reinterpret_cast<uintptr_t*>((uintptr_t)mem::game_assembly_base + 52527840); //"ConVar_Graphics_c*" alkad rust
			auto unknown = *reinterpret_cast<uintptr_t*>((uintptr_t)convar + 0xb8);
			*reinterpret_cast<float*>(unknown + 0x18) = vars->visual.playerfov;
		}
	}

	void set_admin_flag(rust::classes::PlayerFlags flag) {
		int PlayerFlag = *reinterpret_cast<int*>((uintptr_t)this + playerFlags);

		*reinterpret_cast<int*>((uintptr_t)this + playerFlags) = PlayerFlag |= (int)flag;
	}

	bool is_teammate(BasePlayer* local_player) {
		auto team = mem::read<uintptr_t>((uintptr_t)local_player + clientTeam);

		auto member = mem::read<uintptr_t>(team + 0x30);

		auto size = mem::read<int>(member + 0x18);

		auto list = mem::read<uintptr_t>(member + 0x10);

		auto steam_id = this->userID();

		for (int i = 0; i < size; i++) {
			auto ent = mem::read<uintptr_t>(list + 0x20 + i * 0x8);

			auto id = mem::read<unsigned long>(ent + 0x20);

			if (id == steam_id)
				return true;
		}
		return false;
	}

	//auto lastSentTickTime() {
	//	return *reinterpret_cast<float*>((uintptr_t)this + _lastSentTickTime);
	//}

	System::list<Item*>* get_belt_items()
	{
		const auto inventory = *reinterpret_cast<uintptr_t*>((uintptr_t)this + player_inventory);
		if (!inventory)
			return {};

		const auto container_belt = *reinterpret_cast<uintptr_t*>(inventory + containerBelt);
		if (!container_belt)
			return {};

		// get_once(uint32_t, itemList, 0, get_offset("ItemContainer", "itemList"));
		const auto list_wrapper = *reinterpret_cast<uintptr_t*>(container_belt + itemList);
		if (!list_wrapper)
			return {};

		const auto item_list =
			*reinterpret_cast<System::list<Item*>**>(list_wrapper + 0x10);
		if (!item_list)
			return {};

		return item_list;
	}

	System::list<Item*>* get_wearable_items()
	{
		const auto     inventory = *reinterpret_cast<uintptr_t*>((uintptr_t)this + player_inventory);
		if (!inventory)
			return {};

		const auto container_belt = *reinterpret_cast<uintptr_t*>(inventory + containerWear);
		if (!container_belt)
			return {};

		// get_once(uint32_t, itemList, 0, get_offset("ItemContainer", "itemList"));
		const auto list_wrapper = *reinterpret_cast<uintptr_t*>(container_belt + itemList);
		if (!list_wrapper)
			return {};

		const auto item_list =
			*reinterpret_cast<System::list<Item*>**>(list_wrapper + 0x10);
		if (!item_list)
			return {};

		return item_list;
	}

	template<typename T = Networkable*>
	T find_closest(char* class_name , Networkable* target_entity, float max_distance) {
		auto client_entities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
		if (!client_entities)
			return { nullptr };

		rust::classes::list* entity_list = (rust::classes::list*)client_entities; 
		
		auto list_value = entity_list->get_value<uintptr_t>();
		if (!list_value)
			return { nullptr };

		auto size = entity_list->get_size();
		if (!size)
			return { nullptr };

		auto buffer = entity_list->get_buffer<uintptr_t>();
		if (!buffer)
			return { nullptr };

		auto closest_entity_distance = 9999;
		T best_ent = nullptr;

		for (int i = 0; i <= size; i++) {
			auto current_object = *reinterpret_cast<uintptr_t*>(buffer + 0x20 + (i * 0x8));
			if (!current_object)
				continue;

			auto base_object = *reinterpret_cast<uintptr_t*>(current_object + 0x10);
			if (!base_object)
				continue;

			auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
			if (!object)
				continue;

			auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);
			auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
			auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);

			auto name = *(int*)(entity_class_name);

			auto target_position = ((BaseEntity*)target_entity)->get_transform()->get_position();
			auto ent_position = ((BaseEntity*)ent)->get_transform()->get_position();
			auto best_position = Vector3(0, 0, 0);
			if(best_ent)
				best_position = ((BaseEntity*)best_ent)->get_transform()->get_position();

			if (!LI_FIND(strcmp)(entity_class_name, class_name)
				&& ent_position.distance(target_position) < max_distance
				&& (!best_ent || ent_position.distance(target_position) < best_position.distance(target_position)))
			{
				best_ent = reinterpret_cast<T>(ent);
			}
		}
		return best_ent;
	}

	std::pair<aim_target, bool> resolve_closest_entity(float max_distance, bool get_code = true) {
		aim_target closest_entity;
		auto client_entities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
		if (!client_entities)
			return { closest_entity, false };

		rust::classes::list* entity_list = (rust::classes::list*)client_entities;

		auto list_value = entity_list->get_value<uintptr_t>();
		if (!list_value)
			return { closest_entity, false };

		auto size = entity_list->get_size();
		if (!size)
			return { closest_entity, false };

		auto buffer = entity_list->get_buffer<uintptr_t>();
		if (!buffer)
			return { closest_entity, false };

		auto closest_entity_distance = 9999;
		bool is_code_lock = false;/*iscodelock/is_tree*/

		for (int i = 0; i <= size; i++) {
			auto current_object = *reinterpret_cast<uintptr_t*>(buffer + 0x20 + (i * 0x8));
			if (!current_object)
				continue;

			auto base_object = *reinterpret_cast<uintptr_t*>(current_object + 0x10);
			if (!base_object)
				continue;

			auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
			if (!object)
				continue;

			auto ent = *reinterpret_cast<uintptr_t*>(base_object + 0x28);
			auto ent_class = *reinterpret_cast<uintptr_t*>(ent);
			auto entity_class_name = (char*)*reinterpret_cast<uintptr_t*>(ent_class + 0x10);

			auto name = *(int*)(entity_class_name);

			if (get_code) {

				if (!(name == 'edoC') && !(name == 'LyeK'))
					continue;

				if (name == 'edoC')
					is_code_lock = true;

				auto flag = *reinterpret_cast<int*>(ent + 0x128);

				if (flag == 16)//Locked
					continue;
			}
			else {
				if (name != 'eerT' && name != 'HerO')
					continue;

				if (name == 'HerO')
					is_code_lock = false;
				else
					is_code_lock = true;

				if (name == 'eerT') {
					if (*(int*)(entity_class_name + 4) != 'itnE')
						continue;
				}
			}

			auto game_object = *reinterpret_cast<uintptr_t*>(object + 0x30);

			auto Transform = *reinterpret_cast<uintptr_t*>(game_object + 0x8);

			auto visual_state = *reinterpret_cast<uintptr_t*>(Transform + 0x38);

			auto world_position = *reinterpret_cast<Vector3*>(visual_state + 0x90);

			auto bone_pos = this->model()->boneTransforms()->get(48)->get_position();

			auto distance = bone_pos.get_3d_dist(world_position);
			if (distance < closest_entity_distance && distance < max_distance) {
				auto object_class = *reinterpret_cast<uintptr_t*>(object + 0x30);
				if (!object_class)
					continue;

				auto entity = *reinterpret_cast<uintptr_t*>(object_class + 0x18);
				if (!entity)
					continue;

				auto baseentity = *reinterpret_cast<uintptr_t*>(entity + 0x28);
				if (!baseentity)
					continue;

				auto ent = reinterpret_cast<BasePlayer*>(baseentity);

				aim_target new_target;

				auto local = ClosestPoint(this, world_position);
				if (local.get_3d_dist(world_position) >= max_distance)
					continue;

				new_target.pos = world_position;
				new_target.ent = (BasePlayer*)ent;
				new_target.visible = /*unity::is_visible(bone_pos, world_position)*/true;
				new_target.found = true;

				closest_entity_distance = distance;
				closest_entity = new_target;
			}
		}

		return { closest_entity , is_code_lock };
	}

	bool is_sleeping()
	{
		auto Flags = *reinterpret_cast<int*>((uintptr_t)this + playerFlags);
		return Flags & 16;
	}

	Item* GetActiveItem()
	{
		//unsigned int ActUID = this->clActiveItem();
		unsigned int ActUID = mem::read<unsigned int>((uintptr_t)this + 0x5D0); //private uint clActiveItem; //
		if (!ActUID)
			return 0;
		Item* ActWeapon;

		uint64_t Inventory = mem::read<uint64_t>((uintptr_t)this + player_inventory);
		uint64_t Belt = mem::read<uint64_t>(Inventory + 0x28);
		uint64_t ItemList = mem::read<uint64_t>(Belt + 0x38);

		auto items = mem::read<uint64_t>(ItemList + 0x10);
		if (!items)
			return 0;

		for (int i = 0; i < 6; i++) //For each slot	
		{
			Item* WeaponInfo = mem::read<Item*>(items + 0x20 + (i * 0x8));;

			unsigned int WeaponUID = mem::read<unsigned int>((uintptr_t)WeaponInfo + 0x28);
			if (!WeaponUID)
				return 0;
			if (ActUID == WeaponUID)
			{
				ActWeapon = WeaponInfo;
				return ActWeapon;
			}
		}
		return 0;
	}

	bool is_local_player() {
		if (!this)
			return false;

		auto player_model = this->playerModel();
		if (!player_model)
			return false;
		return player_model->isLocalPlayer();
	}

	GameObject* get_game_object()
	{
		if (!(uintptr_t)this)
			return nullptr;

		const auto unk0 = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		if (!unk0)
			return nullptr;

		const auto unk1 = *reinterpret_cast<GameObject**>(unk0 + 0x30);
		if (!unk1)
			return nullptr;

		return unk1;
	}

	void console_echo(const wchar_t* str) {
		//string::format(("%s %d"), _("B:"), (int)vars->visual.VisBcolor))
		//auto s = string::wformat(_(L"trap [%d]: %s"), (int)get_fixedTime(), str);
		console_msg((uintptr_t)this, str);
	}
};

class Planner : public HeldEntity {
public:
	Vector3 rotationoffset() { return mem::read<Vector3>((uintptr_t)this + planner_rotationoffset); }
	void rotationoffset(Vector3 o) { mem::write((uintptr_t)this + planner_rotationoffset, o); }
	uintptr_t currentconstruction() { return mem::read<uintptr_t>((uintptr_t)this + planner_currentconstruction); }
	void currentconstruction(uintptr_t o) { mem::write((uintptr_t)this + planner_rotationoffset, o); }
	uintptr_t guide() { return mem::read<uintptr_t>((uintptr_t)this + planner_guide); }
};

class DecayEntity : public Component {
public:
};

class StabilityEntity : public DecayEntity {
public:
};

class BuildingBlock : public StabilityEntity{
public:
	rust::classes::BuildingGrade grade() { 
		//public BuildingGrade.Enum grade; // 0x274
		return *reinterpret_cast<rust::classes::BuildingGrade*>((uintptr_t)this + 0x274);
	}

	bool CanAffordUpgrade(rust::classes::BuildingGrade g, BasePlayer* p) {
		if (!this) return false;

		typedef bool (*AAA)(uintptr_t, int, BasePlayer*);//real rust 7202688
		return ((AAA)(mem::game_assembly_base + 7202688))((uintptr_t)this, (int)g, p);
		//return canaffordupgrade((uintptr_t)this, g, p);
	}

	bool CanChangeToGrade(rust::classes::BuildingGrade g, BasePlayer* p) {
		if (!this) return false;

		typedef bool (*AAA)(uintptr_t, int, BasePlayer*);//real rust 7203152
		return ((AAA)(mem::game_assembly_base + 7203152))((uintptr_t)this, (int)g, p);
		//return canchangetograde((uintptr_t)this, g, p);
	}

	void Upgrade(rust::classes::BuildingGrade g, BasePlayer* p) {
		if (!this) return;
		return upgradetograde((uintptr_t)this, g, p);
	}
};

namespace ConVar {
	class Graphics {
	public:
		static float& _fov() {
			static auto clazz = il2cpp::find_class(_("Graphics"), _("ConVar"));//CLASS("Assembly-CSharp::ConVar::Graphics");
			return *reinterpret_cast<float*>(std::uint64_t(clazz + 0x00B8) + 0x18);
		}
	};
}

struct OBB {
public:
	Vector4 rotation;
	Vector3 position;
	Vector3 extents;
	Vector3 forward;
	Vector3 right;
	Vector3 up;
	float reject;
	OBB(Vector3 position, Vector4 rotation, Bounds bounds) {
		this->rotation = rotation;
		auto r = Vector3(rotation.x, rotation.y, rotation.z);
		this->position = (position + r).multiply(bounds.center);
		this->extents = bounds.extents;
		auto temp = rotation * Vector4(0, 0, 1, 0);
		this->forward = Vector3(temp.x, temp.y, temp.z);
		temp = rotation * Vector4(1, 0, 0, 0);
		this->right = Vector3(temp.x, temp.y, temp.z);
		temp = rotation * Vector4(0, 1, 0, 0);
		this->up = Vector3(temp.x, temp.y, temp.z);
		this->reject = this->extents.Length();
	}

	Vector3 ClosestPoint(Vector3 target)
	{
		bool flag = false;
		bool flag2 = false;
		bool flag3 = false;
		Vector3 vector = this->position;
		Vector3 lhs = target - this->position;
		float num = lhs.dot(this->right);
		if (num > this->extents.x)
		{
			vector += this->right * this->extents.x;
		}
		else if (num < -this->extents.x)
		{
			vector -= this->right * this->extents.x;
		}
		else
		{
			flag = true;
			vector += this->right * num;
		}
		float num2 = lhs.dot(this->up);
		if (num2 > this->extents.y)
		{
			vector += this->up * this->extents.y;
		}
		else if (num2 < -this->extents.y)
		{
			vector -= this->up * this->extents.y;
		}
		else
		{
			flag2 = true;
			vector += this->up * num2;
		}
		float num3 = lhs.dot(this->forward);
		if (num3 > this->extents.z)
		{
			vector += this->forward * this->extents.z;
		}
		else if (num3 < -this->extents.z)
		{
			vector -= this->forward * this->extents.z;
		}
		else
		{
			flag3 = true;
			vector += this->forward * num3;
		}
		if (flag && flag2 && flag3)
		{
			return target;
		}
		return vector;
	}

	float Distance(OBB other) {
		OBB obb = *this;
		OBB obb2 = other;
		Vector3 vector = obb.position;
		Vector3 vector2 = obb2.position;
		vector = obb.ClosestPoint(vector2);
		vector2 = obb2.ClosestPoint(vector);
		vector = obb.ClosestPoint(vector2);
		vector2 = obb2.ClosestPoint(vector);
		return vector.distance(vector2);
	}
	float Distance(Vector3 position) { return position.distance(this->ClosestPoint(position)); }
};

class _Line {
public:
	Vector3 start;
	Vector3 end;
	_Line(Vector3 s, Vector3 e) {
		start = s; end = e;
	}
	_Line() { }
	Vector3 ClosestPoint(Vector3 pos)
	{
		Vector3 a = end - start;
		float magnitude = a.Length();
		if (magnitude == 0.f) return start;
		Vector3 vector = a / magnitude;
		Vector3 lhs = pos - start;
		return start + vector * std::clamp(lhs.dot(vector), 0.f, magnitude);
	}
};

class TickInterpolator {
private:
	struct Segment {
		Vector3 point;
		float length;
		Segment(Vector3 a, Vector3 b) {
			this->point = b;
			this->length = a.distance(b);
		}
	};
public:
	std::vector<Segment> points = std::vector<Segment>();
	int index;
	float len;
	Vector3 currentPoint;
	Vector3 startPoint;
	Vector3 endPoint;

	void Reset() {
		this->index = 0;
		this->currentPoint = this->startPoint;
	}
	void Reset(Vector3 point) {
		this->points.clear();
		this->index = 0;
		this->len = 0.f;
		this->endPoint = point;
		this->startPoint = point;
		this->currentPoint = point;
	}
	void AddPoint(Vector3 point) {
		Segment segment = Segment(this->endPoint, point);
		this->points.push_back(segment);
		this->len += segment.length;
		this->endPoint = segment.point;
	}
	bool MoveNext(float distance) {
		float num = 0.f;
		while (num < distance && this->index < this->points.size()) {
			Segment segment = this->points[this->index];
			this->currentPoint = segment.point;
			num += segment.length;
			this->index++;
		}
		return num > 0.f;
	}
	bool HasNext() {
		return this->index < this->points.size();
	}
};

class TickHistory
{
public:
	std::vector<Vector3> points = {};
	int Count()
	{
		return points.size();
	}

	float Distance(BasePlayer* ent, Vector3 point)
	{
		Vector3 position = ent->get_transform()->get_position();
		if (Count() == 0)
		{
			return position.distance(point);
		}
		Vector4 rotation = ent->get_transform()->get_rotation();
		Bounds bounds = GetBounds((uintptr_t)ent);

		auto trans = ent->get_transform();
		bool flag = trans ? !(!trans) : false;
		VMatrix _mv; _mv.matrix_identity();
		VMatrix matrix4x = flag ? _mv : get_localToWorldMatrix(trans);

		VMatrix tickHistoryMatrix = matrix4x;
		float num = FLT_MAX;
		for (int i = 0; i < Count(); i++)
		{
			Vector3 point2 = tickHistoryMatrix.MultiplyPoint3x4(points[i]);
			Vector3 point3 = (i == Count() - 1) ? position : tickHistoryMatrix.MultiplyPoint3x4(points[i + 1]);
			_Line line(point2, point3);
			Vector3 position2 = line.ClosestPoint(point);
			OBB obb(position2, rotation, bounds);
			num = min(num, obb.Distance(point));
		}
		return num;
	}

	void AddPoint(Vector3 point, int limit = -1)
	{
		while (limit > 0 && Count() >= limit)
		{
			pop_front(this->points);
			//this->points.pop_back();
			//this->points.insert(this->points.begin(), 1, point);
		}
		this->points.push_back(point);
	}

	void TransformEntries(VMatrix matrix)
	{
		for (int i = 0; i < Count(); i++)
		{
			Vector3 vector = this->points[i];
			vector = matrix.MultiplyPoint3x4(vector);
			this->points[i] = vector;
		}
	}
};

void attack_melee(aim_target target, BaseProjectile* baseprojectile, bool is_player = false) {
	if (!target.visible)
		return;

	if (target.teammate)
		return;

	Vector3 local_position = unity::get_camera_pos();

	if (baseprojectile->nextAttackTime() >= get_time())
		return;

	if (baseprojectile->timeSinceDeploy() < baseprojectile->deployDelay())
		return;

	auto hit_test_class = il2cpp::init_class(_("HitTest"));
	if (!hit_test_class)
		return;

	HitTest* hit_test = (HitTest*)il2cpp::methods::object_new(hit_test_class);
	

	Ray ray = Ray(local_position, (target.pos - local_position).Normalized());

	Transform* trans = is_player ? target.ent->model()->boneTransforms()->get(48) : target.ent->get_transform();

	if (!trans)
		return;

	hit_test->MaxDistance() = 1000;
	hit_test->HitTransform() = trans;
	hit_test->AttackRay() = ray;
	hit_test->DidHit() = true;
	hit_test->HitEntity() = target.ent;
	hit_test->HitPoint() = InverseTransformPoint(trans, target.pos);
	hit_test->HitNormal() = Vector3(0, 0, 0);
	hit_test->damageProperties() = (DamageProperties*)*reinterpret_cast<uintptr_t*>(baseprojectile + 0x50);

	StartAttackCooldown(baseprojectile, baseprojectile->repeatDelay());

	return ProcessAttack(baseprojectile, hit_test);
}

Vector3 WorldToScreen(Vector3 position)
{
	auto matrix = unity::get_view_matrix();

	if (!matrix.m) {
		return { 0,0,0 };
	}
	Vector3 out;
	const auto temp = matrix.transpose();

	auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
	auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
	auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

	float w = translation_vector.dot(position) + temp[3][3];

	if (w < 0.098f) {
		return Vector3(0, 0, 0);
	}

	float x = up.dot(position) + temp._24;
	float y = right.dot(position) + temp._14;

	out.x = (static_cast<float>(unity::get_width()) / 2) * (1 + y / w);
	out.y = (static_cast<float>(unity::get_height()) / 2) * (1 - x / w);
	out.z = w;

	return out;
}