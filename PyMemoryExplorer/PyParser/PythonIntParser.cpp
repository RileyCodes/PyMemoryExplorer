#include "PythonIntParser.h"

#include "../PyMemReader.h"


bool PythonIntParser::Parse()
{
	CHECK_IS_INITED

	if (!this->memReader->Read((void*)this->remoteAddr, &pyObj, sizeof(pyObj)))
		return false;
	return true;
}
