#include <cassert>
#include <windows.h>


#include "PythonDictParser.h"
#include "PythonIntParser.h"
#include "PythonLongParser.h"
#include "PythonStringParser.h"
#include "../HeapMgr.h"
#include "../HeapGuardPtr.h"
#include "../PyMemReader.h"


#define MAX_DICT_ENTRIES_SIZE 2000
#define MAX_DICT_ENTRIES_BUFFER MAX_DICT_ENTRIES_SIZE * sizeof(PyDictEntry)
#define PERTURB_SHIFT 5


PyDictEntry* PythonDictParser::lookdict_int(PyDictObject* mp, long long key, register long hash, PyDictEntry* ep)
{
	register size_t i;
	register size_t perturb;
	register PyDictEntry* freeslot;
	register size_t mask = (size_t)mp->ma_mask;
	PyDictEntry* ep0 = (PyDictEntry*)ep;
	//register PyDictEntry *ep;

	pyPtr dummy = (pyPtr)this->memReader->py27DictDummy;

	i = hash & mask;
	ep = &ep0[i];

	long long keyLong = 0;
	if (ep->me_key != NULL)
	{
		PythonIntParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyLong = dict_keyname.pyObj.ob_ival;
	}


	//if (ep->me_key == NULL || ep->me_key == (pyPtr)key)
	//    return ep;
	if (ep->me_key == dummy)
		freeslot = ep;
	else
	{
		if (ep->me_hash == hash && keyLong == key)
			return ep;
		freeslot = NULL;
	}

	/* In the loop, me_key == dummy is by far (factor of 100s) the
	   least likely outcome, so test for that last. */
	for (perturb = hash; ; perturb >>= PERTURB_SHIFT)
	{
		i = (i << 2) + i + perturb + 1;
		ep = &ep0[i & mask];
		if (ep->me_key == NULL)
			return freeslot == NULL ? ep : freeslot;

		PythonIntParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyLong = dict_keyname.pyObj.ob_ival;

		if (/*ep->me_key == (pyPtr)key*/(ep->me_hash == hash
			&& ep->me_key != dummy
			&& keyLong == key))
			return ep;
		if (ep->me_key == dummy && freeslot == NULL)
			freeslot = ep;
	}
	assert(0); /* NOT REACHED */
	return 0;
}


PyDictEntry* PythonDictParser::lookdict_long(PyDictObject* mp, long long key, register long hash, PyDictEntry* ep)
{
	register size_t i;
	register size_t perturb;
	register PyDictEntry* freeslot;
	register size_t mask = (size_t)mp->ma_mask;
	PyDictEntry* ep0 = (PyDictEntry*)ep;
	//register PyDictEntry *ep;

	pyPtr dummy = (pyPtr)this->memReader->py27DictDummy;

	auto maxBufferAddress = (pyPtr)ep + MAX_DICT_ENTRIES_BUFFER;

	i = hash & mask;
	ep = &ep0[i];
	if ((pyPtr)ep >= maxBufferAddress)
	{
		return NULL;
	}


	long long keyLong = 0;
	if (ep->me_key != NULL)
	{
		//MAX_DICT_ENTRIES_BUFFER
		PythonLongParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyLong = dict_keyname.Value;
	}


	//if (ep->me_key == NULL || ep->me_key == (pyPtr)key)
	//    return ep;
	if (ep->me_key == dummy)
		freeslot = ep;
	else
	{
		if (ep->me_hash == hash && keyLong == key)
			return ep;
		freeslot = NULL;
	}

	/* In the loop, me_key == dummy is by far (factor of 100s) the
	   least likely outcome, so test for that last. */
	for (perturb = hash; ; perturb >>= PERTURB_SHIFT)
	{
		i = (i << 2) + i + perturb + 1;
		ep = &ep0[i & mask];
		if (ep->me_key == NULL)
			return freeslot == NULL ? ep : freeslot;

		PythonLongParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyLong = dict_keyname.Value;

		if (/*ep->me_key == (pyPtr)key*/(ep->me_hash == hash
			&& ep->me_key != dummy
			&& keyLong == key))
			return ep;
		if (ep->me_key == dummy && freeslot == NULL)
			freeslot = ep;
	}
	assert(0); /* NOT REACHED */
	return 0;
}


PythonDictParser::PythonDictParser()
{
}

