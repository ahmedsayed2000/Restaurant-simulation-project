#pragma once
#include "Node.h"

template <typename T>
class List {
private:
	Node<T>* Head;
	int itemcount;
public:
	List();
	List(const List<T>& L);
	bool isEmpty();
	int getlength();
	Node<T>* getHead();
	bool insert(int pos,T Item);
	bool remove(int pos , T entry);
	void clear();
	bool replace(int pos, T Item);
	virtual ~List();
};

template<typename T>
List<T>::List()
{
	Head = nullptr;
	itemcount = 0;
}

template<typename T>
inline List<T>::List(const List<T>& L)
{
	if (!L.Head)
	{
		this->Head = NULL;
		this->itemcount = 0;
		return;
	}
	Node<T>* temp = L.Head;
	while (temp)
	{
		this->insert(this->getlength(), temp->getItem());
		temp = temp->getNext();
	}
}

template<typename T>
inline bool List<T>::isEmpty()
{
	return itemcount <= 0;
}

template<typename T>
inline int List<T>::getlength()
{
	return itemcount;
}

template<typename T>
inline Node<T>* List<T>::getHead()
{
	return Head;
}

template<typename T>
inline bool List<T>::insert(int pos, T Item)
{
	bool ableToInsert = (pos >= 0) && (pos <= itemcount + 1);
	if (ableToInsert)
	{
		Node<T>* ptr = new Node<T>(Item);
		if (pos == 1 || pos == 0) {
			ptr->setNext(Head);
			Head = ptr;
		}
		else {
			Node<T>* prev = Head;
			int count=1;
			while (count < pos) {
				prev = prev->getNext();
				count++;
			}
			ptr->setNext(prev->getNext());
			prev->setNext(ptr);
		}
		itemcount++;
	}
	return ableToInsert;
}

template<typename T>
inline bool List<T>::remove(int pos , T &entry)
{
	bool ableToRemove = (pos >= 1) && (pos <= itemcount);
	if (ableToRemove) {
		Node<T>* ptr = nullptr;
		if (pos == 1) {
			ptr = Head;
			Head = Head->getNext();
		}
		else {
			Node<T>* prev = Head;
			ptr = prev->getNext();
			int count=2;
			while (count < pos) {
				prev = prev->getNext();
				count++;
			}
			ptr = prev->getNext();
			prev->setNext(ptr->getNext());
		}
		entry=ptr->getItem();
		delete ptr;
		ptr = nullptr;
		itemcount--;
	}
	return ableToRemove;
}

template<typename T>
inline void List<T>::clear()
{
	while (!isEmpty())
	{
		remove(1);
	}
}

template<typename T>
inline bool List<T>::replace(int pos, T Item)
{
	Node<T>* temp = Head;
	int i = 0;
	while (temp)
	{
		if (i == pos)
		{
			temp->setItem(item);
			return true;
		}
		else
		{
			i++;
			temp = temp->getNext();
		}
	}
	return false;
}

template<typename T>
inline List<T>::~List()
{
	clear();
}


