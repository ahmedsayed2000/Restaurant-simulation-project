#pragma once
#include "Events/Event.h"
class PromoteEvent :	public Event
{
	double Extra_Money;
public:
	PromoteEvent(int eTime, int ordID  ,  double money);
	virtual void Execute(Restaurant* pRest);
};

