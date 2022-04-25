#include "Client.hpp"


//Client::Client(/*std::unique_ptr<sf::TcpSocket> socket,*/ int id)



Client::Client(sf::Uint16 id, bool isHost) {
	/*if (socket == nullptr) {
		sf::TcpSocket socket;
		this->mSocket = *(std::unique_ptr<sf::TcpSocket>)&socket;
	}
	else {
		this->mSocket = &socket;
	}*/
	
	this->mId = id;
	this->mIsHost = isHost;
}

//Client::Client(Client& copy) {
//	// idk if this will work cause Sockets cant be copied
//
//}

void Client::run() {

	// ------------ ON EVENT(Join) --------- (maybe??)
	if (true) 
		this->joinHost(); // this joins and get init Info
	
	this->mSocket.setBlocking(false); // ??? idk if i should set it non blockin but if i dont i think id have to multithread
	
	// ~~~~~~ this is just running(waiting) till game starts ~~~~
	sf::Packet packet;

	do {

		// recieve packet
		LobbyData data;
		try {
			if (recievePacket(packet)) {	// if server sent a lobby packet
				
				this->lastPacket = packet;
				packet >> data;

				if (data.mIsGameStarting) {  // could do something here but idrk yet
					//data.mTimeTillStart;
				}
			}
		}
		catch (std::runtime_error& e) {
			cout << "Exception: " << e.what() << endl;
		}
		


		// display screen // (screen possibly has a timer at top based off time till start?)


		// if game started then 
		if (data.mIsGameStarting && data.mTimeTillStart <= 0) {  // could do something here but idrk yet
			break;
		}

	} while (true);


	// load match

	


}

// if a packet is recieved it returns true
bool Client::recievePacket(sf::Packet& packet) {

	if (this->mSocket.receive(packet) == sf::Socket::Done) {
		return true;
	}
	else {
		throw std::runtime_error("No packet to recieve");
	}

}

//((*this->mSocket)->connect())
//((this->mSocketR)->connect())
//if (((*mSocket))->connect(ip, port) != sf::Socket::Done) {
void Client::connect(const char* ip, unsigned short port) {
	std::string temp = ip;
	cout << "Client is trying to connect to " << temp << " through port " << port << "...." << endl;
	//try { // getting a break here for some reason
	//	if (this->mSocket.connect(ip, port) != sf::Socket::Done) {
	//		logl("Could not connect to the server");
	//	}
	//	else {
	//		cout << "Connected to the server" << endl; // getting a breakpoint here when using logl();
	//	}
	//}
	//catch (...) {
	//	cout << "Exception thrown int the connect func" << endl;
	//}

	//if (this->mSocket.connect(ip, port) != sf::Socket::Done) {
	//	logl("Could not connect to the server");
	//}
	//else {
	//	cout << "Connected to the server" << endl; // getting a breakpoint here when using logl();
	//}

	if (this->mSocket.connect(ip, port) == sf::Socket::Done) {
		cout << "Connected to the server" << endl; // getting a breakpoint here when using logl();
	}
	else {
		logl("Could not connect to the server");
	}

} // 


void Client::sendPacket(sf::Packet& packet) {
	if (!(this->mSocket.isBlocking())) { // if its non-blocking then
		if (this->mSocket.send(packet) == sf::Socket::Partial) { // if its partial then you MUST try sending the packet agian
			this->sendPacket(packet); // so ill send again
		}
	} 
	else if (this->mSocket.send(packet) != sf::Socket::Done) { // otherwise just send it
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
	cout << "please type in the IP address of the host: "; // << endl;
	
	std::cin.ignore(); // or i can use // std::cin.clear(); std::cin.sync(); // this is because I use cin earlier so i messes up getline.. i prob shgould go back and change the cin to getlines
	std::getline(std::cin, str);

	if (str == "..." || str == "" || str == "\n") { // this is to speed up debugging
		this->connect("10.219.207.40", port);
	}
	else {
		this->connect(str.c_str(), port);
		
	}

	this->recieveStartInfo();
	logl("Client recieved initilization information.");
}

void Client::recieveStartInfo() {
	sf::Packet packet;
	while (true) { // i switched the conditions(apr 22 1:24pm)
		if (this->mSocket.receive(packet) == sf::Socket::Done) {
			//  \/ If an exception is thrown by the destructor of an object that is destroyed as a result of the stack unwinding to handle a different exception, the program will exit-(See link for exc handl. in client.hpp)
			Data data(packet);// this fixed my first read access violation// moving it from in try to out of try

			try { // look at client.hpp for good exception handling link
				this->mId = data.mRecipientId;
				this->lastPacket = packet;
				logl("Your client Id is " << this->mId);	// https://www.reddit.com/r/cpp/comments/t754ez/exception_transition_vso1269037_visual_studio_2019/

			}
			catch (std::runtime_error& e) {
				logl("Runtime Exception: " << e.what() << " thrown.");
			}
			catch (std::exception& e1) {
				logl("General Exception: " << e1.what() << " thrown.");
			}
			break; //  // while debugging(1:17 pm Apr 22) i stepped into this func and it gavce me "Exception thrown PA9_Game.exe has triggered a breakpoint." at line 46(client.cpp) at the cout << connected to srvr << endl;
			// (Apr 22 1:44pm) Im getting the error again // HEAP[PA9_Game.exe]: Invalid address specified to RtlValidateHeap( 00D90000, 00DB24E0 ) ::: PA9_Game.exe has triggered a breakpoint // at line 50
			// possible helpful link ^^^^^ https://stackoverflow.com/questions/1007188/rtlvalidateheap-problem
			// \/ Here are the debug console outputs.. Notable things are that it says "Module was built without symbols." for the network module so im not sure what that means	
		}
		else {
			logl("Couldnt get the initilization info");
		}
	}
}


//std::unique_ptr<sf::TcpSocket>& Client::getRefSocket() {
//	return *this->mSocket;
//}

sf::TcpSocket& Client::getSocket() {
	return this->mSocket;
}