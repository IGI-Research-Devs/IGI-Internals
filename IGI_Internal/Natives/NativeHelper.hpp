#pragma once 
#include "Natives.hpp" 
#include "NativeCaller.hpp" 
#define NATIVE_DECL __declspec(noinline) inline 

namespace IGI {
	namespace PLAYER {
		//Set Player profile properties. 
		NATIVE_DECL void SET_PLAYER_INDEX_NAME(int index, const char* name) { std::memcpy((char*)PLAYER_INDEX_ADDR(index + 1), name, PLAYER_NAME_SIZE); }
		NATIVE_DECL void SET_PLAYER_INDEX_MISSION(int index, byte mission) { *(byte*)(PLAYER_INDEX_ADDR(index + 1) + PLAYER_ACTIVE_MISSION_OFF) = (byte)mission; }
		NATIVE_DECL void SET_PLAYER_ACTIVE_NAME(const char* name) { std::memcpy((char*)PLAYER_ACTIVE_ADDR, name, PLAYER_NAME_SIZE); }
		NATIVE_DECL void SET_PLAYER_ACTIVE_MISSION(byte mission) { { *(byte*)(PLAYER_ACTIVE_ADDR + PLAYER_ACTIVE_MISSION_OFF) = (byte)mission; } }
	}

	namespace CONFIG {
		NATIVE_DECL void CONFIG_READ(const char* config_file) { NATIVE_INVOKE((NativeHash)HASH::CONFIG_READ, config_file); }
		NATIVE_DECL void CONFIG_WRITE(const char* config_file) { NATIVE_INVOKE((NativeHash)HASH::CONFIG_WRITE, config_file); }
		NATIVE_DECL void WEAPON_CONFIG_READ(const char* config_file) { NATIVE_INVOKE((NativeHash)HASH::WEAPON_CONFIG_READ, 0, config_file); }
	}

	namespace GAME {
		NATIVE_DECL void INPUT_ENABLE() { NATIVE_INVOKE((NativeHash)HASH::INPUT_ENABLE, (LPCSTR)local_buf); }
		NATIVE_DECL void INPUT_DISABLE() { NATIVE_INVOKE((NativeHash)HASH::INPUT_DISABLE, (LPCSTR)local_buf); }
		NATIVE_DECL void QUIT() { *(PINT)0x5C8DE8 = 0; }
	}

	namespace LEVEL {
		NATIVE_DECL void RESTART() { NATIVE_INVOKE((NativeHash)HASH::LEVEL_RESTART); }
		NATIVE_DECL void SET(int level) { *(PINT)0x5C8DE8 = (level < 1 || level > GAME_LEVEL_MAX) ? 1 : level; }
	}

	namespace HUMAN {
		NATIVE_DECL void HUMAN_PLAYER_LOAD() { NATIVE_INVOKE((NativeHash)HASH::HUMANPLAYER_LOAD); }

	}

	namespace WEAPON {
		NATIVE_DECL void SET_UNLIMITED_AMMO(bool enable) { *(PINT)0x56E214 = enable; }
		NATIVE_DECL void TYPE_OPEN() { NATIVE_INVOKE((NativeHash)HASH::WEAPON_TYPE_OPEN); }
	}

	namespace QTASK {
		NATIVE_DECL void UPDATE() { NATIVE_INVOKE((NativeHash)HASH::QTASK_UPDATE); }
		NATIVE_DECL void UPDATE_LIST(int* qtask_list) { NATIVE_INVOKE((NativeHash)HASH::QTASK_UPDATE_LIST, qtask_list); }
		NATIVE_DECL void RESET() { NATIVE_INVOKE((NativeHash)HASH::QHASH_RESET); }
		NATIVE_DECL void HASH_INIT(int hash_val) { NATIVE_INVOKE((NativeHash)HASH::QHASH_INIT, hash_val); };
	}

	namespace QFILE {
		NATIVE_DECL void QSC_COMPILE(const char* qsc_file) { NATIVE_INVOKE((NativeHash)HASH::QSC_COMPILE, qsc_file); }

	}

	namespace GFX {
		NATIVE_DECL void GRAPHICS_RESET() { NATIVE_INVOKE((NativeHash)HASH::GRAPHICS_RESET, (LPCSTR)local_buf); }
	}

	namespace SFX {
		NATIVE_DECL void MUSIC_ENABLE() { NATIVE_INVOKE((NativeHash)HASH::MUSIC_ENABLE, (LPCSTR)local_buf); }
		NATIVE_DECL void MUSIC_DISABLE() { NATIVE_INVOKE((NativeHash)HASH::MUSIC_DISABLE, (LPCSTR)local_buf); }
		NATIVE_DECL void MUSIC_UPDATE_VOLUME() { NATIVE_INVOKE((NativeHash)HASH::MUSIC_UPDATE_VOLUME, (LPCSTR)local_buf); }
		NATIVE_DECL void MUSIC_SET_VOLUME(int volume) { NATIVE_INVOKE((NativeHash)HASH::MUSIC_SET_VOLUME, volume, volume); }
		NATIVE_DECL void MUSIC_SET_SFX_VOLUME(int volume) { NATIVE_INVOKE((NativeHash)HASH::MUSIC_SET_SFX_VOLUME, volume); }
	}

	namespace MISC {
		NATIVE_DECL void FRAMES_SET(int frames) { NATIVE_INVOKE((NativeHash)HASH::FRAMES_SET, frames); };
		NATIVE_DECL void CUTSCENE_DELETE() { NATIVE_INVOKE((NativeHash)HASH::CUTSCENE_DELETE, (LPCSTR)local_buf); }
		NATIVE_DECL void STATUS_MESSAGE_DELETE() { NATIVE_INVOKE((NativeHash)HASH::STATUS_MESSAGE_DELETE, (LPCSTR)local_buf); }
		NATIVE_DECL void GAMEMATERIAL_LOAD() { NATIVE_INVOKE((NativeHash)HASH::GAMEMATERIAL_LOAD); }
		NATIVE_DECL void LOG_ADD(const char* log_msg) { NATIVE_INVOKE((NativeHash)HASH::LOG_ADD, log_msg); }
		NATIVE_DECL void WARNINGS_DISABLE() { *(PINT)0x936274 = 0; }
		NATIVE_DECL void ERRORS_DISABLE() { *(PINT)0x936268 = 0; }
	}
}