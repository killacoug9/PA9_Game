#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "GameData.hpp"
#include "LobbyData.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>

//#include <exception>

using std::vector;
using std::cout;
using std::endl;
using std::endl;
// A Client(computer/User) has a socket and the computer/network info, and it also contains a playerl... 
// im not sure if client should inherit from player, or if client should contain a player(composition)

// interesting resource on error handling and what it can and cannot do // https://stackoverflow.com/questions/23543417/catch-is-not-catching-an-exception-my-program-is-still-crashing

#define SERVER_PORT 53000
#define logl(x) cout << x << endl;
#define sysin(x, y) { cout << x << " : "; std::cin.ignore(); std::getline(std::cin, y); }; // I love this stuff
#define SERVER_ID 0

class Client {
public:
	//Client(sf::TcpSocket* socket = nullptr, int id = 0);
	Client(sf::Uint16 id = 65535, bool isHost = false); // could be 0 as well??

	//Client(Client& copy);

	// runs on start
	void run();

	void joinHost(unsigned short port = SERVER_PORT);

	void recieveStartInfo();

	// connects the client to a server, creates creates the socket connection
	void connect(const char* ip, unsigned short port); // this must be const char* and notr a string obj

	void sendPacket(sf::Packet& packet);

	void attemptServerConnection();

	// will tell the client if a new person joined their lobby
	void checkForNewPlayerConnected();

	void setId(sf::Uint16& temp) { this->mId = temp; } // put a &here, idk why

	sf::Uint16 getId() { return this->mId; }

	sf::TcpSocket& getSocket();

	bool recievePacket(sf::Packet& packet); 

protected:
	
	sf::TcpSocket mSocket; //  // comment to self:: mutualbetween client and server(middleman)

	sf::Packet lastPacket; // maybe need this?
	sf::Uint16 mId; // maybe make capslock??
	
private:
	bool mIsHost;

};

