#pragma once
#include "Common.hpp"
#include "Logger.hpp"
#include "Utils/DbgHelper.hpp"
#include "GTLibc.hpp"
#include "DbgHelper.hpp"
#include "Natives/NativeConst.hpp"

using namespace IGI;
using namespace Utility;

auto ParseConfig = (int(__cdecl*)(char* q_file))0x405850;
auto ParseWeaponConfig = (int(__cdecl*)(int index, char* cfg_file))0x4071E0;
auto CompileConfig = (int(__cdecl*)(int a1, char* q_file, int a3))0x4F0CF0;
auto CreateConfig = (int(__cdecl*)(char* file_name))0x405BD0;
auto LevelLoad = (int(__cdecl*)(int level_addr, int level_len, int param3, int param4))0x4F0E10;
auto LoadLevelMenu = (void(__cdecl*)(void))0x416fe0;
auto LoadResourceFile = (int* (__cdecl*)(const char* res_file, char** buffer))0x4B5F00;
auto MenuManager = (int(__cdecl*)(int a1, char* a2, char a3, char a4, int a5))0x418B00;
auto QuitLevel = (int(__cdecl*)(int param))0x416550;
auto QuitLevelParam = (int(__cdecl*)(unsigned int a1, int a2, int a3))0x401530;
auto RemoveSymbol = (char* (__cdecl*)(int* a1, char symbol))0x4C0460;
auto ScriptInit = (char(__cdecl*)(int a1, char a2, int a3, char a4))0x4F0E50;
auto Script_SetSymbolContext = (int(__cdecl*)(char symbol_name, int symbol_buf))0x4B8930;
auto SetFramesVar = (void(__cdecl*)(int frame_count))0x402820;
auto StartLevel = (int(__cdecl*)(int, int, int, int))0x415B30;
auto StatusMsg = (int(__cdecl*)(int send_status, const char* buffer, const char* msg_sprite, const char* v6))0x485970;
auto TaskTypeSet = (int(__cdecl*)(int* task_name, int task_param))0x4B8810;
auto UnLoadResource = (int(__cdecl*)(char* res_file))0x4B6380;
auto UpdateQTaskList = (int(__cdecl*)(int a1))0x401B20;

decltype(ParseConfig) ParseConfigOut;
decltype(ParseWeaponConfig) ParseWeaponConfigOut;
decltype(CreateConfig) CreateConfigOut;
decltype(SetFramesVar) SetFramesVarOut;
decltype(StartLevel) StartLevelOut;
decltype(QuitLevel) QuitLevelOut;
decltype(LevelLoad) LevelLoadOut;
decltype(LoadResourceFile) LoadResourceOut;
decltype(StatusMsg) StatusMsgOut;

auto CompileQVM = (void(__cdecl*)(char*))0x4B85B0;
decltype(CompileQVM) CompileQVMOut;

auto GameOpenFile = (FILE * (__cdecl*)(char*, char*))0x4A5350;
decltype(GameOpenFile) GameOpenFileOut;

auto LoadQVM = (int* (__cdecl*)(LPCSTR))0x4B80B0;
decltype(LoadQVM) LoadQVMOut;

auto AssembleQAS = (int(__cdecl*)(char*, char*))0x4BB270;
decltype(AssembleQAS) AssembleQASOut;

auto AmmoTypeOpen = (void(__cdecl*)(int))0x47CA40;
decltype(AmmoTypeOpen) AmmoTypeOpenOut;

auto WeaponTypeOpen = (void(__cdecl*)(int))0x413A90;
decltype(WeaponTypeOpen) WeaponTypeOpenOut;

auto LoadGameData = (int(__cdecl*)(char*, char*))0x4A53B3;
decltype(LoadGameData) LoadGameDataOut;

auto SetGameDataSymbol = (int(__cdecl*)(char*))0x4B80A0;
decltype(SetGameDataSymbol) SetGameDataSymbolOut;

auto TextPrint = (void(__cdecl*)(int*, byte*, int, int))0x4B77F0;
decltype(TextPrint) TextPrintOut;

