#include "TList.h"
#include "TIterator.h"


template <class T>
TList<T>::TList() {	first = nullptr;}

template <class T>
TList<T>::~TList() { cout << "List deleted!" << endl; }

template <class T>
int TList<T>::length() {
	int i = 0;
	shared_ptr<TListItem<T>> item = this->first;
	while (item != nullptr){
		item = item->GetNext();
		i++;
	}
	return i;
}

template <class T>
void TList<T>::addFirst(shared_ptr<T> &figure) {
	shared_ptr<TListItem<T>> other = make_shared<TListItem<T>>(figure);

	other->SetNext(first);
	first = other;
}

template <class T>
void TList<T>::insert(int index, shared_ptr<T> &figure) {
	shared_ptr<TListItem<T>> iter = this->first;
	shared_ptr<TListItem<T>> other = make_shared<TListItem<T>>(figure);
	
	if (index == 1) {
		other->SetNext(iter);
		this->first = other;
	}
	else {
		if (index <= this->length()) {
			for (int i = 1; i < index - 1; ++i) {
				iter = iter->GetNext();
			}
			other->SetNext(iter->GetNext());
			iter->SetNext(other);
		}
		else {
			throw invalid_argument("Index error!\n\n");
		}
	}
}

template <class T>
void TList<T>::addLast(shared_ptr<T> &figure) {
	shared_ptr<TListItem<T>> other = make_shared<TListItem<T>>(figure);
	shared_ptr<TListItem<T>> iter = this->first;
	if (first != nullptr) {
		while (iter->GetNext() != nullptr) {
			iter = iter->SetNext(iter->GetNext());
		}
		iter->SetNext(other);
		other->SetNext(nullptr);
	}
	else {
		first = other;
	}
}

template <class T>
bool TList<T>::empty() {
	return first == nullptr;
}

template <class T>
void TList<T>::delElement(int &index) {
	shared_ptr<TListItem<T>>iter = this->first;
	if (index <= this->length()) {
		if (index == 1) {
			this->first = iter->GetNext();
		}
		else {
			for (int i = 1; i < index - 1; ++i) {
				iter = iter->GetNext();
			}
			iter->SetNext(iter->GetNext()->GetNext());
		}
	}
	else {
		throw invalid_argument("Index error!\n\n");
	}
	
}

template <class T>
void TList<T>::eraseList() {
	first = nullptr;
}

template <class T>
TIterator<TListItem<T>, T> TList<T>::begin() {
	return TIterator<TListItem<T>, T>(first);
}

template <class T>
TIterator<TListItem<T>, T> TList<T>::end() {
	return TIterator<TListItem<T>, T>(nullptr);
}

template <class T>
ostream& operator<<(ostream& os, const TList<T>& list) {
	shared_ptr<TListItem<T>> item = list.first;
	int i = 1;
	while (item != nullptr) {
		cout << "[" << i << "]";
		item->GetFigure()->Print();
		item = item->GetNext();
		i++;
	}
	return os;
}

template class TList<Hexagon>;
template ostream& operator<<(ostream &out, const TList<Hexagon> &figure);
