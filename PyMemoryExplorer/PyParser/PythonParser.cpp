#include "../pch.h"
#include "PythonParser.h"

#include "PythonDictParser.h"
#include "../PyMemReader.h"


void PythonParser::Init(PyMemReader* memoryReader, void* remoteAddr)
{
	this->memReader = memoryReader;
	this->remoteAddr = remoteAddr;
	this->isReady = true;
}
