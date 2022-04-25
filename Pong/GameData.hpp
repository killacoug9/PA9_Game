#pragma once

//#include "Data.hpp"
//
//class GameData :
//    public Data
//{
//
//
//
//    GameData(sf::Packet& packet) : Data(packet) {
//        //packet >> move.x >> move.y >> pos.x >> pos.y >> isCaught;
//        if (packet >> mMove.x >> mMove.y >> mPos.x >> mPos.y >> mIsCaught >> mGamePaused) {
//
//        }
//        else {
//            logl("The data couldnt be de-serialized");
//        }
//    }
//
//    // was gonna do this but not yet
//    //void parse(sf::Packet& packet) {
//        //this->Data::parse(packet);
//       // packet >> 
//    //}
//
//    // data members // where it would be private
//        // I use Uint because SFML recconds it so that data isnt lost/corrupted between different systems
//    sf::Vector2f mMove;
//    sf::Vector2f mPos;
//    bool mIsCaught;
//    bool mGamePaused;
//
//};

