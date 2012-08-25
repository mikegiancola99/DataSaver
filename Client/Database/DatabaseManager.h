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
#include <vector>
#include <string>
#include "FileEntry.h"

using namespace std;

class DatabaseManager
{
public:
    // create tables - general init. 
    // only call once during installation
    void SetupDB();

    // saved content stuff
    void AddFile(FileEntry* inEntry);

    // returns row id. +'ve number if found, -1 if not
    int FindFile(const wstring& inMD5);
    int FindFile(FileEntry* inEntry);

    // marks state to 1 for that element
    void MarkFileSent(const wstring& inMD5);

    // managed dirs stuff
    void AddDir(const string& inDir);
    void AddDir(const wstring& inDir);
    vector<wstring> GetManagedDirs();
    int FindDir(const wstring& inDir);
    int FindDir(const string& inDir);
    wstring FindDirByIndex(int inRowId);

    // managed types
    void AddType(const string& inType);
    vector<wstring> GetManagedTypes();

    void AddServer(const string& inServer);
    wstring GetServer();

private:
    vector<wstring>   GetStringsFromDB(const wstring& inSQL);
    vector<int>       GetIntsFromDB(const wstring& inSQL);
    vector<FileEntry> GetFileEntriesFromDB(const wstring& inSQL);

    static int StringListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames);
    static int IntListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames);
    static int FileEntryListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames);

};