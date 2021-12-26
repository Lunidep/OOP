#ifndef AllQueue_H
#define AllQueue_H 1

#include <iostream>
#include <iterator> 
#include <exception>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>



template<typename T>
class AllQueue {
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	class Iterator {
	public:
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::random_access_iterator_tag;

		Iterator(value_type* it = nullptr) : ptr{ it } {}

		Iterator(const Iterator& other) : ptr{ other.ptr } {}

		Iterator& operator=(const Iterator& other) {
			ptr = other.ptr;
			return *this;
		}

		Iterator operator--() {
			ptr--;
			return *this;
		}

		Iterator operator--(int s) {
			Iterator it = *this;
			--(*this);
			return it;
		}

		Iterator operator++() {
			ptr++;
			return *this;
		}

		Iterator operator++(int s) {
			Iterator it = *this;
			++(*this);
			return it;
		}

		reference operator*() {
			return *ptr;
		}

		pointer operator->() {
			return ptr;
		}

		bool operator==(const Iterator rhs) const {
			return ptr == rhs.ptr;
		}

		bool operator!=(const Iterator rhs) const {
			return ptr != rhs.ptr;
		}

		reference operator[](difference_type n) {
			return *(*this + n);
		}

		template<typename U>
		friend U& operator+=(U& r, typename U::difference_type n);

		template<typename U>
		friend U operator+(U a, typename U::difference_type n);

		template<typename U>
		friend U operator+(typename U::difference_type, U a);

		template<typename U>
		friend U& operator-=(U& r, typename U::difference_type n);

		template<typename U>
		friend typename U::difference_type operator-(U b, U a);

		template<typename U>
		friend bool operator<(U a, U b);

		template<typename U>
		friend bool operator>(U a, U b);

		template<typename U>
		friend bool operator==(U a, U b);

		template<typename U>
		friend bool operator>=(U a, U b);

		template<typename U>
		friend bool operator<=(U a, U b);

	private:
		value_type* ptr;
	};

	using iterator = Iterator;
	using const_iterator = const Iterator;


	AllQueue() : storageSize{ 0 }, alreadyUsed{ 0 }, storage{ new value_type[1] } {}

	AllQueue(size_t size) {
		if (size < 0) {
			throw std::logic_error("size must be >= 0");
		}
		alreadyUsed = 0;
		storageSize = size;
		storage = new value_type[size + 1];
	}

	~AllQueue() {
		alreadyUsed = storageSize = 0;
		delete[] storage;
		storage = nullptr;
	}

	size_t Size() const {
		return alreadyUsed;
	}

	bool Empty() const {
		return Size() == 0;
	}

	iterator Begin() {
		if (!Size())
			return nullptr;
		return storage;
	}

	iterator End() {
		if (!Size())
			return nullptr;
		return (storage + alreadyUsed);
	}

	const_iterator Begin() const {
		if (!Size())
			return nullptr;
		return storage;
	}

	const_iterator End() const {
		if (!Size())
			return nullptr;
		return (storage + alreadyUsed);
	}

	reference Front() {
		return storage[0];
	}

	const_reference Front() const {
		return storage[0];
	}

	reference Back() {
		return storage[alreadyUsed - 1];
	}

	const_reference Back() const {
		return storage[alreadyUsed - 1];
	}

	reference At(size_t index) {
		if (index < 0 || index >= alreadyUsed) {
			throw std::out_of_range("the index must be greater than or equal to zero and less than the number of elements");
		}

		return storage[index];
	}

	const_reference At(size_t index) const {
		if (index < 0 || index >= alreadyUsed) {
			throw std::out_of_range("the index must be greater than or equal to zero and less than the number of elements");
		}

		return storage[index];
	}

	reference operator[](size_t index) {
		return storage[index];
	}

	const_reference operator[](size_t index) const {
		return storage[index];
	}

	size_t getStorageSize() const {
		return storageSize;
	}

	void PushBack(const T& value) {
		if (alreadyUsed < storageSize) {
			storage[alreadyUsed] = value;
			++alreadyUsed;
			return;
		}

		size_t nextSize = 1;
		if (!Empty()) {
			nextSize = storageSize * 2;
		}

		AllQueue<T> next{ nextSize };
		next.alreadyUsed = alreadyUsed;
		std::copy(Begin(), End(), next.Begin());
		next[alreadyUsed] = value;
		++next.alreadyUsed;
		Swap(*this, next);
	}

	void PopBack() {
		if (alreadyUsed) {
			alreadyUsed--;
		}
	}

	iterator Erase(const_iterator pos) {
		AllQueue<T> newAllQueue{ getStorageSize() };
		Iterator newIt = newAllQueue.Begin();
		for (Iterator it = Begin(); it != pos; it++, newIt++) {
			*newIt = *it;
		}
		Iterator result = newIt;
		for (Iterator it = pos + 1; it != End(); it++, newIt++) {
			*newIt = *it;
		}
		newAllQueue.alreadyUsed = alreadyUsed - 1;
		Swap(*this, newAllQueue);

		return result;
	}


	template<typename U>
	friend void Swap(AllQueue<U>& lhs, AllQueue<U>& rhs);

private:
	size_t storageSize;
	size_t alreadyUsed;
	value_type* storage;
};

template<typename T>
T& operator+=(T& r, typename T::difference_type n) {
	r.ptr = r.ptr + n;
	return r;
}

template<typename T>
T operator+(T a, typename T::difference_type n) {
	T temp = a;
	temp += n;
	return temp;
}

template<typename T>
T operator+(typename T::difference_type n, T a) {
	return a + n;
}

template<typename T>
T& operator-=(T& r, typename T::difference_type n) {
	r.ptr = r.ptr - n;
	return r;
}

template<typename T>
typename T::difference_type operator-(T b, T a) {
	return b.ptr - a.ptr;
}

template<typename T>
bool operator<(T a, T b) {
	return a - b < 0 ? true : false;
}

template<typename T>
bool operator>(T a, T b) {
	return b < a;
}

template<typename T>
bool operator==(T a, T b) {
	return a - b == 0 ? true : false;
}

template<typename T>
bool operator>=(T a, T b) {
	return a > b || a == b;
}

template<typename T>
bool operator<=(T a, T b) {
	return a < b || a == b;
}

template<typename U>
void Swap(AllQueue<U>& lhs, AllQueue<U>& rhs) {
	std::swap(lhs.alreadyUsed, rhs.alreadyUsed);
	std::swap(lhs.storageSize, rhs.storageSize);
	std::swap(lhs.storage, rhs.storage);
}

#endif