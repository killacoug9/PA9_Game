#include "Client.hpp"


//Client::Client(/*std::unique_ptr<sf::TcpSocket> socket,*/ int id)

Client::Client(int id) {
	/*if (socket == nullptr) {
		sf::TcpSocket socket;
		this->mSocket = *(std::unique_ptr<sf::TcpSocket>)&socket;
	}
	else {
		this->mSocket = &socket;
	}*/
	
	this->mId = id;
}

//Client::Client(Client& copy) {
//	// idk if this will work cause Sockets cant be copied
//
//}


//((*this->mSocket)->connect())
//((this->mSocketR)->connect())
//if (((*mSocket))->connect(ip, port) != sf::Socket::Done) {
void Client::connect(const char* ip, unsigned short port) {
	if (this->mSocketR.connect(ip, port) != sf::Socket::Done) {
		logl("Could not connect to the server");
	}
	else {
		logl("Connected to the server");
	}
}

void Client::attemptServerConnection() {

}

// will tell the client if a new person joined their lobby
void Client::checkForNewPlayerConnected() {

}


std::unique_ptr<sf::TcpSocket>& Client::getRefSocket() {
	return *this->mSocket;
}