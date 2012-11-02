// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "HashManager.h"
#include <windows.h>
#include <Wincrypt.h>

#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>

#define BUFSIZE 1024
#define MD5LEN  16

wstring HashManager::HashGen(const wstring& inFilename)
{
                    int byteTotal = 0;

    HCRYPTHASH hHash = 0;
    HCRYPTPROV hProv = 0;
    HANDLE hFile = CreateFile(inFilename.c_str(), GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile)
    {
        
        BOOL success = CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
        if (success)
        {
            success = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);
            if (success)
            {
                BYTE rgbFile[BUFSIZE];
                DWORD cbRead = 0;
                success = ReadFile(hFile, rgbFile, BUFSIZE, &cbRead, NULL);
                while (success && (0 != cbRead))
                {
                    byteTotal += cbRead;
                    CryptHashData(hHash, rgbFile, cbRead, 0);
                    success = ReadFile(hFile, rgbFile, BUFSIZE, &cbRead, NULL);
                }
            }
        }
    }

    DWORD cbHash = MD5LEN;
    BYTE rgbHash[MD5LEN];
    char buffer[MD5LEN];
    
    string tmp;

    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        CHAR rgbDigits[] = "0123456789abcdef";
        for (DWORD i = 0; i < cbHash; i++)
        {
             printf("%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
             sprintf_s(buffer, MD5LEN, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
             tmp += buffer;
        }
    }

    

    if (hHash)
        CryptDestroyHash(hHash);
    
    if(hProv)
        CryptReleaseContext(hProv, 0);
    
    if(hFile)
        CloseHandle(hFile);
        
    wstring result(tmp.begin(), tmp.end());
    return result; 
}