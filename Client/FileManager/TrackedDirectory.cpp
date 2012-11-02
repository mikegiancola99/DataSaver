// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "StdAfx.h"
#include "TrackedDirectory.h"
#include <Windows.h>
#include "HashManager.h"

typedef void (CALLBACK *FileChangeCallback)(LPTSTR, DWORD, LPARAM);
typedef struct tagDIR_MONITOR
{
	OVERLAPPED ol;
	HANDLE     hDir;
	BYTE       buffer[32 * 1024];
	LPARAM     lParam;
	DWORD      notifyFilter;
	BOOL       fStop;
	FileChangeCallback callback;
} *HDIR_MONITOR;

void TrackedDirectory::LoadDirectory(const wstring& inPath, vector<FileEntry>& outFiles, vector<wstring>& outDirs)
{
    wstring searchPath(inPath + L"\\*.*");
    wstring lastBits(searchPath.substr(searchPath.length() - 4));

    HashManager hashMgr;

    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &ffd);
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            wstring fileName(ffd.cFileName);
            if ((fileName.compare(L".") != 0) && (fileName.compare(L"..") != 0))
            {
                outDirs.push_back(fileName);
            }
        }
        else
        {
            LARGE_INTEGER filesize;
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;

            const wstring hash = hashMgr.HashGen(inPath + wstring(L"\\") + wstring(ffd.cFileName));
            FileEntry entry;
            entry.SetFilename(ffd.cFileName);
            entry.SetPath(inPath);
            entry.SetHash(hash);
            outFiles.push_back(entry);

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

}

void TrackedDirectory::WatchDirectory(vector<wstring> inDirsToWatch)
{
    HDIR_MONITOR pMonitor = (HDIR_MONITOR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*pMonitor));

	pMonitor->hDir = CreateFile(L"C:\\temp", 
                                FILE_LIST_DIRECTORY, 
                                FILE_SHARE_READ | FILE_SHARE_WRITE | 
                                FILE_SHARE_DELETE,
	                            NULL, 
                                OPEN_EXISTING, 
                                FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, 
                                NULL);

	if (pMonitor->hDir != INVALID_HANDLE_VALUE)
	{
		pMonitor->ol.hEvent    = CreateEvent(NULL, TRUE, FALSE, NULL);
		pMonitor->notifyFilter =  FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_FILE_NAME;
		//pMonitor->callback     = callback;

        ReadDirectoryChangesW(pMonitor->hDir, pMonitor->buffer, sizeof(pMonitor->buffer), FALSE, pMonitor->notifyFilter, NULL, &pMonitor->ol, MonitorCallback);

//		if (RefreshMonitoring(pMonitor))
//		{
//			return pMonitor;
//		}
//		else
//		{
//			CloseHandle(pMonitor->ol.hEvent);
//			CloseHandle(pMonitor->hDir);
	//	}
	}

	HeapFree(GetProcessHeap(), 0, pMonitor);
}

VOID CALLBACK TrackedDirectory::MonitorCallback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
	TCHAR                    szFile[MAX_PATH];
	PFILE_NOTIFY_INFORMATION pNotify;
	HDIR_MONITOR             pMonitor  = (HDIR_MONITOR) lpOverlapped;
	size_t                   offset    =  0;
	//BOOL RefreshMonitoring(HDIR_MONITOR pMonitor);

	if (dwErrorCode == ERROR_SUCCESS)
	{
		do
		{
			pNotify = (PFILE_NOTIFY_INFORMATION) &pMonitor->buffer[offset];
			offset += pNotify->NextEntryOffset;
            lstrcpynW(szFile, pNotify->FileName, min(MAX_PATH, pNotify->FileNameLength / sizeof(WCHAR) + 1));
			pMonitor->callback(szFile, pNotify->Action, pMonitor->lParam);

		} while (pNotify->NextEntryOffset != 0);
	}

//	if (!pMonitor->fStop)
//	{
//		RefreshMonitoring(pMonitor);
//	}
}