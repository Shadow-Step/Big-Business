#include "Auction.h"
#pragma once

namespace stg
{
	enum Type
	{
		Mainmenu,
		Newgame,
		Gameloop,
		Loadgame,
		Options
	};
}

class Stage
{
protected:
	RectangleShape background;
	static Texture backtexture;
	vector<Button*>	button;
	stg::Type stagetype;
public:
	Stage();
	virtual ~Stage();

	//Functions
	virtual void Update(const float &dtime) = 0;
	virtual void Draw(RenderTarget &target) = 0;
	virtual void CheckButton(Button &button) = 0;
	virtual void CatchEvent(const Event&event) = 0;
	static void InitTextures();
	//Getters
	inline const stg::Type GetStageType()const { return this->stagetype; }
	Button& FindButton(form::id id);
};

class STMainmenu : public Stage
{
private:
	vector<Button*>warningbutt;
	bool warnigbox = false;
public:
	STMainmenu();
	~STMainmenu();
	//Functions
	void Update(const float &dtime)override;
	void Draw(RenderTarget &target)override;
	void CheckButton(Button &button)override;
	void CatchEvent(const Event &event)override;
};

class STGameLoop : public Stage
{
private:
	vector<Card*>	card;
	vector<Player*>	player;
	vector<Button*> cardbutt;
	Text turnext;

	Player *plr = nullptr;
	Card   *crd = nullptr;
	Card   *sel = nullptr;
	bool animation		= false;
	bool selector		= false;
	int currplayer		= 0;
	int cubes			= 0;
	float animtime		= 0;
	float animtimeMax	= 0.1;

public:
	STGameLoop();
	~STGameLoop();
	//Functions
	void Update(const float &dtime)override;
	void Draw(RenderTarget &target)override;
	void CheckButton(Button&button)override;
	void CatchEvent(const Event &event)override;
	void EndTurn();
	void CheckCard();
	void Animation(const float &dtime);
	void SelectCard(Card &card);
	void Selector();
	//Static

	static int playersN;
	static int startMoney;
	static bool gameStarted;

};

class STOptions : public Stage
{
public:
	STOptions();
};

class STNewGame : public Stage
{
private:
	
public:
	STNewGame();
	~STNewGame();
	//Functions
	void Update(const float &dtime)override;
	void Draw(RenderTarget &target)override;
	void CheckButton(Button &button)override;
	void CatchEvent(const Event &event)override;
	void DeactSameButtons(form::id id);
};