#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
#include <Windows.h>
#include <windows.h> 
#include <excpt.h>

#include "Server.hpp"

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

	void allowJoinLoopMember(Server& server, sf::RenderWindow& window, sf::Event& event);

	void runMenuScreen(sf::RenderWindow& window, sf::Event& event);

	sf::RectangleShape& getBackgroundPicture() { return background; }

	void drawOtherPlayers(sf::RenderWindow& window);

	void updateOtherPlayers();

	void setMainMenuText(std::string one, std::string two, std::string three){
		this->mainMenu[0].setString(one);
		this->mainMenu[1].setString(two);
		this->mainMenu[2].setString(three);
	}

	~MainMenu();
private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[MAX_MAIN_MENU];

	//photo to main menu background
	sf::RectangleShape background;	
	sf::Texture mainBackground;
	
};

void textArrSetProperties(sf::Text* mainMenu[3], std::string strArr[3], sf::Font& font);

void allowJoinLoop(Server& server, sf::RenderWindow& window, sf::Event event, sf::Text* optionsArr[3]);

void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight, Client& client, std::vector<Client>& playerList);

int func();