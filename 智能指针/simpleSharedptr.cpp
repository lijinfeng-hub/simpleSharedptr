#include "simpleSharedptr.h"
template<typename T>
void simpleSharedptr<T>::release()
{
		if (control)
		{
			--control->ref_count;
			if (!control->ref_count)
			{
				delete ptr;
				ptr = nullptr;
				delete control;
				control = nullptr;
			}
		}
}
template<typename T>
simpleSharedptr<T>::simpleSharedptr() :ptr(nullptr), control(nullptr) {}
template<typename T>
simpleSharedptr<T>::simpleSharedptr(T* p) : ptr(p)
{
	if (p)
	{
		control = new controlBlock();
	}
	else
	{
		control = nullptr;
	}
}
template<typename T>
simpleSharedptr<T>::~simpleSharedptr()
{
	if (ptr)
	{
		release();
	}
}
template<typename T>
simpleSharedptr<T>::simpleSharedptr(const simpleSharedptr& other) :
	ptr(other.ptr), control(other.control)
{
	if (control)
	{
		++control->ref_count;
	}
}
template<typename T>
simpleSharedptr<T>::simpleSharedptr(const simpleSharedptr& other) :
	ptr(other.ptr), control(other.control)
{
	if (control)
	{
		++control->ref_count;
	}
}
template<typename T>
simpleSharedptr<T>&simpleSharedptr<T>::operator=(const simpleSharedptr& other)
{
	if (this != &other)
	{
		release();
		ptr = other.ptr;
		control = other.control;
		if (control)
		{
			++control->ref_count;
		}
	}
	return *this;
}
template<typename T>
simpleSharedptr<T>::simpleSharedptr(simpleSharedptr&& other)noexcept
	:ptr(other.ptr), control(other.control)
{
	other.ptr = nullptr;
	other.control = nullptr;
}
template<typename T>
simpleSharedptr<T>simpleSharedptr<T>::operator=(simpleSharedptr&& other)noexcept
{
	if (this != other)
	{
		ptr = other.ptr;
		control = other.control;
		other.ptr = nullptr;
		other.control = nullptr;
	}
	return *this;
}
template<typename T>
T* simpleSharedptr<T>::operator->()const
{
	return ptr;
}
template<typename T>
T& simpleSharedptr<T>::operator*()const
{
	return *ptr;
}
template<typename T>
T* simpleSharedptr<T>::get()
{
	return ptr;
}
template<typename T>
int simpleSharedptr<T>:: use_count()
{
	return control ? control->ref_count : 0;
}
template<typename T>
void simpleSharedptr<T>:: reset(T* p)
{
	release();
	ptr = p;
	if (p)
	{
		control = new controlBlock();
	}
	else
	{
		control = nullptr;
	}
}