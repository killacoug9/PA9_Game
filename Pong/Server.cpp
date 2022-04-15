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




void Server::listenForConections(){
	
	sf::TcpListener listenerSocket;
	listenerSocket.listen(SERVER_PORT);
	acceptConnection(listenerSocket);

	//if (listenerSocket.listen(SERVER_PORT) != sf::Socket::Done) { // the ==(and to the right of it) is incorrect but im doing this so it compiles
	//	acceptConnection(listenerSocket);
	//}
	
}

// return the true if the socket got connected succesfully
bool Server::acceptConnection(sf::TcpListener& listener) {
	// this is Tcp rn

	// sf::TcpSocket client; // do i need to do this dynamically??
	Client* newClient = new Client();

	while (true) {
		/*if (listener.accept(*(newClient->getSocket())) == sf::Socket::Done) {
				cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
				this->mClientVector.push_back(newClient);
			}*/
		if (listener.accept((newClient->getRefSocket())) == sf::Socket::Done) {
			cout << "A new client just connected from " << (newClient->getSocket())->sf::TcpSocket::getRemoteAddress() << endl;
			this->mClientVector.push_back(newClient);
		}
	}

	return true;
}