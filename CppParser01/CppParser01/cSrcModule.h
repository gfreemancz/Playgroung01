#pragma once


#include "stdafx.h"

#include <iostream>
#include <string>

class cSrcModule
{
public:
	cSrcModule();
	cSrcModule(std::string arg_FileName);
	~cSrcModule();

	//getters and setters
	ui32 getFileSize(void) { return FileSize; }
	ui32 getLineCount(void) { return LineCount; }
	std::string & getNameReference(void) { return FileName; }
	std::string & getContentReference(void) { return FileContent; }

private:
	std::string FileName;
	std::string FileContent;
	ui32 FileSize;
	ui32 LineCount;
};

