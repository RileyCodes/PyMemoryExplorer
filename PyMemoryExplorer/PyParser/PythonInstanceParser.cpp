#include "PythonInstanceParser.h"


#include "PythonDictParser.h"
#include "../PyDefine.h"
#include "../PyMemReader.h"

bool PythonInstanceParser::Parse()
{
	CHECK_IS_INITED

	if (!this->memReader->Read((void*)this->remoteAddr, &pyInstance, sizeof(pyInstance)))
		return false;

	in_dict.Init(this->memReader, (void*)pyInstance.in_dict);
	if (!in_dict.Parse())
		return false;

	PyClassObject pyClassObj;


	if (!this->memReader->Read((void*)this->pyInstance.in_class, &pyClassObj, sizeof(pyClassObj)))
		return false;


	PythonDictParser cl_dict;
	cl_dict.Init(this->memReader, (void*)pyClassObj.cl_dict);
	if (!cl_dict.Parse())
		return false;
	return true;
}
