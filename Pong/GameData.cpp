#include "GameData.hpp"


sf::Packet& operator<<(sf::Packet& lhs, GameData& rhs) {
	lhs << rhs.mSenderId << rhs.mRecipientId << rhs.mGameActive << rhs.temp << rhs.mMove.x << rhs.mMove.y << rhs.mPos.x << rhs.mPos.y << rhs.mIsCaught << rhs.mGamePaused << rhs.mDirection;
	return lhs;
}

GameData& operator>>(sf::Packet& lhs, GameData& rhs) {
	int dir;
	lhs >> rhs.mSenderId >> rhs.mRecipientId >> rhs.mGameActive >> rhs.temp >> rhs.mMove.x >> rhs.mMove.y >> rhs.mPos.x >> rhs.mPos.y >> rhs.mIsCaught >> rhs.mGamePaused >> dir;
	rhs.mDirection = (Direction) dir;

	return rhs;
}