// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#pragma once
#include <string>

using namespace std;

class DBConstants
{
public:
    static const wstring dbName;
    
    static const wstring managedDirsTable;
    static const wstring managedTypesTable;
    static const wstring savedContentTable;
    
    static const wstring createManagedDirsTable;
    static const wstring createManagedTypesTable;
    static const wstring createSavedContentTable;

    static const wstring addManagedDirSQL;
    static const wstring addManagedTypeSQL;
    static const wstring addServerSQL;

    static const wstring find_A_DirSQL;
    static const wstring find_A_TypeSQL;
    static const wstring getALLDirsSQL;
    static const wstring getALLTypesSQL;
    static const wstring addFileEntrySQL;
    static const wstring findFileEntryByHashSQL;

    static const wstring selectAllSQL;
private:
};