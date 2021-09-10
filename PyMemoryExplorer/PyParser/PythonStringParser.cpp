#include "../pch.h"
#include "PythonStringParser.h"

#include <windows.h>


#include "../PyDefine.h"
#include "../PyMemReader.h"

bool PythonStringParser::Parse()
{
	CHECK_IS_INITED


	if (!this->memReader->Read((void*)this->remoteAddr, &pyString, sizeof(pyString)))
		return false;

	if (pyString.ob_size <= 0)
		return false;

	if (pyString.ob_size >= 5000)
		return false;

	size = min(sizeof(stringBuffer), pyString.ob_size);

	size_t offsetof = offsetof(PyStringObject, ob_sval);
	this->memReader->Read((void*)((pyPtr)this->remoteAddr + (pyPtr)offsetof), &stringBuffer, size);

	return true;
}
