// DataSaver.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"



class CDataSaverModule : public ATL::CAtlExeModuleT< CDataSaverModule >
	{
public :
	};

CDataSaverModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

