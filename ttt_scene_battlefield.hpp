#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_helpers.hpp"

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

		// Visual Elements
		sf::RectangleShape battle_board
			, x_marker
			, o_marker
			, x_active_halo
			, o_active_halo
			, x_hint_halo
			, o_hint_halo;

	public:
		SceneBattlefield(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts);
		void render();
		int handle(sf::Event* xevent);
		int handle_mouse_click(int click_X, int click_y);
};

#endif