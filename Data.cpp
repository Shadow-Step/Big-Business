#include "Data.h"

void Data::setData(int price, int profit)
{
	{
		this->price = base_price = price;
		this->profit = base_profit = profit;
	}
}
void Data::resetData()
{
	level = 1;
	poly_level = 1;
	boost = 1;
	profitmod = 0;
	recountData();
}
void Data::recountData()
{
	price = base_price * ((float)level / 2.f + 0.5); 
	poly_level > 2 ? base_profit = price * ((float)poly_level / 4) : base_profit = price / 3;
	profit = (base_profit + profitmod)*boost;
}
