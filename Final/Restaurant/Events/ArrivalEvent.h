#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdSize;			//Size of  the order
	int OrdMoney;		//Total order money
	ORD_TYPE OrdType;	//order type: Normal, vegan, VIP	                
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType );

	//ArrivalEvent(int eTime, int oID, ORD_TYPE oType,ORD_STATUS , double);
	ArrivalEvent (int , int , ORD_TYPE , double );
	//Add more constructors if needed
	ArrivalEvent(int time, int id, int size, ORD_TYPE typ, int money);
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif