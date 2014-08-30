#include "ttt_scene_battlefield.hpp"

SceneBattlefield::SceneBattlefield(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts)
{
	window = xwindow;
	ttt_fonts = xttt_fonts;

	// Some RenderWindow calculations
	sf::Vector2f window_size_v2f(window->getSize());

	// Create board as background
	sf::Texture* battle_board_texture = TTTHelpers::load_texture("assets/images/battle-board.png");
	sf::Vector2u battle_board_texture_size = battle_board_texture->getSize();

	battle_board.setTexture(battle_board_texture);
	battle_board.setSize( sf::Vector2f(battle_board_texture_size.x, battle_board_texture_size.y) );
	battle_board.setPosition( (window_size_v2f.x / 2) - (battle_board_texture_size.x / 2), (window_size_v2f.y / 2) - (battle_board_texture_size.y / 2) );
	battle_board.setTextureRect( sf::IntRect(0, 0, battle_board_texture_size.x, battle_board_texture_size.y) );

	// Create markers

	// Create active halos

	// Create hinting halos
}

int SceneBattlefield::handle(sf::Event* xevent)
{
	int new_scene = 1;
	event = xevent;

	return new_scene;
}

void SceneBattlefield::render()
{
	window->draw( battle_board );
}