#pragma once
#include "PythonParser.h"
#include "PythonDictParser.h"


class PythonInstanceParser : public PythonParser
{
public:

	PythonDictParser in_dict;
	PyInstanceObject pyInstance;
	bool Parse();
};
