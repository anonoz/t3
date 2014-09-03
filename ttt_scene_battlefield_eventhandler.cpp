/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_battlefield.hpp"

int SceneBattlefield::handle(sf::Event* xevent)
{
	int new_scene = 1;
	event = xevent;

	// Things to watch for mouse movement:
	// - Cursor tracking
	// - Cursor gray out for invalid hit zone 
	// - Halo hinting for grids
	if (event->type == sf::Event::MouseMoved)
	{
		handle_mouse_over();
	}

	// Things to watch for mouse click:
	// - Placement of markers
	if (event->type == sf::Event::MouseButtonPressed)
	{
		new_scene = handle_mouse_click();
	}

	// Alternative keyboard way of playing the game
	if (event->type == sf::Event::KeyPressed)
	{
		new_scene = handle_keypress(event->key.code);
	}

	return new_scene;
}

int SceneBattlefield::handle_mouse_over()
{
	sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	
	// Hint halos
	std::vector< int > board_grid_coords = getGridHit( mouse_position );

	if (board_grid_coords[1] > -1 && board_grid_coords[0] == instance->getCurrentBoardId())
	{
		sf::Vector2f halo_coordinates = getBoardHaloCoorginates(board_grid_coords[1]);

		if (instance->getCurrentPlayer() == 'X')
		{
			o_hint_halo.setPosition(halo_coordinates);
			x_hint_halo.setPosition(sf::Vector2f(1000, 1000));
		}
		else
		{
			x_hint_halo.setPosition(halo_coordinates);
			o_hint_halo.setPosition(sf::Vector2f(1000, 1000));
		}
	}
	else
	{
		x_hint_halo.setPosition(sf::Vector2f(1000, 1000));
		o_hint_halo.setPosition(sf::Vector2f(1000, 1000));
	}

	// Restart n Quit buttons
	if (restart_button.getGlobalBounds().contains(mouse_position))
	{
		restart_button.setTexture(restart_button_hover_texture);
	}
	else if (quit_button.getGlobalBounds().contains(mouse_position))
	{
		quit_button.setTexture(quit_button_hover_texture);
	}
	else
	{
		restart_button.setTexture(restart_button_normal_texture);
		quit_button.setTexture(quit_button_normal_texture);
	}

	// Mouse cursor toggling
	// - ACTIVE if player is targeting active board & empty grid
	
	// Dude to real time need this event handler moved to renderer

	mouse_cursor.setTextureRect( sf::IntRect(0, 0, x_marker_texture->getSize().x, x_marker_texture->getSize().y) );
}

int SceneBattlefield::handle_mouse_click()
{
	sf::Vector2f mouse_position( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) );
	// Game still running
	if (instance->getWinner() != ' ' || (instance->isMultiplayer() && instance->isDisconnected()))
	{
		// Handle play again button
		if (playagain_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
		{
			reset();

			if (!instance->isMultiplayer())
				return 0;
		}
	}
	else
	{
		std::vector<int> board_grid_coords = getGridHit( mouse_position );

		// Do something when its not -1
		if (board_grid_coords[0] >= 0)
		{
			bool placement_successful = instance->setGrid(board_grid_coords[0], board_grid_coords[1]);

			srand(time(NULL));
			int which_sound_to_play = rand() % 1;
			if (placement_successful && which_sound_to_play)
			{
				placement_ok1_sound.play();
			}
			else if (placement_successful && !which_sound_to_play)
			{
				placement_ok2_sound.play();
			}
			else
			{
				placement_error_sound.play();
			}

			if (instance->getWinner() != ' ')
			{
				winner_sound.play();
				std::cout << "We have a winner: " << instance->getWinner();
			}

			if (instance->checkTie())
			{
				tie_sound.play();
			}
		}

		// Restart n Quit buttons
		if (restart_button.getGlobalBounds().contains(mouse_position))
		{
			instance->reset();
		}
		else if (quit_button.getGlobalBounds().contains(mouse_position))
		{
			instance->reset();
			if (instance->isMultiplayer())
			{
				instance->requestDisconnection();
			}
			return 0;
		}

	}

	return 1;
}

