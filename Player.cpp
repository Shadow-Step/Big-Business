#include "Player.h"
Card* Player::lot = nullptr;
int Player::ID = 1;
int Player::bets[5];

Player::Player(Vector2f position, int startMoney)
{
	this->id = Player::ID;
	this->money = startMoney;
	this->sprite.setRadius(11);
	this->sprite.setOrigin(11, 11);
	this->sprite.setOutlineThickness(1);
	
	
	this->SetPosition(position);
	
	//this->money = 1200;
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
		buttonpos = Vector2f(20, 80);
		break;
	case 2:
		this->name.setPosition(1200, 20);
		this->name.setFillColor(Color::Blue);
		this->sprite.setFillColor(Color::Blue);
		dyn_text_pos = Vector2f(1150, 44);
		dyn_text_dir = Vector2f(-1, 0);
		buttonpos = Vector2f(1160, 80);
		break;
	case 3:
		this->name.setPosition(20, 700);
		this->name.setFillColor(Color::Green);
		this->sprite.setFillColor(Color::Green);
		dyn_text_pos = Vector2f(130, 724);
		dyn_text_dir = Vector2f(1, 0);
		buttonpos = Vector2f(20, 650);
		break;
	case 4:
		this->name.setPosition(1200, 700);
		this->name.setFillColor(Color::Magenta);
		this->sprite.setFillColor(Color::Magenta);
		dyn_text_pos = Vector2f(1150, 724);
		dyn_text_dir = Vector2f(-1, 0);
		buttonpos = Vector2f(1160, 650);
		break;
	}

	aucbutt.push_back(new Button(
		"+",
		Vector2f(32, 32),
		Vector2f(buttonpos),
		form::id::plus));
	aucbutt.push_back(new Button(
		"",
		Vector2f(100, 32),
		Vector2f(buttonpos.x+40,buttonpos.y),
		form::id::buy_card));
	aucbutt.push_back(new Button(
		"-",
		Vector2f(32, 32),
		Vector2f(buttonpos.x+148,buttonpos.y),
		form::id::minus));

	Player::ID++;
}
Player::~Player()
{
	Player::ID = 1;
	for (size_t i = 0; i < prop.size(); i++)
	{
		prop.erase(prop.begin()+i);
	}
	for (size_t i = 0; i < aucbutt.size(); i++)
	{
		delete aucbutt[i];
	}
	aucbutt.resize(0);
}

