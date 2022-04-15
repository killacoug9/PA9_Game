#pragma once

#include <SFML/Graphics.hpp>
 


class PlayerEntity {
public:
	PlayerEntity();

	// drawSelf();



private:
	sf::Vector2f pos;
	bool is_visible;
	float movementSpeed;


};

