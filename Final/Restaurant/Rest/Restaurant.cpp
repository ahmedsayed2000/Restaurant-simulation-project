#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
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
		N_order.insert(N_order.getlength()+1,pO);
		break;
	case TYPE_VGAN:
		vegan_order.enqueue(pO);
		break;
	case TYPE_VIP:
		vip_order.enqueue(pO,pO->getMoney());
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

bool Restaurant:: PromotionOrder (int id , double money)
{
	Order* pord;
	for(int i=1; i<=N_order.getlength() ; i++)
	{
		N_order.remove(i);
		if(pord->GetID() == id)
		{
			pord->setOrder_Typ(TYPE_VIP);
			pord->set_Money(pord->getMoney()+money);
			vip_order.enqueue(pord,pord->getMoney());
			return true;
		}
		else
			N_order.insert(i,pord);
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

	int sN_min,sN_max,sV_min,sV_max,sG_min,sG_max;     // speed of each type of cooks

	int BO,BN_min,BN_max,BG_min,BG_max,BV_min,BV_max;  // BO is number of orders a cook must prepate before a break
	// (BN_max/min)/(BG_min/max)/(BV_min/max)  are break duration limits for this type of cook

	ifstream infile;
	infile.open("inputs.txt");
	//cout<<infile.is_open()<<endl;

	infile>>N>>G>>V;
	infile>>sN_min>>sN_max>>sV_min>>sV_max>>sG_min>>sG_max;
	infile>>BO>>BN_min>>BN_max>>BG_min>>BG_max>>BV_min>>BV_max;
	//cout<<N<<G<<V;

	ORD_TYPE Ntyp=TYPE_NRM;
	ORD_TYPE Gtyp=TYPE_VGAN;
	ORD_TYPE Vtyp=TYPE_VIP;
	bool is_inRange;

	int cID=1;
	int break_dur;
	int speed;
	int spd_counter=0;
	int brk_counter=0;
	for(int i=0 ; i<N ; i++)
	{
		is_inRange=false;
		while(!is_inRange)
		{
			if((spd_counter<=(sN_max-sN_min)) && (brk_counter<=(BN_max-BN_min)))
			{
				speed=sN_min+spd_counter;
				break_dur=BN_min+brk_counter;
				spd_counter++;   brk_counter++;
				is_inRange=true;
			}
			else if(spd_counter<=(sN_max-sN_min))
				brk_counter=0;
			else if(brk_counter<=(BN_max-BN_min))
				spd_counter=0;
			else
			{
				brk_counter=0;
				spd_counter=0;
			}
		}
		Cook* pc = new Cook(cID,Ntyp,speed);
		pc->set_Break_duration(break_dur);   pc->set_Break_Orders(BO);
		N_Cook.insert(1, pc);
		cID++;

	}

	for(int i=0 ; i<G ; i++)
	{
		is_inRange=false;
		while(!is_inRange)
		{
			if((spd_counter<=(sG_max-sG_min)) && (brk_counter<=(BG_max-BG_min)))
			{
				speed=sG_min+spd_counter;
				break_dur=BG_min+brk_counter;
				spd_counter++;   brk_counter++;
				is_inRange=true;
			}
			else if(spd_counter<=(sG_max-sG_min))
				brk_counter=0;
			else if(brk_counter<=(BG_max-BG_min))
				spd_counter=0;
			else
			{
				brk_counter=0;
				spd_counter=0;
			}
		}
		Cook* pc = new Cook(cID,Gtyp,speed);
		pc->set_Break_duration(break_dur);   pc->set_Break_Orders(BO);
		Veg_Cook.insert(1, pc);
		cID++;

	}
	for(int i=0 ; i<V ; i++)
	{
		is_inRange=false;
		while(!is_inRange)
		{
			if((spd_counter<=(sV_max-sV_min)) && (brk_counter<=(BV_max-BV_min)))
			{
				speed=sV_min+spd_counter;
				break_dur=BV_min+brk_counter;
				spd_counter++;   brk_counter++;
				is_inRange=true;
			}
			else if(spd_counter<=(sV_max-sV_min))
				brk_counter=0;
			else if(brk_counter<=(BV_max-BV_min))
				spd_counter=0;
			else
			{
				brk_counter=0;
				spd_counter=0;
			}
		}
		Cook* pc = new Cook(cID,Vtyp,speed);
		pc->set_Break_duration(break_dur);   pc->set_Break_Orders(BO);
		Vip_Cook.insert(1, pc);
		cID++;
	}


	/////////////// injury probability and rest period /////////////
	infile>>injprob>>rstprd;

	//////////////////////////////// reading auto promtion limit and VIP time
	//steps after which the order is considered an urgent order

	infile>>AutoP>>VIP_wt;


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

		WaitOrders_Handling();
		pGUI->waitForClick();
		CurrentTimeStep++;
		pGUI->UpdateInterface();

//<<<<<<< Updated upstream
		WaitOrders_Handling();

		///////////////////////////////////////Service Stage///////////////////////////////////////////////////////////////
		ofstream myfile;
		Node<Order*>* ptr = vip_service.getHead();
		Cook* cook;
		int count = 1;
		while (ptr) {
			cook = (ptr->getItem())->getCook();
			ptr->getItem()->set_ServiceTime(ptr->getItem()->get_ServiceTime() + 1);
			(ptr->getItem())->set_remainDishes((ptr->getItem()) ->get_remainDishes()-cook->getSpeed());
			if ((ptr->getItem())->get_remainDishes() <= 0) {
				cook->set_OrdersPrepared(cook->get_OrdersPrepared() + 1);
				cook->setState(false);
				ptr->getItem()->setStatus(DONE);
				finshed_orders.enqueue(ptr->getItem());
				ptr = ptr->getNext();
				vip_service.remove(count);
			}
			else
			{
				ptr = ptr->getNext();
				count++;
			}
		}
		ptr = veg_service.getHead();
		count = 1;
		while (ptr) {
			cook = (ptr->getItem())->getCook();
			ptr->getItem()->set_ServiceTime(ptr->getItem()->get_ServiceTime() + 1);
			(ptr->getItem())->set_remainDishes((ptr->getItem())->get_remainDishes() - cook->getSpeed());
			if ((ptr->getItem())->get_remainDishes() <= 0) {
				cook->set_OrdersPrepared(cook->get_OrdersPrepared() + 1);
				cook->setState(false);
				ptr->getItem()->setStatus(DONE);
				finshed_orders.enqueue(ptr->getItem());
				ptr = ptr->getNext();
				veg_service.remove(count);
			}
			else
			{
				ptr = ptr->getNext();
				count++;
			}
			
		}
		ptr = nor_service.getHead();
		count = 1;
		while (ptr) {
			cook = (ptr->getItem())->getCook();
			ptr->getItem()->set_ServiceTime(ptr->getItem()->get_ServiceTime() + 1);
			(ptr->getItem())->set_remainDishes((ptr->getItem())->get_remainDishes() - cook->getSpeed());
			if ((ptr->getItem())->get_remainDishes() <= 0) {
				cook->set_OrdersPrepared(cook->get_OrdersPrepared() + 1);
				cook->setState(false);
				ptr->getItem()->setStatus(DONE);
				finshed_orders.enqueue(ptr->getItem());
				ptr = ptr->getNext();
				nor_service.remove(count);
			}
			else
			{
				ptr = ptr->getNext();
				count++;
			}
		}

	}

}