int SceneBattlefield::handle_keypress(int keycode)
{
	// ESC key to go back to menu
	if (keycode == sf::Keyboard::Escape)
	{
		// Multiplayer cannot quit
		if (instance->isMultiplayer())
			return 1;

		return 0;
	}

	// Numeric to choose grid
	if (keycode >= sf::Keyboard::Num1 && keycode <= sf::Keyboard::Num9 && instance->getWinner() == ' ')
	{
		bool placement_successful = instance->setGrid(instance->getCurrentBoardId(), keycode - sf::Keyboard::Num0 - 1);
		srand(time(NULL));
		int which_sound_to_play = rand() % 1;
		// Sorry DRY principle, jsut this once I swear I promise
		if (placement_successful && which_sound_to_play)
		{
			placement_ok1_sound.play();
		}
		else if (placement_successful && !which_sound_to_play)
		{
			placement_ok2_sound.play();
		}
		else
		{
			placement_error_sound.play();
		}

		if (instance->getWinner() != ' ')
		{
			winner_sound.play();
			std::cout << "We have a winner: " << instance->getWinner();
		}

		if (instance->checkTie())
		{
			tie_sound.play();
		}
	}

	return 1;
}

// Given the mouse coordinates and try to determine whether a grid has been hit
std::vector<int> SceneBattlefield::getGridHit(const sf::Vector2f& mouse_coords)
{
	int hit_x = mouse_coords.x, hit_y = mouse_coords.y;

	std::vector<int> board_grid(2, -1);

	// Column 1 board
	if (hit_x >= TOP_LEFT_X && hit_x <= TOP_LEFT_X + 3 * DELTA_GRID_X)
	{
		board_grid[0] = 0;
	}
	// Column 2 board
	else if (hit_x >= TOP_LEFT_X + DELTA_BOARD_X && hit_x <= TOP_LEFT_X + DELTA_BOARD_X + 3 * DELTA_GRID_X)
	{
		board_grid[0] = 1;
	}
	// Column 3 board
	else if (hit_x >= TOP_LEFT_X + 2 * DELTA_BOARD_X && hit_x <= TOP_LEFT_X + 2 * DELTA_BOARD_X + 3 * DELTA_GRID_X ) {
		board_grid[0] = 2;
	}
	// Oops, out of board!
	else {
		board_grid[0] = -1;

		// Short circuit
		return board_grid;
	}

	// Row 1 board
	if (hit_y >= TOP_LEFT_Y && hit_y <= TOP_LEFT_Y + 3 * DELTA_GRID_Y)
	{
		// board_grid[0] = 0;
	}
	// Row 2 board
	else if (hit_y >= TOP_LEFT_Y + DELTA_BOARD_Y && hit_y <= TOP_LEFT_Y + DELTA_BOARD_Y + 3 * DELTA_GRID_Y)
	{
		board_grid[0] += 3;
	}
	// Row 3 board
	else if (hit_y >= TOP_LEFT_Y + 2 * DELTA_BOARD_Y && hit_y <= TOP_LEFT_Y + 2 * DELTA_BOARD_Y + 3 * DELTA_GRID_Y ) {
		board_grid[0] += 6;
	}
	// Oops, out of board!
	else {
		board_grid[0] = -1;

		// Short circuit again
		return board_grid;
	}

	// Before we calculate grid, we minus off the hit coords

	if (board_grid[0] % 3 == 0) hit_x -= TOP_LEFT_X;
	if (board_grid[0] % 3 == 1) hit_x -= TOP_LEFT_X + DELTA_BOARD_X;
	if (board_grid[0] % 3 == 2) hit_x -= TOP_LEFT_X + 2 * DELTA_BOARD_X;

	if (board_grid[0] / 3 == 0) hit_y -= TOP_LEFT_Y;
	if (board_grid[0] / 3 == 1) hit_y -= TOP_LEFT_Y + DELTA_BOARD_Y;
	if (board_grid[0] / 3 == 2) hit_y -= TOP_LEFT_Y + 2 * DELTA_BOARD_Y;

	// Calculate grid now
	if (hit_x <= DELTA_GRID_X)
	{
		board_grid[1] = 0;
	}
	else if (hit_x > 1 * DELTA_GRID_X && hit_x <= 2 * DELTA_GRID_X)
	{
		board_grid[1] = 1;
	}
	else if (hit_x > 2 * DELTA_GRID_X && hit_x <= 3 * DELTA_GRID_X)
	{
		board_grid[1] = 2;
	}
	else
	{
		board_grid[1] = -1;
	}

	// grid Y
	if (hit_y <= DELTA_GRID_Y)
	{
		// board_grid[1] += 0;
	}
	else if (hit_y > 1 * DELTA_GRID_Y && hit_y <= 2 * DELTA_GRID_Y)
	{
		board_grid[1] += 3;
	}
	else if (hit_y > 2 * DELTA_GRID_Y && hit_y <= 3 * DELTA_GRID_Y)
	{
		board_grid[1] += 6;
	}
	else
	{
		board_grid[1] = -1;
	}

	return board_grid;
}
