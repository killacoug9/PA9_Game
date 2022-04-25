#include "LobbyData.hpp"


sf::Packet& operator<<(sf::Packet& lhs, LobbyData& rhs) {
    lhs << rhs.mSenderId << rhs.mRecipientId << rhs.mGameActive << rhs.temp << rhs.mIsGameStarting << rhs.mTimeTillStart << rhs.mNumPlayers;
    //lhs << ((Data*) &rhs) << rhs.mIsGameStarting << rhs.mTimeTillStart << rhs.mNumPlayers;

    return lhs;
}


sf::Packet& operator>>(sf::Packet& lhs, LobbyData& rhs) {
    lhs >> rhs.mSenderId >> rhs.mRecipientId >> rhs.mGameActive >> rhs.temp >> rhs.mIsGameStarting >> rhs.mTimeTillStart >> rhs.mNumPlayers;
    //lhs >> rhs >> rhs.mIsGameStarting >> rhs.mTimeTillStart >> rhs.mNumPlayers;

    return lhs;
}
