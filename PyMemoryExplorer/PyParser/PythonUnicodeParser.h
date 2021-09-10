#pragma once
#include <windows.h>
#include "PythonParser.h"
#include "../PyDefine.h"


class PythonUnicodeParser : public PythonParser
{
public:

	SmallWStringBuffer stringBuffer;

	int size;

	PyUnicodeObject pyUnicode;
	bool Parse();
	bool ParseLargeBuffer(wchar_t* LargeBuffer, int size);


	PythonUnicodeParser()
	{
		ZeroMemory(&stringBuffer, sizeof(stringBuffer));
	}
};
