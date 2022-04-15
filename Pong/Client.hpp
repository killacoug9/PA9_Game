#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::endl;
// A Client(computer/User) has a socket and the computer/network info, and it also contains a playerl... 
// im not sure if client should inherit from player, or if client should contain a player(composition)

#define logl(x) cout << x << endl;

class Client {
public:
	//Client(sf::TcpSocket* socket = nullptr, int id = 0);
	Client(int id = 0);

	//Client(Client& copy);

	void connect(const char* ip, unsigned short port); // this must be const char* and notr a string obj



	void attemptServerConnection();

	// will tell the client if a new person joined their lobby
	void checkForNewPlayerConnected();

	std::unique_ptr<sf::TcpSocket>& getRefSocket();

	//std::unique_ptr<sf::TcpSocket>& getSocket();

private:
	//sf::TcpSocket socket; // if i use this then it wont be able to have getteres cause it cant be copied and no copy constructor
	
	std::unique_ptr<sf::TcpSocket>* mSocket; // this is ptr to ptr
	sf::TcpSocket mSocketR;

	//std::unique_ptr<sf::TcpSocket>& mSocket; // this is ptr to reference
	sf::Packet lastPacket; // maybe need this?
	int mId; // maybe make capslock??
	

};

