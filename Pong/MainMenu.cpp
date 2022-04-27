#include"MainMenu.hpp"
#include"character.hpp"

#include "Server.hpp"

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

void MainMenu::allowJoinLoopMember(Server& server, sf::RenderWindow& window, sf::Event& event) {

	sf::Uint16 numberOfPlayers = server.getNumPlayers();

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::W) {

				//if (choice - 1 >= 0) {
				//	mainMenu[choice].setFillColor(sf::Color::Black);
				//	choice--;
				//	if (choice == -1) {
				//		choice = 2;
				//	}
				//	mainMenu[choice].setFillColor(sf::Color::Green);
				//}
				this->MoveUp();

				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::S) {

				//if (choice + 1 <= MAX_MAIN_MENU) {
				//	mainMenu[choice].setFillColor(sf::Color::Black);
				//	choice++;
				//	if (choice == 3) {
				//		choice = 2;
				//	}
				//	mainMenu[choice].setFillColor(sf::Color::Green);
				//}
				this->MoveDown();

				break;
			}
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {

			if (this->MainMenuPressed() == 0) {
				server.setGameJoinable(false); // this will cuase the allow join server func to send an init packet to all clients

			}
			if (this->MainMenuPressed() == 1) {
				cout << "Nothing happened in hostJoin choice == 1;" << endl;
			}
			if (this->MainMenuPressed() == 2) {
				window.close();
				break;
			}
		}
	}

}

void MainMenu::runMenuScreen(sf::RenderWindow& window, sf::Event& event) {
	Client clientObj;
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

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {

			//int x = this->MainMenuPressed();
			if (this->MainMenuPressed() == 0) {
				//window.close();
				
				Server serverObj;
				cout << "Server Object: " << serverObj.getGameJoinable() << endl;

				sf::Thread* passedThread; // thread i pass into run so i can terminate the listen thread from here
				
				//serverObj.run();
				std::thread threadl(&Server::run, std::ref(serverObj), passedThread);
				/////////////////////////////

				clientObj.joinHost();

				sf::RenderWindow JoinHost(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Allow Join Host Menu", sf::Style::Default);

				MainMenu objForBackground(JoinHost.getSize().x, JoinHost.getSize().y);

				

				//sf::Text* optionsArr[3];
				objForBackground.setMainMenuText("Start", "Null", "Exit");

				while (JoinHost.isOpen() && serverObj.getGameJoinable()) {
					sf::Event JoinHostEvent;
					serverObj.getGameJoinable() ? objForBackground.setMainMenuText("Start", "Joinable", "Exit") : objForBackground.setMainMenuText("Start", "Not-Joinable", "Exit");
					objForBackground.allowJoinLoopMember(serverObj, JoinHost, JoinHostEvent);

					JoinHost.clear();
					JoinHost.draw(objForBackground.getBackgroundPicture());
					objForBackground.drawTextButtons(JoinHost);
					JoinHost.display();
				}


				//__try {
				//	passedThread->terminate();
				//	delete passedThread;
				//}
				//__except (EXCEPTION_EXECUTE_HANDLER) {
				//	cout << "Goofy Exception" << endl;
				//}
				
				
				//threadl.join(); // std


				/////////////////////////////////////////////////////////////////////////////////////////////////////////// runs the actual ganme

				if (!serverObj.getGameJoinable()) { // if they didnt click exit in the prevoius window

					// it sends message game is starting.. not here
					// then itll send the num players.. then itll send them in order in vector
					sf::Packet oPack;
					Data d(serverObj.getNumPlayers(), 1, true, "", "");
					
					LobbyData ld(true, (sf::Int16) 10, serverObj.getNumPlayers(), SERVER_ID);

					//serverObj.messageAllClients(&ld);
					serverObj.messageAllClients(ld);

					int numPlayers = serverObj.getNumPlayers();

					cout << "Num players is:" << numPlayers << endl;

					//std::vector<Client> playerList;
					std::vector<Client*> playerList;
					


					for (sf::Uint16 i = 0, id = 1; i < numPlayers; i++, id++)
					{
						playerList.push_back(new Client());
						playerList.at(i)->setId(id);
					}

					// multi thread server here

					//serverObj.messageAllClients(&d);

					//Sleep(2000);

					sf::RenderWindow GameWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Host Menu");

					runGame(GameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, clientObj, playerList);


				}
				threadl.join();
			}
			if (this->MainMenuPressed() == 1) {
				
				//sf::RenderWindow Join(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Join Menu");
			

				
				//clientObj.run();
				clientObj.joinHost();

				clientObj.getSocket().setBlocking(false);


				LobbyData lData;
				//sf::Packet packet;
				int numPlayers;
				bool startPacketRecieved = false;

				
				//while (Join.isOpen() ) {
				while (!startPacketRecieved && lData.mTimeTillStart >= DEFAULT_START_TIME) {
					//sf::Event aevent;
					//while (Join.pollEvent(aevent)) {
					//	if (aevent.type == sf::Event::Closed) {
					//		Join.close();
					//	}
					//	
					//}
					sf::Packet packet;
					try {
						if (clientObj.recievePacket(packet)) {
							
							//clientObj.recievePacket(packet);
							packet >> lData;
							

							if (lData.mTimeTillStart <= DEFAULT_START_TIME || lData.mGameActive) {
								numPlayers = lData.mNumPlayers;
								
								break;
							}
						}
						/*clientObj.recievePacket(packet);
						packet >> lData;
						if (lData.mTimeTillStart <= DEFAULT_START_TIME) {
							numPlayers = lData.mNumPlayers;
							cout << " i think the game startting" << endl;
							break;
						}*/
					}
					catch (std::runtime_error& e) {
						//cout << "[Client] Exception in Join recive: " << e.what() << endl;
					}

				}
				

				sf::RenderWindow GameWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Host Menu");

				//ssddint numPlayers = ;

				//cout << "Num players is:" << numPlayers << endl;

				//std::vector<Client> playerList;
				std::vector<Client*> playerList;



				for (sf::Uint16 i = 0, id = 1; i < numPlayers; i++, id++)
				{
					playerList.push_back(new Client());
					playerList.at(i)->setId(id);
				}

				runGame(GameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, clientObj, playerList);

			}
			if (this->MainMenuPressed() == 2) {
				window.close();
				break;
			}
		}
	}
}


