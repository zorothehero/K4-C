#pragma once
#include "../rust/unity.hpp"
#include "../rust/features/player_esp.hpp"
#include "../settings.hpp"
#include "../utils/string_format.h"

inline float NormalizeAngle(float angle) {
	while (angle > 360.0f) {
		angle -= 360.0f;
	}
	while (angle < 0.0f) {
		angle += 360.0f;
	}
	return angle;
}

inline Vector3 NormalizeAngles(Vector3 angles) {
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

inline Vector3 EulerAngles(Vector4 q1) {
	float num = q1.w * q1.w;
	float num2 = q1.x * q1.x;
	float num3 = q1.y * q1.y;
	float num4 = q1.z * q1.z;
	float num5 = num2 + num3 + num4 + num;
	float num6 = q1.x * q1.w - q1.y * q1.z;
	Vector3 vector;
	if (num6 > 0.4995f * num5) {
		vector.y = 2.0f * std::atan2f(q1.y, q1.x);
		vector.x = 1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	if (num6 < -0.4995f * num5) {
		vector.y = -2.0f * std::atan2f(q1.y, q1.x);
		vector.x = -1.57079637f;
		vector.z = 0.0f;
		return NormalizeAngles(vector * 57.2958f);
	}
	Vector4 quaternion = Vector4(q1.w, q1.z, q1.x, q1.y);
	vector.y = std::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	vector.x = std::asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
	vector.z = std::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
	return NormalizeAngles(vector * 57.2958f);
}

#define rgba(r,g,b,a) gui::Color(r / 255.f, g / 255.f, b / 255.f, a)

namespace gui {
	class Color {
	public:
		float r;
		float g;
		float b;
		float a;
		Color(float rr, float gg, float bb, float aa) {
			r = rr;
			g = gg;
			b = bb;
			a = aa;
		}
	};

	namespace methods {
		static auto get_whiteTexture = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Texture2D"), _("get_whiteTexture"), 0, _(""), _("UnityEngine"))));

		static auto get_skin = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("get_skin"), 0, _(""), _("UnityEngine"))));

		static auto set_fontSize = reinterpret_cast<void(*)(uintptr_t label, int size)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIStyle"), _("set_fontSize"), -1, _(""), _("UnityEngine"))));

		static auto set_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("set_color"), -1, _(""), _("UnityEngine"))));

		static auto Label = reinterpret_cast<void(*)(rust::classes::Rect position, uintptr_t content, uintptr_t style)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 3, _("content"), _("UnityEngine"), 2)));

		static auto _Label = reinterpret_cast<void(*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 2, _("text"), _("UnityEngine"), 2)));
		static auto ptr_Label = reinterpret_cast<void(*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 2, _("text"), _("UnityEngine"), 2)));

		static auto set_alignment = reinterpret_cast<void(*)(uintptr_t label, uintptr_t value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIStyle"), _("set_alignment"), -1, _(""), _("UnityEngine"))));

		static auto get_current = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_current"), 0, _(""), _("UnityEngine"))));

		static auto gui_content_temp = reinterpret_cast<uintptr_t(*)(rust::classes::string*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIContent"), _("Temp"), 1, _("t"), _("UnityEngine"), 1)));

		static auto gui_content_temp_ptr = reinterpret_cast<uintptr_t(*)(uintptr_t*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIContent"), _("Temp"), 1, _("t"), _("UnityEngine"), 1)));

		static auto set_skin = reinterpret_cast<void(*)(uintptr_t skin)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("set_skin"), 0, _(""), _("UnityEngine"))));

		static auto get_type = reinterpret_cast<rust::classes::EventType(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_type"), 0, _(""), _("UnityEngine"))));

		static auto DrawTexture = reinterpret_cast<void (*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("DrawTexture"), 2, _("image"), _("UnityEngine"), 2)));
		
		//Rect position, Texture image, ScaleMode scaleMode, bool alphaBlend, float imageAspect, Color color, float borderWidth, float borderRadius
		static auto Box = reinterpret_cast<void (*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Box"), 2, _("text"), _("UnityEngine"), 2)));

		static auto DrawLine = reinterpret_cast<void (*)(Vector3, Vector3, gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Debug"), _("DrawLine"), 3, _("color"), _("UnityEngine"), 3)));

		static auto set_gizmos_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Gizmos"), _("set_color"), -1, _(""), _("UnityEngine"))));

		static auto HorizontalSlider = reinterpret_cast<float(*)(rust::classes::Rect position, float value, float leftValue, float rightValue)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("HorizontalSlider"), 4, _(""), _("UnityEngine"))));
		
		static auto get_activemodel = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseViewModel"), _("get_ActiveModel"), 0, _(""), _(""))));
		


		//gl stuff?

		static auto Vertex = reinterpret_cast<void(*)(Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Vertex"), 0, _(""), _("UnityEngine"))));

		static auto Begin = reinterpret_cast<void(*)(int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Begin"), 0, _(""), _("UnityEngine"))));

		static auto End = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("End"), 0, _(""), _("UnityEngine"))));

		static auto Color = reinterpret_cast<void(*)(col)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Color"), 0, _(""), _("UnityEngine"))));
		
		static auto PushMatrix = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("PushMatrix"), 0, _(""), _("UnityEngine"))));

		static auto PopMatrix = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("PopMatrix"), 0, _(""), _("UnityEngine"))));
		
		static auto dont_destroy_on_load = reinterpret_cast<void(*)(uintptr_t target)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("DontDestroyOnLoad"), 0, _(""), _("UnityEngine"))));
		
		static auto create = reinterpret_cast<void(*)(uintptr_t self, rust::classes::string shader)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("Internal_CreateGameObject"), 0, _(""), _("UnityEngine"))));
		
		static auto add_component = reinterpret_cast<void(*)(uintptr_t self, uintptr_t componentType)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("Internal_AddComponentWithType"), 0, _(""), _("UnityEngine"))));

		//static auto name = reinterpret_cast<void(*)( )>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_(""), _(""), 0, _(""), _(""))));
	}

	uintptr_t white_texture;

	void init_gui() {
		methods::ptr_Label = reinterpret_cast<void(*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 2, _("text"), _("UnityEngine"), 2)));

		methods::gui_content_temp_ptr = reinterpret_cast<uintptr_t(*)(uintptr_t*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIContent"), _("Temp"), 1, _("t"), _("UnityEngine"), 1)));

		methods::HorizontalSlider = reinterpret_cast<float(*)(rust::classes::Rect position, float value, float leftValue, float rightValue)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("HorizontalSlider"), 4, _(""), _("UnityEngine"))));

		methods::get_whiteTexture = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Texture2D"), _("get_whiteTexture"), 0, _(""), _("UnityEngine"))));

		methods::get_skin = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("get_skin"), 0, _(""), _("UnityEngine"))));

		methods::set_fontSize = reinterpret_cast<void(*)(uintptr_t label, int size)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIStyle"), _("set_fontSize"), -1, _(""), _("UnityEngine"))));

		methods::set_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("set_color"), -1, _(""), _("UnityEngine"))));

		methods::Label = reinterpret_cast<void(*)(rust::classes::Rect position, uintptr_t content, uintptr_t style)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 3, _("content"), _("UnityEngine"), 2)));

		methods::_Label = reinterpret_cast<void(*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Label"), 2, _("text"), _("UnityEngine"), 2)));

		methods::set_alignment = reinterpret_cast<void(*)(uintptr_t label, uintptr_t value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIStyle"), _("set_alignment"), -1, _(""), _("UnityEngine"))));

		methods::get_current = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_current"), 0, _(""), _("UnityEngine"))));

		methods::gui_content_temp = reinterpret_cast<uintptr_t(*)(rust::classes::string*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUIContent"), _("Temp"), 1, _("t"), _("UnityEngine"), 1)));

		methods::set_skin = reinterpret_cast<void(*)(uintptr_t skin)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("set_skin"), 0, _(""), _("UnityEngine"))));

		methods::get_type = reinterpret_cast<rust::classes::EventType(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Event"), _("get_type"), 0, _(""), _("UnityEngine"))));

		unity::LoadAllAssets = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAllAssets"), 1, _("type"), _("UnityEngine"), 1)));

		unity::LoadFromFile = reinterpret_cast<uintptr_t(*)(rust::classes::string path)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile"), 1, _("path"), _("UnityEngine"), 1)));

		unity::LoadAsset = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, rust::classes::string path, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset"), 2, _("name"), _("UnityEngine"), 1)));

		methods::DrawTexture = reinterpret_cast<void (*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("DrawTexture"), 2, _("image"), _("UnityEngine"), 2)));

		methods::Box = reinterpret_cast<void (*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Box"), 2, _("text"), _("UnityEngine"), 2)));

		methods::DrawLine = reinterpret_cast<void (*)(Vector3, Vector3, gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Debug"), _("DrawLine"), 3, _("color"), _("UnityEngine"), 3)));

		methods::set_gizmos_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Gizmos"), _("set_color"), -1, _(""), _("UnityEngine"))));

		methods::get_activemodel = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BaseViewModel"), _("get_ActiveModel"), 0, _(""), _(""))));

		methods::Vertex = reinterpret_cast<void(*)(Vector3)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Vertex"), 0, _(""), _("UnityEngine"))));

		methods::Begin = reinterpret_cast<void(*)(int)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Begin"), 0, _(""), _("UnityEngine"))));

		methods::End = reinterpret_cast<void(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("End"), 0, _(""), _("UnityEngine"))));

		methods::Color = reinterpret_cast<void(*)(col)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GL"), _("Color"), 0, _(""), _("UnityEngine"))));
		//methods::dont_destroy_on_load = reinterpret_cast<void(*)(uintptr_t target)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Object"), _("DontDestroyOnLoad"), 0, _(""), _("UnityEngine"))));
		//
		//methods::create = reinterpret_cast<void(*)(uintptr_t self, rust::classes::string shader)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("InternalCreateGameObject"), 0, _(""), _("UnityEngine"))));
		//
		//methods::add_component = reinterpret_cast<void(*)(uintptr_t self, uintptr_t componentType)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GameObject"), _("InternalAddComponentWithType"), 0, _(""), _("UnityEngine"))));

		//set font????????????

		white_texture = methods::get_whiteTexture();
	}

	uintptr_t label, skin;
	bool open;
	bool InsertPressed;
	float opacity = 0.f;
	float tick_time_when_called;

	const wchar_t* get_keystr(int key) {
		switch (key)
		{
		case 0:
			return _(L"none");
		case 8:
			return _(L"backspace");
		case 127:
			return _(L"delete");
		case 9:
			return _(L"tab");
		case 12:
			return _(L"clear");
		case 13:
			return _(L"return");
		case 19:
			return _(L"pause");
		case 27:
			return _(L"none");
		case 32:
			return _(L"space");
		case 256:
			return _(L"0");
		case 257:
			return _(L"1");
		case 258:
			return _(L"2");
		case 259:
			return _(L"3");
		case 260:
			return _(L"4");
		case 261:
			return _(L"5");
		case 262:
			return _(L"6");
		case 263:
			return _(L"7");
		case 264:
			return _(L"8");
		case 265:
			return _(L"9");
		case 266:
			return _(L".");
		case 267:
			return _(L"/");
		case 268:
			return _(L"*");
		case 269:
			return _(L"+");
		case 270:
			return _(L"-");
		case 271:
			return _(L"enter");
		case 272:
			return _(L"equals");
		case 273:
			return _(L"up");
		case 274:
			return _(L"down");
		case 275:
			return _(L"right");
		case 276:
			return _(L"left");
		case 277:
			return _(L"ins");
		case 278:
			return _(L"home");
		case 279:
			return _(L"end");
		case 280:
			return _(L"pageup");
		case 281:
			return _(L"pagedown");
		case 282:
			return _(L"f1");
		case 283:
			return _(L"f2");
		case 284:
			return _(L"f3");
		case 285:
			return _(L"f4");
		case 286:
			return _(L"f5");
		case 287:
			return _(L"f6");
		case 288:
			return _(L"f7");
		case 289:
			return _(L"f8");
		case 290:
			return _(L"f9");
		case 291:
			return _(L"f10");
		case 292:
			return _(L"f11");
		case 293:
			return _(L"f12");
		case 294:
			return _(L"f13");
		case 295:
			return _(L"f14");
		case 296:
			return _(L"f15");
		case 48:
			return _(L"0");
		case 49:
			return _(L"1");
		case 50:
			return _(L"2");
		case 51:
			return _(L"3");
		case 52:
			return _(L"4");
		case 53:
			return _(L"5");
		case 54:
			return _(L"6");
		case 55:
			return _(L"7");
		case 56:
			return _(L"8");
		case 57:
			return _(L"9");
		case 33:
			return _(L"!");
		case 34:
			return _(L"\"");
		case 35:
			return _(L"#");
		case 36:
			return _(L"$");
		case 37:
			return _(L"%");
		case 38:
			return _(L"&");
		case 39:
			return _(L"'");
		case 40:
			return _(L"(");
		case 41:
			return _(L")");
		case 42:
			return _(L"*");
		case 43:
			return _(L"+");
		case 44:
			return _(L",");
		case 45:
			return _(L"-");
		case 46:
			return _(L".");
		case 47:
			return _(L"/");
		case 58:
			return _(L":");
		case 59:
			return _(L";");
		case 60:
			return _(L"<");
		case 61:
			return _(L"=");
		case 62:
			return _(L">");
		case 63:
			return _(L"?");
		case 64:
			return _(L"@");
		case 91:
			return _(L"[");
		case 92:
			return _(L"\\");
		case 93:
			return _(L"]");
		case 94:
			return _(L"^");
		case 95:
			return _(L"_");
		case 96:
			return _(L"`");
		case 97:
			return _(L"a");
		case 98:
			return _(L"b");
		case 99:
			return _(L"c");
		case 100:
			return _(L"d");
		case 101:
			return _(L"e");
		case 102:
			return _(L"f");
		case 103:
			return _(L"g");
		case 104:
			return _(L"h");
		case 105:
			return _(L"i");
		case 106:
			return _(L"j");
		case 107:
			return _(L"k");
		case 108:
			return _(L"l");
		case 109:
			return _(L"m");
		case 110:
			return _(L"n");
		case 111:
			return _(L"o");
		case 112:
			return _(L"p");
		case 113:
			return _(L"q");
		case 114:
			return _(L"r");
		case 115:
			return _(L"s");
		case 116:
			return _(L"t");
		case 117:
			return _(L"u");
		case 118:
			return _(L"v");
		case 119:
			return _(L"w");
		case 120:
			return _(L"x");
		case 121:
			return _(L"y");
		case 122:
			return _(L"z");
		case 123:
			return _(L"{");
		case 124:
			return _(L"|");
		case 125:
			return _(L"}");
		case 126:
			return _(L"~");
		case 300:
			return _(L"numlk");
		case 301:
			return _(L"caps");
		case 302:
			return _(L"scrl");
		case 303:
			return _(L"rshift");
		case 304:
			return _(L"lshift");
		case 305:
			return _(L"rctrl");
		case 306:
			return _(L"lctrl");
		case 307:
			return _(L"ralt");
		case 308:
			return _(L"lalt");
		case 310:
			return _(L"lcmd");
		case 311:
			return _(L"lwin");
		case 309:
			return _(L"rcmd");
		case 312:
			return _(L"rwin");
		case 313:
			return _(L"altgr");
		case 315:
			return _(L"help");
		case 316:
			return _(L"pr");
		case 317:
			return _(L"sysreq");
		case 318:
			return _(L"break");
		case 319:
			return _(L"menu");
		case 323:
			return _(L"m0");
		case 324:
			return _(L"m1");
		case 325:
			return _(L"m2");
		case 326:
			return _(L"m3");
		case 327:
			return _(L"m4");
		case 328:
			return _(L"m5");
		case 329:
			return _(L"m");
		}
		return _(L"undefined");
	}

	void outline_box(Vector2 pos, Vector2 size, Color clr)
	{
		methods::set_color(clr);

		methods::DrawTexture(rust::classes::Rect(pos.x, pos.y, 1, size.y), white_texture);
		methods::DrawTexture(rust::classes::Rect(pos.x + size.x, pos.y, 1, size.y), white_texture);
		methods::DrawTexture(rust::classes::Rect(pos.x, pos.y, size.x, 1), white_texture);
		methods::DrawTexture(rust::classes::Rect(pos.x, pos.y + size.y, size.x, 1), white_texture);
	}

	void horizontal_line(Vector2 pos, float size, Color clr)
	{
		methods::set_color(clr);

		methods::DrawTexture(rust::classes::Rect(pos.x, pos.y, size, 1), white_texture);
	}


	void line(Vector2 start, Vector2 end, Color clr, float thickness = 1.f, bool outline = false)
	{
		col c = col(clr.r, clr.g, clr.b, clr.a);
		gui::methods::PushMatrix();
		gui::methods::Begin(1);
		gui::methods::Color(c);

		gui::methods::Color({ 0,0,0,255 });
		gui::methods::Vertex(Vector3(start.x - thickness, start.y, 0));
		gui::methods::Vertex(Vector3(end.x + thickness, end.y, 0));
		gui::methods::Color(c);
		gui::methods::Vertex(Vector3(start.x, start.y, 0));
		gui::methods::Vertex(Vector3(end.x, end.y, 0));

		gui::methods::End();
		gui::methods::PopMatrix();
		return;
	}

	void circle(Vector2 o, float r, col clr, bool filled = false) {
		gui::methods::Begin(1.5);
		gui::methods::Color(clr);
		for (float num = 0.f; num < 6.2831855f; num += 0.05f)
		{
			gui::methods::Vertex(Vector3(cos(num) * r + o.x, sin(num) * r + o.y, 0));
			gui::methods::Vertex(Vector3(cos(num + 0.05f) * r + o.x, sin(num + 0.05f) * r + o.y, 0));
		}
		gui::methods::End();
	}

	void vertical_line(Vector2 pos, float size, Color clr)
	{
		methods::set_color(clr);

		methods::DrawTexture(rust::classes::Rect(pos.x, pos.y, 1, size), white_texture);
	}

	void fill_box(rust::classes::Rect pos, Color clr)
	{
		methods::set_color(clr);
		methods::DrawTexture(pos, white_texture);
	}


	void init() {
		if (label && skin)
			return;

		skin = methods::get_skin();
		label = mem::read<uintptr_t>(skin + 0x38);

		unity::bundle = unity::LoadFromFile(_(L"rust.assets"));
		//unity::galaxy_bundle = unity::LoadFromFile(_(L"galaxy.chams"));
		unity::bundle_font = unity::LoadFromFile(_(L"font.assets"));

		const auto set_font = [&](rust::classes::string font_name, int size) {
			static auto font = unity::LoadAsset(unity::bundle_font, font_name, il2cpp::type_object("UnityEngine", "Font"));
			*reinterpret_cast<std::uintptr_t*>(skin + 0x18) = font; // lol.
			methods::set_fontSize(label, size);
		};

		//static auto font = methods::LoadAsset(unity::bundle_font, rust::classes::string(_(L"minecraftchmc.ttf")), il2cpp::type_object(_("UnityEngine"), _("Font")));
		//*reinterpret_cast<uintptr_t*>(skin + 0x18) = font;

		//methods::set_fontSize(label, 24);
		set_font(_(L"tahoma.ttf"), 14);

		methods::set_alignment(label, 0);
		methods::set_color(Color(1, 1, 1, 1));
	}

	void Label(rust::classes::Rect pos, rust::classes::string text, Color clr, bool centered = false, float size = 12) {
		methods::set_color(clr);

		uintptr_t content = methods::gui_content_temp(&text);

		methods::set_fontSize(label, size);          //prepare style	

		if (centered)
			methods::set_alignment(label, 0x4);
		else
			methods::set_alignment(label, 0x0);

		methods::Label(pos, content, label);
	}

	void Label(rust::classes::Rect pos, uintptr_t text, Color clr, bool centered = false, float size = 12) {
		methods::set_color(clr);

		methods::set_fontSize(label, size);

		methods::ptr_Label(pos, text);
	}

	void Label(rust::classes::Rect pos, rust::classes::string text, float font_size = 0) {

		if (!font_size)
			methods::_Label(pos, text);
		else {
			uintptr_t content = methods::gui_content_temp(&text);

			methods::set_fontSize(label, font_size);          //prepare style	

			methods::Label(pos, content, label);
		}
	}

	int active_tab = 0;
	Vector2 tab_size;

	Color perc_col(float Num, float alpha = 1.0f)
	{
		float red, green, blue;
		if (Num < 0.5)
		{
			red = Num * 2.f * 255.f;
			green = 255.f;
			blue = 0.f;
		}
		else
		{
			red = 255.f;
			green = (2.f - 2.f * Num) * 255.f;
			blue = 0.f;
		}

		red -= 100;
		green -= 100;
		blue -= 100;
		return Color(red / 255, green / 255, blue / 255, alpha);
	}


	int last_active_id = 0;

	void tab(rust::classes::EventType event, Vector2 pos, Vector2 mouse, const wchar_t* tab_name, int id) {
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + 2, pos.y - 4 + id * tab_size.y + 2.0f, tab_size.x, tab_size.y).Contains(mouse)) {
				last_active_id = active_tab;
				active_tab = id;
				opacity = 0.0f;
			}
		}
		else if (event == rust::classes::EventType::Repaint) {
			if (active_tab == id) {
				float o = (opacity / 255.f);
				fill_box(rust::classes::Rect(pos.x, pos.y + id * tab_size.y, tab_size.x + 2, tab_size.y), rgba(21.f, 27.f, 37.f, o));
			}
			else if (active_tab == last_active_id) {
				float o = ((255.f - opacity) / 255.f);
				fill_box(rust::classes::Rect(pos.x, pos.y + id * tab_size.y, tab_size.x + 2, tab_size.y), rgba(21.f, 27.f, 37.f, o));
			}

			Label(rust::classes::Rect{ pos.x + 2, pos.y + 1 + id * tab_size.y + 1, tab_size.x, tab_size.y }, tab_name, rgba(0, 0, 0, 255.f), true, 12);
			Label(rust::classes::Rect{ pos.x + 2, pos.y + id * tab_size.y, tab_size.x, tab_size.y }, tab_name, rgba(159.f, 163.f, 169.f, 255.f), true, 12);
		}
	}

	const wchar_t* keybind_str;
	int* kbref = 0;
	int* ref_clicked = 0;
	bool getting_keybind = false;
	bool combo_clicked = false;
	bool true_placehold = true;
	bool false_placehold = false;
	std::wstring* pinputtext;
	bool _ti = false;
	bool inputting_text = false;

	bool button(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, wchar_t* name) {
		pos.x += 5;
		current_pos.y += 5;
		rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 40, 14);
		fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));
		if (poz.Contains(mouse))
		{
			rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 40, 14);
			fill_box(poz, rgba(39, 47, 59, 255.f));
		}
		if (event == rust::classes::EventType::MouseDown) {
			if (poz.Contains(mouse)) {
				rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 40, 14);
				fill_box(poz, rgba(249.f, 130.f, 109.f, 255.f));
				return true;
			}
		}

		gui::Label({ poz.x , poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), true, 10);
		current_pos.y += 15;
		return false;
	}

	void textbox(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, wchar_t* name, std::wstring* str) {

		pos.x += 5;

		rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));
		if (poz.Contains(mouse))
		{
			rust::classes::Rect t = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + 18, 150, 2);
			fill_box(t, rgba(159.f, 163.f, 169.f, 255.f));
		}
		if (event == rust::classes::EventType::MouseDown) {
			if (poz.Contains(mouse))
				inputting_text = !inputting_text;
			else inputting_text = false;
		}

		
		gui::Label({ poz.x + 4, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 10);

		if(inputting_text)
		{
			rust::classes::Rect t = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + 18, 150, 2);
			fill_box(t, rgba(249.f, 130.f, 109.f, 255.f));
			pinputtext = str;
			gui::Label({ poz.x + 44, poz.y, poz.wid, poz.hei }, rust::classes::string(str->c_str()), rgba(249.f, 130.f, 109.f, (opacity / 255.f)), false, 10);
		}
		else
			gui::Label({ poz.x + 44, poz.y, poz.wid, poz.hei }, rust::classes::string(str->c_str()), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 10);
		//draw label of current_text
		current_pos.y += 20;
	}

	void combobox(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* name, std::array<wchar_t*, 8> combo_str, std::array<bool*, 8> combo) {
		pos.x += 10;
		rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));

		if (poz.Contains(mouse))
		{
			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + 18, 150, 2);
			fill_box(poz, rgba(181, 140, 132, (opacity / 255.f)));
			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		}

		gui::Label({ poz.x + 5, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 13);

		if (combo_clicked)
		{
			gui::line({ poz.x + 130, poz.y + 13 }, { poz.x + 135, poz.y + 8 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
			gui::line({ poz.x + 140, poz.y + 13 }, { poz.x + 135, poz.y + 8 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));

			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + 18, 150, 2);
			fill_box(poz, rgba(249.f, 130.f, 109.f, (opacity / 255.f)));
			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		}
		else {
			gui::line({ poz.x + 130, poz.y + 8 }, { poz.x + 135, poz.y + 13 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
			gui::line({ poz.x + 140, poz.y + 8 }, { poz.x + 135, poz.y + 13 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
		}

		if (event == rust::classes::EventType::MouseDown) 
		{
			if (poz.Contains(mouse))
				combo_clicked = !combo_clicked;
			else
			{
				bool clicked_inside = false;
				if (combo_clicked)
				{
					for (size_t i = 1; i < 8; i++)
					{
						poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + (i * 20), 150, 15);
						if (poz.Contains(mouse))
						{
							if (&combo[i])
							{
								*combo[i] = !*combo[i];
								clicked_inside = true;
							}
						}
					}
				}
				if(clicked_inside == false)
					combo_clicked = false;
			}
		}
		if (combo_clicked)
		{
			for (size_t i = 1; i < 8; i++)
			{
				poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + (i * 20), 150, 20);
				fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));

				auto name = combo_str[i];

				gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), true, 10);

				bool s = *combo[i];
				if (s)
					gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(249.f, 130.f, 109.f, (opacity / 255.f)), true, 10);

				if (poz.Contains(mouse))
					gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(181, 140, 132, (opacity / 255.f)), true, 10);
			}
		}
		current_pos.y += 30;
	}

	int* list_open = 0;
	bool list_clicked = false;
	void listbox(rust::classes::EventType event,
		Vector2 pos,
		Vector2& current_pos,
		Vector2 mouse,
		const wchar_t* button_name,
		std::array<wchar_t*, 13> str_list,
		int* selected = 0) 
	{
		pos.x += 10;
		rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));

		auto sz = sizeof(str_list) / sizeof(str_list[0]);

		gui::Label({ poz.x + 5, poz.y, poz.wid, poz.hei }, rust::classes::string(string::wformat(_(L"%s: %s"), button_name, str_list[*selected])), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 13);

		if (list_clicked && list_open == selected)
		{
			gui::line({ poz.x + 130, poz.y + 13 }, { poz.x + 135, poz.y + 8 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
			gui::line({ poz.x + 140, poz.y + 13 }, { poz.x + 135, poz.y + 8 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));

			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + 18, 150, 2);
			fill_box(poz, rgba(249.f, 130.f, 109.f, (opacity / 255.f)));
			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
		}
		else
		{
			gui::line({ poz.x + 130, poz.y + 8 }, { poz.x + 135, poz.y + 13 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
			gui::line({ poz.x + 140, poz.y + 8 }, { poz.x + 135, poz.y + 13 }, rgba(159.f, 163.f, 169.f, (opacity / 255.f)));
		}


		if (event == rust::classes::EventType::MouseDown)
		{
			poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y, 150, 20);
			if (poz.Contains(mouse)) {
				list_clicked = !list_clicked;
				if (list_open != selected)
					list_open = selected;
			}
			if (list_clicked && list_open == selected)
			{
				for (size_t i = 1; i < sz; i++)
				{
					if (str_list[i][0] == '\x00') continue;
					poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + (i * 20), 150, 15);
					if (poz.Contains(mouse))
						if (str_list[i])
							*selected = i;
				}
			}
		}

		if (list_clicked && list_open == selected) {
			for (size_t i = 1; i < sz; i++)
			{
				if (str_list[i][0] == '\x00') continue;
				poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + (i * 20), 150, 20);

				fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));

				auto name = str_list[i];

				gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), true, 10);

				if (*selected > 8)
					*selected = 0;
				bool s = LI_FIND(wcscmp)(str_list[*selected], str_list[i]) == 0;
				if (s)
					gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(249.f, 130.f, 109.f, (opacity / 255.f)), true, 10);

				if (poz.Contains(mouse))
				{
					poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f + 2, pos.y + current_pos.y + (i * 20) + 2, 146, 16);
					fill_box(poz, rgba(22, 27, 36, 255.f));
					poz = rust::classes::Rect(pos.x + tab_size.x + 2.0f, pos.y + current_pos.y + (i * 20), 150, 20);
					gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(name), rgba(181, 140, 132, (opacity / 255.f)), true, 10);
				}
			}
		}

		current_pos.y += 30;
	}

	void checkbox(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* checked_ref, int id, bool keybind = false, int* keybind_ref = 0, Color col = Color(255, 255, 255, 220)) {

		pos.x += 5;
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown && !combo_clicked && !list_clicked) {
			if (rust::classes::Rect(pos.x + tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4 + 3 + 2.0f, 100, button_size + 3).Contains(mouse)) {
				*checked_ref = !*checked_ref;
			}
		}

		if (keybind)
		{
			rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 100 + 2.0f, pos.y + current_pos.y, 31, 15);
			fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));
			if (event == rust::classes::EventType::MouseDown && !combo_clicked && !list_clicked) {
				if (poz.Contains(mouse)) {
					getting_keybind = !getting_keybind;
					if (getting_keybind)
					{
						ref_clicked = keybind_ref;
						kbref = keybind_ref;
					}
				}
			}
			if (getting_keybind && keybind_ref == ref_clicked)
			{
				fill_box(rust::classes::Rect(poz.x, poz.y + 14.f, poz.wid, 2.f), rgba(249.f, 130.f, 109.f, (opacity / 255.f)));
				gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(get_keystr(*keybind_ref)), rgba(249.f, 130.f, 109.f, (opacity / 255.f)), true, 10);
			}

			gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, rust::classes::string(get_keystr(*keybind_ref)), rgba(159.f, 163.f, 169.f, (opacity / 255.f)), true, 10);
		}

		float o1 = (opacity / 255.f);
		//outline_box(Vector2(pos.x + tab_size.x + 3 + 2.0f, pos.y + 7 + current_pos.y - 4), Vector2(10, 10), rgba(14.f, 18.f, 24.f, o1));
		//outline_box(Vector2(pos.x + 2 + tab_size.x + 3 + 2.0f, pos.y + 10 + current_pos.y - 5), Vector2(7, 7), rgba(249.f, 130.f, 109.f, o1));
		fill_box(rust::classes::Rect{ pos.x + 3 + tab_size.x + 3 + 2.0f, pos.y + 10 + current_pos.y - 4, 5, 5 }, rgba(14.f, 18.f, 24.f, (opacity / 255.f)));

		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + 15 + tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, rgba(0, 0, 0, (opacity / 255.f)), false, 14);
			if (*checked_ref) {
				//fill_box(rust::classes::Rect{ pos.x + tab_size.x + 3 + 2.0f, pos.y + 7 + current_pos.y - 4, 10, 10 }, rgba(14.f, 18.f, 24.f, (opacity / 255.f)));
				fill_box(rust::classes::Rect{ pos.x + 3 + tab_size.x + 3 + 2.0f, pos.y + 10 + current_pos.y - 4, 5, 5 }, rgba(249.f, 130.f, 109.f, (opacity / 255.f)));
				gui::Label(rust::classes::Rect{ pos.x + 15 + tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, rgba(249.f, 130.f, 109.f, (opacity / 255.f)), false, 14);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + 15 + tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 14);


			//rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 100 + 2.0f, pos.y + current_pos.y - 4 + 3 + 2.0f, 23, button_size + 3);
			//fill_box(poz, rgba(14.f, 18.f, 24.f, (opacity / 255.f)));
			//gui::Label(poz, button_name, rgba(159.f, 163.f, 169.f, (opacity / 255.f)), false, 14);

		}
		current_pos.y += button_size;
	}

	void OnKeyUp(rust::classes::KeyCode key) {
		if (key == rust::classes::KeyCode::Insert) {
			InsertPressed = false;
		}
	}

	void OnKeyDown(rust::classes::KeyCode key) {
		if (!InsertPressed && key == rust::classes::KeyCode::Insert) {
			InsertPressed = true;
			open = !open;
			if (!open) getting_keybind = false;
		}

		if (getting_keybind && (int)(key) != 0)
		{
			*kbref = (int)(key);
			getting_keybind = false;
			//keybind_map[keybind_str] = key;
		}
		if (inputting_text)
		{
			auto og = *pinputtext;

			auto keystr = get_keystr((int)key);
			if (((int)key >= 97 && (int)key <= 122) || (int)key == 8)
			{
				std::wstring new_text = og;

				if (!wcscmp(keystr, _(L"backspace"))
					|| (int)key == 8) //backspace
					new_text = new_text.substr(0, new_text.size() - 1);
				else if (pinputtext->size() < 16)
				{
					if (!wcscmp(keystr, _(L"space"))) //spacebar
						new_text.append(_(L" "));
					else if (wcscmp(keystr, _(L"none"))) //none
						new_text.append(keystr);
				}
				*pinputtext = new_text;
			}
		}
	}

	void buttonvis(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void buttoninv(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void buttonteam(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(vars->visual.TeamRcolor, vars->visual.TeamGcolor, vars->visual.TeamBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.TeamRcolor, vars->visual.TeamGcolor, vars->visual.TeamBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(vars->visual.TeamRcolor, vars->visual.TeamGcolor, vars->visual.TeamBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void Slider(rust::classes::EventType event, Vector2 pos, Vector2 mouse, uintptr_t text, Vector2& current_pos, float& out, float max, int id, float font_size = 0, const char* fmt = _("%.1f"))
	{
		pos.x += 100;
		pos.y += 9;
		const float button_size = 8;

		int wid = 150;

		int pzx = pos.x + id + 3 + 2.0f + 1;

		rust::classes::Rect pz = rust::classes::Rect(pzx, pos.y + current_pos.y - 4 + 1, wid, button_size);

		//if mouse within box highlight thumb
		//if mouse down within box, set thumb to position

		if (event == rust::classes::EventType::MouseDown) {
			if (pz.Contains(mouse)) {
				out = (((pos.x + 7) - mouse.x) * (max / wid)) * -1;
			}
		}

		float val = -((wid - 1) * (out / max));
		if (event == rust::classes::EventType::Repaint) {
			fill_box(pz, rgba(14.f, 18.f, 24.f, (opacity / 255.f)));
			if (val < 0) val = val * -1;
			rust::classes::Rect pzf = rust::classes::Rect(pz.x + 2, pz.y + 2, val, 4);
			fill_box(pzf, rgba(249.f, 130.f, 109.f, (opacity / 255.f)));
		}


		//out = gui::methods::HorizontalSlider(pz, out, value.x, value.y);

		//slider label
		gui::Label(rust::classes::Rect{ pos.x + id + 3 + 2.0f + 6, pos.y + current_pos.y - 3 - 10, 200, 16 }, text, gui::Color(0, 0, 0, (opacity / 255.f) > 120 ? 120 : opacity), false, 10);
		gui::Label(rust::classes::Rect{ pos.x + id + 3 + 2.0f + 5, pos.y + current_pos.y - 4 - 10, 200, 16 }, text, Color(255, 255, 255, (opacity / 255.f)), false, 10);

		auto nstr = il2cpp::methods::new_string(string::format(fmt, out));
		//slider value
		gui::Label(rust::classes::Rect{ pos.x + id + val, pos.y + current_pos.y - 3, 200, 16 }, nstr, gui::Color(0, 0, 0, (opacity / 255.f) > 120 ? 120 : opacity), false, 8);
		gui::Label(rust::classes::Rect{ pos.x + id + val, pos.y + current_pos.y - 4, 200, 16 }, nstr, Color(255, 255, 255, (opacity / 255.f)), false, 8);

		current_pos.y += button_size + 8;
	}

	void Progbar(Vector2 start, Vector2 end, float a, float b)
	{
		if (a < 0) return;
		fill_box(rust::classes::Rect(start.x, start.y, end.x, end.y + 1), rgba(21.f, 27.f, 37.f, 255.f));

		if ((a / b) > 1)
			a = b;

		fill_box(rust::classes::Rect(start.x + 1, start.y + 1, (end.x * (a / b)) - 1, end.y - 1), perc_col(a / b));
	}

	float out;

	Vector2 window_position = { 650, 200 };
	Vector2 lmp = { 650, 200 };
	void OnGUI(uintptr_t rcx)
	{
		tab_size = Vector2(102, 35);
		init();

		float t = 0.0f;

		if (esp::local_player)
			t = esp::local_player->get_last_sent_tick_time();

		if (opacity < 255.0f)
			opacity += 2.f;

		auto current = methods::get_current();
		auto event_type = methods::get_type(current);

		bool md = false;
		rust::classes::KeyCode k;
		if (LI_FIND(GetAsyncKeyState)(VK_RBUTTON) & 0x8000)
		{
			k = rust::classes::KeyCode::Mouse1;
			md = true;
		}
		if (LI_FIND(GetAsyncKeyState)(VK_MBUTTON) & 0x8000)
		{
			k = rust::classes::KeyCode::Mouse2;
			md = true;
		}
		if (LI_FIND(GetAsyncKeyState)(VK_XBUTTON1) & 0x8000)
		{
			k = rust::classes::KeyCode::Mouse3;
			md = true;
		}
		if (LI_FIND(GetAsyncKeyState)(VK_XBUTTON2) & 0x8000)
		{
			k = rust::classes::KeyCode::Mouse4;
			md = true;
		}

		if (event_type == rust::classes::EventType::KeyDown || event_type == rust::classes::EventType::KeyUp
			|| event_type == rust::classes::EventType::MouseDown || event_type == rust::classes::EventType::MouseUp
			|| md) {
			rust::classes::KeyCode cur = md ? k : unity::get_keyCode(current);
			if (event_type == rust::classes::EventType::KeyDown || event_type == rust::classes::EventType::MouseDown
				|| md)
				OnKeyDown(cur);
			else
				OnKeyUp(cur);
		}

		auto mouse = get_mousePosition();
		auto height = unity::get_height();

		Vector2 pos, menu_pos = window_position, menu_size = { 500, 380 }, button_size = { 200, 0 }, mouse_pos = { mouse.x, height - mouse.y };

		if (event_type == rust::classes::EventType::Repaint) {
			{
				static int cases = 0;
				static float r = 1.00f, g = 0.00f, b = 1.00f;
				switch (cases) {
				case 0: { r -= 0.0015f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.0015f; b -= 0.0015f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.0015f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.0015f; g -= 0.0015f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				const float ScreenWidth = 1920;
				const float ScreenHeight = 1080;
				const Vector2 screen_center = Vector2(1920 / 2, 1080 / 2);

				if (vars->visual.crosshair) {
					//gui::vertical_line(vector2{ (float)(ScreenWidth / 2), (float)(ScreenHeight / 2 + 2) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::vertical_line(vector2{ (float)(ScreenWidth / 2), (float)((ScreenHeight / 2)) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::horizontal_line(vector2{ (float)(ScreenWidth / 2 + 2), (float)(ScreenHeight / 2) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::horizontal_line(vector2{ (float)((ScreenWidth / 2) - 1),(float)(ScreenHeight / 2) }, 4.f, gui::Color(1, 0, 0, 0.5));


					gui::vertical_line(Vector2{ (float)(ScreenWidth / 2), (float)(ScreenHeight / 2) }, 1.f, gui::Color(1, 0, 0, 1));
				}

				if (esp::local_player)
				{
					float bars = 0;
					if (vars->visual.desync_indicator)
					{
						Progbar({ 900, (650 + (bars++ * 10)) }, { 120, 4 }, settings::desyncTime, 1.0f);
					}
					if (vars->visual.speedhack_indicator)
					{
						Progbar({ 900, (650 + (bars++ * 10)) }, { 120, 4 }, settings::speedhack, 10.0f);
					}
					//put extra gui things here
					auto held = esp::local_player->get_active_weapon();
					if (vars->combat.always_reload)
					{
						if (held->get_base_projectile())
						{
							auto b = held->get_base_projectile();
							auto r = esp::rl_time;
							if (settings::time_since_last_shot < r)
								Progbar({ 900, (650 + (bars++ * 10)) }, { 120, 4 }, settings::time_since_last_shot, (r - 0.2f));
						}
					}
					if ((esp::best_target.player && esp::best_target.player->is_alive())
						&& vars->visual.snapline > 1)
					{
						Vector2 start = vars->visual.snapline == 2 ? Vector2(ScreenWidth / 2, 0) :
							vars->visual.snapline == 3 ? Vector2(ScreenWidth / 2, 540) :
							vars->visual.snapline == 4 ? Vector2(ScreenWidth / 2, 1080) :
							Vector2(ScreenWidth / 2, 1080);
						Vector3 o = WorldToScreen(esp::best_target.pos);
						if (o.x != 0 && o.y != 0)
						{
							if (esp::best_target.visible)
								gui::line(start, Vector2(o.x, o.y), gui::Color(0, 0.9, 0.2, 1), 0.1f, true);
							else
								gui::line(start, Vector2(o.x, o.y), gui::Color(0.9, 0, 0.2, 1), 0.1f, true);
						}
					}

					if (vars->visual.draw_fov) {
						esp::draw_target_fov(col(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1), Vector2(ScreenWidth / 2, ScreenHeight / 2), vars->combat.aimbotfov);
					}

					if (vars->visual.flyhack_indicator) {
						if (settings::vert_flyhack >= 3.f) {
							Progbar({ screen_center.x - 300, screen_center.y - 500 },
								{ 600, 5 },
								settings::vert_flyhack,
								settings::vert_flyhack);
						}
						else {
							Progbar({ screen_center.x - 300, screen_center.y - 500 },
								{ 600, 5 },
								settings::vert_flyhack,
								3.f);
						}

						if (settings::hor_flyhack >= 6.5f) {
							Progbar({ screen_center.x - 300, screen_center.y - 470 },
								{ 600, 5 },
								settings::hor_flyhack,
								settings::hor_flyhack);
						}
						else {
							Progbar({ screen_center.x - 300, screen_center.y - 470 },
								{ 600, 5 },
								settings::hor_flyhack,
								6.5f);
						}
					}
				}

				esp::start();
			}
		}

		//watermark
		fill_box(rust::classes::Rect{ 10, 6, 80, 16 }, rgba(14.f, 18.f, 24.f, 255));
		outline_box({ 10, 6 }, { 80, 16 }, rgba(249.f, 130.f, 109.f, 255.f));
		fill_box(rust::classes::Rect{ 10, 20, 81, 3 }, rgba(249.f, 130.f, 109.f, 255));
		gui::Label(rust::classes::Rect{ 12, 4, 80, 20 }, _(L"traphouse"), gui::Color(1, 1, 1, 1), true, 12);

		if (open) {
			{
				int margin = 3;
				static int cases = 0;
				static float r = 1.00f, g = 0.00f, b = 1.00f;
				switch (cases) {
				case 0: { r -= 0.0015f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.0015f; b -= 0.0015f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.0015f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.0015f; g -= 0.0015f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				unity::set_lockstate(rust::classes::CursorLockMode::None);

				if (LI_FIND(GetAsyncKeyState)(VK_LBUTTON)) {
					auto z = rust::classes::Rect{ window_position.x, window_position.y, menu_size.x, 30 };

					if (z.Contains(mouse_pos))
					{
						window_position = (window_position + (mouse_pos - window_position) - Vector2(250, 15));
					}
					lmp = mouse_pos;
				}

				outline_box({ menu_pos.x - 1, menu_pos.y - 1 }, { menu_size.x + 1, menu_size.y + 1 }, rgba(249.f, 130.f, 109.f, 255.f));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y + 30, menu_size.x, menu_size.y - 30 }, rgba(21.f, 27.f, 37.f, 255));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y, menu_size.x, 30 }, rgba(14.f, 18.f, 24.f, 255));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y + 30, tab_size.x + 2, menu_size.y - 30 }, rgba(14.f, 18.f, 24.f, 255));

				//MENU TIME

				gui::Label(rust::classes::Rect{ menu_pos.x + 2.0f + 1, menu_pos.y - 4 + 1, menu_size.x, 30 }, _(L"traphouse"), gui::Color(1, 1, 1, 1), true, 16);

				menu_pos.y += 30;
				menu_size.y -= 25;

				auto weapon_tab = 0, visual_tab = 1, misc_tab = 3, other_esp = 2, color_tab = 4;

				tab(event_type, menu_pos, mouse_pos, _(L"Combat"), weapon_tab);
				tab(event_type, menu_pos, mouse_pos, _(L"Visual"), visual_tab);
				tab(event_type, menu_pos, mouse_pos, _(L"Esp"), other_esp);
				tab(event_type, menu_pos, mouse_pos, _(L"Misc"), misc_tab);
				tab(event_type, menu_pos, mouse_pos, _(L"Colors"), color_tab);

				menu_pos = { menu_pos.x + 10, menu_pos.y + 30 };
				menu_size.x -= 90;
				menu_size.y -= 15;

				std::array<wchar_t*, 13> list1_names = {
						_(L"none"),
						_(L"none"),
						_(L"clap"),
						_(L"friendly"),
						_(L"thumbsdown"),
						_(L"thumbsup"),
						_(L"ok"),
						_(L"point"),
						_(L"shrug"),
						_(L"victory"),
						_(L"wave"),
						_(L"\x00"),
						_(L"\x00")
				};
				std::array<wchar_t*, 13> list2_names = {
						_(L"none"),
						_(L"none"),
						_(L"top"),
						_(L"center"),
						_(L"bottom"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00")
				};
				std::array<wchar_t*, 13> list3_names = {
						_(L"none"),
						_(L"none"),
						_(L"normal"),
						_(L"seethrough"),
						_(L"wireframe"),
						_(L"lit"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00")
				};
				std::array<wchar_t*, 13> list4_names = {
						_(L"none"),
						_(L"none"),
						_(L"seethrough"),
						_(L"chams (rgb)"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00"),
						_(L"\x00")
				};

				std::array<wchar_t*, 8> combo1_names = {
						_(L"Null"),
						_(L"Head"),
						_(L"Body"),
						_(L"Upper arms"),
						_(L"Penis"),
						_(L"Hands"),
						_(L"Legs"),
						_(L"Feet")
				};
				std::array<bool*, 8> combo1_refs = {
					&vars->combat.hitboxes.Head,
					&vars->combat.hitboxes.Head,
					&vars->combat.hitboxes.Body,
					&vars->combat.hitboxes.Upperbody,
					&vars->combat.hitboxes.Penis,
					&vars->combat.hitboxes.Hands,
					&vars->combat.hitboxes.Legs,
					&vars->combat.hitboxes.Feet
				};

				switch (active_tab) {
				case 0:
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"PSilent"), &vars->combat.psilent, weapon_tab, true, &vars->keybinds.psilent);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Fov")), pos, vars->combat.aimbotfov, 1100.f, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent melee"), &vars->combat.silent_melee, weapon_tab, true, &vars->keybinds.silentmelee);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Thick bullet"), &vars->combat.thick_bullet, weapon_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Bullet size")), pos, vars->combat.thickness, 2.0f, weapon_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Removals"), &vars->combat.weapon_removals, weapon_tab);

					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Legit recoil"), &vars->combat.legit_recoil, weapon_tab); //
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Recoil X")), pos, vars->combat.recoily, 5.f, weapon_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Recoil Y")), pos, vars->combat.recoilx, 5.f, weapon_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Recoil"), &vars->combat.norecoil, weapon_tab);		 // make into slider?
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Spread"), &vars->combat.nospread, weapon_tab);		 //
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Sway"), &vars->combat.nosway, weapon_tab); //doesnt work?
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Automatic"), &vars->combat.automatic, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Aimbot"), &vars->combat.aimbot, weapon_tab, true, &vars->keybinds.aimbot);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Smoothing")), pos, vars->combat.aimbot_smooth, 1.f, weapon_tab);

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Body-aim"), &vars->combat.bodyaim, weapon_tab);


					//textbox(event_type, menu_pos, pos, mouse_pos, _(L"Config"), vars->misc.current_config);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Override hitboxes"), &vars->combat.hitbox_override, weapon_tab);

					pos.y += 30;
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L""), &vars->combat.random_hitbox, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Rapid fire"), &vars->combat.rapidfire, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Fast bullet"), &vars->combat.fast_bullet, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Bullet tp"), &vars->combat.bullet_tp, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Autoshoot"), &vars->combat.autoshoot, weapon_tab, true, &vars->keybinds.autoshoot);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Manipulator"), &vars->combat.manipulator, weapon_tab, true, &vars->keybinds.manipulator);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Shoot at fat"), &vars->combat.shoot_at_fatbullet, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Double-tap"), &vars->combat.doubletap, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Always reload"), &vars->combat.always_reload, weapon_tab);

					pos.y -= 190;
					pos.x += 5;
					combobox(event_type, menu_pos, pos, mouse_pos, _(L"Choose hitboxes"), combo1_names, combo1_refs);

					break;
				case 1:
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Desync indicator"), &vars->visual.desync_indicator, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Flyhack indicator"), &vars->visual.flyhack_indicator, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Speedhack indicator"), &vars->visual.speedhack_indicator, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Players"), &vars->visual.playeresp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Full Box"), &vars->visual.full_box, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Corner Box"), &vars->visual.corner_box, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Crosshair Health"), &vars->visual.midhealth, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Crosshair Name"), &vars->visual.midname, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Name"), &vars->visual.nameesp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Distance"), &vars->visual.distance, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Wounded"), &vars->visual.woundedflag, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Weapon Esp"), &vars->visual.weaponesp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Hotbar Esp"), &vars->visual.hotbar_esp, visual_tab);

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Bullet tracers"), &vars->visual.tracers, visual_tab);
					listbox(event_type, menu_pos, pos, mouse_pos, _(L"Snapline"), list2_names, &vars->visual.snapline);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Bottom healthbar"), &vars->visual.bottomhealth, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Side healthbar"), &vars->visual.sidehealth, visual_tab);
					pos.y += 25;
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Rainbow chams"), &vars->visual.rainbow_chams, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Sleeper"), &vars->visual.sleeper_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"NPC"), &vars->visual.npc_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Corpse"), &vars->visual.corpses, visual_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Misc"), &vars->visual.misc_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Held icons"), &vars->visual.spriteitem, visual_tab);
					pos.y += 25;
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Skeleton"), &vars->visual.skeleton, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Offscreen indicator"), &vars->visual.offscreen_indicator, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Show fov"), &vars->visual.draw_fov, visual_tab);

					pos.y -= 210;
					listbox(event_type, menu_pos, pos, mouse_pos, _(L"Chams"), list3_names, &vars->visual.shader);
					pos.y += 95;
					listbox(event_type, menu_pos, pos, mouse_pos, _(L"Hands"), list4_names, &vars->visual.hand_chams);
					pos.y += 115;

					//Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("third-person dist")), pos, vars->misc.tpcamdist, 20.f, misc_tab);
					//Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("third-person fov")), pos, vars->misc.tpcamfov, 90.f, misc_tab);

					break;
				case 2:
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Materials"), &vars->visual.materials, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Stone ore"), &vars->visual.stone_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Metal ore"), &vars->visual.metal_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Sulfur ore"), &vars->visual.sulfur_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Cloth"), &vars->visual.cloth, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Vehicles"), &vars->visual.vehicles, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Patrol-heli"), &vars->visual.heli_esp, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Dropped items"), &vars->visual.dropped_items, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Stashes"), &vars->visual.stash, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Ladder"), &vars->visual.ladder, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Airdrops"), &vars->visual.airdrops, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Traps"), &vars->visual.traps, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Corpses"), &vars->visual.corpses, other_esp);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Food"), &vars->visual.food, other_esp);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Animals"), &vars->visual.animal, other_esp);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Barrels"), &vars->visual.barrels, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Tool cupboard"), &vars->visual.tc_esp, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Manipulator angles"), &vars->visual.angles, other_esp);
					menu_pos.x += 170;
					pos.y = 0; //?

					listbox(event_type, menu_pos, pos, mouse_pos, _(L"Gesture"), list1_names, &vars->misc.gesture_spam);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Skin changer"), &vars->misc.skinchanger, other_esp);

					break;
				case 3:
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Player Movement"), &vars->misc.Movement, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Omnisprint"), &vars->misc.always_sprint, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Can hold items"), &vars->combat.always_shoot, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Infinite jump"), &vars->misc.infinite_jump, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Timescale"), &vars->misc.speedhack, misc_tab, true, &vars->keybinds.timescale);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Scale")), pos, vars->misc.speedhackspeed, 10.f, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Spiderman"), &vars->misc.spiderman, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Big jump"), &vars->misc.gravity, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Shoot while mounted"), &vars->misc.attack_on_mountables, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Auto farm"), &vars->misc.autofarm, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent farm"), &vars->misc.silent_farm, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent walk"), &vars->misc.silentwalk, misc_tab, true, &vars->keybinds.silentwalk);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Spinbot"), &vars->misc.spinbot, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Fake lag"), &vars->misc.fake_lag, misc_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Emulate projectile"), &vars->misc.emulate_p, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Desync"), &vars->misc.desync, misc_tab, true, &vars->keybinds.desync_ok);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Instant med"), &vars->misc.instant_med, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No recycler"), &vars->misc.norecycler, misc_tab);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Admin mode"), &vars->misc.admin_mode, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Always day"), &vars->visual.always_day, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Anti-flyhack"), &vars->misc.flyhack_stop, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Fly up wall"), &vars->misc.flywall, misc_tab, true, &vars->keybinds.flywall);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No collisions"), &vars->misc.no_playercollision, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Interactive debug"), &vars->misc.interactive_debug, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Suicide"), &vars->misc.TakeFallDamage, misc_tab, true, &vars->keybinds.suicide);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Longneck"), &vars->misc.eyeoffset, misc_tab, true, &vars->keybinds.neck);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Auto upgrade"), &vars->misc.auto_upgrade, misc_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Size")), pos, vars->misc.playereyes, 1.5f, misc_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Player FOV"), &vars->misc.playerfovtoggle, misc_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Player fov")), pos, vars->visual.playerfov, 150, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Zoom"), &vars->visual.zoomtoggle, misc_tab, true, &vars->keybinds.zoom);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Zoom fov")), pos, vars->visual.zoomfov, 50, misc_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Brightnight"), &vars->misc.brightnight, misc_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Stars")), pos, vars->visual.staramount, 1000, misc_tab);

					menu_pos.y += 5;
					textbox(event_type, menu_pos, pos, mouse_pos, _(L"config:"), &vars->config_name);
					menu_pos.x += 20;
					if (button(event_type, menu_pos, pos, mouse_pos, _(L"load"))) {
						load_config();
					}
					pos.y -= 20;
					menu_pos.x += 70;
					if (button(event_type, menu_pos, pos, mouse_pos, _(L"save"))) {
						save_config();
					}
					menu_pos.x -= 90;
					pos.y += 10;
					break;
				case 4:
					bool f = 0;
					buttonvis(event_type, menu_pos, pos, mouse_pos, _(L"Visible color"), &f, color_tab, Color(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1));
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)vars->visual.VisRcolor)), pos, vars->visual.VisRcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)vars->visual.VisGcolor)), pos, vars->visual.VisGcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)vars->visual.VisBcolor)), pos, vars->visual.VisBcolor, 1.f, color_tab);
					//}

					buttoninv(event_type, menu_pos, pos, mouse_pos, _(L"Invisible color"), &f, color_tab, Color(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1));
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)vars->visual.InvRcolor)), pos, vars->visual.InvRcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)vars->visual.InvGcolor)), pos, vars->visual.InvGcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)vars->visual.InvBcolor)), pos, vars->visual.InvBcolor, 1.f, color_tab);
					//}
					buttonteam(event_type, menu_pos, pos, mouse_pos, _(L"Teammate color"), &f, color_tab, Color(vars->visual.TeamRcolor, vars->visual.TeamGcolor, vars->visual.TeamBcolor, 1));
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)vars->visual.TeamRcolor)), pos, vars->visual.TeamRcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)vars->visual.TeamGcolor)), pos, vars->visual.TeamGcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)vars->visual.TeamBcolor)), pos, vars->visual.TeamBcolor, 1.f, color_tab);
					//}
					buttonteam(event_type, menu_pos, pos, mouse_pos, _(L"Name color"), &f, color_tab, Color(vars->visual.nameRcolor, vars->visual.nameGcolor, vars->visual.nameBcolor, 1));
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)vars->visual.nameRcolor)), pos, vars->visual.nameRcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)vars->visual.nameGcolor)), pos, vars->visual.nameGcolor, 1.f, color_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)vars->visual.nameBcolor)), pos, vars->visual.nameBcolor, 1.f, color_tab);
					//}
					break;
				};
				pos = { 0, 0 };
			}
		}
	}
}

