#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// TTT files
#include "ttt_helpers.hpp"

class TTTModel
{
	private:
		std::vector< std::vector<char> > main_board;

	public:
		TTTModel();
		bool checkWin();
};

TTTModel::TTTModel()
{
	// Wipe the game clean
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			main_board[i][j] = ' ';
		}
	}
}

bool TTTModel::checkWin()
{
	// Check each board
	return true;
}
