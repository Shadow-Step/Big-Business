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
	Text text;
public:
	ToolTip(string str);
	void Update(const float &time);
	inline void Draw(RenderTarget & target) { target.draw(tooltip); target.draw(text); }

	//Setters
	inline void SetString(string str) { this->text.setString(str); }
};