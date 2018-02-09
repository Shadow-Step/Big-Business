#include "Card.h"
int Card::ID;
vector<Texture>Card::texture;

Card::Card()
{
	this->card.setSize(Vector2f(100, 160));	
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);
	
	Card::ID++;
}
Card::Card(Vector2f position,float angle)
{
	this->id = Card::ID;

	this->card.setSize(Vector2f(80, 120));
	this->card.setOrigin(card.getSize().x / 2, card.getSize().y / 2);
	this->card.setPosition(position);
	this->card.setRotation(angle);
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);
	
	this->price = 300;
	this->profit = 100;
	this->type = card::Type::type1;

	switch (this->id)
	{
	case 0:
		this->price = 180;
		this->profit = 60;
		break;
	case 1:
		this->price = 300;
		this->profit = 100;
		break;
	case 2:
		this->price = 240;
		this->profit = 80;
		break;
	case 3:
		this->price = 450;
		this->profit = 150;
		break;
	case 4:
		this->price = 90;
		this->profit = 30;
		break;
	case 5:
		this->price = 120;
		this->profit = 40;
		break;
	case 6:
		this->price = 210;
		this->profit = 70;
		break;
	case 7:
		this->price = 600;
		this->profit = 200;
		break;
	case 8:
		this->price = 240;
		this->profit = 80;
		break;
	}
	
	
	this->tooltip = new ToolTip("Price: " + to_string(price) + "\n\n" +
		"Profit: " + to_string(profit) + "\n\n" +
		"Owner: ");

	Card::ID++;
}
Card::Card(Vector2f position, float angle,card::Name name)
{
	this->card.setSize(Vector2f(120, 120));
	this->card.setOrigin(card.getSize().x / 2, card.getSize().y / 2);
	this->card.setPosition(position);
	this->card.setRotation(angle);
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);

	this->owner = card::Owner::goverment;
}
Card::~Card()
{
	Card::ID = 0;
	delete tooltip;
}

void Card::Update(const float & dtime)
{
	if (instance != form::Instance::active)//temp
	{
		if (!card.getGlobalBounds().contains(EngineData::mousepos))
			this->instance = form::Instance::idle;
		else if (card.getGlobalBounds().contains(EngineData::mousepos))
			this->instance = form::Instance::hover;
	}

	if (this->instance == form::Instance::hover &&
		Mouse::isButtonPressed(Mouse::Left) &&
		EngineData::clicktime > EngineData::clicktimeMax)
	{
		this->instance = form::Instance::left_click;
		EngineData::clicktime = 0;
	}
	else if (this->instance == form::Instance::hover &&
		Mouse::isButtonPressed(Mouse::Right))
		this->instance = form::Instance::right_click;
}
void Card::Draw(RenderTarget & target)
{
	target.draw(this->card);
	if(tooltip!=nullptr && tooldraw)
	tooltip->Draw(target);
}

void Card::InitTextures()
{
}
void Card::SetOwner(int id)
{
	this->owner = (card::Owner)id;
	switch (owner)
	{
	case card::Owner::player_1:
		card.setFillColor(Color::Red);
		tooltip->SetString("Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 1");
		break;
	case card::Owner::player_2:
		card.setFillColor(Color::Blue);
		tooltip->SetString("Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 2");
		break;
	case card::Owner::player_3:
		card.setFillColor(Color::Green);
		tooltip->SetString("Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 3");
		break;
	case card::Owner::player_4:
		card.setFillColor(Color::Magenta);
		tooltip->SetString("Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 4");
		break;
	case card::Owner::neutral:
		card.setFillColor(Color::White);
		if(tooltip!=nullptr)
		tooltip->SetString("Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: ");
		break;
	}
}
