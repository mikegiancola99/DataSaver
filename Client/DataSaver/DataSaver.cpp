// ******************************************************************
//  Copyright 2012 Mike Giancola, All Right Reserved.
//
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// ******************************************************************


#include "stdafx.h"
#include "resource.h"
#include "TrackedDirectory.h"
#include "DatabaseManager.h"
#include "AppManager.h"


class CDataSaverModule : public ATL::CAtlExeModuleT< CDataSaverModule >
	{
public :
	};

CDataSaverModule _AtlModule;



void InstallSystem()
{
    DatabaseManager dbMgr;
    dbMgr.SetupDB();
}

void AddDir(const string& inDir)
{
    DatabaseManager dbMgr;
    dbMgr.AddDir(inDir);
}

void AddType(const string& inType)
{
    DatabaseManager dbMgr;
    dbMgr.AddType(inType);
}

void AddServer(const string& inServer)
{
    DatabaseManager dbMgr;
    dbMgr.AddServer(inServer);
}

void ProcessCmdLine(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        string param(argv[i]);
        std::transform(param.begin(), param.end(), param.begin(), tolower);
        if (param.compare("install") == 0)
            InstallSystem();
        else if (param.compare("adddir") == 0)
        {
            char* tmpArg = argv[i+1];
            if (tmpArg)
                AddDir(tmpArg);
        }
        else if (param.compare("addtype") == 0)
        {
            char* tmpArg = argv[i+1];
            if (tmpArg)
                AddType(tmpArg);
        }
        else if (param.compare("server") == 0)
        {
            char* tmpArg = argv[i+1];
            if (tmpArg)
                AddServer(tmpArg);
        }
        else if (param.compare("testrun") == 0)
        {
            AppManager appMgr;
            appMgr.Start();
        }
    }
}


//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR lpCmdLine, int nShowCmd)
{
    //ProcessCmdLine(argc, argv);
    InstallSystem();
    AddDir("C:\\Users\\mike\\Pictures");
    
    AppManager appMgr;
    appMgr.Start();
	return _AtlModule.WinMain(nShowCmd);
}

