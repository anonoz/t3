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

// Multiplayer functions
void TTT_Instance::resetMultiplayer()
{
	multiplayer_port = 50001;

	multiplayer_mode = true;
	multiplayer_connected = false;
	multiplayer_listening_for_client = false;

	socket = new sf::TcpSocket;
}

void TTT_Instance::quitMultiplayer()
{
	multiplayer_mode = false;
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

bool TTT_Instance::isItMyTurn()
{
	return multiplayer_myturn;
}

char TTT_Instance::whoAmI()
{
	return (multiplayer_amiserver) ? 'X' : 'O';
}

bool TTT_Instance::didConnectionFail()
{
	if (multiplayer_connection_failed == false)
	{
		return true;
	}

	return false;
}

bool TTT_Instance::isDisconnected()
{
	return multiplayer_connection_failed;
}

bool TTT_Instance::didIJustLost()
{
	if (getWinner() != ' ' && getWinner() != whoAmI() && multiplayer_loserbetold == true)
	{
		std::cout << " I LOST NOW PLAY SOME SAX " << std::endl;
		multiplayer_loserbetold = false;
		return true;
	}

	return false;
}

// Client attempts to connect to server
bool TTT_Instance::connect(string ip_address)
{
	if (ip_address.length() == 0)
	{
		return false;
	}

	// Set flag
	multiplayer_connecting = true;
	multiplayer_connected = false;
	multiplayer_amiserver = false;

	// Stop listening thread
	stopListeningForClient();

	// Try socket connection
	startConnectingToServer(ip_address);

	return true;
}

// Server specific
void TTT_Instance::listenForClient()
{
	listener = new sf::TcpListener;
	listener->listen(multiplayer_port);

	std::cout << "Listening for client on port " << multiplayer_port << std::endl;
	int listen_status = listener->accept(*socket);

	if (listen_status == sf::Socket::Done)
	{
		multiplayer_amiserver = true;
		onConnectingSuccess();
		return;
	}
	else
	{
		// Maybe someone is using the socket, nvm, listen to another
		listener->listen(multiplayer_port + 1);
		listen_status = listener->accept(*socket);

		if (listen_status != sf::Socket::Done)
			onConnectingFailure();
		else
			multiplayer_amiserver = true;
			onConnectingSuccess();

		return;
	}
}

void TTT_Instance::startListeningForClient()
{
	listenForClient_thread = new sf::Thread(&TTT_Instance::listenForClient, this);
	listenForClient_thread->launch();
}

void TTT_Instance::stopListeningForClient()
{
	if (listenForClient_thread == 0) return;
	std::cout << "Stopping listener for client... " << std::endl;
	listenForClient_thread->terminate();
	listener->close();
}

// Client specific
void TTT_Instance::connectToServer()
{
	multiplayer_amiserver = false;

	std::cout << "Connecting to server " << server->toString() << std::endl;

	int connect_status = socket->connect(*server, multiplayer_port);
	std::cout << connect_status << std::endl;

	if (connect_status == sf::Socket::Done)
	{
		std::cout << "Connected to server" << std::endl;
		onConnectingSuccess();
		return;
	}
	else
	{
		connect_status = socket->connect(*server, multiplayer_port + 1);

		if (connect_status != sf::Socket::Done)
		{
			std::cout << "Failed to connect to server" << std::endl;
			onConnectingFailure();
			return;
		}
		else
		{
			onConnectingSuccess();
			return;
		}
	}
}

void TTT_Instance::startConnectingToServer(string ip_address)
{
	server = new sf::IpAddress(ip_address);
	connectToServer_thread = new sf::Thread(&TTT_Instance::connectToServer, this);
	connectToServer_thread->launch();
}

void TTT_Instance::stopConnectingToServer()
{
	if (connectToServer_thread == 0) return;
	connectToServer_thread->terminate();
}

// Actual gaming functions in multiplayer
void TTT_Instance::onConnectingSuccess()
{
	// Turn off listenin thread
	// stopListeningForClient();

	// Connection successful hook
	multiplayer_connected = true;
	multiplayer_connecting = false;
	multiplayer_connection_failed = false;

	// Clean game slate
	reset();

	if (multiplayer_amiserver)
	{
		// Server to client first active board
		sf::Packet sending_packet;
		// Tell client what board we are on now!
		sending_packet << 0 << current_board_id << 0;
		
		if (socket->send(sending_packet) == sf::Socket::Done)
		{
			
		}

		multiplayer_myturn = true;
	}
	else
	{
		// Eh server bro, where do we first start ah...
		sf::Packet receiving_packet;

		if (socket->receive(receiving_packet) == sf::Socket::Done)
		{
			int message_type, message_board_id;
			receiving_packet >> message_type >> message_board_id;
			if (message_type == 0) // initiation message
			{
				current_board_id = message_board_id;
			}
		}

		current_player = 'X';
		multiplayer_myturn = false;
		startWaitingForNextMove();
	}

	return;
}

void TTT_Instance::onConnectingFailure()
{
	multiplayer_connected = false;
	multiplayer_connecting = false;
	multiplayer_connection_failed = true;

	// restart listening thread
	startListeningForClient();
}

bool TTT_Instance::sendGridPlacementRequest(int board_id, int grid_id)
{
	// stopWaitingForNextMove();

	int socket_send_result = sendPacket(2, board_id, grid_id);
	std::cout << "Sending grid placement request" << std::endl;

	if (socket_send_result == sf::Socket::Done)
	{
		sf::Packet receiving_packet;
		int message_type, input_x, input_y;

		int retrieval_status = socket->receive(receiving_packet);

		if (retrieval_status == sf::Socket::Done)
		{
			std::cout << "Received approval message" << std::endl;
			receiving_packet >> message_type >> input_x >> input_y;
			if (message_type == 3)
			{
				if (input_x > -1 && input_y > -1)
				{
					multiplayer_myturn = false;
					startWaitingForNextMove();
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			std::cout << "Something wronng when getting approval: " << retrieval_status << std::endl;
			return false;
		}
	}
	else if (socket_send_result == sf::Socket::Disconnected)
	{
		reportDisconnection();
	}
	else
	{
		std::cout << "Request sending error: " << socket_send_result << std::endl;
	}
}

void TTT_Instance::waitForNextMove()
{
	std::cout << "Waiting for next move... " << std::endl;
	while (true)
	{
		sf::Packet receiving_packet;

		int socket_receive_status;

		socket_receive_status = socket->receive(receiving_packet);
		std::cout << "Socket received packet" << std::endl;

		int message_type, input_x, input_y;

		receiving_packet >> message_type >> input_x >> input_y;

		if (socket_receive_status == sf::Socket::Done)
		{

			std::cout << "Packet content: " << message_type << input_x << input_y << std::endl;

			if (message_type == 1)
			{
				// Enemy moved their mouse!
				enemy_mouse_position[0] = input_x;
				enemy_mouse_position[1] = input_y;
			}
			else if (message_type == 2)
			{
				std::cout << "Enemy requested for placement!" << std::endl;
				if (checkGrid(input_x, input_y))
				{
					// Approve
					sendPacket(3, input_x, input_y);

					// Sync to our database as well
					main_board[ input_x ][ input_y ] = (multiplayer_amiserver) ? 'O' : 'X';

					// Our turn babe
					current_board_id = input_y;

					// State change
					current_player = (multiplayer_amiserver) ? 'X' : 'O';
					multiplayer_myturn = true;

					// Am I losing?
					if (getWinner() != ' ' && getWinner() != whoAmI())
					{
						std::cout << "I think I lost... " << std::endl;
						multiplayer_loserbetold = true;
					}

					stopWaitingForNextMove();
				}
				else
				{
					// No thats not legal
					sendPacket(3, -1, -1);
				}
			}
			else if (message_type == 3)
			{
				main_board[ input_x ][ input_y ] = (multiplayer_amiserver) ? 'X' : 'O';
				std::cout << "This shouldnt be called" << std::endl;
			}
		}
		else if (socket_receive_status == sf::Socket::Disconnected)
		{
			reportDisconnection();
		}
		else
		{
			return;
		}
	}
}

void TTT_Instance::startWaitingForNextMove()
{
	waitForNextMove_thread = new sf::Thread(&TTT_Instance::waitForNextMove, this);
	waitForNextMove_thread->launch();
}

void TTT_Instance::stopWaitingForNextMove()
{
	if (waitForNextMove_thread == 0) return;
	waitForNextMove_thread->terminate();
}

void TTT_Instance::reportDisconnection()
{
	multiplayer_connected = false;
	multiplayer_connection_failed = true;

	waitForNextMove_thread->terminate();

	reset();
}

// Packet services
int TTT_Instance::sendPacket(int message_type, int input_x, int input_y)
{
	sf::Packet sending_packet;
	sending_packet << message_type << input_x << input_y;

	int send_status = socket->send(sending_packet);
	return send_status;
}
