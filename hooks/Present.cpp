#include <iostream>
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "../include/libmem++/libmem.hpp"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_win32.h"
#include "../include/imgui/imgui_impl_dx11.h"

#include "../base.h"

HRESULT __fastcall Base::Hooks::Present(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags)
{
	__try {
		if (!Data::InitImGui)
		{
			Data::pSwapChain = thisptr;
			if (SUCCEEDED(Data::pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Data::pDxDevice11)))
			{
				Data::pDxDevice11->GetImmediateContext(&Data::pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				Data::pSwapChain->GetDesc(&sd);
				Data::hWindow = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				Data::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				Data::pDxDevice11->CreateRenderTargetView(pBackBuffer, NULL, &Data::pMainRenderTargetView);
				pBackBuffer->Release();
				Data::oWndProc = (WNDPROC)SetWindowLongPtr(Data::hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();
				io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
				ImGui_ImplWin32_Init(Data::hWindow);
				ImGui_ImplDX11_Init(Data::pDxDevice11, Data::pContext);
				Data::InitImGui = true;
			}
		}

		if (!Data::InitImGui) return Data::oPresent(thisptr, SyncInterval, Flags);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (Data::ShowMenu)
		{
			ImGui::Begin("ImGui Window");
			ImGui::Text("Test ImGUI Window");
			if (ImGui::Button("Detach"))
			{
				ImGui::End();
				ImGui::EndFrame();
				ImGui::Render();
				Data::pContext->OMSetRenderTargets(1, &Data::pMainRenderTargetView, NULL);
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				Base::Detach();
				return Data::oPresent(thisptr, SyncInterval, Flags);
			}
			ImGui::End();
		}

		ImGui::EndFrame();
		ImGui::Render();

		Data::pContext->OMSetRenderTargets(1, &Data::pMainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return Data::oPresent(thisptr, SyncInterval, Flags);
	} __except(true) {}
}