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
Button & Stage::FindButton(form::id id)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		if (button[i]->GetID() == id)
			return *button[i];
	}
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
	for (size_t i = 0; i < warningbutt.size(); i++)
	{
		delete warningbutt[i];
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

//////////////////////////////////////////////////////
STGameLoop::STGameLoop()
{
	Card::InitTextures();
	
	Vector2f size(220, 60);
	button.push_back(new Button(
		EngineData::strings[str::str_EndTurn],
		size,
		Vector2f(350, EngineData::winsize.y - size.y-139),
		form::id::end_turn));

	button.push_back(new Button(
		EngineData::strings[str::str_ThrowCubes],
		size,
		Vector2f(793,EngineData::winsize.y - size.y - 139),
		form::id::throw_cubes));
	
	Vector2f pos(300, 48);
	size = Vector2f(80, 120);
	int space = 4;

	//Down horizontal line
	for (size_t i = 0; i < 10; i++)
	{
		if(i == 0)
			card.push_back(new Card(Vector2f(
				EngineData::winsize.x+20 - pos.x - (size.x*i) - (space*i),
				EngineData::winsize.y - size.y + pos.y), 0,card::Name::startcard));
		else if (i == 9)
			card.push_back(new Card(Vector2f(
				EngineData::winsize.x-20 - pos.x - (size.x*i) - (space*i),
				EngineData::winsize.y - size.y + pos.y), 0,card::Name::tempcard));
		else
		card.push_back(new Card(Vector2f(
		EngineData::winsize.x - pos.x - (size.x*i)-(space*i),
		EngineData::winsize.y-size.y+pos.y),0));
	}
	//Left vertical line
	for (size_t i = 0; i < 6; i++)
	{
		card.push_back(new Card(Vector2f(
			0 + card[9]->GetPosition().x,
			card[9]->GetPosition().y - 104 - (size.x*i) - (space*i)), 90));
	}
	//Top horizontal line
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 0)
			card.push_back(new Card(Vector2f(
				card[15]->GetPosition().x,
				card[15]->GetPosition().y-104), 0, card::Name::bonuscard));
		else if (i == 9)
			card.push_back(new Card(Vector2f(
				card[card.size()-1]->GetPosition().x+104,
				card[card.size() - 1]->GetPosition().y), 0, card::Name::prisoncard));
		else
			card.push_back(new Card(Vector2f(
				card[16]->GetPosition().x + 20+ (size.x*i) + (space*i),
				card[16]->GetPosition().y), 180));
	}
	//Right vertical line
	for (size_t i = 0; i < 6; i++)
	{
		card.push_back(new Card(Vector2f(
			card[25]->GetPosition().x,
			card[25]->GetPosition().y + 104 + (size.x*i) + (space*i)), 270));
	}

	for (size_t i = 0; i < playersN; i++)
	{
		player.push_back(new Player(card[0]->GetPosition(),startMoney));
	}

	plr = player[0];
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
	if (!animation)
	{
		for (size_t i = 0; i < button.size(); i++)
		{
			button[i]->Update(dtime);
			CheckButton(*button[i]);
		}
		for (size_t i = 0; i < player.size(); i++)
		{
			player[i]->Update(dtime);
		}
		for (size_t i = 0; i < card.size(); i++)
		{
			card[i]->Update(dtime);
			SelectCard(*card[i]);
		}
	}
	else
	{
		Animation(dtime);
	}

	//Update Dynamic Text
	for (size_t i = 0; i < DynamicText::dyntext.size(); i++)
	{
		if (DynamicText::dyntext[i]->IsAlive())
			DynamicText::dyntext[i]->Update(dtime);
		else
		{
			delete DynamicText::dyntext[i];
			DynamicText::dyntext.erase(DynamicText::dyntext.begin() + i);
		}
	}
}
void STGameLoop::Draw(RenderTarget & target)
{
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Draw(target);
	}
	for (size_t i = 0; i < card.size(); i++)
	{
		card[i]->Draw(target);
	}
	for (size_t i = 0; i < player.size(); i++)
	{
		player[i]->Draw(target);
	}
	for (size_t i = 0; i < DynamicText::dyntext.size(); i++)
	{
		DynamicText::dyntext[i]->Draw(target);
	}
}
void STGameLoop::CheckButton(Button & button)
{
	if (button.GetInstance() == form::Instance::active)
	{
		button.SetColor(Color(100, 100, 100));
		button.TextSetColor(Color(15, 15, 15));
	}
	else if (button.GetInstance() == form::Instance::idle)
	{
		button.SetColor(Color::Blue);
		button.TextSetColor(Color(196, 196, 196));
	}
	else if (button.GetInstance() == form::Instance::hover)
	{
		button.SetColor(Color::Red);
		button.TextSetColor(Color::White);
	}
	else if (button.GetInstance() == form::Instance::left_click)
	{
		switch (button.GetID())
		{
		case form::id::end_turn:
			button.SetInstance(form::Instance::active);
			FindButton(form::id::throw_cubes).SetInstance(form::Instance::hover);
			EndTurn();
			break;
		case form::id::throw_cubes:
			button.SetInstance(form::Instance::active);
			FindButton(form::id::end_turn).SetInstance(form::Instance::hover);
			cubes = rand() % 12 + 2;
			animation = true;
			break;
		case form::id::buy_card:
			if (plr->money >= crd->price)
			{
				plr->property[crd->type]++;
				plr->prop.push_back(crd);
				plr->SetMoney(-crd->price);
				if (plr->property[crd->type] == 3)
					SetMonopoly(crd->type, true);
				crd->SetOwner(plr->GetID());

				//card[player[currplayer]->GetPosition()]->SetOwner(player[currplayer]->GetID());
				delete this->button[this->button.size() - 1];
				this->button.pop_back();
			}
			else
			{
				button.SetInstance(form::Instance::active);
			}
			break;
		}
	}
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
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			EngineData::clicktime = 0;
			plr->SetMoney(plr->prop[plr->prop.size()-1]->price / 2);
			plr->prop[plr->prop.size() - 1]->SetOwner(card::Owner::neutral);
			plr->prop.pop_back();
		}
	}
}
void STGameLoop::EndTurn()
{
	crd->tooldraw = false;
	crd = nullptr;

	int alive = 0;
	for (size_t i = 0; i < player.size(); i++)
	{
		if (player[i]->money <= 0)
		{
			for (size_t c = 0; c < card.size(); c++)
			{
				if (card[c]->owner == (card::Owner)player[i]->GetID())
				{
					card[c]->SetOwner(card::Owner::neutral);
				}
			}
			player[i]->bankrupt = true;
			for (size_t s = 0; s < 8; s++)
			{
				if (player[i]->property[s] == 3)
					SetMonopoly((card::Type)s, false);
			}
		}
		else
		{
			alive++;
		}
	}
	if (alive == 1)
	{
		//Win stage
	}
	
	if (button.size() > 2)
	button.pop_back();
	
	if (alive > 1)
		{
			do
			{
				currplayer++;
				if (currplayer >= player.size())
					currplayer = 0;

			} while (player[currplayer]->bankrupt);
			plr = player[currplayer];
		}
}
void STGameLoop::CheckCard()
{
	crd = card[plr->position];

	if (crd->GetOwner() == card::Owner::neutral)
	{
		crd->tooldraw = true;
		button.push_back(new Button(
			EngineData::strings[str::str_Buy],
			Vector2f(100,50),
			Vector2f(630,400),
			form::id::buy_card));

		if (plr->money < crd->price)
		{
			button[button.size() - 1]->SetInstance(form::Instance::active);
		}
	}
	else if (crd->GetOwner() == card::Owner::goverment)
	{
		if (crd->name == card::Name::startcard)
		{
			int temp = 0;
			//temp
			for (size_t i = 0; i < plr->prop.size(); i++)
			{
				temp +=plr->prop[i]->profit;
			}
			plr->SetMoney(temp);
		}
	}
	else
	{
		crd->tooldraw = true;
		if (crd->owner != plr->id)
		{
			plr->SetMoney(-crd->profit);
			
			player[crd->GetOwner() - 1]->SetMoney(crd->profit);
			
		}
	}
}
void STGameLoop::Animation(const float & dtime)
{
	animtime += dtime;
	if (animtime > animtimeMax)
	{
		plr->SetPosition(1);
		plr->SetPosition(card[plr->position]->GetPosition());
		
		cubes--;
		if (cubes <= 0)
		{
			animation = false;
			CheckCard();
		}
		animtime = 0;
	}
}
void STGameLoop::SetMonopoly(card::Type type, bool choise)
{
	if (choise == true)
	{
		for (size_t i = 0; i < card.size(); i++)
		{
			if (card[i]->type == type && !card[i]->monopoly)
			{
				card[i]->profit *= 2;
				card[i]->monopoly = true;
				
			}
		}
	}
	else
	{
		for (size_t i = 0; i < card.size(); i++)
		{
			if (card[i]->type == type && card[i]->monopoly)
			{
				card[i]->profit /= 2;
				card[i]->monopoly = false;
				
			}
		}
	}

}
void STGameLoop::SelectCard(Card &card)
{
	if (card.instance == form::Instance::left_click)
	{
		card.card.setFillColor(Color::Yellow);
	}
	if (card.instance == form::Instance::hover)
	{
		
	}
	if (card.instance == form::Instance::idle)
	{
		card.card.setFillColor(Color::White);
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
