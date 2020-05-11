#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(int eTime, int ordID,int money):Event(eTime,ordID)
{
	Extra_Money = money;
}

void PromoteEvent::Execute(Restaurant* pRest)
{

}
