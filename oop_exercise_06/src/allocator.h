#ifndef ALLOCATOR_H
#define ALLOCATOR_H 1

#include <iostream>
#include <exception>
#include "allqueue.h"


template<typename T, size_t ALLOC_SIZE>
class allocator {
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using is_always_equal = std::false_type;

	template<typename U>
	struct rebind {
		using other = allocator<U, ALLOC_SIZE>;
	};

	allocator() : begin{ new char[ALLOC_SIZE] },
		end{ begin + ALLOC_SIZE }, tail{ begin } {}

	allocator(const allocator&) = delete;
	allocator(allocator&&) = delete;

	~allocator() {
		delete[] begin;
		begin = end = tail = nullptr;
		buf.~AllQueue();
	}

	T* allocate(size_t n) {
		if (n != 1) {
			throw std::logic_error("This allocator can't allocate arrays");
		}
		if (end - tail < sizeof(T)) {
			if (!buf.Empty()) {
				char* ptr = buf.Back();
				buf.PopBack();
				return reinterpret_cast<T*>(ptr);
			}
			throw std::bad_alloc();
		}
		T* result = reinterpret_cast<T*>(tail);
		tail += sizeof(T);
		return result;
	}

	void deallocate(T* ptr, size_t n) {
		if (n != 1) {
			throw std::logic_error("This allocator can't deallocate arrays");
		}
		if (ptr == nullptr) {
			return;
		}
		buf.PushBack(reinterpret_cast<char*>(ptr));
	}

private:
	char* begin;
	char* end;
	char* tail;
	AllQueue<char*> buf;
};

#endif