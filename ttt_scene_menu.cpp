#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"

class SceneMenu
{
	private:
		sf::RenderWindow* window;
		std::vector< sf::Font* > ttt_fonts;
		sf::Font kenvector_future_thin, kenpixel_blocks;

		// Visual Elements
		sf::Text heading1, start_button, about_button;

	public:
		SceneMenu(sf::RenderWindow& xwindow, std::vector<sf::Font*>& xttt_fonts);
		void render();
		void handle(sf::Event& event);
};

SceneMenu::SceneMenu(sf::RenderWindow& xwindow, std::vector<sf::Font*>& xttt_fonts)
{
	window = &xwindow;
	ttt_fonts = xttt_fonts;

	kenvector_future_thin = TTTHelpers::load_font("assets/fonts/kenvector_future_thin.ttf");
	kenpixel_blocks = TTTHelpers::load_font("assets/fonts/kenpixel_blocks.ttf");

	// Prepare visuals
	heading1.setFont(kenvector_future_thin); std::cout<<"set font"<<std::endl;
	heading1.setColor(sf::Color::Black);
	heading1.setStyle(sf::Text::Regular);
	heading1.setCharacterSize(20); std::cout<<"set char size"<<std::endl;
	heading1.setPosition(100, 100); std::cout<<"set position"<<std::endl;
	TTTHelpers::set_text_string(heading1, "TAC TIC TOE"); std::cout<<"set string cfg"<<std::endl;

	start_button.setFont(kenpixel_blocks);
	start_button.setColor(sf::Color::Black);
	start_button.setStyle(sf::Text::Regular);
	start_button.setCharacterSize(50);
	start_button.setPosition(414, 518);
	TTTHelpers::set_text_string(start_button, "START");
}

// INSIDE LOOP
void SceneMenu::render()
{
	std::cout<<"DRAW"<<std::endl;
	// window->draw(heading1); 

	// Draw start
	// window->draw(start_button);

	// Draw about

	// Draw the pale ttt board
}

void SceneMenu::handle(sf::Event& event)
{
	// On menu we need to know when user clicks on the buttons

}