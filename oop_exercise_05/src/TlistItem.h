#ifndef TLISTITEM_H
#define	TLISTITEM_H

#include "Hexagon.h"
#include <memory>


template <class T>
class TListItem {
public:
	TListItem(const shared_ptr<T> &figure);
	template <class A> friend ostream& operator<<(ostream& os, const TListItem<A>& obj);

	shared_ptr<TListItem<T>> SetNext(shared_ptr<TListItem<T>> next);
	shared_ptr<TListItem<T>> GetNext();
	shared_ptr<T> GetFigure();

	virtual ~TListItem();
private:
	shared_ptr<T> figure;
	shared_ptr<TListItem<T>> next;
};

#endif