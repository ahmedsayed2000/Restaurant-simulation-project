#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int Break_Orders;         // number of orders a cook must prepate before a break
	int Break_duration;         // break duration for this type of cook
	int Orders_Prepared;
	int OutTime;
	bool busy;                // busy or not
	bool injured;              // injured during service
	bool inBreak;           // whether the cook is in break or not
	int Break_counter;        // incrementig until the cook finishes his break time


public:
	Cook();
	Cook(int id , ORD_TYPE tp, float sp );
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
	void setSpeed(float sp);
	float getSpeed();
	void set_Break_Orders (int);
	int get_Break_Orders ();
	void set_Break_duration(int);
	int get_Break_duration();
	void setState(bool state);
	bool getState();
	void setInjury (bool);
	bool getInjury();
	void set_inBreak (bool);
	bool is_inBreak();
	void set_BreakCounter(int);
	int get_BreakCounter();
	void set_OrdersPrepared(int op);
	int get_OrdersPrepared();
	void set_OutTime(int ot);
	int get_OutTime();


};
