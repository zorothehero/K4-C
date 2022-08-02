#pragma once
#include "../utils/vector.hpp"
#include "../memory/il2cpp.hpp"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define member(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define min(a,b)            (((a) < (b)) ? (a) : (b))

struct Ray {
	Vector3 origin;
	Vector3 dir;
	Ray() { }
	Ray(Vector3 o, Vector3 d) {
		origin = o;
		dir = d;
	}
};

namespace System {
	template<typename T = void*>
	class Array {
	public:
		uint32_t size() {
			if (!this) return 0;
			return *reinterpret_cast<uint32_t*>(this + 0x18);
		}
		T get(int idx) {
			if (!this) return T{};
			return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
		}
		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};

	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}

		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};

	class string {
	public:
		char zpad[0x10];
		int size;
		wchar_t str[128 + 1];
		string() {}
		string(const wchar_t* st) {
			size = min(m_wcslen((wchar_t*)st), 128);
			for (int i = 0; i < size; i++) {
				str[i] = st[i];
			}
			str[size] = 0;
		}
	};
}

namespace protobuf {
	enum class HitTestType
	{
		Generic = 0,
		ProjectileEffect = 1,
		Projectile = 2,
		MeleeAttack = 3,
		Use = 4,
	};

	class Attack {
	public:
		union {
			member(Vector3, pointStart, 0x14);
			member(Vector3, pointEnd, 0x18);
			member(unsigned int, hitID, 0x2C);
			member(unsigned int, hitBone, 0x30);
			member(Vector3, hitNormalLocal, 0x34);
			member(Vector3, hitPositionLocal, 0x40);
			member(Vector3, hitNormalWorld, 0x4C);
			member(Vector3, hitPositionWorld, 0x48);
			member(unsigned int, hitPartID, 0x64);
			member(unsigned int, hitMaterialID, 0x68);
			member(unsigned int, hitItem, 0x6C);
		};
	};

	class InputMessage {
	public:
		member(bool, ShouldPool, 0x10);
		member(bool, _disposed, 0x11);
		member(int, buttons, 0x14);
		member(Vector3, aimAngles, 0x18);
		member(Vector3, mouseDelta, 0x24);
	};

	class PlayerTick {
	public:
		member(bool, ShouldPool, 0x10);
		member(bool, _disposed, 0x11);
		member(InputMessage*, inputState, 0x18);
		member(Vector3, position, 0x20);
		//DEFINE_MEMBER_N(modelstate*, modelState, 0x30);
		member(uintptr_t, modelState, 0x30);
		member(UINT, activeItem, 0x38);
		member(Vector3, eyePos, 0x3C);
		member(UINT, parentID, 0x48);
		member(UINT, deltaMs, 0x4C);
	};

	class PlayerAttack {
	public:
		union {
			member(Attack*, attack, 0x18);
		};
	};

	class CreateBuilding {
	public:
		bool ShouldPool; // 0x10
		bool _disposed; // 0x11
		unsigned int entity; // 0x14
		unsigned int socket; // 0x18
		bool onterrain; // 0x1C
		Vector3 position; // 0x20
		Vector3 normal; // 0x2C
		Ray ray; // 0x38
		unsigned int blockID; // 0x50
		Vector3 rotation; // 0x54
	};

	class PlayerProjectileAttack {
	public:
		union {
			member(PlayerAttack*, playerAttack, 0x18);
			member(Vector3, hitVelocity, 0x20);
			member(float, hitDistance, 0x2C);
			member(float, travelTime, 0x30);
		};
	};

	class PlayerProjectileRicochet {
	public:
		union {
			member(Vector3, hitPosition, 0x18);
			member(Vector3, inVelocity, 0x24);
			member(Vector3, outVelocity, 0x30);
			member(Vector3, hitNormal, 0x3C);
		};
	};

	class PlayerProjectileUpdate {
	public:
		union {
			member(int, projectileID, 0x14);
			member(Vector3, position, 0x18);
			member(Vector3, velocity, 0x24);
			member(float, traveltime, 0x30);
		};
	};
}

