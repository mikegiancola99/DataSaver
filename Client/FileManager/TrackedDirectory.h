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
#pragma once
#include <string>
#include <vector>
#include "FileEntry.h"

using namespace std;

class TrackedDirectory
{
public:
   void LoadDirectory(const wstring& inPath, vector<wstring>& outDirs);

private:
    wstring m_dirPath;
    int m_numEntries;
};