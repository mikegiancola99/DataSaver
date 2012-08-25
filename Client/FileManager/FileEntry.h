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

#include <String>
using namespace std;

class FileEntry
{
public:
    void SetFilename(const wstring& inName);
    void SetPath(const wstring& inPath);
    void SetHash(const wstring& inMD5);
    void SetFilesize(int inSize);
    void SetRowId(int inRowId);

    wstring GetFilename();
    wstring GetPath();
    wstring GetHash();
    int     GetFileSize();
    int     GetRowId();

private:
    wstring m_filename;
    wstring m_path;
    wstring m_hash;
    int     m_filesize;
    int     m_rowId;
};