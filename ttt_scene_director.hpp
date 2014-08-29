#ifndef SCENE_DIRECTOR_HPP
#define SCENE_DIRECTOR_HPP

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
		std::vector< sf::Font* > ttt_fonts;

		SceneMenu*		scene_menu;

	public:
		SceneDirector(sf::RenderWindow* xwindow);
		int getCurrentScene();
		void setCurrentScene(int target_current_scene);
		void handle(sf::Event& event);
		void render();

};

#endif