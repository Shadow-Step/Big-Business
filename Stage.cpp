#include "Stage.h"

int STGameLoop::playersN = 1;
int STGameLoop::startMoney = 0;
bool STGameLoop::gameStarted = false;
Stage::Stage()
{
}
Stage::~Stage()
{
}
/////////////////////////////////////////
STMainmenu::STMainmenu()
{
	this->background.setSize(EngineData::winsize);
	this->background.setFillColor(Color::Cyan);//temp

	int space = 5;
	float x = EngineData::winsize.x / 2 - 125;
	float y = 150;
	Vector2f tempsize(250, 50);

	button.push_back(new Button(
		EngineData::strings[str::str_NewGame],
		tempsize,
		Vector2f(x, y + (button.size()*tempsize.y) + space * button.size()), 
		form::id::new_game));

	button.push_back(new Button(
		EngineData::strings[str::str_LoadGame],
		tempsize,
		Vector2f(x, y + (button.size()*tempsize.y)+space * button.size()), 
		form::id::load_game));

	button.push_back(new Button(
		EngineData::strings[str::str_Options],
		tempsize,
		Vector2f(x, y + (button.size()*tempsize.y) + space*button.size()), 
		form::id::options));

	button.push_back(new Button(
		EngineData::strings[str::str_Exit],
		tempsize,
		Vector2f(x, y + (button.size()*tempsize.y) + space * button.size()), 
		form::id::exit));

	//TEMP!!!
	tempsize = Vector2f(75, 50);
	warningbutt.push_back(new Button(
		EngineData::strings[str::str_Yes],
		tempsize,
		Vector2f(595,370),
		form::id::yes));

	
	warningbutt.push_back(new Button(
		EngineData::strings[str::str_No],
		tempsize,
		Vector2f(595+75+20, 370),
		form::id::no));
	//END TEMP!!!
}
STMainmenu::~STMainmenu()
{
	for (size_t i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}
void STMainmenu::Update(const float & dtime)
{
	//temp
	if(STGameLoop::gameStarted)
	FindButton(form::id::new_game).TextSetString(EngineData::strings[str::str_Continue]);
	else
	FindButton(form::id::new_game).TextSetString(EngineData::strings[str::str_NewGame]);
	//end temp

	

	if (warnigbox)
	{
		for (size_t i = 0; i < warningbutt.size(); i++)
		{
			warningbutt[i]->Update(dtime);
			CheckButton(*warningbutt[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < button.size(); i++)
		{
			button[i]->Update(dtime);
			CheckButton(*button[i]);
		}
	}
}
void STMainmenu::Draw(RenderTarget & target)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Draw(target);
	}
	if(warnigbox)
		for (size_t i = 0; i < warningbutt.size(); i++)
		{
			warningbutt[i]->Draw(target);
		}
}
void STMainmenu::CheckButton(Button & button)
{
		if (button.GetInstance() == form::Instance::idle)
			button.SetColor(Color::Blue);
		else if (button.GetInstance() == form::Instance::hover)
			button.SetColor(Color::Red);
		else if (button.GetInstance() == form::Instance::left_click)
		{
			switch (button.GetID())
			{
			case form::id::new_game:
				if (!STGameLoop::gameStarted)
					EngineData::msgbox.push_back(MsgBox::stage_switch_newgame);
				else
					EngineData::msgbox.push_back(MsgBox::stage_switch_gameloop);
				button.SetInstance(form::Instance::hover);
				break;
			case form::id::load_game:
				break;
			case form::id::options:
				break;
			case form::id::exit:
				warnigbox = true;
				button.SetInstance(form::Instance::hover);
				break;

			//TEMP!!!
			case form::id::yes:
				if (!STGameLoop::gameStarted)
					EngineData::msgbox.push_back(MsgBox::window_action_close);
				else
				{
					EngineData::msgbox.push_back(MsgBox::stage_clear_gameloop);
					STGameLoop::gameStarted = false;
				}
				button.SetInstance(form::Instance::hover);
				warnigbox = false;
			break;
			case form::id::no:
				button.SetInstance(form::Instance::hover);
				warnigbox = false;
			break;
			//END TEMP!!!
			}
		}
}
void STMainmenu::CatchEvent(const Event & event)
{
	
}
Button& STMainmenu::FindButton(form::id id)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		if (button[i]->GetID() == id)
			return *button[i];
	}
}
//////////////////////////////////////////////////////
STGameLoop::STGameLoop()
{
	Card::InitTextures();
	
	for (size_t i = 0; i < playersN; i++)
	{
		player.push_back(new Player(startMoney));
	}
	
	Vector2f pos(340, 10);
	Vector2f size(83, 120);
	for (size_t i = 0; i < 8; i++)
	{
		card.push_back(new Card(Vector2f(pos.x+(size.x*i), pos.y)));
		card.push_back(new Card(Vector2f(pos.x+(size.x*i), pos.y+620)));
	}
	pos = Vector2f(25, 12+size.y);
	for (size_t i = 0; i < 6; i++)
	{
		card.push_back(new Card(Vector2f(pos.x+272+40,pos.y+(size.x*i))));
		card[card.size() - 1]->SetRotation(90);
		card.push_back(new Card(Vector2f(pos.x+1059+40, pos.y + (size.x*i))));
		card[card.size() - 1]->SetRotation(90);
	}

	gameStarted = true;

}
STGameLoop::~STGameLoop()
{

	for (size_t i = 0; i < card.size(); i++)
	{
		delete card[i];
	}
	for (size_t i = 0; i < player.size(); i++)
	{
		delete player[i];
	}
}
void STGameLoop::Update(const float & dtime)
{
	for (size_t i = 0; i < player.size(); i++)
	{
		player[i]->Update(dtime);
	}
	for (size_t i = 0; i < card.size(); i++)
	{
		card[i]->Update(dtime);
	}
}
void STGameLoop::Draw(RenderTarget & target)
{
	for (size_t i = 0; i < card.size(); i++)
	{
		card[i]->Draw(target);
	}
	for (size_t i = 0; i < player.size(); i++)
	{
		player[i]->Draw(target);
	}
}
void STGameLoop::CheckButton(Button & button)
{
}
void STGameLoop::CatchEvent(const Event & event)
{
	if (EngineData::clicktime > EngineData::clicktimeMax)
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			EngineData::clicktime = 0;
			EngineData::msgbox.push_back(MsgBox::stage_switch_mainmenu);
		}
	}
}
////////////////////////////////////////////////////
STNewGame::STNewGame()
{
	int space = 5;
	float x = EngineData::winsize.x / 2 - 125;
	float y = 150;
	Vector2f tempsize(150, 50);

	button.push_back(new Button(
		EngineData::strings[str::str_Back],
		tempsize,
		Vector2f(20, EngineData::winsize.y-tempsize.y-20), 
		form::id::back));

	button.push_back(new Button(
		EngineData::strings[str::str_Start],
		tempsize,
		Vector2f(EngineData::winsize.x-tempsize.x-20, 
			EngineData::winsize.y - tempsize.y-20), 
		form::id::launch));
	///////////////
	tempsize = Vector2f(100, 50);
	Vector2f pos(500, 100);
	x = 0;

	button.push_back(new Button(
		tempsize,
		Vector2f(pos.x, pos.y),
		form::id::ng_players_01));
	button[button.size() - 1]->SetInstance(form::Instance::active);

	x++;
	button.push_back(new Button(
		tempsize,
		Vector2f(pos.x+(tempsize.x*x)+space*x, pos.y),
		form::id::ng_players_02));
	x++;
	button.push_back(new Button(
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y),
		form::id::ng_players_03));
	x++;
	button.push_back(new Button(
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y),
		form::id::ng_players_04));
	
}
STNewGame::~STNewGame()
{
	for (size_t i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}
void STNewGame::Update(const float & dtime)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Update(dtime);
		CheckButton(*button[i]);
	}
}
void STNewGame::Draw(RenderTarget & target)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Draw(target);
	}
}
void STNewGame::CheckButton(Button & button)
{
	if(button.GetInstance() == form::Instance::active)
		button.SetColor(Color::Magenta);
	else if (button.GetInstance() == form::Instance::idle)
		button.SetColor(Color::Cyan);
	else if (button.GetInstance() == form::Instance::hover)
		button.SetColor(Color::Blue);
	else if (button.GetInstance() == form::Instance::left_click)
	{
		switch (button.GetID())
		{
		case form::id::back:
			EngineData::msgbox.push_back(MsgBox::stage_switch_mainmenu);
			button.SetInstance(form::Instance::hover);
			break;
		case form::id::launch:
			EngineData::msgbox.push_back(MsgBox::stage_switch_gameloop);
			button.SetInstance(form::Instance::hover);
			break;
		case form::id::ng_players_01:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::playersN = 1;
			break;
		case form::id::ng_players_02:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::playersN = 2;
			break;
		case form::id::ng_players_03:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::playersN = 3;
			break;
		case form::id::ng_players_04:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::playersN = 4;
			break;
		}
	}
}
void STNewGame::CatchEvent(const Event & event)
{
}
void STNewGame::DeactSameButtons(form::id id)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		if (button[i]->GetID() == form::id::ng_players_01 ||
			button[i]->GetID() == form::id::ng_players_02 ||
			button[i]->GetID() == form::id::ng_players_03 ||
			button[i]->GetID() == form::id::ng_players_04)
			button[i]->SetInstance(form::Instance::idle);
	}

}
