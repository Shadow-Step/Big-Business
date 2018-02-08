#include "Forms.h"

namespace plr
{
	enum pl_enum
	{
		player_1,
		player_2,
		player_3,
		player_4,
		neutral
	};
}
namespace card
{
	enum Type
	{

	};
	enum Name
	{

	};
}

#pragma once
class Card
{
private:
	RectangleShape card;

	card::Type type;
	card::Name name;
	plr::pl_enum owner = plr::neutral;

	int price;
	int profit;
	
	
public:
	Card();
	virtual ~Card();

	//Functions
	static void InitTextures();

	static vector<Texture>texture;
};