auto GameTextPrint = (void(__cdecl*)(int**, byte*))0x4B6E90;
decltype(GameTextPrint) GameTextPrintOut;

auto StatusMessageShow = (int(__cdecl*)(int, int**, int*, int, int, int))0x485DB0;
decltype(StatusMessageShow) StatusMessageShowOut;

auto GunPickup = (void(__cdecl*)(int, int*))0x45FFC0;
auto AmmoPickup = (void(__cdecl*)(int, int*))0x45FF80;
auto GenericPickup = (void(__cdecl*)(int*))0x46C3C0;
decltype(GunPickup) GunPickupOut;
decltype(AmmoPickup) AmmoPickupOut;
decltype(GenericPickup) GenericPickupOut;

auto ShowError = (void(__cdecl*)(LPCSTR))0x4AF7B0;
decltype(ShowError) ShowErrorOut;

auto ShowWarning = (void(__cdecl*)(LPCSTR))0x4AF810;
decltype(ShowWarning) ShowWarningOut;

auto GetPlayerXPHit = (uint32_t(__cdecl*)(void))0x00416d80;
decltype(GetPlayerXPHit) GetPlayerXPHitOut;

auto HumanViewCam = (uint32_t(__cdecl*)(int, int))0x00463760;
decltype(HumanViewCam) HumanViewCamOut;

auto SFXItems = (int* (__cdecl*)(int, char*))0x004E6B00;
decltype(SFXItems) SFXItemsOut;

auto HumanXPHit = (void(__cdecl*)(int, char*, int))0x004637C0;
decltype(HumanXPHit) HumanXPHitOut;

auto HumanXPDead = (void(__cdecl*)(int, char*, int))0x004638a0;
decltype(HumanXPDead) HumanXPDeadOut;

auto WeaponDrop = (void(__cdecl*)(int**))0x0046cea0;
decltype(WeaponDrop) WeaponDropOut;

struct HUMAN_SOLDIER {
	string model_id;
	int ai_id;
	int graph_id;
	string weapon;
	bool is_dead;
	int e_team;
};

inline std::list<HUMAN_SOLDIER> human_soldiers;

HUMAN_SOLDIER AddHumanSoldierData(string file_name) {
	HUMAN_SOLDIER soldier = {};

	auto file_data = Utility::ReadFile(file_name,true);

	if (!file_data.empty()) {
		std::regex data_regex(R"(\w{0,}_\w{0,})");
		auto words_begin = std::sregex_iterator(file_data.begin(), file_data.end(), data_regex);
		auto words_end = std::sregex_iterator();

		const string soldier_tag = "HumanSoldier_", weapon_id_tag = "WEAPON_ID";

		auto find_ai_id = [](string s)-> int {
			string id; for (const auto& c : s) if (::isdigit(c)) id += c;
			return std::stoi(id);
		};

		for (auto index = words_begin; index != words_end; ++index) {

			auto match = *index;
			string match_str = match.str();

			if (match_str.find(soldier_tag) != std::string::npos)
				soldier.ai_id = find_ai_id(match_str);
			else if (match_str.find(weapon_id_tag) != std::string::npos)
				soldier.weapon = match_str;
		}
		soldier.model_id = file_data.substr(0,8);

		human_soldiers.push_back(soldier);
	}
	else LOG_ERROR("%s Human soldier data cannot be empty.",FUNC_NAME);
	return soldier;
}

void WeaponDropDetour(int** param_1) {

	int entity_dead = 0;
	//__asm {
	//	fld[esi + 0x100]
	//	fcomp[esi + 0x118]
	//	fnstsw ax
	//	test ah, 0x01
	//	je MY_LBL
	//	MY_LBL :
	//	mov entity_dead, 1
	//}

	if (*(double*)(param_1 + 0x40) < *(double*)(param_1 + 0x46)) entity_dead = 1;

	if (entity_dead)
	{
		LOG_CONSOLE("%s param_1: %p", "WeaponDrop", param_1);
		LOG_CONSOLE("%s p_100: %f p_118: %f p_120 : %f", "WeaponDrop", *(double*)(param_1 + 0x100), *(double*)(param_1 + 0x118), *(double*)(param_1 + 0x120));
	}
	WeaponDropOut(param_1);
}


