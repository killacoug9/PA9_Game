#pragma once

#include "Data.hpp"

class GameData :
    public Data
{

public:

    GameData() : Data() {
        this->mMove = {};
        this->mPos = {};
        this->mIsCaught = false;
        this->mGamePaused = false;
        this->mDirection = NORTH;
    }

    GameData(sf::Vector2f move, sf::Vector2f pos, bool isCaught = false, bool gamePaused = false, Direction direc = NORTH, sf::Uint16 SenderId = 0, sf::Uint16 RecipientId = 0, bool GameActive = false, std::string Message = "", sf::String temp = "")
        : Data(SenderId, RecipientId, GameActive, Message, temp)
    {
        this->mMove = move;
        this->mPos = pos;
        this->mIsCaught = isCaught;
        this->mGamePaused = gamePaused;
        this->mDirection = direc;

    }

    GameData(sf::Packet& packet) : Data(packet) {
        //packet >> move.x >> move.y >> pos.x >> pos.y >> isCaught;
        if (packet >> mMove.x >> mMove.y >> mPos.x >> mPos.y >> mIsCaught >> mGamePaused, mDirection) {

        }
        else {
            logl("The data couldnt be de-serialized");
        }
    }

    // was gonna do this but not yet
    //void parse(sf::Packet& packet) {
        //this->Data::parse(packet);
       // packet >> 
    //}

    // data members // where it would be private
        // I use Uint because SFML recconds it so that data isnt lost/corrupted between different systems
    sf::Vector2f mMove;
    sf::Vector2f mPos;
    bool mIsCaught;
    bool mGamePaused;
    Direction mDirection;

};

sf::Packet& operator<<(sf::Packet& lhs, GameData& rhs);

GameData& operator>>(sf::Packet& lhs, GameData& rhs);