#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/PyMemoryExplorer.lib")
#else
#pragma comment(lib, "../x64/Release/PyMemoryExplorer.lib")
#endif


#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

#include "../PyMemoryExplorer/const.h"
#include "../PyMemoryExplorer/PyMemReader.h"
#include "../PyMemoryExplorer/PyParser/PythonDictParser.h"
#include "../PyMemoryExplorer/PyParser/PythonListParser.h"
#include "../PyMemoryExplorer/PyParser/PythonStringParser.h"
#include "../PyMemoryExplorer/PyParser/PythonTupleParser.h"

HANDLE GetProcessByName(const std::wstring& processName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, processName.c_str()) == 0)
			{
				const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				CloseHandle(snapshot);
				return hProcess;
			}
		}
	}

	CloseHandle(snapshot);
	return nullptr;
}

void Run()
{
	auto* hProcess = GetProcessByName(L"python.exe");
	if (hProcess == nullptr)
	{
		printf("ERROR: Unable to find process. \n");
		return;
	}

	ResultInfo resInfo;
	PyMemReader pyMemReader(hProcess, &resInfo);
	if (resInfo.lastError != ErrorType::Err_OK)
	{
		string errMsg = "ERROR: Failed in PyMemReader, Last error was:" +
			std::to_string(static_cast<int>(resInfo.lastError)) + "\n";
		printf(errMsg.c_str());
		return;
	}

	int totalObjectsCount = 0;

	pyMemReader.EnumGC([&pyMemReader, &totalObjectsCount](PythonObjectParser& obj)
	{
		totalObjectsCount++;
		string objsFound = "Objects found: " + std::string(obj.tp_name) + "\n";
		printf(objsFound.c_str());

		if (strcmp(obj.tp_name, "dict") == 0)
		{
			PythonDictParser dictParser;
			dictParser.Init(&pyMemReader, obj.remoteAddr);
			if (dictParser.Parse())
			{
				int x = 0;
			}
		}
		else if (strcmp(obj.tp_name, "list") == 0)
		{
			PythonListParser parser;
			parser.Init(&pyMemReader, obj.remoteAddr);
			if (parser.Parse())
			{
				int x = 0;
			}
		}
		else if (strcmp(obj.tp_name, "list") == 0)
		{
			PythonListParser parser;
			parser.Init(&pyMemReader, obj.remoteAddr);
			if (parser.Parse())
			{
				int x = 0;
			}
		}
		else if (strcmp(obj.tp_name, "tuple") == 0)
		{
			PythonTupleParser parser;
			parser.Init(&pyMemReader, obj.remoteAddr);
			if (parser.Parse())
			{
				for (auto tupleItem : parser.cppTuple)
				{
					if (strcmp(tupleItem.tp_name, "str") == 0)
					{
						PythonStringParser parser;
						parser.Init(&pyMemReader, tupleItem.remoteAddr);
						if (parser.Parse())
						{
							int x = 0;
						}
					}
				}
			}
		}
	});

	string objsFound = "Total Objects found: " + std::to_string(totalObjectsCount) + "\n";
	printf(objsFound.c_str());
}

int main()
{
	Run();
	system("pause");
}
