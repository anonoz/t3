/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_multiplayer.hpp"

SceneMultiplayer::SceneMultiplayer(sf::RenderWindow* xwindow, vector<sf::Font*>* xttt_fonts, TTT_Instance* xinstance)
{
	window = xwindow;
	ttt_fonts = xttt_fonts;
	instance = xinstance;

	subscene = 0;

	// Calculating middle of the screen from RenderWindow size to fit ttt board
	sf::Vector2f window_size_v2f(window->getSize());

	// Create the battlefield background
	sf::Texture* battle_board_texture = TTTHelpers::load_texture("assets/images/battle-board.png");
	sf::Vector2u battle_board_texture_size = battle_board_texture->getSize();

	battle_board.setTexture(battle_board_texture);
	battle_board.setSize( sf::Vector2f(battle_board_texture_size.x, battle_board_texture_size.y) );
	battle_board.setPosition( (window_size_v2f.x / 2) - (battle_board_texture_size.x / 2), (window_size_v2f.y / 2) - (battle_board_texture_size.y / 2) );
	battle_board.setTextureRect( sf::IntRect(0, 0, battle_board_texture_size.x, battle_board_texture_size.y) );

	// Create blue multiplayer connection prompt mat
	sf::Texture* blue_mat_texture = TTTHelpers::load_texture("assets/images/multiplayer-prompt-mat.png");
	sf::Vector2u blue_mat_texture_size = blue_mat_texture->getSize();

	blue_mat.setTexture(blue_mat_texture);
	blue_mat.setSize( sf::Vector2f(blue_mat_texture_size.x, blue_mat_texture_size.y) );
	blue_mat.setPosition( (window_size_v2f.x / 2) - (blue_mat_texture_size.x / 2), (window_size_v2f.y / 2) - (blue_mat_texture_size.y / 2) );
	blue_mat.setTextureRect( sf::IntRect(0, 0, blue_mat_texture_size.x, blue_mat_texture_size.y) );

	// Heading 1 multiplayer
	heading1.setFont(*((*ttt_fonts)[4]));
	heading1.setColor(sf::Color::White);
	heading1.setStyle(sf::Text::Regular);
	heading1.setCharacterSize(80);
	heading1.setPosition((window_size_v2f.x / 2), (window_size_v2f.y / 2) - 170);
	TTTHelpers::set_text_string(heading1, "MULTIPLAYER", "CT");

	// X button to chicken out back to menu
	sf::Texture* x_button_texture = TTTHelpers::load_texture("assets/images/x-button.png");
	sf::Vector2u x_button_texture_size = x_button_texture->getSize();

	x_button.setTexture(x_button_texture);
	x_button.setSize( sf::Vector2f(x_button_texture_size.x, x_button_texture_size.y) );
	x_button.setPosition(764, 105);
	x_button.setTextureRect( sf::IntRect(0, 0, x_button_texture_size.x, x_button_texture_size.y) );

	// "Key in your friend's ip address"
	key_in_prompt.setFont(*((*ttt_fonts)[4]));
	key_in_prompt.setColor(sf::Color::White);
	key_in_prompt.setStyle(sf::Text::Regular);
	key_in_prompt.setCharacterSize(19);
	key_in_prompt.setPosition((window_size_v2f.x / 2), (window_size_v2f.x / 2) - 170);
	TTTHelpers::set_text_string(key_in_prompt, "KEY IN YOUR FRIEND'S IP ADDRESS", "CT");

	// IP address text box
	user_input_ip_address = "";

	ip_address_textbox.setFont(*((*ttt_fonts)[4]));
	ip_address_textbox.setColor(sf::Color::White);
	ip_address_textbox.setStyle(sf::Text::Regular);
	ip_address_textbox.setCharacterSize(60);
	ip_address_textbox.setPosition((window_size_v2f.x / 2), (window_size_v2f.x / 2) - 134);
	TTTHelpers::set_text_string(ip_address_textbox, user_input_ip_address, "CT");

	// Dotted line
	sf::Texture* dotted_line_texture = TTTHelpers::load_texture("assets/images/dotted-line.png");
	sf::Vector2u dotted_line_texture_size = dotted_line_texture->getSize();

	dotted_line.setTexture(dotted_line_texture);
	dotted_line.setSize( sf::Vector2f(dotted_line_texture_size.x, dotted_line_texture_size.y) );
	dotted_line.setPosition( (window_size_v2f.x / 2) - (dotted_line_texture_size.x / 2), (window_size_v2f.y / 2) - (dotted_line_texture_size.y / 2) + 10 );
	dotted_line.setTextureRect( sf::IntRect(0, 0, dotted_line_texture_size.x, dotted_line_texture_size.y) );

	// "Or Give Your Friend's Yours"
	give_friend_your_ip.setFont(*((*ttt_fonts)[4]));
	give_friend_your_ip.setColor(sf::Color::White);
	give_friend_your_ip.setStyle(sf::Text::Regular);
	give_friend_your_ip.setCharacterSize(19);
	give_friend_your_ip.setPosition((window_size_v2f.x / 2), (window_size_v2f.x / 2) - 40 );
	TTTHelpers::set_text_string(give_friend_your_ip, "OR GIVE YOUR FRIEND YOURS & GAME WILL START", "CT");

	// Your IP Address
	your_ip_address.setFont(*((*ttt_fonts)[0]));
	your_ip_address.setColor(sf::Color::White);
	your_ip_address.setStyle(sf::Text::Regular);
	your_ip_address.setCharacterSize(19);
	your_ip_address.setPosition((window_size_v2f.x / 2), (window_size_v2f.x / 2) - 20);
	TTTHelpers::set_text_string(your_ip_address, sf::IpAddress::getLocalAddress().toString(), "CT");

	// Connect button
	sf::Texture* connect_button_texture = TTTHelpers::load_texture("assets/images/connect-button.png");
	sf::Vector2u connect_button_texture_size = connect_button_texture->getSize();

	connect_button.setTexture(connect_button_texture);
	connect_button.setSize( sf::Vector2f(connect_button_texture_size.x, connect_button_texture_size.y) );
	connect_button.setPosition( (window_size_v2f.x / 2) - (connect_button_texture_size.x / 2), (window_size_v2f.y / 2) - (connect_button_texture_size.y / 2) + 150 );
	connect_button.setTextureRect( sf::IntRect(0, 0, connect_button_texture_size.x, connect_button_texture_size.y) );

	sf::Texture* connect_button_inactive_texture = TTTHelpers::load_texture("assets/images/connect-button-inactive.png");
	sf::Vector2u connect_button_inactive_texture_size = connect_button_inactive_texture->getSize();

	connect_button_inactive.setTexture(connect_button_inactive_texture);
	connect_button_inactive.setSize( sf::Vector2f(connect_button_inactive_texture_size.x, connect_button_inactive_texture_size.y) );
	connect_button_inactive.setPosition( (window_size_v2f.x / 2) - (connect_button_inactive_texture_size.x / 2), (window_size_v2f.y / 2) - (connect_button_inactive_texture_size.y / 2) + 150 );
	connect_button_inactive.setTextureRect( sf::IntRect(0, 0, connect_button_inactive_texture_size.x, connect_button_inactive_texture_size.y) );

	// Subscene 1: Waiting for your friend...
	s1_waiting.setFont(*((*ttt_fonts)[4]));
	s1_waiting.setColor(sf::Color::White);
	s1_waiting.setStyle(sf::Text::Regular);
	s1_waiting.setCharacterSize(20);
	s1_waiting.setPosition((window_size_v2f.x / 2), (window_size_v2f.x / 2) - 134);
	TTTHelpers::set_text_string(s1_waiting, "Waiting for your friend to connect...", "CT");

}