namespace rust {
	namespace classes {
		enum class Signal {
			Attack,
			Alt_Attack,
			DryFire,
			Reload,
			Deploy,
			Flinch_Head,
			Flinch_Chest,
			Flinch_Stomach,
			Flinch_RearHead,
			Flinch_RearTorso,
			Throw,
			Relax,
			Gesture,
			PhysImpact,
			Eat,
			Startled
		};
		enum BUTTON : uint32_t {
			FORWARD = 2,
			BACKWARD = 4,
			LEFT = 8,
			RIGHT = 16,
			JUMP = 32,
			DUCK = 64,
			SPRINT = 128,
			USE = 256,
			FIRE_PRIMARY = 1024,
			FIRE_SECONDARY = 2048,
			RELOAD = 8192,
			FIRE_THIRD = 134217728
		};

		enum class layer : uint32_t {
			Default = 0,
			TransparentFX = 1,
			Ignore_Raycast = 2,
			Reserved1 = 3,
			Water = 4,
			UI = 5,
			Reserved2 = 6,
			Reserved3 = 7,
			Deployed = 8,
			Ragdoll = 9,
			Invisible = 10,
			AI = 11,
			PlayerMovement = 12,
			Vehicle_Detailed = 13,
			Game_Trace = 14,
			Vehicle_World = 15,
			World = 16,
			Player_Server = 17,
			Trigger = 18,
			Player_Model_Rendering = 19,
			Physics_Projectile = 20,
			Construction = 21,
			Construction_Socket = 22,
			Terrain = 23,
			Transparent = 24,
			Clutter = 25,
			Debris = 26,
			Vehicle_Large = 27,
			Prevent_Movement = 28,
			Prevent_Building = 29,
			Tree = 30,
			Unused2 = 31
		};

		enum objects
		{
			MAINCAMERA = 5,
			PLAYER = 6,
			TERRAIN = 20001,
			CORPSE = 20009, //Animals & Players
			MISC = 20006, //Trash cans, Sleeping Bags, Storage Box, etc
			ANIMAL = 20008,
			SKYDOME = 20012,
			RIVERMESH = 20014,
			MONUMENT = 20015 //Airport, Powerplant, etc
		};

		enum class Layers
		{
			Terrain = 8388608,
			World = 65536,
			Ragdolls = 512,
			Construction = 2097152,
			ConstructionSocket = 4194304,
			Craters = 1,
			GameTrace = 16384,
			Trigger = 262144,
			VehiclesDetailed = 8192,
			RainFall = 1101070337,
			Deploy = 1235288065,
			DefaultDeployVolumeCheck = 537001984,
			BuildLineOfSightCheck = 2097152,
			ProjectileLineOfSightCheck = 2162688,
			ProjectileLineOfSightCheckTerrain = 10551296,
			MeleeLineOfSightCheck = 2162688,
			EyeLineOfSightCheck = 2162688,
			EntityLineOfSightCheck = 1218519041,
			PlayerBuildings = 18874624,
			PlannerPlacement = 161546496,
			Solid = 1218652417,
			VisCulling = 10551297,
			AltitudeCheck = 1218511105,
			HABGroundEffect = 1218511105,
			AILineOfSight = 1218519297,
			DismountCheck = 1486946561,
			AIPlacement = 278986753,
			WheelRay = 1235321089,
			z = 1503731969,
		};

		enum class BuildingGrade
		{
			None = -1,
			Twigs = 0,
			Wood = 1,
			Stone = 2,
			Metal = 3,
			TopTier = 4,
			Count = 5
		};

