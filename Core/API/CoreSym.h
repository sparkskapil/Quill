#pragma once
#pragma warning(disable:4251)
#ifdef MODEL_DLL
#define MODELAPI __declspec(dllexport)
#else
#define MODELAPI __declspec(dllimport)
#endif
