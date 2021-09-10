#include "PythonTupleParser.h"

#include "../PyMemReader.h"

bool PythonTupleParser::Parse()
{
	CHECK_IS_INITED

	this->memReader->Read(this->remoteAddr, &pyTuple, sizeof(pyTuple));
	if (pyTuple.ob_size > 2000 || pyTuple.ob_size <= 0) return false;

	for (Py_ssize_t i = 0; i < pyTuple.ob_size; i++)
	{
		pyPtr pPtr_to_obitem = NULL;

		pyPtr offsetof = offsetof(PyTupleObject, ob_item);
		pyPtr intp = (pyPtr)this->remoteAddr + offsetof + (i * sizeof(pPtr_to_obitem));

		this->memReader->Read((void*)intp, &pPtr_to_obitem, sizeof(pPtr_to_obitem));

		PythonObjectParser parser;
		parser.Init(this->memReader, (void*)pPtr_to_obitem);
		//dict_value.Init(this->memoryReader, (void*)pyTuple.ob_item[i]);
		if (!parser.Parse())
			continue;
		cppTuple.emplace_back(parser);
	}
	return true;
}
