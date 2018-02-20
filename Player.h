#include "Card.h"

#pragma once
class Player
{
private:
	CircleShape sprite;
	Text name;
	Vector2f dyn_text_pos;
	Vector2f dyn_text_dir;
	Vector2f buttonpos;

	vector<Card*>cards;//

	vector<Card*>prop;
	vector<Button*>aucbutt;

	Pos pos;

	int id;
	int money;
	//int position = 0;
	int property[8]; // refactoring!
	int credit_count = 0;

	bool credit		= false;
	bool protection = false;

	bool active		= false;
	bool AI			= false;
	bool bankrupt	= false;
	bool inprison	= false;
	bool life		= true; //?

public:
	Player(Vector2f position,int startMoney);
	virtual ~Player();
	//Functions
	void Update(const float &dtime);
	void UpdateText();
	void Draw(RenderTarget & target);
	void CheckButton(Button & button);
	void EraseProperty(int id);
	void SetMoney(int amount);
	void BuyProperty(Card *card);
	void SellProperty(Card *card);
	void UpProperty(Card *card);
	static void StartAuction(Card * card);
	//Getters
	inline const int GetPosition()const { return this->pos.curr; }
	inline const int GetID()const { return this->id; }
	//Setters
	void SetPosition(Vector2f position);
	inline void SetPosition(int position) { this->pos.setPos(position); }
	//Static
	static int ID;
	static Card *lot;
	static int bets[5];
	

	friend class STGameLoop;
};

