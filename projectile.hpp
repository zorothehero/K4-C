#pragma once

#include "rust/features/player_esp.hpp"
#include "rust/classes.hpp"

#include <windows.h>
#include "offsets.h"

namespace O::Projectile {
	constexpr auto initialVelocity = 0x18;
	constexpr auto drag = 0x24;
	constexpr auto gravityModifier = 0x28;
	constexpr auto thickness = 0x2c;
	constexpr auto initialDistance = 0x30;
	constexpr auto remainInWorld = 0x34;
	constexpr auto stickProbability = 0x38;
	constexpr auto breakProbability = 0x3c;
	constexpr auto conditionLoss = 0x40;
	constexpr auto ricochetChance = 0x44;
	constexpr auto penetrationPower = 0x48;
	constexpr auto damageProperties = 0x50;
	constexpr auto damageDistances = 0x58;
	constexpr auto damageMultipliers = 0x60;
	constexpr auto damageTypes = 0x68;
	constexpr auto rendererToScale = 0x70;
	constexpr auto firstPersonRenderer = 0x78;
	constexpr auto createDecals = 0x80;
	constexpr auto flybySound = 0x88;
	constexpr auto flybySoundDistance = 0x90;
	constexpr auto closeFlybySound = 0x98;
	constexpr auto closeFlybyDistance = 0xa0;
	constexpr auto tumbleSpeed = 0xa4;
	constexpr auto tumbleAxis = 0xa8;
	constexpr auto swimScale = 0xb4;
	constexpr auto swimSpeed = 0xc0;
	constexpr auto owner = 0xd0;
	constexpr auto sourceWeaponPrefab = 0xd8;
	constexpr auto sourceProjectilePrefab = 0xe0;
	constexpr auto mod = 0xe8;
	constexpr auto projectileID = 0xf0;
	constexpr auto seed = 0xf4;
	constexpr auto clientsideEffect = 0xf8;
	constexpr auto clientsideAttack = 0xf9;
	constexpr auto integrity = 0xfc;
	constexpr auto maxDistance = 0x100;
	constexpr auto modifier = 0x104;
	constexpr auto invisible = 0x114;
	constexpr auto currentVelocity = 0x118;
	constexpr auto currentPosition = 0x124;
	constexpr auto traveledDistance = 0x130;
	constexpr auto traveledTime = 0x134;
	constexpr auto launchTime = 0x138;
	constexpr auto sentPosition = 0x13c;
	constexpr auto previousPosition = 0x148;
	constexpr auto previousVelocity = 0x154;
	constexpr auto previousTraveledTime = 0x160;
	constexpr auto isRicochet = 0x164;
	constexpr auto isRetiring = 0x165;
	constexpr auto flybyPlayed = 0x166;
	constexpr auto wasFacingPlayer = 0x167;
	constexpr auto flybyPlane = 0x168;
	constexpr auto flybyRay = 0x178;
	constexpr auto cleanupAction = 0x190;
	constexpr auto hitTest = 0x198;
	constexpr auto swimRandom = 0x1a0;
	constexpr auto _waterMaterialID = 0x4;
	constexpr auto cachedWaterString = 0x8;
};

#define safe_read(Addr, Type) mem::read<Type>((DWORD64)Addr)
#define safe_write(Addr, Data, Type) mem::write<Type>((DWORD64)Addr, Data);

class Projectile;

static auto _retire = reinterpret_cast<void(*)(Projectile*)>(0);
static auto _update = reinterpret_cast<void(*)(Projectile*)>(0);
static auto Do_Hit = reinterpret_cast<bool(*)(Projectile*, uintptr_t, Vector3, Vector3)>(0);


static auto GetName = reinterpret_cast<str(*)(uintptr_t)>(0);

static auto HitPointWorld = reinterpret_cast<Vector3(*)(uintptr_t)>(0);
static auto HitNormalWorld = reinterpret_cast<Vector3(*)(uintptr_t)>(0);

