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
	
	switch (this->id)
	{
	case 0:
		this->type = card::Type::type2;
		this->price = 180;
		this->profit = 60;
		break;
	case 1:
		this->type = card::Type::type3;
		this->price = 300;
		this->profit = 100;
		break;
	case 2:
		this->type = card::Type::type3;
		this->price = 240;
		this->profit = 80;
		break;
	case 3:
		this->type = card::Type::type2;
		this->price = 450;
		this->profit = 150;
		break;
	case 4:
		this->type = card::Type::type3;
		this->price = 90;
		this->profit = 30;
		break;
	case 5:
		this->type = card::Type::type2;
		this->price = 120;
		this->profit = 40;
		break;
	case 6:
		this->type = card::Type::type4;
		this->price = 210;
		this->profit = 70;
		break;
	case 7:
		this->type = card::Type::type4;
		this->price = 600;
		this->profit = 200;
		break;
	case 8:
		this->type = card::Type::type4;
		this->price = 240;
		this->profit = 80;
		break;
	case 9:
		this->type = card::Type::type5;
		this->price = 1200;
		this->profit = 400;
		break;
	case 10:
		this->type = card::Type::type2;
		this->price = 120;
		this->profit = 40;
		break;
	case 11:
		this->type = card::Type::type4;
		this->price = 900;
		this->profit = 300;
		break;
	case 12:
		this->type = card::Type::type5;
		this->price = 250;
		this->profit = 50;
	case 13:
		this->type = card::Type::type5;
		this->price = 2100;
		this->profit = 700;
		break;
	case 14:
		this->type = card::Type::type1;
		this->name = card::Name::taxes;
		this->price = 600;
		this->profit = 0;
		break;
	case 15:
		this->type = card::Type::type3;
		this->price = 600;
		this->profit = 200;
		break;
	case 16:
		this->type = card::Type::type5;
		this->price = 3000;
		this->profit = 1000;
		break;
	case 17:
		this->type = card::Type::type1;
		this->name = card::Name::taxes;
		this->price = 600;
		this->profit = 0;
		break;
	case 18:
		this->type = card::Type::type7;
		this->price = 300;
		this->profit = 100;
		break;
	case 19:
		this->type = card::Type::type6;
		this->price = 210;
		this->profit = 70;
		break;
	case 20:
		this->type = card::Type::type7;
		this->price = 240;
		this->profit = 80;
		break;
	case 21:
		this->type = card::Type::type1;
		this->name = card::Name::taxes;
		this->price = 600;
		this->profit = 0;
		break;
	case 22:
		this->type = card::Type::type1;
		this->name = card::Name::taxes;
		this->price = 600;
		this->profit = 0;
		break;
	case 23:
		this->type = card::Type::type6;
		this->price = 3000;
		this->profit = 1000;
		break;
	case 24:
		this->type = card::Type::type6;
		this->price = 900;
		this->profit = 300;
		break;
	case 25:
		this->type = card::Type::type7;
		this->price = 90;
		this->profit = 30;
		break;
	case 26:
		this->type = card::Type::type7;
		this->price = 600;
		this->profit = 200;
		break;
	case 27:
		this->type = card::Type::type6;
		this->price = 2700;
		this->profit = 900;
		break;
	}
	
	switch (this->type)
	{
	case card::Type::type1:
		card.setOutlineColor(Color(100,15,100));
		break;
	case card::Type::type2:
		card.setOutlineColor(Color::Red);
		break;
	case card::Type::type3:
		card.setOutlineColor(Color(100,100,100));
		break;
	case card::Type::type4:
		card.setOutlineColor(Color(123,11,200));
		break;
	case card::Type::type5:
		card.setOutlineColor(Color::Blue);
		break;
	case card::Type::type6:
		card.setOutlineColor(Color::Magenta);
		break;
	case card::Type::type7:
		card.setOutlineColor(Color::Yellow);
		break;
	case card::Type::type8:
		card.setOutlineColor(Color::Green);
		break;
	}
	this->tooltip = new ToolTip("Lvl " + to_string(level) + 
		"\n\n"+"Price: " + to_string(price) + "\n\n" +
		"Profit: " + to_string(profit) + "\n\n" +
		"Owner: ");
	baseprofit = this->profit;
	baseprice = this->price;
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
	this->name = name;
	this->type = card::Type::type8;
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

	/*if (this->instance == form::Instance::hover &&
		Mouse::isButtonPressed(Mouse::Left) &&
		EngineData::clicktime > EngineData::clicktimeMax)
	{
		this->instance = form::Instance::active;
		tooldraw = true;
		EngineData::clicktime = 0;
	}
	else if (this->instance == form::Instance::active &&
		Mouse::isButtonPressed(Mouse::Left) &&
		!card.getGlobalBounds().contains(EngineData::mousepos))
	{
		EngineData::clicktime = 0;
		this->instance = form::Instance::idle;
		tooldraw = false;
	}*/


	if (tooldraw)
		card.setOutlineThickness(3);
	else
		card.setOutlineThickness(-5);

	if (monopoly3)
	{
		card.setOutlineThickness(-12);
		//card.setOutlineColor(Color(250,100,0));
	}
	if (monopoly4)
	{
		card.setOutlineThickness(-16);
		//card.setOutlineColor(Color(64, 128, 128));
	}
	
}
void Card::Draw(RenderTarget & target)
{
	target.draw(this->card);
	if(tooltip!=nullptr && tooldraw)
	tooltip->Draw(target);
}
void Card::UpdateText()
{
	if (tooltip != 0)
	{
		if(owner!=card::Owner::neutral)
		tooltip->SetString("Lvl " + to_string(level) +
			"\n\n" + "Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl " + to_string(owner));
		else
			tooltip->SetString("Lvl " + to_string(level) +
				"\n\n" + "Price: " + to_string(price) + "\n\n" +
				"Profit: " + to_string(profit) + "\n\n" +
				"Owner: ");
	}
}
void Card::InitTextures()
{
}
void Card::Select(bool choise)
{
	if (choise = true)
	{
		card.setOutlineThickness(3);
		tooldraw = true;
	}
	else
	{
		card.setOutlineThickness(1);
		tooldraw = false;
	}
}
void Card::SetOwner(int id)
{
	this->owner = (card::Owner)id;
	switch (owner)
	{
	case card::Owner::player_1:
		card.setFillColor(Color::Red);
		tooltip->SetString("Lvl " + to_string(level) +
			"\n\n" + "Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 1");
		break;
	case card::Owner::player_2:
		card.setFillColor(Color::Blue);
		tooltip->SetString("Lvl " + to_string(level) +
			"\n\n" + "Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 2");
		break;
	case card::Owner::player_3:
		card.setFillColor(Color::Green);
		tooltip->SetString("Lvl " + to_string(level) +
			"\n\n" + "Price: " + to_string(price) + "\n\n" +
			"Profit: " + to_string(profit) + "\n\n" +
			"Owner: Pl 3");
		break;
	case card::Owner::player_4:
		card.setFillColor(Color::Magenta);
		tooltip->SetString("Lvl " + to_string(level) +
			"\n\n" + "Price: " + to_string(price) + "\n\n" +
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
