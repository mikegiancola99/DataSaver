// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "StdAfx.h"
#include <stdio.h>
#include "TrackedDirectory.h"
#include <algorithm>
#include "DatabaseManager.h"
#include "AppManager.h"

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

//extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
//								HINSTANCE /*hPrevInstance*/, 
 //                               LPTSTR lpCmdLine, 
//								int nShowCmd)
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    //ProcessCmdLine(argc, argv);

    // read directories to monitor from database
    // 
    //TrackedDirectory dir;
    //dir.LoadDirectory(L"c:\\temp\\");
	return 0;
}