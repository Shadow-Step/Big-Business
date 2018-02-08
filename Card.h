#include "Forms.h"


namespace card
{
	enum Owner
	{
		goverment,
		player_1,
		player_2,
		player_3,
		player_4,
		neutral
	};
	enum Type
	{

	};
	enum Name
	{
		startcard,
		bonuscard,
		prisoncard,
		tempcard
	};
}

#pragma once
class Card
{
private:
	RectangleShape card;
	ToolTip * tooltip = nullptr;

	card::Type type;
	card::Name name;
	card::Owner owner = card::Owner::neutral;

	int price;
	int profit;
	int id;
	bool tooldraw = false;
public:
	Card();
	Card(Vector2f position,float angle);
	Card(Vector2f position, float angle, card::Name name);
	virtual ~Card();

	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget &target);
	static void InitTextures();

	//Setters
	inline void SetPosition(Vector2f position) { this->card.setPosition(position); }
	inline void SetPosition(float x, float y) { this->card.setPosition(x, y); }
	inline void SetRotation(float angle) { this->card.setRotation(angle); }
	void SetOwner(int id);
	//Getters
	inline const Vector2f GetSize()const { return this->card.getSize(); }
	inline const Vector2f GetPosition()const { return this->card.getPosition(); }
	inline const card::Owner GetOwner()const { return this->owner; }
	//Static
	static vector<Texture>texture;
	static int ID;

	friend class STGameLoop;
};

