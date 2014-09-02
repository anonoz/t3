/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_scene_battlefield.hpp"

// Calculation aids
// Board level
const float SceneBattlefield::TOP_LEFT_X = 147;
const float SceneBattlefield::TOP_LEFT_Y = 37;

const int SceneBattlefield::DELTA_BOARD_X = 173;
const int SceneBattlefield::DELTA_BOARD_Y = 183;

// Grid level
const int SceneBattlefield::TOP_LEFT_GRID_X = 25;
const int SceneBattlefield::TOP_LEFT_GRID_Y = 25;

const int SceneBattlefield::DELTA_GRID_X = 50;
const int SceneBattlefield::DELTA_GRID_Y = 50;

SceneBattlefield::SceneBattlefield(sf::RenderWindow* xwindow, std::vector<sf::Font*>* xttt_fonts, TTT_Instance* xinstance)
{
	window = xwindow;
	ttt_fonts = xttt_fonts;

	// Game instance got from director
	instance = xinstance;

	// Some RenderWindow calculations
	sf::Vector2f window_size_v2f(window->getSize());

	// Create board as background
	sf::Texture* battle_board_texture = TTTHelpers::load_texture("assets/images/battle-board.png");
	sf::Vector2u battle_board_texture_size = battle_board_texture->getSize();

	battle_board.setTexture(battle_board_texture);
	battle_board.setSize( sf::Vector2f(battle_board_texture_size.x, battle_board_texture_size.y) );
	battle_board.setPosition( (window_size_v2f.x / 2) - (battle_board_texture_size.x / 2), (window_size_v2f.y / 2) - (battle_board_texture_size.y / 2) );
	battle_board.setTextureRect( sf::IntRect(0, 0, battle_board_texture_size.x, battle_board_texture_size.y) );

	// Create marker textures and rectangle
	x_marker_texture = TTTHelpers::load_texture("assets/images/x-marker.png");
	sf::Vector2u x_marker_texture_size = x_marker_texture->getSize();

	x_marker.setTexture(x_marker_texture);
	x_marker.setSize( sf::Vector2f(x_marker_texture_size.x, x_marker_texture_size.y) );
	x_marker.setTextureRect( sf::IntRect(0, 0, x_marker_texture_size.x, x_marker_texture_size.y) );

	x_marker.setPosition(getGridCoordinates(8,8));

	o_marker_texture = TTTHelpers::load_texture("assets/images/o-marker.png");
	sf::Vector2u o_marker_texture_size = o_marker_texture->getSize();

	o_marker.setTexture(o_marker_texture);
	o_marker.setSize( sf::Vector2f(o_marker_texture_size.x, o_marker_texture_size.y) );
	o_marker.setTextureRect( sf::IntRect(0, 0, o_marker_texture_size.x, o_marker_texture_size.y) );

	// Create mouse cursors (the inactive textures too)
	x_marker_inactive_texture = TTTHelpers::load_texture("assets/images/x-marker-inactive.png");
	o_marker_inactive_texture = TTTHelpers::load_texture("assets/images/o-marker-inactive.png");

	mouse_cursor = x_marker;

	// Create active halos
	sf::Texture* x_active_halo_texture = TTTHelpers::load_texture("assets/images/x-active-halo-bg.png");
	sf::Texture* o_active_halo_texture = TTTHelpers::load_texture("assets/images/o-active-halo-bg.png");

	sf::Vector2u x_active_halo_texture_size = x_active_halo_texture->getSize();

	x_active_halo.setTexture(x_active_halo_texture);
	x_active_halo.setSize( sf::Vector2f(x_active_halo_texture_size.x, x_active_halo_texture_size.y) );
	x_active_halo.setTextureRect( sf::IntRect(0, 0, x_active_halo_texture_size.x, x_active_halo_texture_size.y) );

	o_active_halo = x_active_halo;
	o_active_halo.setTexture(o_active_halo_texture);

	// Create hinting halos
	sf::Texture* x_hint_halo_texture = TTTHelpers::load_texture("assets/images/x-hint-halo-bg.png");
	sf::Texture* o_hint_halo_texture = TTTHelpers::load_texture("assets/images/o-hint-halo-bg.png");

	sf::Vector2u x_hint_halo_texture_size = x_hint_halo_texture->getSize();

	x_hint_halo.setTexture(x_hint_halo_texture);
	x_hint_halo.setSize( sf::Vector2f(x_hint_halo_texture_size.x, x_hint_halo_texture_size.y) );
	x_hint_halo.setTextureRect( sf::IntRect(0, 0, x_hint_halo_texture_size.x, x_hint_halo_texture_size.y) );
	x_hint_halo.setPosition(1000,1000);

	o_hint_halo = x_hint_halo;
	o_hint_halo.setTexture(o_hint_halo_texture);

	// Create grid hitzones for event handling

	// Create winner mat
	sf::Texture* x_winner_mat_texture = TTTHelpers::load_texture("assets/images/x-winner-mat.png");
	sf::Texture* o_winner_mat_texture = TTTHelpers::load_texture("assets/images/o-winner-mat.png");
	sf::Texture* tie_mat_texture = TTTHelpers::load_texture("assets/images/tie-mat.png");

	sf::Vector2u winner_mat_texture_size = x_winner_mat_texture->getSize();

	x_winner_mat.setTexture(x_winner_mat_texture);
	x_winner_mat.setSize( sf::Vector2f(winner_mat_texture_size.x, winner_mat_texture_size.y) );
	x_winner_mat.setTextureRect( sf::IntRect(0, 0, winner_mat_texture_size.x, winner_mat_texture_size.y) );
	x_winner_mat.setPosition( (window_size_v2f.x / 2) - (winner_mat_texture_size.x / 2), (window_size_v2f.y / 2) - (winner_mat_texture_size.y / 2) );

	o_winner_mat = x_winner_mat;
	o_winner_mat.setTexture(o_winner_mat_texture);

	tie_mat = x_winner_mat;
	tie_mat.setTexture(tie_mat_texture);

	// Create winner mat textual notices
	x_winner_notice.setFont(*((*ttt_fonts)[4]));
	x_winner_notice.setColor(sf::Color::White);
	x_winner_notice.setStyle(sf::Text::Regular);
	x_winner_notice.setCharacterSize(80);
	x_winner_notice.setPosition(x_winner_mat.getPosition().x + x_winner_mat.getSize().x / 2, (x_winner_mat.getPosition().y + x_winner_mat.getSize().y / 2) - 60);
	TTTHelpers::set_text_string(x_winner_notice, "PLAYER X WON", "CT");

	o_winner_notice = x_winner_notice;
	TTTHelpers::set_text_string(o_winner_notice, "PLAYER O WON", "CT");

	tie_notice = x_winner_notice;
	TTTHelpers::set_text_string(tie_notice, "TIE", "CT");	

	// Create winner mat play again inactive and active buttons
	sf::Texture* playagain_button_texture = TTTHelpers::load_texture("assets/images/playagain-button.png");
	sf::Vector2u playagain_button_texture_size = playagain_button_texture->getSize();

	playagain_button.setTexture(playagain_button_texture);
	playagain_button.setSize( sf::Vector2f(playagain_button_texture_size.x, playagain_button_texture_size.y));
	playagain_button.setTextureRect(sf::IntRect(0, 0, playagain_button_texture_size.x, playagain_button_texture_size.y));
	playagain_button.setPosition( (window_size_v2f.x / 2) - (playagain_button.getSize().x / 2) , (window_size_v2f.y / 2) - (playagain_button.getSize().y / 2) + 40);

	// Create the soundbytes
	placement_ok1_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_1.ogg");
	placement_ok2_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_2.ogg");
	placement_error_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/placement_error.ogg");
	winner_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/result_win.ogg");
	tie_sound_buffer = *TTTHelpers::load_sound_buffer("assets/sounds/result_tie.ogg");

	placement_ok1_sound.setBuffer(placement_ok1_sound_buffer);
	placement_ok2_sound.setBuffer(placement_ok2_sound_buffer);
	placement_error_sound.setBuffer(placement_error_sound_buffer);
	winner_sound.setBuffer(winner_sound_buffer);
	tie_sound.setBuffer(tie_sound_buffer);

}

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
	// Mouse Cursor
	sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

	sf::Vector2f cursor_position = mouse_position;
	cursor_position.x = cursor_position.x - mouse_cursor.getSize().x / 2;
	cursor_position.y = cursor_position.y - mouse_cursor.getSize().y / 2;
	mouse_cursor.setPosition(cursor_position);

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

	// Mouse cursor toggling
	// - ACTIVE if player is targeting active board & empty grid
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
	mouse_cursor.setTextureRect( sf::IntRect(0, 0, x_marker_texture->getSize().x, x_marker_texture->getSize().y) );
}

int SceneBattlefield::handle_mouse_click()
{
	if (instance->getWinner() == ' ')
	{
		std::vector<int> board_grid_coords = getGridHit( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) );

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

	}
	else
	{
		// Handle play again button
		if (playagain_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))))
		{
			reset();
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

void SceneBattlefield::render()
{
	// Draw mainboard
	window->draw( battle_board );

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
	if (instance->getWinner() == 'X')
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

	// If got winner draw play again button too

	// Draw cursors
	if ((!instance->isMultiplayer() && instance->getWinner() == ' ') || (instance->isMultiplayer() && instance->isItMyTurn()))
	{
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

void SceneBattlefield::reset()
{
	// Instance = game model. The truth. The source...
	instance->reset();
}