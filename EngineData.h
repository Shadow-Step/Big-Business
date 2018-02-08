#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;


enum MsgBox
{
	stage_switch_newgame,
	stage_switch_loadgame,
	stage_switch_options,
	stage_switch_mainmenu,
	stage_switch_gameloop,
	stage_clear_gameloop,

	window_action_close,
	window_action_fullscreen
};
namespace str
{
	enum Strings
	{
		str_NewGame,
		str_Continue,
		str_LoadGame,
		str_Options,
		str_Exit,
		str_Back,
		str_Start,
		str_Yes,
		str_No,
		str_EndTurn,
		str_ThrowCubes,
		str_Buy
	};
}
class EngineData
{
public:
	//Functions
	static void InitFont();
	static void InitStrings();
	
	//Statics
	static float clicktime;
	static float clicktimeMax;

	static Font font;
	static Vector2f winsize;
	static Vector2f mousepos;

	static vector<MsgBox>msgbox;
	static vector<string>strings;
};

class Cursor
{
private:
	static Texture texture;
	static Sprite cursor;
public:
	static void InitCursor();
	static inline void Update(const float &dtime) { Cursor::cursor.setPosition(EngineData::mousepos); }
	static inline void Draw(RenderTarget &target) { target.draw(Cursor::cursor); }
};