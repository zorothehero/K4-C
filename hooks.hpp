#pragma once
#include "memory/il2cpp.hpp"
#include "settings.hpp"
#include "mmisc.hpp"
#include "offsets.h"
#include <math.h>
#include "Keybind.h"

#include "spherearray.h"

#include <Windows.h>
//#include <vector>

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
	//std::array<projectileshoot_projectile, 8> projectiles; //0x18
	//projectileshoot_projectile projectiles[];
	//std::vector<projectileshoot_projectile> projectiles;
	rust::list<projectileshoot_projectile*>* projectiles; //0x18
};

namespace misc
{
	bool emulated = false;
	projectileshoot emulated_shot;

	float flyhackDistanceVertical = 0.f;
	float flyhackDistanceHorizontal = 0.f;
	float flyhackPauseTime = 0.f;
	float desyncTimeRaw = 0.f;
	float desyncTimeClamped = 0.f;
	float tickDeltaTime = 0.f;
	TickInterpolator ticks;
	bool isInAir = false;

	bool manual = false;
	bool autoshot = false;
	bool manipulate_vis = false;
	Vector3 cLastTickPos{};
	Vector3 cLastTickEyePos{};
	Vector3 best_lean{};
	Vector3 best_target{};

	struct fired_projectile {
		Projectile* original;
		Projectile* fake;
		float fired_at;
		int updates;
		aim_target player;
	};

	struct NodeTarget {
		Vector3 pos;
		int steps;
		std::vector<Vector3> path;
		uintptr_t ent;
	};
	NodeTarget node;

	std::array<fired_projectile, 32> fired_projectiles;
	// ADD PROJECTILES TO THIS LIST WHEN FIRED FROM RPC, MAYBE STRUCT THAT CONTAINS SHOOT TIME AND AMOUNT OF UPDATES ALREADY?
	// LOOP LIST IN CLIENTINPUT, ONLY CALL UPDATE WHENEVER TIME MORE THAN 0.03125f FROM PREVIOUS?
	// MIGHT NOT EVEN WORK, MIGHT BE TOO FAST, MAYBE WE JUST CALL IT ONCE PER 0.03125f?
	//

	double fabs(double x)
	{
		union { double f; uint64_t i; } u = { x };
		u.i &= -1ULL / 2;
		return u.f;
	}

	bool TestNoClipping(base_player* ply = esp::local_player,
		Vector3 oldPos = Vector3(0, 0, 0),
		Vector3 newPos = Vector3(0, 0, 0),
		float radius = 0.01f,
		float backtracking = 0.01f)
	{
		Vector3 normalized = (newPos - oldPos).Normalized();
		Vector3 vector = oldPos - normalized * backtracking;
		float magnitude = (newPos - vector).Length();
		Ray z = Ray(vector, normalized);
		bool flag = unity::Raycast(z, magnitude + radius, 429990145);

		if (!flag)
		{
			typedef bool (*AAA)(Ray, float, float, int);
			//real rust 0x226ECA0
			//alkad rust 0x2258180
			flag = ((AAA)(mem::game_assembly_base + 0x226ECA0))(z, radius, magnitude, 429990145);
		}
		return flag;
	}

	bool ValidateEyePos(Vector3 pos, 
		Vector3 offset = Vector3(0, 0, 0))
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
		Vector3 actual_eye_pos = loco->get_player_eyes()->get_position();

		if (position2.distance(loco->get_player_eyes()->get_position()) > 0.06f
			&& TestNoClipping(loco, cLastTickPos, position2))
			//&& TestNoClipping(loco, cLastTickEyePos, position2))
		{
			flag = true;
		}
		else if (position2.distance(loco->get_player_eyes()->get_position()) > 0.01f
			&& TestNoClipping(loco, actual_eye_pos, eyepos)) {
			flag = true;
		}

