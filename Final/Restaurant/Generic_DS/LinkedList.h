# pragma once
#include"Node.h"
# include<iostream>
using namespace std;

template<typename T>
class LinkedList
{
	Node<T>* Head;
	int counter;

	Node<T>* Get_ptr_to(int index);
public:
	LinkedList();
	LinkedList(const LinkedList<T>& L1);
	void InsertEnd(T val);
	bool deleteNode(T val);
	bool isempty();
	bool contains(T val);
	int  get_count();
	T& operator[](int index);
	void print();
	Node<T>* get_Head();
	void clear();
	~LinkedList();
};
template<class T>
LinkedList<T>::~LinkedList()
{
	clear();
}
template<typename T>
inline Node<T>* LinkedList<T>::Get_ptr_to(int index)
{
	int count = 0;
	Node<T>* itr = Head;
	while (itr && count != index) {
		itr = itr->getNext();
		count++;
	}
	return itr;

}

template<typename T>
inline LinkedList<T>::LinkedList() {
	Head = NULL;
	counter = 0;
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& L1)
{
	Head = NULL;
	counter = 0;
	Node<T>* itr = L1.Head;
	while (itr)
	{
		InsertEnd(itr->data);
		itr = itr->getNext();
	}
}

template<typename T>
inline void LinkedList<T>::InsertEnd(T val)
{
	Node<T>* NEW = new Node<T>;
	NEW->setItem(val);
	NEW->setNext(NULL);
	counter++;

	if (Head == NULL) 
	{
		Head = NEW;
		return;
	}

	Node<T>* lastNode = Head;
	while (lastNode->getNext()) lastNode = lastNode->getNext();
	lastNode->setNext(NEW);

}

template<typename T>
inline bool LinkedList<T>::deleteNode(T val)
{

	if (Head == NULL) return false;

	
	if (Head->getItem() == val)
	{
		if (Head->getNext() == NULL)
		{
			delete Head;
			Head = NULL;
			counter = 0;
			return true;
		}

		Node<T>* temp = Head;
		Head = Head->getNext();
		delete temp;
		counter--;
		return true;
	}

	//THE VAL IS NOT IN THE HEAD
	Node<T>* itr = Head->getNext();
	Node<T>* prev = Head;
	while (itr) 
	{
		if (itr->getItem()== val)
		{
			prev->setNext(itr->getNext());
			delete itr;
			counter--;
			return true;
		}
		prev = itr;
		itr = itr->getNext();
	}

	//NO VAL FOUND IN THE WHOLE DAMN LIST
	return false;
}

template<typename T>
inline void LinkedList<T>::clear()
{
	Node<T>* itr = Head;
	Node<T>* temp;
	while (itr)
	{
		temp = itr->getNext();
		delete itr;
		itr = temp;
	}
	Head = NULL;
	counter = 0;
}

template<typename T>
inline bool LinkedList<T>::isempty()
{
	return counter == 0;
}

template<typename T>
inline bool LinkedList<T>::contains(T val)
{
	Node<T>* itr = Head;
	while (itr) 
	{
		if (itr->getItem() == val) return true;
		itr = itr->getNext();
	}
	return false;
}

template<typename T>
inline int LinkedList<T>::get_count()
{
	return counter;
}

template<typename T>
inline T& LinkedList<T>::operator[](int index)
{
	if (index >= 0 && index < counter)
	{
		Node<T>* node=Get_ptr_to(index);
		return node->getItem();
	}
	else
	{
		throw "\nLINKED LIST ERROR 1 : INVALID INDEX";
	}
}

template<typename T>
inline void LinkedList<T>::print()
{
	std::cout << "\n{ ";
	Node<T>* itr = Head;
	while (itr) 
	{
		std::cout << itr->getItem()<< "  ";
		itr = itr->getNext();
	}
	std::cout << "}\n";
}

template<typename T>
inline Node<T>* LinkedList<T>::get_Head()
{
	return Head;
}
