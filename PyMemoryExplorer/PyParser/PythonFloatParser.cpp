#include "PythonFloatParser.h"

#include "../PyMemReader.h"


bool PythonFloatParser::Parse()
{
	CHECK_IS_INITED

	if (!this->memReader->Read(static_cast<void*>(this->remoteAddr), &pyObj, sizeof(pyObj)))
		return false;
	return true;
}
