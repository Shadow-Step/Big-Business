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
	for (size_t i = 0; i < 8; i++)
	{
		this->property[i] = 0;
	}

	this->name.setFont(EngineData::font);
	this->name.setCharacterSize(18);

	switch (this->id)
	{
	case 1:
		this->name.setPosition(20, 20);
		this->name.setFillColor(Color::Red);
		this->sprite.setFillColor(Color::Red);
		dyn_text_pos = Vector2f(130, 44);
		dyn_text_dir = Vector2f(1, 0);
		break;
	case 2:
		this->name.setPosition(1200, 20);
		this->name.setFillColor(Color::Blue);
		this->sprite.setFillColor(Color::Blue);
		dyn_text_pos = Vector2f(1150, 44);
		dyn_text_dir = Vector2f(-1, 0);
		break;
	case 3:
		this->name.setPosition(20, 700);
		this->name.setFillColor(Color::Green);
		this->sprite.setFillColor(Color::Green);
		dyn_text_pos = Vector2f(130, 724);
		dyn_text_dir = Vector2f(1, 0);
		break;
	case 4:
		this->name.setPosition(1200, 700);
		this->name.setFillColor(Color::Magenta);
		this->sprite.setFillColor(Color::Magenta);
		dyn_text_pos = Vector2f(1150, 724);
		dyn_text_dir = Vector2f(-1, 0);
		break;
	}

	Player::ID++;
}

Player::~Player()
{
	Player::ID = 1;
	for (size_t i = 0; i < prop.size(); i++)
	{
		prop.erase(prop.begin()+i);
	}
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
void Player::SetMoney(int amount)
{
	this->money += amount;
	if (amount > 0)
	{
		DynamicText::SpawnText("+" + to_string(amount),
			dyn_text_pos, dyn_text_dir, Color::Green);
	}
	else
	{
		DynamicText::SpawnText(to_string(amount),
			dyn_text_pos, dyn_text_dir,Color::Red);
	}
}

