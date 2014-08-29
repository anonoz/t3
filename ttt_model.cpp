class TTTModel
{
	private:
		vector< vector<char> > main_board;

	public:
		TTTModel(){ init(); }
		bool checkWin();
};

void init()
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

bool checkWin()
{
	// Check each board
	for 
}