void Restaurant:: WaitOrders_Handling ()
{
	AddTo_Service();
	increment_Wt();

	Order* pord;
	for(int i=1; i<=N_order.getlength() ; i++)
	{
		N_order.remove(i);
		pGUI->AddToDrawingList(pord);
		N_order.insert(i,pord);
	}

	int count;
	Order** ptr=vip_order.toArray(count);
	for(int i=0 ; i<count ; i++)
		pGUI->AddToDrawingList(ptr[i]);

	ptr=vegan_order.toArray(count);
	for(int i=0 ; i<count ; i++)
		pGUI->AddToDrawingList(ptr[i]);
}

void Restaurant:: AddTo_Service ()
{
	///////// for vip orders//////////////
	while(!vip_order.isEmpty())
	{
		Cook* ptr=find_availableCook(TYPE_VIP);
		Order* Pord;
		if(ptr)
		{
			ptr->setState(true);
			vip_order.dequeue(Pord);
			Pord->set_cook(ptr);
			Pord->set_remainDishes(Pord->GetSize());
			vip_service.insert(vip_service.getlength()+1,Pord);
		}
		else
		{
			break;
		}
	}

	UrgentOrders_Handle();

	////////////// for VEGAN orders ////////////////////
	while(!vegan_order.isEmpty())
	{
		Cook* ptr=find_availableCook(TYPE_VGAN);
		Order* Pord;
		if(ptr)
		{
			ptr->setState(true);
			vegan_order.dequeue(Pord);
			Pord->set_remainDishes(Pord->GetSize());
			Pord->set_cook(ptr);
			veg_service.insert(veg_service.getlength()+1,Pord);
		}
		else
			break;
	}
	////////////// for NORMAL orders ////////////////////
	while(!N_order.isEmpty())
	{
		Cook* ptr=find_availableCook(TYPE_NRM);
		Order* Pord;
		if(ptr)
		{
			ptr->setState(true);
//<<<<<<< Updated upstream
			N_order.remove(1);
//=======
			N_order.remove(N_order.getlength());
//>>>>>>> Stashed changes
			Pord->set_remainDishes(Pord->GetSize());
			Pord->set_cook(ptr);
			nor_service.insert(nor_service.getlength()+1,Pord);
		}
		else
			break;
	}

	AutoPromotion_handling();

}

