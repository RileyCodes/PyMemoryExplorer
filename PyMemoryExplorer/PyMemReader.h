#pragma once
#include <functional>

#include "HeapMgr.h"
#include "pch.h"
#include "PythonGCMemoryReader.h"
#include "PyParser/PythonObjectParser.h"

class PythonDictParser;
class PythonInstanceParser;

struct ReadByteeErr
{
	int locationMark;
	DWORD err;
};

class PyMemReader
{
public:
	void* py27DictDummy = nullptr;
	pyPtr py27BaseAddr = 0;
	HANDLE processHandle = nullptr;

	PyInterpreterState interpreterState;
	PyThreadState threadState;
	PyObject f_locals;
	PyDictObject f_globals;
	PythonGCMemoryReader gcReader;

	HeapGuardPtr<HeapGuard<void*, void(*)(void*)>> GCTableObjs;

	void InitFrameBasedData();
	ResultInfo* result = nullptr;

	PyMemReader(HANDLE processHandle, ResultInfo* result);

	void GetPy27ModuleAddress(pyPtr& py27BaseAddr) const;
	void EnumGC(std::function<void(PythonObjectParser&)> callback);
	bool Read(void* readAddr, void* outBuffer, size_t size);
	void Update() const;
};
