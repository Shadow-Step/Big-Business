#include "Card.h"
int Card::ID;
vector<Texture>Card::texture;
vector<Texture>Card::card_texture;
vector<int>Card::randid;

Card::Card()
{
	this->card.setSize(Vector2f(100, 160));	
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);
	
	Card::ID++;
}
Card::Card(Card & card)
{

}
Card::Card(card::Name name)
{
	this->card.setSize(Vector2f(160, 240));
	this->card.setOrigin(card.getSize().x / 2, card.getSize().y / 2);
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);

	this->id = Card::ID;
	this->type = card::Type::type8;
	this->name = name;
	
	switch (name)
	{
	case card::Name::crd_lumbermill:
		data.setData(90, 30);
		this->special = card::Special::clone;
		this->card.setTexture(&card_texture[0]);
		break;
	case card::Name::crd_factory:
		data.setData(240, 80);
		this->special = card::Special::money_curse;
		this->card.setTexture(&card_texture[1]);
		break;
	case card::Name::crd_goldmine:
		data.setData(180, 60);
		this->special = card::Special::clone;
		this->card.setTexture(&card_texture[2]);
		break;
	case card::Name::crd_ironmine:
		data.setData(300, 100);
		this->special = card::Special::money_aura;
		this->card.setTexture(&card_texture[3]);
		break;
	case card::Name::crd_powerstation:
		data.setData(210, 70);
		this->special = card::Special::money_aura;
		this->card.setTexture(&card_texture[4]);
		break;
	}

	this->tooltip = new ToolTip("Lvl " + to_string(data.level) +
		"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
		"Profit: " + to_string(data.profit) + "\n\n" +
		"Owner: ");

	this->info.setFont(EngineData::font);
	this->info.setFillColor(Color::Black);
	this->info.setString(to_string(data.price) + "\n\n\n\n\n\n\n\n" + to_string(data.profit));
	
		
	Card::ID++;
}
Card::Card(Vector2f position,float angle)
{
	if (Card::ID == 4)
	{
		this->id = 4;
	}
	else if (Card::ID == 11)
	{
		this->id = 11;
	}
	else if (Card::ID == 17)
	{
		this->id = 17;
	}
	else if (Card::ID == 25)
	{
		this->id = 25;
	}
	else
	{
	
		int temp = rand() % Card::randid.size();
		
			while (Card::randid[temp] == 999)
				temp = rand() % randid.size();

		this->id = Card::randid[temp];
		randid.erase(randid.begin() + temp);
		
	}

	//this->id = Card::ID;
	
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
		data.setData(180, 60);
		break;
	case 1:
		this->type = card::Type::type3;
		data.setData(300, 100);
		break;
	case 2:
		this->type = card::Type::type3;
		data.setData(240, 80);
		break;
	case 3:
		this->type = card::Type::type2;
		data.setData(450, 150);
		break;
	case 4:
		this->type = card::Type::type1;
		this->owner = card::Owner::goverment;
		this->name = card::Name::bonuscard;
		break;
	case 5:
		this->type = card::Type::type2;
		data.setData(120, 40);
		break;
	case 6:
		this->type = card::Type::type4;
		data.setData(210, 70);
		break;
	case 7:
		this->type = card::Type::type4;
		data.setData(600, 200);
		break;
	case 8:
		this->type = card::Type::type4;
		data.setData(240, 80);
		break;
	case 9:
		this->type = card::Type::type5;
		data.setData(450, 150);
		break;
	case 10:
		this->type = card::Type::type2;
		data.setData(120, 40);
		break;
	case 11:
		this->type = card::Type::type1;
		this->owner = card::Owner::goverment;
		this->name = card::Name::bonuscard;
		break;
	case 12:
		this->type = card::Type::type5;
		data.setData(250, 50);
	case 13:
		this->type = card::Type::type5;
		data.setData(300, 100);
		break;
	case 14:
		this->type = card::Type::type3;
		data.setData(120, 40);
		break;
	case 15:
		this->type = card::Type::type3;
		data.setData(600, 200);
		break;
	case 16:
		this->type = card::Type::type5;
		data.setData(900, 300);
		break;
	case 17:
		this->type = card::Type::type1;
		this->owner = card::Owner::goverment;
		this->name = card::Name::bonuscard;
		break;
	case 18:
		this->type = card::Type::type7;
		data.setData(300, 100);
		break;
	case 19:
		this->type = card::Type::type6;
		data.setData(210, 70);
		break;
	case 20:
		this->type = card::Type::type7;
		data.setData(240, 80);
		break;
	case 21:
		this->type = card::Type::type4;
		data.setData(900, 300);
		break;
	case 22:
		this->type = card::Type::type7;
		data.setData(120, 40);
		break;
	case 23:
		this->type = card::Type::type6;
		data.setData(480, 160);
		break;
	case 24:
		this->type = card::Type::type6;
		data.setData(210, 70);
		break;
	case 25:
		this->type = card::Type::type1;
		this->owner = card::Owner::goverment;
		this->name = card::Name::bonuscard;
		break;
	case 26:
		this->type = card::Type::type7;
		data.setData(600, 200);
		break;
	case 27:
		this->type = card::Type::type6;
		data.setData(450, 150);
		break;
	}
	
	switch (this->type)
	{
	case card::Type::type1:
		card.setOutlineColor(Color(100,15,100));
		this->card.setTexture(&Card::texture[1]);
		break;
	case card::Type::type2:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color(230,125,0));
		break;
	case card::Type::type3:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color(100,100,100));
		break;
	case card::Type::type4:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color(123,11,200));
		break;
	case card::Type::type5:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color(0,0,160));
		break;
	case card::Type::type6:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color::Green);
		break;
	case card::Type::type7:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color::Yellow);
		break;
	case card::Type::type8:
		this->card.setTexture(&Card::texture[0]);
		card.setOutlineColor(Color::Green);
		break;
	}

	if(type != card::Type::type1)
	this->tooltip = new ToolTip("Lvl " + to_string(data.level) +
		"\n\n"+"Price: " + to_string(data.price) + "\n\n" +
		"Profit: " + to_string(data.profit) + "\n\n" +
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

	if(name == card::Name::taxcard)
	this->card.setTexture(&Card::texture[3]);
	else if (name == card::Name::prisoncard)
	this->card.setTexture(&Card::texture[4]);
	else
	this->card.setTexture(&Card::texture[2]);

	this->data.price = 99999;
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

	if (tooldraw)
		card.setOutlineThickness(3);
	else
		card.setOutlineThickness(-5);

	if (data.poly_level == 3)
	{
		card.setOutlineThickness(-12);
		
	}
	if (data.poly_level == 4)
	{
		card.setOutlineThickness(-16);
		
	}
	
}
void Card::Draw(RenderTarget & target)
{
	target.draw(this->card);
	//target.draw(this->info);
	if(tooltip!=nullptr && tooldraw)
	tooltip->Draw(target);
	
}
void Card::UpdateText()
{
	if (tooltip != 0)
	{
		if(owner!=card::Owner::neutral)
		tooltip->SetString("Lvl " + to_string(data.level) +
			"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: Pl " + to_string(owner));
		else
			tooltip->SetString("Lvl " + to_string(data.level) +
				"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
				"Profit: " + to_string(data.profit) + "\n\n" +
				"Owner: ");
	}
}
void Card::InitTextures()
{
	Texture temp;
	temp.loadFromFile("texture/card.jpg");
	Card::texture.push_back(temp);
	temp.loadFromFile("texture/bonuscard.png");
	Card::texture.push_back(temp);
	temp.loadFromFile("texture/startcard.png");
	Card::texture.push_back(temp);
	temp.loadFromFile("texture/taxcard.png");
	Card::texture.push_back(temp);
	temp.loadFromFile("texture/jailcard.png");
	Card::texture.push_back(temp);

	temp.loadFromFile("texture/cards/001.png");
	Card::card_texture.push_back(temp);
	temp.loadFromFile("texture/cards/002.png");
	Card::card_texture.push_back(temp);
	temp.loadFromFile("texture/cards/003.png");
	Card::card_texture.push_back(temp);
	temp.loadFromFile("texture/cards/004.png");
	Card::card_texture.push_back(temp);
	temp.loadFromFile("texture/cards/005.png");
	Card::card_texture.push_back(temp);
	
}
void Card::InitRands()
{
	for (size_t i = 0; i < 28; i++)
	{
		if(i != 4 && i != 11 && i != 17 && i != 25)
		randid.push_back(i);
		else
			randid.push_back(999);
	}
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
void Card::SetPolyLevel(int level)
{
	data.setPolyLevel(level);
	UpdateText();
}
void Card::SetOwner(int id)
{
	this->owner = (card::Owner)id;
	switch (owner)
	{
	case card::Owner::player_1:
		card.setFillColor(Color::Red);
		tooltip->SetString("Lvl " + to_string(data.level) +
			"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: Pl 1");
		break;
	case card::Owner::player_2:
		card.setFillColor(Color::Blue);
		tooltip->SetString("Lvl " + to_string(data.level) +
			"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: Pl 2");
		break;
	case card::Owner::player_3:
		card.setFillColor(Color::Green);
		tooltip->SetString("Lvl " + to_string(data.level) +
			"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: Pl 3");
		break;
	case card::Owner::player_4:
		card.setFillColor(Color::Magenta);
		tooltip->SetString("Lvl " + to_string(data.level) +
			"\n\n" + "Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: Pl 4");
		break;
	case card::Owner::neutral:
		card.setFillColor(Color::White);
		if(tooltip!=nullptr)
		tooltip->SetString("Price: " + to_string(data.price) + "\n\n" +
			"Profit: " + to_string(data.profit) + "\n\n" +
			"Owner: ");
		break;
	}
}

void Card::operator=(Card & card)
{
	this->card.setFillColor(card.card.getFillColor());
	this->data.price = card.data.price;
	this->data.base_price = card.data.base_price;
	this->data.profit = card.data.profit;
	this->data.base_profit = card.data.base_profit;
	this->id = card.id;
	this->data.level = card.data.level;
	this->data.profitmod = card.data.profitmod;
	this->special = card.special;
	
	UpdateText();
}
