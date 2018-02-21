#pragma once

class Data
{
public:
	Data() {}

	//Data
	int profit = 0;
	int price = 0;
	int base_profit = 0;
	int base_price = 0;
	int profitmod = 0;
	int level = 1;
	int poly_level = 1;
	float boost = 1;

	//Functions
	void setData(int price, int profit);
	void setPolyLevel(int poly_level) { this->poly_level = poly_level; recountData(); }
	void resetData();
	void recountData();
	
	//@boostProfit() ->example "-0.50" decrease by 50%, "+0.20" boost by 20%
	inline void boostProfit(float amount) { this->boost += amount; recountData(); }
	inline void incProfitMod(int amount) { this->profitmod += amount; recountData(); }
	//@incLevel() -> increment++ or decrement-- level; +1 or -1
	inline void incLevel(int amount) { this->level += amount; recountData(); }
	
};

class Pos
{
private:
	size_t vector_size = 32;
	void cDir()
	{
		curr + 1 == vector_size ? front = 0 : front = curr + 1;
		curr - 1 < 0 ? back = vector_size - 1 : back = curr - 1;
	}
public:
	Pos(){}
	Pos(int x) { this->curr = x; cDir(); }
	//Data
	int front;
	int curr;
	int back;
	//Functions
	void setPos(size_t pos)
	{
		if (pos >= vector_size || pos < 0)
			throw("Out of range. Template Pos -> setPos(T pos)");
		else
		{
			this->curr = pos;
			cDir();
		}
	}
	inline void setSize(size_t size) { this->vector_size = size; }

	Pos& operator++()
	{
		curr + 1 == vector_size ? curr = 0 : curr += 1;
		cDir();
		return *this;
	}
	Pos& operator++(int)
	{
		Pos temp = *this;
		++*this;
		return temp;
	}
	Pos& operator--()
	{
		curr - 1 < 0 ? curr = vector_size-1 : curr -= 1;
		cDir();
		return *this;
	}
	bool operator==(Pos & other)
	{
		return this->curr == other.curr;
	}
	void operator=(Pos & other)
	{
		this->curr = other.curr;
		this->front = other.front;
		this->back = other.back;
	}
};