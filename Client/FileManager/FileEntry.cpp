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

void FileEntry::SetRowId(int inRowId)
{ m_rowId = inRowId; }

wstring FileEntry::GetFilename()
{ return m_filename; }

wstring FileEntry::GetPath()
{ return m_path; }

wstring FileEntry::GetHash()
{ return m_hash; }

int FileEntry::GetFileSize()
{ return m_filesize; }

int FileEntry::GetRowId()
{ return m_rowId; }