static auto Trace_All = reinterpret_cast<void(*)(uintptr_t, uintptr_t, int)>(0);
static auto get_magnitude = reinterpret_cast<float(*)(uintptr_t)>(0);
static auto seteffect = reinterpret_cast<void(*)(uintptr_t, float)>(0);

static auto Sphere = reinterpret_cast<void (*)(Vector3 vPos, float fRadius, col color, float fDuration, bool distanceFade)>(0);
static auto getrandomvel = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ItemModProjectile"), _("GetRandomVelocity"), 0, _(""), _(""))));

static auto _launch = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Launch"), 0, _(""), _(""))));


void init_projectile() {
	_update = reinterpret_cast<void(*)(Projectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Update"), 0, _(""), _(""))));
	Sphere = reinterpret_cast<void (*)(Vector3 vPos, float fRadius, col color, float fDuration, bool distanceFade)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Sphere"), 5, _(""), _("UnityEngine"))));
	_retire = reinterpret_cast<void(*)(Projectile*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Retire"), 0, _(""), _(""))));
	Trace_All = reinterpret_cast<void(*)(uintptr_t, uintptr_t, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameTrace"), _("TraceAll"), 3, _(""), _(""))));

	HitPointWorld = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HitTest"), _("HitPointWorld"), 0, _(""), _(""))));
	HitNormalWorld = reinterpret_cast<Vector3(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HitTest"), _("HitNormalWorld"), 0, _(""), _(""))));

	GetName = reinterpret_cast<str(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetNameCache"), _("GetName"), 1, _(""), _(""))));
	Do_Hit = reinterpret_cast<bool(*)(Projectile*, uintptr_t, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), 0, _(""), _(""))));
	get_magnitude = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Vector3"), _("get_magnitude"), 0, _(""), _("UnityEngine"))));
	getrandomvel = reinterpret_cast<float(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ItemModProjectile"), _("GetRandomVelocity"), 0, _(""), _(""))));
	seteffect = reinterpret_cast<void(*)(uintptr_t, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("SetEffectScale"), 1, _(""), _(""))));
	_launch = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("Launch"), 0, _(""), _(""))));
}

