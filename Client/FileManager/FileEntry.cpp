// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "stdafx.h"
#include "FileEntry.h"

void FileEntry::SetFilename(const wstring& inName)
{  m_filename = inName; }

void FileEntry::SetPath(const wstring& inPath)
{ m_path = inPath; }

void FileEntry::SetHash(const wstring& inMD5)
{ m_hash = inMD5; }

void FileEntry::SetFilesize(int inSize)
{ m_filesize = inSize; }

wstring FileEntry::GetFilename()
{ return m_filename; }

wstring FileEntry::GetPath()
{ return m_path; }

wstring FileEntry::GetHash()
{ return m_hash; }

int FileEntry::GetFileSize()
{ return m_filesize; }