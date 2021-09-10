#include "PythonListParser.h"

#include "../PyMemReader.h"

bool PythonListParser::Parse()
{
	CHECK_IS_INITED

	this->memReader->Read(this->remoteAddr, &pyList, sizeof(pyList));

	if (pyList.ob_size > 50000 || pyList.ob_size <= 0)
		return false;

	//https://stackoverflow.com/questions/46664007/why-do-tuples-take-less-space-in-memory-than-lists

	pyPtr offsetofOb_Item = offsetof(PyListObject, ob_item);
	void* pPtrToObItemList = NULL;

	pyPtr intp = (pyPtr)this->remoteAddr + offsetofOb_Item;
	this->memReader->Read((void*)intp, &pPtrToObItemList, sizeof(pPtrToObItemList));
	for (Py_ssize_t i = 0; i < pyList.ob_size; i++)
	{
		pyPtr pPtr_to_obitem = NULL;

		pyPtr intp2 = (pyPtr)pPtrToObItemList + (i * sizeof(pPtr_to_obitem));

		this->memReader->Read((void*)intp2, &pPtr_to_obitem, sizeof(pPtr_to_obitem));

		ItemsRemoteAddr.push_back(pPtr_to_obitem);
	}
	return true;
}
