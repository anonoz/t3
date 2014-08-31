/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>

// TTT files
#include "ttt_helpers.hpp"

using namespace std;

#ifndef TTT_INSTANCE_HPP
#define TTT_INSTANCE_HPP

class TTT_Instance
{
	private:
		std::vector< std::vector<char> > main_board;
		
		char current_player;
		int current_board_id;

	public:
		TTT_Instance();
		void reset();
		bool setGrid(int board_id, int grid_id);
		char getGrid(int board_id, int grid_id);
		bool checkGrid(int board_id, int grid_id);

		char getCurrentPlayer();
		
		int getCurrentBoardId();

		std::vector< std::vector<char> > getMainBoard();
		char getWinner();
		bool checkTie();
};

#endif