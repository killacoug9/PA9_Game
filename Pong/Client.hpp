#pragma once

#include <SFML/Network.hpp>

// A Client(computer/User) has a socket and the computer/network info, and it also contains a playerl... 
// im not sure if client should inherit from player, or if client should contain a player(composition)

class Client {
public:
	Client();

	Client(Client& copy);

	void attemptServerConnection();

	// will tell the client if a new person joined their lobby
	void checkForNewPlayerConnected();


private:
	sf::TcpSocket socket;
	int id; // maybe make capital??
	

};

