#include "EngineData.h"

Font EngineData::font;

Sprite Cursor::cursor;
Texture Cursor::texture;

	Vector2f EngineData::winsize;
	Vector2f EngineData::mousepos;


vector<string>EngineData::strings;
vector<MsgBox>EngineData::msgbox;

	float EngineData::clicktime = 0;
	float EngineData::clicktimeMax = 0.2;

void EngineData::InitFont()
{
	EngineData::font.loadFromFile("font/ben_krush.ttf");
}
void EngineData::InitStrings()
{
	//Temp!!!
	EngineData::strings.push_back("New Game");
	EngineData::strings.push_back("Continue");
	EngineData::strings.push_back("Load Game");
	EngineData::strings.push_back("Options");
	EngineData::strings.push_back("Exit");
	EngineData::strings.push_back("Back");
	EngineData::strings.push_back("Start");
	EngineData::strings.push_back("Yes");
	EngineData::strings.push_back("No");
	//End temp!!!
}
void Cursor::InitCursor()
{
	//temp
	Vector2f size(58, 58);
	Cursor::texture.loadFromFile("texture/cursor.png");
	Cursor::cursor.setTexture(Cursor::texture);
	Cursor::cursor.setTextureRect(IntRect(3, 3, size.x, size.y));
	Cursor::cursor.setOrigin(size.x/2,size.y/2);
	Cursor::cursor.setScale(0.3, 0.3);
	//end temp
}
