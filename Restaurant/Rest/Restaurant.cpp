#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"

//Takes the type of event as a character and returns a pointer to a dynamically created event of that type
Event* Restaurant::CreateSpecificEvent(char type)
{
	switch (type)
	{
	case 'R': return new ArrivalEvent()		;

	case 'X': return new CancellationEvent();

	case 'P': return new PromotionEvent()	;

	default: return nullptr;
	}
}

Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	
	Cook** CooksList = Kitch.toArray();
	for (int i = 0; i < Kitch.getNumCooks(); ++i) pGUI->AddToDrawingList(CooksList[i]);
	delete[] CooksList;


	int OrdersCount;
	Order** OrdersList = OrdersQueue.toArray(OrdersCount);

	for (int i = 0; i < OrdersCount; ++i) pGUI->AddToDrawingList(OrdersList[i]);

	delete[] OrdersList;
}
bool Restaurant::loadEventsAndCooksFromFile(string path)
{
	std::ifstream file;
	file.open(path);
	
	if (file.is_open()) {
		Kitch.loadCooksFromFile(file);
		file >> autoPlimit;
		loadEventsFromFile(file);

		file.close();
		return true;
	}
	else return false;
}

void Restaurant::loadEventsFromFile(std::ifstream& file)
{
	int num;
	file >> num;
	Event* temp;
	for (int i = 0; i < num; ++i) {
		char eventType;
		file >> eventType;
		temp = CreateSpecificEvent(eventType);
		temp->readInfo(file);
		EventsQueue.enqueue(temp);
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2

	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();
		
	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;	
	Cook *pC = new Cook[C_count];
	int cID = 1;

	for(int i=0; i<C_count; i++)
	{
		cID+= (rand()%15+1);	
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand()%TYPE_CNT));
	}	

		
	int EvTime = 0;

	int O_id = 1;
	
	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		O_id += (rand()%4+1);		
		int OType = rand()%TYPE_CNT;	//Randomize order type		
		EvTime += (rand()%5+1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}	

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file

	
	
	
	
	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;
	

	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		

/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks
		
		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for(int i=0; i<C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);
		
		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);
		
		for(int i=0; i<size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete []pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

void Restaurant::RemoveFromDemoQueue(int NormalOrderID,int ArrivalTime)
{
	Queue<Order*> Temp;
	Order* pO;
	while (!DEMO_Queue.isEmpty())
	{
		//Remove an Order 
		DEMO_Queue.dequeue(pO);

		//If the Order is the one we need to delete then delete it and continue 
		if (pO->GetType() == TYPE_NRM && pO->getArrivalTime() == ArrivalTime && pO->GetID() == NormalOrderID) {
			delete pO;
			continue;
		};
		
		//Else save the order to a temporary queue so we can return it again
		Temp.enqueue(pO);
	}

	//Return all the other orders from the temporary queue to the main queue
	while (!Temp.isEmpty())
	{
		Temp.dequeue(pO);
		DEMO_Queue.enqueue(pO);
	}
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////


