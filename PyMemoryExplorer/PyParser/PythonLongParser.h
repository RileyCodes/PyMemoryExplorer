#pragma once
#include "PythonParser.h"
#include "../PyDefine.h"

class PythonLongParser : public PythonParser
{
public:

	PyLongObject pyObj;

	long long Value = 0;
	bool Parse();
};
