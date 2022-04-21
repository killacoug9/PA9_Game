#pragma once

#include "Data.hpp"

class LobbyData :
    public Data
{
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
    sf::Int8 mTimeTillStart;
    sf::Uint8 mNumPlayers;


};

