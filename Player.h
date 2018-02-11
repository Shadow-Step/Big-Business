#include "Card.h"
#pragma once
class Player
{
private:
	RectangleShape sprite;
	Text name;
	Vector2f dyn_text_pos;
	Vector2f dyn_text_dir;
	vector<Card*>prop;

	int id;
	int money;
	int position = 0;
	int property[8];
	bool bankrupt = false;
	bool inprison = false;
	bool life = true;

public:
	Player(Vector2f position,int startMoney);
	virtual ~Player();
	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget & target);
	void SetPosition(Vector2f position);
	void EraseProperty(int id);
	void SetMoney(int amount);
	void BuyProperty(Card *card);
	void SellProperty(Card *card);
	//Getters
	inline const int GetPosition()const { return this->position; }
	inline const int GetID()const { return this->id; }
	//Setters
	inline void SetPosition(int position) { this->position+position>=32?this->position = 0:this->position+=position; }
	//Static
	static int ID;

	friend class STGameLoop;
};

