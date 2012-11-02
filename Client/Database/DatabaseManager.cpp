// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "StdAfx.h"
#include "DatabaseManager.h"
#include "DBConstants.h"
#include <sqlite3.h>
#include <algorithm>

// ************************************************************************

vector<wstring> DatabaseManager::GetManagedTypes()
{    
    const wstring sql(DBConstants::selectAllSQL + DBConstants::managedTypesTable);
    return GetStringsFromDB(sql);
}

// ************************************************************************

vector<wstring> DatabaseManager::GetManagedDirs()
{
    const wstring sql(DBConstants::selectAllSQL + DBConstants::managedDirsTable);
    return GetStringsFromDB(sql);
}

// ************************************************************************

void DatabaseManager::SetupDB()
{
    GetStringsFromDB(DBConstants::createManagedDirsTable);
    GetStringsFromDB(DBConstants::createManagedTypesTable);
    GetStringsFromDB(DBConstants::createSavedContentTable);
}

// ************************************************************************

void DatabaseManager::AddDir(const wstring& inDir)
{
    string tmp(inDir.begin(), inDir.end());
    AddDir(tmp);
}

// ************************************************************************

void DatabaseManager::AddDir(const string& inDir)
{
    int existing = FindDir(inDir);
    if (existing == -1)
    {
        wstring sql(DBConstants::addManagedDirSQL);
        const wstring indexStr(L"{0}");
        int findLoc = sql.find(indexStr);
        if (findLoc >= 0)
        {
            sql.replace(findLoc, indexStr.length(), wstring(inDir.begin(), inDir.end()));
            std::transform(sql.begin(), sql.end(), sql.begin(), ::tolower);
            GetStringsFromDB(sql);
        }
    }
}

// ************************************************************************

void DatabaseManager::AddType(const string& inType)
{
    wstring sql(DBConstants::addManagedTypeSQL);
    const wstring indexStr(L"{0}");
    int findLoc = sql.find(indexStr);
    if (findLoc >= 0)
    {
        sql.replace(findLoc, indexStr.length(), wstring(inType.begin(), inType.end()));
        std::transform(sql.begin(), sql.end(), sql.begin(), ::tolower);
        GetStringsFromDB(sql);
    }
}

// ************************************************************************

void DatabaseManager::AddServer(const string& inServer)
{
}

// ************************************************************************

int DatabaseManager::FindDir(const string& inDir)
{
    wstring tmp(inDir.begin(), inDir.end());
    return FindDir(tmp);
}

// ************************************************************************

int DatabaseManager::FindDir(const wstring& inDir)
{
    int result = -1;

    wstring sql(DBConstants::find_A_DirSQL);
    const wstring indexStr(L"{0}");
    int findLoc = sql.find(indexStr);
    if (findLoc >= 0)
    {
        sql.replace(findLoc, indexStr.length(), wstring(inDir.begin(), inDir.end()));
        std::transform(sql.begin(), sql.end(), sql.begin(), ::tolower);
        vector<int> resultVec = GetIntsFromDB(sql);
        if (resultVec.size() == 1)
            result = resultVec[0];
    }
    return result;
}

// ************************************************************************

void DatabaseManager::AddFile(FileEntry* inEntry)
{
    wstring sql(DBConstants::addFileEntrySQL);

    int dirIndex = FindDir(inEntry->GetPath());
    if (dirIndex > -1)
    {
        const wstring index0Str(L"{0}");
        int index0Loc = sql.find(index0Str);
        char buff[512];
        ltoa(dirIndex, buff, 10);
        string tmpBuff(buff);
        sql.replace(index0Loc, index0Str.length(), wstring(tmpBuff.begin(), tmpBuff.end()));
    }

    const wstring index1Str(L"{1}");
    int index1Loc = sql.find(index1Str);
    sql.replace(index1Loc, index1Str.length(), inEntry->GetFilename());

    const wstring index2Str(L"{2}");
    int index2Loc = sql.find(index2Str);
    sql.replace(index2Loc, index2Str.length(), inEntry->GetHash());
    
    GetStringsFromDB(sql);
}

// ************************************************************************

int DatabaseManager::StringListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames)
{
    if (vec2Fill && colValues)
    {
        vector<wstring>* tmpVec = (vector<wstring>*)vec2Fill;
        if (numCols == 1)
        {
            char* tmpPtr = colValues[0];
            if(tmpPtr)
            {
                string tmp(tmpPtr);
                tmpVec->push_back(wstring(tmp.begin(), tmp.end()));
            }
        }
    }
    return 0;
}

// ************************************************************************

int DatabaseManager::IntListCallback(void* vec2Fill, int numCols, char** colValues, char** colNames)
{
    if (vec2Fill && colValues)
    {
        vector<int>* tmpVec = (vector<int>*)vec2Fill;
        if (numCols == 1)
        {
            tmpVec->push_back(atoi(colValues[0]));
        }
    }
    return 0;
}

// ************************************************************************

vector<wstring> DatabaseManager::GetStringsFromDB(const wstring& inSQL)
{
    vector<wstring> result;
    const wstring dbPath(DBConstants::dbName);
    string strDbPath(dbPath.begin(), dbPath.end());
    sqlite3* db;
    int rc = sqlite3_open(strDbPath.c_str(), &db);
    if (rc == 0)
    {
        char *zErrMsg = 0;
        string sql(inSQL.begin(), inSQL.end());
        rc = sqlite3_exec(db, sql.c_str(), DatabaseManager::StringListCallback, &result, &zErrMsg);
        if (rc == SQLITE_OK)
        {
            sqlite3_close(db);
        }
        else
        {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        }
    }
   return result;
}

// ************************************************************************

vector<int> DatabaseManager::GetIntsFromDB(const wstring& inSQL)
{
    vector<int> result;
    const wstring dbPath(DBConstants::dbName);
    string strDbPath(dbPath.begin(), dbPath.end());
    sqlite3* db;
    int rc = sqlite3_open(strDbPath.c_str(), &db);
    if (rc == 0)
    {
        char *zErrMsg = 0;
        string sql(inSQL.begin(), inSQL.end());
        rc = sqlite3_exec(db, sql.c_str(), DatabaseManager::IntListCallback, &result, &zErrMsg);
        if (rc == SQLITE_OK)
        {
            sqlite3_close(db);
        }
        else
        {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
        }
    }
   return result;
}
