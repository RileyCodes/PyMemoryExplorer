#pragma once

#include "PyParser/PythonParser.h"

#include <array>
#include <functional>
#include <set>
#include <unordered_map>

#include "PyParser/PythonObjectParser.h"

using std::set;
using std::string;
using std::unordered_map;

class PythonGCMemoryReader : public PythonParser
{
public:
	int gcTableSize = 0;
	void* pRemoteGCTable = nullptr;

	void FindGCTableAuto(ResultInfo& result);
	void Table2PtrList(void* gc_list, pyPtr gc_originalRemoteAddr, void* GCTableObjs[1]);
	void UpdateGCTable(void* GCTableObjs[], ResultInfo& result);
	void EnumGCObjects(void* GCTableObjs[], std::function<void(PythonObjectParser&)> callback);


	PythonGCMemoryReader() = default;
};
