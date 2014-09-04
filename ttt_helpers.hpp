/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#ifndef TTTHELPERS_HPP
#define TTTHELPERS_HPP

namespace TTTHelpers
{
	sf::Font* 	load_font(const std::string& fontFilename);
	sf::Texture*	load_texture(const std::string& imageFilename);
	sf::SoundBuffer*	load_sound_buffer(const std::string& soundFilename);
	void		set_text_string(sf::Text& myText, const std::string& myString);
	void		set_text_string(sf::Text& myText, const std::string& myString, const std::string& myOriginPositionFlags);
};

#endif