#pragma once
#include "PythonObjectParser.h"
#include <vector>

using std::vector;

class PythonTupleParser : public PythonParser
{
public:

	PyTupleObject pyTuple;
	vector<PythonObjectParser> cppTuple;

	bool Parse();

	PythonTupleParser() = default;
	~PythonTupleParser() = default;
};
