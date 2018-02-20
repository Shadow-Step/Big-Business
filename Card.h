#include "Forms.h"
#include "Data.h"

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
		type1,
		type2,
		type3,
		type4,
		type5,
		type6,
		type7,
		type8,
	};
	enum Name
	{
		startcard,
		bonuscard,
		prisoncard,
		taxcard,
		taxes,
		crd_lumbermill,
		crd_ironmine,
		crd_goldmine,
		crd_factory,
		crd_powerstation
	};
	enum Special
	{
		none,
		cross_card,
		protection,
		credit,
		clone,
		money_back,
		money_aura,
		money_curse
	};
}

#pragma once
class Card
{
protected:
	RectangleShape card;
	ToolTip * tooltip = nullptr;
	Text info;
	card::Type type;
	card::Name name;
	card::Owner owner = card::Owner::neutral;
	card::Special special = card::Special::none;
	form::Instance instance;

	Data data;

	int id;
	bool tooldraw = false;
	
public:
	Card();
	Card(Card & card);
	Card(card::Name name);
	Card(Vector2f position,float angle);
	Card(Vector2f position, float angle, card::Name name);
	virtual ~Card();

	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget &target);
	void UpdateText();
	static void InitTextures();
	static void InitRands();
	void Select(bool choise);
	//Setters
	inline void SetPosition(Vector2f position) { this->card.setPosition(position); }
	inline void SetPosition(float x, float y) { this->card.setPosition(x, y); }
	inline void SetRotation(float angle) { this->card.setRotation(angle); }
	void SetPolyLevel(int level);
	void SetOwner(int id);
	//Getters
	inline const Vector2f GetSize()const { return this->card.getSize(); }
	inline const Vector2f GetPosition()const { return this->card.getPosition(); }
	inline const card::Owner GetOwner()const { return this->owner; }
	inline const int GetID()const { return this->id; }
	//Static
	static vector<Texture>texture;
	static vector<Texture>card_texture;
	static int ID;
	static vector<int>randid;

	friend class STGameLoop;
	friend class Player;
	//Operator
	void operator=(Card & card);
};