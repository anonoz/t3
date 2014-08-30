#ifndef SCENE_DIRECTOR_HPP
#define SCENE_DIRECTOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_scene_menu.hpp"
#include "ttt_scene_battlefield.hpp"

class SceneDirector
{
	private:
		int current_scene;
		sf::RenderWindow* window;
		sf::Event* event;
		std::vector< sf::Font* > ttt_fonts;

		SceneMenu*		scene_menu;
		SceneBattlefield* scene_battlefield;

	public:
		SceneDirector(sf::RenderWindow* xwindow);
		int getCurrentScene();
		void setCurrentScene(int target_current_scene);
		void handle(sf::Event* xevent);
		void render();

};

#endif