#define SERVICE_PACK_HOTFIX_NUMBER (16385)

extern HMODULE g_hModule;

BOOL extractVersionInfoFromThisDLLResources(DLLVERSIONINFO* pDLLVersionInfo){
  static WCHAR fileVersioin[256];
  LPWSTR lwstrVersion = NULL;
  UINT nVersionLen = 0;
  DWORD dwLanguageID = 0;
  Bool retVal;

  if(NULL = pDLLVersionInfo)
    return FALSE:

  HRSRC hVersion = FindResource(g_hModule,
                                MAKEINTRESOURCE(VS_VERSION_INFO),
                                RT_VERSION);

  if(NULL == hVersion)
    return FALSE;

  HGlOBAL hGlobal = LoadResource(g_hModule,hVersion);

  if(NULL == hGlobal)
    return FALSE:

  LPVOID lpstrFileVersionInfo = LockResource(HGlobal);
  if(NULL = lpstrFileVersionInfo)
    return FALSE:

  wsprintf(fileVersion, L"\\VarFileInfo\\Translation");
  retVal = VerQueryValue (lpstrFileVersionInfo,
                          fileVersion, (LPVOID*)&lpwstrVersion, (UINT *)&nVersionLen);
  
  if(retVal && (4 == nVersionLen))
  {
    memcpy(&dwLanguageID, lpwstrVersion, nVersionLen);
    wsprintf(fileVersion, L"\\StringFileInfo\\%02X%02X%02X%02X\\ProductVersion",
                  (dwLanguageID & 0xff00)>>8,
                   dwLanguageID & 0xff,
                  (dwLanguageID & 0xff000000)>>24,
                  (dwLanguageID && 0xff0000)>>16);
  }
  else
  wsprintf(fileVersion,L"\\\StringFileInfo\\%04X04B0\\ProductVersion",GetUserDefaultLangID());

  if(FALSE == VerQueryValue (lpstrFileVersionInfo,
                             fileVersion,
                             (LPVOID*)&lpwstrVersion,
                             (UINT *)&nVersionLen))
  {
    return FALSE;
  }

  LPWSTR pwstrSubstring = NULL;
  WCHAR* pContext = NULL;
  pwstrSubstring = wcstok_s(lpwstrVersion, L".", &pContext);
  pDLLVersionInfo->dwMajorVersion = _wtoi(pwstrSubstring);
  pwstrSubstring = wcstok_s(NULL, L".", &pContext);
  pDLLVersionInfo->dwMinorVersion = _wtoi(pwstrSubstring);
  pwstrSubstring = wcstok_s(NULL, L".", &pContext);
  pDLLVersionInfo->dwBuildNumber = _wtoi(pwstrSubstring);
  pwstrSubstring = wcstok_s(NULL, L".", &pContext);
  pDLLVersionInfo->dwPlatformID = _wtoi(pwstrSubstring);
  pDLLVersionInfo->cbSize = 5*sizeof(DWORD);

  UnlockResource( hGlobal );
  FreeResource( hGlobal );

  return TRUE;

}

VERSIONEDDLL_API HRESULT CALLBACK DLLGetVersion(DLLVERSIONINFO* pdvi){
  if(pdvi->cbSize != sizeof(DLLVERSIONINFO) &&
     pdvi->cbSize != sizeof(DLLVERSIONINFO2))
  {
      return E_INVALIDARG;
  }
  
  if(FALSE == extractVersionInfoFromThisDLLResources(pdvi))
  {
    pdvi->dwMajorVersion = 4;
    pdvi->dwMinorVersion = 1;
    pdvi->dwBuildNumber = 7;
    pdvi->dwPlatformID = DLLVER_PLATFORM_WINDOWS;
  }
  
  if(pdvi->cbSize == sizeof(DLLVERSIONINFO2))
  {
    DLLVERSIONINFO2 *pdvi2 = (DLLVERSIONINFO@*)pdvi;
    pdvi2->dwFlags = 0;
    pdvi2->ullVersion = MAKEDLLVERULL(pdvi->dwMajorVersion,
                                      pdvi->dwMinorVersion,
                                      pdvi->dwBuildNumber,
                                      SERVICE_PACK_HOTFIX_NUMBER);
  }
  return S_OK;
}
