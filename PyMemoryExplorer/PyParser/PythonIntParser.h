#pragma once
#include "PythonParser.h"
#include "../PyDefine.h"

class PythonIntParser : public PythonParser
{
public:

	PyIntObject pyObj;
	bool Parse();
};
