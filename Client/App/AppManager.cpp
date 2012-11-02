// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "StdAfx.h"
#include "AppManager.h"
#include "DatabaseManager.h"
#include "TrackedDirectory.h"

void AppManager::Start()
{
    DatabaseManager dbMgr;
    vector<FileEntry> fileList;
    vector<wstring> subDirList;
    TrackedDirectory trackDir;

    vector<wstring> dirList = dbMgr.GetManagedDirs();
    for(vector<wstring>::iterator it = dirList.begin(); it != dirList.end(); it++)
    {
        trackDir.LoadDirectory(*it, fileList, subDirList);
    }

    for(vector<FileEntry>::iterator it = fileList.begin(); it != fileList.end(); it++)
    {
        dbMgr.AddFile(&*it);
    }
}