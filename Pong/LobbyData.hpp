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
    
    void parse(sf::Packet& packet) {
        Data::parse(packet);
        this->mMessage = "";
        if (packet >> mIsGameStarting >> mTimeTillStart >> mNumPlayers) {
            for (int i = 0; i < this->temp.getSize(); i++) {

                this->mMessage += (char)(*(this->temp.getData() + i));
                //this->mMessage = temp;
            }
        }
        else {
            logl("The data couldnt be de-serialized");
            //throw std::runtime_error("The data couldnt be de-serialized");
        }

    }

    // this is subject to change
    bool mIsGameStarting;
    sf::Int16 mTimeTillStart;
    sf::Uint16 mNumPlayers;
};

sf::Packet& operator<<(sf::Packet& lhs, LobbyData& rhs);

sf::Packet& operator>>(sf::Packet& lhs, LobbyData& rhs);



