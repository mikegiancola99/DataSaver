// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#pragma once
#include <string>
#include "FileEntry.h"

using namespace std;

class DataXFer
{
public:
    bool SendFile(const wstring& inFile);
    bool SendPostback();
private:
};