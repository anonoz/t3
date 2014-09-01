/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_menu.hpp"

SceneMenu::SceneMenu(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts)
{
	std::cout << "Constructing scene_menu" << std::endl;
	window = xwindow;
	ttt_fonts = xttt_fonts;

	// Calculating middle of the screen from RenderWindow size to fit ttt board
	sf::Vector2f window_size_v2f(window->getSize());

	// Prepare texts
	heading1.setFont(*((*ttt_fonts)[2])); std::cout<<"set font"<<std::endl;
	heading1.setColor(sf::Color::Black);
	heading1.setStyle(sf::Text::Regular);
	heading1.setCharacterSize(62); std::cout<<"set char size"<<std::endl;
	heading1.setPosition(186, 78); std::cout<<"set position"<<std::endl;
	TTTHelpers::set_text_string(heading1, "TAC TIC TOE"); std::cout<<"set string cfg"<<std::endl;

	// Shiny new start button
	sf::Texture* start_button_texture = TTTHelpers::load_texture("assets/images/start-button.png");
	sf::Vector2u start_button_texture_size = start_button_texture->getSize();

	start_button.setTexture(start_button_texture);
	start_button.setSize(sf::Vector2f(start_button_texture_size.x, start_button_texture_size.y));
	start_button.setPosition((window_size_v2f.x / 2) - (start_button_texture_size.x / 2), (window_size_v2f.y / 2) - (start_button_texture_size.y / 2) + 140);

	sf::Texture* multiplayer_button_texture = TTTHelpers::load_texture("assets/images/menu-multiplayer-button.png");
	sf::Vector2u multiplayer_button_texture_size = multiplayer_button_texture->getSize();

	multiplayer_button.setTexture(multiplayer_button_texture);
	multiplayer_button.setSize(sf::Vector2f(multiplayer_button_texture_size.x, multiplayer_button_texture_size.y));
	multiplayer_button.setPosition((window_size_v2f.x / 2) - (multiplayer_button_texture_size.x / 2), (window_size_v2f.y / 2) - (multiplayer_button_texture_size.y / 2) + 240);

	// Prepare the mini board
	// sf::Texture* mini_board = TTTHelpers::load_texture("assets/images/mini-board.png");
	sf::Texture* mini_board_texture = TTTHelpers::load_texture("assets/images/mini-board.png");
	sf::Vector2u mini_board_texture_size = mini_board_texture->getSize();

	mini_board.setTexture(mini_board_texture);
	mini_board.setSize(sf::Vector2f(mini_board_texture_size.x, mini_board_texture_size.y));
	mini_board.setPosition((window_size_v2f.x / 2) - (mini_board_texture_size.x / 2), (window_size_v2f.y / 2) - (mini_board_texture_size.y / 2));
	mini_board.setTextureRect( sf::IntRect(0, 0, mini_board_texture->getSize().x, mini_board_texture->getSize().y) );

}

// INSIDE LOOP
void SceneMenu::render()
{
	window->setMouseCursorVisible(true);

	// Draw heading 1
	window->draw(heading1);

	// Draw start
	window->draw(start_button);

	// Draw multi
	window->draw(multiplayer_button);

	// Draw the pale ttt board
	window->draw(mini_board);
}

int SceneMenu::handle(sf::Event* xevent)
{
	int new_scene = 0; // by default dont change new scene, thereby 0
	event = xevent;

	// On menu we need to know when user clicks on the buttons
	switch (xevent->type)
	{
		case sf::Event::MouseButtonReleased:
		{
			new_scene = handle_mouse_click(event->mouseButton.x, event->mouseButton.y);
			std::cout << "Mouse pressed detected at " << event->mouseButton.x << ", " << event->mouseButton.y << std::endl;
			break;
		}
	}

	return new_scene;
}

int SceneMenu::handle_mouse_click(int click_x, int click_y)
{
	// Start button check
	if (start_button.getGlobalBounds().contains(click_x, click_y))
	{
		return 1;
	}

	// Multiplayer
	if (multiplayer_button.getGlobalBounds().contains(click_x, click_y))
	{
		return 2;
	}

	return 0;
}

// Scene changing
