#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_scene_director.hpp"
#include "ttt_helpers.hpp"

using namespace std;

// The Main Loop
// =============
//
// > Don't mind me commenting stuffs, coding alone in a confined room
//   can be boring.  - Anonoz
int main()
{
	// Mockup is 800x600, tutorial says 800x600, therefore 800x600
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "TAC TIC TOE!", sf::Style::Titlebar | sf::Style::Close);

	// CPU usage fix and other lovely tweaks
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);

	// Game instance (model in MVC)
	TTT_Instance* instance = new TTT_Instance;

	// Initiate scene director (graphics dpt)
	SceneDirector director(window, instance);

	// Here goes the actual loop
	while (window->isOpen())
	{
		// The obligatory event handler
		sf::Event* event = new sf::Event();
		while (window->pollEvent(*event))
		{
			// KILL!
			if (event->type == sf::Event::Closed)
				window->close();

			// Let scene director delegate event handling to other scenes
			if (director.getCurrentScene() >= 0 and director.getCurrentScene() <= 4)
			{
				director.handle(event);
			}
			else
			{
				window->close();
			}
		}

		// Wipe it as clear as how Mr Yoong does it
		window->clear(sf::Color::White);

		// Let director render
		director.render();

		// Finalise loop
		window->display();

		// Clear event memory
		delete event;

		// Clear console for status reporting
		// system("cls");
	}

	// Anyway if got any port stuff, close them
	instance->stopListeningForClient();
	instance->stopWaitingForNextMove();
	instance->stopConnectingToServer();

	return 0;
}