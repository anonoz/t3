/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_battlefield.hpp"

void SceneBattlefield::render()
{
	// Draw mainboard
	window->draw( battle_board );

	// Draw buttons
	if (!instance->isMultiplayer())
	{
		window->draw(restart_button);
	}
	window->draw(quit_button);

	// Draw active halo
	sf::Vector2f halo_coordinates = getBoardHaloCoorginates( instance->getCurrentBoardId() );

	if ((instance->isMultiplayer() && instance->isItMyTurn()) || !instance->isMultiplayer())
	{
		if (instance->getCurrentPlayer() == 'X')
		{
			x_active_halo.setPosition(halo_coordinates);
			window->draw( x_active_halo );
		}
		else if (instance->getCurrentPlayer() == 'O')
		{
			o_active_halo.setPosition(halo_coordinates);
			window->draw( o_active_halo );
		}

		// Draw hint halo
		if (instance->getCurrentPlayer() == 'X')
		{
			window->draw(o_hint_halo);
		}
		else
		{
			window->draw(x_hint_halo);
		}
	}

	// Draw exising markers
	std::vector< std::vector<char> > main_board = instance->getMainBoard();

	for (int board_id = 0; board_id < 9; board_id++)
	{
		for (int grid_id = 0; grid_id < 9; grid_id++)
		{
			if (main_board[ board_id ][ grid_id ] == 'X')
			{
				sf::RectangleShape x_marker_placements = x_marker;
				x_marker_placements.setPosition( getGridCoordinates(board_id, grid_id) );

				window->draw( x_marker_placements );
			}
			else if (main_board[ board_id ][ grid_id ] == 'O')
			{
				sf::RectangleShape o_marker_placements = o_marker;
				o_marker_placements.setPosition( getGridCoordinates(board_id, grid_id) );

				window->draw( o_marker_placements );
			}
		}
	}

	// Draw winner mat
	// OMFG somebody ragequit liao!
	if (instance->isMultiplayer() && instance->isDisconnected())
	{
		window->draw(o_winner_mat);
		window->draw(disconnected_notice);
		window->draw(playagain_button);
	}
	// Player wins on LAN
	else if (instance->getWinner() != ' ' && instance->isMultiplayer() && instance->whoAmI() == instance->getWinner())
	{
		window->draw(x_winner_mat);
		window->draw(you_won_notice);
		window->draw(playagain_button);
	}
	// Player lost LAN game
	else if (instance->getWinner() != ' ' && instance->isMultiplayer() && instance->whoAmI() != instance->getWinner())
	{
		window->draw(o_winner_mat);
		window->draw(you_lost_notice);
		window->draw(playagain_button);

		if (instance->didIJustLost())
		{
			std::cout << "Play sax" << std::endl;
			loser_sound.play();
		}
	}
	else if (instance->getWinner() == 'X')
	{
		window->draw(x_winner_mat);
		window->draw(x_winner_notice);
		window->draw(playagain_button);
	}
	else if (instance->getWinner() == 'O')
	{
		window->draw(o_winner_mat);
		window->draw(o_winner_notice);
		window->draw(playagain_button);
	}
	else if (instance->checkTie())
	{
		window->draw(tie_mat);
		window->draw(tie_notice);
		window->draw(playagain_button);
	}

	// Draw cursors
	if (	(!instance->isMultiplayer() && instance->getWinner() == ' ') 
		|| 	(instance->isMultiplayer() && instance->isItMyTurn() && !instance->isDisconnected())
		||	(instance->isMultiplayer() && instance->getWinner() != ' ')
		)
	{
		// Mouse Cursor
		sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

		sf::Vector2f cursor_position = mouse_position;
		cursor_position.x = cursor_position.x - mouse_cursor.getSize().x / 2;
		cursor_position.y = cursor_position.y - mouse_cursor.getSize().y / 2;
		mouse_cursor.setPosition(cursor_position);

		// Belongs to ttt_scene_battlefield_eventhandler but moved here
		//   due to need for real time update
		std::vector< int > board_grid_coords = getGridHit( mouse_position );

		if (instance->checkGrid(board_grid_coords[0], board_grid_coords[1]))
		{
			if (instance->getCurrentPlayer() == 'X')
			{
				mouse_cursor.setTexture(x_marker_texture);
			}
			else
			{
				mouse_cursor.setTexture(o_marker_texture);
			}
		}
		else
		{
			if (instance->getCurrentPlayer() == 'X')
			{
				mouse_cursor.setTexture(x_marker_inactive_texture);
			}
			else
			{
				mouse_cursor.setTexture(o_marker_inactive_texture);
			}
		}
		
		window->setMouseCursorVisible(false);
		window->draw(mouse_cursor);
	}
	else
	{
		window->setMouseCursorVisible(true);
	}
}

// Given the ID of board and grid, return the coordinates for renderer
sf::Vector2f SceneBattlefield::getGridCoordinates(int board_id, int grid_id)
{
	// sf::Vector2u coordinates;
	float top_left_x = TOP_LEFT_X, top_left_y = TOP_LEFT_Y;

	// Calculate X at board level (translation of coords inside battlefield)
	if (board_id % 3 > 0) top_left_x += DELTA_BOARD_X;
	if (board_id % 3 > 1) top_left_x += DELTA_BOARD_X;

	// Board Y at board level
	if (board_id >= 3) top_left_y += DELTA_BOARD_Y;
	if (board_id >= 6) top_left_y += DELTA_BOARD_Y;

	// X at grid level (translation of coords inside a board)
	if (grid_id % 3 > 0) top_left_x += DELTA_GRID_X;
	if (grid_id % 3 > 1) top_left_x += DELTA_GRID_X;

	// Y at grid level
	if (grid_id >= 3) top_left_y += DELTA_GRID_Y;
	if (grid_id >= 6) top_left_y += DELTA_GRID_Y;

	return sf::Vector2f(top_left_x, top_left_y);
}

// Calculate halo board coordinates
sf::Vector2f SceneBattlefield::getBoardHaloCoorginates(int board_id)
{
	sf::Vector2f grid_coords = getGridCoordinates(board_id, 0);

	return sf::Vector2f(grid_coords.x - 22, grid_coords.y - 20);
}
