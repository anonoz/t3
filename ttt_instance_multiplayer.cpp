/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/

#include "ttt_instance.hpp"

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
	stopWaitingForNextMove();
	requestDisconnection();
	reset();
}

bool TTT_Instance::isMultiplayer()
{
	return multiplayer_mode;
}

bool TTT_Instance::isListening()
{
	return multiplayer_listening_for_client;
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
	multiplayer_listening_for_client = true;

	listener = new sf::TcpListener;
	listener->listen(multiplayer_port);


	// If successful, will be stuck in line below
	int listen_status = listener->accept(*socket);

	if (listen_status == sf::Socket::Done)
	{
		std::cout << "Listening for client on port " << multiplayer_port << std::endl;
		multiplayer_amiserver = true;
		onConnectingSuccess();
		return;
	}
	else
	{
		// Maybe someone is using the socket, nvm, listen to another
		delete listener;
		listener = new sf::TcpListener;
		listener->listen(multiplayer_port + 1);
		listen_status = listener->accept(*socket);

		if (listen_status != sf::Socket::Done)
		{
			// SO WRONG IT ENDS UP HERE!!!
			multiplayer_listening_for_client = false;
			std::cout << "Second listen failure: " << listen_status << std::endl;
		}
		else
		{
			std::cout << "Listening for client on port " << multiplayer_port + 1 << std::endl;
			multiplayer_amiserver = true;
			onConnectingSuccess();
		}

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
	if (listenForClient_thread == NULL) return;
	std::cout << "Stopping listener for client... " << std::endl;
	listenForClient_thread->terminate();
	delete listener, listenForClient_thread;
	listener = NULL;
	listenForClient_thread = NULL;
	multiplayer_listening_for_client = false;
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
	std::cout << "Sending grid placement request: "
		<< board_id
		<< grid_id
		<< std::endl;

	int socket_send_result = sendPacket(2, board_id, grid_id);

	if (socket_send_result == sf::Socket::Done)
	{
		sf::Packet receiving_packet;
		int message_type = 0,
			input_x = 0,
			input_y = 0;

		int retrieval_status = socket->receive(receiving_packet);

		if (retrieval_status == sf::Socket::Done)
		{
			receiving_packet >> message_type >> input_x >> input_y;

			std::cout << "Received approval message:" 
				<< message_type
				<< " " << input_x
				<< " " << input_y
				<< std::endl;

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
			else if (message_type == 99)
			{
				std::cout << "Message 99 captured in placement reply" << std::endl;
				reportDisconnection();
				return false;
			}
		}
		else if (retrieval_status == sf::Socket::Disconnected)
		{
			reportDisconnection();
			return false;
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
		return false;
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
			else if (message_type == 99)
			{
				reportDisconnection();
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
	if (waitForNextMove_thread == NULL) return;
	waitForNextMove_thread->terminate();
	delete waitForNextMove_thread;
	waitForNextMove_thread = NULL;
	std::cout << "No longer waiting for next move" << std::endl;
}

void TTT_Instance::reportDisconnection()
{
	multiplayer_connected = false;
	multiplayer_connection_failed = true;

	stopWaitingForNextMove();

	// reset();
	// quitMultiplayer();
}

void TTT_Instance::requestDisconnection()
{
	if (isDisconnected()) return;
	sendPacket(99, 0, 0);
	stopListeningForClient();
}

// Packet services
int TTT_Instance::sendPacket(int message_type, int input_x, int input_y)
{
	sf::Packet sending_packet;
	sending_packet << message_type << input_x << input_y;

	int send_status = socket->send(sending_packet);

	std::cout << "Packet sent: " << message_type << input_x << input_y << std::endl;

	return send_status;
}
