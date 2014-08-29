#ifndef SCENE_DIRECTOR_H
#define SCENE_DIRECTOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_scene_menu.hpp"

class SceneDirector
{
	private:
		int current_scene;
		sf::RenderWindow* window;

		SceneMenu		scene_menu;

	public:
		SceneDirector(sf::RenderWindow& xwindow);
		int getCurrentScene();
		void handle(sf::Event& event);
		void render();

};

#endif