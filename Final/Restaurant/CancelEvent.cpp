#include "CancelEvent.h"

CancelEvent::CancelEvent(int eTime, int ordID):Event(eTime,ordID)
{
}

void CancelEvent::Execute(Restaurant* pRest)
{
	 pRest->CancelOrder(OrderID);
		//   to do print messaege    that  successfully cancelation
		//   to do print failed cancelation 
}