PyDictEntry* PythonDictParser::lookdict_string(PyDictObject* mp, string key, register long hash, PyDictEntry* ep)
{
	register size_t i;
	register size_t perturb;
	register PyDictEntry* freeslot;
	register size_t mask = (size_t)mp->ma_mask;
	PyDictEntry* ep0 = (PyDictEntry*)ep;
	//register PyDictEntry *ep;

	auto a = sizeof(PyDictEntry);

	pyPtr dummy = (pyPtr)this->memReader->py27DictDummy;

	i = hash & mask;
	ep = &ep0[i];

	std::string keyName = "";
	if (ep->me_key != NULL)
	{
		PythonStringParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyName.assign(dict_keyname.stringBuffer.buffer, dict_keyname.size);
	}


	//if (ep->me_key == NULL || ep->me_key == (pyPtr)key)
	//    return ep;
	if (ep->me_key == dummy)
		freeslot = ep;
	else
	{
		if (ep->me_hash == hash && keyName == key)
			return ep;
		freeslot = NULL;
	}

	/* In the loop, me_key == dummy is by far (factor of 100s) the
	   least likely outcome, so test for that last. */
	for (perturb = hash; ; perturb >>= PERTURB_SHIFT)
	{
		i = (i << 2) + i + perturb + 1;
		ep = &ep0[i & mask];
		if (ep->me_key == NULL)
			return freeslot == NULL ? ep : freeslot;

		PythonStringParser dict_keyname;
		dict_keyname.Init(this->memReader, (void*)ep->me_key);
		if (!dict_keyname.Parse())
			return NULL;

		keyName.assign(dict_keyname.stringBuffer.buffer, dict_keyname.size);

		if (/*ep->me_key == (pyPtr)key*/(ep->me_hash == hash
			&& ep->me_key != dummy
			&& keyName == key))
			return ep;
		if (ep->me_key == dummy && freeslot == NULL)
			freeslot = ep;
	}
	assert(0); /* NOT REACHED */
	return 0;
}


bool PythonDictParser::Parse(std::set<string>& requestedKeys)
{
	//int x=string_hash("124");
	CHECK_IS_INITED

	if (!this->memReader->Read(this->remoteAddr, &pyDict, sizeof(pyDict)))
		return false;

	if (pyDict.ma_mask > 10000 || pyDict.ma_mask <= 0)
		return false;

	size_t dict_entries_size = min(MAX_DICT_ENTRIES_BUFFER, (pyDict.ma_mask + 1) * sizeof(PyDictEntry));
	size_t dict_entries_count = dict_entries_size / sizeof(PyDictEntry);

	static thread_local HeapGuardPtr<HeapGuard<PyDictEntry, void(*)(void*)>> ptr_dict_entries;

	if (!ptr_dict_entries.p)
		ptr_dict_entries = HeapMgr::MallocVarArr<PyDictEntry>(ObjectId::DictEntries, new
		                                                      PyDictEntry[MAX_DICT_ENTRIES_SIZE],
		                                                      MAX_DICT_ENTRIES_BUFFER);


	if (!this->memReader->Read((void*)pyDict.ma_table, ptr_dict_entries->t, dict_entries_size))
		return false;
	//lookdict_string

	if (requestedKeys.size() == 0)
	{
		for (Py_ssize_t i = 0; i < dict_entries_count; ++i)
		{
			PythonStringParser dict_keyname;
			dict_keyname.Init(this->memReader, (void*)ptr_dict_entries->t[i].me_key);
			if (!dict_keyname.Parse())
				continue;

			std::string keyName(dict_keyname.stringBuffer.buffer, dict_keyname.size);

			static std::set<string> targeting;
			if (!requestedKeys.empty())
			{
				if (requestedKeys.count(keyName) == 0)
				{
					continue;
				}
			}

			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)ptr_dict_entries->t[i].me_value);
			if (!dict_value.Parse())
				continue;

			content[keyName] = dict_value;
		}
	}
	else
	{
		for (auto requestedKey : requestedKeys)
		{
			int hash = 0;

			PyDictEntry* dict_entry = NULL;
			hash = string_hash(requestedKey);

			dict_entry = lookdict_string(&pyDict, requestedKey, hash, ptr_dict_entries->t);
			if (dict_entry == NULL)
				continue;


			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)dict_entry->me_value);
			if (!dict_value.Parse())
				continue;


			content[requestedKey] = dict_value;
		}
	}

	return true;
}

