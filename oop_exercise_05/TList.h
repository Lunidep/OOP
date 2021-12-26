#ifndef TLIST_H
#define	TLIST_H

#include <memory>
#include "Hexagon.h"
#include "TListItem.h"
#include "TIterator.h"

template <class T>
class TList {
public:
	TList();
	virtual ~TList();

	int length();

	void addFirst(shared_ptr<T> &figure);
	void insert(int index, shared_ptr<T> &figure);
	void addLast(shared_ptr<T> &figure);

	bool empty();
	void delElement(int &index);
	void eraseList();

	TIterator<TListItem<T>, T> begin();
	TIterator<TListItem<T>, T> end();
	template <class A> friend ostream& operator<<(ostream& os, const TList<A>& list);
	
private:
	shared_ptr<TListItem<T>> first;
};

#endif	/* TLIST_H */