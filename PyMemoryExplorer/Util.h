#pragma once
#include "pch.h"
#include "SecureByteArray.h"

template <class T, class lambda>
class HeapGuard;

template <class T>
class HeapGuardPtr;

class Util
{
public:
	Util() = default;
	~Util() = default;

	static void RandomBytes(unsigned char* buffer, size_t& size);


	static std::string GetRandomString(int length);
	static std::string bin2hex(std::string const& s);
	static std::string hex2bin(std::string const& s);

	static void RemoteLog(std::string Log, int errorCode, int Step);


	static void Log(LogErrLevel level, LogType logType);
	static void Log(LogErrLevel level, LogType logType,
	                HeapGuardPtr<HeapGuard<SecureByteArray, void(*)(void*)>>& addtInfo);
};
