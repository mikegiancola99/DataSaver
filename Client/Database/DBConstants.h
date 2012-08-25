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

using namespace std;

class DBConstants
{
public:
    static const wstring dbName;
    
    // saved content table stuff
    static const wstring savedContentTable;
    static const wstring createSavedContentTable;
    static const wstring addFileEntrySQL;
    static const wstring findFileEntryByHashSQL;
    static const wstring findQueuedContent;
    static const wstring updateContentState;

    // managed dirs table stuff
    static const wstring managedDirsTable;
    static const wstring createManagedTypesTable;
    static const wstring createManagedDirsTable;
    static const wstring find_A_DirSQL;
    static const wstring getALLDirsSQL;
    static const wstring addManagedDirSQL;
    static const wstring findDirByRowIdSQL;

    // managed types table stuff
    static const wstring managedTypesTable;
    static const wstring addManagedTypeSQL;
    static const wstring addServerSQL;
    static const wstring find_A_TypeSQL;    
    static const wstring getALLTypesSQL;
    
    static const wstring selectAllSQL;
private:
};