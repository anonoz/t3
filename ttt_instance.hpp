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