//#include <stdafx.h>
#include <windows.h>

HMODULE g_hModule = nullptr;

bool APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved){
  switch(ul_reason_for_call){
  case DLL_PROCESS_DETACH:
    g_hModule = NULL;
    break;
  case DLL_PROCESS_ATTACH:
    g_hModule = hModule;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
    break;
  }
  return TRUE;
}
