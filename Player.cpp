#include "Player.h"

int Player::ID = 1;

Player::Player(Vector2f position, int startMoney)
{
	this->id = Player::ID;
	//this->money = startMoney;
	this->sprite.setSize(Vector2f(22, 22));
	this->sprite.setOrigin(11, 11);
	this->SetPosition(position);
	
	this->money = 1200;

	this->name.setFont(EngineData::font);
	this->name.setCharacterSize(18);

	switch (this->id)
	{
	case 1:
		this->name.setPosition(20, 20);
		this->name.setFillColor(Color::Red);
		this->sprite.setFillColor(Color::Red); 
		break;
	case 2:
		this->name.setPosition(1200, 20);
		this->name.setFillColor(Color::Blue);
		this->sprite.setFillColor(Color::Blue);
		break;
	case 3:
		this->name.setPosition(20, 700);
		this->name.setFillColor(Color::Green);
		this->sprite.setFillColor(Color::Green);
		break;
	case 4:
		this->name.setPosition(1200, 700);
		this->name.setFillColor(Color::Magenta);
		this->sprite.setFillColor(Color::Magenta);
		break;
	}

	Player::ID++;
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
	target.draw(sprite);
}

void Player::SetPosition(Vector2f position)
{
	int temp = 12;
	switch (id)
	{
	case 1:
		sprite.setPosition(position.x - temp, position.y - temp);
		break;
	case 2:
		sprite.setPosition(position.x + temp, position.y - temp);
		break;
	case 3:
		sprite.setPosition(position.x - temp, position.y + temp);
		break;
	case 4:
		sprite.setPosition(position.x + temp, position.y + temp);
		break;
	}
}
