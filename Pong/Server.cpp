#include "Server.hpp"


Server::Server(int nPlayers, bool gActive) {
	// this is esentially start server(func/phase)..
		// you have an IP and Port.. you then let people connect to that, then when the host wants to start the game
		// you will go into the mode to read and transmit data between players, for x time or until a condition.
			// then you will enter the post match phase, or you will just go back to the lobby.
	this->mNumberOfPlayers = nPlayers;
	this->mGameActive = gActive;

	cout << "The servers IP is " << sf::IpAddress::getLocalAddress() << endl;// might need to do sf::IpAddress::getLocalAddress().toString()
}

void Server::run() {
	bool inLobby = true;
	bool keepListening = true;

	while (inLobby && keepListening) {
		keepListening = this->listenForConections();

	}
	
	// once we have all the connections.. when the game mstart is initiated we will go into second stage


}



void Server::lobbyOperations() {



}

void Server::runGameOperations() {

}

bool Server::listenForConections(){
	sf::TcpListener listenerSocket;
	listenerSocket.listen(SERVER_PORT);

	acceptConnection(listenerSocket);
	return false; // will need to be changed later
}

// return the true if the socket got connected succesfully
bool Server::acceptConnection(sf::TcpListener& listener) {
	// this is Tcp rn

	/*	Client* newClient = new Client();

	sf::TcpSocket client;

	while (true) {
		/*if (listener.accept(*(newClient->getSocket())) == sf::Socket::Done) {
				cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
				this->mClientVector.push_back(newClient);
			}
		/*if (listener.accept((newClient->getRefSocket())) == sf::Socket::Done) {
			cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
			this->mClientVector.push_back(newClient);
		}

	if (listener.accept(client) == sf::Socket::Done) {
		logl("A new client just connected from " << client.sf::TcpSocket::getRemoteAddress());

		this->mClientVector.push_back(newClient);
	}
	else {
		logl("A new client didnt connect");
	}
}*/

	// sf::TcpSocket client; // do i need to do this dynamically??
	Client* newClient = new Client();

	sf::TcpSocket client;

	while (true) {
		/*if (listener.accept(*(newClient->getSocket())) == sf::Socket::Done) {
				cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
				this->mClientVector.push_back(newClient);
			}*/
		/*if (listener.accept((newClient->getRefSocket())) == sf::Socket::Done) {
			cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
			this->mClientVector.push_back(newClient);
		}*/
		if (listener.accept(newClient->getSocket()) == sf::Socket::Done) {
			logl("A new client just connected from " << newClient->getSocket().sf::TcpSocket::getRemoteAddress()); // displays the clients Ip
			this->numPlayersPlusOne();
			newClient->setId(this->mNumberOfPlayers);
			
			this->mClientVector.push_back(newClient);
			sendInitInfo(*newClient);
			break;
		}
		else {
			logl("A new client didnt connect");
		}
	}

	return true;
}

void Server::sendInitInfo(Client& newClient) {
	sf::Packet newPacket;
	newPacket << 0 << newClient.getId() << false; // zero because the server ID is 0
	newClient.getSocket().send(newPacket);
}

void Server::numPlayersPlusOne() {
	this->mNumberOfPlayers += 1;
}