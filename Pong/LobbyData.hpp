#pragma once

#include "Data.hpp"

#define DEFAULT_START_TIME 10

class LobbyData : public Data
{

public:
    LobbyData(bool gameStarting = false, sf::Int16 ttS = 999, sf::Uint16 numPlayers = 1, sf::Uint16 SenderId = 0, sf::Uint16 RecipientId = 0, bool GameActive = false, std::string Message = "", sf::String temp = "")
        : Data(SenderId, RecipientId, GameActive, Message, temp) 
    {
        this->mIsGameStarting = gameStarting;
        this->mTimeTillStart = ttS;
        this->mNumPlayers = numPlayers;
    }

 /*   LobbyData() : Data() {
        this->mIsGameStarting = false;
        this->mTimeTillStart = 999;
        this->mNumPlayers = 1;
    }*/

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

LobbyData& operator>>(sf::Packet& lhs, LobbyData& rhs) {
    lhs >> rhs.mSenderId >> rhs.mRecipientId >> rhs.mGameActive >> rhs.temp >> rhs.mIsGameStarting >> rhs.mTimeTillStart >> rhs.mNumPlayers;

    return rhs;
}



