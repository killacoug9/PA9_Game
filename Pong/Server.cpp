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



void Server::run(sf::Thread* thread) {

	// start one thread to allow for and accept people to join game, and in another thread allow the host to stop searching with user input and end the game

	//sf::Thread threadl(&Server::run, this);

	thread = new sf::Thread(&Server::letPeopleJoin, this);
	thread->launch();

	//std::thread threadl(&Server::letPeopleJoin, this, std::ref(allowJoin));
	 
	//do {
	//	int counter = 0;
	//	std::string temp;
	//	if (!(counter % 25)) { // so it doesnt spam the console
	//		sysin("do you still want people to be able to join?", temp);
	//		if (temp == "n") {
	//			allowJoin = false;
	//		}
	//	}
	//	counter++;
	//} while (allowJoin);
	 
	while (this->getGameJoinable()) {
		//cout << "WHy exut" << this->getGameJoinable() << endl;
		Sleep(500);
	}

	cout << "terminating thread" << endl;
	thread->terminate();

	//if (threadl.joinable()) {
	//	threadl.join(); // shouldnt need this but whatever
	//}

	// for now i cab just put this goofily in main and 

	Sleep(2000);

	sf::Uint16 strtTemp = 10;

	///; ------------- On Event(host clicks start) ------------
	//LobbyData data(true, DEFAULT_START_TIME, mNumberOfPlayers, SERVER_ID);
	LobbyData someData(true, strtTemp, mNumberOfPlayers, SERVER_ID);
	//LobbyData someData(true, DEFAULT_START_TIME, mNumberOfPlayers, SERVER_ID);

	//cout << "stris" << someData.mIsGameStarting << "ttsserver" << someData.mTimeTillStart << endl;
	//this->messageAllClients(&someData); // send a lobby packet saying the game is about to starts;
	this->messageAllClients(someData); // send a lobby packet saying the game is about to starts;
	
	// once we have all the connections.. when the game mstart is initiated we will go into second stage
	this->mGameActive = true;

	//for (int i = 0; i < this->mClientVector.size(); i++)
	//{
	//	this->mClientVector.at(i)->getSocket().setBlocking(false);

	//}

	sf::Packet packet;
	GameData gameDataTemp;
	while (this->mGameActive) {
		
		for (int i = 0; i < this->mClientVector.size(); i++)
		{
			try {
				if (recievePacket(this->mClientVector.at(i)->getSocket(), packet)) {
					packet >> gameDataTemp;
					messageAllClients(gameDataTemp);
				}
			}
			catch (std::runtime_error& e) {
				cout << "[Server] Exception: " << e.what() << endl;
			}
		}

	}
	

}

bool Server::recievePacket(sf::TcpSocket& sock, sf::Packet& packet) {
	if (sock.receive(packet) == sf::Socket::Done) {
		return true;
	}
	else {
		throw std::runtime_error("No packet to recieve");
	}
}


// func that makes lobby open to joining, kinda
void Server::letPeopleJoin() {

	while (this->getGameJoinable()) {
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
			break;
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

 //data* so that not only can i use polymorphism, but also so that i can change the packet data between who isend it to
void Server::messageAllClients(Data* data) {

	sf::Packet packet;

	for (int i = 0; i < this->mClientVector.size(); i++)
	{
		data->mRecipientId = this->mClientVector.at(i)->getId();

		packet << data; // this is so annyoing
		//packet << data->mSenderId << data->mRecipientId << data->mGameActive << data->temp;

		this->mClientVector.at(i)->sendPacket(packet);
	}
}

void Server::messageAllClients(LobbyData& data) {

	sf::Packet packet;

	for (int i = 0; i < this->mClientVector.size(); i++)
	{
		data.mRecipientId = this->mClientVector.at(i)->getId();

		packet << data; // this is so annyoing
		//packet << data->mSenderId << data->mRecipientId << data->mGameActive << data->temp;

		this->mClientVector.at(i)->sendPacket(packet);
	}
}

void Server::messageAllClients(GameData& data) {

	sf::Packet packet;

	for (int i = 0; i < this->mClientVector.size(); i++)
	{
		data.mRecipientId = this->mClientVector.at(i)->getId();

		packet << data; // this is so annyoing
		//packet << data->mSenderId << data->mRecipientId << data->mGameActive << data->temp;

		this->mClientVector.at(i)->sendPacket(packet);
	}
}

////data* so that not only can i use polymorphism, but also so that i can change the packet data between who isend it to
//void Server::messageAllClients(LobbyData& data) {
//
//	sf::Packet packet;
//
//	for (int i = 0; i < this->mClientVector.size(); i++)
//	{
//		data.mRecipientId = this->mClientVector.at(i)->getId();
//
//		packet << data; // this is so annyoing
//		//packet << data->mSenderId << data->mRecipientId << data->mGameActive << data->temp;
//
//		this->mClientVector.at(i)->sendPacket(packet);
//	}
//}


void Server::numPlayersPlusOne() {
	this->mNumberOfPlayers += 1;
}