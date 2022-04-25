#include"MainMenu.hpp"
#include"character.hpp"


MainMenu::MainMenu(float width, float height) {
	
	if (!font.loadFromFile("Fonts/Freedom.ttf")) {
		std::cout << "could not load font\n";
	}
		
	//Host
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Black);
	mainMenu[0].setString("Host");
	mainMenu[0].setCharacterSize(64);
	mainMenu[0].setPosition(150, 300);
	//join
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Black);
	mainMenu[1].setString("Join");
	mainMenu[1].setCharacterSize(64);
	mainMenu[1].setPosition(150, 375);
	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Black);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(64);
	mainMenu[2].setPosition(150, 450);

	MainMenuSelected = -1;

	// this makes the picture dude background
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	mainBackground.loadFromFile("Textures/HideAndSeek.png");
	background.setTexture(&mainBackground);
}

MainMenu::~MainMenu(){

}

void MainMenu::drawTextButtons(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_MAIN_MENU; i++) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Black);

		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Green);
	}
}

void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= MAX_MAIN_MENU) {

		mainMenu[MainMenuSelected].setFillColor(sf::Color::Black);

		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Green);
	}
}

void MainMenu::runMenuScreen(sf::RenderWindow& window, sf::Event& event) {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::W) {
				this->MoveUp();
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::S) {
				this->MoveDown();
				break;
			}
		}

		if (event.key.code == sf::Keyboard::Return) {



			int x = this->MainMenuPressed();
			if (x == 0) {
				sf::RenderWindow Host(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Host Menu");

				runGame(Host, WINDOW_WIDTH, WINDOW_HEIGHT);

			}
			if (x == 1) {
				sf::RenderWindow Join(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Join Menu");
				while (Join.isOpen()) {
					sf::Event aevent;
					while (Join.pollEvent(aevent)) {
						if (aevent.type == sf::Event::Closed) {
							Join.close();
						}

					}

					Join.clear();
					Join.display();
				}
			}
			if (x == 2) {
				window.close();
				break;
			}
		}
	}
}


void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight) {
	
	//init game 
	float gridSizeF = 64.f;
	unsigned girdSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/Arial.ttf");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Green);
	text.setFont(font);
	text.setPosition(20.f, 20.f);
	text.setString("Test");

	//init window

	window.setFramerateLimit(120);

	sf::View view;
	
	view.setSize(windowWidth, windowHeight);

	
	//view center is like spawn point
	view.setCenter(0, 0);
	float viewSpeed = 300.f;//how fast the view moves like move speed
	
	const int mapSize = 20;//20 x 20 tiles
	//init game elements
	
	sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

	shape.setFillColor(sf::Color::Blue);
	
	//map
	std::vector<std::vector<sf::RectangleShape>> tileMap;

	tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

	for (int x = 0; x < mapSize; x++)
	{
		tileMap[x].resize(mapSize, sf::RectangleShape());
		for (int y = 0; y < mapSize; y++)
		{

			tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
			tileMap[x][y].setFillColor(sf::Color::White);
			tileMap[x][y].setOutlineThickness(1.f);
			tileMap[x][y].setOutlineColor(sf::Color::Black);
			tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
		}
	}


	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0;

	//character
	//int half_Sprite_x = 0, half_sprite_y = 0;
	bool keyPress = false;

	//create sprite

	Character model({ float(window.getSize().x) / 2 - 32 ,float(window.getSize().y) / 2 - 32 });

	//timepoint for delta time measurement
	auto tp = std::chrono::steady_clock::now();

	//tile selctor
	//sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));

	//tileSelector.setFillColor(sf::Color::Transparent);
	//tileSelector.setOutlineThickness(1.f);
	//tileSelector.setOutlineColor(sf::Color::Green);

	while (window.isOpen())
	{
		//Update dt
		dt = dtClock.restart().asSeconds();

		//update mouse positions
		mousePosScreen = sf::Mouse::getPosition();
		mousePosWindow = sf::Mouse::getPosition(window);

		window.setView(view);
		mousePosView = window.mapPixelToCoords(mousePosWindow);
		
		//if (mousePosView.x >= 0.f) {
		//	mousePosGrid.x = mousePosView.x / gridSizeF;
		//}
		//if (mousePosView.y >= 0.f) {
		//	mousePosGrid.y = mousePosView.y / gridSizeF;
		//}

		window.setView(window.getDefaultView());
		//update game elements
		//tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

		sf::Vector2f dir = { 0.0, 0.0 };

		////update ui
		//std::stringstream ss;
		//ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		//	<< "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		//	<< "View: " << mousePosView.x << " " << mousePosView.y << "\n"
		//	<< "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
		//text.setString(ss.str());

		//events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		//update
		//update input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
			//view.mMove(-viewSpeed * dt, 0.f);
			view.move(-viewSpeed * dt, 0.f);
			//character
			dir.x -= 1.0;
			keyPress = true;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Right
			//view.mMove(viewSpeed * dt, 0.f);
			view.move(viewSpeed * dt, 0.f);

			dir.x += 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//Up
			//view.mMove(0.f, -viewSpeed * dt);
			view.move(0.f, -viewSpeed * dt);

			dir.y -= 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Down
			//view.mMove(0.f, viewSpeed * dt);
			view.move(0.f, viewSpeed * dt);

			dir.y += 1.0;
			keyPress = true;
		}
		if (keyPress == true) {
			model.setDirection(dir);

			//update model
			model.update(dt);

			keyPress = false;
		}


		//render
		window.clear();
		window.setView(view);
		
		//render game elements

		//map
		fromX = view.getCenter().x / gridSizeF - 8;
		toX = view.getCenter().x / gridSizeF + 9;
		fromY = view.getCenter().y / gridSizeF -5;
		toY = view.getCenter().y / gridSizeF + 6;

		//only loads what is on the view
		if (fromX < 0) {
			fromX = 0;
		}
		else if (fromX >= mapSize) {
			fromX = mapSize - 1;
		}
		if (fromY < 0) {
			fromY = 0;
		}
		else if (fromY >= mapSize) {
			fromY = mapSize - 1;
		}

		if (toX < 0) {
			toX = 0;
		}
		else if (toX >= mapSize) {
			toX = mapSize - 1;
		}
		if (toY < 0) {
			toY = 0;
		}
		else if (toY >= mapSize) {
			toY = mapSize - 1;
		}

		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				window.draw(tileMap[x][y]);
			}
		}
		

		//selector
		//window.draw(tileSelector);
		//draw ui
		window.setView(window.getDefaultView());
		model.draw(window);
		window.draw(text);
		
		//finished
		window.display();

	}

}


