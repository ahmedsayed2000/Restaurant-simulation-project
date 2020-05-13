#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order:: Order (int id , int time, ORD_TYPE typ , double  money)
{
	ArrTime=time;
	//FinishTime=ArrTime+5;
	ID = (id>0&&id<1000)?id:0;
	type=typ;
	status = WAIT;
	totalMoney=money;
	WaitTime=0;
	ServTime=0;
}


Order::~Order()
{
}

void Order::SetId(int i)
{
	ID = i;
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetSize(int d)
{
	Size = d>0?d:0;
}

int Order::GetSize() const
{
	return Size;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order :: set_Money(double money)
{
	totalMoney=money;
}

double Order :: getMoney()
{
	return totalMoney;
}

void Order :: set_ArrTime(int tm)
{
	ArrTime=tm;
}

int Order :: get_ArrTime()
{
	return ArrTime;
}

void Order :: set_FinishTime(int tm)
{
	FinishTime=tm;
}

int Order :: get_FinishTime()
{
	return FinishTime;
}

void Order :: setOrder_Typ ( ORD_TYPE tp)
{
	type=tp;
}

void Order :: set_cancellation (bool cancel)
{
	isCancelled=cancel;
}

bool Order::get_cancellation()
{
	return isCancelled;
}

void Order:: set_remainDishes(float d)
{
	remain_dishes=d;
}

float Order:: get_remainDishes()
{
	return remain_dishes;
}

void Order ::set_cook(Cook* ptr)
{
	cook=ptr;
}

Cook* Order::getCook()
{
	return cook;
}

int Order::get_WaitTime()
{
	return WaitTime;
}

void Order:: set_WaitTime(int time)
{
	WaitTime=time;
}


/*int Order::getPriority()
{
return Priority;
}

<<<<<<< Updated upstream
void Order:: setPriority(int pr)
{
Priority = getMoney();
}*/
//=======
void Order::set_ServiceTime(int time)
{
	ServTime = time;
}

int Order::get_ServiceTime()
{
	return ServTime;
}
//>>>>>>> Stashed changes

