#pragma once
#include"PriorityNode.h"
#include"..\Rest\Order.h"
template <typename T>
class PriorityQueue
{
private :
	
	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
public :
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T>& Q);
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,int priority);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
///////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& Q)
{
	backPtr = frontPtr = NULL;
	PriorityNode<T>* temp = Q.frontPtr;
	while (temp)
	{
		this->enqueue(temp->getItem(), temp->getPriority());
		temp = temp->getNext();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool PriorityQueue<T>::enqueue( const T& newEntry, int priority)
{
	PriorityNode<T>* newNodePtr = new Node<T>(newEntry);
	PriorityNode<T>* ptr;
	PriorityNode<T>* prev;
	newNodePtr->setPriority(priority);
	// Insert the new node
	if (isEmpty() || priority < frontPtr->getPriority())
		frontPtr = newNodePtr; // The queue is empty
	else {
		prev = frontPtr;
		ptr = frontPtr->getNext();
		if (priority > frontPtr->getPriority()) 
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else if (ptr == nullptr || priority>ptr->getPriority()) 
		{
			frontPtr->setNext(newNodePtr);
			newNodePtr->setNext(ptr);
		}
		else
		{
			while (ptr) 
			{
				if (priority > ptr->getPriority) 
				{
					prev->setNext(newNodePtr);
					newNodePtr->setNext(ptr);
					break;
				}
				else 
				{
					prev = ptr;
					ptr = ptr->setNext();
				}
			}
		}
	}
		
	return true ;
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool PriorityQueue<T>:: dequeue(T& frntEntry)
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool PriorityQueue<T>:: peekFront(T& frntEntry) const
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	T x;
	while (frontPtr)
	{
		this->dequeue(x);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count=0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
