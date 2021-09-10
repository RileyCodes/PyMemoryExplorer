#pragma once
#include <cstddef>


class SecureByteArray
{
public:

	unsigned char* data = nullptr;
	size_t length = 0;


	SecureByteArray();
	~SecureByteArray();

	void FromByteArray(unsigned char* byte, size_t buffersize);
	void ToByteArray(unsigned char* buffer);
	void Clear();
};
