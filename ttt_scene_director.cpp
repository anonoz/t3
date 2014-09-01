/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"
#include "ttt_scene_menu.hpp"
#include "ttt_scene_battlefield.hpp"

#include "ttt_scene_director.hpp"

SceneDirector::SceneDirector(sf::RenderWindow* xwindow)
{
	window = xwindow;

	// Load fonts
	sf::Font* kenvector_future_thin = TTTHelpers::load_font("assets/fonts/kenvector_future_thin.ttf");
		ttt_fonts.push_back(kenvector_future_thin);

	sf::Font* kenpixel_blocks = TTTHelpers::load_font("assets/fonts/kenpixel_blocks.ttf");
		ttt_fonts.push_back(kenpixel_blocks);

	sf::Font* kenpixel_square = TTTHelpers::load_font("assets/fonts/kenpixel_square.ttf");
		ttt_fonts.push_back(kenpixel_square);

	sf::Font* kenpixel = TTTHelpers::load_font("assets/fonts/kenpixel.ttf");
		ttt_fonts.push_back(kenpixel);

	sf::Font* kenvector_future = TTTHelpers::load_font("assets/fonts/kenvector_future.ttf");
		ttt_fonts.push_back(kenvector_future);

	// Game instance should be controlled from here
	instance = new TTT_Instance();

	// Initiate scenes
	scene_menu = new SceneMenu(window, &ttt_fonts);
	std::cout << "Scene menu created in director... "<< std::endl;

	scene_battlefield = new SceneBattlefield(window, &ttt_fonts, instance);
	std::cout << "Scene battlefield created in director... " << std::endl;

	scene_multiplayer = new SceneMultiplayer(window, &ttt_fonts, instance);

	// Set graphics state
	setCurrentScene(0);

	std::cout << "Finished constructing director!" << std::endl;
}

int SceneDirector::getCurrentScene()
{
	return current_scene;
}

void SceneDirector::setCurrentScene(int target_current_scene)
{
	if (target_current_scene < 0 || target_current_scene > 4)
		return;

	// Some scenes would like to be... entered
	if (target_current_scene == 2) scene_multiplayer->enter();

	current_scene = target_current_scene;
	return;
}

// INSIDE LOOP
void SceneDirector::handle(sf::Event* xevent)
{
	switch (current_scene)
	{
		case 0:
			setCurrentScene(scene_menu->handle(xevent));
			break;
		case 1:
			setCurrentScene(scene_battlefield->handle(xevent));
			break;
		case 2:
			setCurrentScene(scene_multiplayer->handle(xevent));
			break;
	}
}

void SceneDirector::render()
{
	switch (current_scene)
	{
		case 0:
			scene_menu->render();
			break;
		case 1:
			scene_battlefield->render();
			break;
		case 2:
			scene_multiplayer->render();
			break;
	}
}