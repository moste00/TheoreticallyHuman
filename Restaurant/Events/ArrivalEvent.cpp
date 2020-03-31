#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ORD_TYPE ArrivalEvent::fromCharToOrder(char o) {
	return (o == 'N') ? TYPE_NRM :
		   (o == 'G') ? TYPE_VGAN :
		   (o == 'V') ? TYPE_VIP :
		   TYPE_CNT;
}


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent()
{
}

void ArrivalEvent::readInfo(std::ifstream& file)
{
	char Ordtype;
	file >> Ordtype;
	OrdType = fromCharToOrder(Ordtype);
	int temp;
	file >> temp;
	Event::EventTime = temp ;
	file >> temp;
	Event::OrderID = temp ;
	file >> temp;
	OrdNumDishes = temp;
	file >> temp;
	OrdMoney = temp;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	//TODO: Replace AddtoDemoQueue call IN PHASE 2

	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID,OrdType, OrdNumDishes, OrdMoney,EventTime);
	pRest->AddtoDemoQueue(pOrd);
}


//void ArrivalEvent::print()
//{
//	std::cout << OrdType << "   " << EventTime << "  " << OrderID << "   " << OrdNumDishes << "   " << OrdMoney << "\n";;
//}
