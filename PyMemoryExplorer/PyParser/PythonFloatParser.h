#pragma once
#include "PythonParser.h"
#include "../PyDefine.h"

class PythonFloatParser : public PythonParser
{
public:
	PyFloatObject pyObj;
	bool Parse();
};
