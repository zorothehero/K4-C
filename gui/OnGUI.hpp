#pragma once
#include "../rust/unity.hpp"
#include "../rust/features/player_esp.hpp"
#include "../settings.hpp"
#include "../utils/string_format.h"

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

		static auto LoadAllAssets = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAllAssets"), 1, _("type"), _("UnityEngine"), 1)));

		static auto LoadFromFile = reinterpret_cast<uintptr_t(*)(rust::classes::string path)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile"), 1, _("path"), _("UnityEngine"), 1)));

		static auto LoadAsset = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, rust::classes::string path, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset"), 2, _("name"), _("UnityEngine"), 1)));		 

		static auto DrawTexture = reinterpret_cast<void (*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("DrawTexture"), 2, _("image"), _("UnityEngine"), 2)));

		static auto Box = reinterpret_cast<void (*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Box"), 2, _("text"), _("UnityEngine"), 2)));

		static auto DrawLine = reinterpret_cast<void (*)(Vector3, Vector3, gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Debug"), _("DrawLine"), 3, _("color"), _("UnityEngine"), 3)));

		static auto set_gizmos_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Gizmos"), _("set_color"), -1, _(""), _("UnityEngine"))));

		static auto HorizontalSlider = reinterpret_cast<float(*)(rust::classes::Rect position, float value, float leftValue, float rightValue)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("HorizontalSlider"), 4, _(""), _("UnityEngine"))));
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

		methods::LoadAllAssets = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAllAssets"), 1, _("type"), _("UnityEngine"), 1)));

		methods::LoadFromFile = reinterpret_cast<uintptr_t(*)(rust::classes::string path)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile"), 1, _("path"), _("UnityEngine"), 1)));
		
		methods::LoadAsset = reinterpret_cast<uintptr_t(*)(uintptr_t bundle, rust::classes::string path, uintptr_t type)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset"), 2, _("name"), _("UnityEngine"), 1)));

		methods::DrawTexture = reinterpret_cast<void (*)(rust::classes::Rect, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("DrawTexture"), 2, _("image"), _("UnityEngine"), 2)));

		methods::Box = reinterpret_cast<void (*)(rust::classes::Rect, rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("GUI"), _("Box"), 2, _("text"), _("UnityEngine"), 2)));

		methods::DrawLine = reinterpret_cast<void (*)(Vector3, Vector3, gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Debug"), _("DrawLine"), 3, _("color"), _("UnityEngine"), 3)));

		methods::set_gizmos_color = reinterpret_cast<void(*)(gui::Color)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Gizmos"), _("set_color"), -1, _(""), _("UnityEngine"))));

		white_texture = methods::get_whiteTexture();
	}

	uintptr_t label, skin;
	bool open;
	bool InsertPressed;
	float opacity = 0.f;
	float tick_time_when_called;

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

		//unity::bundle = methods::LoadFromFile(_(L"rust.assets"));
		//unity::bundle_font = methods::LoadFromFile(_(L"z.mc"));

		if (unity::bundle)
		{
			//unity::chams_shader = methods::LoadAsset(unity::bundle, _(L"Chams"), unity::GetType(_(L"UnityEngine.Shader, UnityEngine.CoreModule")));
		}

		const auto set_font = [&](rust::classes::string str, int sz) {
			//static auto font = methods::LoadAsset(unity::bundle, str, unity::GetType(_(L"UnityEngine.Font, UnityEngine.CoreModule")));
			static auto font = methods::LoadAsset(unity::bundle_font, str, il2cpp::type_object(_("UnityEngine"), _("Font")));
			*reinterpret_cast<uintptr_t*>(skin + 0x18) = font;

			methods::set_fontSize(label, sz);
		};

		//set_font(_(L"minecraftchmc.ttf"), 24);

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
			Label(rust::classes::Rect{ pos.x + 2, pos.y + id * tab_size.y, tab_size.x, tab_size.y }, tab_name,		  rgba(159.f, 163.f, 169.f, 255.f), true, 12);
		}
	}

	const wchar_t* keybind_str;
	int* kbref = 0;
	int* ref_clicked = 0;
	bool getting_keybind = false;


	void checkbox(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* checked_ref, int id, bool keybind = false, int* keybind_ref = 0, Color col = Color(255, 255, 255, 220)) {
		
		std::map<int, const wchar_t*> keycode_str =
		{
			{ 0, L"none" },
			{ 8, L"backspace" },
			{ 127, L"delete" },
			{ 9, L"tab" },
			{ 12, L"clear" },
			{ 13, L"return" },
			{ 19, L"pause" },
			{ 27, L"none" },
			{ 32, L"space" },
			{ 256, L"0" },
			{ 257, L"1" },
			{ 258, L"2" },
			{ 259, L"3" },
			{ 260, L"4" },
			{ 261, L"5" },
			{ 262, L"6" },
			{ 263, L"7" },
			{ 264, L"8" },
			{ 265, L"9" },
			{ 266, L"." },
			{ 267, L"/" },
			{ 268, L"*" },
			{ 269, L"+" },
			{ 270, L"-" },
			{ 271, L"enter" },
			{ 272, L"equals" },
			{ 273, L"up" },
			{ 274, L"down" },
			{ 275, L"right" },
			{ 276, L"left" },
			{ 277, L"ins" },
			{ 278, L"home" },
			{ 279, L"end" },
			{ 280, L"pageup" },
			{ 281, L"pagedown" },
			{ 282, L"f1" },
			{ 283, L"f2" },
			{ 284, L"f3" },
			{ 285, L"f4" },
			{ 286, L"f5" },
			{ 287, L"f6" },
			{ 288, L"f7" },
			{ 289, L"f8" },
			{ 290, L"f9" },
			{ 291, L"f10" },
			{ 292, L"f11" },
			{ 293, L"f12" },
			{ 294, L"f13" },
			{ 295, L"f14" },
			{ 296, L"f15" },
			{ 48, L"0" },
			{ 49, L"1" },
			{ 50, L"2" },
			{ 51, L"3" },
			{ 52, L"4" },
			{ 53, L"5" },
			{ 54, L"6" },
			{ 55, L"7" },
			{ 56, L"8" },
			{ 57, L"9" },
			{ 33, L"!" },
			{ 34, L"\"" },
			{ 35, L"#" },
			{ 36, L"$" },
			{ 37, L"%" },
			{ 38, L"&" },
			{ 39, L"'" },
			{ 40, L"(" },
			{ 41, L")" },
			{ 42, L"*" },
			{ 43, L"+" },
			{ 44, L"," },
			{ 45, L"-" },
			{ 46, L"." },
			{ 47, L"/" },
			{ 58, L":" },
			{ 59, L";" },
			{ 60, L"<" },
			{ 61, L"=" },
			{ 62, L">" },
			{ 63, L"?" },
			{ 64, L"@" },
			{ 91, L"[" },
			{ 92, L"\\" },
			{ 93, L"]" },
			{ 94, L"^" },
			{ 95, L"_" },
			{ 96, L"`" },
			{ 97, L"a" },
			{ 98, L"b" },
			{ 99, L"c" },
			{ 100, L"d" },
			{ 101, L"e" },
			{ 102, L"f" },
			{ 103, L"g" },
			{ 104, L"h" },
			{ 105, L"i" },
			{ 106, L"j" },
			{ 107, L"k" },
			{ 108, L"l" },
			{ 109, L"m" },
			{ 110, L"n" },
			{ 111, L"o" },
			{ 112, L"p" },
			{ 113, L"q" },
			{ 114, L"r" },
			{ 115, L"s" },
			{ 116, L"t" },
			{ 117, L"u" },
			{ 118, L"v" },
			{ 119, L"w" },
			{ 120, L"x" },
			{ 121, L"y" },
			{ 122, L"z" },
			{ 123, L"{" },
			{ 124, L"|" },
			{ 125, L"}" },
			{ 126, L"~" },
			{ 300, L"numlock" },
			{ 301, L"capslock" },
			{ 302, L"scrolllock" },
			{ 303, L"rshift" },
			{ 304, L"lshift" },
			{ 305, L"rcontrol" },
			{ 306, L"lcontrol" },
			{ 307, L"ralt" },
			{ 308, L"lalt" },
			{ 310, L"lcommand" },
			{ 310, L"lapple" },
			{ 311, L"lwindows" },
			{ 309, L"rcommand" },
			{ 309, L"rapple" },
			{ 312, L"rwindows" },
			{ 313, L"altgr" },
			{ 315, L"help" },
			{ 316, L"pr" },
			{ 317, L"sysreq" },
			{ 318, L"break" },
			{ 319, L"menu" },
			{ 323, L"mouse0" },
			{ 324, L"mouse1" },
			{ 325, L"mouse2" },
			{ 326, L"mouse3" },
			{ 327, L"mouse4" },
			{ 328, L"mouse5" },
			{ 329, L"mouse6" }
		};

		pos.x += 5;
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4 + 3 + 2.0f, 100, button_size + 3).Contains(mouse)) {
				*checked_ref = !*checked_ref;
			}
		}

		if (keybind)
		{
			rust::classes::Rect poz = rust::classes::Rect(pos.x + tab_size.x + 100 + 2.0f, pos.y + current_pos.y, 31, 15);
			fill_box(poz, rgba(14.f, 18.f, 24.f, 255.f));
			if (event == rust::classes::EventType::MouseDown) {
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
				gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, keycode_str[*keybind_ref], rgba(249.f, 130.f, 109.f, (opacity / 255.f)), true, 10);
			}
			
			gui::Label({ poz.x + 1, poz.y, poz.wid, poz.hei }, keycode_str[*keybind_ref], rgba(159.f, 163.f, 169.f, (opacity / 255.f)), true, 10);
		}
		
		float o1 = (opacity / 255.f);
		outline_box(Vector2(pos.x + tab_size.x + 3 + 2.0f, pos.y + 7 + current_pos.y - 4), Vector2(10, 10), rgba(14.f, 18.f, 24.f, o1));

		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + 15 + tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, rgba(0, 0, 0, (opacity / 255.f)), false, 14);
			if (*checked_ref) {
				fill_box(rust::classes::Rect{ pos.x + tab_size.x + 3 + 2.0f, pos.y + 7 + current_pos.y - 4, 10, 10 }, rgba(14.f, 18.f, 24.f, (opacity / 255.f)));
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
	}

	void buttonvis(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void buttoninv(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void buttonteam(rust::classes::EventType event, Vector2 pos, Vector2& current_pos, Vector2 mouse, const wchar_t* button_name, bool* out, int id, Color col = Color(settings::visuals::TeamRcolor, settings::visuals::TeamGcolor, settings::visuals::TeamBcolor, 1)) {
		const float button_size = 20;
		if (event == rust::classes::EventType::MouseDown) {
			if (rust::classes::Rect(pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 100, button_size + 3).Contains(mouse)) {
				*out = !*out;
			}
		}


		if (event == rust::classes::EventType::Repaint) {
			gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f + 1, pos.y + current_pos.y - 4 + 1, 200, button_size + 3 }, button_name, gui::Color(0, 0, 0, 120), false, 10);
			if (*out) {
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::TeamRcolor, settings::visuals::TeamGcolor, settings::visuals::TeamBcolor, 1), false, 10);
			}
			else
				gui::Label(rust::classes::Rect{ pos.x + id * tab_size.x + 3 + 2.0f, pos.y + current_pos.y - 4, 200, button_size + 3 }, button_name, Color(settings::visuals::TeamRcolor, settings::visuals::TeamGcolor, settings::visuals::TeamBcolor, 1), false, 10);
		}
		current_pos.y += button_size;
	}

	void Slider(rust::classes::EventType event, Vector2 pos, Vector2 mouse, uintptr_t text, Vector2& current_pos, float& out, float max, int id, float font_size = 0, const char* fmt = _("%.1f"))
	{
		pos.x += 100;
		pos.y += 4;
		const float button_size = 8;

		int wid = 150;

		int pzx = pos.x + id + 3 + 2.0f + 1;

		rust::classes::Rect pz = rust::classes::Rect(pzx, pos.y + current_pos.y - 4 + 1, wid, button_size);

		//if mouse within box highlight thumb
		//if mouse down within box, set thumb to position

		if (event == rust::classes::EventType::MouseDown) {
			if (pz.Contains(mouse)) {
				out = (((pos.x + 7) - mouse.x) * (max/wid)) * -1;
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

		current_pos.y += button_size + 5;
	}

	void Progbar(Vector2 start, Vector2 end, float a, float b)
	{
		fill_box(rust::classes::Rect(start.x, start.y, end.x, end.y + 1), rgba(21.f, 27.f, 37.f, 255.f));

		if (a < 0) a = 0;
		if ((a / b) > b)
			a = b;

		fill_box(rust::classes::Rect(start.x + 1, start.y + 1, (end.x * (a / b)) - 1, end.y - 1), perc_col(a/b));
	}

	float out;

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

		if (event_type == rust::classes::EventType::KeyDown || event_type == rust::classes::EventType::KeyUp) {
			rust::classes::KeyCode cur = unity::get_keyCode(current);
			if (event_type == rust::classes::EventType::KeyDown)
				OnKeyDown(cur);
			else
				OnKeyUp(cur);
		}

		auto mouse = get_mousePosition();
		auto height = unity::get_height();

		Vector2 pos, menu_pos = { 650, 200 }, menu_size = { 500, 330 }, button_size = { 200, 0 }, mouse_pos = { mouse.x, height - mouse.y };

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

				if (settings::misc::Crosshair) {
					//gui::vertical_line(vector2{ (float)(ScreenWidth / 2), (float)(ScreenHeight / 2 + 2) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::vertical_line(vector2{ (float)(ScreenWidth / 2), (float)((ScreenHeight / 2)) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::horizontal_line(vector2{ (float)(ScreenWidth / 2 + 2), (float)(ScreenHeight / 2) }, 4.f, gui::Color(1, 0, 0, 0.5));
					//gui::horizontal_line(vector2{ (float)((ScreenWidth / 2) - 1),(float)(ScreenHeight / 2) }, 4.f, gui::Color(1, 0, 0, 0.5));


					gui::vertical_line(Vector2{ (float)(ScreenWidth / 2), (float)(ScreenHeight / 2) }, 1.f, gui::Color(1, 0, 0, 1));
				}

				if (esp::local_player)
				{
					float bars = 0;
					if (settings::visuals::desync_indicator)
					{
						Progbar({ 900, (650 + (bars++ * 10)) }, { 120, 4 }, settings::desyncTime, 1.0f);
					}
					//put extra gui things here
					auto held = esp::local_player->get_active_weapon();
					if (settings::weapon::always_reload)
					{
						if (held->get_base_projectile())
						{
							auto b = held->get_base_projectile();
							Progbar({ 900, (650 + (bars++ * 10)) }, { 120, 4 }, settings::time_since_last_shot, (b->get_reload_time() - (b->get_reload_time() / 10)));
						}
					}
				}

				esp::start();
			}
		}

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

				outline_box({ menu_pos.x - 1, menu_pos.y - 1 }, { menu_size.x + 1, menu_size.y + 1}, rgba(249.f, 130.f, 109.f, 255.f));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y + 30, menu_size.x, menu_size.y - 30 }, rgba(21.f, 27.f, 37.f, 255));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y, menu_size.x, 30 }, rgba(14.f, 18.f, 24.f, 255));
				fill_box(rust::classes::Rect{ menu_pos.x, menu_pos.y + 30, tab_size.x + 2, menu_size.y - 30 }, rgba(14.f, 18.f, 24.f, 255));

				//MENU TIME

				gui::Label(rust::classes::Rect{ menu_pos.x + 2.0f + 1, menu_pos.y - 4 + 1, menu_size.x, 30 }, _(L"K4"), gui::Color( 1, 1, 1, 1), true, 16);

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

				if (settings::misc::code_lock_code < 1000)
					settings::misc::code_lock_code = 1000;
				else if (settings::misc::code_lock_code > 9999)
					settings::misc::code_lock_code = 9999;

				switch (active_tab) {
				case 0:
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"PSilent"), &settings::weapon::psilent, weapon_tab, true, &settings::keybind::psilent);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Fov")), pos, settings::weapon::aimbotfov, 2500.f, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent melee"), &settings::weapon::silent_melee, weapon_tab, true, &settings::keybind::silentmelee);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Thick bullet"), &settings::weapon::thick_bullet, weapon_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Size")), pos, settings::weapon::thickness, 1.f, weapon_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Removals"), &settings::weapon::weapon_removals, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Legit recoil"), &settings::weapon::legit_recoil, weapon_tab); //
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Recoil"), &settings::weapon::norecoil, weapon_tab);		 // make into slider?
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Spread"), &settings::weapon::nospread, weapon_tab);		 //
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No Sway"), &settings::weapon::nosway, weapon_tab); //doesnt work?
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Automatic"), &settings::weapon::automatic, weapon_tab);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Force head"), &settings::weapon::hitbox_override, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Force random"), &settings::weapon::random_hitbox, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Rapid fire"), &settings::weapon::rapidfire, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Fast bullet"), &settings::weapon::fast_bullet, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Bullet tp"), &settings::weapon::bullet_tp, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Autoshoot"), &settings::weapon::autoshoot, weapon_tab, true, &settings::keybind::autoshoot);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Manipulator"), &settings::weapon::manipulator, weapon_tab, true, &settings::keybind::manipulator);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Double-tap"), &settings::weapon::doubletap, weapon_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Always reload"), &settings::weapon::always_reload, weapon_tab);
					break;
				case 1:
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Desync indicator"), &settings::visuals::desync_indicator, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Players"), &settings::visuals::player_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Full Box"), &settings::visuals::full_box, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Corner Box"), &settings::visuals::corner_box, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Crosshair Health"), &settings::visuals::midhealth, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Crosshair Name"), &settings::visuals::midname, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Name"), &settings::visuals::nameesp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Distance"), &settings::visuals::distance, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Wounded"), &settings::visuals::woundedflag, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Weapon Esp"), &settings::visuals::weaponesp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Hotbar Esp"), &settings::visuals::hotbar_esp, visual_tab);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Bottom healthbar"), &settings::visuals::bottomhealth, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Side healthbar"), &settings::visuals::sidehealth, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Chams"), &settings::visuals::chams, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Rainbow chams"), &settings::visuals::rainbow_chams, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Sleeper"), &settings::visuals::sleeper_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"NPC"), &settings::visuals::npc_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Corpse"), &settings::visuals::corpses, visual_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Misc"), &settings::visuals::misc_esp, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Held sprites"), &settings::visuals::spriteitem, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Snaplines"), &settings::visuals::snaplines, visual_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Show fov"), &settings::visuals::show_fov, visual_tab);
					break;
				case 2:
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Materials"), &settings::visuals::materials, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Stone ore"), &settings::visuals::stone_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Metal ore"), &settings::visuals::metal_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Sulfur ore"), &settings::visuals::sulfur_ore, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Cloth"), &settings::visuals::cloth, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Vehicles"), &settings::visuals::vehicles, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Patrol-heli"), &settings::visuals::heli_esp, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Dropped items"), &settings::visuals::dropped_items, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Stashes"), &settings::visuals::stash, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Airdrops"), &settings::visuals::airdrops, other_esp);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Traps"), &settings::visuals::traps, other_esp);
					//button(event_type, menu_pos, pos, mouse_pos, _(L"Toolcupboard Esp"), &settings::visuals::tc_esp, other_esp);
					break;
				case 3:
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Player Movement"), &settings::misc::Movement, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Omnisprint"), &settings::misc::always_sprint, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Can hold items"), &settings::weapon::always_shoot, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Infinite jump"), &settings::misc::infinite_jump, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Timescale"), &settings::misc::speedhack, misc_tab, true, &settings::keybind::timescale);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Scale")), pos, settings::misc::speedhackspeed, 10.f, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Spiderman"), &settings::misc::spiderman, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Big jump"), &settings::misc::gravity, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Shoot while mounted"), &settings::misc::attack_on_mountables, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent farm"), &settings::misc::silent_farm, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Silent walk"), &settings::misc::silentwalk, misc_tab, true, &settings::keybind::silentwalk);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Spinbot"), &settings::misc::spinbot, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Fake lag"), &settings::misc::fake_lag, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Desync"), &settings::misc::desync, misc_tab, true, &settings::keybind::desync_ok);

					menu_pos.x += 170;
					pos.y = 0; //?

					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Admin mode"), &settings::misc::admin_mode, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"No collisions"), &settings::misc::no_playercollision, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Instant med"), &settings::misc::instant_med, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Suicide"), &settings::misc::TakeFallDamage, misc_tab, true, &settings::keybind::suicide);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Longneck"), &settings::misc::eyeoffset, misc_tab, true, &settings::keybind::neck);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Size")), pos, settings::misc::playereyes, 1.5f, misc_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Player FOV"), &settings::misc::playerfovtoggle, misc_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Player fov")), pos, settings::misc::playerfov, 150, misc_tab);
					checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Zoom"), &settings::misc::zoomtoggle, misc_tab, true, &settings::keybind::zoom);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Zoom fov")), pos, settings::misc::zoomfov, 50, misc_tab);
					//checkbox(event_type, menu_pos, pos, mouse_pos, _(L"Brightnight"), &settings::misc::brightnight, misc_tab);
					Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(_("Stars")), pos, settings::misc::staramount, 1000, misc_tab);
					break;
				case 4:
					buttonvis(event_type, menu_pos, pos, mouse_pos, _(L"Visible color"), &settings::misc::trollface, color_tab, Color(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1)); {
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)settings::visuals::VisRcolor)), pos, settings::visuals::VisRcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)settings::visuals::VisGcolor)), pos, settings::visuals::VisGcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)settings::visuals::VisBcolor)), pos, settings::visuals::VisBcolor, 1.f, color_tab);
					}

					buttoninv(event_type, menu_pos, pos, mouse_pos, _(L"Invisible color"), &settings::misc::trollface, color_tab, Color(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1)); {
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)settings::visuals::InvRcolor)), pos, settings::visuals::InvRcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)settings::visuals::InvGcolor)), pos, settings::visuals::InvGcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)settings::visuals::InvBcolor)), pos, settings::visuals::InvBcolor, 1.f, color_tab);
					}
					buttonteam(event_type, menu_pos, pos, mouse_pos, _(L"Teammate color"), &settings::misc::trollface, color_tab, Color(settings::visuals::TeamRcolor, settings::visuals::TeamGcolor, settings::visuals::TeamBcolor, 1)); {
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)settings::visuals::TeamRcolor)), pos, settings::visuals::TeamRcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)settings::visuals::TeamGcolor)), pos, settings::visuals::TeamGcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)settings::visuals::TeamBcolor)), pos, settings::visuals::TeamBcolor, 1.f, color_tab);
					}
					buttonteam(event_type, menu_pos, pos, mouse_pos, _(L"Name color"), &settings::misc::trollface, color_tab, Color(settings::visuals::nameRcolor, settings::visuals::nameGcolor, settings::visuals::nameBcolor, 1)); {
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("R:"), (int)settings::visuals::nameRcolor)), pos, settings::visuals::nameRcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("G:"), (int)settings::visuals::nameGcolor)), pos, settings::visuals::nameGcolor, 1.f, color_tab);
						Slider(event_type, menu_pos, mouse_pos, il2cpp::methods::new_string(string::format(("%s %d"), _("B:"), (int)settings::visuals::nameBcolor)), pos, settings::visuals::nameBcolor, 1.f, color_tab);
					}
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
								if (settings::visuals::hotbar_esp) {
									gui::fill_box({ 661 + info_y, (unity::get_height() * 0.8f), 90, 90 }, { 0, 0, 0, 0.12 });

									gui::methods::set_color({ 1, 1, 1, 1 });
									gui::methods::DrawTexture({ 663 + info_y, (unity::get_height() * 0.8f) + 5, rect.wid / 3.0f, rect.hei / 3.0f }, texture);
									gui::Label(rust::classes::Rect{ x + 2.0f + 1, info_y - 4 + 13 + 1 + (unity::get_height() * 0.75f), width - 10, height / current_item }, item_name, gui::Color(0, 0, 0, 120), true, 12);
									gui::Label(rust::classes::Rect{ x + 2.0f, info_y - 4 + 13 + (unity::get_height() * 0.75f), width - 10, height / current_item }, item_name, gui::Color(255, 255, 255, 220), true, 12);

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
			if (settings::visuals::midname && settings::misc::Crosshair) {
				//draw player name dropshadow
				gui::Label(rust::classes::Rect{ 861, 442 , 200, 260 }, target.player->get_player_name(), gui::Color(0, 0, 0, 1), true, 12);
				// draw player name
				gui::Label(rust::classes::Rect{ 862, 441, 200, 260 }, target.player->get_player_name(), gui::Color(1, 1, 1, 1), true, 12);
			}
			if (settings::visuals::midhealth && settings::misc::Crosshair) {
				const auto cur_health = target.player->get_health();
				//draw player health dropshadow
				gui::Label(rust::classes::Rect{ 861 , 457, 200, 260 }, il2cpp::methods::new_string(string::format(("[%.f]"), cur_health)), gui::Color(0, 0, 0, 1), true, 10);
				//draw player health
				gui::Label(rust::classes::Rect{ 862 , 456, 200, 260 }, il2cpp::methods::new_string(string::format(("[%.f]"), cur_health)), gui::Color(1, 1, 1, 1), true, 10);
			}
		}
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

	void do_chams(base_player* player)
	{
		if (settings::visuals::chams) {
			static int cases = 0;
			static float r = 1.00f, g = 0.00f, b = 1.00f;
			switch (cases) {
			case 0: { r -= 0.0004f; if (r <= 0) cases += 1; break; }
			case 1: { g += 0.0004f; b -= 0.0004f; if (g >= 1) cases += 1; break; }
			case 2: { r += 0.0004f; if (r >= 1) cases += 1; break; }
			case 3: { b += 0.0004f; g -= 0.0004f; if (b >= 1) cases = 0; break; }
			default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
			}
			auto _multiMesh = mem::read<uintptr_t>(player->get_player_model() + 0x2D0); //SkinnedMultiMesh _multiMesh;
			if (_multiMesh) {
				auto render = get_Renderers(_multiMesh);

				for (int i = 0; i < render->get_size(); i++) {
					auto renderer = render->get_value(i);

					//////// CHAMMINGS ///////

					if (renderer) {
						auto material = get_material(renderer);
						if (material) {
							if (!shader)
								shader = Find(_(L"Hidden/Internal-Colored"));
							unity::set_shader(material, shader);
							SetInt(material, _(L"_ZTest"), 8); // through walls

							if (settings::visuals::rainbow_chams) {
								SetColor(material, _(L"_Color"), col(r, g, b, 1));
							}
							else if (get_IsNpc(player->get_player_model()) && player->is_visible(local_player->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position(), player->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position())) {
								SetColor(material, _(L"_Color"), col(0, 0.5, 1, 0.5));
							}
							else if (get_IsNpc(player->get_player_model())) {
								SetColor(material, _(L"_Color"), col(0, 0, 0.6, 0.5));
							}
							else if (get_IsNpc(player->get_player_model())) {
								SetColor(material, _(L"_Color"), col(0, 0, 0.6, 0.5));
							}
							else if (player->is_teammate(local_player)) {
								SetColor(material, _(L"_Color"), col(0, 1, 1, 1));
							}
							else if (player->is_visible(local_player->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position(), player->get_bone_transform((int)rust::classes::Bone_List::head)->get_bone_position())) {
								SetColor(material, _(L"_Color"), col(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1));
							}
							else {
								SetColor(material, _(L"_Color"), col(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1));
							}
						}
					}
				}
			}
		}
	}

	void draw_player(base_player* player, bool is_npc)
	{
		if (!local_player)
			return;

		do_chams(player);

		//   esp colors
		auto visible_color = gui::Color(settings::visuals::VisRcolor, settings::visuals::VisGcolor, settings::visuals::VisBcolor, 1);
		auto invisible_color = gui::Color(settings::visuals::InvRcolor, settings::visuals::InvGcolor, settings::visuals::InvBcolor, 1);
		auto teammate_color = gui::Color(settings::visuals::TeamRcolor, settings::visuals::TeamGcolor, settings::visuals::TeamBcolor, 1);
		auto safezone_color = gui::Color{ 249.f/255.f, 130.f/255.f, 109.f/255.f, 1.0 };
		bounds_t bounds;

		struct bone_t {
			Vector3 screen;
			int8_t     index;
			bool       on_screen;
			Vector3 world_position;
			bool visible;
		};

		std::array<bone_t, 20> bones = {
			bone_t{ Vector3{}, 17, false, Vector3{}, false }, bone_t{ Vector3{}, 18, false, Vector3{}, false },
			bone_t{ Vector3{}, 15, false, Vector3{}, false }, bone_t{ Vector3{}, 14, false, Vector3{}, false },
			bone_t{ Vector3{}, 1, false, Vector3{}, false },  bone_t{ Vector3{}, 2, false, Vector3{}, false },
			bone_t{ Vector3{}, 3, false, Vector3{}, false },  bone_t{ Vector3{}, 6, false, Vector3{}, false },
			bone_t{ Vector3{}, 5, false, Vector3{}, false },  bone_t{ Vector3{}, 21, false, Vector3{}, false },
			bone_t{ Vector3{}, 23, false, Vector3{}, false }, bone_t{ Vector3{}, 48, false, Vector3{}, false },
			bone_t{ Vector3{}, 24, false, Vector3{}, false }, bone_t{ Vector3{}, 25, false, Vector3{}, false },
			bone_t{ Vector3{}, 26, false, Vector3{}, false }, bone_t{ Vector3{}, 27, false, Vector3{}, false },
			bone_t{ Vector3{}, 55, false, Vector3{}, false }, bone_t{ Vector3{}, 56, false, Vector3{}, false },
			bone_t{ Vector3{}, 57, false, Vector3{}, false }, bone_t{ Vector3{}, 76, false, Vector3{}, false }
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
			if (!is_visible)
				is_visible = player->is_visible(camera_position, bones[16].world_position);

			gui::Color clr = !is_teammate ? (is_visible ? visible_color : invisible_color) : teammate_color;
			if (HasPlayerFlag(player, rust::classes::PlayerFlags::SafeZone))
				clr = safezone_color;

			float box_width = bounds.right - bounds.left;
			float box_height = bounds.bottom - bounds.top;

			const float ScreenWidth = 1920;
			const float ScreenHeight = 1080;
			if (settings::misc::Crosshair) {
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

			if (settings::visuals::full_box && settings::visuals::boxesp) {
				//full box
				gui::outline_box(Vector2{ bounds.left - 1, bounds.top - 1 }, Vector2{ box_width + 2, box_height + 2 }, gui::Color(0, 0, 0, 120));
				gui::outline_box(Vector2{ bounds.left, bounds.top }, Vector2{ box_width, box_height }, clr);
				gui::outline_box(Vector2{ bounds.left + 1, bounds.top + 1 }, Vector2{ box_width - 2, box_height - 2 }, gui::Color(0, 0, 0, 120));
				//full box
			}

			if (settings::visuals::corner_box && settings::visuals::boxesp) {
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
			if (settings::visuals::bottomhealth) {
				gui::fill_box(rust::classes::Rect(bounds.left, bounds.bottom + 6, box_width + 1, 6), gui::Color(0, 0, 0, 120));
				gui::fill_box(rust::classes::Rect(bounds.left + 2, bounds.bottom + 8, ((box_width / max_health) * cur_health) - 2, 2), health_color);
				//gui::Label(rust::classes::Rect{ bounds.left, bounds.bottom + 10, box_width, box_width / 2 }, il2cpp::methods::new_string(string::format(("%.f"), cur_health)), gui::Color(255, 255, 255, 220), false, box_width / 3);
				//HEALTH NUMBER UNDER BAR ^^^^^^^^^^^^^ LAGGY
			}
			if (settings::visuals::sidehealth) {
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
					if (settings::visuals::spriteitem) {
						gui::methods::set_color({ 1, 1, 1, 1 });
						gui::methods::DrawTexture({ bounds.right + 2.0f + 1, bounds.top - 4 + 13 + 1, rect.wid / 7, rect.hei / 7 }, texture);
					}
				}
				float half = (bounds.right - bounds.left) / 2;
				auto weapon_name = player_weapon->get_weapon_name();
				if (weapon_name)
				{
					// WEAPON NAME ESP
					if (settings::visuals::weaponesp) {
						auto half = (bounds.right - bounds.left) / 2;
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 1.f, 80.f + half * 2 + 80.f , 20 }, weapon_name, gui::Color(0, 0, 0, 120), true, 10.5);
						gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 0.f, 80.f + half * 2 + 79.f , 20 }, weapon_name, gui::Color(249.f / 255.f, 130.f / 255.f, 109.f / 255.f, 1), true, 10);
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

				std::wstring nw(name);

				if (settings::visuals::nameesp) {
					auto half = (bounds.right - bounds.left) / 2;

					if (settings::visuals::woundedflag) {

						const wchar_t* woundedlol = L"[Wounded]";

						if (HasPlayerFlag(player, rust::classes::PlayerFlags::Wounded)) {

							//outline 
							gui::Label(rust::classes::Rect{ bounds.left - 79.5f  , bounds.top - 17.f, 79.f + half * 2 + 79.5f , 20 }, woundedlol, gui::Color(0, 0, 0, 120), true, 9.5);
							//actual text
							gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.top - 18.f, 80.f + half * 2 + 80.f , 20 }, woundedlol, gui::Color(0.9,0.9,0.1, 1), true, 9);
						}

					}

					if (settings::visuals::distance)
					{
						
						//std::string d = _("[") + std::to_string((int)distance);
						//nw = nw + _(L"\n") + std::wstring(d.begin(), d.end()) + _(L"m]");
					}


					gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 7.f, 79.f + half * 2 + 80.f , 30 }, nw.c_str(), gui::Color(0, 0, 0, 120), true, 10.5);
					gui::Label(rust::classes::Rect{ bounds.left - 80.f  , bounds.bottom + 8.f, 80.f + half * 2 + 80.f , 30 }, nw.c_str(), gui::Color(settings::visuals::nameRcolor, settings::visuals::nameGcolor, settings::visuals::nameBcolor, 1), true, 10);
				}
				// PLAYER NAME
			}
		}
	}
}