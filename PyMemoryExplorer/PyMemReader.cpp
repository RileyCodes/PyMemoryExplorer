#include "pch.h"
#include <Windows.h>
#include <Psapi.h>
#include "PyMemReader.h"


#include "HeapMgr.h"
#include "HeapGuardPtr.h"
#include "PyParser/PythonDictParser.h"

typedef NTSYSAPI NTSTATUS (NTAPI* __ntReadVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG NumberOfBytesToRead,
	PULONG NumberOfBytesReaded
);


auto hModule = LoadLibraryA("ntdll");
auto RVM = reinterpret_cast<__ntReadVirtualMemory>(GetProcAddress(hModule, "NtReadVirtualMemory"));

void PyMemReader::GetPy27ModuleAddress(pyPtr& py27BaseAddr) const
{
	HMODULE hMods[2048];
	DWORD cbNeeded = 0;

	if (EnumProcessModulesEx(processHandle, hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_64BIT))
	{
		for (size_t i = 0; i < (cbNeeded / (sizeof(HMODULE))); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(processHandle, hMods[i], szModName,
			                        sizeof(szModName) / sizeof(TCHAR)))
			{
				if (wcsstr(szModName, L"python27.dll") != nullptr)
				{
					py27BaseAddr = reinterpret_cast<pyPtr>(hMods[i]);
					return;
				}
			}
		}
	}

	DWORD err = GetLastError();

	this->result->lastError = ErrorType::Err_GetPy27ModuleAddress;
	return;
}

void PyMemReader::EnumGC(std::function<void(PythonObjectParser&)> callback)
{
	gcReader.EnumGCObjects(GCTableObjs.p->t, callback);
}


void PyMemReader::InitFrameBasedData()
{
	//Removed
	return;
}

PyMemReader::PyMemReader(HANDLE processHandle, ResultInfo* result)
{
	this->result = result;
	this->processHandle = processHandle;

	GetPy27ModuleAddress(py27BaseAddr);

	if (this->result->lastError != ErrorType::Err_OK)
		return;


	GCTableObjs = HeapMgr::MallocVarArr<void*>(ObjectId::GCTableObjs, new void*[GC_OBJECT_MAX], 0);

	if (this->result->lastError != ErrorType::Err_OK)
		return;

	gcReader.Init(this, reinterpret_cast<void*>(py27BaseAddr));
	gcReader.FindGCTableAuto(*this->result);
	if (this->result->lastError != ErrorType::Err_OK)
		return;

	gcReader.UpdateGCTable(GCTableObjs.p->t, *this->result);

	if (this->result->lastError != ErrorType::Err_OK)
		return;
}

void PyMemReader::Update() const
{
	//Removed
	return;
}


bool PyMemReader::Read(void* readAddr, void* outBuffer, size_t size)
{
	SIZE_T dwSize = 0;

	if (!ReadProcessMemory(processHandle, reinterpret_cast<void*>(reinterpret_cast<INT64>(readAddr)),
	                       static_cast<void*>(outBuffer), size, &dwSize))
	{
		DWORD err = ::GetLastError();
		DWORD exitCode = 0;
		if (GetExitCodeProcess(processHandle, &exitCode) == FALSE)
		{
			//TODO: Some error logging?
			err = ::GetLastError() + 5000;
		}
		else if (exitCode != STILL_ACTIVE)
		{
			err = STILL_ACTIVE;
		}
		return false;
	}
	return true;
}
