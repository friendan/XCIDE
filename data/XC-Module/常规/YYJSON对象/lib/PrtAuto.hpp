#pragma once
#include <atomic>

template<typename T>
class PtrAuto {
	typedef void(*CustomFree)(T* obj);

private:
	T* m_obj;
	std::atomic<int>* counter;
	CustomFree customfree = NULL;

	void release() {
		if (--(*counter) == 0) {
			delete counter;
			if (m_obj) {
				if (customfree)
					customfree(m_obj);
				else
					delete m_obj;
			}
		}
	}

public:
	PtrAuto(const PtrAuto& other) :
		m_obj(other.m_obj),
		counter(other.counter) {
		(*counter)++;
	}

	PtrAuto(T* obj) :
		m_obj(obj),
		counter(new std::atomic<int>(1)) {
	}

	PtrAuto<T>& operator = (const PtrAuto<T>& other) {
		if (this != &other) {
			this->release();
			counter = other.counter;
			m_obj = other.m_obj;
			++(*counter);
		}
		return *this;
	}

	~PtrAuto() { release(); }

	T* operator *() { return m_obj; }

	T* get() { return *m_obj; }

	void fn_release(CustomFree custom_release) { customfree = custom_release; }
};


