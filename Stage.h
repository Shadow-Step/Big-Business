#include "Player.h"
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

	stg::Type stagetype;
public:
	Stage();
	virtual ~Stage();

	//Functions
	virtual void Update(const float &dtime) = 0;
	virtual void Draw(RenderTarget &target) = 0;
	virtual void CheckButton(Button &button) = 0;
	virtual void CatchEvent(const Event&event) = 0;
	//Getters
	inline const stg::Type GetStageType()const { return this->stagetype; }
};

class STMainmenu : public Stage
{
private:
	vector<Button*>button;
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
	Button& FindButton(form::id id);
};

class STGameLoop : public Stage
{
private:
	vector<Card*>card;
	vector<Player*>player;
public:
	STGameLoop();
	~STGameLoop();
	//Functions
	void Update(const float &dtime)override;
	void Draw(RenderTarget &target)override;
	void CheckButton(Button&button)override;
	void CatchEvent(const Event &event)override;
	
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
	vector<Button*>button;
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