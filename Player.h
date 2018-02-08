#include "Card.h"
#pragma once
class Player
{
private:
	Sprite sprite;

	int money;
public:
	Player(int startMoney);
	virtual ~Player();
};

