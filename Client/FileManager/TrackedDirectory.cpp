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
#include "StdAfx.h"
#include "TrackedDirectory.h"
#include "HashManager.h"
#include "DatabaseManager.h"

// need to make sure that inpath ends w/ \\ 
// returns list of subdirectories in outDirs, pushes new files to database
void TrackedDirectory::LoadDirectory(const wstring& inPath, vector<wstring>& outDirs)
{
    wstring searchPath(inPath + L"\\*.*");
    wstring lastBits(searchPath.substr(searchPath.length() - 4));

    HashManager hashMgr;
    DatabaseManager dbMgr;

    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &ffd);
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            const wstring fileName(ffd.cFileName);
            if ((fileName.compare(L".") != 0) && (fileName.compare(L"..") != 0))
                outDirs.push_back(inPath + L"\\" + fileName);
        }
        else
        {
            LARGE_INTEGER filesize;
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            
            wstring tmpFilename(ffd.cFileName);
            std::transform(tmpFilename.begin(), tmpFilename.end(), tmpFilename.begin(), tolower);
            if (tmpFilename.find(L".jpg") != string::npos)
            {
                const wstring hash = hashMgr.HashGen(inPath + wstring(L"\\") + wstring(ffd.cFileName));
                if (dbMgr.FindFile(hash) == -1)
                {
                    FileEntry entry;
                    entry.SetFilename(ffd.cFileName);
                    entry.SetPath(inPath);
                    entry.SetHash(hash);
                    dbMgr.AddFile(&entry);
                }
            }

         //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

/*
    HANDLE hDir = ::CreateFile(inPath.c_str(), 
                               FILE_LIST_DIRECTORY, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
                               NULL, 
                               OPEN_EXISTING, 
                               FILE_FLAG_BACKUP_SEMANTICS, // | FILE_FLAG_OVERLAPPED, 
                               NULL);

    DWORD dwBytes=0;
    FILE_NOTIFY_INFORMATION notifyBuffer;
    BOOL success = ::ReadDirectoryChangesW(hDir, 
                                           &notifyBuffer, 
                                           sizeof(FILE_NOTIFY_INFORMATION), 
                                           TRUE, 
                                           FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME,
                                           &dwBytes,
                                           NULL,
                                           NULL);
*/
    //FILE_NOTIFY_INFORMATION* fni = (FILE_NOTIFY_INFORMATION*)buf;
//CStringW wstr(fni.Data, fni.Length / sizeof(wchar_t));


    int zzzTop = 0;
}