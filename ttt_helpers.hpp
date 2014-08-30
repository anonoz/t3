namespace TTTHelpers
{
	sf::Font* 	load_font(const std::string& fontFilename);
	sf::Texture*	load_texture(const std::string& imageFilename);
	void		set_text_string(sf::Text& myText, const std::string& myString);
	void		set_text_string(sf::Text& myText, const std::string& myString, const std::string& myOriginPositionFlags);
};
