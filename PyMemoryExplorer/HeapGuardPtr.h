#pragma once

template <class T>
class HeapGuardPtr
{
public:
	T* p = nullptr;


	T* operator->()
	{
		return this->p;
	}

	T& operator*()
	{
		return *(this->p);
	}

	void operator=(T* input)
	{
		if (this->p != nullptr)
		{
			delete p;
			this->p = NULL;
		}
		this->p = input;
		return;
	}

	HeapGuardPtr()
	{
		this->p = NULL;
	}

	~HeapGuardPtr()
	{
		delete p;
	}
};
