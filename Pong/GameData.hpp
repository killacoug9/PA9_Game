#pragma once

#include "Data.hpp"

class GameData :
    public Data
{

    GameData(sf::Packet& packet) : Data(packet) {
        //packet >> move.x >> move.y >> pos.x >> pos.y >> isCaught;
        if (packet >> move.x >> move.y >> pos.x >> pos.y >> isCaught) {

        }
        else {
            logl("The data couldnt be de-serialized");
        }
    }


    // data members // where it would be private
        // I use Uint because SFML recconds it so that data isnt lost/corrupted between different systems
    sf::Vector2f move;
    sf::Vector2f pos;
    bool isCaught;

};
