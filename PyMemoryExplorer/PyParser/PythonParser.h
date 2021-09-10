#pragma once
#include "../pch.h"
class PyMemReader;

class PythonParser
{
public:

	PyMemReader* memReader;
	void* remoteAddr = nullptr;
	bool isReady = false;
	void Init(PyMemReader* memoryReader, void* remoteAddr);
	PythonParser() = default;
	~PythonParser() = default;
};
