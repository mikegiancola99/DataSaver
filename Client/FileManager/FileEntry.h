// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
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

    wstring GetFilename();
    wstring GetPath();
    wstring GetHash();
    int     GetFileSize();

private:
    wstring m_filename;
    wstring m_path;
    wstring m_hash;
    int     m_filesize;
};