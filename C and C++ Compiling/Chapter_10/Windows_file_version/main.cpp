BOOL versionInfoFromFileVersionInfoString(LPSTR lpstrFileVersionInfo,DLLVERSIONINFO* pDLLVersionInfo){
  static WCHAR fileVersion[256];
  LPWSTR lpwstrVersion = NULL;
  UINT nVersionLen = 0;
  DWORD dwLanguageID = 0;
  BOOL retVal;

  if(NULL == pDLLVersionInfo)
    return FALSE;

  wsprintf(fileVersion, L"\\VarFileInfo\\Translation");
  retVal = VerQueryValue ( lpstrFileVersionInfo,
  fileVersion, (LPVOID*)&lpwstrVersion, (UINT *)&nVersionLen);
  
  if(retVal && (4 == nVersionLen)){
    memcpy(&dwLanguageID, lpwstrVersion, nVersionLen);
    wsprintf(fileVersion, L"\\StringFileInfo\\%02X%02X%02X%02X\\FileVersion",
            (dwLanguageID & 0xff00)>>8,
             dwLanguageID & 0xff,
            (dwLanguageID & 0xff000000)>>24,
            (dwLanguageID & 0xff0000)>>16);
  }else
    wsprintf(fileVersion,L"\\StringFileInfo\\%04X04B0\\FileVersion",GetUserDefaultLangID());
  
  if(FALSE == VerQueryValue (lpstrFileVersionInfo,
                             fileVersion,
                            (LPVOID*)&lpwstrVersion,
                            (UINT *)&nVersionLen)){
    return FALSE;
  }

  LPWSTR pwstrSubstring = NULL;
  WCHAR* pContext = NULL;
  pwstrSubstring = wcstok_s(lpwstrVersion, L".", &pContext);
  pDLLVersionInfo->dwMajorVersion = _wtoi(pwstrSubstring);

  pwstrSubstring = wcstok_s(NULL, L".",&pContext);
  pDLLVersionInfo->dwMinorVersion = _wtoi(pwstrSubstring);

  pwstrSubstring = wcstok_s(NULL, L".",&pContext);
  pDLLVersionInfo->dwBuildNumber = _wtoi(pwstrSubstring);

  pwstrSubstring = wcstok_s(NULL, L".",&pContext);
  pDLLVersionInfo->dwPlatformID = _wtoi(pwstrSubstring);
}

BOOL extractDLLFileVersion(DLLVERSIONINFO* pDLLVersionInfo){
  DWORD dwVersionHandle = 0;
  DWORD dwVersionInfoSize = GetFileVersionInfoSize (DLL_FILENAME, &dwVersionHandle);
  
  if(0 == dwVersionInfoSize)
    return FALSE;
  
  LPSTR lpstrFileVersionInfo = (LPSTR) malloc (dwVersionInfoSize);

  if (lpstrFileVersionInfo == NULL)
    return FALSE;

  BOOL bRetValue = GetFileVersionInfo(DLL_FILENAME,
                                      dwVersionHandle,
                                      dwVersionInfoSize,
                                      lpstrFileVersionInfo);

  if(bRetValue){
    bRetValue = versionInfoFromFileVersionInfoString(lpstrFileVersionInfo, pDLLVersionInfo);
  }

  free (lpstrFileVersionInfo);
  return bRetValue;
}

int main(int argc, char *argv[]){
  memset(&dvi, 0, sizeof(DLLVERSIONINFO));
  if(extractDLLFileVersion(&dvi)){
    printf("DLL File Version(major,minor,build,platformID) = %d.%d.%d.%d\n",
            dvi.dwMajorVersion,dvi.dwMinorVersion,
            dvi.dwBuildNumber, dvi.dwPlatformID);
  }
  else{
    printf("DLL File Version extraction failed\n");
  }

  FreeLibrary(hDll);
  return 0;  
}

