#pragma once
#include <vector>
#include "PythonObjectParser.h"

using std::vector;

class PythonListParser : public PythonParser
{
public:

	PyListObject pyList;
	vector<pyPtr> ItemsRemoteAddr{};

	PythonListParser() = default;

	bool Parse();

	~PythonListParser() = default;
};
