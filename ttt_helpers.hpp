#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>


namespace TTTHelpers
{
	sf::Font* 	load_font(const std::string& fontFilename);
	sf::Texture*	load_texture(const std::string& imageFilename);
	sf::SoundBuffer*	load_sound_buffer(const std::string& soundFilename);
	void		set_text_string(sf::Text& myText, const std::string& myString);
	void		set_text_string(sf::Text& myText, const std::string& myString, const std::string& myOriginPositionFlags);
};
