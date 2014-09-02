/************ P R O J E C T ****************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2014/15
ID and Name #1 : 1131123100 Chong Hon Siong
Contacts #1 : 0173009142 honsiongchs@gmail.com
Lecture Section : TC101
Tutorial Section: TC201
********************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
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

		// MP flags
		unsigned short multiplayer_port;
		bool multiplayer_mode;
		bool multiplayer_connected;
		bool multiplayer_listening_for_client;
		bool multiplayer_connecting;
		bool multiplayer_connection_failed;
		bool multiplayer_amiserver;
		bool multiplayer_myturn;
		bool multiplayer_loserbetold;

		// MP variables
		int enemy_mouse_position[2];
		int enemy_latest_placement[2];


		// TCP for multiplayer
		sf::TcpListener* listener;
		sf::TcpSocket* socket;
		sf::IpAddress* server;

		// OMG some advanced shit here
		sf::Thread* listenForClient_thread;
		sf::Thread* connectToServer_thread;
		sf::Thread* waitForNextMove_thread;

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

		// Multiplayer specific
		void resetMultiplayer();
		void quitMultiplayer();

		bool isMultiplayer();
		bool isConnected();
		bool isConnecting();
		bool isItMyTurn();
		char whoAmI();
		bool didConnectionFail();
		bool isDisconnected();
		bool didIJustLost();

		bool connect(string ip_address);

		void listenForClient();
		void startListeningForClient();
		void stopListeningForClient();

		void connectToServer();
		void startConnectingToServer(string ip_address);
		void stopConnectingToServer();

		void onConnectingSuccess();
		void onConnectingFailure();

		bool sendGridPlacementRequest(int board_id, int grid_id);

		void waitForNextMove();
		void startWaitingForNextMove();
		void stopWaitingForNextMove();

		void reportDisconnection();

		int sendPacket(int, int, int);
};

#endif