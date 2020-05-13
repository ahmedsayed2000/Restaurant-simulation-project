#include "PromoteEvent.h"
#include "Rest\Restaurant.h"

PromoteEvent::PromoteEvent(int eTime, int ordID,double money):Event(eTime,ordID)
{
	Extra_Money = money;
}

void PromoteEvent::Execute(Restaurant* pRest)
{
	pRest->PromotionOrder(OrderID,Extra_Money);
}
