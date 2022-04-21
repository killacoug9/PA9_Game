#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::endl;

#define logl(x) cout << x << endl;

class Data
{
	// can use sf::getDataSize() on the packet to see if its a lobby poacket or game packet??

public: // fuck it, imm just make it public because i dont wanna deal with setters and getter rn.. can change later
	Data(sf::Packet& packet) {
		if (packet >> mSenderId >> mRecipientId >> mMessage) {

		}
		else {
			logl("The data couldnt be de-serialized");
		}
		
	}

	//sf::Packet& operator<<(Data& rhs) {
	//	this << 
	//}

	// data members // where it would be private
		// I use Uint because SFML recconds it so that data isnt lost/corrupted between different systems
	sf::Uint8 mSenderId;
	sf::Uint8 mRecipientId;
		bool mGameActive; // will tell them when to make game screen // conditional
	std::string mMessage; // random for testing






};

