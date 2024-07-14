BOOL extractDLLProductVersion(HMODULE hDll, DLLVERSIONINFO* pDLLVersionInfo)
{
  if(NULL == pDLLVersionInfo)
    return FALSE;
  }

  DLLGETVERSIONPROC pDllGetVersion;
  pDllGetVersion = (DLLGETVERSIONPROC) GetProcAddress(hDll, "DllGetVersion");

  if(NULL == pDllGetVersion)
    return FALSE;

  ZeroMemory(pDLLVersionInfo, sizeof(DLLVERSIONINFO));
  pDLLVersionInfo->cbSize = sizeof(DLLVERSIONINFO);
  HRESULT hr = (*pDllGetVersion)(pDLLVersionInfo);

  if(FAILED(hr))
    return FALSE;

  return TRUE;

}

