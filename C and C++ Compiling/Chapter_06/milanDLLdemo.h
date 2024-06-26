#ifndef MILANDLLDEMO_EXPORTS
#define MILANDLLDEMO_API __declspec(dllexport)
#else
#define MILANDLLDEMO_API __declspec(dllimport)
#endif

//This class exports from the milanDLLdemo.dll
class MILANDLLDEMO_API CmilanDLLdemo {
public:
  CmilanDLLdemo(void);
};

extern MILANDLLDEMO_API int nmilanDLLdemo;

MILANDLLDEMO_API int fnmilanDLLdemo(void);