//	///; ------------- On Event(host clicks start) ------------
///LobbyData data(true, DEFAULT_START_TIME, mNumberOfPlayers, SERVER_ID);

//messageAllClients(&data); // send a lobby packet saying the game is about to starts;

void textArrSetProperties(sf::Text* mainMenu[3], std::string strArr[3], sf::Font& font) {

	if (!font.loadFromFile("Fonts/Freedom.ttf")) {
		std::cout << "could not load font\n";
	}

	//Host
	mainMenu[0]->setFont(font);
	mainMenu[0]->setFillColor(sf::Color::Black);
	mainMenu[0]->setString(strArr[0]);
	mainMenu[0]->setCharacterSize(64);
	mainMenu[0]->setPosition(150, 300);
	//join
	mainMenu[1]->setFont(font);
	mainMenu[1]->setFillColor(sf::Color::Black);
	mainMenu[1]->setString(strArr[1]);
	mainMenu[1]->setCharacterSize(64);
	mainMenu[1]->setPosition(150, 375);
	//Exit
	mainMenu[2]->setFont(font);
	mainMenu[2]->setFillColor(sf::Color::Black);
	mainMenu[2]->setString(strArr[2]);
	mainMenu[2]->setCharacterSize(64);
	mainMenu[2]->setPosition(150, 450);
}

