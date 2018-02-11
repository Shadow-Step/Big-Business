#include "Forms.h"
vector<DynamicText*> DynamicText::dyntext;


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

ToolTip::ToolTip(string str)
{
	tooltip.setSize(Vector2f(160, 240));
	tooltip.setPosition(600, 150);
	tooltip.setFillColor(Color::White);

	text.setFont(EngineData::font);
	text.setCharacterSize(18);
	text.setString(str);
	text.setFillColor(Color(136, 136, 136));
	text.setPosition(625, 280);
}
void ToolTip::Update(const float & time)
{
}


DynamicText::DynamicText(std::string text,
	Vector2f position,
	Vector2f direction,
	Color color,
	int size,
	float speed,
	float slowdown,
	float lifetime,
	float hidingtime)
{
	this->color = color;
	this->transparent = 255;

	this->text.setFont(EngineData::font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(this->color);
	this->text.setPosition(position);


	this->direction = direction;
	this->lifetimeMax = lifetime;
	this->lifetime = 0;
	this->hidingtime = hidingtime;
	this->speed = speed;
	this->slowdown = slowdown;
	this->alive = true;
}

DynamicText::~DynamicText()
{
}

void DynamicText::Update(const float &time)
{

	if (this->lifetime < this->lifetimeMax)
		this->lifetime += time;

	if (speed>0)
		speed -= slowdown * time;
	if (speed <= 0)
		speed = 0;
	if (this->lifetime > lifetimeMax - hidingtime)
	{
		if (transparent > 0)
			transparent -= (255 / hidingtime)*time;
		if (transparent <= 0)
			transparent = 0;

		color.a = transparent;
		text.setFillColor(color);
	}
	if (this->lifetime < this->lifetimeMax)
	{
		text.move(direction.x*speed*time, (direction.y*speed)*time);
	}
	else
	{
		alive = false;
	}
}

void DynamicText::Draw(RenderTarget &target)
{
	target.draw(this->text);
}

void DynamicText::SpawnText(string str, Vector2f position, Vector2f direction)
{
	DynamicText::dyntext.push_back(new DynamicText(str,
		position,
		direction,
		Color::Cyan,
		18,
		150.f,
		300.f,
		1.f,
		0.5));
}

void DynamicText::SpawnText(string str, Vector2f position, Vector2f direction,Color color)
{
	DynamicText::dyntext.push_back(new DynamicText(str,
		position,
		direction,
		color,
		18,
		150.f,
		300.f,
		1.f,
		0.5));
}
