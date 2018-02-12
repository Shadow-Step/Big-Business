#include "Engine.h"
#include <time.h>
//ToDo resize window and reset position for all forms
//All stages

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(VideoMode::getDesktopMode(), "Big Business");
	EngineData::winsize = (Vector2f)window.getSize();
	Engine engine(&window);
	


	Clock timer;
	float dtime = 0;

	while (window.isOpen())
	{
		dtime = timer.restart().asSeconds();

		EngineData::mousepos = (Vector2f)Mouse::getPosition(window);
		if(EngineData::clicktime<EngineData::clicktimeMax)
		EngineData::clicktime += dtime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			engine.CatchEvent(event, dtime);//temp

			if (event.type == sf::Event::Closed)
				window.close();
		}
		engine.Update(dtime);//temp

		window.clear();

		engine.Draw(window);//temp
		
		window.display();
	}

	return 0;
}