/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

/**
 * Director (Controller)
 * ========
 *
 * - Manage the current scene to show
 * - Delegate event handling job and rendering job
 *     to the correct scene object
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_instance.hpp"
#include "ttt_scene_menu.hpp"
#include "ttt_scene_battlefield.hpp"
#include "ttt_scene_multiplayer.hpp"
#include "ttt_scene_help.hpp"

using namespace std;

#ifndef SCENE_DIRECTOR_HPP
#define SCENE_DIRECTOR_HPP
class SceneDirector
{
	private:
		int current_scene;
		sf::RenderWindow* window;
		sf::Event* event;
		std::vector< sf::Font* > ttt_fonts;

		TTT_Instance* instance;

		SceneMenu*		scene_menu;
		SceneBattlefield* scene_battlefield;
		SceneMultiplayer* scene_multiplayer;
		SceneHelp*		scene_help;

	public:
		SceneDirector(sf::RenderWindow* xwindow, TTT_Instance* xinstance);
		int getCurrentScene();
		void setCurrentScene(int target_current_scene);
		void handle(sf::Event* xevent);
		void render();

};

#endif