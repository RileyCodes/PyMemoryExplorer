#include "pch.h"
#include "SecureByteArray.h"
#include "Util.h"


SecureByteArray::SecureByteArray()
{
}


SecureByteArray::~SecureByteArray()
{
	Clear();
}

void SecureByteArray::FromByteArray(unsigned char* byte, size_t buffersize)
{
	Clear();

	data = new unsigned char[buffersize];
	memcpy_s(data, buffersize, byte, buffersize);
	length = buffersize;
}


void SecureByteArray::ToByteArray(unsigned char* buffer)
{
	if (data == nullptr)
	{
		return;
	}
	memcpy_s(buffer, length, data, length);
}

void SecureByteArray::Clear()
{
	if (data != nullptr)
	{
		Util::RandomBytes(data, length);
		delete[]data;
		length = 0;
		data = nullptr;
	}
}