// not really using
void allowJoinLoop(Server& server, sf::RenderWindow& window, sf::Event event, sf::Text* optionsArr[3]) {

	sf::Uint16 numberOfPlayers = server.getNumPlayers();

	//LobbyData data(true, DEFAULT_START_TIME, numberOfPlayers, SERVER_ID);

	//server.messageAllClients(&data); // send a lobby packet saying the game is about to starts;

	int choice = -1;
	//sf::Text optionsArr[3];
	std::string tempStrArr[3] = { "Start", "Null", "Exit" };

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::W) {
				
				if (choice - 1 >= 0) {
					optionsArr[choice]->setFillColor(sf::Color::Black);

					choice--;
					if (choice == -1) {
						choice = 2;
					}
					optionsArr[choice]->setFillColor(sf::Color::Green);
				}

				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::S) {
				
				if (choice + 1 <= MAX_MAIN_MENU) {

					optionsArr[choice]->setFillColor(sf::Color::Black);

					choice++;
					if (choice == 3) {
						choice = 2;
					}
					optionsArr[choice]->setFillColor(sf::Color::Green);
				}

				break;
			}
		}

		if (event.key.code == sf::Keyboard::Return) {

			if (choice == 0) {
				
			}
			if (choice == 1) {
				cout << "Nothing happened in hostJoin choice == 1;" << endl;
			}
			if (choice == 2) {
				window.close();
				break;
			}
		}
	}

}


void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight, Client& client, std::vector<Client*>& playerList) {

#define MS_PER_PACKET 100

	client.getSocket().setBlocking(false);

	bool isCaught = false;

	GameData inData;
	sf::Packet inPacket;

	GameData inData1; 
	GameData inData2; 
	GameData inData3;

	std::vector<GameData*> vectTemp;

	GameData oldInData;
	sf::Packet oldInPacket;

	Direction direc;

	//init game 
	float gridSizeF = 64.f;
	unsigned girdSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;
	sf::Clock packetClock;
	sf::Clock recClock;

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


	auto lambdaThread = [](sf::RenderWindow& window, Client& client, std::vector<Client*>& playerList, sf::Clock& recClock, GameData& inData, sf::Packet& inPacket, float& dt) {
		while (window.isOpen()) {
			if (recClock.getElapsedTime().asMilliseconds() > MS_PER_PACKET / 4) { // doesnt garuentee u get a packet from everyone // higher denomenator means more lag??
				try {
					client.recievePacket(inPacket); // gameData packet
					//inPacket >> oldInData;

					inPacket >> inData;
					int temp = inData.mSenderId;
					//cout << "whT" << inData.mSenderId << endl;
					//cout << "Size" << inPacket.getDataSize() << endl;
					if (playerList.at(temp - 1)->getId() != client.getId()) {
						playerList.at(temp - 1)->getPlayer().setPos(inData.mPos);
						playerList.at(temp - 1)->getPlayer().setDirection(inData.mDirection);
						playerList.at(temp - 1)->getPlayer().update(dt);
						//playerList.at(temp - 1)->getPlayer().draw(window);
						//playerList.at(temp - 1)->setPrevPacket(inPacket);
						//playerList.at(temp - 1)->setPrevData(inData);
					}


				}
				catch (std::runtime_error& e) {
					if (e.what() != "No packet to recieve") {
						//cout << "Exception in recive packet" << e.what() << endl;
					}

				}
				catch (std::out_of_range& e) {
					cout << e.what() << endl;
				}
				recClock.restart();
			}
		}
	};

	std::thread ClientRecieveThread(lambdaThread, std::ref(window), std::ref(client), std::ref(playerList), std::ref(recClock), std::ref(inData), std::ref(inPacket), std::ref(dt));
	

	while (window.isOpen())
	{
		//Update dt
		dt = dtClock.restart().asSeconds();

		//update mouse positions

		window.setView(view);

		window.setView(window.getDefaultView());
		//update game elements


		sf::Vector2f dir = { 0.0, 0.0 };

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

			view.move(-viewSpeed * dt, 0.f);
			//character
			dir.x -= 1.0;
			direc = WEST;
			keyPress = true;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Right

			view.move(viewSpeed * dt, 0.f);

			dir.x += 1.0;
			direc = EAST;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//Up

			view.move(0.f, -viewSpeed * dt);

			dir.y -= 1.0;
			direc = NORTH;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Down

			view.move(0.f, viewSpeed * dt);

			dir.y += 1.0;
			direc = SOUTH;
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
		fromY = view.getCenter().y / gridSizeF - 5;
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

		//draw ui

		
		if (packetClock.getElapsedTime().asMilliseconds() > MS_PER_PACKET) {
			GameData data({}, view.getCenter(), isCaught, false, direc, client.getId(), SERVER_ID, true, "", "");
			sf::Packet outPacket;
			outPacket << data;

			client.sendPacket(outPacket);
			packetClock.restart();
		}


/*		if (recClock.getElapsedTime().asMilliseconds() > MS_PER_PACKET / 4) { // doesnt garuentee u get a packet from everyone // higher denomenator means more lag??
			try {
				client.recievePacket(inPacket); // gameData packet
				//inPacket >> oldInData;

				inPacket >> inData;
				int temp = inData.mSenderId;
				//cout << "whT" << inData.mSenderId << endl;
				//cout << "Size" << inPacket.getDataSize() << endl;
				if (playerList.at(temp - 1)->getId() != client.getId()) {
					playerList.at(temp - 1)->getPlayer().setPos(inData.mPos);
					playerList.at(temp - 1)->getPlayer().setDirection(inData.mDirection);
					playerList.at(temp - 1)->getPlayer().update(dt);
					//playerList.at(temp - 1)->getPlayer().draw(window);
					//playerList.at(temp - 1)->setPrevPacket(inPacket);
					//playerList.at(temp - 1)->setPrevData(inData);
				}

				
			}
			catch (std::runtime_error& e) {
				if (e.what() != "No packet to recieve") {
					//cout << "Exception in recive packet" << e.what() << endl;
				}

			}
			catch (std::out_of_range& e) {
				cout << e.what() << endl;
			}
			recClock.restart();
		}*/

		for (int i = 0; i < playerList.size(); i++) // draw all but yourself
		{
			if (playerList.at(i)->getId() != client.getId()) {
				playerList.at(i)->getPlayer().draw(window);
			}
		}

		//for (int i = 0; i < playerList.size(); i++) // you are in player list 
		//{
		//	try {
		//		if (client.recievePacket(inPacket)) {
		//			//client.recievePacket(inPacket); // gameData packet
		//			inPacket >> oldInData;

		//			if (oldInData.mSenderId != client.getId()) {
		//				inPacket >> inData;
		//				cout << "whT" << inData.mSenderId << endl;
		//				cout << "Size" << inPacket.getDataSize() << endl;
		//				playerList.at((int)--inData.mSenderId)->getPlayer().setPos(inData.mPos);
		//				playerList.at((int)--inData.mSenderId)->getPlayer().setDirection(inData.mDirection);
		//				playerList.at((int)--inData.mSenderId)->getPlayer().update(dt);
		//				playerList.at((int)--inData.mSenderId)->getPlayer().draw(window);
		//			}
		//			


		//		}
		//		else {

		//		}

		//	}
		//	catch (std::runtime_error& e) {
		//		if (e.what() != "No packet to recieve") {
		//			//cout << "Exception in recive packet" << e.what() << endl;
		//		}

		//	}
		//	catch (std::out_of_range& e) {
		//		cout << e.what() << endl;
		//	}

		//}

		//window.clear();
		window.setView(window.getDefaultView());
		model.draw(window);

		window.draw(text);
		
		//finished
		window.display();
	}
	ClientRecieveThread.join();
}

