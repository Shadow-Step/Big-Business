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
	Card(Vector2f position);
	virtual ~Card();

	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget &target);
	static void InitTextures();

	//Setters
	inline void SetPosition(Vector2f position) { this->card.setPosition(position); }
	inline void SetPosition(float x, float y) { this->card.setPosition(x, y); }
	inline void SetRotation(float angle) { this->card.setRotation(angle); }
	//Getters
	inline const Vector2f GetSize()const { return this->card.getSize(); }
	//Static
	static vector<Texture>texture;
	static int ID;
};

