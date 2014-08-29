#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"
#include "ttt_scene_menu.hpp"

#include "ttt_scene_director.hpp"

SceneDirector::SceneDirector(sf::RenderWindow& xwindow)
{
	window = &xwindow;

	// Load fonts
	sf::Font kenvector_future_thin = TTTHelpers::load_font("assets/fonts/kenvector_future_thin.ttf");
		ttt_fonts.push_back(&kenvector_future_thin);

	// Initiate scenes
	SceneMenu scene_menu_object(*window, ttt_fonts);
	std::cout << "Scene menu created in director... "<< std::endl;
	scene_menu = &scene_menu_object;

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
void SceneDirector::handle(sf::Event& event)
{
	switch (current_scene)
	{
		case 0:
			scene_menu->handle(event);
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