		enum class Bone_List : int
		{
			// assets / prefabs / player / player_mod = 0,
			pelvis = 1,
			l_hip = 2,
			l_knee = 3,
			l_foot = 4,
			l_toe = 5,
			l_ankle_scale = 6,
			penis = 7,
			GenitalCensor = 8,
			GenitalCensor_LOD0 = 9,
			Inner_LOD0 = 10,
			GenitalCensor_LOD1 = 11,
			GenitalCensor_LOD2 = 12,
			r_hip = 13,
			r_knee = 14,
			r_foot = 15,
			r_toe = 16,
			r_ankle_scale = 17,
			spine1 = 18,
			spine1_scale = 19,
			spine2 = 20,
			spine3 = 21,
			spine4 = 22,
			l_clavicle = 23,
			l_upperarm = 24,
			l_forearm = 25,
			l_hand = 26,
			l_index1 = 27,
			l_index2 = 28,
			l_index3 = 29,
			l_little1 = 30,
			l_little2 = 31,
			l_little3 = 32,
			l_middle1 = 33,
			l_middle2 = 34,
			l_middle3 = 35,
			l_prop = 36,
			l_ring1 = 37,
			l_ring2 = 38,
			l_ring3 = 39,
			l_thumb1 = 40,
			l_thumb2 = 41,
			l_thumb3 = 42,
			IKtarget_righthand_min = 43,
			IKtarget_righthand_max = 44,
			l_ulna = 45,
			neck = 46,
			head = 47,
			jaw = 48,
			eyeTranform = 49,
			l_eye = 50,
			l_Eyelid = 51,
			r_eye = 52,
			r_Eyelid = 53,
			r_clavicle = 54,
			r_upperarm = 55,
			r_forearm = 56,
			r_hand = 57,
			r_index1 = 58,
			r_index2 = 59,
			r_index3 = 60,
			r_little1 = 61,
			r_little2 = 62,
			r_little3 = 63,
			r_middle1 = 64,
			r_middle2 = 65,
			r_middle3 = 66,
			r_prop = 67,
			r_ring1 = 68,
			r_ring2 = 69,
			r_ring3 = 70,
			r_thumb1 = 71,
			r_thumb2 = 72,
			r_thumb3 = 73,
			IKtarget_lefthand_min = 74,
			IKtarget_lefthand_max = 75,
			r_ulna = 76,
			l_breast = 77,
			r_breast = 78,
			BoobCensor = 79,
			BreastCensor_LOD0 = 80,
			BreastCensor_LOD1 = 81,
			BreastCensor_LOD2 = 82,
			collision = 83,
			displacement = 84
		};

		class list {
		public:
			template <typename T>
			T get_value() {
				auto list = *reinterpret_cast<uintptr_t*>(this + 0x10);
				if (!list)
					return 0;

				auto value = *reinterpret_cast<T*>(list + 0x28);
				if (!value)
					return 0;
				return value;
			}

			int get_size() {
				auto value = get_value<uintptr_t>();
				if (!value)
					return 0;

				auto size = mem::read<int>(value + 0x10);
				if (!size)
					return 0;
			}

			template <typename T>
			T get_buffer() {
				auto value = get_value<uintptr_t>();

				return *reinterpret_cast<uintptr_t*>(value + 0x18);
			}
		};

