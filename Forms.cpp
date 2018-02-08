#include "Forms.h"



Forms::Forms()
{
}
Forms::~Forms()
{
}

Button::Button(Vector2f size, Vector2f position, form::id ID)
{
	this->button.setSize(size);
	this->button.setPosition(position);
	this->ID = ID;
}
Button::Button(string str, Vector2f size, Vector2f position,form::id ID)
{
	this->button.setSize(size);
	this->button.setPosition(position);
	this->ID = ID;

	this->buttontext.setFont(EngineData::font);
	this->buttontext.setCharacterSize(30);
	this->buttontext.setString(str);
	this->buttontext.setFillColor(Color::Green);
	ResetTextPosition();
	
	this->texton = true;
}
void Button::Update(const float & dtime)
{
	if (instance != form::Instance::active)//temp
	{
		if (!button.getGlobalBounds().contains(EngineData::mousepos))
			this->instance = form::Instance::idle;
		else if (button.getGlobalBounds().contains(EngineData::mousepos))
			this->instance = form::Instance::hover;
	}

	if (this->instance == form::Instance::hover &&
		Mouse::isButtonPressed(Mouse::Left) &&
		EngineData::clicktime > EngineData::clicktimeMax)
	{
		this->instance = form::Instance::left_click;
		EngineData::clicktime = 0;
	}
	else if (this->instance == form::Instance::hover &&
		Mouse::isButtonPressed(Mouse::Right))
		this->instance = form::Instance::right_click;
	
}
void Button::Draw(RenderTarget & target)
{
	target.draw(button);
	if(texton)
	target.draw(buttontext);
}
void Button::ResetTextPosition()
{
	this->buttontext.setOrigin(0, 2 + (this->buttontext.getCharacterSize() - this->buttontext.getLocalBounds().height));
	this->buttontext.setPosition(this->button.getPosition().x + (this->button.getGlobalBounds().width - this->buttontext.getGlobalBounds().width) / 2,
		this->button.getPosition().y + (this->button.getGlobalBounds().height - this->buttontext.getGlobalBounds().height) / 2);
}