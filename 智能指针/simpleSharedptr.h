#pragma once
struct controlBlock
{
	int ref_count;
	controlBlock() :ref_count(1) {};
};
	template<typename T>
class simpleSharedptr
	{
	private:
		T* ptr;
		controlBlock* control;
		void release();
	public:
		simpleSharedptr();
		explicit simpleSharedptr(T* p);
		~simpleSharedptr();
		simpleSharedptr(const simpleSharedptr& other);
		simpleSharedptr& operator=(const simpleSharedptr& other);
		simpleSharedptr(simpleSharedptr&& other)noexcept;
		simpleSharedptr operator=(simpleSharedptr&& other)noexcept;
		T* operator->()const;
		T& operator*()const;
		T* get();
		int use_count();
		void reset(T* p = nullptr);
	};

