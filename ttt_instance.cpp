#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"
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
	// Wipe the game clean
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
	current_board_id = rand() % 8;

	// Player O starts first
	current_player = 'X';

	std::cout << "TTT_INSTANCE constructed" << std::endl;
}

std::vector< std::vector<char> > TTT_Instance::getMainBoard()
{
	return main_board;
}

bool TTT_Instance::setGrid(int board_id, int grid_id)
{
	if (board_id != current_board_id)
	{
		std::cout << "Not the active board" << std::endl;
		return false;
	}

	// Check if someone placed there before
	if (getGrid(current_board_id, grid_id) == ' ')
	{
		main_board[ current_board_id ][ grid_id ] = current_player;

		current_player = (current_player == 'O') ? 'X' : 'O';
		current_board_id = grid_id;

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
		if (board[0] == board[1] && board[1] == board[2])
		{
			if (board[0] != ' ') return board[0];
		}

		if (board[3] == board[4] && board[4] == board[5])
		{
			if (board[3] != ' ') return board[3];
		}

		if (board[6] == board[7] && board[7] == board[8])
		{
			if (board[6] != ' ') return board[6];
		}

		// Check vertical lines
		if (board[0] == board[3] && board[3] == board[6])
		{
			if (board[0] != ' ') return board[0];
		}

		if (board[1] == board[4] && board[4] == board[7])
		{
			if (board[1] != ' ') return board[1];
		}

		if (board[2] == board[5] && board[5] == board[8])
		{
			if (board[2] != ' ') return board[2];
		}

		// Check diagonal lines
		if (board[0] == board[4] && board[4] == board[8])
		{
			if (board[0] != ' ') return board[0];
		}

		if (board[2] == board[4] && board[4] == board[6])
		{
			if (board[2] != ' ') return board[2];
		}
	}

	return ' ';
}
