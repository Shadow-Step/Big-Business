#include "Stage.h"

int STGameLoop::playersN = 4;
int STGameLoop::startMoney = 1200;
bool STGameLoop::gameStarted = false;
Texture Stage::backtexture;

Stage::Stage()
{
	
	this->background.setSize(EngineData::winsize);
	this->background.setTexture(&backtexture);
}
Stage::~Stage()
{
}
void Stage::InitTextures()
{
	Stage::backtexture.loadFromFile("texture/back.jpg");
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
	target.draw(background);
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
	Button::InitTextures();
	Card::InitTextures();
	Card::InitRands();

	turnext.setFont(EngineData::font);
	turnext.setCharacterSize(20);
	turnext.setPosition(600, 580);

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
				EngineData::winsize.y - size.y + pos.y), 0,card::Name::taxcard));
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
				card[15]->GetPosition().y-104), 0, card::Name::startcard));
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
		player.push_back(new Player(card[0]->GetPosition(), startMoney));
		if (i == 0)
		{
			
		}
		if (i == 1)
		{
			player[1]->SetPosition(9);
			player[1]->SetPosition(card[9]->GetPosition());
		}
		if (i == 2)
		{
			player[2]->SetPosition(16);
			player[2]->SetPosition(card[16]->GetPosition());
		}
		if (i == 3)
		{
			player[3]->SetPosition(25);
			player[3]->SetPosition(card[25]->GetPosition());
		}
		player[i]->AI = true;
	}
	player[0]->AI = false;
	

	cardbutt.push_back(new Button(
		"Sell",
		Vector2f(100, 50),
		Vector2f(765, 340),
		form::id::sell_card));
	cardbutt.push_back(new Button(
		"Upgrade",
		Vector2f(150, 50),
		Vector2f(765, 285),
		form::id::upgrade_card));

	plr = player[0];
	gameStarted = true;

	////////////////////////
	
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
	for (size_t i = 0; i < cardbutt.size(); i++)
	{
		delete cardbutt[i];
	}
}
void STGameLoop::Update(const float & dtime)
{
	if (warning == nullptr)
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
			}
			//TEMP!
			if(showcards)
			for (size_t i = 0; i < plr->cards.size(); i++)
			{
				if (viewer > 0)
				{
					plr->cards[viewer - 1]->card.setScale(0.8, 0.8);
					plr->cards[viewer - 1]->card.setPosition(600-5, 490);

					plr->cards[viewer - 1]->info.setCharacterSize(14);
					plr->cards[viewer - 1]->info.setPosition(600 - 25, 490-20);
					
				}

				plr->cards[viewer]->card.setScale(1, 1);
				plr->cards[viewer]->card.setPosition(685-5, 490);

				plr->cards[viewer]->info.setCharacterSize(16);
				plr->cards[viewer]->info.setPosition(685 - 25, 490-20);

				if (viewer < plr->cards.size() - 1)
				{
					plr->cards[viewer + 1]->card.setScale(0.8, 0.8);
					plr->cards[viewer + 1]->card.setPosition(770-5, 490);

					plr->cards[viewer + 1]->info.setCharacterSize(14);
					plr->cards[viewer + 1]->info.setPosition(770 - 25, 490-20);
				}
				
				
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

		//Sell and Upgrade buttons
		if (crd != nullptr && crd->owner == plr->id)
		{
			for (size_t i = 0; i < cardbutt.size(); i++)
			{
				cardbutt[i]->Update(dtime);
				CheckButton(*cardbutt[i]);
			}
		}

		//Check if player -> BOT
		if (plr->AI)
		{
			if (aistage == stg::AIstage::start_turn)
			{
				while (plr->bankrupt && plr->prop.size() > 0)
				{
					plr->SellProperty(plr->prop[0]);
				}

				if (!plr->bankrupt)
				{
					ThrowCubes();
				}
				else
				{
					EndTurn();
				}

			}
			else if (aistage == stg::AIstage::end_turn)
				EndTurn();//
		}
	}
	else
	{
		warning->Update(dtime);
		if (!warning->GetLife())
		{
			if (warning->GetCoise() == true)
			{
				(this->*fooptr)();
			}
			fooptr = nullptr;
			delete warning;
			warning = nullptr;
		}
	}
}
void STGameLoop::Draw(RenderTarget & target)
{
	target.draw(background);

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

	//Draw Sell and Upgrade buttons
	if (crd != nullptr && crd->owner == plr->id)
	{
		for (size_t i = 0; i < cardbutt.size(); i++)
		{
			cardbutt[i]->Draw(target);
		}
	}

	//Turn Text
	target.draw(turnext);

	//TEMP!!!
	if (showcards == true && plr->cards.size()>0)
	{
		if (viewer>0)
		plr->cards[viewer-1]->Draw(target);
		if (viewer < plr->cards.size() - 1)
		plr->cards[viewer+1]->Draw(target);

		plr->cards[viewer]->Draw(target);
	}

	//Warning box draw
	if (warning != nullptr)
		warning->Draw(target);
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
			EndTurn();
			break;
		case form::id::throw_cubes:
			ThrowCubes();

			////temp!!!
			//warning = new WarningBox(Vector2f(200,100),
			//	Vector2f(400,400),"Some text over here");
			//fooptr = &STGameLoop::ThrowCubes;
			////end temp!!!
			break;
		case form::id::buy_card: // Must be deleted!
			if (plr->money > crd->data.price)
			{
				plr->BuyProperty(crd);
				//temp
				delete this->button[this->button.size() - 1];
				this->button.pop_back();
			}
			else
			{
				button.SetInstance(form::Instance::active);
			}
			break;
		case form::id::sell_card:
			plr->SellProperty(crd);
			crd->UpdateText();
			break;
		case form::id::upgrade_card:
			button.SetInstance(form::Instance::hover);
			if (plr->money > crd->data.base_price/2 && crd->data.level < 3)
			{
				plr->UpProperty(crd);
			}
			break;
		}
	}
}
void STGameLoop::CatchEvent(const Event & event)
{
	
	if (EngineData::clicktime > EngineData::clicktimeMax && warning==nullptr)
	{
		if (selector && Mouse::isButtonPressed(Mouse::Left))
		{
			Selector();
		}
		if (selector && Mouse::isButtonPressed(Mouse::Right))
		{
			EngineData::clicktime = 0;
			if (crd != nullptr)
			{
				crd->card.setOutlineThickness(1);
				crd->tooldraw = false;
				crd = nullptr;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			EngineData::clicktime = 0;
			EngineData::msgbox.push_back(MsgBox::stage_switch_mainmenu);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !animation)
		{
			EngineData::clicktime = 0;
			if (FindButton(form::id::end_turn).GetInstance() != form::Instance::active)
			{
				FindButton(form::id::end_turn).SetInstance(form::Instance::active);
				FindButton(form::id::throw_cubes).SetInstance(form::Instance::hover);
				EndTurn();
			}
			else
			{
				if (crd != nullptr)
				{
					crd->card.setOutlineThickness(1);
					crd->tooldraw = false;
					crd = nullptr;
				}
				if (!plr->bankrupt)
				{
					FindButton(form::id::throw_cubes).SetInstance(form::Instance::active);
					FindButton(form::id::end_turn).SetInstance(form::Instance::hover);
					cubes = rand() % 11 + 2;
					DynamicText::SpawnText(to_string(cubes),
						Vector2f(890, 540), Vector2f(0, -1), Color::Blue, 30);

					animation = true;
				}
				else if (plr->bankrupt && plr->prop.size() == 0)
				{
					FindButton(form::id::end_turn).SetInstance(form::Instance::hover);
				}
				else
				{
					DynamicText::SpawnText("Bankrupt!",
						Vector2f(835, 550), Vector2f(0, -1), Color::Red, 22);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			EngineData::clicktime = 0;
			for (size_t i = 0; i < player.size(); i++)
			{
				player[i]->AI = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			player[0]->SetMoney(10000);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			EngineData::clicktime = 0;
			PlaceCard();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && viewer > 0)
		{
			EngineData::clicktime = 0;
			viewer--;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && viewer < plr->cards.size()-1)
		{
			EngineData::clicktime = 0;
			viewer++;
		}
	}
}
void STGameLoop::PlaceCard()
{
	//enum for PlaceCard() only
	enum own
	{
		//Enemy's card
		enem,
		//My card
		mein,
		//Neutral card
		neut,
		//Goverment's card
		gove
	};
	//Get owner of the card in position "x" return local enum "own::"
	auto on = [&](int x)
	{
		if (card[x]->GetOwner() == plr->GetID())
			return own::mein;
		else if (card[x]->GetOwner() == card::Owner::neutral)
			return own::neut;
		else if (card[x]->GetOwner() == card::Owner::goverment)
			return own::gove;
		else
			return own::enem;
	};
	//find selected card in vector<> return index
	auto fcard = [&]() 
	{
		for (size_t i = 0; i < card.size(); i++)
		{
			if (card[i]->GetID() == crd->GetID())
				return i;
		}
	};
	//generate position n.front n.curr n.back
	Pos n = fcard();

	if (plr->cards.size() > 0)
	{
		*crd = *plr->cards[viewer];
			
			//check special before placing//
			if (card[n.back]->special == card::Special::money_aura &&
				on(n.back) == own::mein)
			{
				crd->data.boostProfit(0.50);
				
			}
			if (card[n.front]->special == card::Special::money_aura &&
				on(n.front) == own::mein)
			{
				crd->data.boostProfit(0.50);
				
			}

			if (card[n.back]->special == card::Special::money_curse &&
				on(n.back) == own::enem)
			{
				crd->data.boostProfit(-0.50);
				
			}
			if (card[n.front]->special == card::Special::money_curse &&
				on(n.front) == own::enem)
			{
				crd->data.boostProfit(-0.50);
				
			}

			crd->UpdateText();
			//END check special before placing//

		plr->cards.erase(plr->cards.begin() + viewer);
		plr->BuyProperty(crd);
		if (viewer>0)
			viewer--;

		//Use special after placing//
		switch (crd->special)
		{
		case card::Special::money_aura:
			if (on(n.front) == own::mein)
			{
				card[n.front]->data.boostProfit(0.50);
				card[n.front]->UpdateText();
				card[n.front]->card.setFillColor(Color::Cyan);
			}
			if (on(n.back) == own::mein)
			{
				card[n.back]->data.boostProfit(0.50);
				card[n.back]->UpdateText();
				card[n.back]->card.setFillColor(Color::Cyan);
			}
			break;
		case card::Special::money_curse:
			if (on(n.front) == own::enem)
			{
				card[n.front]->data.boostProfit(-0.50);
				card[n.front]->UpdateText();
				card[n.front]->card.setFillColor(Color::Black);
			}
			if (on(n.back) == own::enem)
			{
				card[n.back]->data.boostProfit(-0.50);
				card[n.back]->UpdateText();
				card[n.back]->card.setFillColor(Color::Black);
			}
			break;
		case card::Special::clone:
			if (on(n.back) == own::neut)
			{
				*card[n.back] = *crd;
				Card::ID++;
				card[n.back]->id = Card::ID;
				plr->SetMoney(card[n.back]->data.price);
				plr->BuyProperty(card[n.back]);
				card[n.back]->UpdateText();
			}
			break;
		default:
			break;
		}
	}
}
void STGameLoop::ClearCrd()
{
	if (crd != nullptr)
	{
		crd->tooldraw = false;
		Player::lot = nullptr;
		crd = nullptr;
	}
}
void STGameLoop::EndTurn()
{
	//Switch buttons instances
	FindButton(form::id::throw_cubes).SetInstance(form::Instance::hover);
	FindButton(form::id::end_turn).SetInstance(form::Instance::active);

	//Clear crd
	ClearCrd();

	selector = true;
	showcards = false;

	//Check dead players
	for (size_t i = 0; i < player.size(); i++)
	{
		if (player[i]->money <= 0 && player[i]->prop.size()==0)
		{
			for (size_t c = 0; c < card.size(); c++)
			{
				if (card[c]->owner == player[i]->id)
					card[c]->SetOwner(card::Owner::neutral);
			}
			delete player[i];
			player.erase(player.begin() + i);
			currplayer--;
		}
	}
	
	//Delete Buy button
	if (button.size() > 2)
	button.pop_back();
	
	//Select player
	if (player.size() > 0)
	{
		bool select = false;
		while (!select)
		{
			currplayer++;
			if (currplayer >= player.size())
				currplayer = 0;
			if (player[currplayer]->inprison == true)
			{
				player[currplayer]->inprison = false;
			}
			else
			{
				plr = player[currplayer];
				select = true;
				turnext.setString("Player: " + to_string(plr->id) + " turn");
				switch (plr->id)
				{
				case 1:
					turnext.setFillColor(Color::Red);
					break;
				case 2:
					turnext.setFillColor(Color::Blue);
					break;
				case 3:
					turnext.setFillColor(Color::Green);
					break;
				case 4:
					turnext.setFillColor(Color::Magenta);
					break;
				}
			}
		}
	}

	//Switch AI stage
	aistage = stg::AIstage::start_turn;
}
void STGameLoop::CheckCard()
{
	if(crd->owner == card::Owner::neutral)
		showcards = true;

	//Check Type6 card
	auto pos = [=](int pos,int dir)
	{
		if (pos + dir == card.size())
		{
			return 0;
		}
		else if (pos + dir < 0)
			return (int)card.size() - 1;
		else
			return pos + dir;
	};
	auto own = [&](int id)
	{
		for (size_t i = 0; i < player.size(); i++)
		{
			if (player[i]->GetID() == id)
				return i;
		}
	};
	if (card[plr->pos.front]->type == card::Type::type6 &&
		card[plr->pos.front]->owner != card::Owner::neutral &&
		card[plr->pos.front]->owner != plr->GetID())
	{
		plr->SetMoney(-card[plr->pos.front]->data.profit / 3);
		player[own(card[plr->pos.front]->owner)]->SetMoney(card[plr->pos.front]->data.profit / 3);
	}
	else if (card[plr->pos.back]->type == card::Type::type6 &&
		card[plr->pos.back]->owner != card::Owner::neutral &&
		card[plr->pos.back]->owner != plr->GetID())
	{
		plr->SetMoney(-card[plr->pos.back]->data.profit / 3);
		player[own(card[plr->pos.back]->owner)]->SetMoney(card[plr->pos.back]->data.profit / 3);
	}
	//End Check Type6 card

	//Check Type7 card
	if (crd->type == card::Type::type7 && crd->owner != card::Owner::neutral)
	{
		crd->data.incProfitMod(10);
		crd->UpdateText();
	}
	//End Check Type7 card

		if (crd->GetOwner() == card::Owner::neutral)
		{
			Player::StartAuction(crd);
			crd->tooldraw = true;

			//AI
			if(plr->money>crd->data.price && plr->AI)
			plr->BuyProperty(crd);//

			/*button.push_back(new Button(
				EngineData::strings[str::str_Buy],
				Vector2f(100,50),
				Vector2f(630,400),
				form::id::buy_card));
			if (plr->money <= crd->price)
			{
				button[button.size() - 1]->SetInstance(form::Instance::active);
			}*/
		}
		else if (crd->GetOwner() == card::Owner::goverment)
		{
			if (crd->name == card::Name::startcard)
			{
				int temp = 0;
				//temp
				for (size_t i = 0; i < plr->prop.size(); i++)
				{
					temp += plr->prop[i]->data.profit/2;
				}
				plr->SetMoney(temp);
			}
			else if (crd->name == card::Name::taxcard)
			{
				int temp = 0;
				//temp
				for (size_t i = 0; i < plr->prop.size(); i++)
				{
					temp += plr->prop[i]->data.price / 10;
				}
				plr->SetMoney(-temp);
			}
			else if (crd->name == card::Name::prisoncard)
			{
				plr->inprison = true;
				DynamicText::SpawnText("Prison!",
					Vector2f(630, 500), Vector2f(0, -1), Color::Red, 22);
			}
			//else if (crd->name == card::Name::bonuscard)
			//{
			//	vector<int>index;
			//	crd->tooldraw = true;
			//	switch (rand() % 4)
			//	{
			//	case 0:
			//		delete crd->tooltip;
			//		crd->tooltip = new ToolTip("Gain 500");
			//		plr->SetMoney(500);
			//		break;
			//	case 1:
			//		/*delete crd->tooltip;
			//		crd->tooltip = new ToolTip("Get random propety");
			//			for (size_t i = 0; i < card.size(); i++)
			//			{
			//				if (card[i]->GetOwner() == card::Owner::neutral)
			//					index.push_back(i);
			//			}
			//			if (index.size() > 0)
			//			{
			//				int in = index[rand() % index.size()];
			//				plr->SetMoney(card[in]->price);
			//				plr->BuyProperty(card[in]);
			//			}*/
			//		break;
			//	case 2:
			//		delete crd->tooltip;
			//		crd->tooltip = new ToolTip("Taxes -200");
			//		plr->SetMoney(-200);
			//		break;
			//	case 3:
			//		
			//		break;
			//	}
			//}

		}
		else
		{
			crd->tooldraw = true;
			if (crd->owner != plr->id)
			{
				//Card Type Check
				if (crd->type == card::Type::type4)
				{
					plr->credit = true;
					plr->credit_count = crd->data.profit / 2;
				}
				//End Card Type Check

				if (!player[own(crd->owner)]->inprison)
				{
					//Card Type Check
					if (plr->protection == false)
					{
						plr->SetMoney(-crd->data.profit);
						player[own(crd->owner)]->SetMoney(crd->data.profit);
					}
					else if (plr->protection == true)
					{
						plr->SetMoney(-crd->data.profit/2);
						player[own(crd->owner)]->SetMoney(crd->data.profit/2);
						plr->protection = false;
					}
					//End Card Type Check
				}

			}
			else if (crd->owner == plr->id)
			{
				//Card Type Check
				if(crd->type == card::Type::type3)
				plr->SetMoney(crd->data.profit / 3);
				if (crd->type == card::Type::type5)
					plr->protection = true;
				//End Card Type Check

				//AI
				if (plr->AI && plr->money >= (crd->data.price * 2) && crd->data.level < 3)
				{
					plr->UpProperty(crd);
				}
			}

		}

		aistage = stg::AIstage::end_turn;


}
void STGameLoop::Animation(const float & dtime)
{
	animtime += dtime;
	if (animtime > animtimeMax)
	{
		plr->pos++;
		plr->SetPosition(card[plr->pos.curr]->GetPosition());
		cubes--;

		//Card Type Check
		if (card[plr->pos.curr]->owner == plr->id && 
			card[plr->pos.curr]->type == card::Type::type2 &&
			cubes != 0)
			plr->SetMoney(card[plr->pos.curr]->data.profit / 10);
		//End Card Type Check

		if (cubes <= 0)
		{
			animation = false;
			selector = false;
			crd = card[plr->pos.curr];
			aistage = stg::AIstage::check_card;
			CheckCard();
		}
		animtime = 0;
	}
}
void STGameLoop::Selector()
{
	for (size_t i = 0; i < card.size(); i++)
	{
		if (card[i]->card.getGlobalBounds().contains(EngineData::mousepos))
		{
			//Clear crd
			ClearCrd();

			//Select card
			crd = card[i];
			crd->card.setOutlineThickness(3);
			crd->tooldraw = true;
			return;///!!!
		}
	}
}
void STGameLoop::ThrowCubes()
{
	//Switch AI stage
	aistage = stg::AIstage::throw_cubes;

	if (!plr->bankrupt)
	{
		//Clear crd
		ClearCrd();
		
		//Switch buttons instances
		FindButton(form::id::throw_cubes).SetInstance(form::Instance::active);
		FindButton(form::id::end_turn).SetInstance(form::Instance::hover);

		//Get rand cubes
		cubes = rand() % 11 + 2;

		//Spawn cubes text
		DynamicText::SpawnText(to_string(cubes),
			Vector2f(890, 540), Vector2f(0, -1), Color::Blue, 30);

		//Start animation
		animation = true;

		//Card Type Check
		if (plr->credit == true)
		{
			plr->SetMoney(-plr->credit_count);
			plr->credit = false;
		}
		//End Card Type Check
	}
	else if (plr->bankrupt && plr->prop.size()==0)
	{
		//Bankrupt -> delete player in EndTurn()
		EndTurn();
	}
	else
	{
		//Spawn message
		DynamicText::SpawnText("Bankrupt!",
			Vector2f(835, 550), Vector2f(0, -1), Color::Red, 22);
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

	button.push_back(new Button("1",
		tempsize,
		Vector2f(pos.x, pos.y),
		form::id::ng_players_01));
	button[button.size() - 1]->SetInstance(form::Instance::active);

	button.push_back(new Button("1200",
		tempsize,
		Vector2f(pos.x, pos.y+55),
		form::id::ng_startmoney_01));
	button[button.size() - 1]->SetInstance(form::Instance::active);


	x++;
	button.push_back(new Button("2",
		tempsize,
		Vector2f(pos.x+(tempsize.x*x)+space*x, pos.y),
		form::id::ng_players_02));

	button.push_back(new Button("2400",
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y+55),
		form::id::ng_startmoney_02));
	x++;
	button.push_back(new Button("3",
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y),
		form::id::ng_players_03));
	button.push_back(new Button("3600",
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y+55),
		form::id::ng_startmoney_03));
	x++;
	button.push_back(new Button("4",
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y),
		form::id::ng_players_04));
	button.push_back(new Button("4800",
		tempsize,
		Vector2f(pos.x + (tempsize.x*x) + space * x, pos.y+55),
		form::id::ng_startmoney_04));
	
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
	target.draw(background);
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
		button.SetColor(Color::Blue);
	else if (button.GetInstance() == form::Instance::hover)
		button.SetColor(Color::Red);
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
			///////////////////////////////////////////
		case form::id::ng_startmoney_01:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::startMoney = 1200;
			break;
		case form::id::ng_startmoney_02:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::startMoney = 2400;
			break;
		case form::id::ng_startmoney_03:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::startMoney = 3600;
			break;
		case form::id::ng_startmoney_04:
			DeactSameButtons(button.GetID());
			button.SetInstance(form::Instance::active);
			STGameLoop::startMoney = 4800;
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
		if (id >= 16 && id <= 19)
		{
			if (button[i]->GetID() == form::id::ng_players_01 ||
				button[i]->GetID() == form::id::ng_players_02 ||
				button[i]->GetID() == form::id::ng_players_03 ||
				button[i]->GetID() == form::id::ng_players_04)
				button[i]->SetInstance(form::Instance::idle);
		}
		else
		{
			if (button[i]->GetID() == form::id::ng_startmoney_01 ||
				button[i]->GetID() == form::id::ng_startmoney_02 ||
				button[i]->GetID() == form::id::ng_startmoney_03 ||
				button[i]->GetID() == form::id::ng_startmoney_04)
				button[i]->SetInstance(form::Instance::idle);
		}
	}

}
