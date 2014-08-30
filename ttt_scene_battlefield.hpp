#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_helpers.hpp"
#include "ttt_instance.hpp"

using namespace std;

#ifndef TTT_SCENE_BATTLEFIED_HPP
#define TTT_SCENE_BATTLEFIED_HPP

class SceneBattlefield
{
	private:
		// Gamewide
		sf::RenderWindow* window;
		sf::Event* event;
		std::vector< sf::Font* >* ttt_fonts;

		// Instance initiation
		TTT_Instance* instance;

		// Visual Elements
		sf::Texture* x_marker_texture,
			*o_marker_texture,
			*x_marker_inactive_texture,
			*o_marker_inactive_texture;

		sf::Text x_winner_notice,
			o_winner_notice,
			play_again;

		sf::RectangleShape battle_board
			, x_marker
			, o_marker
			, x_active_halo
			, o_active_halo
			, x_hint_halo
			, o_hint_halo
			, mouse_cursor
			, x_winner_mat
			, o_winner_mat
			, winner_mat_playagain_button;

	public:
		SceneBattlefield(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts);
		void render();
		int handle(sf::Event* xevent);
		int handle_mouse_click(int click_X, int click_y);

		sf::Vector2f getGridCoordinates(int board_id, int grid_id);
		sf::Vector2f getBoardHaloCoorginates(int board_id);
		std::vector<int> getGridHit(const sf::Vector2f& mouse_coords);
};

#endif