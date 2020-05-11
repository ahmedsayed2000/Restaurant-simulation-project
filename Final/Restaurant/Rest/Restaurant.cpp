#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	Load();
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		interactive_mode();
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		break;

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)

	Node<Cook*>* ptr = N_Cook.getHead();
	while(ptr)
	{
		pGUI->AddToDrawingList(ptr->getItem());
		ptr=ptr->getNext();
	}



	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	Order* pord;
	for (int i =1 ; i<6 ; i++)
	{
		ExecuteEvents(i);
	}
	

	while (!DEMO_Queue.isEmpty())
	{
		DEMO_Queue.peekFront(pord);
		pGUI->AddToDrawingList(pord);
		DEMO_Queue.dequeue(pord);
	}
}

void Restaurant::AddOrders(Order* pO)
{
	ORD_TYPE TYP = pO->GetType();
	switch (TYP)
	{
	case TYPE_NRM:
		N_order.insert(N_order.getlength(),pO);
		break;
	case TYPE_VGAN:
		vegan_order.enqueue(pO);
		break;
	case TYPE_VIP:
		vip_order.enqueue(pO);
		break;
	default:
		break;
	}
}

bool Restaurant::CancelOrder(int id)
{
	if (N_order.isEmpty())  return false;

	Node<Order*>*  pOrd;
	pOrd = N_order.getHead();
	int count = 1;
	while (pOrd)
	{
		Order* ord = pOrd->getItem();
		if (ord->GetID() ==id)
		{
			N_order.remove(count);
			return true;
		}
		pOrd = pOrd->getNext();
		count++;
	}
	return false;

}

void Restaurant:: set_AutoP (int at)
{
	AutoP=at;
}

int Restaurant::  get_AutoP ()
{
	return AutoP;
}

void Restaurant:: Load()
{
	/////////////////// this section to read cooks information\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	int cookSum=0;
	int N,V,G;        // N for normal cooks  \ G for n=vegan cooks  \ V for vip cooks

	int sN,sV,sG;     // speed of each type of cooks

	int BO,BN,BG,BV;  // BO is number of orders a cook must prepate before a break
	// BN/BG/BV  are break duration for this type of cook

	ifstream infile;
	infile.open("inputs.txt");
	//cout<<infile.is_open()<<endl;

	infile>>N>>G>>V;
	infile>>sN>>sG>>sV;
	infile>>BO>>BN>>BG>>BV;

	ORD_TYPE Ntyp=TYPE_NRM;
	ORD_TYPE Gtyp=TYPE_VGAN;
	ORD_TYPE Vtyp=TYPE_VIP;

	int cID=1;
	for(int i=0 ; i<N ; i++)
	{
		cID+= (rand()%15+1);
		Cook* pc = new Cook(cID,Ntyp,sN);
		pc->set_Break_duration(BN);   pc->set_Break_Orders(BO);
		N_Cook.insert(1, pc);
	}
	for(int i=0 ; i<G ; i++)
	{
		cID+= (rand()%15+1);
		Cook* pc = new Cook(cID,Gtyp,sG);
		pc->set_Break_duration(BG);   pc->set_Break_Orders(BO);
		Veg_Cook.insert(1, pc);
	}
	for(int i=0 ; i<V ; i++)
	{
		cID+= (rand()%15+1);
		Cook* pc = new Cook(cID,Vtyp,sV);
		pc->set_Break_duration(BV);   pc->set_Break_Orders(BO);
		Vip_Cook.insert(1, pc);
	}

	//////////////////////////////// reading auto promtion limit \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	int AT;
	infile>>AT;
	set_AutoP(AT);



	////////////////// this section to read arrival orders information \\\\\\\\\\\\\\\\\\\\\\\\

	int numOfEvents;
	infile>>numOfEvents;
	char Ev , ord_type;
	int money,id,time,size;    // total mony - id - current time step - number of dishes
	ORD_TYPE typ;
	Event* ArrEv;
	for(int i=0 ; i<numOfEvents ; i++)
	{
		infile>>Ev;
		switch (Ev)
		{
		case'R': 
			{
				infile>>ord_type>>time>>id>>size>>money;
				if(ord_type=='N')
				{
					typ=TYPE_NRM;
					ArrEv = new ArrivalEvent(time, id, size, typ, money);
				}
				else if(ord_type=='G')
				{
					typ=TYPE_VGAN;
					ArrEv=new ArrivalEvent(time, id, size, typ, money);
				}
				else
				{
					typ=TYPE_VIP;;
					ArrEv=new ArrivalEvent(time, id, size, typ, money);
				}
			}
			break;

		case'X':
			{
				infile>>time>>id;
				ArrEv = new CancelEvent(time, id);
			}
			break;

		case'P':
			{
				infile>>time>>id>>money;
				ArrEv = new PromoteEvent(time, id, money);

			}
			break;
		default:
			break;
		}

		EventsQueue.enqueue(ArrEv);
	}
}

