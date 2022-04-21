#pragma once

#include <SFML/Network.hpp>
#include "GameData.hpp"
#include "LobbyData.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::endl;
// A Client(computer/User) has a socket and the computer/network info, and it also contains a playerl... 
// im not sure if client should inherit from player, or if client should contain a player(composition)

#define SERVER_PORT 53000
#define logl(x) cout << x << endl;

class Client {
public:
	//Client(sf::TcpSocket* socket = nullptr, int id = 0);
	Client(sf::Uint8 id = 0);

	//Client(Client& copy);

	void joinHost(unsigned short port = SERVER_PORT);

	void recieveStartInfo();

	// connects the client to a server, creates creates the socket connection
	void connect(const char* ip, unsigned short port); // this must be const char* and notr a string obj

	void sendPacket(sf::Packet& packet);

	void attemptServerConnection();

	// will tell the client if a new person joined their lobby
	void checkForNewPlayerConnected();

	void setId(sf::Uint8 temp) { this->mId = temp; }

	sf::Uint8 getId() { return this->mId; }

	sf::TcpSocket& getSocket();

private:
	//sf::TcpSocket socket; // if i use this then it wont be able to have getteres cause it cant be copied and no copy constructor
	
	//std::unique_ptr<sf::TcpSocket>* mSocket; // this is ptr to ptr
	sf::TcpSocket mSocket; //  // comment to self:: mutualbetween client and server(middleman)

	//std::unique_ptr<sf::TcpSocket>& mSocket; // this is ptr to reference
	sf::Packet lastPacket; // maybe need this?
	sf::Uint8 mId; // maybe make capslock??
	

};

