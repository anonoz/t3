/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

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