		return flag;
	}


	//OnProjectileAttack stuff
	bool OnProjectileAttack(Projectile* p,
		base_player* ply,
		rust::classes::PlayerProjectileAttack* ppa) 
	{
		auto playerAttack = ppa->playerAttack;
		

			

		return true;
	}


	bool can_manipulate(base_player* ply, 
		Vector3 pos, 
		float mm_eye = 7.f) //7m only check rn
	{
		Vector3 v = *reinterpret_cast<Vector3*>((uintptr_t)ply + eyes);
		Vector3 re_p = ply->get_bone_transform(47)->get_bone_position() + ply->get_bone_transform(47)->up() * (ply->get_player_eyes()->get_view_offset().y + v.y);

		if (ply->is_visible(re_p, pos)) {
			misc::best_lean = Vector3(0, 0, 0);
			return true;
		}

		auto do_check = [&](Vector3 a) {
			Vector3 p = re_p + a;

			if (!ply->is_visible(p, re_p))
				return false;

			//if (!ply->is_visible(p - Vector3(0, 0.3, 0), re_p)) //double check not too low as likes to shoot from just under the ground
			//	return false;

			if(vars->visual.angles)
				Sphere(p, 0.05f, col(10, 30, 90, 1), 0.02f, 10);

			if (!ply->is_visible(p, pos))
			{
				if(!vars->combat.thick_bullet || !vars->combat.shoot_at_fatbullet) return false;
				bool t = false;
				Vector3 z = pos;
				//pos.y -= -0.2f; //imagine aiming at chest?????????
				std::array<Vector3, 5> positions = {
					z + Vector3(0, .3f, 0),
					z + Vector3(.9f, 0, 0),
					z + Vector3(-.9f, 0, 0),
					z + Vector3(0, 0, .9f),
					z + Vector3(0, 0, -.9f)
				};
				////Line(p, pos + Vector3(0, 1, 0), col(1,1,1,1), 10.f, true, false);
				for (auto v : positions) {
					if (vars->visual.angles)
						Sphere(v, 0.05f, col(10, 30, 90, 1), 0.02f, 10);
					if (ply->is_visible(p, v))
					{
						if (ply->is_visible(z, v))
						{
							t = true;
							misc::best_target = v;
							break;
						}
					}
				}
				
				if (!t) return false;
			}

			if (ValidateEyePos(p))
				return false;

			misc::best_lean = a;
			return true;
		};

		for (float y = 1.5f; y > -1.5f; y -= vars->combat.thick_bullet ? 0.3f : 0.1f) {
			int points = vars->combat.thick_bullet ? 7 : 20;
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

	bool TestFlying2(base_player* ply,
		Vector3 oldPos = Vector3(0,0,0),
		Vector3 newPos = Vector3(0,0,0),
		bool verifyGrounded = true)
	{
		if (verifyGrounded)
		{
			auto extrusion = 2.f;
			Vector3 vec = (oldPos + newPos) * 0.5f;
			auto margin = 0.05f;
			float radius = GetRadius(ply);
			float height = GetHeight(ply);
			Vector3 vec2 = vec + Vector3(0.f, radius - extrusion, 0.f);
			Vector3 vec3 = vec + Vector3(0.f, height - radius, 0.f);
			float radius2 = radius - margin;
			isInAir = !unity::CheckCapsule(vec2, vec3, radius2, 1503731969, 1);

			if (isInAir)
			{
				bool flag = false;
				Vector3 vec4 = newPos - oldPos;
				float num2 = std::fabs(vec4.y);
				float num3 = vec4.length_2d();

				if (vec4.y >= 0.f)
				{
					flag = true;
					flyhackDistanceVertical += vec4.y;
				}

				if (num2 < num3)
				{
					flag = true;
					flyhackDistanceHorizontal += num3;
				}

				if (flag)
				{
					float num4 = max((flyhackPauseTime > 0.f ? 10.f : 1.5f), 0.f);
					float num5 = GetJumpHeight(ply) + num4;
					if (flyhackDistanceVertical > num5)
						return true;
					
					float num6 = num4;
					float num7 = 5.f + num6;
					if (flyhackDistanceHorizontal > num7)
						return true;
				}
			}
			else
			{
				flyhackDistanceVertical = 0.0f;
				flyhackDistanceHorizontal = 0.0f;
			}
		}
		return false;
	}

	bool ValidateMove(float deltaTime) {
		auto lp = esp::local_player;
		bool result;
		bool flag = deltaTime > 1.f;

		flyhackPauseTime = max(0.f, flyhackPauseTime - deltaTime);
		ticks.Reset();
		auto trans = get_transform(esp::local_player);
		
		if (ticks.HasNext()) {
			bool flag = trans ? !(!trans) : false;
			VMatrix v; v.matrix_identity();
			VMatrix matrix4x = flag ? v : get_localToWorldMatrix(trans);

			Vector3 oldPos = flag ? ticks.startPoint :
				matrix4x.MultiplyPoint3x4(ticks.startPoint);
			Vector3 vector = flag ? ticks.startPoint :
				matrix4x.MultiplyPoint3x4(ticks.endPoint);
			float num = 0.1f;
			float num2 = 15.0f;
			num = max(ticks.len / num2, num);
			while (ticks.MoveNext(num))
			{
				vector = (flag ? ticks.currentPoint
					: matrix4x.MultiplyPoint3x4(ticks.currentPoint));

				TestFlying2(lp, oldPos, vector, true);
				oldPos = vector;
			}
		}
		return true;
	}

	void FinalizeTick(float deltatime) {
		if (esp::local_player->is_sleeping())
			return;
		tickDeltaTime += deltatime;
		bool flag = ticks.startPoint != ticks.endPoint;
		if (flag) {
			if (ValidateMove(tickDeltaTime)
				&& (vars->visual.flyhack_indicator || vars->misc.flyhack_stop)) {
				//good
			}
			else {
				//bad
			}
			settings::vert_flyhack = flyhackDistanceVertical;
			settings::hor_flyhack = flyhackDistanceHorizontal;
		}
		ticks.Reset(get_transform(esp::local_player)->get_bone_position());
		//ticks.Reset(esp::local_player->get_player_eyes()->get_position());
	}

	void ServerUpdate(float deltaTime, 
		base_player* ply) {
		desyncTimeRaw = max(ply->get_last_sent_tick_time() - deltaTime, 0.f);
		desyncTimeClamped = max(desyncTimeRaw, 1.f);
		FinalizeTick(deltaTime);
	}

	bool LineCircleIntersection(Vector3 center, 
		float radius, 
		Vector3 rayStart, 
		Vector3 rayEnd,
		float& offset)
	{
		Vector2 P(rayStart.x, rayStart.z);
		Vector2 Q(rayEnd.x, rayEnd.z);

		float a = Q.y - P.y;
		float b = P.x - Q.x;
		float c = (a * (P.x) + b * (P.y)) * -1.f;

		float x = center.x;
		float y = center.z;

		float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
		float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

		Vector2 closestPoint(c_x, c_y);

		float distance = P.Distance(Q);

		if (P.Distance(closestPoint) > distance || Q.Distance(closestPoint) > distance)
		{
			return false;
		}

		if (radius > closestPoint.Distance(Vector2(center.x, center.z)))
		{
			Vector2 P(rayStart.x, rayStart.y);
			Vector2 Q(rayEnd.x, rayEnd.y);

			float a = Q.y - P.y;
			float b = P.x - Q.x;
			float c = (a * (P.x) + b * (P.y)) * -1.f;

			float x = center.x;
			float y = center.y;

			float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
			float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

			Vector2 closestPoint(c_x, c_y);
			if (radius > closestPoint.Distance(Vector2(center.x, center.y)))
			{
				return true;
			}
			else
			{
				offset += std::fabs(center.y - closestPoint.y);
				return false;
			}
		}

		return false;
	};

	//AUTO BOT STUFF LOLLLL
	//
	// AIMS:
	// AUTO FARM { 
	//	FORCE LOOKING TO WALKING DIRECTION
	//	CONSTANTLY CHECK FOR PLAYERS, 
	//   -HAVE THEY ALREADY LOOKED AT ME MORE THAN TWICE? CHEATER?
	//   -ARE THEY VISIBLE?
	//	 -SHOOT AT PLAYER?
	// 
	//	RETURN TO BASE?
	//	AUTO DEPOT????
	// }
	// 
	// 
	// AUTO BOT? {
	//	IF NOT FARMING LOOK FOR PLACE TO PEEK WITH MANIP ??
	//	HVH MODE?
	//  ....??????
	// }
	//

	Vector3 lowest_pos(Vector3 in)
	{
		Vector3 current = in;
		for (size_t i = 0; i < 100; i++)
		{
			if (esp::local_player->is_visible(in, current))
			{
				current = Vector3(current.x, current.y -= 1.f, current.z);
				continue;
			}
			else break;
		}
		return Vector3(current.x, current.y += 1.6f, current.z);
	}

	float dist_from_ground(Vector3 v)
	{
		Vector3 p = v;
		int t = 0;
		while (t++ < 100)
		{
			if (!esp::local_player->is_visible(v, p))
				return v.distance(p);
			p.y -= 0.1;
		}
	}

	namespace autobot {
		bool needs_to_jump = false;
		int psteps = 0;
		Vector3 last_pos = Vector3(0, 0, 0);
		float last_pos_time = 0.f;

		void PathSmooth(std::vector<Vector3>& ref) {
			std::vector<int> indexes = { };
			if (ref.size() < 3) return;
			std::vector<Vector3> new_path = { ref[0], ref[1] };
			auto lp = esp::local_player;
			Vector3 current = ref[0];
			Vector3 next = ref[1];
			int fi = 0;
			for (size_t i = 2; i < ref.size(); i++)
			{
				next = ref[i];
				if (lp->is_visible(current, next))
					continue;
				else
					new_path.push_back(next);
			}
			if (!new_path.empty() && new_path.size() < ref.size())
				ref = new_path;
		}

		void CreatePath(Vector3 marker_pos, 
			Vector3 point)
		{
			node.pos = marker_pos;
			node.steps = 1;
			//create path
			std::vector<Vector3> path;
			Vector3 original = point;
			bool failed = false;
			Vector3 old_point = point;
			float control = 0.f;
			int iterations = 0;
			while (point.distance(node.pos) > 1.5f)
			{
				if (iterations++ > 500)
					break;

				path.push_back(point);
				//Vector3 new_point = lowest_pos(Vector3::move_towards(point, node.pos, 1.0f));
				Vector3 new_point = Vector3::move_towards(point, node.pos, 1.0f);

				if (esp::local_player->is_visible(point, new_point, 1.5f))
				{
					esp::local_player->console_echo(string::wformat(_(L"[trap]: CreatePath - visibility straight ahead (%d)"), path.size()));
					old_point = point;
					point = lowest_pos(new_point);
				}
				else
				{
					esp::local_player->console_echo(string::wformat(_(L"[trap]: CreatePath - no visibility straight ahead, creating sphere (%d)"), path.size()));

					std::vector<Vector3> ps = {};

					for (auto e : sphere1m) //create sphere if cannot find LOS straight ahead
						if (esp::local_player->is_visible(point, point + e, 1.5f)
							&& (point + e).distance(node.pos) < point.distance(node.pos)
							&& (point + e).distance(point) > 0.7f)
						{
							ps.push_back(lowest_pos(point + e));
						}

					Vector3 best = Vector3(0, 0, 0);
					if (ps.size() == 0) {
						esp::local_player->console_echo(string::wformat(_(L"[trap]: CreatePath could not create another node, path size: %i"), path.size()));
						break;
					}

					esp::local_player->console_echo(string::wformat(_(L"[trap]: CreatePath - potentials: %d"), ps.size()));

					for (auto e : ps)
						if (e.distance(node.pos) < best.distance(node.pos)
							&& dist_from_ground(e) < 1.6f)
							best = e;
					esp::local_player->console_echo(string::wformat(_(L"[trap]: CreatePath - closest (best chosen) (%d, %d, %d) (%d)"), (int)best.x, (int)best.y, (int)best.z, path.size()));
					old_point = point;
					point = best;
				}
			}
			node.path = path;
			//if (!node.path.empty())
			//	PathSmooth(node.path);
		}

		void do_jump(playerwalkmovement* pwm, 
			modelstate* state,
			float force = 10.f) {
			if (!pwm || !state) return;
			state->set_flag(rust::classes::ModelState_Flag::OnGround);
			state->setjumped(true);
			pwm->set_jump_time(get_time());
			auto vel = pwm->get_body_velocity();
			pwm->set_body_velocity(Vector3(vel.x, force, vel.z));
		}

		void auto_farm(playerwalkmovement* pwm) {
			auto lp = esp::local_player;
			if (!lp || !pwm) return; 
			
			Vector3 vel = pwm->get_TargetMovement();
			vel = Vector3(vel.x / vel.length() * 5.5f, vel.y, vel.z / vel.length() * 5.5f);
			auto eyepos = lp->get_player_eyes()->get_position();

			auto transform = get_transform((base_player*)node.ent);
			auto hp = *reinterpret_cast<float*>(node.ent + 0x178); //detect if broken with this fuck knows why
			if (transform && hp > 60) {
				auto marker_pos = get_position((uintptr_t)transform);
				Sphere(marker_pos, 1.f, col(1, 1, 1, 1), 0.02f, 100.f);
				if (node.steps > 0
					&& eyepos.distance(node.pos) < 1.f)
				{
					node.path.clear();
					node.pos = Vector3(0, 0, 0);
					node.steps = 0;
					vel = Vector3(0, 0, 0);
				}

				if (eyepos.distance(node.pos) >= 1.f)
				{
					if (node.path.empty() && (node.pos.is_empty() || node.pos == Vector3(0, 0, 0))
						&& eyepos.distance(node.pos) > 1.f)
						CreatePath(marker_pos, eyepos);

					Vector3 current_step = node.path[node.steps];

					psteps = node.steps;
					if (current_step.distance(node.pos) <= 0.5f)
					{
						vel = Vector3(0, 0, 0);
						node.path.clear();
						node.pos = Vector3(0, 0, 0);
						node.steps = 0;
						return;
					}

					//draw path
					if (!node.path.empty())
					{
						for (size_t i = 1; i < node.path.size(); i++)
						{
							if (node.path[i] == current_step)
								Line(node.path[i - 1], node.path[i], col(12, 150, 100, 50), 0.02f, false, true);
							else
								Line(node.path[i - 1], node.path[i], col(12, 150, 100, 50), 0.02f, false, true);
						}
					}

					if (eyepos.distance(current_step) < 1.6f)
						node.steps += 1;

					if (node.steps >= node.path.size() - 1)
					{
						vel = Vector3(0, 0, 0);
						node.path.clear();
						node.pos = Vector3(0, 0, 0);
						node.steps = 0;
						return;
					}

					Vector3 dir = ((Vector3(current_step.x, current_step.y - dist_from_ground(current_step) + 0.1f, current_step.z)) - eyepos).Normalized();
					vel = { (dir.x / dir.length() * 5.5f), vel.y, (dir.z / dir.length() * 5.5f) };
					pwm->set_TargetMovement(vel);

					last_pos = eyepos;
					last_pos_time = get_fixedTime();

					if (node.path[node.steps].y - eyepos.y > 1.f)
					{
						needs_to_jump = true;
						pwm->set_TargetMovement({ vel.x, vel.y += 10, vel.z });


						//auto state = lp->get_model_state();
						//if (settings::vert_flyhack < 2.5f && settings::hor_flyhack < 6.f)
						//{
						//	pwm->force_jump(state, true);
						//	do_jump(pwm, state, 3.f);
						//}
					}
				}
			}
			else
			{
				misc::node.ent = (uintptr_t)lp->find_closest(_("OreResourceEntity"), (networkable*)lp, 200.f);

				misc::node.path.clear();
				misc::node.pos = Vector3(0, 0, 0);
				misc::node.steps = 0;
			}
		}
	}

	void get_prediction(aim_target target,
		Vector3 rpc_position,
		Vector3 target_pos,
		Vector3 original_vel,
		Vector3 &aimbot_velocity,
		Vector3 &_aimdir,
		Projectile* p,
		bool skip_draw = false) {

		float travel_t;
		Vector3 player_velocity = Vector3(0, 0, 0);
		std::vector<Vector3> path = {};
		int simulations = 0;

		target_pos.y -= 0.1f;

		if (target.player) {
			auto travel = 0.f;
			auto vel = (getmodifiedaimcone(0, rpc_position - target_pos, true)).Normalized() * original_vel.length();
			auto drag = p->drag();
			auto grav = p->gravityModifier();
			auto gravity = get_gravity();
			auto deltatime = get_deltaTime();
			auto timescale = get_timeScale();
			auto offset = 0.1f;
			simulations = 0;

			//auto wv = GetWorldVelocity(target.player);
			//player_velocity = Vector3(wv.x, 0, wv.z);


			while (simulations < 300) {
				travel_t = 0.f;
				auto pos = rpc_position;
				auto origin = pos;
				float num = deltatime * timescale;
				float travelTime = 0.f;
				int num3 = (int)(8.f / num);

				Vector3 vt = target_pos + Vector3(0, offset, 0);
				_aimdir = getmodifiedaimcone(0.f, vt - rpc_position, true);
				auto velocity = _aimdir.Normalized() * original_vel.length();

				//predict movement?

				for (size_t i = 0; i < num3; i++)
				{
					origin = pos;
					pos += velocity * num;
					velocity += gravity * grav * num;
					velocity -= velocity * drag * num;
					travel_t += num;
					if (misc::LineCircleIntersection(target_pos, 0.1f, origin, pos, offset))
					{
						//Line(origin, pos, col(0, 1, 0, 1), 10.f, false, true);
						aimbot_velocity = (_aimdir).Normalized() * original_vel.length();
						//emulate 1 tick has already passed
						aimbot_velocity += gravity * grav * num;
						aimbot_velocity -= aimbot_velocity * drag * num;
						break;
					}
					else
					{
						//Line(origin, pos, col(1, 1, 1, 1), 10.f, false, true);
					}
				}
				offset += 0.1f;
				simulations++;
				if (!aimbot_velocity.is_empty())
					break;
			}
		}

		if (travel_t > 0.f) {
			//movement prediction
			aimbot_velocity = Vector3(0, 0, 0);
			if (target.player) {
				auto wv = target.avg_vel;
				
				if(wv.is_empty() || wv.is_nan())
					wv = GetWorldVelocity(target.player);

				Vector3 player_velocity = Vector3(wv.x, 0, wv.z) * 0.9f;
				Vector3 final_vel = player_velocity * travel_t;
				Vector3 actual = target_pos += final_vel;

				auto partialTime = p->partialTime();
				auto travel = 0.f;
				auto vel = (getmodifiedaimcone(0, rpc_position - actual, true)).Normalized() * original_vel.length();
				auto drag = p->drag();
				auto grav = p->gravityModifier();
				auto gravity = get_gravity();
				auto deltatime = get_deltaTime();
				auto timescale = get_timeScale();
				auto offset = 0.1f;
				simulations = 0;


				travel_t = 0.f;

				while (simulations < 1200) {
					path.clear();
					auto pos = rpc_position;
					auto origin = pos;
					float num = deltatime * timescale;
					float travelTime = 0.f;
					int num3 = (int)(8.f / num);

					Vector3 vt = actual + Vector3(0, offset, 0);
					_aimdir = getmodifiedaimcone(0.f, vt - rpc_position, true);
					auto velocity = _aimdir.Normalized() * original_vel.length();

					//predict movement?

					for (size_t i = 0; i < num3; i++)
					{
						path.push_back(origin);
						origin = pos;
						pos += velocity * num;
						velocity += gravity * grav * num;
						velocity -= velocity * drag * num;
						travel_t += num;

						if (misc::LineCircleIntersection(actual, 0.1f, origin, pos, offset))
						{
							//Line(origin, pos, col(0, 1, 0, 1), 10.f, false, true);
							aimbot_velocity = (_aimdir).Normalized() * original_vel.length();
							//emulate 1 tick has already passed
							aimbot_velocity += gravity * grav * num;
							aimbot_velocity -= aimbot_velocity * drag * num;

							if (!skip_draw && vars->visual.tracers)
							{
								path.push_back(target_pos);
								Vector3 va = path[0];
								for (auto v : path) {
									Line(va, v, col(12, 150, 100, 50), 10.f, false, true);
									va = v;
								}
							}
							break;
						}
						else
						{
							//Line(origin, pos, col(1, 1, 1, 1), 10.f, false, true);
						}
					}
					offset += 0.05f;
					simulations++;
					if (!aimbot_velocity.is_empty())
						break;
				}
			}
		}
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
		static auto Run = reinterpret_cast<rust::classes::string(*)(uintptr_t, rust::classes::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 0, _(""), _(""))));


		static auto get_bodyleanoffset = reinterpret_cast<Vector3(*)(playereyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));
		static auto EyePositionForPlayer = reinterpret_cast<Vector3(*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));
		static auto isdown = reinterpret_cast<bool(*)(input_state*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));
		static auto eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));
		static auto baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));
		static auto attackent_addpunch = reinterpret_cast<void(*)(uintptr_t, Vector3, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HeldEntity"), _("AddPunch"), 0, _(""), _(""))));
		static auto baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(base_projectile*, rust::classes::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));
		static auto DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

		
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

	static auto set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

	static auto draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

	static auto set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

	static auto GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

	static auto get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

	static auto IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

	static auto OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

	static auto change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address); //BaseEntity$$ServerRPC<string, bool> Address

	static auto ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);
	
	static auto get_resourcePath = reinterpret_cast<rust::classes::string (*)(uintptr_t)>(mem::game_assembly_base + offsets::Method$ResourceRef_method);

	static auto DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

	static auto PerformanceUI_Update = reinterpret_cast<void (*)(void*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PerformanceUI"), _("Update"), -1, _(""), _("Facepunch"))));

	void init_hooks() {
		orig::IsConnected = reinterpret_cast<bool (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("IsConnected"), 0, _(""), _("Network"))));
		orig::OnNetworkMessage = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Client"), _("OnNetworkMessage"), 1, _(""), _(""))));
		orig::BaseProjectile_OnSignal = reinterpret_cast<void (*)(base_projectile*, int, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("OnSignal"), 2, _(""), _(""))));
		orig::baseplayer_client_input = reinterpret_cast<void (*)(base_player*, input_state*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		orig::playerwalkmovement_client_input = reinterpret_cast<void (*)(playerwalkmovement*, uintptr_t, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		orig::DoFixedUpdate = reinterpret_cast<void (*)(playerwalkmovement*, modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));
		orig::blocksprint = reinterpret_cast<void (*)(base_player*, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("BlockSprint"), 1, _(""), _(""))));
		orig::Run = reinterpret_cast<rust::classes::string(*)(uintptr_t, rust::classes::string, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ConsoleSystem"), _("Run"), 0, _(""), _(""))));

		orig::get_bodyleanoffset = reinterpret_cast<Vector3(*)(playereyes*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerEyes"), _("get_BodyLeanOffset"), 0, _(""), _(""))));

		orig::isdown = reinterpret_cast<bool(*)(input_state*, int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("InputState"), _("IsDown"), 1, _(""), _(""))));

		orig::UpdateVelocity = reinterpret_cast<void (*)(playerwalkmovement*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("UpdateVelocity"), -1, _(""), _(""))));

		orig::EyePositionForPlayer = reinterpret_cast<Vector3(*)(basemountable*, base_player*, Vector4)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseMountable"), _("EyePositionForPlayer"), 2, _(""), _(""))));

		orig::eokadoattack = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("FlintStrikeWeapon"), _("DoAttack"), 0, _(""), _(""))));

		orig::baseprojectile_launchprojectile = reinterpret_cast<void(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		orig::baseprojectile_createprojectile = reinterpret_cast<uintptr_t(*)(base_projectile*, rust::classes::string, Vector3, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseProjectile"), _("CreateProjectile"), 0, _(""), _(""))));

		orig::DoHit = reinterpret_cast<bool (*)(Projectile*, HitTest*, Vector3, Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Projectile"), _("DoHit"), -1, _(""), _(""))));

		orig::attackent_addpunch = reinterpret_cast<void(*)(uintptr_t, Vector3, float)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("HeldEntity"), _("AddPunch"), 0, _(""), _(""))));

		serverrpc_projecileshoot = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("4C 8B 0D ? ? ? ? 48 8B 75 28"));

		serverrpc_uint = rb::pattern::find_rel(
			_("GameAssembly.dll"), _("74 3A 4C 8B 0D ? ? ? ? 48 8B CB"));

		ServerRPC_int = reinterpret_cast<void (*)(base_projectile*, rust::classes::string funcName, unsigned int arg1, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_uint_);

		get_resourcePath = reinterpret_cast<rust::classes::string(*)(uintptr_t)>(mem::game_assembly_base + offsets::Method$ResourceRef_method);

		change_code_rpc = reinterpret_cast<void (*)(base_player*, rust::classes::string, uintptr_t, bool, uintptr_t)>(mem::game_assembly_base + offsets::BaseEntity$$ServerRPC_string_bool_Address);

		set_sprinting = reinterpret_cast<void (*)(modelstate*, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));

		draw_get = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("Get"), 0, _(""), _("UnityEngine"))));

		set_flying = reinterpret_cast<void (*)(modelstate * model_state, bool value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("set_flying"), 1, _(""), _(""))));

		GetSpeed = reinterpret_cast<float (*)(base_player * baseplayer, float running, float ducking)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("GetSpeed"), 2, _(""), _(""))));

		get_ducked = reinterpret_cast<bool (*)(modelstate*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("ModelState"), _("get_ducked"), 0, _(""), _(""))));

		IsSwimming = reinterpret_cast<bool (*)(base_player*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("IsSwimming"), 0, _(""), _(""))));

		PerformanceUI_Update = reinterpret_cast<void (*)(void*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PerformanceUI"), _("Update"), -1, _(""), _("Facepunch"))));

		OnLand = reinterpret_cast<void (*)(base_player*, float fVelocity)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));

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

	bool flying = false, is_speeding = false, is_lagging = false, has_intialized_methods = false, wake = true;
	float nextActionTime = 0, period = 1.4721;
	Vector3 m_debugcam_toggle_pos, m_debugcam_pos;
	uintptr_t do_fixed_update_ptr, client_input_ptr, bodylean_ptr, mounteyepos_ptr, isdown_ptr, __go;

	void hk_serverrpc_projectileshoot(int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5) {
		Projectile* p;
		Vector3 rpc_position;
		float time = get_fixedTime();
		float travel_t = 0.f;
		int simulations = 0;
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

			const auto stats = baseprojectile->get_stats(weapon->get_item_definition_id());

			Vector3 aim_angle;

			bool manipulated = false;

			Vector3 original_vel{};

			bool vis_fat = false;
			//get position of player with velocity
			//get direction to that
			//calculate perfect Y velocity in loop to find where projectile lands

			//calc new target position with velocity
			Vector3 target_velocity, target_pos;
			if (target.player)
			{
				target_pos = target.player->get_bone_transform(48)->get_bone_position();
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

				target.visible = target.player->is_visible(rpc_position, target.pos);
				if (misc::best_target == Vector3(0, 0, 0)
					&& vars->combat.thick_bullet
					&& vars->combat.shoot_at_fatbullet
					&& !target.visible)
				{
					for (auto v : sphere1m)
					{
						if (target.player)
						{
							if (target.player->is_visible(target_pos, target_pos + v)
								&& target.player->is_visible(target_pos + v, rpc_position))
								misc::best_target = target_pos + v;
						}
					}
				}

				if (vars->combat.manipulator
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
				auto projectile = *(base_projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				Vector3 a;
				misc::get_prediction(target, rpc_position, target_pos, original_vel, aimbot_velocity, a, p);

				/*
				Vector3 orig;
				Vector3 velocity;

				Vector3 new_position = rpc_position;
				float	partialtime = p->partialTime();
				float	traveltime = 0.f;
				Vector3 grav = get_gravity();
				float	drag = p->drag();
				float timestep = 0.03125f;
				float offset = 5.f;
				if (!drag) break;

				for (int iii = 0; iii < 10000; iii++)
				{
					orig = rpc_position;
					//aim_direction = getmodifiedaimcone(0, (orig - target_pos) + Vector3(0, offset, 0), true);
					velocity = -(Vector3(aim_direction.x, aim_direction.y, aim_direction.z).Normalized() * original_vel.length());
					velocity.y += offset;
					partialtime = p->partialTime();
					traveltime = 0.f;
					//velocity = target_direction.Normalized() * velocity.length();
					//Vector3 original_velocity = velocity;

					for (float f = 0.f; f < 8.f; f += timestep) {
						Projectile::SimulateProjectile(new_position, velocity, partialtime, traveltime, grav, drag, timestep);

						traveltime += timestep;

						if (orig.distance(target_pos) > 400.f)
							break;

						if (misc::LineCircleIntersection(target_pos, 0.1f, orig, new_position, offset))
						{
							aimbot_velocity = -(Vector3(aim_direction.x, aim_direction.y, aim_direction.z).Normalized() * original_vel.length());

							Line(orig, new_position, col(0.0, 1.0, 0.4, 1), 10.f, false, true);
							Sphere(new_position, 0.1f, col(0.0, 1.0, 0.1, 1), 10.f, 400.f);
							break;
						}
						else
						{
							Line(orig, new_position, col(0.2, 0.5, 0.9, 1), 10.f, false, true);
						}

						if (!aimbot_velocity.is_empty())
							break;

						orig = new_position;
					}
					if (!aimbot_velocity.is_empty())
						break;
					offset += 0.001f;
				}
				*/
				break;
			}


			for (int i = 0; i < size; i++) {
				auto projectile = *(uintptr_t*)(shoot_list + 0x20 + i * 0x8);
				if (target.player && (target.visible || manipulated || misc::autoshot) && !target.teammate) {
					*reinterpret_cast<Vector3*>(projectile + 0x24) = aimbot_velocity; //startvel
				}
			}

			for (int i = 0; i < projectile_list->get_size(); i++) {
				auto projectile = *(base_projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
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
					if (target.player && !target.teammate) {
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
					projectile->set_projectile_thickness(vars->combat.thickness > 1.f ? 1.f : vars->combat.thickness);
				else
					projectile->set_projectile_thickness(projectile->thickness);
				
				p->integrity(1.f);
				 
				 
				//create and SEND FAKE copy of projectile so game only updates original
				//Projectile* fake = new Projectile(*p);
				p->initialVelocity(aimbot_velocity);
				misc::fired_projectile f = { p, nullptr, time, 1, target };
				
				//p = *(Projectile**)((uintptr_t)projectile_list + 0x20 + i * 0x8);
				//*reinterpret_cast<uintptr_t*>((uintptr_t)projectile_list + 0x20 + i * 0x8) = (uintptr_t)fake;
				
				for (size_t i = 0; i < 32; i++)
					if (misc::fired_projectiles[i].fired_at <= 10.f) {
						misc::fired_projectiles[i] = f;
						break;
					}
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
		auto  ppu = reinterpret_cast<rust::classes::PlayerProjectileUpdate*>(_ppa);

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
		auto  ppa = reinterpret_cast<rust::classes::PlayerProjectileRicochet*>(_ppa);
		

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
		//	Vector3 targetpos = esp::best_target.player->get_bone_transform(48)->get_bone_position();
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
			
			//Update((Projectile*)projectile); //many invalids with fat bullet manipulator as projectile position isnt updated before the hit

			auto hit_test = projectile->get_hit_test();
			if (!hit_test)
				break;

			if (!hit_test->get_gameobject())
				break;

			auto layer = hit_test->get_gameobject()->get_layer();
			auto prefab_name = hit_test->get_gameobject()->get_prefab_name();

			aim_target target = esp::best_target;//esp::local_player->get_aimbot_target(camera_pos);

			if (!target.player || !target.network_id)
				break;

			auto hit_entity = (base_player*)hit_test->get_hit_entity();
			if (layer == rust::classes::layer::Player_Server) {
				if (hit_entity->is_teammate(esp::local_player)) {
					hit_test->set_ignore_entity(hit_entity);
					return;
				}
			}
			else {
				hit_test->set_ignore_entity(hit_entity);
				return;
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
					 && esp::local_player->is_visible(target.player->get_bone_transform(
						 (int)rust::classes::Bone_List::head)->get_bone_position(), projectile->get_current_position()))
					test[0] = { 698017942, 2173623152 };
				if (vars->combat.hitboxes.Body
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::pelvis)->get_bone_position(), projectile->get_current_position()))
					test[1] = { 1031402764, 1750816991 };
				if (vars->combat.hitboxes.Upperbody
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::spine4)->get_bone_position(), projectile->get_current_position()))
					test[2] = { 3901657145, 1750816991 };
				if (vars->combat.hitboxes.Hands
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::r_hand)->get_bone_position(), projectile->get_current_position()))
					test[3] = { 102231371, 1750816991 };
				if (vars->combat.hitboxes.Penis
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::penis)->get_bone_position(), projectile->get_current_position()))
					test[4] = { 3771021956, 1750816991 };
				if (vars->combat.hitboxes.Legs
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::l_hip)->get_bone_position(), projectile->get_current_position()))
					test[5] = { 3892428003, 1750816991 };
				if (vars->combat.hitboxes.Feet
					&& esp::local_player->is_visible(target.player->get_bone_transform(
						(int)rust::classes::Bone_List::r_foot)->get_bone_position(), projectile->get_current_position()))
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

	void hk_serverrpc_doplace(int64_t rcx, int64_t rdx, int64_t r9, int64_t _ppa, int64_t arg5) {
		//auto  planner = reinterpret_cast<Planner*>(get_rbx_value());
		auto  ppa = reinterpret_cast<rust::classes::CreateBuilding*>(_ppa);


		const auto orig_fn =
			reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(
				hooks::orig::createbuilding);

		if(!esp::local_player)
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		auto wpn = esp::local_player->get_active_weapon();
		auto held = wpn ? wpn->get_base_projectile() : nullptr; 
		if (LI_FIND(strcmp)(held->get_class_name(), _("Planner")))
			return orig_fn(rcx, rdx, r9, _ppa, arg5);
		auto planner = reinterpret_cast<Planner*>(held);

		auto guide = planner->guide();
		if(!guide)
			return orig_fn(rcx, rdx, r9, _ppa, arg5);

		auto position = *reinterpret_cast<Vector3*>(guide + 0x18 + 0x34);
		auto normal = *reinterpret_cast<Vector3*>(guide + 0x18 + 0x40);

		if (GetAsyncKeyState(0x38)) { //0x43 = C
			*reinterpret_cast<unsigned int*>(ppa + 0x14) = esp::selected_entity_id;


			auto build_id = *reinterpret_cast<unsigned int*>(ppa + 0x14);
			networkable* FindEntity = *reinterpret_cast<networkable**>(esp::find_networkable_by_id(build_id));
			if (FindEntity) {
				transform* tr = get_transform((base_player*)FindEntity);
				//transform* Traaa = get_transform//FindEntity->_get_transform();
				if (tr) {
					*reinterpret_cast<Vector3*>(ppa + 0x20) = InverseTransformPoint(tr, position);
					*reinterpret_cast<Vector3*>(ppa + 0x2C) = InverseTransformDirection(tr, normal);
				}
			}
		}
		return orig_fn(rcx, rdx, r9, _ppa, arg5);
	}

