#include "Server.hpp"



Server::Server(int nPlayers, bool gActive, bool gameJoinable) {
	// this is esentially start server(func/phase)..
		// you have an IP and Port.. you then let people connect to that, then when the host wants to start the game
		// you will go into the mode to read and transmit data between players, for x time or until a condition.
			// then you will enter the post match phase, or you will just go back to the lobby.
	this->mNumberOfPlayers = nPlayers;
	this->mGameActive = gActive;
	this->mGameJoinable = gameJoinable;

	cout << "The servers IP is " << sf::IpAddress::getLocalAddress() << endl;// might need to do sf::IpAddress::getLocalAddress().toString()
}

Server::~Server() {
	for (int i = 0; i < this->mClientVector.size(); i++)
	{
		delete this->mClientVector.at(i);
	}
	logl("Deleted Server Obj");
}



void Server::run() {
	
	bool& allowJoin = this->mGameJoinable;

	// start one thread to allow for and accept people to join game, and in another thread allow the host to stop searching with user input and end the game

	std::thread threadl(&Server::letPeopleJoin, this, std::ref(allowJoin));


	do {
		int counter = 0;
		std::string temp;
		if (!(counter % 25)) { // so it doesnt spam the console
			sysin("do you still want people to be able to join?", temp);
			if (temp == "n") {
				allowJoin = false;
			}
		}
		counter++;
	} while (allowJoin);

	if (threadl.joinable()) {
		threadl.join(); // shouldnt need this but whatever
	}

	///; ------------- On Event(host clicks start) ------------
	LobbyData data = LobbyData(true, DEFAULT_START_TIME, mNumberOfPlayers, SERVER_ID);

	messageAllClients(&data); // send a lobby packet saying the game is about to starts;


	
	// once we have all the connections.. when the game mstart is initiated we will go into second stage
	while (true) {
		logl("playing game");
	}

}

// func that makes lobby open to joining, kinda
void Server::letPeopleJoin(bool& allowJoin) {
	bool inLobby = true;

	while (inLobby && allowJoin) {
		this->listenForConections();
	}
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
			onClientConnect(newClient); // displays the clients Ip
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
	sf::Uint16 serverId = 0;	// zero because the server ID is 0

	sf::String temp = "You got initilized!!!";
	cout << "Server:: about to send packet to client";
	newPacket << serverId << newClient.getId() << false << temp; 

	newClient.sendPacket(newPacket);
}

void Server::onClientConnect(Client*& newClient) { // a option message when someone connects
	logl("[SERVER] New Connection from : " << newClient->getSocket().sf::TcpSocket::getRemoteAddress()); // displays the clients Ip
}

// data* so that not only can i use polymorphism, but also so that i can change the packet data between who isend it to
void Server::messageAllClients(Data* data) {

	sf::Packet packet;

	for (int i = 0; i < this->mClientVector.size(); i++)
	{
		data->mRecipientId = this->mClientVector.at(i)->getId();
		packet << *data;
		this->mClientVector.at(i)->sendPacket(packet);
	}
}

void Server::numPlayersPlusOne() {
	this->mNumberOfPlayers += 1;
}