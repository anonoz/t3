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

#include "ttt_helpers.hpp"

using namespace std;

#ifndef SCENE_HELP_HPP
#define SCENE_HELP_HPP

class SceneHelp
{
	private:
		// Gamewide
		sf::RenderWindow* window;
		sf::Event* event;
		std::vector< sf::Font* >* ttt_fonts;

		// Some Textures meant to be available class-wide
		sf::Texture* quit_button_normal_texture;
		sf::Texture* quit_button_hover_texture;

		// Visual Elements
		sf::RectangleShape page1,
			page2,
			page3,
			page4,
			page5,
			quit_button,
			prev_page,
			next_page,
			ok_button;

		// State control
		int current_page;

	public:
		SceneHelp(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts);

		void render();

		int handle(sf::Event* xevent);

		int handleMouseOver();
		int handleMouseClick();
		int handleKeyPress(int);

		void nextPage();
		void prevPage();
};

#endif