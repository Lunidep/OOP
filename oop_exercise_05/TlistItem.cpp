#include "TListItem.h"
#include <iostream>

template <class T>
TListItem<T>::TListItem(const shared_ptr<T> & figure) {
	this->figure = figure;
	this->next = nullptr;
}

template <class T>
TListItem<T>::~TListItem() {}

template <class T>
shared_ptr<TListItem<T>> TListItem<T>::SetNext(shared_ptr<TListItem<T>> next) {
	shared_ptr<TListItem<T>> old = this->next;
	this->next = next;
	return old;
}

template <class T>
shared_ptr<TListItem<T>> TListItem<T>::GetNext() {
	return this->next;
}

template <class T>
shared_ptr<T> TListItem<T>::GetFigure(){
	return this->figure;
}

template <class T>
ostream& operator<<(ostream& os, const TListItem<T>& obj) {
	os << "[" << obj.figure << "]";
	return os;
}

template class TListItem<Hexagon>;
template ostream& operator<<(ostream& out, const TListItem<Hexagon>& obj);
