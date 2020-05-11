#include "Cook.h"


Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE tp, float sp)
{
	setID(id);  setSpeed(sp);   setType(tp); setState(false); setInjury(false);
}



Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook:: setSpeed(int sp)
{
	speed=sp;
}
float Cook:: getSpeed()
{
	return speed;
}

void Cook:: set_Break_Orders (int bo)
{
	Break_Orders=bo;
}

int Cook:: get_Break_Orders ()
{
	return Break_Orders;
}

void Cook:: set_Break_duration(int bi)
{
	Break_duration=bi;
}

int Cook:: get_Break_duration()
{
	return Break_duration;
}

void Cook::setState(bool state)
{
	busy = state;
}

bool Cook::getState()
{
	return busy;
}

bool Cook:: getInjury()
{
	return injured;
}

void Cook :: setInjury (bool inj)
{
	injured=inj;
}




