#pragma once
#include "vars.hpp"
Vars* vars = new Vars();

#define M_PI 3.14159265358979323846f
#define M_PI_2 1.57079632679489661923
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
namespace settings {
	float desyncTime = 0.0f;
	float time_since_last_shot = 0.0f;
	float hor_flyhack = 0.f;
	float vert_flyhack = 0.f;

	namespace keybind {
	}

	namespace visuals {

	}

	namespace misc {

	}
}