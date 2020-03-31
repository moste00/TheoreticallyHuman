#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	
	int totalNumDishes;	//Number of dishes in an order 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	
	//
	// TODO: Add More Data Members As Needed
	//
	int finishedNumDishes; // Number of dishes finished so far

public:
	Order(int ID, ORD_TYPE r_Type, int totalNumDishes, double totalMoney,int ArrTime);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;


	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//
	void promoteToVIP();
	void increaseTotalMoney(double);
	void incrementFinishedDishes(int);
	int getArrivalTime();

};

#endif