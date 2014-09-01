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
	reset();

	std::cout << "TTT_INSTANCE constructed" << std::endl;
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

	// Player O starts first
	current_player = 'X';
}

std::vector< std::vector<char> > TTT_Instance::getMainBoard()
{
	return main_board;
}

bool TTT_Instance::setGrid(int board_id, int grid_id)
{
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

				current_player = (current_player == 'O') ? 'X' : 'O';
				current_board_id = grid_id;
			}
			else
			{
				std::cout << "Conflicting placement over TCP" << std::endl;
			};

			waitForNextMove();
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

// Multiplayer functions
void TTT_Instance::resetMultiplayer()
{
	multiplayer_port = 50001;

	multiplayer_mode = true;
	multiplayer_connected = false;
	multiplayer_listening_for_client = false;
}

bool TTT_Instance::isMultiplayer()
{
	return multiplayer_mode;
}

bool TTT_Instance::isConnected()
{
	return multiplayer_connected;
}

bool TTT_Instance::isConnecting()
{
	return multiplayer_connecting;
}

bool TTT_Instance::connect(string ip_address)
{
	socket = new sf::TcpSocket;

	multiplayer_connecting = true;
	multiplayer_amiserver = ip_address.length() == 0;

	// Try socket connection
	bool connection_successful = (multiplayer_amiserver) ? connectToServer(ip_address) : listenForClient();
	if(connection_successful)
	{
		multiplayer_connecting = false;
		multiplayer_connected = true;
	}
	else
	{
		delete socket;
		multiplayer_connecting = false;
		return false;
	}

	// If connection succeeds, start by letting server decide
	//   first board, then send first board notice to client.
	if (multiplayer_amiserver)
	{
		reset();

		// Tell client what board we are on now!
		int message[3] = {0, current_board_id, 0};
		
		if (socket->send(message, sizeof(message)) == sf::Socket::Done)
		{
			multiplayer_myturn = true;
		}
	}
	// If I am client, get the current active board
	else {

		// Eh server bro, where do we first start ah...
		int message[3];
		std::size_t received;
		if (socket->receive(message, sizeof(message), received) == sf::Socket::Done)
		{
			if (message[0] == 0) // initiation message
			{
				current_board_id = message[1];
			}
		}

		multiplayer_myturn = false;
		waitForNextMove();
	}

	return true;
}

// Server specific
bool TTT_Instance::listenForClient()
{
	listener = new sf::TcpListener;
	listener->listen(multiplayer_port);

	std::cout << "Listening for client on port " << multiplayer_port << std::endl;
	int listen_status = listener->accept(*socket);

	if (listen_status == sf::Socket::Done)
	{
		std::cout << "Got a client... " << std::endl;
		return true;
	}
	else
	{
		std::cout << "No client today... " << std::endl;
		return false;
	}
}

// Client specific
bool TTT_Instance::connectToServer(string ip_address)
{
	server = new sf::IpAddress(ip_address);

	std::cout << "Connecting to server " << server->toString() << std::endl;

	int connect_status = socket->connect(*server, multiplayer_port);
	std::cout << connect_status << std::endl;

	if (connect_status == sf::Socket::Done)
	{
		std::cout << "Connected to server" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed to connect to server" << std::endl;
		return false;
	}
}

// Actual gaming functions in multiplayer
bool TTT_Instance::sendGridPlacementRequest(int board_id, int grid_id)
{
	int message[3] = {2, board_id, grid_id};
	int socket_send_result = socket->send(message, sizeof(message));

	if (socket_send_result == sf::Socket::Done)
	{
		int received_message[3];
		std::size_t received;
		if (socket->receive(received_message, sizeof(received_message), received) != sf::Socket::Done)
		{
			if (received_message[0] == 3)
			{
				if (received_message[1] > -1 && received_message[2] > -1)
				{
					return true;
				}
			}
		}
	}
	else if (socket_send_result == sf::Socket::Disconnected)
	{
		multiplayer_connected = false;
	}
}

void TTT_Instance::waitForNextMove()
{
	int message[3] = {};
	std::size_t received;

	int socket_receive_status;

	while (!multiplayer_myturn)
	{
		socket_receive_status = socket->receive(message, sizeof(message), received);

		if (socket_receive_status == sf::Socket::Done)
		{

			if (message[0] == 1)
			{
				// Enemy moved their mouse!
			}
			else if (message[0] == 2)
			{
				int reply_message[3] = {};
				// Enemy requested for placement!
				if (checkGrid(message[1], message[2]))
				{
					// Approve
					reply_message = {3, message[1], message[2]};

					// Sync to our database as well
					main_board[ message[1] ][ message[2] ] = (multiplayer_amiserver) ? 'O' : 'X';

					multiplayer_myturn = true;
				}
				else
				{
					// No thats not legal
					reply_message = {3, -1, -1};
				}

				socket->send(reply_message, sizeof(reply_message));
				break;
			}
		}
		
	}
}