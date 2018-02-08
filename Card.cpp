#include "Card.h"
int Card::ID;
vector<Texture>Card::texture;

Card::Card()
{
	this->card.setSize(Vector2f(100, 160));	
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);
	
	Card::ID++;
}
Card::Card(Vector2f position)
{
	this->card.setPosition(position);
	this->card.setSize(Vector2f(80, 120));
	this->card.setOutlineThickness(1);
	this->card.setOutlineColor(Color::Cyan);
}
Card::~Card()
{
}

void Card::Update(const float & dtime)
{
}
void Card::Draw(RenderTarget & target)
{
	target.draw(this->card);
}
void Card::InitTextures()
{
}
