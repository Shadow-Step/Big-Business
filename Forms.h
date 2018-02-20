#include "EngineData.h"
#pragma once

namespace form
{
	enum id
	{
		continue_gameloop,
		new_game,
		load_game,
		options,
		exit,
		back,
		launch,
		yes,
		no,
		end_turn,
		throw_cubes,
		buy_card,
		sell_card,
		upgrade_card,
		plus,
		minus,

		ng_players_01,
		ng_players_02,
		ng_players_03,
		ng_players_04,
		ng_startmoney_01,
		ng_startmoney_02,
		ng_startmoney_03,
		ng_startmoney_04
	};
	enum Instance
	{
		idle,
		hover,
		left_click,
		right_click,
		active
	};
}

class Forms // temp
{
public:
	Forms();
	virtual ~Forms();
};
class Button : public Forms
{
private:
	RectangleShape button;
	static Texture buttontexture;
	Text buttontext;
	
	form::id ID;
	form::Instance instance;

	bool texton = false;

	//Functions
	void ResetTextPosition();
public:
	Button(Vector2f size, Vector2f position,form::id ID);
	Button(string str, Vector2f size, Vector2f position, form::id ID);

	//Functions
	void Update(const float &dtime);
	void Draw(RenderTarget &target);
	static void InitTextures();
	//Getters
	inline const form::id GetID()const { return this->ID; }
	inline const form::Instance GetInstance()const { return this->instance; }
	//Setters
	inline void SetColor(Color color) { this->button.setFillColor(color); }
	inline void SetInstance(form::Instance instance) { this->instance = instance; }
	inline void TextSetColor(Color color) { this->buttontext.setFillColor(color); }
	inline void TextSetString(string str) { this->buttontext.setString(str); ResetTextPosition(); }
};
class Label : public Forms
{
public:

};
class ToolTip : Forms
{
private:
	RectangleShape tooltip;
	Texture tooltex;
	Text text;
public:
	ToolTip(string str);
	ToolTip(string str,Texture &texture, Vector2f position = Vector2f(600,150));
	//Functions
	void Update(const float &time);
	inline void Draw(RenderTarget & target) { target.draw(tooltip); target.draw(text); }
	//Setters
	inline void SetString(string str) { this->text.setString(str); }
	inline void SetTexture(Texture texture) { this->tooltip.setTexture(&texture); }
};
class DynamicText : public Forms
{
private:
	Text text;
	Font font;

	Vector2f direction;
	Color color;

	float lifetime;
	float lifetimeMax;
	float speed;
	float slowdown;
	float hidingtime;
	float transparent;
	bool alive;

public:
	//Constructor
	DynamicText(std::string text,
		Vector2f position,
		Vector2f direction,
		Color color,
		int size,
		float speed,
		float slowdown,
		float lifetime,
		float hidingtime);

	//Getters
	inline const bool IsAlive()const { return this->alive; }

	//Funtions
	void Update(const float &time);
	void Draw(RenderTarget &target);
	static void SpawnText(string str,Vector2f position, Vector2f direction);
	static void SpawnText(string str, Vector2f position, Vector2f direction,Color color,int size = 18);
	
	//Static
	static vector <DynamicText*> dyntext;
	virtual ~DynamicText();
};
class WarningBox : public Forms
{
private:
	RectangleShape board;
	Text text;
	vector<Button*>button;
	

	bool life = true;
	bool choise = false;
public:
	WarningBox(Vector2f size, Vector2f position, string text);
	~WarningBox();

	void Update(const float &dtime);
	void Draw(RenderTarget & target);
	void CheckButtons(Button & button);

	inline const bool GetLife()const { return this->life; }
	inline const bool GetCoise()const { return this->choise; }
};