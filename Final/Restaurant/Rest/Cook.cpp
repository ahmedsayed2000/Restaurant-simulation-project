#include "Cook.h"


Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE tp, float sp)
{
	setID(id);  setSpeed(sp);   setType(tp); setState(false); setInjury(false);
	set_inBreak(false);  set_BreakCounter(0);

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

void Cook:: setSpeed(float sp)
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

void Cook::set_BreakCounter(int count)
{
	Break_counter=count;
}
int Cook::get_BreakCounter()
{
	return Break_counter;
}
void Cook::set_OrdersPrepared(int op)
{
	Orders_Prepared = op;
}
int Cook::get_OrdersPrepared()
{
	return Orders_Prepared;
}
void Cook::set_OutTime(int ot)
{
	OutTime = ot;
}
int Cook::get_OutTime()
{
	return OutTime;
}
void Cook::set_inBreak(bool B)
{
	inBreak=B;
}
bool Cook::is_inBreak()
{
	return inBreak;
}

<<<<<<< HEAD
void Cook::set_inRest(bool r)
{
	inRest=r;
}

bool Cook::is_InRest()
{
	return inRest;
}
=======
>>>>>>> bc88a6930d6ccf387b84ebe862783bfda7782083



