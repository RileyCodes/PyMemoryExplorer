#include "pch.h"
#include "PythonGCMemoryReader.h"

#include "PyMemReader.h"
#include "Util.h"
#include "PyParser/PythonListParser.h"
#include "PyParser/PythonUnicodeParser.h"
#include "PyParser/PythonIntParser.h"
#include "PyParser/PythonLongParser.h"
#include "PyParser/PythonFloatParser.h"


static struct gc_generation generations[NUM_GENERATIONS] = {
	/* PyGC_Head,                               threshold,      count */
	{{{GEN_HEAD(0), GEN_HEAD(0), 0}}, 700, 0},
	{{{GEN_HEAD(1), GEN_HEAD(1), 0}}, 10, 0},
	{{{GEN_HEAD(2), GEN_HEAD(2), 0}}, 10, 0},
};

void PythonGCMemoryReader::FindGCTableAuto(ResultInfo& result)
{
	const auto maxScan = 5294810;
	//GET GC
	int findAddress = GC_BEGIN_ADDRESS;

	int Count = 0;
	while (1)
	{
		Count++;
		void* p = (void*)((pyPtr)this->remoteAddr + (pyPtr)findAddress);

		this->memReader->Read(p, &generations, sizeof(generations));
		if (generations[0].threshold == 700)
		{
			if (generations[1].threshold == 10)
			{
				if (generations[2].threshold == 10)
				{
					pRemoteGCTable = p;
					return;
				}
			}
		}
		findAddress += 1;

		if (Count > maxScan)
		{
			break;
		}
	}
	result.lastError = ErrorType::Err_GCNotFound;
	return;
}

void PythonGCMemoryReader::UpdateGCTable(void* GCTableObjs[], ResultInfo& result)
{
	gcTableSize = 0;
	if (pRemoteGCTable != NULL)
	{
		for (auto i = 0; i < NUM_GENERATIONS; i++)
		{
			pyPtr offsetof = (pyPtr)&generations[i].head - (pyPtr)&generations;

			Table2PtrList(GEN_HEAD_X64(i), ((pyPtr)pRemoteGCTable + (pyPtr)offsetof), GCTableObjs);
		}
		return;
	}
	result.lastError = ErrorType::Err_ReadGCTableFailed;
}

void PythonGCMemoryReader::EnumGCObjects(void* GCTableObjs[1], std::function<void(PythonObjectParser&)> callback)
{
	for (int it = 0; it < gcTableSize; it++)
	{
		PythonObjectParser obj;
		obj.Init(this->memReader, GCTableObjs[it]);
		if (!obj.Parse())
			continue;
		callback(obj);
	}
}

void PythonGCMemoryReader::Table2PtrList(void* gc_list, pyPtr gc_originalRemoteAddr, void* GCTableObjs[1])
{
	pyPtr gc;
	PyGC_Head gc_next;

	gc_next = *(PyGC_Head*)gc_list;

	int i = 0;

	for (gc = gc_next.gc.gc_next; gc != gc_originalRemoteAddr;)
	{
		if (i > GC_OBJECT_MAX)
		{
			break;
		}

		if (gc == NULL)
		{
			break;
		}

		this->memReader->Read((void*)gc_next.gc.gc_next, &gc_next, sizeof(gc_next));
		gc = gc_next.gc.gc_next;

		pyPtr op = FROM_GC(gc);
		GCTableObjs[i] = (void*)op;
		i++;
		gcTableSize++;
	}
	return;
}
