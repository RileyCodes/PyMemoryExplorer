#pragma once
#include <Windows.h>
#include "PythonParser.h"


class PythonStringParser : public PythonParser
{
public:
	size_t size;

	PyStringObject pyString;
	SmallStringBuffer stringBuffer;
	bool Parse();


	PythonStringParser()
	{
		ZeroMemory(&stringBuffer, sizeof(stringBuffer));
	}
};
