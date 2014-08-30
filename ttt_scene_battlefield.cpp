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

	// Create marker textures and rectangle
	sf::Texture* x_marker_texture = TTTHelpers::load_texture("assets/images/x-marker.png");
	sf::Vector2u x_marker_texture_size = x_marker_texture->getSize();

	x_marker.setTexture(x_marker_texture);
	x_marker.setSize( sf::Vector2f(x_marker_texture_size.x, x_marker_texture_size.y) );
	x_marker.setTextureRect( sf::IntRect(0, 0, x_marker_texture_size.x, x_marker_texture_size.y) );

		//testing
		x_marker.setPosition(getGridCoordinates(3,3));

	sf::Texture* o_marker_texture = TTTHelpers::load_texture("assets/images/o-marker.png");
	sf::Vector2u o_marker_texture_size = o_marker_texture->getSize();

	o_marker.setTexture(o_marker_texture);
	o_marker.setSize( sf::Vector2f(o_marker_texture_size.x, o_marker_texture_size.y) );
	o_marker.setTextureRect( sf::IntRect(0, 0, o_marker_texture_size.x, o_marker_texture_size.y) );

	// Create mouse cursors

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
	// Draw mainboard
	window->draw( battle_board );

	window->draw(x_marker);
}

sf::Vector2f SceneBattlefield::getGridCoordinates(int board_id, int grid_id)
{
	// sf::Vector2u coordinates;

	// Board level
	float top_left_x = 150;
	float top_left_y = 40;

	int delta_board_x = 173;
	int delta_board_y = 183;

	// Grid level
	int top_left_grid_x = 25;
	int top_left_grid_y = 25;

	int delta_grid_x = 50;
	int delta_grid_y = 50;

	// Calculate X at board level (translation of coords inside battlefield)
	if (board_id % 3 > 0) top_left_x += delta_board_x;
	if (board_id % 3 > 1) top_left_x += delta_board_x;

	// Board Y at board level
	if (board_id >= 3) top_left_y += delta_board_y;
	if (board_id >= 6) top_left_y += delta_board_y;

	// X at grid level (translation of coords inside a board)
	if (grid_id % 3 > 0) top_left_x += delta_grid_x;
	if (grid_id % 3 > 1) top_left_x += delta_grid_x;

	// Y at grid level
	if (board_id >= 3) top_left_y += delta_grid_y;
	if (board_id >= 6) top_left_y += delta_grid_y;

	return sf::Vector2f(top_left_x, top_left_y);
}