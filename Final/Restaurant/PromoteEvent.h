#pragma once
#include "Events/Event.h"
class PromoteEvent :	public Event
{
	int Extra_Money;
public:
	PromoteEvent(int eTime, int ordID  ,  int money);
	virtual void Execute(Restaurant* pRest);
};

