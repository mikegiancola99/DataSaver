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
#include "StdAfx.h"
#include "AppManager.h"
#include "DatabaseManager.h"
#include "TrackedDirectory.h"
#include "DataXFer.h"

void AppManager::Start()
{
    DatabaseManager dbMgr;
    vector<wstring> subDirList = dbMgr.GetManagedDirs();
    TrackedDirectory trackDir;
    vector<wstring> masterDirList;
    vector<wstring> dirList;

    do
    {
        dirList = subDirList;
        subDirList.clear();
        for(vector<wstring>::iterator it = dirList.begin(); it != dirList.end(); it++)
            trackDir.LoadDirectory(*it, subDirList);
        masterDirList.insert(masterDirList.begin(), dirList.begin(), dirList.end());
    } while (subDirList.size() > 0);

    int sree = 0;
    /*
    vector<FileEntry> fileList;
    for(vector<FileEntry>::iterator it = fileList.begin(); it != fileList.end(); it++)
    {
        FileEntry filePtr = *it;

        dbMgr.AddFile(&filePtr);
        DataXFer xfer;
        xfer.SendFile(filePtr.GetPath() + L"\\" +  filePtr.GetFilename());
    }
    */

}