#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string> 

#include "Item.hpp"

using std::string;

class Coin : public Item {
private:
	string textureName;

public:
	Coin() {
		textureName = "coinSprite.png";
		loadNewTexture(textureName);
		setSpriteTexture();
		changeSpriteScale({ 0.07, 0.07 });
	}



};