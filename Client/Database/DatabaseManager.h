// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#pragma once
#include <vector>
#include <string>
#include "FileEntry.h"

using namespace std;

class DatabaseManager
{
public:
    vector<wstring> GetManagedDirs();
    vector<wstring> GetManagedTypes();
    wstring GetServer();

    void SetupDB();
    void AddDir(const string& inDir);
    void AddDir(const wstring& inDir);

    void AddType(const string& inType);
    void AddServer(const string& inServer);

    int FindDir(const wstring& inDir);
    int FindDir(const string& inDir);

    void AddFile(FileEntry* inEntry);

private:
    wstring GetDatabasePath();
    vector<wstring> GetStringsFromDB(const wstring& inSQL);
    vector<int> GetIntsFromDB(const wstring& inSQL);

    static int StringListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames);
    static int IntListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames);
};