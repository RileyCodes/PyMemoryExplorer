#include "Windows.h"
#include "PythonObjectParser.h"

#include "../PyMemReader.h"

bool PythonObjectParser::Parse(bool lookforDict)
{
	CHECK_IS_INITED

	ZeroMemory(&tp_name, sizeof(tp_name));

	if (!this->memReader->Read((void*)this->remoteAddr, &pyObj, sizeof(pyObj)))
		return false;

	pyPtr tp_nameRemoteAddr = NULL;
	if (!this->memReader->Read((void*)(this->pyObj.ob_type + 24), &tp_nameRemoteAddr, sizeof(pyPtr)))
		return false;

	if (lookforDict)
	{
		if (!this->memReader->Read((void*)(this->pyObj.ob_type + 264), &tp_dictRemoteAddr, sizeof(pyPtr)))
			return false;
	}

	if (!this->memReader->Read((void*)tp_nameRemoteAddr, &tp_name, sizeof(tp_name)))
		return false;

	return true;
}
