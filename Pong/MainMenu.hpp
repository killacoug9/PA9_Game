#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>

#define MAX_MAIN_MENU 3

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

class MainMenu {
public:
	MainMenu(float width, float height);

	void drawTextButtons(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	void runMenuScreen(sf::RenderWindow& window, sf::Event& event);

	sf::RectangleShape& getBackgroundPicture() { return background; }

	~MainMenu();
private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[MAX_MAIN_MENU];

	//photo to main menu background
	sf::RectangleShape background;	
	sf::Texture mainBackground;
	
};


void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight);

int func();