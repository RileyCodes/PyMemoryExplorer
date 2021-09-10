#include "PythonUnicodeParser.h"
#include <windows.h>
#include "../PyDefine.h"
#include "../PyMemReader.h"

bool PythonUnicodeParser::Parse()
{
	CHECK_IS_INITED

	if (!this->memReader->Read((void*)this->remoteAddr, &pyUnicode, sizeof(pyUnicode)))
		return false;

	int UnicodeLength = pyUnicode.length * 2;
	if (UnicodeLength <= 0)
		return false;

	if (UnicodeLength >= 5000)
		return false;

	size_t offsetof = offsetof(PyUnicodeObject, str);

	void* pToString = NULL;

	this->memReader->Read((void*)((pyPtr)this->remoteAddr + (pyPtr)offsetof), &pToString, sizeof(pToString));

	this->memReader->Read(pToString, &stringBuffer, min(sizeof(stringBuffer), UnicodeLength));

	return true;
}


bool PythonUnicodeParser::ParseLargeBuffer(wchar_t* LargeBuffer, int size)
{
	CHECK_IS_INITED

	if (!this->memReader->Read((void*)this->remoteAddr, &pyUnicode, sizeof(pyUnicode)))
		return false;

	int UnicodeLength = pyUnicode.length * 2;
	if (UnicodeLength <= 0)
		return false;

	if (UnicodeLength >= size)
		return false;

	size_t offsetof = offsetof(PyUnicodeObject, str);

	void* pToString = NULL;

	this->memReader->Read((void*)((pyPtr)this->remoteAddr + (pyPtr)offsetof), &pToString, sizeof(pToString));

	this->memReader->Read(pToString, LargeBuffer, min(size, UnicodeLength));

	return true;
}