void Player::Update(const float & dtime)
{
	
	name.setString("Player " + to_string(id) + "\n\n" + "Money: " + to_string(money));
	if (money <= 0 && prop.size() == 0)
	{
		life = false;
	}

	if(Player::lot!=nullptr && money>Player::lot->price)
	for (size_t i = 0; i < aucbutt.size(); i++)
	{
		aucbutt[1]->TextSetString(to_string(bets[id]));
		aucbutt[i]->Update(dtime);
		CheckButton(*aucbutt[i]);
	}
}
void Player::Draw(RenderTarget & target)
{
	target.draw(name);
	target.draw(sprite);
	if (Player::lot != nullptr && money>Player::lot->price)
	for (size_t i = 0; i < aucbutt.size(); i++)
	{
		aucbutt[i]->Draw(target);
	}
}
void Player::CheckButton(Button & button)
{
	if (button.GetInstance() == form::Instance::active)
	{
		button.SetColor(Color(100, 100, 100));
		button.TextSetColor(Color(15, 15, 15));
	}
	else if (button.GetInstance() == form::Instance::idle)
	{
		button.SetColor(Color::Blue);
		button.TextSetColor(Color(196, 196, 196));
	}
	else if (button.GetInstance() == form::Instance::hover)
	{
		button.SetColor(Color::Red);
		button.TextSetColor(Color::White);
	}
	else if (button.GetInstance() == form::Instance::left_click)
	{
		switch (button.GetID())
		{
		case form::id::plus:
			button.SetInstance(form::Instance::hover);
			if(bets[id] + lot->price / 10 < money)
				bets[id] += lot->price / 10;
			aucbutt[1]->TextSetString(to_string(bets[id]));
			break;
		case form::id::minus:
			button.SetInstance(form::Instance::hover);
			if(bets[id] - lot->price / 10 >= lot->price)
				bets[id] -= lot->price / 10;
			aucbutt[1]->TextSetString(to_string(bets[id]));
			break;
		case form::id::buy_card:
			if (money > bets[id])
			{
				button.SetInstance(form::Instance::hover);
				SetMoney(-(bets[this->id] - lot->price));
				BuyProperty(Player::lot);
				Player::lot = nullptr;
			}
			break;
		}
	}
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
void Player::EraseProperty(int id)
{
	for (size_t i = 0; i < prop.size(); i++)
	{
		if (prop[i]->GetID() == id)
		{
			prop.erase(prop.begin() + i);
		}
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
	else if(amount <0)
	{
		DynamicText::SpawnText(to_string(amount),
			dyn_text_pos, dyn_text_dir,Color::Red);
	}
	if (money <= 0)
		bankrupt = true;
	else
		bankrupt = false;
}
void Player::SellProperty(Card * card)
{
	for (size_t i = 0; i < prop.size(); i++)
	{
		if (prop[i]->id == card->id)
		{
			if (prop[i]->level > 1)
			{
				
				prop[i]->level--;
				prop[i]->price -= prop[i]->baseprice;
				prop[i]->profit -= prop[i]->baseprofit;
				SetMoney(prop[i]->baseprice / 2);
			}
			else
			{
				prop[i]->SetOwner(card::Owner::neutral);
				SetMoney(prop[i]->baseprice / 2);
				property[prop[i]->type]--;

				if (property[card->type] == 2)
				{
					for (size_t c = 0; c < prop.size(); c++)
					{
						if (prop[c]->type == card->type)
						{
							prop[c]->baseprofit /= 2;
							prop[c]->profit = prop[c]->baseprofit * prop[c]->level;
							prop[c]->monopoly3 = false;
							prop[c]->UpdateText();
						}
					}
				}
				else if (property[card->type] == 3)
				{
					for (size_t c = 0; c < prop.size(); c++)
					{
						if (prop[c]->type == card->type)
						{
								prop[c]->baseprofit = (prop[c]->baseprofit / 3) * 2;
								prop[c]->profit = prop[c]->baseprofit * prop[c]->level;
								prop[c]->monopoly4 = false;
								prop[c]->monopoly3 = true;
								prop[c]->UpdateText();

						if (prop[c]->id == card->id)
							{
							prop[c]->baseprofit /= 2;
							prop[c]->profit = prop[c]->baseprofit * prop[c]->level;
							prop[c]->monopoly3 = false;
							prop[c]->UpdateText();
							}
						}
					}
				}

				prop.erase(prop.begin() + i);
			}
		}
	}
	
	
}
void Player::StartAuction(Card * card)
{
	for (size_t i = 0; i < 5; i++)
	{
		bets[i] = card->price;
	}
	Player::lot = card;
}
void Player::BuyProperty(Card * card)
{
	SetMoney(-card->price);
	card->SetOwner(id);
	prop.push_back(card);
	property[card->type]++;

	if (property[card->type] == 3)
	{
		for (size_t i = 0; i < prop.size(); i++)
		{
			if (prop[i]->type == card->type)
			{
				prop[i]->baseprofit *= 2;
				prop[i]->profit = prop[i]->baseprofit * prop[i]->level;
				prop[i]->monopoly3 = true;
				prop[i]->UpdateText();
			}
		}
	}
	else if (property[card->type] == 4)
	{
		prop[prop.size() - 1]->baseprofit *= 2;
		prop[prop.size() - 1]->profit = prop[prop.size() - 1]->baseprofit * prop[prop.size() - 1]->level;
		prop[prop.size() - 1]->monopoly3 = true;
		prop[prop.size() - 1]->UpdateText();

		for (size_t i = 0; i < prop.size(); i++)
		{
			if (prop[i]->type == card->type)
			{
				prop[i]->baseprofit = (prop[i]->baseprofit / 2) * 3;
				prop[i]->profit = prop[i]->baseprofit * prop[i]->level;
				prop[i]->monopoly4 = true;
				prop[i]->UpdateText();
			}
		}
	}
}
