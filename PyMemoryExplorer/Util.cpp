#include "pch.h"
#include <random>
#include <string>
#include <iomanip>
#include "Util.h"

struct SingleLog
{
	int level;
	time_t time;
};


std::string Util::GetRandomString(int length)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, length); // assumes 32 < number of characters in str         
}

void Util::RandomBytes(unsigned char* buffer, size_t& size)
{
}

std::string Util::bin2hex(const std::string& input)
{
	std::string res;
	const char hex[] = "0123456789ABCDEF";
	for (auto sc : input)
	{
		auto c = static_cast<unsigned char>(sc);
		res += hex[c >> 4];
		res += hex[c & 0xf];
	}
	std::transform(res.begin(), res.end(), res.begin(), ::tolower);
	return res;
}

std::string Util::hex2bin(std::string const& s)
{
	std::string sOut;
	sOut.reserve(s.length() / 2);

	std::string extract;
	for (std::string::const_iterator pos = s.begin(); pos < s.end(); pos += 2)
	{
		try
		{
			extract.assign(pos, pos + 2);
			sOut.push_back(std::stoi(extract, nullptr, 16));
		}
		catch (std::invalid_argument e)
		{
			return "";
		}
	}
	return sOut;
}


void Util::Log(LogErrLevel level, LogType logType)
{
}


void Util::Log(LogErrLevel level, LogType logType, HeapGuardPtr<HeapGuard<SecureByteArray, void(*)(void*)>>& addtInfo)
{
}