void HumanXPHitDetour(int param_1, char* param_2, int param_3) {
	LOG_CONSOLE("%s param_1: %p param_2: '%s' param_3 : %d", "PlayerHit", param_1, param_2, param_3);
	LOG_CONSOLE("%s AI_Id: '%s'", "PlayerHit", (char*)(param_1 + 0x100));
	HumanXPHitOut(param_1, param_2, param_3);
}

void HumanXPDeadDetour(int param_1, char* param_2, int param_3) {
	LOG_CONSOLE("%s param_1: %p param_2: '%s' param_3 : %d", "PlayerDead", param_1, param_2, param_3);

	const int AI_BUF_SIZE = 8000;
	string ai_data(AI_BUF_SIZE, '\0');
	void* ai_type_addr = (void*)(param_1 + 0x100);
	LOG_CONSOLE("%s AiType %p", "PlayerDead", ai_type_addr);

	std::memcpy(ai_data.data(), ai_type_addr, AI_BUF_SIZE);
	const string ai_file = Utility::GetModuleFolder() + "\\" + "ai_data.dat";
	Utility::WriteFile(ai_file, ai_data, true);

	//Print soldier data information.
	auto soldier = AddHumanSoldierData(ai_file);

	LOG_CONSOLE("Soldier Model: '%s'",soldier.model_id.c_str());
	LOG_CONSOLE("Soldier Id: %d",soldier.ai_id);
	LOG_CONSOLE("Soldier Weapon: '%s'",soldier.weapon.c_str());

	soldier.is_dead = true;
	human_soldiers.push_back(soldier);

	//std::filesystem::rename(ai_file,Utility::GetModuleFolder() + "\\" + soldier.model_id + ".dat");
	if (!Utility::RemoveFile(ai_file)) LOG_ERROR("%s File '%s' cannot be removed", FUNC_NAME, ai_file);

	HumanXPDeadOut(param_1, param_2, param_3);
}

int* __cdecl SFXItemsDetour(int param_1, char* sfx_item) {
	auto ret_val = SFXItemsOut(param_1, sfx_item);
	LOG_FILE("%s param_1: %p ret_val : %p sfx_item: %s", "SFXItems", param_1, ret_val, sfx_item);
	//const string log_file = GetModuleFolder() + "\\" + LOG_FILE_NAME;
	//auto file_data = Utility::ReadFile(log_file);

	//if (file_data.find(sfx_item) == std::string::npos)
	//	LOG_FILE("\"%s\",", sfx_item);

	return ret_val;
}

void HumanViewCamDetour(int param_1, int param_2) {
	LOG_INFO("%s param_1: %p param_2: %d", "HumanViewCam", param_1, param_2);
	HumanViewCamOut(param_1, param_2);
}

uint32_t GetPlayerXPHitDetour(void) {
	uint32_t xp_hit = GetPlayerXPHitOut();
	LOG_INFO("%s xp_hit: %p", "GetPlayerXPHit", xp_hit);
	return xp_hit;
}

void ShowWarningDetour(LPCSTR warn_msg) {
	LOG_FILE("%s warn_msg: %s", "ShowWarning", warn_msg);
	ShowWarningOut(warn_msg);
}

void ShowErrorDetour(LPCSTR err_msg) {
	LOG_FILE("%s err_msg: %s", "ShowError", err_msg);
	ShowErrorOut(err_msg);
}

void GenericPickupDetour(int* param_1) {
	if ((*(char*)(param_1 + 0x119) != '\0') && (*(char*)(param_1 + 0x11a) != '\0'))
		LOG_FILE("%s param_1: %p *param_1: %p param_1_handler: '%s'", "GenericPickup", param_1, *param_1, *(param_1 + 0x1A0));
	GenericPickupOut(param_1);
}

void GunPickupDetour(int param_1, int* param_2) {
	LOG_FILE("%s param_1: %p param_2: %p Weapon_Id : %d", "GunPickup", param_1, param_2, *param_2);
	GunPickupOut(param_1, param_2);
}

