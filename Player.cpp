#include "Player.h"

int Player::ID = 1;

Player::Player(int startMoney)
{
	//this->money = startMoney;
	this->id = Player::ID;
	this->money = 500;

	Player::ID++;

	this->name.setFont(EngineData::font);
	this->name.setCharacterSize(18);

	switch (this->id)
	{
	case 1:
		this->name.setPosition(20, 20);
		this->name.setFillColor(Color::Red);
		break;
	case 2:
		this->name.setPosition(1200, 20);
		this->name.setFillColor(Color::Blue);
		break;
	case 3:
		this->name.setPosition(20, 700);
		this->name.setFillColor(Color::Green);
		break;
	case 4:
		this->name.setPosition(1200, 700);
		this->name.setFillColor(Color::Magenta);
		break;
	}
}

Player::~Player()
{
	Player::ID = 1;
}

void Player::Update(const float & dtime)
{
	name.setString("Player " + to_string(id) + "\n\n" + "Money: " + to_string(money));
}

void Player::Draw(RenderTarget & target)
{
	target.draw(name);
}
