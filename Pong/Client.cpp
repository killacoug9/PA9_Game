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

	//try { // getting a break here for some reason
	//	if (this->mSocket.connect(ip, port) != sf::Socket::Done) {
	//		logl("Could not connect to the server");
	//	}
	//	else {
	//		cout << "Connected to the server" << endl; // getting a breakpoint here when using logl();
	//	}
	//	
	//}
	//catch (...) {
	//	cout << "Exception thrown int the connect func" << endl;
	//}
	if (this->mSocket.connect(ip, port) != sf::Socket::Done) {
		logl("Could not connect to the server");
	}
	else {
		cout << "Connected to the server" << endl; // getting a breakpoint here when using logl();
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
	std::cin.clear();
	std::getline(std::cin, str);

	if (str != "...") { // this is to speed up debugging
		this->connect(str.c_str(), port);
	}
	else {
		
		this->connect("10.219.207.40", port);
	}

	this->recieveStartInfo();
	cout << "here" << endl;
}

void Client::recieveStartInfo() {
	sf::Packet packet;

	while (true) {
		if (this->mSocket.receive(packet) != sf::Socket::Done) {
			logl("Couldnt get the init info");
		}
		else {
			Data data(packet);// this fixed my first read access violation// moving it from in tyr to out of try
			try {
				
				//packet >> 0 >> newClient.getId() >> false;
				this->mId = data.mRecipientId;
				this->lastPacket = packet;
				logl("Client: The client recieved the init info");
				logl("The Id is " << (unsigned int)this->mId); // https://www.reddit.com/r/cpp/comments/t754ez/exception_transition_vso1269037_visual_studio_2019/
				cout << "sumn" << endl;
			}
			catch (std::runtime_error& e) {
				logl("Runtime Exception: " << e.what() << " thrown.");
			}
			catch (std::exception& e1) {
				logl("General Exception: " << e1.what() << " thrown.");
			}
			logl("here before");
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