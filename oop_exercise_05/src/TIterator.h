#ifndef TITERATOR_H
#define TITERATOR_H

#include <memory>
#include <iostream>
using namespace std;

template <class N, class T>
class TIterator{
public:
	TIterator(shared_ptr<N> n) {
		cur = n;
	}

	shared_ptr<T> operator* () {
		return cur->GetFigure();
	}

	shared_ptr<T> operator-> () {
		return cur->GetFigure();
	}

	void operator++() {
		cur = cur->GetNext();
	}

	TIterator operator++ (int) {
		TIterator cur(*this);
		++(*this);
		return cur;
	}

	bool operator== (const TIterator &i) {
		return (cur == i.cur);
	}

	bool operator!= (const TIterator &i) {
		return (cur != i.cur);
	}

private:
	shared_ptr<N> cur;
};

#endif