void AmmoPickupDetour(int param_1, int* param_2) {
	LOG_FILE("%s param_1: %p param_2: %p Ammo_Id : %d", "AmmoPickup", param_1, param_2, *param_2);
	AmmoPickupOut(param_1, param_2);
}

void StatusMessageShowDetour(int param_1, int** param_2, int* param_3, int param_4, int param_5, int param_6) {
	LOG_FILE("%s param_1 : %p param_2 : %p param_3 : %p param_4 : %p param_5 : %p param_6 : %p", "StatusMessageShow", param_1, param_2, param_3, param_4, param_5, param_6);
	Sleep(100);
	char* text = nullptr;

	__asm {
		lea ebx, [esi + 0x10]
		shl edx, 0x0A
		sub eax, ecx
		lea edi, [esp + edx * 0x1 + 0x28]
		mov text, edi
	}
	LOG_FILE("%s text: %s", "StatusMessageShow", text);
	g_DbgHelper->StackTrace(true);
	StatusMessageShowOut(param_1, param_2, param_3, param_4, param_5, param_6);
}

void __cdecl GamePrintTextDetour(int** param_1, byte* param_2) {
	LOG_FILE("%s param_1 : %p *param_1 : %p **param_1 : '%s' param_2 : '%s'", "GamePrintText", param_1, *param_1, READ_PTR(param_1 + 0x180), param_2);

	Sleep(100);
	g_DbgHelper->StackTrace(true);
	GameTextPrintOut(param_1, param_2);
}

void __cdecl PrintTextDetour(int* param_1, byte* param_2, int param_3, int param_4) {
	LOG_FILE("%s param_1 : %p param_2 : '%s' param_3 : %p param_4 : %p", "PrintText", param_1, param_2, param_3, param_4);
	Sleep(100);
	g_DbgHelper->StackTrace(true);
	TextPrintOut(param_1, param_2, param_3, param_4);
}

void ReadWholeFile(LPCSTR file_name, LPCSTR file_mode = "rb") {
	LOG_FILE("%s File : %s Mode : %s", FUNC_NAME, file_name, file_mode);
	try {
		if (string(file_mode) == "rb") {
			auto file_string = string(file_name);
			std::ifstream ifs(file_name, std::ios::binary);
			if (ifs.good()) {
				std::ofstream ofs(file_string.insert(file_string.length() - 4, "_open"), std::ios::binary);
				std::vector<byte> buffer(std::istreambuf_iterator<char>(ifs), {});
				std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<char>(ofs, ""));
			}
			else
			{
				LOG_FILE("%s File : %s doesn't exist", FUNC_NAME, file_name);
			}
		}
	}
	catch (std::exception const& ex) {
		LOG_ERROR("Exception: ",ex.what() );
	}
}

int __cdecl SetGameDataSymbolDetour(char* symbol_file) {
	LOG_FILE("%s : symbol_file : %s", "SetGameDataSymbol", symbol_file);
	Sleep(100);
	int ret_val = SetGameDataSymbolOut(symbol_file);
	g_DbgHelper->StackTrace(true);
	return ret_val;
}

int __cdecl LoadGameDataDetour(char* res_buf, char* res_path) {
	LOG_FILE("%s res_buf: '%p' res_path: '%s'", "LoadGameData", res_buf, res_path);
	Sleep(100);
	g_DbgHelper->StackTrace(true);
	return LoadGameDataOut(res_buf, res_path);
}

int __cdecl  StatusMsgDetour(int send_status, const char* buffer, const char* msg_sprite, const char* status_byte) {
	LOG_FILE("%s send_status : %p buffer : '%s' msg_sprite : '%s' status_byte : %p", FUNC_NAME, send_status, buffer, msg_sprite, status_byte);
	Sleep(100);
	return StatusMsgOut(send_status, buffer, msg_sprite, status_byte);
}

int __cdecl ParseConfigDetour(char* q_file) {
	LOG_FILE("%s : q_file : %s", FUNC_NAME, q_file);
	Sleep(100);
	int ret_val = ParseConfigOut(q_file);
	//g_DbgHelper->StackTrace(true, false, true);
	return ret_val;
}

