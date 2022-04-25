#include "Data.hpp"

sf::Packet& operator<<(sf::Packet& lhs, Data& rhs) {
	lhs << rhs.mSenderId << rhs.mRecipientId << rhs.mGameActive << rhs.temp;
	return lhs;
}

Data& operator>>(sf::Packet& lhs, Data& rhs) {
	lhs >> rhs.mSenderId >> rhs.mRecipientId >> rhs.mGameActive >> rhs.temp;

	return rhs;
}