#pragma once
#include "../pch.h"
#include "PythonParser.h"

class PythonObjectParser : public PythonParser
{
public:

	PyObject pyObj;
	pyPtr tp_dictRemoteAddr = NULL;
	char tp_name[32];
	bool Parse(bool lookforDict = false);
};
