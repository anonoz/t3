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

	// CPU usage fix
	window->setFramerateLimit(60);

	// Initiate scene director (graphics dpt)
	cout << "Invoking scene director... " << endl;
	SceneDirector director(window);
	cout << "Scene director is up" << endl;

	// Here goes the actual loop
	cout << "Starting main loop... " << endl;
	while (window->isOpen())
	{
		// The obligatory event handler
		sf::Event event;
		while (window->pollEvent(event))
		{
			// KILL!
			if (event.type == sf::Event::Closed)
				window->close();

			// Let scene director delegate event handling to other scenes
			if (director.getCurrentScene() >= 0 and director.getCurrentScene() <= 4)
			{
				cout << "Delegating event handling to director... " << endl;
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
		cout << "Calling render... " << endl;
		director.render();
		cout << "Rendering done! " << endl;

		// Finalise loop
		window->display();
	}

	return 0;
}