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

	// Create the battlefield background
	sf::Texture* battle_board_texture = TTTHelpers::load_texture("assets/images/battle-board.png");
	sf::Vector2u battle_board_texture_size = battle_board_texture->getSize();

	battle_board.setTexture(battle_board_texture);
	battle_board.setSize( sf::Vector2f(battle_board_texture_size.x, battle_board_texture_size.y) );
	battle_board.setPosition( (window_size_v2f.x / 2) - (battle_board_texture_size.x / 2), (window_size_v2f.y / 2) - (battle_board_texture_size.y / 2) );
	battle_board.setTextureRect( sf::IntRect(0, 0, battle_board_texture_size.x, battle_board_texture_size.y) );

	// Create big black mat
	sf::Texture* black_mat_texture = TTTHelpers::load_texture("assets/images/black-mat.png");
	sf::Vector2u black_mat_texture_size = black_mat_texture->getSize();

	black_mat.setTexture(black_mat_texture);
	black_mat.setSize( sf::Vector2f(black_mat_texture_size.x, black_mat_texture_size.y) );
	black_mat.setPosition( (window_size_v2f.x / 2) - (black_mat_texture_size.x / 2), (window_size_v2f.y / 2) - (black_mat_texture_size.y / 2) );
	black_mat.setTextureRect( sf::IntRect(0, 0, black_mat_texture_size.x, black_mat_texture_size.y) );

	// Prepare texts
	heading1.setFont(*((*ttt_fonts)[4]));
	heading1.setColor(sf::Color::White);
	heading1.setStyle(sf::Text::Regular);
	heading1.setCharacterSize(80); 
	heading1.setPosition((window_size_v2f.x / 2), (window_size_v2f.y / 2) - 170); 
	TTTHelpers::set_text_string(heading1, "TAC TIC TOE", "CT"); 

	tagline.setFont(*((*ttt_fonts)[3]));
	tagline.setColor(sf::Color::White);
	tagline.setStyle(sf::Text::Regular);
	tagline.setCharacterSize(19);
	tagline.setPosition((window_size_v2f.x / 2), (window_size_v2f.y / 2) - 70);
	TTTHelpers::set_text_string(tagline, "BECAUSE TIC TAC TOE IS TOO MAINSTREAM", "CT");

	pick_your_battle = tagline;
	pick_your_battle.setPosition((window_size_v2f.x / 2), (window_size_v2f.y / 2) + 50);
	TTTHelpers::set_text_string(pick_your_battle, "PICK YOUR BATTLE", "CT");

	// Shiny new start button
	sf::Texture* single_button_texture = TTTHelpers::load_texture("assets/images/single-button.png");
	sf::Vector2u single_button_texture_size = single_button_texture->getSize();

	single_button.setTexture(single_button_texture);
	single_button.setSize(sf::Vector2f(single_button_texture_size.x, single_button_texture_size.y));
	single_button.setPosition((window_size_v2f.x / 2) - (single_button_texture_size.x / 2) - 200, (window_size_v2f.y / 2) - (single_button_texture_size.y / 2) + 140);

	sf::Texture* lan_button_texture = TTTHelpers::load_texture("assets/images/lan-button.png");
	sf::Vector2u lan_button_texture_size = lan_button_texture->getSize();

	lan_button.setTexture(lan_button_texture);
	lan_button.setSize(sf::Vector2f(lan_button_texture_size.x, lan_button_texture_size.y));
	lan_button.setPosition((window_size_v2f.x / 2) - (lan_button_texture_size.x / 2) + 200, (window_size_v2f.y / 2) - (lan_button_texture_size.y / 2) + 140);

	// Easter help 
	sf::Texture* help_button_texture = TTTHelpers::load_texture("assets/images/help.png");
	sf::Vector2u help_button_texture_size = help_button_texture->getSize();

	help_button.setTexture(help_button_texture);
	help_button.setSize( sf::Vector2f(help_button_texture_size.x, help_button_texture_size.y) );
	help_button.setPosition(764, 105);
	help_button.setTextureRect( sf::IntRect(0, 0, help_button_texture_size.x, help_button_texture_size.y) );

}

// INSIDE LOOP
void SceneMenu::render()
{
	window->setMouseCursorVisible(true);

	// Draw backgrouds
	window->draw(battle_board);
	window->draw(black_mat);

	// Draw texts
	window->draw(heading1);
	window->draw(tagline);
	window->draw(pick_your_battle);

	// Draw buttons
	window->draw(single_button);
	window->draw(lan_button);
	window->draw(help_button);
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
	if (single_button.getGlobalBounds().contains(click_x, click_y))
	{
		return 1;
	}

	// Multiplayer
	if (lan_button.getGlobalBounds().contains(click_x, click_y))
	{
		return 2;
	}

	// Help button
	if (help_button.getGlobalBounds().contains(click_x, click_y))
	{
		system("start http://anonoz.github.io/t3");
	}

	return 0;
}

// Scene changing
