// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#pragma once
#include <string>
#include <vector>
#include "FileEntry.h"

using namespace std;

class TrackedDirectory
{
public:
   void LoadDirectory(const wstring& inPath, vector<FileEntry>& outFiles, vector<wstring>& outDirs);
   void WatchDirectory(vector<wstring> inDirsToWatch);


private:
    static VOID CALLBACK MonitorCallback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);

    wstring m_dirPath;
    int m_numEntries;
};