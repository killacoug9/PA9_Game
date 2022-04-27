#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
#include <string> 

using std::string;


class Item {
private:
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;

public:

	Item(const sf::Vector2f& newPos, const string textureLocation) {
		pos = newPos;
		texture.loadFromFile(textureLocation);
		sprite.setTexture(texture);
	}
	Item() = default;

	void setPos(const sf::Vector2f& newPos) {
		pos = newPos;

	}

	sf::FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}

	void changeSpriteScale(const sf::Vector2f& newSize) {
		sprite.setScale(newSize);
	}

	void loadNewTexture(const string newTexture) {
		texture.loadFromFile(newTexture);
	}

	void setSpriteTexture() {
		sprite.setTexture(texture);
	}

	void draw(sf::RenderTarget& rt) const {
		rt.draw(sprite);
	}

	void updateSprite() {
		sprite.setPosition(pos);
	}

	bool checkSpawn(const sf::Vector2f& newPos) {

		bool xValid = false, yValid = false, valid = false;
		int x = 0, y = 0;
		x = newPos.x;
		y = newPos.y;

		if (x % 4 == 0) {
			xValid = true;
		}
		if (y % 4 == 0) {
			yValid = true;
		}
		if (xValid == true && yValid == true) {
			valid = true;
		}
		return valid;
	}

	sf::Vector2f getPos() {
		return pos;
	}

	sf::Vector2i itemGridPos() {
		sf::Vector2i temp;
		temp.x = pos.x / 64;
		temp.y = pos.y / 64;
		return temp;
	}

	void deleteItem() {
		pos = { 1400, 900 };
		sprite.setColor(sf::Color::Black);
		updateSprite();
	}

	void spawn() {
		float x = 0, y = 0;
		bool valid = false;

		while (valid == false) {
			x = rand() % 21;
			y = rand() % 21;
			valid = checkSpawn({ x,y });
		}

		//setPos({ 7* 64.0f,4* 64.f });

		setPos({ x * 64.0f,y * 64.0f });
		updateSprite();
	}

};