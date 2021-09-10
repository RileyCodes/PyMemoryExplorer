#pragma once
#include <cassert>

#include "pch.h"
#include "HeapGuardPtr.h"
#include <mutex>
#include <unordered_map>
#include "SecureByteArray.h"
#include "Util.h"


using std::unordered_map;
using std::lock_guard;


template <class T, class lambda>
class HeapGuard
{
public:
	T* t;
	int id;
	lambda deleteAction;
	HeapGuard<T, lambda>(int id, T* t, lambda ld);
	~HeapGuard<T, lambda>();
};


class HeapMgr
{
public:

	static std::unordered_map<int, int> resMap;
	static std::mutex lock;
	template <class T>
	static HeapGuard<T, void(*)(void*)>* MallocVar(int position, void* p, int pSize);

	template <class T>
	static HeapGuard<T, void(*)(void*)>* MallocVarArr(ObjectId position, void* p, int pSize);

	HeapMgr();
	~HeapMgr();
};


template <class T, class lambda>
HeapGuard<T, lambda>::HeapGuard(int id, T* t, lambda ld)
{
	std::lock_guard<std::mutex> guard(HeapMgr::lock);
	this->id = id;
	this->t = t;
	this->deleteAction = ld;

	std::unordered_map<int, int>::iterator it = HeapMgr::resMap.find(id);
	const int count = (it == HeapMgr::resMap.end()) ? 1 : it->second + 1;
	HeapMgr::resMap[id] = count;
	if (count > MAX_INSTANCE_COUNT)
	{
		GuradReport report;
		report.Count = count;
		report.id = id;


		HeapGuardPtr<HeapGuard<SecureByteArray, void(*)(void*)>> info;
		info = HeapMgr::MallocVar<SecureByteArray>(id, new SecureByteArray(), sizeof(SecureByteArray));
		info->t->FromByteArray(reinterpret_cast<unsigned char*>(&report), sizeof(id));

		Util::Log(LogErrLevel::Warning, LogType::TooManyInstance, info);
	}
}


template <class T, class lambda>
HeapGuard<T, lambda>::~HeapGuard()
{
	lock_guard<std::mutex> guard(HeapMgr::lock);
	const unordered_map<int, int>::iterator it = HeapMgr::resMap.find(id);

	if (it == HeapMgr::resMap.end())
	{
		assert(false);
		return;
	}
	HeapMgr::resMap[id] = it->second--;
	deleteAction(t);
}


template <class T>
HeapGuard<T, void(*)(void*)>* HeapMgr::MallocVar(int position, void* p, int pSize)
{
	return new HeapGuard<T, void(*)(void*)>(position, (T*)p, [](void* p) -> void
	{
		T* ptoDel = (T*)p;
		delete ptoDel;
	});
}

template <class T>
HeapGuard<T, void(*)(void*)>* HeapMgr::MallocVarArr(ObjectId position, void* p, int pSize)
{
	auto Buffer = new HeapGuard<T, void(*)(void*)>(static_cast<int>(position), (T*)p, [](void* p) -> void
	{
		T* ptoDel = (T*)p;
		delete[] ptoDel;
	});

	if (pSize > 0)
		ZeroMemory(p, pSize);
	return Buffer;
}
