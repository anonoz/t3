/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

// This scene is only to prompt user for IP address
//   or client to connect in.
// Then it will pass the game back to battlefield and instance
//   but with special mode.

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "ttt_helpers.hpp"
#include "ttt_instance.hpp"

using namespace std;

#ifndef SCENE_MULTIPLAYER_HPP
#define SCENE_MULTIPLAYER_HPP

class SceneMultiplayer
{
	private:
		sf::RenderWindow* window;
		sf::Event* event;
		vector< sf::Font* >* ttt_fonts;
		TTT_Instance* instance;

		sf::IpAddress ip_address;
		string user_input_ip_address;

		int subscene;

		sf::RectangleShape battle_board,
			blue_mat,
			dotted_line,
			connect_button,
			x_button;

		sf::Text heading1,
			key_in_prompt,
			ip_address_textbox,
			give_friend_your_ip,
			your_ip_address,
			s1_waiting;

	public:
		SceneMultiplayer(sf::RenderWindow* xwindow, vector< sf::Font* >* xttt_fonts, TTT_Instance* xinstance);

		void enter();
		void leave();

		void render();

		int handle(sf::Event* event);
		int handle_mouse_click(int click_x, int click_y);
		int handle_keypress(int key);
};

#endif