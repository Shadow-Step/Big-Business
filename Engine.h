#include "Stage.h"
#pragma once
class Engine
{
private:
	RenderWindow *window;

	Stage		*currentStage = nullptr;
	STGameLoop	*gameloop = nullptr;
	STMainmenu	*mainmenu = nullptr;
	STOptions	*options = nullptr;
	STNewGame   *newgame = nullptr;
public:
	Engine(RenderWindow *window);
	virtual ~Engine();

	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget &target);
	void CatchEvent(const Event &event, const float &dtime);
	void SwitchStage(stg::Type type);
	void CheckMessageBox();
	
};

