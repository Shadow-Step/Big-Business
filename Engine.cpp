#include "Engine.h"



Engine::Engine(RenderWindow *window)
{
	this->window = window;
	window->setKeyRepeatEnabled(false);//temp
	window->setMouseCursorVisible(false);//temp

	Cursor::InitCursor();
	EngineData::InitFont();
	EngineData::InitStrings();

	//mainmenu = new STMainmenu();
	//this->currentStage = mainmenu;

	gameloop = new STGameLoop();
	this->currentStage = gameloop;
}
Engine::~Engine()
{
	
}

void Engine::Update(const float & dtime)
{
	CheckMessageBox();
	currentStage->Update(dtime);
	Cursor::Update(dtime);
}
void Engine::Draw(RenderTarget & target)
{
	currentStage->Draw(target);
	Cursor::Draw(target);
}
void Engine::CatchEvent(const Event & event, const float & dtime)
{
	currentStage->CatchEvent(event);
}
void Engine::CheckMessageBox()
{
	for (size_t i = 0; i < EngineData::msgbox.size(); i++)
	{
		switch (EngineData::msgbox[i])
		{
			////STAGE!!!
		case MsgBox::stage_switch_newgame:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			SwitchStage(stg::Type::Newgame);
			break;
		case MsgBox::stage_switch_loadgame:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			SwitchStage(stg::Type::Loadgame);
			break;
		case MsgBox::stage_switch_options:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			SwitchStage(stg::Type::Options);
			break;
		case MsgBox::stage_switch_gameloop:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			SwitchStage(stg::Type::Gameloop);
			break;
		case MsgBox::stage_switch_mainmenu:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			SwitchStage(stg::Type::Mainmenu);
			break;
			//STAGE CLEAR
		case MsgBox::stage_clear_gameloop:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			delete gameloop;
			gameloop = nullptr;
			break;
			//WINDOW
		case MsgBox::window_action_close:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			window->close();
			break;
		case MsgBox::window_action_fullscreen:
			EngineData::msgbox.erase(EngineData::msgbox.begin() + i);
			window->create(VideoMode::getDesktopMode(), "Big Business",Style::Fullscreen);
			break;
		}
	}
}
void Engine::SwitchStage(stg::Type type)
{
	switch (type)
	{
	case stg::Type::Mainmenu:
		if (mainmenu == nullptr)
			mainmenu = new STMainmenu();
		currentStage = mainmenu;
			break;
	case stg::Type::Gameloop:
		if (gameloop == nullptr)
			gameloop = new STGameLoop();//temp
			
		currentStage = gameloop;
		break;
	case stg::Type::Options:
		break;
	case stg::Type::Loadgame:
		break;
	case stg::Type::Newgame:
		if (newgame == nullptr)
			newgame = new STNewGame();//temp
		currentStage = newgame;
		break;
	}
}
