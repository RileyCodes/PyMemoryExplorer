#include "PythonLongParser.h"

#include "../PyMemReader.h"

long long safePow(long long v1, long long v2)
{
	long long res = v1;
	if (v2 == NULL)
		return 1;

	v2--;
	for (int i = 0; i < v2; i++)
	{
		res = res * v1;
	}
	return res;
}

bool PythonLongParser::Parse()
{
	CHECK_IS_INITED

	int size = sizeof(pyObj);

	if (!this->memReader->Read((void*)this->remoteAddr, &pyObj, sizeof(pyObj)))
		return false;

	if (pyObj.ob_size > 19 || pyObj.ob_size < 0)
		return false;

	if (pyObj.ob_size == 0)
	{
		Value = 0;
		return true;
	}

	for (int i = 0; i < pyObj.ob_size; i++)
	{
		Value += pyObj.ob_digit[i] * (safePow(2, PyLong_SHIFT * i));
	}
	return true;
}
