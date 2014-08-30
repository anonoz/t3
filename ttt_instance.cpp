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
		for (int grid_id = 0; grid_id < 9; grid_id++)
		{
			main_board[ board_id ][ grid_id ] = ' ';
		}
	}

	// Player O starts first
	current_player = 'O';
}

bool TTT_Instance::setGrid(int grid_id)
{
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

// For each board, check if O and X took down either of the 3 verticals, 3 horizontals or the 2 diagonals.
bool TTT_Instance::getWinningStatus()
{
	for (int board_id = 0; board_id < 9; board_id++)
	{


	}
}
