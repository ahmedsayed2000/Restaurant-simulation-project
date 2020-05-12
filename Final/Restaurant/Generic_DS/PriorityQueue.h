#pragma once
#include"..\Rest\Order.h"
#include<iostream>
using namespace std;
//=================   Class Definition =====================//

template < typename T>
class PriorityNode
{
private:
	T item; // A data item
	PriorityNode<T>* next; // Pointer to next node
	double priority;
public:

	PriorityNode()
	{
		next = nullptr;
	}

	PriorityNode(const T& r_Item)
	{
		item = r_Item;
		next = nullptr;
	}

	PriorityNode(const T& r_Item, PriorityNode<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}

	void setItem(const T& r_Item)
	{
		item = r_Item;
	}

	void setNext(PriorityNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem() const
	{
		return item;
	}

	PriorityNode<T>* getNext() const
	{
		return next;
	}

	void setPriority(double pri)
	{
		priority = pri;
	}

	double getPriority()
	{
		return priority;
	}

};


template <typename T>
class PriorityQueue
{
private :
	
	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
public :
	PriorityQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;

	}

		PriorityQueue(const PriorityQueue<T>& Q)
		{
			backPtr = frontPtr = NULL;
			PriorityNode<T>* temp = Q.frontPtr;
			while (temp)
			{
				this->enqueue(temp->getItem(), temp->getPriority());
				temp = temp->getNext();
			}
		}

		bool isEmpty() const
		{
			return frontPtr == nullptr;
		}

		bool enqueue(const T& newEntry, double priority)
		{
			PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry);
			newNodePtr->setPriority(priority);

		
			if (isEmpty())
			{
				frontPtr = backPtr=newNodePtr; // The queue is empty
				return true;
			}

			PriorityNode<T>* prev =frontPtr;
			PriorityNode<T>* ptr =frontPtr->getNext();

			if (priority > frontPtr->getPriority())
			{
				newNodePtr->setNext(frontPtr);
				frontPtr = newNodePtr;
			}
			else if (ptr == nullptr || priority > ptr->getPriority())
			{
				frontPtr->setNext(newNodePtr);
				newNodePtr->setNext(ptr);
			}
			else
			{
				while (ptr)
				{
					if (priority > ptr->getPriority())
					{
						prev->setNext(newNodePtr);
						newNodePtr->setNext(ptr);
						break;
					}
					else
					{
						prev = ptr;
						ptr = ptr->getNext();
					}
				}
			}
			
			return true;

		}

		bool dequeue(T& frntEntry)
		{
			if (isEmpty())
				return false;

			PriorityNode<T>* nodeToDeletePtr = frontPtr;

			frntEntry = frontPtr->getItem();
			frontPtr = frontPtr->getNext();

			// Queue is not empty; remove front
			if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
				backPtr = nullptr;

			// Free memory reserved by the dequeued node
			delete nodeToDeletePtr;


			return true;

		}

		bool peekFront(T& frntEntry) const
		{
			if (isEmpty())
				return false;

			frntEntry = frontPtr->getItem();
			return true;

		}

		~PriorityQueue()
		{
			T x;
			while (frontPtr)
			{
				this->dequeue(x);
			}
		}

		T* toArray(int& count)
		{
			count = 0;

			if (isEmpty())
				return nullptr;
			//counting the no. of items in the Queue
			PriorityNode<T>* temp = frontPtr;
			while (temp)
			{
				count++;
				temp = temp->getNext();
			}


			T* Arr = new T[count];
			temp = frontPtr;
			for (int i = 0; i < count; i++)
			{
				Arr[i] = temp->getItem();
				temp = temp->getNext();
			}
			return Arr;
		}

};


// ==============================================================    template specialization for VIP Order ===========================================	//
/*template<>
class PriorityNode<Order*>
{
private:
	Order* item; // A data item
	PriorityNode<Order*>* next; // Pointer to next node
	double priority;
public:

	PriorityNode()
	{
		next = nullptr;
	}

	PriorityNode(Order* r_Item)
	{
		item = r_Item;
		next = nullptr;
	}

	PriorityNode(Order* r_Item, PriorityNode<Order*>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}

	void setItem(Order* r_Item)
	{
		item = r_Item;
	}

	void setNext(PriorityNode<Order*>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	Order* getItem() const
	{
		return item;
	}

	PriorityNode<Order*>* getNext() const
	{
		return next;
	}

	void setPriority(double pri)
	{
		priority = pri;
	}

	double getPriority()
	{
		return priority;
	}

};


/*template <>
class PriorityQueue<Order *>
{
private:
	PriorityNode<Order*>* backPtr;
	PriorityNode<Order*>* frontPtr;
public:

	PriorityQueue<Order*>::PriorityQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}


	PriorityQueue(const PriorityQueue<Order*>& Q)
    {
		backPtr = frontPtr = nullptr;
		PriorityNode<Order*>* temp = Q.frontPtr;
		while (temp)
		{
			this->enqueue(temp->getItem() , temp->getPriority());
			temp = temp->getNext();
		}
	}

	bool isEmpty() const
	{
		return frontPtr == nullptr;
	}

	bool enqueue( Order* newEntry, double priority)
	{
		PriorityNode<Order *>* newNodePtr = new PriorityNode<Order *>(newEntry);
		newNodePtr->setPriority(priority);


		if (isEmpty())
		{
			frontPtr = backPtr = newNodePtr; // The queue is empty
			return true;
		}

		PriorityNode<Order*>* prev = frontPtr;
		PriorityNode<Order*>* ptr = frontPtr->getNext();

		if (priority > frontPtr->getPriority())
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else if (ptr == nullptr || priority > ptr->getPriority())
		{
			frontPtr->setNext(newNodePtr);
			newNodePtr->setNext(ptr);
		}
		else
		{
			while (ptr)
			{
				if (priority > ptr->getPriority())
				{
					prev->setNext(newNodePtr);
					newNodePtr->setNext(ptr);
					break;
				}
				else
				{
					prev = ptr;
					ptr = ptr->getNext();
				}
			}
		}

		return true;

	}

	bool dequeue(Order* & frntEntry)
	{
		if (isEmpty())
			return false;

		PriorityNode<Order*>* nodeToDeletePtr = frontPtr;

		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
			backPtr = nullptr;

		// Free memory reserved by the dequeued node
		delete nodeToDeletePtr;

		return true;
	}


	bool peekFront(Order*& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}

	~PriorityQueue()
	{
		Order* x;
		while (frontPtr)
		{
			this->dequeue(x);
		}
	}


	Order* * toArray(int& count)
	{
		count = 0;

		if (isEmpty())
			return nullptr;
		//counting the no. of items in the Queue
		PriorityNode<Order*>* temp = frontPtr;
		while (temp)
		{
			count++;
			temp = temp->getNext();
		}


		Order** Arr = new Order * [count];
		temp = frontPtr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = temp->getItem();
			temp = temp->getNext();
		}
		return Arr;
	}
};*/