void MainMenu::updateOtherPlayers() {

}

void MainMenu::drawOtherPlayers(sf::RenderWindow& window) {
	
}


/* Goofy
void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight, Client& client, std::vector<Client*>& playerList) {

	client.getSocket().setBlocking(false);

	bool isCaught = false;
	bool packetSent = false;
	Direction direc;

	GameData inData;
	sf::Packet inPacket;
	GameData oldInData;
	sf::Packet oldInPacket;

	//for (int i = 0; i < playerList.size(); i++)
	//{
	//	//playerList.at(i).getPlayer().update//{ float(window.getSize().x) / 2 - 32, float(window.getSize().y) / 2 - 32 }
	//}

	//init game
	float gridSizeF = 64.f;
	unsigned girdSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;
	sf::Clock packetClock;

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


	while (window.isOpen())
	{
		//Update dt
		dt = dtClock.restart().asSeconds();

		//update mouse positions

		window.setView(view);

		window.setView(window.getDefaultView());
		//update game elements


		sf::Vector2f dir = { 0.0, 0.0 };

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

			view.move(-viewSpeed * dt, 0.f);
			//character
			dir.x -= 1.0;
			direc = WEST;
			keyPress = true;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Right

			view.move(viewSpeed * dt, 0.f);

			dir.x += 1.0;
			direc = EAST;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//Up

			view.move(0.f, -viewSpeed * dt);

			dir.y -= 1.0;
			direc = NORTH;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Down

			view.move(0.f, viewSpeed * dt);

			dir.y += 1.0;
			direc = SOUTH;
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
		fromY = view.getCenter().y / gridSizeF - 5;
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



		//for (int x = fromX; x < toX; x++)
		//{
		//	for (int y = fromY; y < toY; y++)
		//	{
		//		window.draw(tileMap[x][y]);
		//	}
		//}


		//selector

		//draw ui
		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				window.draw(tileMap[x][y]);
			}
		}

		try {
			client.recievePacket(inPacket); // gameData packet
			inPacket >> inData;
		}
		catch (std::runtime_error& e) {
			if (e.what() != "No packet to recieve") {
				//cout << "Exception in recive packet" << e.what() << endl;
			}
		}
		catch (std::out_of_range& e) {
			cout << e.what() << endl;
		}

		if (packetClock.getElapsedTime().asMilliseconds() > 10) {

			GameData data({}, view.getCenter(), isCaught, false, direc, client.getId(), SERVER_ID, true, "", "");
			sf::Packet outPacket;
			outPacket << data;



			client.sendPacket(outPacket);
			for (int i = 0; i < playerList.size(); i++) // you are in player list
			{
				try {

					if (inData.mSenderId != client.getId()) {
						playerList.at(i)->getPlayer().setPos(inData.mPos);
						playerList.at(i)->getPlayer().setDirection(inData.mDirection);
						playerList.at(i)->getPlayer().update(dt);
						//playerList.at(i)->getPlayer().draw(window);

					}
				}
				catch (std::runtime_error& e) {
					if (e.what() != "No packet to recieve") {
						//cout << "Exception in recive packet" << e.what() << endl;
					}
				}
				catch (std::out_of_range& e) {
					cout << e.what() << endl;
				}
			}

			packetClock.restart();
		}
		else {

			try {
				client.recievePacket(inPacket); // gameData packet
				inPacket >> inData;
			}
			catch (std::runtime_error& e) {
				if (e.what() != "No packet to recieve") {
					//cout << "Exception in recive packet" << e.what() << endl;
				}
			}
			catch (std::out_of_range& e) {
				cout << e.what() << endl;
			}

		}
		//window.clear();
		for (int i = 0; i < playerList.size(); i++){ // you are in player list
			if (inData.mSenderId != client.getId()) {
				playerList.at(i)->getPlayer().draw(window);
			}
		}

		window.setView(window.getDefaultView());
		model.draw(window);

		//window.draw(text);
			//finished
		window.display();
		//}
	}

}


*/

/*
void runGame(sf::RenderWindow& window, int windowWidth, int windowHeight) {

	//init game
	float gridSizeF = 64.f;
	unsigned girdSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;

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


	while (window.isOpen())
	{
		//Update dt
		dt = dtClock.restart().asSeconds();

		//update mouse positions


		window.setView(view);

		//if (mousePosView.x >= 0.f) {
		//	mousePosGrid.x = mousePosView.x / gridSizeF;
		//}
		//if (mousePosView.y >= 0.f) {
		//	mousePosGrid.y = mousePosView.y / gridSizeF;
		//}

		window.setView(window.getDefaultView());
		//update game elements


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

			view.move(-viewSpeed * dt, 0.f);
			//character
			dir.x -= 1.0;
			keyPress = true;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Right

			view.move(viewSpeed * dt, 0.f);

			dir.x += 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//Up

			view.move(0.f, -viewSpeed * dt);

			dir.y -= 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Down

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

		//draw ui
		window.setView(window.getDefaultView());
		model.draw(window);

		window.draw(text);

		//finished
		window.display();

	}

}
*/