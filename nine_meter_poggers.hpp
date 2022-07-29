#pragma once
#include "projectile1.hpp"

inline bool CanManipulate(base_projectile* baseProjectile, base_player* TargetPlayer, input_state* input)
{
	auto LocalPlayer = esp::local_player;//CheatCore::m_cheat->LocalPlayer;

	if (!LocalPlayer)
		return false;

	if (vars->combat.manipulator2) { //key will already be checked for in clientinput
		//CheatCore::m_cheat->isDesyncing = true; //not used as far as i know

		float time = get_deltaTime();//UnityEngine::Time::get_deltaTime();
		settings::MagicBulletTimer += time;

		uint64_t State = (uint64_t)input;
		if (!State)
			return 0;

		uint64_t Current = *reinterpret_cast<uint64_t*>(State + 0x10);
		uint64_t Previous = *reinterpret_cast<uint64_t*>(State + 0x18);

		if (settings::MagicBulletTimer >= 1.f)
		{
			LocalPlayer->set_client_tick_interval(0.05f);
			settings::MagicBulletTimer = 0;
		}
		else
		{
			if (Previous && Current)
				*reinterpret_cast<int*>(Previous + 0x14) = *reinterpret_cast<int*>(Current + 0x14);//0;

			LocalPlayer->set_client_tick_interval(99999.f);
		}

	}
	else {
		LocalPlayer->set_client_tick_interval(0.05f);
		settings::MagicBulletTimer = 0;
	}

	if (!baseProjectile)
		return false;

	if (!TargetPlayer)
		return false;

	bool ManipStatus = false;
	bool BehindWallStatus = false;
	Vector3 ManipulationPosition = Vector3(0,0,0), BehindWallPoistion = Vector3(0,0,0);

	if (vars->combat.manipulator2 || vars->combat.targetbehindwall) {

		int layermask;
		//if (settings.PierceMaterials)
		//	layermask = 10551296;
		//else
		layermask = 1218519041;

		bool IsMounted = LocalPlayer->get_model_state()->has_flag(rust::classes::ModelState_Flag::Mounted);

		float maxVelocity;
		if (!IsMounted)
			maxVelocity = get_maxspeed(LocalPlayer);
		else
			maxVelocity = GetMountedVelocity(LocalPlayer);//LocalPlayer->GetPlayerMaxVelocity();

		auto time = unity::get_realtimesincestartup();//UnityEngine::Time::get_realtimeSinceStartup();
		float _timeSinceLastTick = time - LocalPlayer->get_last_sent_tick_time();
		float timeSinceLastTickClamped = max(0.f, min(_timeSinceLastTick, 1.f));
		float maxDist = 0.1f + (timeSinceLastTickClamped + 2.f / 60.f) * 1.5f * maxVelocity;

		static const float MaxVertical = 1.6;
		float max_usable_verical = min(maxDist, MaxVertical);
		Vector3 center = LocalPlayer->get_player_eyes()->GetCenter();
		//Vector3 LastLocalEye = LocalPlayer->lastSentTick()->eyePos;
		Vector3 LastLocalEye = misc::cLastTickEyePos;
		Vector3 Up = LastLocalEye + Vector3(0.f, max_usable_verical, 0.f);
		Vector3 Down = LastLocalEye + Vector3(0.f, -max_usable_verical, 0.f);

		//0x52D200 losradius real rust
		typedef bool(*lr)(Vector3, Vector3, int, float, uintptr_t);
		bool CenterLOS = ((lr)(mem::game_assembly_base + 0x52D200))(center, LastLocalEye, layermask, 0.2f, 0);
		bool UpLOS = CenterLOS && ((lr)(mem::game_assembly_base + 0x52D200))(LastLocalEye, Up, layermask, 0.2f, 0) && LastLocalEye.distance(Up) > 0.01f && misc::ValidateEyePos(LastLocalEye, Up);// && LocalPlayer->checkNoclipMagicBullet(LastLocalEye, Up);
		bool DownLOS = CenterLOS && ((lr)(mem::game_assembly_base + 0x52D200))(LastLocalEye, Down, layermask, 0.2f, 0) && LastLocalEye.distance(Down) > 0.01f && misc::ValidateEyePos(LastLocalEye, Down);// && LocalPlayer->checkNoclipMagicBullet(LastLocalEye, Down);

		static const bool debug_test = false;

		//draw_line_(LastLocalEye, Up, ImColor(255, 0, 0, 255), 0.1f);
		//draw_line_(LastLocalEye, Down, ImColor(255, 0, 0, 255), 0.1f);

		Vector3 trg_pos = esp::best_target.pos;//player->get_bone_transform(48)->get_bone_position();

		auto HitScan = [&](Vector3 from, bool do_ = true, int val = 0) {

			Vector3 head_pos_ = esp::best_target.pos;//player->get_bone_transform(48)->get_bone_position();

			if (vars->combat.targetbehindwall && val) {
				if ((val % 20) == 0) {
					Vector3 RealTargetPosition = Vector3(trg_pos.x, trg_pos.y + 1.15f, trg_pos.z);
					bool LOS = PLOS(from, RealTargetPosition, layermask) && PLOS(trg_pos, RealTargetPosition, layermask);
					//draw_line_(trg_pos, RealTargetPosition, LOS ? Vector4(0, 255, 0, 255) : ImColor(255, 0, 0, 255));
					if (LOS)
						return std::make_pair(LOS, RealTargetPosition);
				}

				float DegreeEnemyx = cos(val) * 1.7f;
				float DegreeEnemyz = sin(val) * 1.7f;
				Vector3 RealTargetPosition = Vector3(trg_pos.x + DegreeEnemyx, trg_pos.y, trg_pos.z + DegreeEnemyz);
				bool LOS = PLOS(from, RealTargetPosition, layermask) && PLOS(trg_pos, RealTargetPosition, layermask);

				return std::make_pair(LOS, RealTargetPosition);
			}

			if (!do_)
				return std::make_pair(false, head_pos_);

			if (vars->combat.HitScan) {
				if (!esp::best_target.player) return std::make_pair(false, head_pos_);
				for (auto bone : { 48, 3, 4, 15, 14, 26, 57 }) {
					Vector3 TargetPosition;
					if (bone == 48) TargetPosition = head_pos_;
					else TargetPosition = esp::best_target.player->get_bone_transform(bone)->get_bone_position();
					if (PLOS(from, TargetPosition, layermask)) {
						settings::HitScanBone = bone;
						return std::make_pair(true, TargetPosition);
					}
				}
				return std::make_pair(false, head_pos_);
			}
			else
				return std::make_pair(PLOS(from, head_pos_, layermask), head_pos_);
		};
		auto HitResultUp = HitScan(Up);
		auto HitResultDown = HitScan(Down);
		auto HitResultForward = HitScan(LastLocalEye);

		if (vars->visual.angles)
		{
			Sphere(HitResultUp.second, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, false);
			Sphere(HitResultDown.second, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, false);
			Sphere(HitResultForward.second, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, false);
		}

		if (HitResultForward.first)
		{
			ManipStatus = true;
			ManipulationPosition = LastLocalEye;
			BehindWallPoistion = HitResultForward.second;
			settings::CanMagicBoolet = false;
		}
		else if (PLOS(LastLocalEye, Up, layermask) && HitResultUp.first && maxDist < max_usable_verical && UpLOS)
		{
			ManipStatus = true;
			ManipulationPosition = Up;
			BehindWallPoistion = HitResultUp.second;
			settings::CanMagicBoolet = false;
		}
		else if (PLOS(LastLocalEye, Down, layermask) && HitResultDown.first && maxDist < max_usable_verical && DownLOS)
		{
			ManipStatus = true;
			ManipulationPosition = Down;
			BehindWallPoistion = HitResultDown.second;
			settings::CanMagicBoolet = false;
		}
		//else if (settings.AimKey.get()) {

		for (int val = 0; val < 720; val += 10)
		{
			float DegreeX = cos(val) * maxDist;
			float DegreeZ = sin(val) * maxDist;

			Vector3 DiagonalUp = Vector3(LastLocalEye.x + DegreeX, LastLocalEye.y + max_usable_verical - 0.01f, LastLocalEye.z + DegreeZ);
			Vector3 DiagonalDown = Vector3(LastLocalEye.x + DegreeX, LastLocalEye.y + -max_usable_verical - 0.01f, LastLocalEye.z + DegreeZ);
			Vector3 Horizontal = Vector3(LastLocalEye.x + DegreeX, LastLocalEye.y, LastLocalEye.z + DegreeZ);

			if (vars->visual.angles)
			{
				Sphere(DiagonalUp, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, 0);
				Sphere(DiagonalDown, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, 0);
				Sphere(Horizontal, 0.1f, col(r * 100, g * 100, b * 100, 255), 0.05f, 0);
			}

			auto HitResultDiagonalUp = HitScan(DiagonalUp, true, val); //settings.ManipulationUp
			auto HitResultDiagonalDown = HitScan(DiagonalDown, true, val); //settings.ManipulationDown
			auto HitResultHorizontal = HitScan(Horizontal, true, val);

			bool DiagonalUpLOS = false; 
			//if (settings.ManipulationUp)
			if (true)
				//DiagonalUpLOS = LocalPlayer->checkNoclipMagicBullet(LastLocalEye, DiagonalUp) 
				DiagonalUpLOS = misc::ValidateEyePos(LastLocalEye, DiagonalUp)
					&& LocalPlayer->is_visible(center, LastLocalEye, 0.2f) 
					&& LocalPlayer->is_visible(LastLocalEye, DiagonalUp, 0.2f)
					&& LastLocalEye.distance(DiagonalUp) > 0.01f 
					&& PLOS(LastLocalEye, DiagonalUp, layermask) 
					&& HitResultDiagonalUp.first;

			bool DiagonalDownLOS = false; 
			//if (settings.ManipulationDown) 
			if (true)
				DiagonalDownLOS = misc::ValidateEyePos(LastLocalEye, DiagonalDown)
					&& LocalPlayer->is_visible(center, LastLocalEye, 0.2f)
					&& LocalPlayer->is_visible(LastLocalEye, DiagonalDown, 0.2f)
					&& LastLocalEye.distance(DiagonalDown) > 0.01f 
					&& PLOS(LastLocalEye, DiagonalDown, layermask) 
					&& HitResultDiagonalDown.first;

			bool HorizontalLOS = false; 
			//if (settings.Manipulation)
			if (true)
				HorizontalLOS = misc::ValidateEyePos(LastLocalEye, Horizontal)
					&& LocalPlayer->is_visible(center, LastLocalEye, 0.2f) 
					&& LocalPlayer->is_visible(LastLocalEye, Horizontal, 0.2f)
					&& LastLocalEye.distance(Horizontal) > 0.01f 
					&& PLOS(LastLocalEye, Horizontal, layermask) 
					&& HitResultHorizontal.first;

			if (true) {
				if (DiagonalUpLOS || debug_test)
					if (vars->visual.angles)
						Line(LastLocalEye, DiagonalUp, DiagonalUpLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(LastLocalEye, DiagonalUp, DiagonalUpLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);

				if (DiagonalDownLOS || debug_test)
					if (vars->visual.angles)
						Line(LastLocalEye, DiagonalDown, DiagonalDownLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(LastLocalEye, DiagonalDown, DiagonalDownLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);

				if (HorizontalLOS || debug_test)
					if (vars->visual.angles)
						Line(LastLocalEye, Horizontal, HorizontalLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(LastLocalEye, Horizontal, HorizontalLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);

				if (DiagonalUpLOS || debug_test)
					if (vars->visual.angles)
						Line(DiagonalUp, HitResultDiagonalUp.second, DiagonalUpLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(DiagonalUp, HitResultDiagonalUp.second, DiagonalUpLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);

				if (DiagonalDownLOS || debug_test)
					if (vars->visual.angles)
						Line(DiagonalDown, HitResultDiagonalDown.second, DiagonalUpLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(DiagonalDown, HitResultDiagonalDown.second, DiagonalDownLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);

				if (HorizontalLOS || debug_test)
					if (vars->visual.angles)
						Line(Horizontal, HitResultHorizontal.second, DiagonalUpLOS ? col(0, 235, 190, 255) : col(190, 0, 130, 255), 0.05f, 0, 1);
				//draw_line_(Horizontal, HitResultHorizontal.second, HorizontalLOS ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), 0.1);
			}

			if (!DiagonalUpLOS && !DiagonalDownLOS && !HorizontalLOS)
			{
				ManipulationPosition = LastLocalEye;
				ManipStatus = false;

				if (vars->combat.targetbehindwall && misc::best_lean != Vector3(0, 0, 0)) {
					BehindWallStatus = false;
					BehindWallPoistion = trg_pos;
				}
				else if (misc::best_lean == Vector3(0, 0, 0) && vars->combat.targetbehindwall)
				{
					auto scan = HitScan(LastLocalEye, true, val);
					if (scan.first) {
						BehindWallStatus = true;
						BehindWallPoistion = scan.second;

						ManipStatus = true;
						ManipulationPosition = LastLocalEye;
						break;
					}
				}

			}
			else if (DiagonalUpLOS)
			{
				ManipulationPosition = DiagonalUp;
				ManipStatus = true;
				if (vars->combat.targetbehindwall) {
					BehindWallStatus = true;
					BehindWallPoistion = HitResultDiagonalUp.second;
				}
				break;
			}
			else if (DiagonalDownLOS)
			{
				ManipulationPosition = DiagonalDown;
				ManipStatus = true;
				if (vars->combat.targetbehindwall) {
					BehindWallStatus = true;
					BehindWallPoistion = HitResultDiagonalDown.second;
				}
				break;
			}
			else if (HorizontalLOS)
			{
				ManipulationPosition = Horizontal;
				ManipStatus = true;
				if (vars->combat.targetbehindwall) {
					BehindWallStatus = true;
					BehindWallPoistion = HitResultHorizontal.second;
				}
				break;
			}
		}
		//}
		//else {
		//	ManipStatus = false;
		//	ManipulationPosition = LastLocalEye;
		//	CheatCore::m_cheat->CanMagicBoolet = false;
		//}

		if (LastLocalEye != ManipulationPosition)
		{
			settings::RealGangstaShit = ManipulationPosition;
			settings::FatHitPosition = BehindWallPoistion;
		}
		else
		{
			settings::RealGangstaShit = Vector3(0, 0, 0);
			settings::FatHitPosition = Vector3(0, 0, 0);
		}


		if (LastLocalEye != ManipulationPosition)
		{
			esp::local_player->console_echo(string::wformat(_(L"[trap]: CanManipulate - RealGangstaShit: (%d, %d, %d), FatHitPosition: (%d, %d, %d), distance: %d"),
				(int)ManipulationPosition.x,
				(int)ManipulationPosition.y,
				(int)ManipulationPosition.z,
				(int)BehindWallPoistion.x,
				(int)BehindWallPoistion.y,
				(int)BehindWallPoistion.z,
				(int)LastLocalEye.distance(ManipulationPosition)));
		}
	}

	//if (!settings.AimKey.get())
	//	ManipStatus = false;

	settings::LaunchProjectile = ManipStatus || BehindWallStatus || settings::CanMagicBoolet;
	if (!ManipStatus) {
		settings::HitScanBone = 48;
	}

	return ManipStatus || BehindWallStatus || settings::CanMagicBoolet;
}