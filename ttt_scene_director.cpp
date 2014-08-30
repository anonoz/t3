#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"
#include "ttt_scene_menu.hpp"

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

	// Initiate scenes
	scene_menu = new SceneMenu(window, &ttt_fonts);
	std::cout << "Scene menu created in director... "<< std::endl;

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
	}
}

void SceneDirector::render()
{
	switch (current_scene)
	{
		case 0:
			scene_menu->render();
			break;
	}
}