int __cdecl CreateConfigDetour(char* q_file) {
	LOG_FILE("%s : q_file : %s", FUNC_NAME, q_file);
	Sleep(100);
	int ret_val = CreateConfigOut(q_file);

	//g_DbgHelper->StackTrace(true, false, false);
	return ret_val;
}

int __cdecl ParseWeaponConfigDetour(int index, char* cfg_file) {
	LOG_FILE("%s index : %d cfg_file : %s", FUNC_NAME, index, cfg_file);
	Sleep(100);
	return ParseWeaponConfigOut(index, cfg_file);
}

void __cdecl SetFramesDetour(int frames) {
	LOG_FILE("%s : Frames : %d", FUNC_NAME, frames);
	Sleep(100);
	return SetFramesVarOut(frames);
}

int __cdecl  StartLevelDetour(int param1, int param2, int param3, int param4) {
	LOG_FILE("%s param1 : %p param2 : %p param3 : %p param4 : %p", FUNC_NAME, param1, param2, param3, param4);
	Sleep(100);
	g_DbgHelper->StackTrace(true, false, true);
	return StartLevelOut(param1, param2, param3, param4);
}

int __cdecl  QuitLvlDetour(int param1, int param2, int param3, int param4) {
	LOG_FILE("%s param1 : %p param2 : %p param3 : %p param4 : %p", FUNC_NAME, param1, param2, param3, param4);
	Sleep(100);
	return QuitLevelOut(param1);
}

void __cdecl AmmoTypeOpenDetour(int param1) {
	LOG_INFO("%s param1 : %p", FUNC_NAME, param1);
	AmmoTypeOpenOut(param1);
}

void __cdecl WeaponTypeOpenDetour(int param1) {
	LOG_INFO("%s param1 : %p", FUNC_NAME, param1);
	WeaponTypeOpenOut(param1);
}

int __cdecl AssembleQASDetour(char* file_out, char* file_in) {
	int qas_ret = AssembleQASOut(file_out, file_in);
	LOG_INFO("%s file_in : %s file_out : %s  Status : %d", "AssembleQAS", file_in, file_out, qas_ret);
	return qas_ret;
}

int* __cdecl LoadResourceDetour(char* param1, char** param2) {

	int* res_addr = LoadResourceOut(param1, param2);
	LOG_FILE("%s File '%s'\t Address %p", "LoadResource", param1, (int)res_addr);
	//g_DbgHelper->StackTrace(true, false, true);
	return res_addr;
}

void __cdecl CompileQVMDetour(char* file_name) {
	LOG_INFO("%s file_name : %s", "CompileQVM", file_name);

	*(PDWORD64)(0x0201B1) += 1;
	strcpy((char*)0x943606, file_name);
	Sleep(100);
	CompileQVMOut(file_name);
}

int* __cdecl LoadQVMDetour(LPCSTR file_name) {
	LOG_CONSOLE("%s file_name : %s", "LoadQVM", file_name);

	//auto CompileQVM = (int(__cdecl*)(int))0x4B85B0;
	//auto CompileCleanUp = (int(__cdecl*)(int*))0x4B83D0;
	auto qvm_file = LoadQVMOut(file_name);

	//ReadWholeFile(file_name); 
	return qvm_file;
}

FILE* __cdecl GameOpenFileDetour(char* file_name, char* file_mode) {
	//if (string(file_mode) == "wb")
	LOG_CONSOLE("%s File : '%s' Mode : '%s'", "OpenFile", file_name, file_mode);

	//ReadWholeFile(file_name, file_mode); 
	//g_DbgHelper->StackTrace(true, false, true);

	Sleep(100);
	return GameOpenFileOut(file_name, file_mode);
}

int __cdecl LevelLoadDetour(int param1, int param2, int param3, int param4) {
	LOG_INFO("%s param1 : %s param2 : %p param3 : %p  param4 : %p", "LevelLoad", param1, param2, param3, param4);
	Sleep(100);
	g_DbgHelper->StackTrace(true, false, true);
	return LevelLoadOut(param1, param2, param3, param4);
}