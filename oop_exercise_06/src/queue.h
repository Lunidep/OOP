#ifndef QUEUE_H
#define QUEUE_H 1

#include <iostream>
#include <memory>
#include <algorithm>

#include "allocator.h"

template<typename T, typename Allocator = std::allocator<T>>
class Queue {

	struct Node;

public:
	using value_type = T;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using allocator_type = typename Allocator::template rebind<Node>::other;

	class ForwardIterator {
	public:
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;
		friend class Queue;

		ForwardIterator(std::shared_ptr<Node> it = nullptr) : ptr{ it } {}

		ForwardIterator(const ForwardIterator& other) : ptr{ other.ptr } {}

		ForwardIterator operator++();

		ForwardIterator operator++(int);

		reference operator*();

		const_reference operator*() const;

		std::shared_ptr<Node> operator->();

		std::shared_ptr<const Node> operator->() const;

		bool operator==(const ForwardIterator& rhs) const;

		bool operator!=(const ForwardIterator& rhs) const;

		ForwardIterator Next() const;

	private:
		std::weak_ptr<Node> ptr;
	};

	Queue() : size{ 0 } {}

	void Push(const T& val);

	void Pop();

	ForwardIterator Insert(const ForwardIterator it, const T& val);

	ForwardIterator Erase(const ForwardIterator it);

	reference Front();

	const_reference Front() const;

	reference Back();

	const_reference Back() const;

	ForwardIterator Begin();

	ForwardIterator End();

	bool Empty() const;

	size_type Size() const;

	void Swap(Queue& rhs);

	void Clear();

	void Print();

private:

	struct deleter {
		deleter(allocator_type* alloc) : allocator_{ alloc } {}

		void operator()(Node* ptr) {
			if (ptr != nullptr) {
				std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
				allocator_->deallocate(ptr, 1);
			}
		}

	private:
		allocator_type* allocator_;
	};

	struct Node {
		Node(const T& val, std::shared_ptr<Node> next_, std::weak_ptr<Node> prev_) : value{ val }, next{ next_ }, prev{ prev_ } {}

		std::shared_ptr<Node> next{ nullptr, deleter{&allocator} };
		std::weak_ptr<Node> prev{};
		T value;
	};

	allocator_type allocator{};
	std::shared_ptr<Node> head{ nullptr, deleter{&allocator} };
	std::weak_ptr<Node> tail{};
	size_t size;
};

