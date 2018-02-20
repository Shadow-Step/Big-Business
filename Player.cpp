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

	UpdateText();
	Player::ID++;

	//temp
	this->cards.push_back(new Card(card::Name::crd_lumbermill));
	this->cards.push_back(new Card(card::Name::crd_factory));
	this->cards.push_back(new Card(card::Name::crd_goldmine));
	this->cards.push_back(new Card(card::Name::crd_ironmine));
	this->cards.push_back(new Card(card::Name::crd_powerstation));
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
	if (money <= 0 && prop.size() == 0)
	{
		life = false;
	}

	if(Player::lot!=nullptr && money>Player::lot->data.price)
	for (size_t i = 0; i < aucbutt.size(); i++)
	{
		aucbutt[1]->TextSetString(to_string(bets[id]));
		aucbutt[i]->Update(dtime);
		CheckButton(*aucbutt[i]);
	}
}
void Player::UpdateText()
{
	name.setString("Player " + to_string(id) + "\n\n" + "Money: " + to_string(money));
}
void Player::Draw(RenderTarget & target)
{
	target.draw(name);
	target.draw(sprite);
	if (Player::lot != nullptr && money>Player::lot->data.price)
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
			if(bets[id] + lot->data.price / 10 < money)
				bets[id] += lot->data.price / 10;
			aucbutt[1]->TextSetString(to_string(bets[id]));
			break;
		case form::id::minus:
			button.SetInstance(form::Instance::hover);
			if(bets[id] - lot->data.price / 10 >= lot->data.price)
				bets[id] -= lot->data.price / 10;
			aucbutt[1]->TextSetString(to_string(bets[id]));
			break;
		case form::id::buy_card:
			if (money > bets[id])
			{
				button.SetInstance(form::Instance::hover);
				SetMoney(-(bets[this->id] - lot->data.price));
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
			break;
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

	UpdateText();
}

void Player::SellProperty(Card * card)
{
	auto find_n = [&]() 
	{
		for (size_t i = 0; i < prop.size(); i++)
		{
			if (prop[i]->GetID() == card->GetID())
				return i;
		}
	};
	
	if (card->data.level > 1)
	{
		SetMoney(card->data.base_price / 3);
		card->data.incLevel(-1);
		card->UpdateText();
	}
	else
	{
		SetMoney(card->data.base_price / 2);
		card->data.resetData();
		card->SetOwner(card::Owner::neutral);
		property[card->type]--;
		EraseProperty(card->GetID());

		for (size_t i = 0; i < prop.size(); i++)
		{
			if (prop[i]->type == card->type)
			{
				prop[i]->data.setPolyLevel(property[card->type]);
				prop[i]->UpdateText();
			}
		}
		
	}
}
void Player::UpProperty(Card * card)
{
	int uprice = card->data.base_price / 2;
	if (money > uprice && card->data.level<3)
	{
		SetMoney(-uprice);
		card->data.incLevel(1);
		card->UpdateText();
	}
}
void Player::BuyProperty(Card * card)
{
	SetMoney(-card->data.price);
	card->SetOwner(id);
	prop.push_back(card);
	property[card->type]++;
	for (size_t i = 0; i < prop.size(); i++)
	{
		if (prop[i]->type == card->type)
			prop[i]->SetPolyLevel(property[card->type]);
	}
	
}

void Player::StartAuction(Card * card)
{
	for (size_t i = 0; i < 5; i++)
	{
		bets[i] = card->data.price;
	}
	Player::lot = card;
}