#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, int totalNumDishes, double totalMoney, int ArrTime)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;

	this->totalNumDishes = totalNumDishes;
	this->totalMoney = totalMoney;
	this->ArrTime = ArrTime;

	this->ServTime = -1;
	this->FinishTime = -1;
	this->finishedNumDishes = 0;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::promoteToVIP()
{
	if (type == TYPE_NRM) type = TYPE_VIP;
}

void Order::increaseTotalMoney(double amount)
{
	if (amount > 0) totalMoney += amount;
}

void Order::incrementFinishedDishes(int num)
{
	finishedNumDishes += num;
	if (finishedNumDishes > totalNumDishes) status = DONE;
}

int Order::getArrivalTime()
{
	return ArrTime;
}

