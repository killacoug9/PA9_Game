#include "Server.hpp"


Server::Server() {
	// this is esentially start server(func/phase)..
		// you have an IP and Port.. you then let people connect to that, then when the host wants to start the game
		// you will go into the mode to read and transmit data between players, for x time or until a condition.
			// then you will enter the post match phase, or you will just go back to the lobby.


	cout << "The servers IP is " << sf::IpAddress::getLocalAddress() << endl;// migfht need to do sf::IpAddress::getLocalAddress().toString()

}




void Server::listenForConections(){
	
	sf::TcpListener listenerSocket;

	if (listenerSocket.listen(SERVER_PORT) == sf::Socket::Done) { // the ==(and to the right of it) is incorrect but im doing this so it compiles
		acceptConnection(listenerSocket);
	}
	
}

// return the true if the socket got connected succesfully
bool Server::acceptConnection(sf::TcpListener& listener) {
	// this is Tcp rn

	sf::TcpSocket client; // do i need to do this dynamically??
	if (listener.accept(client) == sf::Socket::Done) {
		cout << "A new client just connected from " << client.getRemoteAddress() << endl;
		this->clientVector.push_back(client);
	}
}