Cook* Restaurant:: find_availableCook(ORD_TYPE typ)
{
	Node<Cook*>* ptr;
	Cook* cook;

	switch(typ)
	{
	case TYPE_VIP:
		{
			ptr=Vip_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest() ))
					return cook;
				else
					ptr=ptr->getNext();
			}

			ptr=N_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest() ))
					return cook;
				else
					ptr=ptr->getNext();
			}

			ptr=Veg_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest()))
					return cook;
				else
					ptr=ptr->getNext();
			}
			return nullptr;
		}
		break;

	case TYPE_VGAN:
		{
			ptr=Veg_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest()))
					return cook;
				else
					ptr=ptr->getNext();
			}
			return nullptr;
		}
		break;

	case TYPE_NRM:
		{
			ptr=N_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest()))
					return cook;
				else
					ptr=ptr->getNext();
			}

			ptr=Vip_Cook.getHead();
			while(ptr)
			{
				cook=ptr->getItem();
				if(!(cook->getState() || cook->is_inBreak() || cook->is_InRest()))
					return cook;
				else
					ptr=ptr->getNext();
			}
			return nullptr;
		}
		break;

	default:
		break;
//=======



		

//>>>>>>> Stashed changes
	}

}

Cook* Restaurant::findInRest_OrInBreak()
{
//<<<<<<< Updated upstream
	Cook* cook=nullptr;
	Node<Cook*>* ptr=Vip_Cook.getHead();
	while(ptr)
	{
		cook=ptr->getItem();
		if(cook->is_inBreak() || cook->is_InRest())
			return cook;
		else
			ptr=ptr->getNext();
	}
	ptr=N_Cook.getHead();
	while(ptr)
	{
		cook=ptr->getItem();
		if(cook->is_inBreak() || cook->is_InRest())
			return cook;
		else
			ptr=ptr->getNext();
	}
	ptr=Veg_Cook.getHead();
	while(ptr)
	{
		cook=ptr->getItem();
		if(cook->is_inBreak() || cook->is_InRest())
			return cook;
		else
			ptr=ptr->getNext();
	}
	return cook;
//=======
	return nullptr;
//>>>>>>> Stashed changes
}

void Restaurant::UrgentOrders_Handle()
{
	Cook* cook;
	Order* pord;
	while(!vip_order.isEmpty())
	{
		vip_order.peekFront(pord);
		if(pord->get_WaitTime() > VIP_wt)
		{
			cook=find_availableCook(TYPE_VIP);
			if(cook)
			{
				cook->setState(true);
				vip_order.dequeue(pord);
				pord->set_cook(cook);
				pord->set_remainDishes(pord->GetSize());
				vip_service.insert(vip_service.getlength()+1,pord);
			}
			else
			{
				cook=findInRest_OrInBreak();
				if(cook)
				{
					cook->setState(true);
					vip_order.dequeue(pord);
					pord->set_cook(cook);
					pord->set_remainDishes(pord->GetSize());
					vip_service.insert(vip_service.getlength()+1,pord);
				}
				else
					return;
			}
		}
		else
			return;

	}
}

void Restaurant:: increment_Wt()
{
	int count;
	Order** ptr=vip_order.toArray(count);
	for(int i=0 ; i<count ; i++)
		ptr[i]->set_WaitTime(ptr[i]->get_WaitTime()+1);

	ptr=vegan_order.toArray(count);
	for(int i=0 ; i<count ; i++)
		ptr[i]->set_WaitTime(ptr[i]->get_WaitTime()+1);

	Order* pord;
	for(int i=1 ; i<=N_order.getlength() ; i++)
	{
		N_order.remove(i);
		pord->set_WaitTime(ptr[i]->get_WaitTime()+1);
		N_order.insert(i,pord);
	}


}


void Restaurant:: AutoPromotion_handling()
{
	Order* pord;
	while(!N_order.isEmpty())
	{
		N_order.remove(1);
		if(pord->get_WaitTime() > AutoP)
		{
			pord->setOrder_Typ(TYPE_VIP);
			vip_order.enqueue(pord,pord->getMoney());
		}
		else
		{
			N_order.insert(1,pord);
			return;
		}
	}
}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}