class Projectile {
public:
	void initialVelocity(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::initialVelocity, d, Vector3); }
	Vector3 initialVelocity() { return safe_read(this + O::Projectile::initialVelocity, Vector3); }
	bool authoritative() { return safe_read(this + isAuthoritative, bool); }
	Vector3 sentPosition() { return safe_read(this + O::Projectile::sentPosition, Vector3); }
	void sentPosition(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::sentPosition, d, Vector3); }

	void currentVelocity(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::currentVelocity, d, Vector3); }
	Vector3 currentVelocity() { return safe_read(this + O::Projectile::currentVelocity, Vector3); }

	float drag() { return safe_read(this + O::Projectile::drag, float); }

	float previoustraveledTime() { return safe_read(this + O::Projectile::previousTraveledTime, float); }
	void previoustraveledTime(float d) { if (!this) return; safe_write(this + O::Projectile::previousTraveledTime, d, float); }

	float gravityModifier() { return safe_read(this + O::Projectile::gravityModifier, float); }
	void integrity(float f) { if (!this) return; safe_write(this + O::Projectile::integrity, f, float); }
	float integrity() { return safe_read(this + O::Projectile::integrity, float); }
	float maxDistance() { return safe_read(this + O::Projectile::maxDistance, float); }
	Vector3 currentPosition() { return safe_read(this + O::Projectile::currentPosition, Vector3); }
	void currentPosition(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::currentPosition, d, Vector3); }

	void partialTime(float f) { if (!this) return; safe_write(this + O::Projectile::tumbleSpeed, f, float); }
	float partialTime() { return safe_read(this + O::Projectile::tumbleSpeed, float); }
	Vector3 prevSentVelocity() { return safe_read(this + O::Projectile::tumbleAxis, Vector3); }
	void prevSentVelocity(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::tumbleAxis, d, Vector3); }
	float sentTraveledTime() { return safe_read(this + O::Projectile::closeFlybyDistance, float); }
	void sentTraveledTime(float d) { if (!this) return; safe_write(this + O::Projectile::closeFlybyDistance, d, float); }
	float ricochetChance() { return safe_read(this + O::Projectile::ricochetChance, float); }
	void ricochetChance(float d) { if (!this) return; safe_write(this + O::Projectile::ricochetChance, d, float); }
	Vector3 prevSentPosition() { return safe_read(this + O::Projectile::sentPosition, Vector3); }
	void prevSentPosition(Vector3 d) { if (!this) return; safe_write(this + O::Projectile::sentPosition, d, Vector3); }
	bool needsLOS() { return safe_read(this + O::Projectile::createDecals, bool); }
	void needsLOS(bool d) { if (!this) return; safe_write(this + O::Projectile::createDecals, d, bool); }

	void SetEffectScale(float f) { if (!this) return; return seteffect((uintptr_t)this, f); }

	float traveledDistance() { return safe_read(this + O::Projectile::traveledDistance, float); }
	void traveledDistance(float d) { if (!this) return; safe_write(this + O::Projectile::traveledDistance, d, float); }

	float initialDistance() { return safe_read(this + O::Projectile::initialDistance, float); }
	float SetInitialDistance(float d) { return safe_write(this + O::Projectile::initialDistance, d, float); }

	float traveledTime() { return safe_read(this + O::Projectile::traveledTime, float); }
	void traveledTime(float d) { if (!this) return; safe_write(this + O::Projectile::traveledTime, d, float); }

	Vector3 previousPosition() { return safe_read(this + O::Projectile::previousPosition, Vector3); }
	void previousPosition(Vector3 d) { safe_write(this + O::Projectile::previousPosition, d, Vector3); }
	
	Vector3 previousVelocity() { return safe_read(this + O::Projectile::previousVelocity, Vector3); }
	void previousVelocity(Vector3 d) { safe_write(this + O::Projectile::previousVelocity, d, Vector3); }

	void hitTest(DWORD64 d) { safe_write(this + O::Projectile::hitTest, d, DWORD64); }
	DWORD64 hitTest() { return safe_read(this + O::Projectile::hitTest, DWORD64); }
	DWORD64 damageProperties() { return safe_read(this + O::Projectile::damageProperties, DWORD64); }

	int projectileID() { return safe_read(this + O::Projectile::projectileID, int); }

	BasePlayer* owner() { return (BasePlayer*)safe_read(this + O::Projectile::owner, DWORD64); }
	DWORD64 sourceWeaponPrefab() { return safe_read(this + O::Projectile::sourceWeaponPrefab, DWORD64); }

	DWORD64 damageDistances() { return safe_read(this + O::Projectile::damageDistances, DWORD64); }

	bool invisible() { return safe_read(this + O::Projectile::invisible, bool); }

	float launchTime() { return safe_read(this + O::Projectile::launchTime, float); }
	void launchTime(float d) { if (!this) return;  safe_write(this + O::Projectile::launchTime, d, float); }

	void Launch() { if (!this) return;  return _launch((uintptr_t)this); }

	void Retire() { if (!this) return;  return _retire(this); }

	bool IsAlive() {
		return (this->integrity() > 0.001f && this->traveledDistance() < this->maxDistance() && this->traveledTime() < 8);
	}

	struct TraceInfo {

		bool valid; // 0x10
		float distance; // 0x14
		DWORD64 entity; // 0x18   //BasePlayer
		Vector3 point; // 0x20
		Vector3 normal; // 0x2C
		DWORD64/*Transform*/ bone; // 0x38
		DWORD64 material; // 0x40
		unsigned int partID; // 0x48
		DWORD64 collider; // 0x50
	};

	float GetHitDist() {
		float travel = traveledTime();

		float num6 = (travel + 2 / 60 + 0.03125f) * 1.5f;
		float maxdist = 0.1f + num6 * 5.5f;
		return maxdist;
	}

	static Vector3 SimulateProjectile(Vector3& position, Vector3& velocity, float& partialTime, float travelTime, Vector3 gravity, float drag, float timestep)
	{
		float num = timestep;
		Vector3 origin = position;
		if (partialTime > 0)
		{
			float num2 = num - partialTime;
			if (travelTime < num2)
			{
				origin = position;
				position += velocity * travelTime;
				partialTime += travelTime;
				return origin;
			}
			origin = position;
			position += velocity * num2;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime -= num2;
		}

		int num3 = FloorToInt(travelTime / num);

		for (int i = 0; i < num3; i++)
		{
			origin = position;
			position += velocity * num;
			velocity += gravity * num;
			velocity -= velocity * drag * num;
		}
		partialTime = travelTime - num * (float)num3;
		if (partialTime > 0)
		{
			origin = position;
			position += velocity * partialTime;
		}
		return origin;
	}

	void UpdateHitTest(TraceInfo info) {
		DWORD64 ht = hitTest();

		safe_write(ht + 0x66, true, bool); //DidHit
		safe_write(ht + 0x88, info.entity, DWORD64); //HitEntity
		safe_write(ht + 0xA8, info.distance, float); //HitDistance

		if (info.material != 0) {
			str material = (GetName(info.material));
			safe_write(ht + 0xC0, material, str); //HitMaterial  
		}

		safe_write(ht + 0xB8, info.partID, unsigned int); //HitPart
		safe_write(ht + 0xB0, info.bone, DWORD64); //HitTransform
		safe_write(ht + 0x90, info.point, Vector3); //HitPoint
		safe_write(ht + 0x9C, info.normal, Vector3); //HitNormal
		safe_write(ht + 0x78, info.collider, DWORD64); //collider

		DWORD64 go = info.collider != 0 ? get_gameObject(info.collider) : get_gameObject(info.bone);
		safe_write(ht + 0x70, go, DWORD64); //gameObject
		if (info.bone != 0) {

			Vector3 hitpoint = InverseTransformPoint(safe_read(ht + 0xB0, Transform*)/*HitTransform*/, info.point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint

			Vector3 normalpoint = InverseTransformDirection(safe_read(ht + 0xB0, Transform*)/*HitTransform*/, info.normal);
			safe_write(ht + 0x9C, normalpoint, Vector3); //HitNormal
		}

	}

	Vector3 Simulate(bool returnvelocity, bool sendtoserver, Vector3& pos, float& part) {
		pos = prevSentPosition(); 
		Vector3 prev = prevSentVelocity(); 
		part = partialTime(); 
		float travel = max(traveledTime() - sentTraveledTime(), 0);

		Vector3 gr = get_gravity(); //static Vector3 get_gravity();


		Vector3 origin = SimulateProjectile(pos, prev, part, travel, gr * gravityModifier(), drag(), 0.03125f);

		if (sendtoserver) {
			prevSentPosition(pos);
			prevSentVelocity(prev);
			partialTime(part);
			sentTraveledTime(traveledTime());
		}

		if (returnvelocity) return prev;

		return origin;
	}

	bool DoFatBulletHit(Projectile* pr, Vector3 point) {
		float maxdist = GetHitDist();

		auto target = esp::local_player->get_aimbot_target(point, maxdist);

		if (get_isAlive((BaseProjectile*)pr) && target.player && !target.teammate) {
			if (!unity::is_visible(target.pos, point, (uintptr_t)esp::local_player)) {
				return false;
			}

			DWORD64 ht = hitTest();
			safe_write(ht + 0x66, true, bool); //DidHit
			safe_write(ht + 0x88, (DWORD64)target.player, DWORD64); //HitEntity
			Transform* Transform;

			if (!target.is_heli) {
				Transform = FindBone(target.player, _(L"spine4"));
				if (vars->combat.hitbox_override)
					Transform = FindBone(target.player, _(L"head"));
			}
			if (!Transform)
				return false;

			safe_write(ht + 0xB0, (uintptr_t)Transform, DWORD64);

			Vector3 hitpoint = InverseTransformPoint(Transform, point);
			safe_write(ht + 0x90, hitpoint, Vector3); //hitPoint
			safe_write(ht + 0x14, point, Vector3);

			bool result = Do_Hit(pr, ht, point, Vector3());
			//Sphere(point, 0.015f, col(1, 0, 0, 1), 20, true);
			return true;
		}
		return false;
	}

	bool DoHit(Projectile* pr, DWORD64 ht, Vector3 point, Vector3 normal, TraceInfo info, bool& exit) {
		bool result = false;
		if (!IsAlive())
			return result;

		auto material = info.material != 0 ? GetName(info.material)->str : (_(L"generic"));

		bool canIgnore = true;
		canIgnore = unity::is_visible(sentPosition(), currentPosition() + currentVelocity().Normalized() * 0.01f, 0);//(uintptr_t)esp::local_player);
		
		if (!canIgnore) {
			integrity(0);
			return true;
		}

		float org;
		if (canIgnore) {
			float time = 0;
			Vector3 pos{};
			Vector3 attackStart = Simulate(false, true, pos, time);

			safe_write(ht + 0x14, Ray(attackStart, Vector3()), Ray);
		}
		Sphere(currentPosition(), 0.2f, col(0, 0, 1, 1), 10.f, 100.f);
		if (canIgnore && m_wcsicmp(material, _(L"Flesh"))) {
			DWORD64 Tra = safe_read(ht + 0xB0, DWORD64);
			if (Tra) {
				auto st = _(L"head");

				set_name(Tra, st);
			}

			result = Do_Hit(pr, ht, point, normal);
			sentPosition(currentPosition());

		}
		return result;
	}

	bool DoMovement(float deltaTime, Projectile* pr) {
		Vector3 a = currentVelocity() * deltaTime;
		float magnitude = a.Length();
		float num2 = 1 / magnitude;
		Vector3 vec2 = a * num2;
		bool flag = false;

		Vector3 vec3 = currentPosition() + vec2 * magnitude;
		float num3 = traveledTime() + deltaTime;

		DWORD64 ht = hitTest();
		if (!ht) {
			/*HitTest_TypeInfo*/
			DWORD64 htstatic = il2cpp::init_class(_("HitTest"), _(""));

			DWORD64 HitTest = il2cpp::methods::object_new(htstatic);
			ht = HitTest;
			hitTest(HitTest);
		}
		Ray ray = Ray(currentPosition(), vec2);
		safe_write(ht + 0x14, ray, Ray); //AttackRay
		safe_write(ht + 0x34, magnitude, float); //MaxDistance

		BasePlayer* ow = this->owner();
		safe_write(ht + 0x80, (DWORD64)ow, DWORD64); //IgnoreEntity
		safe_write(ht + 0x2C, 0, float); //Radius
		safe_write(ht + 0x30, 0.15f, float); //Forgiveness                                        FAT BULLET
		if (!esp::local_player || ow->get_steam_id() == esp::local_player->get_steam_id()) {
			safe_write(ht + 0x10, 0x2, int); //Type
		}
		else safe_write(ht + 0x10, 0x1, int); //Type	`

		if (sourceWeaponPrefab()) {
			safe_write(ht + 0x65, true, bool); //BestHit
			safe_write(ht + 0x68, damageProperties(), DWORD64); //DamageProperties
		}

		typedef DWORD64(__stdcall* Unknown)(DWORD64);
		DWORD64 st = safe_read(mem::game_assembly_base + offsets::Method$Facepunch_Pool_GetList_TraceInfo_Address, DWORD64); //Method$Facepunch.Pool.GetList<TraceInfo>() address

		Unknown get_list = (Unknown)(mem::game_assembly_base + offsets::Method$Facepunch_Pool_GetList_TraceInfo_MethodAddress);//Method$Facepunch.Pool.GetList<TraceInfo>() MethodAddress

		DWORD64 rs = get_list(st);
		if (!rs) 
			return false;

		Trace_All(ht, rs, 1269916433 /*mask*/);

		ht = hitTest();
		safe_write(ht + 0x34, 0, float); //AttackEnd == AttackStart


		int size = safe_read(rs + 0x18, int);

		DWORD64 lst = safe_read(rs + 0x10, DWORD64);

		if (DoFatBulletHit(pr, currentPosition())) {
			integrity(0); 
			return false;
		}

		for (int i = 0; i < size && this->IsAlive() && !flag; i++) {
			TraceInfo Trace = safe_read(lst + 0x20 + (i * sizeof(TraceInfo)), TraceInfo);
			if (Trace.valid) {
				this->UpdateHitTest(Trace);

				Vector3 vec4 = HitPointWorld(ht); //Vector3 HitPointWorld();
				Vector3 normal = HitNormalWorld(ht); //Vector3 HitNormalWorld();

				Line(currentPosition(), vec4, col(1, 1, 1, 1), 20, true, true);
				Sphere(Trace.point, 0.05f, col(0.5, 0, 0, 1), 20, true);

				float magnitude2 = (vec4 - currentPosition()).Length();
				float num5 = magnitude2 * num2 * deltaTime;

				traveledDistance(traveledDistance() + magnitude2);
				traveledTime(traveledTime() + num5);
				currentPosition(vec4);


				bool exit = false;
				if (this->DoHit(pr, ht, vec4, normal, Trace, exit)) {
					flag = true;
				}

				if (exit) {
					return true;
				}
			}
		}

		if (!flag && this->IsAlive()) {
			float magnitude3 = (vec3 - currentPosition()).Length();
			float num6 = magnitude3 * num2 * deltaTime;
			traveledDistance(traveledDistance() + magnitude3);
			traveledTime(traveledTime() + num6);
			currentPosition(vec3);
		}

		return false;
	}

	void DoVelocityUpdate(float deltaTime, Projectile* pr) {
		if (!IsAlive())
			return;

		Vector3 gr = get_gravity(); //static Vector3 get_gravity();

		Vector3 tr = (gr * gravityModifier() * deltaTime);
		currentVelocity(currentVelocity() + tr);

		Vector3 dr = (currentVelocity() * drag() * deltaTime);
		currentVelocity(currentVelocity() - dr);
	}

	void UpdateVelocity(float deltaTime, Projectile* pr) {
		if (traveledTime() != 0) {
			previousPosition(this->currentPosition());
			previoustraveledTime(this->traveledTime());
		}

		Transform* Transform = _get_transform((BasePlayer*)pr);
		Vector3 pos = Transform->get_bone_position();
		this->currentPosition(pos);

		if (traveledTime() == 0) {
			this->sentPosition(pos);
			this->previousPosition(pos);
			partialTime(0); 
			sentTraveledTime(0);
			prevSentVelocity(initialVelocity());
			prevSentPosition(sentPosition());
			needsLOS(false);
		}


		deltaTime *= get_timeScale();


		bool ret = this->DoMovement(deltaTime, pr);
		if (!ret) {
			this->DoVelocityUpdate(deltaTime, pr);
		}

		Line(this->currentPosition(), this->previousPosition(), col(0.6, 0.1, 0.7, 1), 10.f, false, true);
		
		auto Trans = _get_transform((BasePlayer*)pr); //Component | Transform get_transform(); 
		set_position(Trans, currentPosition()); //Transform | void set_position(Vector3 value); 

		Vector4 rotation = LookRotation(currentVelocity(), Vector3(0, 1, 0));

		set_rotation(Trans, rotation);
	}
};

void OnProjectileUpdate(Projectile* unk) {
	__try {
		if (!unk)
			return;

		if (vars->combat.doubletap && settings::desyncTime > 0.f)
			return _update(unk);
		//if(!vars->combat.magic_bullet)
		//	return Update(unk);

		BasePlayer* owner = (BasePlayer*)safe_read(unk + 0xD0, DWORD64);
		if (!owner)
			return;

		if (owner->is_local_player()) {
			if (get_isAlive((BaseProjectile*)unk)) {
				for (; unk->IsAlive(); unk->UpdateVelocity(0.03125f, unk)) {

					if (unk->launchTime() <= 0) {
						break;
					}

					float time = get_time();

					if (time - unk->launchTime() < unk->traveledTime() + 0.03125f) {
						break;
					}
				}
			}
			else {
				_retire(unk);
			}
		}
	}
	__except (true) {
		//error?
	}
}