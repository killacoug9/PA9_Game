#pragma once

#include "Data.hpp"

class LobbyData :
    public Data
{

public:
    LobbyData() : Data() {
        this->mIsGameStarting = false;
        this->mTimeTillStart = -1;
        sf::Uint8 mNumPlayers = 1;
    }



    LobbyData(sf::Packet& packet) : Data(packet) {
        //packet >> mIsGameStarting >> mTimeTillStart >> mNumPlayers;
        if (packet >> mIsGameStarting >> mTimeTillStart >> mNumPlayers) {

        }
        else {
            logl("The data couldnt be de-serialized");
        }

    }
    

    // this is subject to change
    bool mIsGameStarting;
    sf::Int16 mTimeTillStart;
    sf::Uint16 mNumPlayers;
};

sf::Packet& operator<<(sf::Packet& lhs, LobbyData& rhs) {
    lhs << rhs.mSenderId << rhs.mRecipientId << rhs.mGameActive << rhs.temp << rhs.mIsGameStarting << rhs.mTimeTillStart << rhs.mNumPlayers;
    return lhs;
}