void Restaurant:: interactive_mode()
{
	int CurrentTimeStep = 1;
	while (!EventsQueue.isEmpty()|| !vip_service.isEmpty() || !veg_service.isEmpty() || !nor_service.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);

		ExecuteEvents(CurrentTimeStep);
		Vip_Handling(CurrentTimeStep);
		Vegan_Handling(CurrentTimeStep);
		Normal_Handling(CurrentTimeStep);

		Order** order;
		int count;
		order = finshed_orders.toArray(count);
		for (int i = 0; i < count; i++) {
			pGUI->AddToDrawingList(order[i]);
		}
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;
		pGUI->ResetDrawingList();
	}
}

void Restaurant::Vip_Handling(int &timestep)
{
	if (!vip_order.isEmpty()) {
		Order* order;
		vip_order.peekFront(order);
		vip_order.dequeue(order);
		order->setStatus(SRV);
		vip_service.enqueue(order);
	}

	if (timestep % 5 == 0) {
		Order* order;
		if (!vip_service.isEmpty()) {
			vip_service.dequeue(order);
			order->setStatus(DONE);
			finshed_orders.enqueue(order);
		}
	}
	Order** order;
	int count;
	order = vip_order.toArray(count);
	for (int i = 0; i < count; i++) {
		pGUI->AddToDrawingList(order[i]);
	}
	order = vip_service.toArray(count);
	for (int i = 0; i < count; i++) {
		pGUI->AddToDrawingList(order[i]);
	}
	Node<Cook*>*cook = Vip_Cook.getHead();
	while (cook) {
		Cook* ptr = cook->getItem();
		pGUI->AddToDrawingList(ptr);
		cook = cook->getNext();
	}

}

void Restaurant::Vegan_Handling(int & timestep)
{
	if (!vegan_order.isEmpty()) {
		Order* order;
		vegan_order.peekFront(order);
		vegan_order.dequeue(order);
		order->setStatus(SRV);
		veg_service.enqueue(order);
	}
	if (timestep % 5 == 0) {
		Order* order;

		if (!veg_service.isEmpty()) {
			veg_service.dequeue(order);
			order->setStatus(DONE);
			finshed_orders.enqueue(order);
		}
	}
	Order** order;
	int count;

	order = vegan_order.toArray(count);
	for (int i = 0; i < count; i++) {
		pGUI->AddToDrawingList(order[i]);
	}

	order = veg_service.toArray(count);
	for (int i = 0; i < count; i++) {
		pGUI->AddToDrawingList(order[i]);
	}

	Node<Cook*>* cook = Veg_Cook.getHead();
	while (cook) {
		Cook* ptr = cook->getItem();
		pGUI->AddToDrawingList(ptr);
		cook = cook->getNext();
	}

}

void Restaurant::Normal_Handling(int & timestep)
{
	if (!N_order.isEmpty()) {
		Node<Order*>* ptr = N_order.getHead();
		(ptr->getItem())->setStatus(SRV);
		nor_service.enqueue(ptr->getItem());
		N_order.remove(1);
	}



	if (timestep % 5 == 0) {
		Order* order;
		if (!nor_service.isEmpty()) {
			nor_service.dequeue(order);
			order->setStatus(DONE);
			finshed_orders.enqueue(order);
		}

	}

	Node<Cook*>* cook = N_Cook.getHead();
	while (cook) {
		Cook* ptr = cook->getItem();
		pGUI->AddToDrawingList(ptr);
		cook = cook->getNext();
	}


	Node<Order*>* ord = N_order.getHead();
	while (ord)
	{
		Order* ptr = ord->getItem();
		pGUI->AddToDrawingList(ptr);
		ord = ord->getNext();
	}
	Order** order;
	int count;

	order = nor_service.toArray(count);
	for (int i = 0; i < count; i++) {
		pGUI->AddToDrawingList(order[i]);
	}
}

Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}
