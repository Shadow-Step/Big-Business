#include "Card.h"
#pragma once
class Player
{
private:
	Sprite sprite;
	Text name;

	int id;
	int money;
public:
	Player(int startMoney);
	virtual ~Player();

	void Update(const float &dtime);
	void Draw(RenderTarget & target);

	static int ID;
};

