#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
//#include <String.hpp>

using std::vector;
using std::cout;
using std::endl;
using std::endl;

#define logl(x) cout << x << endl;

//enum PacketDataType{
//	initPacket,
//	lobbyPacket,
//	gamePacket
//};


enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Data
{
	// can use sf::getDataSize() on the packet to see if its a lobby poacket or game packet??
public: // fuck it, imm just make it public because i dont wanna deal with setters and getter rn.. can change later
	
	Data(sf::Uint16 SenderId = 65535, sf::Uint16 RecipientId = 65535, bool GameActive = false , std::string Message = "", sf::String temp = "") {
		this->mSenderId = SenderId; 
		this->mRecipientId = RecipientId; 
		this->mGameActive = GameActive;
		this->mMessage = Message;
		this->temp = temp;
	}

	//Data() {
	//	this->mSenderId = 65535; //  65535 is the max value
	//	this->mRecipientId = 65535; // 65535
	//	this->mGameActive = false;
	//	this->mMessage = "The default constructor did this";
	//}
	
	Data(sf::Packet& packet) {
		this->parse(packet);
	}

	Data(Data& copy) {
		this->mSenderId = copy.mSenderId;
		this->mRecipientId = copy.mRecipientId;
		this->mGameActive = copy.mGameActive;
		this->mMessage = copy.mMessage;
		this->temp = copy.temp;
	}

	void parse(sf::Packet& packet) {
		this->mMessage = "";
		if (packet >> mSenderId >> mRecipientId >> mGameActive >> temp) {
			for (int i = 0; i < this->temp.getSize(); i++){

				this->mMessage += (char) (*(this->temp.getData() + i));
				//this->mMessage = temp;
			}
		}
		else {
			logl("The data couldnt be de-serialized");
			//throw std::runtime_error("The data couldnt be de-serialized");
		}

	}



	// data members // where it would be private
		// I use Uint because SFML recconds it so that data isnt lost/corrupted between different systems
		 
// i commented out the types so i could try it with C standard types

	//PacketDataType mType; // dont even know if i need this
	sf::Uint16 mSenderId;
	sf::Uint16 mRecipientId;
	bool mGameActive; // will tell them when to make game screen // conditional
	std::string mMessage; // random for testing
	sf::String temp;


};

sf::Packet& operator<<(sf::Packet& lhs, Data& rhs);

Data& operator>>(sf::Packet& lhs, Data& rhs);