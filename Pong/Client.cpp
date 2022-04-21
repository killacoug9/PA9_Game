#include "Client.hpp"


//Client::Client(/*std::unique_ptr<sf::TcpSocket> socket,*/ int id)

Client::Client(sf::Uint8 id) {
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

void runGame();

//((*this->mSocket)->connect())
//((this->mSocketR)->connect())
//if (((*mSocket))->connect(ip, port) != sf::Socket::Done) {
void Client::connect(const char* ip, unsigned short port) {
	if (this->mSocket.connect(ip, port) != sf::Socket::Done) {
		logl("Could not connect to the server");
	}
	else {
		logl("Connected to the server");
	}
} // 

void Client::sendPacket(sf::Packet& packet) {
	if (this->mSocket.send(packet) != sf::Socket::Done) {
		logl("Could not send packet");
	}
}



void Client::attemptServerConnection() {
	// not sure what this func should do but ok.. // -Kyle

	

}

// will tell the client if a new person joined their lobby
void Client::checkForNewPlayerConnected() {

}


void Client::joinHost(unsigned short port) {
	const char* tempIp;
	std::string str;
	cout << "please type in the IP address of the host" << endl;
	//std::getline(std::cin, tempIp);
	std::getline(std::cin, str);

	this->connect(str.c_str(), port);

	this->recieveStartInfo();
}

void Client::recieveStartInfo() {
	sf::Packet packet;

	while (true) {
		if (this->mSocket.receive(packet) != sf::Socket::Done) {
			logl("Couldnt get the init info");
		}
		else {
			
			Data data(packet);
			//packet >> 0 >> newClient.getId() >> false;
			this->mId = data.mRecipientId;
			this->lastPacket = packet;
			logl("Client: The client recieved the init info");
			logl("The Id is " << this->mId);
			break;
		}
	}
	
}


//std::unique_ptr<sf::TcpSocket>& Client::getRefSocket() {
//	return *this->mSocket;
//}

sf::TcpSocket& Client::getSocket() {
	return this->mSocket;
}