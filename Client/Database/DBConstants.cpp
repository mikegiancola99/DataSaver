// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "DBConstants.h"

const wstring DBConstants::dbName            = L"dataSaver.db";

const wstring DBConstants::managedDirsTable  = L"managed_dirs";
const wstring DBConstants::managedTypesTable = L"managed_types";
const wstring DBConstants::savedContentTable = L"saved_content";

const wstring DBConstants::createManagedDirsTable  = L"CREATE TABLE " + DBConstants::managedDirsTable  + L" (dir)";
const wstring DBConstants::createManagedTypesTable = L"CREATE TABLE " + DBConstants::managedTypesTable + L" (type)";
const wstring DBConstants::createSavedContentTable = L"CREATE TABLE " + DBConstants::savedContentTable + L" (int dirIndex, filename, md5)";

const wstring DBConstants::find_A_DirSQL  = L"SELECT rowid FROM " + DBConstants::managedDirsTable  + L" WHERE dir='{0}'";
const wstring DBConstants::find_A_TypeSQL = L"SELECT rowid FROM " + DBConstants::managedTypesTable + L" WHERE type='{0}'";
const wstring DBConstants::getALLDirsSQL  = L"SELECT dir  FROM " + DBConstants::managedDirsTable;
const wstring DBConstants::getALLTypesSQL = L"SELECT type FROM " + DBConstants::managedTypesTable;

const wstring DBConstants::addManagedDirSQL        = L"INSERT INTO "  + DBConstants::managedDirsTable  + L"(dir) values ('{0}')";
const wstring DBConstants::addManagedTypeSQL       = L"INSERT INTO "  + DBConstants::managedTypesTable + L"(type) values ('{0}')";

const wstring DBConstants::addFileEntrySQL         = L"INSERT INTO " + DBConstants::savedContentTable + L"(dirIndex, filename, md5) values ({0}, '{1}', '{2}')";
const wstring DBConstants::findFileEntryByHashSQL  = L"SELECT rowid FROM " + DBConstants::savedContentTable + L" WHERE md5='{0}'";

const wstring DBConstants::selectAllSQL      = L"SELECT * FROM ";