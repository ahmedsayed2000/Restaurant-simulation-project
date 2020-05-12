# pragma once
#include"..\PromoteEvent.h"
#include"..\CancelEvent.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\List.h"
#include<fstream>
#include"string.h"
#include "..\Generic_DS\PriorityQueue.h"

#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	
	
	//
	// TODO: Add More Data Members As Needed


	
	float injprob;
	int rstprd;
	int AutoP,VIP_wt;							        //AutoPo is the number of steps after which an order is promoted

	List<Cook*> N_Cook;							// list of Normal cooks
	List<Cook*> Veg_Cook;						// list of Vegan cooks
	List<Cook*> Vip_Cook;						// list of Vip cooks

	List <Order*>            N_order;		        // waiting  normal orders
	PriorityQueue<Order*>    vip_order;				// waiting  vip orders
	Queue<Order*>		     vegan_order;			// waiting  vegan orders

	Queue<Order*>        vip_service;			// service  orders 
	Queue<Order*>        veg_service;
	Queue<Order*>        nor_service;

	Queue<Order*>        finshed_orders;		// finished orders
public:
	
	Restaurant();
	~Restaurant();
	

	//  Logic Finctions
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void Load ();					    // Load function  to read inputs from the external file


	void FillDrawingList();   // GUI  function 

	void AddOrders(Order * pO);   // dealing with arrival Event
	bool CancelOrder(int id);     //dealing with cancel Event

	void set_AutoP (int);
	int  get_AutoP ();
	
    
	void interactive_mode();   // interactive mode
	void Vip_Handling(int &timestep);                       //function to deal with vip orders and cooks
	void Vegan_Handling(int &timestep);                     //function to deal with vegan orders and cooks
	void Normal_Handling(int &timestep);                    //function to deal with normal orders and cooks
};