		enum class KeyCode
		{
			Backspace = 8,
			Delete = 127,
			Tab = 9,
			Clear = 12,
			Return = 13,
			Pause = 19,
			Escape = 27,
			Space = 32,
			Keypad0 = 256,
			Keypad1 = 257,
			Keypad2 = 258,
			Keypad3 = 259,
			Keypad4 = 260,
			Keypad5 = 261,
			Keypad6 = 262,
			Keypad7 = 263,
			Keypad8 = 264,
			Keypad9 = 265,
			KeypadPeriod = 266,
			KeypadDivide = 267,
			KeypadMultiply = 268,
			KeypadMinus = 269,
			KeypadPlus = 270,
			KeypadEnter = 271,
			KeypadEquals = 272,
			UpArrow = 273,
			DownArrow = 274,
			RightArrow = 275,
			LeftArrow = 276,
			Insert = 277,
			Home = 278,
			End = 279,
			PageUp = 280,
			PageDown = 281,
			F1 = 282,
			F2 = 283,
			F3 = 284,
			F4 = 285,
			F5 = 286,
			F6 = 287,
			F7 = 288,
			F8 = 289,
			F9 = 290,
			F10 = 291,
			F11 = 292,
			F12 = 293,
			F13 = 294,
			F14 = 295,
			F15 = 296,
			Alpha0 = 48,
			Alpha1 = 49,
			Alpha2 = 50,
			Alpha3 = 51,
			Alpha4 = 52,
			Alpha5 = 53,
			Alpha6 = 54,
			Alpha7 = 55,
			Alpha8 = 56,
			Alpha9 = 57,
			Exclaim = 33,
			DoubleQuote = 34,
			Hash = 35,
			Dollar = 36,
			Percent = 37,
			Ampersand = 38,
			Quote = 39,
			LeftParen = 40,
			RightParen = 41,
			Asterisk = 42,
			Plus = 43,
			Comma = 44,
			Minus = 45,
			Period = 46,
			Slash = 47,
			Colon = 58,
			Semicolon = 59,
			Less = 60,
			Equals = 61,
			Greater = 62,
			Question = 63,
			At = 64,
			LeftBracket = 91,
			Backslash = 92,
			RightBracket = 93,
			Caret = 94,
			Underscore = 95,
			BackQuote = 96,
			A = 97,
			B = 98,
			C = 99,
			D = 100,
			E = 101,
			F = 102,
			G = 103,
			H = 104,
			I = 105,
			J = 106,
			K = 107,
			L = 108,
			M = 109,
			N = 110,
			O = 111,
			P = 112,
			Q = 113,
			R = 114,
			S = 115,
			T = 116,
			U = 117,
			V = 118,
			W = 119,
			X = 120,
			Y = 121,
			Z = 122,
			LeftCurlyBracket = 123,
			Pipe = 124,
			RightCurlyBracket = 125,
			Tilde = 126,
			Numlock = 300,
			CapsLock = 301,
			ScrollLock = 302,
			RightShift = 303,
			LeftShift = 304,
			RightControl = 305,
			LeftControl = 306,
			RightAlt = 307,
			LeftAlt = 308,
			LeftCommand = 310,
			LeftApple = 310,
			LeftWindows = 311,
			RightCommand = 309,
			RightApple = 309,
			RightWindows = 312,
			AltGr = 313,
			Help = 315,
			Pr = 316,
			SysReq = 317,
			Break = 318,
			Menu = 319,
			Mouse0 = 323,
			Mouse1 = 324,
			Mouse2 = 325,
			Mouse3 = 326,
			Mouse4 = 327,
			Mouse5 = 328,
			Mouse6 = 329
		};

		enum class CursorLockMode
		{
			None = 0,
			Locked = 1,
			Confined = 2
		};

		enum class PlayerFlags
		{
			Unused1 = 1,
			Unused2 = 2,
			IsAdmin = 4,
			ReceivingSnapshot = 8,
			Sleeping = 16,
			Spectating = 32,
			Wounded = 64,
			IsDeveloper = 128,
			Connected = 256,
			ThirdPersonViewmode = 1024,
			EyesViewmode = 2048,
			ChatMute = 4096,
			NoSprint = 8192,
			Aiming = 16384,
			DisplaySash = 32768,
			Relaxed = 65536,
			SafeZone = 131072,
			ServerFall = 262144,
			Workbench1 = 1048576,
			Workbench2 = 2097152,
			Workbench3 = 4194304,
		};

		enum class ModelState_Flag
		{
			Ducked = 1,
			Jumped = 2,
			OnGround = 4,
			Sleeping = 8,
			Sprinting = 16,
			OnLadder = 32,
			Flying = 64,
			Aiming = 128,
			Prone = 256,
			Mounted = 512,
			Relaxed = 1024,
			Crawling = 4096,
		};

		class Rect {
		public:
			float x; // 0x10
			float y; // 0x14
			float wid; // 0x18
			float hei; // 0x1C
			Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) {
				this->x = x;
				this->y = y;
				wid = x_rightsize;
				hei = y_downsize;
			}
			Rect() {
				this->x = 0;
				this->y = 0;
				wid = 0;
				hei = 0;
			}
			bool Contains(Vector2 point)
			{
				return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei);
			}
		};

		enum class EventType : int {
			MouseDown = 0,
			MouseUp = 1,
			MouseDrag = 3,
			KeyDown = 4,
			KeyUp = 5,
			Repaint = 7
		};
	}
}