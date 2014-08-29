#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"
#include "ttt_scene_menu.hpp"

class SceneDirector
{
	private:
		int current_scene;
		sf::RenderWindow* window;
		std::vector< sf::Font* > ttt_fonts;

		SceneMenu* scene_menu;
		// SceneBattlefield 	scene_battlefield;
		// SceneAbout			scene_about;

	public:
		SceneDirector(sf::RenderWindow& xwindow);
		int getCurrentScene();
		void handle(sf::Event& event);
		void render();

};

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
	current_scene = 0;
}

int SceneDirector::getCurrentScene()
{
	return current_scene;
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
			std::cout << "HO" << std::endl;
			scene_menu->render();
			break;
	}
}