#ifdef VERSIONEDDLL_EXPORTS
#define VERSIONEDDLL_API __declspec(dllexport)
#else
#define VERSIONEDDLL_API __declspec(dllimport)
#endif

#include <Shlwapi.h>

VERSIONEDDLL_API HRESULT CALLBACK DLLGetVersion(DLLVERSIONINFO* pdvi);