void SceneMultiplayer::enter()
{
	subscene = 0;
	instance->resetMultiplayer();
	instance->startListeningForClient();
}

void SceneMultiplayer::leave()
{
	std::cout << "Leaving multiplayer prompt page.. " << std::endl;
	instance->stopListeningForClient();
	instance->quitMultiplayer();
}

void SceneMultiplayer::render()
{
	// Fix bug of OS mouse cursor disappearing
	window->setMouseCursorVisible(true);

	window->draw(battle_board);
	window->draw(blue_mat);
	window->draw(heading1);
	window->draw(x_button);

	if (instance->isConnecting())
	{
		window->draw(s1_waiting);
	}
	else
	{
		window->draw(key_in_prompt);

		// If got update its shown
		TTTHelpers::set_text_string(ip_address_textbox, user_input_ip_address, "CT");
		window->draw(ip_address_textbox);

		window->draw(dotted_line);
		window->draw(give_friend_your_ip);
		window->draw(your_ip_address);

		if (user_input_ip_address.length() > 0)
			window->draw(connect_button);
		else
			window->draw(connect_button_inactive);
	}
}

int SceneMultiplayer::handle(sf::Event* xevent)
{
	event = xevent;

	// Checking instance, and go to battlefield when connected
	if (instance->isConnected())
	{
		return 1;
	}

	switch (event->type)
	{
		case sf::Event::MouseButtonReleased:
		{
			// Delegate mouse click event
			return handle_mouse_click(event->mouseButton.x, event->mouseButton.y);
			break;
		}

		case sf::Event::KeyPressed:
		{
			// Delegate keypress event
			return handle_keypress(event->key.code);
			break;
		}
	}

	return 2; // Multiplayer Prompt Scene is 2
}

int SceneMultiplayer::handle_mouse_click(int click_x, int click_y)
{
	// X button to go back to menu
	if (x_button.getGlobalBounds().contains(click_x, click_y))
	{
		return 0; // Menu
	}
	else if (user_input_ip_address.length() > 0 && connect_button.getGlobalBounds().contains(click_x, click_y))
	{
		instance->connect(user_input_ip_address);

		if (instance->isConnected())
			return 1;
	}

	return 2;
}

int SceneMultiplayer::handle_keypress(int key)
{
	if (key == sf::Keyboard::Escape)
	{
		return 0;
	}

	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
	{
		user_input_ip_address += char('A' + (key - sf::Keyboard::A));
	}

	if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
	{
		user_input_ip_address += char('0' + (key - sf::Keyboard::Num0));
	}

	if (key == sf::Keyboard::Period)
	{
		user_input_ip_address += '.';
	}

	if (key == sf::Keyboard::BackSpace)
	{
		user_input_ip_address = user_input_ip_address.substr(0, user_input_ip_address.size()-1);
	}

	if (key == sf::Keyboard::Return && user_input_ip_address.length() > 0)
	{
		instance->connect(user_input_ip_address);
	}

	std::cout << user_input_ip_address << std::endl;

	return 2; // Same scene
}