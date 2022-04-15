#include "Client.hpp"

//Client::Client(sf::TcpSocket* socket, int id) {
Client::Client(std::unique_ptr<sf::TcpSocket> socket, int id) {
	this->mSocket = &socket;
	this->mId = id;
}

//Client::Client(Client& copy) {
//	// idk if this will work cause Sockets cant be copied
//
//}

void Client::attemptServerConnection() {

}

// will tell the client if a new person joined their lobby
void Client::checkForNewPlayerConnected() {

}

// sf::Socket might need to become TcpSocket, we'll see
//sf::TcpSocket* Client::getSocket() {
//	return this->mSocket;
//}

std::unique_ptr<sf::TcpSocket>& Client::getRefSocket() {
	return *this->mSocket;
}