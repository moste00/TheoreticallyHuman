#include "CancellationEvent.h"
#include "..\Restaurant\Rest\Restaurant.h"
CancellationEvent::CancellationEvent(int eTime, int oID) : Event(eTime,oID)
{
}

CancellationEvent::CancellationEvent()
{
}

void CancellationEvent::readInfo(std::ifstream& file)
{
	file >> Event::EventTime >> Event::OrderID;
}

void CancellationEvent::Execute(Restaurant* pRest)
{	
	//TODO: Replace RemoveFromDemoQueue call IN PHASE 2


	//<====================> DEMO BEHAVIOUR <====================> /////////////////////////////////////////////////
	pRest->RemoveFromDemoQueue(Event::OrderID,Event::EventTime);
}
