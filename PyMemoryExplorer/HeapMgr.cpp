#include "pch.h"
#include "HeapMgr.h"

class SecureByteArray;
std::unordered_map<int, int> HeapMgr::resMap;
std::mutex HeapMgr::lock;

HeapMgr::HeapMgr()
{
}


HeapMgr::~HeapMgr()
{
}