bool PythonDictParser::ParseLong(std::set<INT64>& wishedKeys)
{
	//int x=string_hash("124");

	CHECK_IS_INITED

	if (!this->memReader->Read(this->remoteAddr, &pyDict, sizeof(pyDict)))
		return false;

	if (pyDict.ma_mask > 10000 || pyDict.ma_mask <= 0)
		return false;

	size_t dict_entries_size = min(MAX_DICT_ENTRIES_BUFFER, (pyDict.ma_mask + 1) * sizeof(PyDictEntry));
	size_t dict_entries_count = dict_entries_size / sizeof(PyDictEntry);

	static thread_local HeapGuardPtr<HeapGuard<PyDictEntry, void(*)(void*)>> ptr_dict_entries;


	if (!ptr_dict_entries.p)
		ptr_dict_entries = HeapMgr::MallocVarArr<PyDictEntry>(ObjectId::DictEntries_Long,
		                                                      new PyDictEntry[MAX_DICT_ENTRIES_SIZE],
		                                                      MAX_DICT_ENTRIES_BUFFER);


	if (!this->memReader->Read((void*)pyDict.ma_table, ptr_dict_entries->t, dict_entries_size))
		return false;
	//lookdict_string

	if (wishedKeys.size() == 0)
	{
		for (Py_ssize_t i = 0; i < dict_entries_count; ++i)
		{
			PythonLongParser dict_keyname;
			dict_keyname.Init(this->memReader, (void*)ptr_dict_entries->t[i].me_key);
			if (!dict_keyname.Parse())
				continue;

			int hash = 0;

			PyDictEntry* dict_entry = NULL;

			PyLongObject wishedkeyInPy;
			PyLong_FromLongLong(dict_keyname.Value, &wishedkeyInPy);

			hash = long_hash(&wishedkeyInPy);
			dict_entry = lookdict_long(&pyDict, dict_keyname.Value, hash, ptr_dict_entries->t);
			if (dict_entry == NULL)
				continue;


			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)dict_entry->me_value);
			if (!dict_value.Parse())
				continue;


			longdict[dict_keyname.Value] = dict_value;
		}
	}
	else
	{
		for (auto wished_key : wishedKeys)
		{
			int hash = 0;

			PyDictEntry* dict_entry = NULL;

			PyLongObject wishedkeyInPy;
			PyLong_FromLongLong(wished_key, &wishedkeyInPy);

			hash = long_hash(&wishedkeyInPy);
			dict_entry = lookdict_long(&pyDict, wished_key, hash, ptr_dict_entries->t);
			if (dict_entry == NULL)
				continue;


			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)dict_entry->me_value);
			if (!dict_value.Parse())
				continue;


			longdict[wished_key] = dict_value;
		}
	}

	return true;
}

bool PythonDictParser::ParseInt(std::set<long>& wishedKeys)
{
	CHECK_IS_INITED

	if (!this->memReader->Read(this->remoteAddr, &pyDict, sizeof(pyDict)))
		return false;

	if (pyDict.ma_mask > 10000 || pyDict.ma_mask <= 0)
		return false;

	size_t dict_entries_size = min(MAX_DICT_ENTRIES_BUFFER, (pyDict.ma_mask + 1) * sizeof(PyDictEntry));
	size_t dict_entries_count = dict_entries_size / sizeof(PyDictEntry);

	static thread_local HeapGuardPtr<HeapGuard<PyDictEntry, void(*)(void*)>> ptr_dict_entries;


	if (!ptr_dict_entries.p)
		ptr_dict_entries = HeapMgr::MallocVarArr<PyDictEntry>(ObjectId::DictEntries_Int,
		                                                      new PyDictEntry[MAX_DICT_ENTRIES_SIZE],
		                                                      MAX_DICT_ENTRIES_BUFFER);


	if (!this->memReader->Read((void*)pyDict.ma_table, ptr_dict_entries->t, dict_entries_size))
		return false;
	//lookdict_string

	if (wishedKeys.size() == 0)
	{
		for (Py_ssize_t i = 0; i < dict_entries_count; ++i)
		{
			PythonIntParser dict_keyname;
			dict_keyname.Init(this->memReader, (void*)ptr_dict_entries->t[i].me_key);
			if (!dict_keyname.Parse())
				continue;

			int hash = 0;

			PyDictEntry* dict_entry = NULL;

			PyIntObject wishedkeyInPy;
			wishedkeyInPy.ob_ival = dict_keyname.pyObj.ob_ival;

			hash = int_hash(&wishedkeyInPy);
			dict_entry = lookdict_int(&pyDict, dict_keyname.pyObj.ob_ival, hash, ptr_dict_entries->t);
			if (dict_entry == NULL)
				continue;


			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)dict_entry->me_value);
			if (!dict_value.Parse())
				continue;


			longdict[dict_keyname.pyObj.ob_ival] = dict_value;
		}
	}
	else
	{
		for (auto wished_key : wishedKeys)
		{
			int hash = 0;

			PyDictEntry* dict_entry = NULL;

			PyIntObject wishedkeyInPy;
			wishedkeyInPy.ob_ival = wished_key;

			hash = int_hash(&wishedkeyInPy);
			dict_entry = lookdict_int(&pyDict, wished_key, hash, ptr_dict_entries->t);
			if (dict_entry == NULL)
				continue;


			PythonObjectParser dict_value;
			dict_value.Init(this->memReader, (void*)dict_entry->me_value);
			if (!dict_value.Parse())
				continue;


			longdict[wished_key] = dict_value;
		}
	}

	return true;
}
