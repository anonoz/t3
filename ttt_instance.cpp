/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_instance.hpp"

// EXPLANATION
//
// An instance = a game, it can be reset
//
// Board = a single tic tac toe board on the 3x3 tac tie toe battlefield
//
// Grid = A single box within a board.
//
// 1 instance has 3x3 boards that have 3x3 grids each.

TTT_Instance::TTT_Instance()
{
	// Initiate all the flags, even if they are unused
	multiplayer_port = 50001;
	multiplayer_mode = false;
	multiplayer_connected = false;
	multiplayer_listening_for_client = false;
	multiplayer_connecting = false;
	multiplayer_connection_failed = false;
	multiplayer_amiserver = false;
	multiplayer_myturn = false;
	multiplayer_loserbetold = false;

	reset();
}

void TTT_Instance::reset()
{
	main_board.clear();

	for (int board_id = 0; board_id < 9; board_id++)
	{
		vector< char > board;

		for (int grid_id = 0; grid_id < 9; grid_id++)
		{
			board.push_back(' ');
		}

		main_board.push_back(board);
	}

	// Random board
	srand(time(NULL));
	current_board_id = rand() % 8;

	current_player = 'X';
}

void TTT_Instance::quitGame()
{
	if (isMultiplayer())
	{
		quitMultiplayer();
	}
	else
	{
		reset();
	}
}

std::vector< std::vector<char> > TTT_Instance::getMainBoard()
{
	return main_board;
}

bool TTT_Instance::setGrid(int board_id, int grid_id)
{
	// NO if board is not active
	if (current_board_id != board_id)
		return false;

	if (isMultiplayer())
	{
		if (!isItMyTurn())
			return false;
	}

	// Check if someone placed there before
	if (checkGrid(board_id, grid_id))
	{
		// Multiplayer procedure: send the setGrid request to other player
		//   and double check whether the placement is allowed.
		if (isMultiplayer())
		{
			// Send to other computer
			if (sendGridPlacementRequest(board_id, grid_id))
			{
				main_board[ current_board_id ][ grid_id ] = current_player;

				current_player = (multiplayer_amiserver) ? 'O' : 'X';
				current_board_id = grid_id;

				multiplayer_myturn = false;
			}
			else
			{
				std::cout << "Conflicting placement over TCP" << std::endl;
			};
		}
		else
		{
			main_board[ current_board_id ][ grid_id ] = current_player;

			current_player = (current_player == 'O') ? 'X' : 'O';
			current_board_id = grid_id;
		}

		return true;
	}
	else
	{
		std::cout << "Conflicting placement" << std::endl;

		return false;
	}
}

// What is inside the grid?
char TTT_Instance::getGrid(int board_id, int grid_id)
{
	if (board_id > 8 || grid_id > 8)
		return ' ';

	return main_board[ board_id ][ grid_id ];
}

// Can I place here? Let's explicit
bool TTT_Instance::checkGrid(int board_id, int grid_id)
{
	if (board_id != current_board_id)
		return false;

	if (main_board[board_id][grid_id] != ' ')
		return false;

	return true;
}

// Who is playing?
char TTT_Instance::getCurrentPlayer()
{
	return current_player;
}

// Which board is active for piece placement?
int TTT_Instance::getCurrentBoardId()
{
	return current_board_id;
}

// For each board, check if O and X took down either of the 3 verticals, 3 horizontals or the 2 diagonals.
char TTT_Instance::getWinner()
{
	for (int board_id = 0; board_id < 9; board_id++)
	{
		vector< char > board = main_board[ board_id ];

		// Check horizontal lines
		for (int x = 0; x <3; x++)
		{
			if (   board[ x * 3 ] == board[x * 3 + 1]
				&& board[ x * 3 + 1] == board[ x * 3 + 2]
				&& board[ x * 3 ] != ' ' )
				return board[ x * 3 ];
		}

		// Check vertical lines
		for (int y = 0; y < 3; y++)
		{
			if (   board[ y ] == board[y + 3]
				&& board[ y + 3] == board[y + 6]
				&& board[y] != ' ')
				return board[y];
		}

		// Check diagonal lines
		if (  ((board[0] == board[4] && board[4] == board[8])
			|| (board[2] == board[4] && board[4] == board[6]))
			&&  board[4] != ' ')
			return board[4];
	}

	return ' ';
}

bool TTT_Instance::checkTie()
{
	for (int board_id = 0; board_id < 9; board_id++)
	{
		for (int grid_id = 0; grid_id < 9; grid_id++)
		{
			// If one cell is empty, let them fill up the grid!
			if (main_board[board_id][grid_id] == ' ')
				return false;
		}
	}

	return true;
}