float unity::get_fov(Vector3 Pos) {
	esp::matrix = unity::get_view_matrix();

	Vector3 ScreenPos = WorldToScreen(Pos);
	if (ScreenPos.is_empty())
		return 1000;
	return get_2d_dist(Vector2(unity::get_width() / 2, unity::get_height() / 2), ScreenPos);
}

void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = my_fmod(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}

gui::Color HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; ColorConvertHSVtoRGB(h, s, v, r, g, b); return gui::Color(r, g, b, a); }

Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float mainAngle = flAngle;
	mainAngle += 45.f;

	float flYaw = (mainAngle) * (M_PI / 180.0);

	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));

	return Vector2(posonscreenX, posonscreenY);
}

namespace esp
{
	void draw_heli(float x, float y, float w, float h) {
		gui::outline_box({ x - w / 2, y - h / 2 }, { w, h }, { 255, 255, 255, 255 });
		gui::fill_box({ x - w / 2, y - h / 2, w ,h }, { 0.2,0.2,0.2,0.3 });
		gui::outline_box({ x - w / 2 - 1, y - h / 2 - 1 }, { w + 2, h + 2 }, { 0, 0, 0, 1 });
	}

	void draw_tool_cupboard(Vector2 w2s_position, uintptr_t new_str_text, Vector4 color, rust::list<PlayerNameID*>* authorizedPlayers_list)
	{
		auto label = [&](float y, wchar_t* text)
		{
			gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3 - y, 150, 20 }, text, gui::Color(0, 0, 0, 120), false, 12);
			gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2 - y, 150, 20 }, text, gui::Color(color.x, color.y, color.z, color.w), false, 12);
		};

		gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3, 150, 20 }, new_str_text, gui::Color(0, 0, 0, 120), false, 12);
		gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2, 150, 20 }, new_str_text, gui::Color(color.x, color.y, color.z, color.w), false, 12);
		float info_y = 12;

		authorizedPlayers_list->for_each([&](PlayerNameID* authorizedPlayer, int32_t idx) {
			if (authorizedPlayer)
			{
				auto user = authorizedPlayer->get_username();
				label(info_y, user);

				LOG("Username: %ls", user);
				info_y += 30;
			}
			});
	}

	void draw_hackable_crate(Vector2 w2s_position, uintptr_t crate, Vector4 color)
	{
		auto label = [&](float y, wchar_t* text)
		{
			gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3 + y, 150, 20 }, text, gui::Color(0, 0, 0, 120), false, 14);
			gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2 + y, 150, 20 }, text, gui::Color(color.x, color.y, color.z, color.w), false, 14);
		};

		auto timer_text = *reinterpret_cast<uintptr_t*>(crate + 0x440);
		if (!timer_text)
			return;

		auto text = (str)(*reinterpret_cast<uintptr_t*>(timer_text + 0xD0));
		if (!text)
			return;

		auto m_Text = text->str;
		if (!m_Text)
			return;

		gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3, 150, 20 }, _(L"Hackable Crate"), gui::Color(0, 0, 0, 120), false, 14);
		gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2, 150, 20 }, _(L"Hackable Crate"), gui::Color(color.x, color.y, color.z, color.w), false, 14);
		label(12, m_Text);
	}

	void draw_item(Vector2 w2s_position, uintptr_t label, Vector4 color, wchar_t* name) { // vector4 because color gui im mretard dont talk about it
		color /= 255;
		if (label) {
			gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3, 150, 20 }, label, gui::Color(0, 0, 0, 120), false, 12);
			gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2, 150, 20 }, label, gui::Color(color.x, color.y, color.z, color.w), false, 12);
		}
		else {
			gui::Label(rust::classes::Rect{ w2s_position.x + 1, w2s_position.y + 3, 150, 20 }, name, gui::Color(0, 0, 0, 120), false, 12);
			gui::Label(rust::classes::Rect{ w2s_position.x, w2s_position.y + 2, 150, 20 }, name, gui::Color(color.x, color.y, color.z, color.w), false, 12);
		}
	}

	void draw_target_hotbar(aim_target target) {
		auto screen = WorldToScreen(target.pos);

		if (target.player && !target.is_heli && screen.z != 0 && !target.teammate) {
			auto draw_item = [&](bool draw_wearable, float x, float width) {
				rust::list<weapon*>* belt = target.player->get_belt_items();
				if (draw_wearable)
					belt = target.player->get_wearable_items();

				if (belt) {
					float info_y = 0;
					weapon* result = nullptr;


					int current_item = 0;
					//hotbar esp
					belt->for_each([&](weapon* item, int32_t idx) {
						{
							static int cases = 0;
							static float r = 1.00f, g = 0.00f, b = 1.00f;
							switch (cases) {
							case 0: { r -= 0.0008f; if (r <= 0) cases += 1; break; }
							case 1: { g += 0.0008f; b -= 0.0008f; if (g >= 1) cases += 1; break; }
							case 2: { r += 0.0008f; if (r >= 1) cases += 1; break; }
							case 3: { b += 0.0008f; g -= 0.0008f; if (b >= 1) cases = 0; break; }
							default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
							}

							if (!item)
								return;
							const auto item_name = item->get_weapon_name();
							if (item_name) {
								auto sprite = get_iconSprite(item);
								if (!sprite)
									return;
								auto texture = get_texture(sprite);
								if (!texture)
									return;
								auto rect = get_rect(sprite);
								auto height = rect.hei;
								int getam = item->GetAmount();
#define newstring new_string

								current_item += 1;

								//hotbar esp background
								if (vars->visual.hotbar_esp) {
									gui::fill_box({ 661 + info_y, (unity::get_height() * 0.8f), 90, 90 }, { 0, 0, 0, 0.12 });

									gui::methods::set_color({ 1, 1, 1, 1 });
									gui::methods::DrawTexture({ 663 + info_y, (unity::get_height() * 0.8f) + 5, rect.wid / 3.0f, rect.hei / 3.0f }, texture);
									//gui::Label(rust::classes::Rect{ x + 2.0f + 1, info_y - 4 + 13 + 1 + (unity::get_height() * 0.75f), width - 10, height / current_item }, item_name, gui::Color(0, 0, 0, 120), true, 12);
									//gui::Label(rust::classes::Rect{ x + 2.0f, info_y - 4 + 13 + (unity::get_height() * 0.75f), width - 10, height / current_item }, item_name, gui::Color(255, 255, 255, 220), true, 12);

									/*
									gui::fill_box({ 20, 400, 200, 200 }, { 0, 0, 0, 0.12 });
									gui::fill_box({ 20, 400, 200, 200 }, { 0, 0, 0, 0.12 });
									gui::outline_box(vector2{ 20, 400 }, vector2{ 200, 200 }, gui::Color(1, 0, 0, 1));
									gui::outline_box(vector2{ 20, 400 }, vector2{ 200, 200 }, gui::Color(1, 0, 0, 1));
									gui::Label(rust::classes::Rect{ 20, 320, 200, 200 }, target.player->get_player_name(), gui::Color(1, 1, 1, 1), true, 9);
									gui::Label(rust::classes::Rect{ 20, 320, 200, 200 }, target.player->get_player_name(), gui::Color(255, 255, 255, 220), true, 9);
									gui::Label(rust::classes::Rect{ 20, 370 + info_y, 200, 200 }, il2cpp::methods::newstring(string::format(("(x%d) %ls"), getam, item_name)), gui::Color(1, 1, 1, 1), true, 9);
									gui::Label(rust::classes::Rect{ 20, 370 + info_y, 200, 200 }, il2cpp::methods::newstring(string::format(("(x%d) %ls"), getam, item_name)), gui::Color(255, 255, 255, 220), true, 9);
									*/
									info_y += 95;
								}
							}
						}
						});
					info_y = 0;
				}
			};

			float width = 260;
			draw_item(false, (unity::get_width() - width) / 2, width);
		}
	}

	void draw_name(Vector3 position, wchar_t* name)
	{
		if (name)
		{
			gui::Label(rust::classes::Rect{ position.x + 2.0f + 1, position.y - 4 + 1, 150, 20 }, name, gui::Color(0, 0, 0, 120), false, 12);
			gui::Label(rust::classes::Rect{ position.x + 2.0f, position.y - 4, 150, 20 }, name, gui::Color(255, 255, 255, 220), false, 12);
		}
	}

	void draw_middle(aim_target target) {
		//check if player
		if (target.player && !target.teammate && !target.sleeping && target.player != local_player) {
			//check if enabled
			if (vars->visual.midname) {
				//draw player name dropshadow
				gui::Label(rust::classes::Rect{ 861, 442 , 200, 260 }, target.player->get_player_name(), gui::Color(0, 0, 0, 1), true, 12);
				// draw player name
				gui::Label(rust::classes::Rect{ 862, 441, 200, 260 }, target.player->get_player_name(), gui::Color(1, 1, 1, 1), true, 12);
			}
			if (vars->visual.midhealth) {
				const auto cur_health = target.player->get_health();
				//draw player health dropshadow
				gui::Label(rust::classes::Rect{ 861 , 457, 200, 260 }, il2cpp::methods::new_string(string::format(("[%.f]"), cur_health)), gui::Color(0, 0, 0, 1), true, 10);
				//draw player health
				gui::Label(rust::classes::Rect{ 862 , 456, 200, 260 }, il2cpp::methods::new_string(string::format(("[%.f]"), cur_health)), gui::Color(1, 1, 1, 1), true, 10);
			}
		}
	}

	void draw_target_fov(col color, Vector2 o, float r) {
		gui::circle(o, r, color, true);
	}

	void offscreen_indicator(Vector3 position) {
		Vector3 local = esp::local_player->get_player_eyes()->get_position();

		float num = atan2(local.x - position.x, local.z - position.z) * 57.29578f - 180.f - EulerAngles(esp::local_player->get_player_eyes()->get_rotation()).y;

		if (!(num < -420 || num > -300)) return;
		Vector2 tp0 = CosTanSinLineH(num, 5.f,		 1920 / 2, 1080 / 2, 150.f);
		Vector2 tp1 = CosTanSinLineH(num + 2.f, 5.f, 1920 / 2, 1080 / 2, 140.f);
		Vector2 tp2 = CosTanSinLineH(num - 2.f, 5.f, 1920 / 2, 1080 / 2, 140.f);

		Vector2 p = { tp0.x, tp0.y }, p1 = { tp1.x, tp1.y }, p2 = { tp2.x, tp2.y };
		gui::line(tp0, tp1, rgba(249.f, 130.f, 109.f, 255.f));
		gui::line(tp0, tp2, rgba(249.f, 130.f, 109.f, 255.f));
		gui::line(tp1, tp2, rgba(249.f, 130.f, 109.f, 255.f));
	}

	void draw_weapon_icon(weapon* item, Vector2 w2s_position) {

		auto sprite = get_iconSprite(item);
		if (!sprite)
			return;

		auto texture = get_texture(sprite);
		if (!texture)
			return;

		auto rect = get_rect(sprite);
		if (texture) {
			gui::methods::set_color({ 1, 1, 1, 1 });
			gui::methods::DrawTexture({ w2s_position.x + 2.0f + 1, w2s_position.y - 4 + 13 + 1, rect.wid / 7, rect.hei / 7 }, texture);
			//gui::Label({ w2s_position.x + 2.0f + 1, w2s_position.y - 4 + 13 + 1, rect.wid / 7, rect.hei / 7 }, il2cpp::methods::new_string(_("")), gui::Color(196, 124, 0, 255));
		}
	}

	static float r = 1.00f, g = 0.00f, b = 1.00f;
	void do_chams(base_player* player)
	{
		if (!player->is_alive() || player->is_sleeping()) return;
		if (unity::bundle)
		{
			uintptr_t shader = unity::chams_shader_normal;
			switch (vars->visual.shader)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				shader = unity::LoadAsset(unity::bundle, _(L"Chams"), unity::GetType(_("UnityEngine"), _("Shader")));
				break;
			case 3:
				shader = unity::LoadAsset(unity::bundle, _(L"SeethroughShader"), unity::GetType(_("UnityEngine"), _("Shader")));
				break;
			case 4:
				shader = unity::LoadAsset(unity::bundle, _(L"WireframeTransparent"), unity::GetType(_("UnityEngine"), _("Shader")));
				break;
			case 5:
				shader = unity::LoadAsset(unity::bundle, _(L"chamslit"), unity::GetType(_("UnityEngine"), _("Shader")));
				break;
			}

			//if (vars->visual.shader == 6
			//	|| vars->visual.hand_chams == 4)
			//{
			//	if(!unity::galaxy_material)
			//		unity::galaxy_material = unity::LoadAsset(unity::galaxy_bundle, _(L"GalaxyMaterial_10"), unity::GetType(_("UnityEngine"), _("Material")));
			//}

			if ((!shader /* && !unity::galaxy_material*/) && vars->visual.hand_chams < 1) return;

			if (vars->visual.hand_chams > 1
				&& player->is_local_player()) {
				auto model = gui::methods::get_activemodel();
				auto renderers = ((networkable*)model)->GetComponentsInChildren(unity::GetType(_("UnityEngine"), _("Renderer")));
				if (renderers)
				{
					auto sz = *reinterpret_cast<int*>(renderers + 0x18);

					for (int i = 0; i < sz; i++) {
						//if (sz == 2) i == 1; //skips front of weapon
						auto renderer = *reinterpret_cast<uintptr_t*>(renderers + 0x20 + i * 0x8);

						if (!renderer) continue;
						auto material = get_material(renderer);
						if (!material) continue;

						switch (vars->visual.hand_chams)
						{
						case 2:
						{
							uintptr_t s = unity::LoadAsset(unity::bundle, _(L"SeethroughShader"), unity::GetType(_("UnityEngine"), _("Shader")));
							if (s)
								unity::set_shader(material, s);
							break;
						}
						case 3:
						{
							auto s = FindShader(rust::classes::string(_(L"Standard")));
							unity::set_shader(material, s);
							SetColor(material, _(L"_Color"), col(r, g, b, 0.5));
							break;
						}
						//case 4:
						//{
						//	if (unity::galaxy_material && material != unity::galaxy_material)
						//	{
						//		//unity::set_shader(material, unity::space_material);
						//		//auto s = FindShader(rust::classes::string(_(L"Standard")));
						//		//unity::set_shader(unity::galaxy_material, s);
						//		set_material(renderer, unity::galaxy_material);
						//		SetInt(unity::galaxy_material, _(L"_ZTest"), 8);
						//	}
						//	break;
						//}
						}
					}
				}
			}

			if (vars->visual.shader > 1 && (shader /*|| unity::galaxy_material*/) && player) {

				static int cases = 0;
				switch (cases) {
				case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				//unity::chams_shader = unity::LoadAsset(unity::bundle, _(L"Chams"), unity::GetType(_("UnityEngine"), _("Shader")));

				auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
				if (!_multiMesh) return;
				auto render = get_Renderers(_multiMesh);
				if (!render) return;

				for (int i = 0; i < render->get_size(); i++) {
					auto renderer = render->get_value(i);
					if (!renderer) continue;
					auto material = get_material(renderer);
					if (!material) continue;
					//if (vars->visual.shader == 6 && unity::galaxy_material)
					//{
					//	if (material != unity::galaxy_material)
					//	{
					//		set_material(renderer, unity::galaxy_material);
					//		SetInt(unity::galaxy_material, _(L"_ZTest"), 8);
					//	}
					//} else 
					if (shader)
					{
						if (shader != unity::get_shader(material)) {
							unity::set_shader(renderer, shader);
						}
						else
						{
							auto viscolor = col(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1);
							auto inviscolor = col(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1);

							if (vars->visual.rainbow_chams)
							{
								viscolor = col(r, g, b, 1);
								inviscolor = col(1.f - r, 1.f - g, 1.f - b, 1);
							}

							switch (vars->visual.shader)
							{
							case 2:
								SetColor(material, _(L"_ColorVisible"), viscolor);
								SetColor(material, _(L"_ColorBehind"), inviscolor);
								break;
							case 4:
								SetColor(material, _(L"_WireColor"), viscolor);
								break;
							case 5:
								SetColor(material, _(L"_ColorVisible"), viscolor);
								SetColor(material, _(L"_ColorBehind"), inviscolor);
								break;
							}
						}
					}
				}
			}
			return;
		}
	}

	void draw_player(base_player* player, bool is_npc)
	{
		if (!local_player)
			return;

		do_chams(player);

		//   esp colors
		auto visible_color = gui::Color(vars->visual.VisRcolor, vars->visual.VisGcolor, vars->visual.VisBcolor, 1);
		auto invisible_color = gui::Color(vars->visual.InvRcolor, vars->visual.InvGcolor, vars->visual.InvBcolor, 1);
		auto teammate_color = gui::Color(vars->visual.TeamRcolor, vars->visual.TeamGcolor, vars->visual.TeamBcolor, 1);
		auto safezone_color = gui::Color{ 0.99609375, 0.9453125, 0, 1.0 };
		bounds_t bounds;

		struct bone_t {
			Vector3 screen;
			int8_t     index;
			bool       on_screen;
			Vector3 world_position;
			bool visible;
		};

		std::array<bone_t, 20> bones = {
			//additional to original 20 (15 * 2) = 50
			//bone_t{ Vector3{}, 58, false, Vector3{}, false },  // r_index1
			//bone_t{ Vector3{}, 59, false, Vector3{}, false },  // r_index2
			//bone_t{ Vector3{}, 60, false, Vector3{}, false },  // r_index3
			//bone_t{ Vector3{}, 61, false, Vector3{}, false },  // r_little1
			//bone_t{ Vector3{}, 62, false, Vector3{}, false },  // r_little2
			//bone_t{ Vector3{}, 63, false, Vector3{}, false },  // r_little3
			//bone_t{ Vector3{}, 64, false, Vector3{}, false },  // r_middle1
			//bone_t{ Vector3{}, 65, false, Vector3{}, false },  // r_middle2
			//bone_t{ Vector3{}, 66, false, Vector3{}, false },  // r_middle3
			//bone_t{ Vector3{}, 68, false, Vector3{}, false },  // r_ring1
			//bone_t{ Vector3{}, 69, false, Vector3{}, false },  // r_ring2
			//bone_t{ Vector3{}, 70, false, Vector3{}, false },  // r_ring3
			//bone_t{ Vector3{}, 71, false, Vector3{}, false },  // r_thumb1
			//bone_t{ Vector3{}, 72, false, Vector3{}, false },  // r_thumb2
			//bone_t{ Vector3{}, 73, false, Vector3{}, false },  // r_thumb3
			//bone_t{ Vector3{}, 27, false, Vector3{}, false },  // l_index1
			//bone_t{ Vector3{}, 28, false, Vector3{}, false },  // l_index2
			//bone_t{ Vector3{}, 29, false, Vector3{}, false },  // l_index3
			//bone_t{ Vector3{}, 30, false, Vector3{}, false },  // l_little1
			//bone_t{ Vector3{}, 31, false, Vector3{}, false },  // l_little2
			//bone_t{ Vector3{}, 32, false, Vector3{}, false },  // l_little3
			//bone_t{ Vector3{}, 33, false, Vector3{}, false },  // l_middle1
			//bone_t{ Vector3{}, 34, false, Vector3{}, false },  // l_middle2
			//bone_t{ Vector3{}, 35, false, Vector3{}, false },  // l_middle3
			//bone_t{ Vector3{}, 37, false, Vector3{}, false },  // l_ring1
			//bone_t{ Vector3{}, 38, false, Vector3{}, false },  // l_ring2
			//bone_t{ Vector3{}, 39, false, Vector3{}, false },  // l_ring3
			//bone_t{ Vector3{}, 40, false, Vector3{}, false },  // l_thumb1
			//bone_t{ Vector3{}, 41, false, Vector3{}, false },  // l_thumb2
			//bone_t{ Vector3{}, 42, false, Vector3{}, false },  // l_thumb3

			bone_t{ Vector3{}, 2, false, Vector3{}, false },  // l_hip
			bone_t{ Vector3{}, 3, false, Vector3{}, false },  // l_knee
			bone_t{ Vector3{}, 6, false, Vector3{}, false },  // l_ankle_scale
			bone_t{ Vector3{}, 5, false, Vector3{}, false },  // l_toe
			bone_t{ Vector3{}, 24, false, Vector3{}, false }, // l_upperarm
			bone_t{ Vector3{}, 25, false, Vector3{}, false }, // l_forearm
			bone_t{ Vector3{}, 26, false, Vector3{}, false }, // l_hand
			bone_t{ Vector3{}, 27, false, Vector3{}, false }, // l_index1

			bone_t{ Vector3{}, 48, false, Vector3{}, false }, // jaw
			bone_t{ Vector3{}, 18, false, Vector3{}, false }, // spine1
			bone_t{ Vector3{}, 21, false, Vector3{}, false }, // spine3
			bone_t{ Vector3{}, 1, false, Vector3{}, false },  // pelvis
			bone_t{ Vector3{}, 23, false, Vector3{}, false }, // l_clavicle

			bone_t{ Vector3{}, 17, false, Vector3{}, false }, // r_ankle_scale
			bone_t{ Vector3{}, 15, false, Vector3{}, false }, // r_foot
			bone_t{ Vector3{}, 14, false, Vector3{}, false }, // r_knee
			bone_t{ Vector3{}, 55, false, Vector3{}, false }, // r_upperarm
			bone_t{ Vector3{}, 56, false, Vector3{}, false }, // r_forearm
			bone_t{ Vector3{}, 57, false, Vector3{}, false }, // r_hand
			bone_t{ Vector3{}, 76, false, Vector3{}, false }  // r_ulna
		};

		bool is_visible = false;

		bool is_teammate = player->is_teammate(local_player);

		auto camera_position = unity::get_camera_pos();

		const auto get_bounds = [&](bounds_t& out, float expand = 0) -> bool {
			bounds = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

			for (auto& [bone_screen, bone_idx, on_screen, world_position, visible] : bones) {

				auto transform = player->get_bone_transform(bone_idx);

				world_position = transform->get_bone_position();

				if (bone_idx == 48) // lol
					world_position.y += 0.2f;

				bone_screen = WorldToScreen(world_position);
				if (bone_screen.x < bounds.left)
					bounds.left = bone_screen.x;
				if (bone_screen.x > bounds.right)
					bounds.right = bone_screen.x;
				if (bone_screen.y < bounds.top)
					bounds.top = bone_screen.y;
				if (bone_screen.y > bounds.bottom)
					bounds.bottom = bone_screen.y;
				on_screen = true;
			}

			if (bounds.left == FLT_MAX)
				return false;
			if (bounds.right == FLT_MIN)
				return false;
			if (bounds.top == FLT_MAX)
				return false;
			if (bounds.bottom == FLT_MIN)
				return false;

			bounds.left -= expand;
			bounds.right += expand;
			bounds.top -= expand;
			bounds.bottom += expand;

			out = bounds;

			return true;
		};

		if (get_bounds(bounds, 4)) {
			//if (!is_visible)
			//is_visible = unity::is_visible(camera_position, player->get_bone_transform(48)->get_bone_position(), (uintptr_t)esp::local_player);
			
			__try
			{
				for (auto& [bone_screen, bone_idx, on_screen, world_position, visible] : bones) {
					if (is_visible) break;
					is_visible = unity::is_visible(camera_position, world_position, (uintptr_t)esp::local_player);
				}
			}
			__except (true) { is_visible = false; }
			//is_visible = unity::is_visible(camera_position, bones[47].world_position, (uintptr_t)esp::local_player);

			gui::Color clr = !is_teammate ? (is_visible ? visible_color : invisible_color) : teammate_color;
			if (HasPlayerFlag(player, rust::classes::PlayerFlags::SafeZone))
				clr = safezone_color;

			float box_width = bounds.right - bounds.left;
			float box_height = bounds.bottom - bounds.top;

			const float ScreenWidth = 1920;
			const float ScreenHeight = 1080;
			if (vars->visual.crosshair) {
				{
					static int cases = 0;
					static float r = 1.00f, g = 0.00f, b = 1.00f;
					switch (cases) {
					case 0: { r -= 0.0008f; if (r <= 0) cases += 1; break; }
					case 1: { g += 0.0008f; b -= 0.0008f; if (g >= 1) cases += 1; break; }
					case 2: { r += 0.0008f; if (r >= 1) cases += 1; break; }
					case 3: { b += 0.0008f; g -= 0.0008f; if (b >= 1) cases = 0; break; }
					default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
					}

				}
			}
			wchar_t* name = player->get_player_name();
			auto player_weapon = player->get_active_weapon();

			if (vars->visual.full_box) {
				//full box
				gui::outline_box(Vector2{ bounds.left - 1, bounds.top - 1 }, Vector2{ box_width + 2, box_height + 2 }, gui::Color(0, 0, 0, 120));
				gui::outline_box(Vector2{ bounds.left, bounds.top }, Vector2{ box_width, box_height }, clr);
				gui::outline_box(Vector2{ bounds.left + 1, bounds.top + 1 }, Vector2{ box_width - 2, box_height - 2 }, gui::Color(0, 0, 0, 120));
				//full box
			}

			if (vars->visual.corner_box) {
				//corner box
				auto wid = box_width / 4;
				gui::horizontal_line(Vector2{ bounds.left, bounds.top }, wid, clr); //tl
				gui::horizontal_line(Vector2{ bounds.right, bounds.top }, -(wid), clr); //tr
				gui::horizontal_line(Vector2{ bounds.left, bounds.top + 1 }, wid, clr);
				gui::horizontal_line(Vector2{ bounds.right, bounds.top + 1 }, -(wid), clr);

				gui::horizontal_line(Vector2{ bounds.left, bounds.bottom }, wid, clr);
				gui::horizontal_line(Vector2{ bounds.right + 1.f, bounds.bottom }, -(wid), clr);
				gui::horizontal_line(Vector2{ bounds.left, bounds.bottom + 1 }, wid, clr);
				gui::horizontal_line(Vector2{ bounds.right + 1.f, bounds.bottom + 1 }, -(wid), clr);

				gui::vertical_line(Vector2{ bounds.left, bounds.top }, wid, clr);
				gui::vertical_line(Vector2{ bounds.right, bounds.top }, wid, clr);
				gui::vertical_line(Vector2{ bounds.left + 1, bounds.top }, wid, clr);
				gui::vertical_line(Vector2{ bounds.right + 1, bounds.top }, wid, clr);

				gui::vertical_line(Vector2{ bounds.left, bounds.bottom }, -(wid), clr);
				gui::vertical_line(Vector2{ bounds.right, bounds.bottom }, -(wid), clr);
				gui::vertical_line(Vector2{ bounds.left + 1, bounds.bottom }, -(wid), clr);
				gui::vertical_line(Vector2{ bounds.right + 1, bounds.bottom }, -(wid), clr);
				//corner box
			}

			//     health bar   
			const auto cur_health = player->get_health();
			const auto max_health = (is_npc ? player->get_max_health() : 100);
			const auto health_pc = min(cur_health / max_health, 1);
			const auto health_color =
				HSV((health_pc * .25f), 1, .875f * 1);

			const auto     height = (bounds.bottom - bounds.top) * health_pc;
			if (vars->visual.bottomhealth) {
				gui::fill_box(rust::classes::Rect(bounds.left, bounds.bottom + 6, box_width + 1, 6), gui::Color(0, 0, 0, 120));
				gui::fill_box(rust::classes::Rect(bounds.left + 2, bounds.bottom + 8, ((box_width / max_health) * cur_health) - 2, 2), health_color);
				//gui::Label(rust::classes::Rect{ bounds.left, bounds.bottom + 10, box_width, box_width / 2 }, il2cpp::methods::new_string(string::format(("%.f"), cur_health)), gui::Color(255, 255, 255, 220), false, box_width / 3);
				//HEALTH NUMBER UNDER BAR ^^^^^^^^^^^^^ LAGGY
			}
			if (vars->visual.sidehealth) {
				gui::fill_box(rust::classes::Rect(bounds.left - 8, bounds.top + 2, 6, box_height + 3), gui::Color(0, 0, 0, 120));
				gui::fill_box(rust::classes::Rect(bounds.left - 6, bounds.top + box_height - height + 2, 2, height), health_color);
			}

			if (player_weapon)
			{
				auto sprite = get_iconSprite(player_weapon);
				if (!sprite)
					return;

				auto texture = get_texture(sprite);
				if (!texture)
					return;

				auto rect = get_rect(sprite);
				if (texture) {
					if (vars->visual.spriteitem) {
						gui::methods::set_color({ 1, 1, 1, 1 });
						gui::methods::DrawTexture({ bounds.right + 2.0f + 1, bounds.top - 4 + 13 + 1, rect.wid / 7, rect.hei / 7 }, texture);
					}
				}
				float half = (bounds.right - bounds.left) / 2;
				auto weapon_name = player_weapon->get_weapon_name();
				if (weapon_name)
				{
					// WEAPON NAME ESP
					if (vars->visual.weaponesp) {
						auto half = (bounds.right - bounds.left) / 2;
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.top + 10.f, 80.f + half * 2 + 80.f , 20 }, weapon_name, gui::Color(0, 0, 0, 120), true, 10.5);
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.top + 9.f, 80.f + half * 2 + 79.f , 20 }, weapon_name, gui::Color(0.99609375, 0, 0.67578125, 1), true, 10);
					}
				}
			}

			if (name)
			{
				auto transform = player->get_bone_transform(48);

				auto position = transform->get_bone_position();

				auto distance = esp::local_player->get_bone_transform(48)->get_bone_position().distance(position);
				//const char* new_name = ;
				// PLAYER NAME

				//const wchar_t* nw;

				if (vars->visual.nameesp) {
					auto half = (bounds.right - bounds.left) / 2;

					if (vars->visual.woundedflag) {

						const wchar_t* woundedlol = L"Wounded";

						if (HasPlayerFlag(player, rust::classes::PlayerFlags::Wounded)) {

							//outline 
							gui::Label(rust::classes::Rect{ bounds.left - 79.5f  , bounds.top - 32.f, 79.f + half * 2 + 79.5f , 20 }, woundedlol, gui::Color(0, 0, 0, 120), true, 9.5);
							//actual text
							gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.top - 33.f, 80.f + half * 2 + 80.f , 20 }, woundedlol, gui::Color(0.99609, 0.56640, 0, 1), true, 9);
						}

					}

					if (vars->visual.distance)
					{
						auto nstr = string::wformat(_(L"[%dm]"), (int)distance);
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 17.f, 79.f + half * 2 + 80.f , 30 }, nstr, gui::Color(0, 0, 0, 120), true, 10.5);
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 18.f, 80.f + half * 2 + 80.f , 30 }, nstr, gui::Color(vars->visual.nameRcolor, vars->visual.nameGcolor, vars->visual.nameBcolor, 1), true, 10);
					}
					//if (vars->visual.distance)
					//	nw = string::wformat(_(L"%s\n%d"), _(L""), name, (int)distance);
					//else
					//	nw = string::wformat(_(L"%s"), _(L""), name);

					gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 7.f, 79.f + half * 2 + 80.f , 30 }, name, gui::Color(0, 0, 0, 120), true, 10.5);
					gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 8.f, 80.f + half * 2 + 80.f , 30 }, name, gui::Color(vars->visual.nameRcolor, vars->visual.nameGcolor, vars->visual.nameBcolor, 1), true, 10);
				}
				// PLAYER NAME
			}

			std::array<int, 18> skeleton_boneids = {
					48, //jaw
					22, //spine4
					21, //spine3
					7, //pelvis
					3, //l_hip
					14, //r_knee
					6,
					17,
					15,
					4,
					55,
					24,
					56,
					25,
					13,
					2,
					26,
					57
			};



			if (vars->visual.skeleton)
			{
				//jaw -> spine4
				//spine4 -- l_upperarm -> l_lowerarm -> l_hand -> (make hands)
				//spine4 -- r_upperarm -> r_lowerarm -> r_hand -> (make hands)
				//spine4 -> spine3
				//spine3 -> pelvis
				//pelvis -- l_knee -> l_ankle_scale -> l_foot
				//pelvis -- r_knee -> r_ankle_scale -> r_foot
				/*
				for (size_t i = 0; i < 17; i++)
				{
					int id = skeleton_boneids[i++];
					auto transform = player->get_bone_transform(id);
					Vector3 world_position = transform->get_bone_position();
					Vector3 v1 = WorldToScreen(world_position);
					if (id > 17) break;
					transform = player->get_bone_transform(id);
					world_position = transform->get_bone_position();
					Vector3 v2 = WorldToScreen(world_position);
					if (v1.y >= 1080 || v1.x >= 1920 || v1.x <= 0 || v1.y <= 0) continue;
					if (v2.y >= 1080 || v2.x >= 1920 || v2.x <= 0 || v2.y <= 0) continue;
					gui::line(Vector2(v1.x, v1.y), Vector2(v2.x, v2.y), health_color);
				}
				*/
				
				//jaw
				auto transform = player->get_bone_transform(48);
				if (!transform) return;
				Vector3 world_position = transform->get_bone_position();
				Vector3 jaw = WorldToScreen(world_position);

				//spine4
				transform = player->get_bone_transform(22);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 spine4 = WorldToScreen(world_position);

				//spine3
				transform = player->get_bone_transform(21);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 spine3 = WorldToScreen(world_position);

				//pelvis
				transform = player->get_bone_transform(7);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 pelvis = WorldToScreen(world_position);

				//l_hip
				transform = player->get_bone_transform(3);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_hip = WorldToScreen(world_position);

				//r_knee
				transform = player->get_bone_transform(14);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_knee = WorldToScreen(world_position);

				//l_ankle_scale
				transform = player->get_bone_transform(6);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_ankle_scale = WorldToScreen(world_position);

				//r_ankle_scale
				transform = player->get_bone_transform(17);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_ankle_scale = WorldToScreen(world_position);

				//r_foot
				transform = player->get_bone_transform(15);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_foot = WorldToScreen(world_position);

				//l_foot
				transform = player->get_bone_transform(4);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_foot = WorldToScreen(world_position);

				//r_upperarm
				transform = player->get_bone_transform(55);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_upperarm = WorldToScreen(world_position);

				//l_upperarm
				transform = player->get_bone_transform(24);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_upperarm = WorldToScreen(world_position);

				//r_forearm
				transform = player->get_bone_transform(56);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_forearm = WorldToScreen(world_position);

				//l_forearm
				transform = player->get_bone_transform(25);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_forearm = WorldToScreen(world_position);

				//r_hip
				transform = player->get_bone_transform(13);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_hip = WorldToScreen(world_position);

				//l_knee
				transform = player->get_bone_transform(2);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_knee = WorldToScreen(world_position);

				//l_hand
				transform = player->get_bone_transform(26);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 l_hand = WorldToScreen(world_position);

				//r_hand
				transform = player->get_bone_transform(57);
				if (!transform) return;
				world_position = transform->get_bone_position();
				Vector3 r_hand = WorldToScreen(world_position);

				if (jaw.y >= 1080 || jaw.x >= 1920 || jaw.x <= 0 || jaw.y <= 0) return;
				if (spine4.y >= 1080 || spine4.x >= 1920 || spine4.x <= 0 || spine4.y <= 0) return;
				if (spine4.y >= 1080 || spine4.x >= 1920 || spine4.x <= 0 || spine4.y <= 0) return;
				if (spine4.y >= 1080 || spine4.x >= 1920 || spine4.x <= 0 || spine4.y <= 0) return;
				if (l_upperarm.y >= 1080 || l_upperarm.x >= 1920 || l_upperarm.x <= 0 || l_upperarm.y <= 0) return;
				if (r_upperarm.y >= 1080 || r_upperarm.x >= 1920 || r_upperarm.x <= 0 || r_upperarm.y <= 0) return;
				if (spine3.y >= 1080 || spine3.x >= 1920 || spine3.x <= 0 || spine3.y <= 0) return;
				if (pelvis.y >= 1080 || pelvis.x >= 1920 || pelvis.x <= 0 || pelvis.y <= 0) return;
				if (pelvis.y >= 1080 || pelvis.x >= 1920 || pelvis.x <= 0 || pelvis.y <= 0) return;
				if (l_knee.y >= 1080 || l_knee.x >= 1920 || l_knee.x <= 0 || l_knee.y <= 0) return;
				if (r_knee.y >= 1080 || r_knee.x >= 1920 || r_knee.x <= 0 || r_knee.y <= 0) return;
				if (l_hand.y >= 1080 || l_hand.x >= 1920 || l_hand.x <= 0 || l_hand.y <= 0) return;
				if (r_hand.y >= 1080 || r_hand.x >= 1920 || r_hand.x <= 0 || r_hand.y <= 0) return;
				if (r_ankle_scale.y >= 1080 || r_ankle_scale.x >= 1920 || r_ankle_scale.x <= 0 || r_ankle_scale.y <= 0) return;
				if (l_ankle_scale.y >= 1080 || l_ankle_scale.x >= 1920 || l_ankle_scale.x <= 0 || l_ankle_scale.y <= 0) return;

				pelvis.y += 0.2;
				l_hip.y += 0.2;

				gui::line(Vector2(jaw.x, jaw.y), Vector2(spine4.x, spine4.y), health_color);
				gui::line(Vector2(spine4.x, spine4.y), Vector2(spine3.x, spine3.y), health_color);
				gui::line(Vector2(spine4.x, spine4.y), Vector2(l_upperarm.x, l_upperarm.y), health_color);
				gui::line(Vector2(spine4.x, spine4.y), Vector2(r_upperarm.x, r_upperarm.y), health_color);
				gui::line(Vector2(l_upperarm.x, l_upperarm.y), Vector2(l_forearm.x, l_forearm.y), health_color);
				gui::line(Vector2(r_upperarm.x, r_upperarm.y), Vector2(r_forearm.x, r_forearm.y), health_color);
				gui::line(Vector2(l_forearm.x, l_forearm.y), Vector2(l_hand.x, l_hand.y), health_color);
				gui::line(Vector2(r_forearm.x, r_forearm.y), Vector2(r_hand.x, r_hand.y), health_color);
				gui::line(Vector2(spine3.x, spine3.y), Vector2(pelvis.x, pelvis.y), health_color);

				gui::line(Vector2(l_hip.x, l_hip.y), Vector2(l_knee.x, l_knee.y), health_color);
				gui::line(Vector2(pelvis.x, pelvis.y), Vector2(r_knee.x, r_knee.y), health_color);

				gui::line(Vector2(l_knee.x, l_knee.y), Vector2(l_ankle_scale.x, l_ankle_scale.y), health_color);
				gui::line(Vector2(r_knee.x, r_knee.y), Vector2(r_ankle_scale.x, r_ankle_scale.y), health_color);

				//gui::line(Vector2(l_ankle_scale.x, l_ankle_scale.y), Vector2(l_foot.x, l_foot.y), health_color);
				gui::line(Vector2(r_ankle_scale.x, r_ankle_scale.y), Vector2(r_foot.x, r_foot.y), health_color);

				
				//HANDS??
			}
		}
	}
}