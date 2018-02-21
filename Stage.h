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
	enum AIstage
	{
		start_turn,
		throw_cubes,
		check_card,
		end_turn
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

	Player *plr					= nullptr;
	Card   *crd					= nullptr;
	WarningBox *warning			= nullptr;
	void(STGameLoop::*fooptr)() = nullptr;

	bool animation		= false;
	bool selector		= false;
	bool showcards		= false;

	size_t currplayer	= 0;
	int cubes			= 0;
	int viewer			= 1;
	float animtime		= 0;
	float animtimeMax	= 0.1;

	stg::AIstage aistage = stg::AIstage::start_turn;

public:
	STGameLoop();
	~STGameLoop();

	//Functions
	void Update(const float &dtime)override;
	void Draw(RenderTarget &target)override;
	void CheckButton(Button&button)override;
	void CatchEvent(const Event &event)override;
	void PlaceCard();
	void ClearCrd();

	void ThrowCubes();
	void Animation(const float &dtime);
	void CheckCard();
	void EndTurn();
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