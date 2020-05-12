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
	bool busy;                // busy or not
	bool injured;              // injured during service
	float remain_dishes;       // remaining dishes for this cook to finish the order

public:
	Cook();
	Cook(int id , ORD_TYPE tp, float sp );
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
	void setSpeed(int sp);
	float getSpeed();
	void set_Break_Orders (int);
	int get_Break_Orders ();
	void set_Break_duration(int);
	int get_Break_duration();
	void setState(bool state);
	bool getState();
	void setInjury (bool);
	bool getInjury();

};
