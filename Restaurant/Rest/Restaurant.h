#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include <fstream>

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\Queue.h"
#include "..\DynList.h"
#include "..\Events\Event.h"

#include "..\Kitchen.h"
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
	//
	Kitchen Kitch;
	int autoPlimit;
	QueuePriority<Order*> OrdersQueue;

	Event* CreateSpecificEvent(char);

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//


	bool loadEventsAndCooksFromFile(string);
	void loadEventsFromFile(std::ifstream&);

/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	void RemoveFromDemoQueue(int,int);
/// ================================================================================================== 



};

#endif