#define ptr_assert(val) \
    if(val == 0)        \
    return
	uintptr_t client_entities;

	bool __stdcall dohit_hk(Projectile* p, HitTest* h, Vector3 v1, Vector3 v2) {

		return orig::DoHit(p, h, v1, v2);
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


						//if (!unity::space_material)
						//{
						//	/
						//	uintptr_t kl = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::sky_typeinfo);
						//	uintptr_t fieldz = *reinterpret_cast<uintptr_t*>(kl + 0xB8);
						//	uintptr_t instances = *reinterpret_cast<uintptr_t*>(fieldz);
						//	uintptr_t list = *reinterpret_cast<uintptr_t*>(instances + 0x10);
						//	uintptr_t tod_sky = *reinterpret_cast<uintptr_t*>(list + 0x20); // 'Dome'
						//
						//	auto components = *reinterpret_cast<uintptr_t*>(tod_sky + 0xA8);
						//	if (components)
						//	{
						//		auto scattering = *reinterpret_cast<uintptr_t*>(components + 0x1A0);
						//
						//		if (scattering)
						//		{
						//			auto material = *reinterpret_cast<uintptr_t*>(scattering + 0x88); //private Material scatteringMaterial; // 0x78
						//
						//			if(material)
						//				unity::space_material = material; //private Material skyMaskMaterial; // 0x88
										//unity::space_material = *reinterpret_cast<uintptr_t*>(s + 0x78); //private Material skyMaskMaterial; // 0x88
						//		}
						//	}
						//}
						
						//if (!unity::star_material)
						//	unity::star_material = unity::get_StarMaterial(p2);
						//if (!unity::sun_material)
						//	unity::sun_material = unity::get_SunMaterial(p2);
						//if (!unity::moon_material)
						//	unity::moon_material = unity::get_MoonMaterial(p2);
						//if (!unity::atmo_material)
						//	unity::atmo_material = unity::get_AtmosphereMaterial(p2);
						//if (!unity::clear_material)
						//	unity::clear_material = unity::get_ClearMaterial(p2);
						//if (!unity::cloud_material)
						//	unity::cloud_material = unity::get_CloudMaterial(p2);

						const auto TOD_Day = *reinterpret_cast<uintptr_t*>(p2 + 0x50);
						const auto TOD_Night = *reinterpret_cast<uintptr_t*>(p2 + 0x58);
						const auto TOD_Stars = *reinterpret_cast<uintptr_t*>(p2 + 0x70);
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

	void hk_playerwalkmovement_ClientInput(playerwalkmovement* player_walk_movement, uintptr_t inputstate, modelstate* model_state) {
		orig::playerwalkmovement_client_input(player_walk_movement, inputstate, model_state);
		Vector3 vel = player_walk_movement->get_TargetMovement();
		auto loco = esp::local_player;
		auto dont_move = false;

		if (!loco || loco->is_sleeping())
			return;

		if (loco && !loco->is_sleeping() && settings::desyncTime < 0.f) {
			if (vars->misc.flyhack_stop) {
				Vector3 curr = get_transform(esp::local_player)->get_bone_position();
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

			misc::cLastTickEyePos = esp::local_player->get_player_eyes()->get_position();//get_transform(esp::local_player)->get_bone_position();//baseplayer->get_player_eyes()->get_position();
			misc::cLastTickPos = get_transform(esp::local_player)->get_bone_position();//get_transform(esp::local_player)->get_bone_position();//baseplayer->get_player_eyes()->get_position();
			misc::ticks.AddPoint(misc::cLastTickPos);
			misc::ServerUpdate(misc::tickDeltaTime, esp::local_player);
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
		
		auto wpn = esp::local_player->get_active_weapon();
		auto held = wpn ? wpn->get_base_projectile() : nullptr;
		if (vars->combat.always_reload
			&& held)
		{
			misc::time_since_last_shot = (get_fixedTime() - misc::fixed_time_last_shot);
			settings::time_since_last_shot = misc::time_since_last_shot;
			if (misc::just_shot && (misc::time_since_last_shot > 0.2f))
			{
				unity::ServerRPC((uintptr_t)held, rust::classes::string(_(L"StartReload")));
				esp::local_player->console_echo(_(L"[trap]: ClientInput - starting reload"));
				//esp::local_player->SendSignalBroadcast(rust::classes::Signal::Reload); //does this cause animation? YES
				misc::just_shot = false;
			}
			float reloadtime = held->get_reload_time();
			esp::rl_time = reloadtime;

			if (misc::time_since_last_shot > reloadtime //-10% for faster reloads than normal >:)
				&& !misc::did_reload)
			{
				esp::local_player->console_echo(_(L"[trap]: ClientInput - finishing reload"));
				unity::ServerRPC((uintptr_t)held, rust::classes::string(_(L"Reload")));
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
						misc::node.ent = (uintptr_t)loco->find_closest(_("OreResourceEntity"), (networkable*)loco, 200.f);
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

	std::vector<Projectile*> created_projectiles = {};

	void LaunchProjectileClientSide_R(base_projectile* p,
		uintptr_t ammodef,
		int projectilecount = 1,
		float spread = 1.f)
	{
		//this will essentially be recreation of 
		//LaunchProjectileClientSide as that is 
		//what LaunchProjectile calls

		//presume spread is 1 unless nospread, 0

		spread = 0.f;
		if (!p) return;
		if (!ammodef) return;
		auto lp = esp::local_player;
		if (!lp) return;
		auto eyes = lp->get_player_eyes();
		if (!eyes) return;


		auto mod = (uintptr_t)((networkable*)ammodef)->GetComponent(unity::GetType(_(""), _("ItemModProjectile")));
		if (mod) {
			created_projectiles.clear();
			//game gets spread based upon weapon mods here, we will keep as 1

			float num = 1.f; //?
			float num2 = 1.f; //?
			//projectileshoot ps{};


			auto projectileshoot_class = il2cpp::init_class(_("ProjectileShoot"), _("ProtoBuf"));
			projectileshoot* ps = (projectileshoot*)il2cpp::methods::object_new(projectileshoot_class);
			//ps.projectiles = rust::list<projectileshoot_projectile>();
			ps->ammoType = *reinterpret_cast<int*>(ammodef + 0x18 /*public int itemid; // 0x18*/);
			//ps->projectiles = //rust::list<projectileshoot_projectile*>*;
			for (size_t i = 0; i < projectilecount; i++)
			{
				Vector3 position = eyes->get_position();
				Vector3 vector = eyes->body_forward();
				auto projectilespread = *reinterpret_cast<float*>((uintptr_t)mod + 0x30);
				if (spread > 0.f || projectilespread > 0.f) {
					Vector4 rot = eyes->get_rotation();
					float num3 = animcurve_evaluate(*reinterpret_cast<uintptr_t*>((uintptr_t)p + 0x2E8), 1.f); //(Random.Range(0f, 1f));

					//real rust 0x94FEF0
					typedef float(*ind)(uintptr_t, int, int);//public float GetIndexedSpreadScalar(int shotIndex, int maxShots) { }
					auto indexed = ((ind)(mem::game_assembly_base + 0x94FEF0))(mod, i, projectilecount);

					typedef float(*scalar)(uintptr_t);//public float GetIndexedSpreadScalar(int shotIndex, int maxShots) { }
					auto spreadscalar = ((scalar)(mem::game_assembly_base + 0x94FFC0))((uintptr_t)mod);

					float num4 = (projectilecount > 1) ? indexed : spreadscalar;
					vector = getmodifiedaimcone(num * spread + projectilespread * num4, rot.vm(Vector3(0, 1, 0)), projectilecount <= 1);

					{
						//if global.dev draw arrow??????
					}
				}

				uintptr_t attackentity = (uintptr_t)((networkable*)p)->GetComponent(unity::GetType(_(""), _("AttackEntity")));
				auto proj = (Projectile*)((networkable*)mod)->GetComponent(unity::GetType(_(""), _("Projectile")));
				//projectileVelocityScale() could be incorrect
				Vector3 vector2 = vector * (getrandomvel((uintptr_t)mod) * 1.49f/*p->projectileVelocityScale()*/ * num * num2);

				srand(time(0));
				int seed = rand() % 0xfffffff + 1;

				auto projectileid = *reinterpret_cast<int*>((uintptr_t)lp + 0x638) + 1;

				auto gameobjref = *reinterpret_cast<uintptr_t*>((uintptr_t)mod + 0x18 /*public GameObjectRef projectileObject; 0x18*/);

				typedef uintptr_t(__stdcall* createprojectile)(uintptr_t, rust::classes::string, Vector3, Vector3, Vector3);
				auto projectile = ((createprojectile)(mem::game_assembly_base + 0x8C84D0))((uintptr_t)p, _(L"assets/prefabs/ammo/rifle/riflebullet.prefab"), position, vector, vector2);

				if (projectile) {
					*reinterpret_cast<uintptr_t*>((uintptr_t)	projectile + 0xE8 /*public ItemModProjectile mod; // 0xE8*/) = mod;
					*reinterpret_cast<int*>((uintptr_t)			projectile + 0xF4 /*public int seed; // 0xF4*/) = seed;
					*reinterpret_cast<uintptr_t*>((uintptr_t)	projectile + 0xD0 /*public BasePlayer owner; // 0xD0*/) = (uintptr_t)lp;
					*reinterpret_cast<uintptr_t*>((uintptr_t)	projectile + 0xD8 /*public AttackEntity sourceWeaponPrefab; // 0xD8*/) = attackentity;
					*reinterpret_cast<uintptr_t*>((uintptr_t)	projectile + 0xE0 /*public Projectile sourceProjectilePrefab; // 0xE0*/) = (uintptr_t)proj;
					*reinterpret_cast<int*>((uintptr_t)			projectile + 0xF0 /*public int projectileID; // 0xF0*/) = projectileid;
					*reinterpret_cast<bool*>((uintptr_t)		projectile + 0x114 /*public bool invisible; // 0x114*/) = false/*this.IsSilenced();*/;
					created_projectiles.push_back((Projectile*)projectile);
				}

				projectileshoot_projectile shoot;
				shoot.projectileID = projectileid;
				shoot.startPos = position;
				shoot.startVel = vector2;
				shoot.seed = seed;
					
				//ps.projectiles.push_back(shoot);
				for (size_t i = 0; i < numprojectiles; i++)
					(*reinterpret_cast<rust::list<projectileshoot_projectile*>**>(((uintptr_t)ps) + 0x18))->add(i, &shoot);

				auto first = ps->projectiles[0];
				//auto z = first->projectileID;
			}

			
			//call projectileshoot with our projectile
			//base.ServerRPC<ProjectileShoot>("CLProject", projectileShoot);
			typedef void(*rpc)(uintptr_t, rust::classes::string, projectileshoot*, uintptr_t);
			uintptr_t method_addr = mem::read<uintptr_t>(mem::game_assembly_base + 52469984);
			misc::emulated = true;
			((rpc)(mem::game_assembly_base + 24767696))((uintptr_t)lp, _(L"CLProject"), ps, method_addr);

			typedef Vector3(*inherit)(uintptr_t); 
			Vector3 inheritedvel = ((inherit)(mem::game_assembly_base + 0x7F1040))((uintptr_t)lp);

			for (auto c : created_projectiles)
			{
				c->UpdateVelocity(get_deltaTime(), c);
				c->currentVelocity() += inheritedvel;
			}	
			created_projectiles.clear();
		}
	}

	void hk_LaunchProjectile(base_projectile* p)
	{
		//define function that recreates launchprojectile
		if (vars->misc.emulate_p) {
			auto m = *reinterpret_cast<uintptr_t*>((uintptr_t)p + 0x2C0); //public BaseProjectile.Magazine primaryMagazine; // 0x2C0
			auto ammo = *reinterpret_cast<uintptr_t*>((uintptr_t)m + 0x20); //public ItemDefinition ammoType; // 0x20
			auto mod = ((networkable*)ammo)->GetComponent(unity::GetType(_(""), _("ItemModProjectile")));
			//auto projectile = (Projectile*)((networkable*)mod)->GetComponent(unity::GetType(_(""), _("Projectile")));
			if (mod)
			{
				auto ac = GetAimCone((uintptr_t)p);
				//int numprojectiles = *reinterpret_cast<int*>(mod + numprojectiles);
				int numprojectiles = 1;
				LaunchProjectileClientSide_R(p, ammo, numprojectiles/*public int numProjectiles; // 0x2C*/, ac);
				return;
			}
			else
				esp::local_player->console_echo(_(L"[K4] NO ITEMMODPROJECTILE"));
		}

		if (vars->combat.doubletap)
		{
			auto held = esp::local_player->get_active_weapon();
			auto m = held->get_base_projectile()->get_repeat_delay() * .75f; //we can shoot 25% faster??? more bullets?? :DDD

			int r = settings::desyncTime / m;
			if (r > 1)
			{
				esp::local_player->console_echo(string::wformat(_(L"[trap]: Launching %d projectiles!"), r));
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

		if (misc::manual) {
			auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)p + primaryMagazine);
			auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
			*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);

			updateammodisplay((uintptr_t)p);
			shot_fired((uintptr_t)p);
			did_attack_client_side((uintptr_t)p);
			misc::manual = false;
		}

		__try {
			return orig::baseprojectile_launchprojectile((uintptr_t)p);
		} __except(true) {}
	}

	uintptr_t hk_GetBuildingPrivilege(uintptr_t base_entity) {
		uintptr_t result = 0;

		if (vars->misc.force_privlidge
			&& esp::closest_building_block) {

			auto block = (BuildingBlock*)esp::closest_building_block;
			auto tranny = get_transform((base_player*)block);
			auto pos = get_position((uintptr_t)tranny);
			auto distance = esp::local_player->get_player_eyes()->get_position().distance(pos);
			
			if (distance <= 16.f) {
				typedef uintptr_t(*AAA)(uintptr_t);//GetDominatingBuildingPrivilege
				auto building = ((AAA)(mem::game_assembly_base + 0x866050))(esp::closest_building_block);
				typedef uintptr_t(*AAA)(uintptr_t);//GetDominatingBuildingPrivilege
				return ((AAA)(mem::game_assembly_base + 7088112))(building);
			}
		}

		return result;
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

	float last_gesture_rpc = 0.f;

	void hk_baseplayer_ClientInput(base_player* baseplayer, input_state* state) {

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

			misc::fired_projectile placeholder = { nullptr, 0, 1 };
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

		static uintptr_t* serverrpc_createbuilding;
		if (!serverrpc_createbuilding) {
			auto method_serverrpc_createbuilding = *reinterpret_cast<uintptr_t*>(mem::game_assembly_base + offsets::Method$BaseEntity_ServerRPC_CreateBuilding___);

			if (method_serverrpc_createbuilding) {
				serverrpc_createbuilding = **(uintptr_t***)(method_serverrpc_createbuilding + 0x30);

				hooks::orig::createbuilding = *serverrpc_createbuilding;

				*serverrpc_createbuilding = reinterpret_cast<uintptr_t>(&hooks::hk_serverrpc_doplace);
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
			auto tick_time = baseplayer->get_last_sent_tick_time();
			settings::desyncTime = (unity::get_realtimesincestartup() - tick_time) - 0.03125 * 3;

			auto wpn = baseplayer->get_active_weapon();

			auto held = wpn ? wpn->get_base_projectile() : nullptr;

			if (vars->misc.attack_on_mountables) {
				auto mountable = baseplayer->get_mountable();
				if (mountable)
					mountable->canwielditem() = true;
			}

			bool kyslol = false;

			if (vars->misc.TakeFallDamage && unity::GetKey(rust::classes::KeyCode(vars->keybinds.suicide))) {

				OnLand(baseplayer, -8.0001f - 100);
			}

			bool t1 = orig::isdown(state, rust::classes::BUTTON::FIRE_PRIMARY);
			auto t2 = orig::get_bodyleanoffset(baseplayer->get_player_eyes());

			if (vars->misc.admin_mode)
				baseplayer->set_admin_flag(rust::classes::PlayerFlags::IsAdmin);

			if (vars->misc.spiderman) {
				baseplayer->SpiderMan();
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
			if (esp::best_target.player && held && wpn)
			{
				Vector3 target = esp::best_target.player->get_bone_transform(48)->get_bone_position();
				//Sphere(target, 0.05, col(0.8, 0.9, 0.3, 1), 0.05f, 10.f);

				auto getammo = [&](base_projectile* held)
				{
					__try {
						if (held)
						{
							auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)held + primaryMagazine);
							if (!mag) return 0;
							return *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
						}
					}
					__except (true) {
						return 0;
					}
				};

				auto mag_ammo = getammo(held);

				if (vars->combat.manipulator && ((unity::GetKey(rust::classes::KeyCode(vars->keybinds.manipulator)))
						|| misc::manipulate_vis))
				{
					float nextshot = misc::fixed_time_last_shot + held->get_repeat_delay();
					if (misc::can_manipulate(baseplayer, target, mm_eye))
						if (nextshot < time
							&& (held->get_time_since_deploy() > held->get_deploy_delay() ||
								!strcmp(held->get_class_name(), _("BowWeapon")) ||
								!strcmp(held->get_class_name(), _("CompoundBowWeapon")) ||
								!strcmp(held->get_class_name(), _("CrossbowWeapon")))
							&& mag_ammo > 0)
						{
							auto v = esp::local_player->get_player_eyes()->get_position() + misc::best_lean;
							esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - manipulator attempted shot from position (%d, %d, %d) with desync of %d"), (int)v.x, (int)v.y, (int)v.z, (int)(settings::desyncTime * 100.f)));

							misc::manual = true;
							hk_LaunchProjectile(held);
							misc::best_target = Vector3(0, 0, 0);
							baseplayer->send_client_tick();
						}
				}

				if ((vars->combat.autoshoot || unity::GetKey(rust::classes::KeyCode(vars->keybinds.autoshoot))))
				{
					float nextshot = misc::fixed_time_last_shot + held->get_repeat_delay();
					//Sphere(target, 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
					//Sphere(baseplayer->get_bone_transform(48)->get_bone_position(), 0.05f, col(0.6, 0.6, 0.6, 1), 0.02f, 100.f);
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
				baseplayer->set_client_tick_interval(0.99f);
			else if (!is_lagging && !is_speeding)
				baseplayer->set_client_tick_interval(0.05f);


			if (!keybinds::fakelagb || unity::GetKey(keybinds::fakelagk)) {
				if (!is_lagging && !flying && vars->misc.fake_lag && !is_speeding) {
					baseplayer->set_client_tick_interval(0.4f);
					is_lagging = true;
				}
			}
			else if (is_lagging && flying || is_lagging && is_speeding) {
				esp::local_player->set_client_tick_interval(0.03f);
				is_lagging = false;
			}
			else if (is_lagging && !vars->misc.fake_lag) {
				esp::local_player->set_client_tick_interval(0.05f);
				is_lagging = false;
			}

			if (vars->misc.eyeoffset || unity::GetKey((rust::classes::KeyCode)vars->keybinds.neck))
			{
				baseplayer->get_player_eyes()->set_view_offset(Vector3(0, vars->misc.playereyes, 0));
			}

			if (auto movement = baseplayer->get_movement()) {
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
					if (auto modelstate = baseplayer->get_model_state()) {
						modelstate->set_flag(rust::classes::ModelState_Flag::OnGround);
						mem::write<float>((uint64_t)movement + 0x4C, 1); //private float <Grounded>k__BackingField; // 0x4C
					}
				}
			}

			auto item = baseplayer->get_active_weapon();


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
				auto baseprojectile = item->get_base_projectile();
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
						auto target = current.player;
						if (vars->combat.thick_bullet
							&& projectile->authoritative()
							&& projectile->IsAlive()
							&& vars->combat.thickness > 1.1f)//)
						{
							if (target.player)
							{
								auto current_position = get_position((uintptr_t)get_transform((base_player*)projectile));

								//transform* bonetrans = target.player->find_closest_bone(current_position, true
								transform* bonetrans = target.player->get_bone_transform(48);


								Vector3 target_bone = get_position((uintptr_t)bonetrans); //target_bone.y -= 0.8f;
								//Sphere(target_bone, 2.2f, col(12, 150, 100, 50), 10.f, 100.f);

								//if (misc::LineCircleIntersection(target_bone, vars->combat.thickness, current_position, projectile->previousPosition(), offset))
								//{
								//	current_position = Vector3::move_towards(target_bone, current_position, vars->combat.thickness);
								//}

								auto dist = target_bone.distance(current_position);


								//fuck with shit pussy wagon
								float num2 = 1.0f + 0.5f;
								float num8 = 2.0f / 60.0f;
								float num9 = 2.0f * max(max(get_deltaTime(), get_smoothdeltaTime()), get_fixeddeltaTime());
								float num11 = (settings::desyncTime + num8 + num9) * num2;

								//typedef Vector3(*gpv)(uintptr_t);
								//auto pv = ((gpv)(mem::game_assembly_base + 8331264))((uintptr_t)target.player);
								auto pv = GetParentVelocity(target.player);
								float mag = pv.length();
								float num15 = 0.1f + num11 * mag + 0.1f;

								esp::local_player->console_echo(string::wformat(_(L"[trap]: Fat bullet - calculated max: %d"), (int)num15));
								dist -= num15;

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
									set_position(get_transform((base_player*)projectile), newpos);


									HitTest* ht = (HitTest*)projectile->hitTest();
									ht->set_did_hit(true);
									ht->set_hit_entity(target.player);
									ht->set_hit_transform(bonetrans);
									ht->set_hit_point(InverseTransformPoint(bonetrans, newpos));
									ht->set_hit_normal(InverseTransformDirection(bonetrans, newpos));
									Ray r(get_position((uintptr_t)get_transform((base_player*)projectile)), newpos);
									safe_write(ht + 0x14, r, Ray);
									DoHit(projectile, ht, newpos, HitNormalWorld((uintptr_t)ht));
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

					if (target.player
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
						Vector3 eyes = esp::local_player->get_player_eyes()->get_position();
						Vector3 aim_dir;
						Vector3 aim_vel;

						auto m = *reinterpret_cast<uintptr_t*>((uintptr_t)baseprojectile + 0x2C0); //public BaseProjectile.Magazine primaryMagazine; // 0x2C0
						auto ammo = *reinterpret_cast<uintptr_t*>((uintptr_t)m + 0x20); //public ItemDefinition ammoType; // 0x20
						auto mod = ((networkable*)ammo)->GetComponent(unity::GetType(_(""), _("ItemModProjectile")));
						auto projectile = (Projectile*)((networkable*)mod)->GetComponent(unity::GetType(_(""), _("Projectile")));

						//auto v = projectile->initialVelocity();//((base_projectile*)projectile)->get_item_mod_projectile()->get_projectile_velocity();
						//auto v1 = ((base_projectile*)projectile)->projectileVelocityScale();
						//if (vars->combat.fast_bullet)
						//	v1 *= 1.49f;
						//v *= v1;
						auto vel = projectile->initialVelocity();
						//auto vel = (getmodifiedaimcone(0, eyes - target.pos, true)).Normalized() * v;

						//misc::get_prediction(target, eyes, target.pos, vel, aim_vel, aim_dir, (Projectile*)projectile, true);
						

						Vector3 va = baseplayer->bodyAngles();
						Vector2 vb = { va.x, va.y };
						
						auto calc = [&](const Vector3& src, const Vector3& dst) {
							Vector3 d = src - dst;
							return Vector2(RAD2DEG(Vector3::my_asin(d.y / d.length())), RAD2DEG(-Vector3::my_atan2(d.x, -d.z)));
						};
						auto normalize = [&](float& yaw, float& pitch) {
							if (pitch < -89) pitch = -89;
							else if (pitch > 89) pitch = 89;
							if (yaw < -999) yaw += 999;
							else if (yaw > 999) yaw -= 999;
							esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - yaw: %d, pitch: %d"), (int)yaw, (int)pitch));
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
						//Vector2 offset = Vector2(aim_dir.x, aim_dir.y) - vb;
						//smooth the shit
						//normalize(offset.x, offset.y);
						Vector2 ai = vb + offset;//;Vector2(aim_dir.x, aim_dir.y) + offset;
						step(ai);
						step(ai);
						normalize(ai.x, ai.y);
						Vector3 i = { ai.x, ai.y, 0.0f };
						baseplayer->set_bodyAngles(i);
					}

					if (vars->misc.silent_farm) {
						auto entity = baseplayer->resolve_closest_entity(3, false);
						if (entity.first.found && entity.first.player) {
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
								if (baseprojectile->get_time_since_deploy() > baseprojectile->get_deploy_delay() && baseprojectile->get_next_attack_time() <= get_time()) {
									if (time > nextActionTime) {
										nextActionTime = time + period;
										unity::ServerRPC((uintptr_t)baseprojectile, rust::classes::string(_(L"UseSelf")));
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
									mem::write<float>((uint64_t)baseprojectile + 0x378, 1.f); //eoka success fraction
									mem::write<bool>((uint64_t)baseprojectile + 0x388, true); //eoka _didSparkThisFrame
									break;
								default:
									if (vars->combat.fast_bullet)
										if (item_id != 1318558775)
											baseprojectile->SetProjectileVelocityScale(1.49f);
									if (vars->combat.rapidfire)
										baseprojectile->set_repeat_delay(0.02f);
									if (vars->combat.automatic)
										baseprojectile->is_automatic() = true;
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

				if (target.player)
				{
					esp::local_player->console_echo(string::wformat(_(L"[trap]: ClientInput - sending RPC_Assist to player %s"), target.player->get_player_name()));

					if (!target.is_heli && target.player && target.distance <= 5 && target.player->get_health() <= 4 && target.visible)
						unity::ServerRPC((uintptr_t)target.player, rust::classes::string(_(L"RPC_Assist")));
				}
			}

			if (vars->misc.gesture_spam != 0
				&& vars->misc.gesture_spam != 1
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
		}

		orig::baseplayer_client_input(baseplayer, state);

		auto model_state = baseplayer->get_model_state();

		//model_state->set_water_level(99999);


		if (vars->misc.spinbot) {
			state->set_aim_angles(Vector3(100, my_rand() % 999 + -999, 100));
		}


		if (vars->misc.autofarm) {
			if (misc::node.pos != Vector3(0, 0, 0))
			{
				auto dir = (misc::node.pos - baseplayer->get_player_eyes()->get_position()).Normalized();
				state->set_aim_angles(dir);
			}
		}
	}
}
