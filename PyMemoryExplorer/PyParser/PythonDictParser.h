#pragma once


#include <set>
#include <unordered_map>


#include "PythonObjectParser.h"
#include "PythonParser.h"

using std::string;

class PythonDictParser : public PythonParser
{
public:

	PyDictObject pyDict;

	std::unordered_map<std::string, PythonObjectParser> content{};
	std::unordered_map<__int64, PythonObjectParser> longdict{};

	PythonDictParser();


	PyDictEntry* lookdict_string(PyDictObject* mp, string key, register long hash, PyDictEntry* ep);
	PyDictEntry* lookdict_int(PyDictObject* mp, long long key, long hash, PyDictEntry* ep);
	PyDictEntry* lookdict_long(PyDictObject* mp, long long key, register long hash, PyDictEntry* ep);

	bool Parse(std::set<string>& wKeys);
	bool ParseLong(std::set<__int64>& wishedKeys);
	bool ParseInt(std::set<long>& wishedKeys);

	bool Parse()
	{
		std::set<string> dummy;
		return Parse(dummy);
	}

	bool ParseLong()
	{
		std::set<long long> dummy;
		return ParseLong(dummy);
	}

	bool ParseInt()
	{
		std::set<long> dummy;
		return ParseInt(dummy);
	}

	~PythonDictParser() = default;
};
