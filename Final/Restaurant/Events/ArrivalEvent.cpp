#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent (int eTime, int oID, ORD_TYPE oType  ):Event(eTime, oID)
{
	OrdType = oType;
}

/*ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType,ORD_STATUS st ,  double money) : Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney=money;

}*/

ArrivalEvent::ArrivalEvent (int time , int id , ORD_TYPE tp , double money ) : Event(time,id)
{
	OrdType=tp;
	OrdMoney=money;
}

ArrivalEvent::ArrivalEvent(int time, int id, int size, ORD_TYPE typ, int money):Event(time ,id)
{
	OrdSize = size;
	OrdType = typ;
	OrdMoney = money;
}



void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	//Order* pOrd = new Order(OrderID,OrdType);
	//pRest->AddtoDemoQueue(pOrd);


	Order* pOrd = new Order(OrderID,EventTime,OrdType,OrdMoney);
	pOrd->SetSize(OrdSize);
	pOrd->setStatus(WAIT);
	pRest->AddOrders(pOrd);
}
