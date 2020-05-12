#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include"Cook.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Size;	//The size of the order
	//int Priority;
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int WaitTime;

	float remain_dishes;    ////// 34an zyad myz3l4
	Cook* cook;
	
	//
	// TODO: Add More Data Members As Needed
	// current Timestep -> to identify at which time the order will be done
	//int currentTime;

	// check if the order is cancelled or not
	bool isCancelled;

public:
	Order(int ID, ORD_TYPE r_Type);
	Order (int id , int time, ORD_TYPE  tp  ,double money);
	virtual ~Order();

	void SetId(int i) ;
	int GetID();


	ORD_TYPE GetType() const;

	void SetSize(int d);
	int GetSize() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//set and get money
	void set_Money (double money);
	double getMoney ();

	// set and get arrival time
	void set_ArrTime (int tm);
	int get_ArrTime();
	// set and get finish time
	void set_FinishTime (int tm);
	int get_FinishTime();

	
	// set order type
	void setOrder_Typ (ORD_TYPE typ);


	// to check whether the order us cancelled or not
	void set_cancellation (bool check);
	bool get_cancellation ();

	void set_remainDishes(float);
	float get_remainDishes();

	void set_cook(Cook*);
	Cook* getCook();

	//void setPriority(int);
	//int getPriority();

	void set_ServiceTime(int time);
	int  get_ServiceTime();
};

#endif