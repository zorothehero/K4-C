#pragma once

//keys: A-Z Mouse0-6 0-9

namespace keybinds {
	auto psilentk = rust::classes::KeyCode::Mouse4; // the bind
	bool psilentb = false; //if you want the bind enable or not
	auto speedhackk = rust::classes::KeyCode::X;
	bool speedhackb = true;
	auto silentwalkk = rust::classes::KeyCode::Mouse2;
	bool silentwalkb = true;
	auto fakelagk = rust::classes::KeyCode::Z;
	bool fakelagb = false;
	auto desynconk = rust::classes::KeyCode::C;
	bool desynconb = true;

	auto manipulate_key = rust::classes::KeyCode::Mouse3;
}