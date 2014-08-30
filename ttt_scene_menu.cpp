#include "ttt_scene_menu.hpp"

SceneMenu::SceneMenu(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts)
{
	std::cout << "Constructing scene_menu" << std::endl;
	window = xwindow;
	ttt_fonts = xttt_fonts;

	// kenvector_future_thin = TTTHelpers::load_font("assets/fonts/kenvector_future_thin.ttf");
	// kenpixel_blocks = TTTHelpers::load_font("assets/fonts/kenpixel_blocks.ttf");

	// Prepare texts
	heading1.setFont(*((*ttt_fonts)[2])); std::cout<<"set font"<<std::endl;
	heading1.setColor(sf::Color::Black);
	heading1.setStyle(sf::Text::Regular);
	heading1.setCharacterSize(62); std::cout<<"set char size"<<std::endl;
	heading1.setPosition(186, 78); std::cout<<"set position"<<std::endl;
	TTTHelpers::set_text_string(heading1, "TAC TIC TOE"); std::cout<<"set string cfg"<<std::endl;

	start_button.setFont(*((*ttt_fonts)[1]));
	start_button.setColor(sf::Color::Black);
	start_button.setStyle(sf::Text::Regular);
	start_button.setCharacterSize(38);
	start_button.setPosition(405, 425);
	TTTHelpers::set_text_string(start_button, "START", "CT");

	// Watch start button


	// Prepare the mini board
	// sf::Texture* mini_board = TTTHelpers::load_texture("assets/images/mini-board.png");
	sf::Texture* mini_board_texture = TTTHelpers::load_texture("assets/images/mini-board.png");
	sf::Vector2u mini_board_texture_size = mini_board_texture->getSize();

	// Calculating middle of the screen from RenderWindow size to fit ttt board
	sf::Vector2f window_size_v2f(window->getSize());

	mini_board.setTexture(mini_board_texture);
	mini_board.setSize(sf::Vector2f(mini_board_texture_size.x, mini_board_texture_size.y));
	mini_board.setPosition((window_size_v2f.x / 2) - (mini_board_texture_size.x / 2), (window_size_v2f.y / 2) - (mini_board_texture_size.y / 2));
	mini_board.setTextureRect( sf::IntRect(0, 0, mini_board_texture->getSize().x, mini_board_texture->getSize().y) );


	std::cout << "Constructed scene_menu" << std::endl;
}

// INSIDE LOOP
void SceneMenu::render()
{
	window->setMouseCursorVisible(true);

	// Draw heading 1
	window->draw(heading1);

	// Draw start
	window->draw(start_button);

	// Draw about

	// Draw the pale ttt board
	window->draw(mini_board);
}

int SceneMenu::handle(sf::Event* xevent)
{
	int new_scene = 0; // by default dont change new scene, thereby 0
	event = xevent;

	std::cout << "Scene Menu is handling event now " << xevent->type << std::endl;

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
		std::cout << "OMG START BUTTON IS CLICKED!!!" << std::endl;
		return 1;
	}

	return 0;
}

// Scene changing
