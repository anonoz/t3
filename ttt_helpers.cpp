#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace TTTHelpers
{
	sf::Font* load_font(const std::string& fontFilename)
	{
		sf::Font* font_pointer = new sf::Font();

		if (!font_pointer->loadFromFile(fontFilename))
		{
			exit(1);
		}
		else
		{
			std::cout << fontFilename << " font loaded" << std::endl;
		}

		return font_pointer;
	}

	sf::Texture* load_texture(const std::string& imageFilename)
	{
		sf::Texture* texture = new sf::Texture();

		if (!texture->loadFromFile(imageFilename))
		{
			exit(1);
		}
		else
		{
			std::cout << imageFilename << " texture loaded" << std::endl;
		}

		return texture;
	}

	void set_text_string(sf::Text& myText, const std::string& myString, const std::string& myOriginPositionFlags = "LT")
	{
		myText.setString( myString );
		sf::FloatRect myTextLocalBounds = myText.getLocalBounds();
		float myOriginX = myTextLocalBounds.left;
		float myOriginY = myTextLocalBounds.top;

		if (myOriginPositionFlags[0] == 'C')
		{
			myOriginX += myTextLocalBounds.width / 2.0;
		}
		else if (myOriginPositionFlags[0] == 'R')
		{
			myOriginX += myTextLocalBounds.width;
		}

		if (myOriginPositionFlags[1] == 'C')
		{
			myOriginY += myTextLocalBounds.height / 2.0;
		}
		else if (myOriginPositionFlags[1] == 'B')
		{
			myOriginY += myTextLocalBounds.height;
		}

		myText.setOrigin(myOriginX, myOriginY);
	}
	
	void set_text_string(sf::Text& myText, const std::string& myString)
	{
		set_text_string(myText, myString, "LT");
	}

};