template<typename T, typename Allocator>
void Queue<T, Allocator>::Push(const T& value) {
	Node* newptr = allocator.allocate(1);
	std::allocator_traits<allocator_type>::construct(allocator, newptr, value, std::shared_ptr<Node>{nullptr, deleter{ &allocator }}, std::weak_ptr<Node>{});
	std::shared_ptr<Node> newNode{ newptr, deleter{&allocator} };
	if (!head) {
		head = newNode;
		tail = head;
	}
	else {
		newNode->prev = tail;
		tail.lock()->next = newNode;
		tail = newNode;
	}
	size++;
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::Pop() {
	if (head) {
		head = head->next;
		size--;
	}
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::Insert(const typename Queue<T, Allocator>::ForwardIterator it, const T& val) {
	if (it == ForwardIterator{}) { //пустой список или конец 
		if (tail.lock() == nullptr) { // пустой список
			Push(val);
			return Begin();
		}
		else {
			Push(val);
			return tail.lock();
		}
	}
	Node* newptr = allocator.allocate(1);
	std::allocator_traits<allocator_type>::construct(allocator, newptr, val, std::shared_ptr<Node>{nullptr, deleter{ &allocator }}, std::weak_ptr<Node>{});
	std::shared_ptr<Node> newNode{ newptr, deleter{&allocator} };
	if (it == Begin()) {//начало
		newNode->next = it.ptr.lock();
		it.ptr.lock()->prev = newNode;
		head = newNode;
	}
	else {
		newNode->next = it.ptr.lock();
		it.ptr.lock()->prev.lock()->next = newNode;
		newNode->prev = it->prev;
		it.ptr.lock()->prev.lock() = newNode;
	}

	size++;
	return newNode;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::Erase(const typename Queue<T, Allocator>::ForwardIterator it) {
	if (it == ForwardIterator{}) { //удаление несуществующего элемента
		return End();
	}
	if (it->prev.lock().get() == nullptr && head.get() == tail.lock().get()) { //удаление очереди, состоящей только из одного элемента
		head = nullptr;
		tail = head;
		size = 0;
		return End();
	}
	if (it->prev.lock().get() == nullptr) { //удаление первого элемента
		it->next->prev.lock() = nullptr;
		head = it->next;
		size--;
		return head;
	}
	ForwardIterator res = it.Next();
	if (res == ForwardIterator{}) { //удаление последнего элемента
		it->prev.lock()->next = nullptr;
		size--;
		return End();
	}
	//удаление элементов в промежутке
	it->next->prev = it->prev;
	it->prev.lock()->next = it->next;
	size--;
	return res;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::ForwardIterator::operator++() {
	if (ptr.lock() == nullptr) {
		return *this;
	}
	ptr = ptr.lock()->next;
	return *this;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::ForwardIterator::operator++(int s) {
	if (ptr.lock() == nullptr) {
		return *this;
	}
	ForwardIterator old{ this->ptr.lock() };
	++(*this);
	return old;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::reference Queue<T, Allocator>::ForwardIterator::operator*() {
	return ptr.lock()->value;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::const_reference Queue<T, Allocator>::ForwardIterator::operator*() const {
	return ptr.lock()->value;
}

template<typename T, typename Allocator>
std::shared_ptr<typename Queue<T, Allocator>::Node> Queue<T, Allocator>::ForwardIterator::operator->() {
	return ptr.lock();
}

template<typename T, typename Allocator>
std::shared_ptr<const typename Queue<T, Allocator>::Node> Queue<T, Allocator>::ForwardIterator::operator->() const {
	return ptr.lock();
}

template<typename T, typename Allocator>
bool Queue<T, Allocator>::ForwardIterator::operator==(const typename Queue<T, Allocator>::ForwardIterator& rhs) const {
	return ptr.lock().get() == rhs.ptr.lock().get();
}

template<typename T, typename Allocator>
bool Queue<T, Allocator>::ForwardIterator::operator!=(const typename Queue<T, Allocator>::ForwardIterator& rhs) const {
	return ptr.lock() != rhs.ptr.lock();
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::ForwardIterator::Next() const {
	if (ptr.lock() == nullptr)
		return ForwardIterator{};
	return ptr.lock()->next;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::reference Queue<T, Allocator>::Front() {
	if (head == nullptr)
		throw std::out_of_range("Empty item");
	return this->head->value;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::const_reference Queue<T, Allocator>::Front() const {
	if (head == nullptr)
		throw std::out_of_range("Empty item");
	return this->head->value;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::reference Queue<T, Allocator>::Back() {
	if (head == nullptr)
		throw std::out_of_range("Empty item");
	return this->tail.lock()->value;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::const_reference Queue<T, Allocator>::Back() const {
	if (head == nullptr)
		throw std::out_of_range("Empty item");
	return this->tail.lock()->value;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::Begin() {
	return head;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::ForwardIterator Queue<T, Allocator>::End() {
	return ForwardIterator{};
}

template<typename T, typename Allocator>
bool Queue<T, Allocator>::Empty() const {
	return size == 0;
}

template<typename T, typename Allocator>
typename Queue<T, Allocator>::size_type Queue<T, Allocator>::Size() const {
	return size;
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::Swap(Queue& rhs) {
	std::shared_ptr<Node> temp = head;
	head = rhs.head;
	rhs.head = temp;
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::Clear() {
	head = nullptr;
	tail = head;
	size = 0;
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::Print() {
	ForwardIterator it = Begin();
	std::for_each(Begin(), End(), [it, this](auto e)mutable {
		std::cout << e;
		if (it.Next() != this->End()) {
			std::cout << " <- ";
		}
		it++;
		});
	std::cout << "\n";
}

#endif // QUEUE_H