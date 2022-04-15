#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::endl;
// A Client(computer/User) has a socket and the computer/network info, and it also contains a playerl... 
// im not sure if client should inherit from player, or if client should contain a player(composition)

class Client {
public:
	Client(sf::TcpSocket* socket = nullptr, int id = 0);

	//Client(Client& copy);

	void attemptServerConnection();

	// will tell the client if a new person joined their lobby
	void checkForNewPlayerConnected();

	sf::TcpSocket* getSocket();

	sf::TcpSocket& getRefSocket();

private:
	//sf::TcpSocket socket; // if i use this then it wont be able to have getteres cause it cant be copied and no copy constructor
	sf::TcpSocket* mSocket;
	//std::unique_ptr<sf::TcpSocket> socket;
	int mId; // maybe make capital??
	

};

