// This example will use SFML libraries to implement
// the game of Pong

// History: 4/16 - Started from the SFML tutorial code that draws
//                a circle in the window.

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fstream>

//#include "Client.hpp"
#include "Server.hpp"
#include "MainMenu.hpp"

//#define WINDOW_WIDTH 960
//#define WINDOW_HEIGHT 540

// screen is blacked out for x seconds while hiders hide...

/// note to self::  when you start program you are a client with a socket.. when you actually start a game you get a player constructed which is an entity 
// ? when do I assign a userNumber/name/userID

// should i use TCP or UDP???

// will have a menu,[and then a you will connect to a lobby], and then you will go into a game

// someone will be host(preferably beefy computer), and the host will have server and client, others will jsut have client
#define SERVER_LOCAL_IP "10.219.207.40"


std::fstream outfile; // global scope cuzz fucc it why not

int main()
{

	//	const int WINDOW_WIDTH = 960; // change in MainMenu.hpp
	//	const int WINDOW_HEIGHT = 540;

		//make a window
	sf::RenderWindow HomeScreenWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Main Menu", sf::Style::Default);

	MainMenu menuButtons(HomeScreenWindow.getSize().x, HomeScreenWindow.getSize().y);

	////photo to main menu background




	while (HomeScreenWindow.isOpen()) {
		sf::Event event;
		menuButtons.runMenuScreen(HomeScreenWindow, event);

		HomeScreenWindow.clear();
		HomeScreenWindow.draw(menuButtons.getBackgroundPicture());
		menuButtons.drawTextButtons(HomeScreenWindow);
		HomeScreenWindow.display();
}

	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Server server;
	Client clientObj;
	//sf::TcpSocket socket;

	bool isHost = false;

	
	outfile.open("log.txt");

	//sf::Thread thread(&Server::listenForConections, &socket);
	//// /*sf::Thread thread([]() {
	//	std::cout << "I am in thread!" << std::endl;
	//	});*/
	
	// This works too
	//sf::Thread thread(&Server::listenForConections, &server); // works?
	//thread.launch();
	//clientObj.connect(SERVER_LOCAL_IP, SERVER_PORT);


	//socket.connect(SERVER_LOCAL_IP, SERVER_PORT);
	//logl("is this working"); // this doesnt need a semi colon???!??!?!?!?!?!??!?!?!?!??!?!?!?!?!??!?!?!?!??!?!?!?!?!?!?!?
	char input;
	cout << "are you using militthreading?? (y/n)" << endl;
	std::cin >> input;

	if (input == 'y') {
		/* --- when event triggers that they clicked %Host% --- */
		if (true) {

			try {
				isHost = true;

				Server serverObj;

				sf::Thread thread(&Server::run, &serverObj); // works?
				thread.launch(); // this runs the listen for connctions -> accept connections -> sendInitInfo

				//clientObj.connect(SERVER_LOCAL_IP, SERVER_PORT); // not scalable but will work for now.
				clientObj.joinHost();

				// possiblyshow host menu screen?
				thread.wait();
			}
			catch (...) {
				cout << "Caught an exception in main" << endl;
			}
			//isHost = true;
			//Server serverObj;
			//sf::Thread thread(&Server::run, &serverObj); // works?
			//thread.launch(); // this runs the listen for connctions -> accept connections -> sendInitInfo
			////mutex.lock();
			////clientObj.connect(SERVER_LOCAL_IP, SERVER_PORT); // not scalable but will work for now.
			//clientObj.joinHost();
			////mutex.unlock();
			//// possiblyshow host menu screen?
			//thread.wait();
		}
	}
	else {
		
		cout << "are you the host?? : ";// << endl; // put this here to see if it stops my error where it wouldnt let me insert server IP
		std::cin >> input;
		if (input == 'y') {
			Server serverObj;

			serverObj.run();

		}
		else {
			clientObj.run();
			//clientObj.joinHost();
		}
	}

	cout << "out of loop in main" << endl;
	
	

	
		
	if (isHost) { // this is where u show what scrren they are looking at?? whether they are looking at the host menu screen or the joiner screen
		
		//Server serverObj;
		////sf::Thread thread(&Server::listenForConections, &serverObj); // works?
		//sf::Thread thread(&Server::run, &serverObj); // works?
		//thread.launch();
		//clientObj.connect(SERVER_LOCAL_IP, SERVER_PORT); // not scalable but will work for now.
		//


	}
	else {
		// if click join
		//clientObj;
	}

	
	/*
	

int main(void){
	const int windowWidth = 960;
	const int windowHeight = 540;
	//make a window
	sf::RenderWindow MENU(sf::VideoMode(windowWidth,windowHeight), "Main Menu", sf::Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	//photo to main menu background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(windowWidth, windowHeight));
	sf::Texture mainBackground;
	mainBackground.loadFromFile("Textures/HideAndSeek.png");
	background.setTexture(&mainBackground);



	while (MENU.isOpen()) {
		sf::Event event;
		while (MENU.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				MENU.close();
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					mainMenu.MoveUp();
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::S) {
					mainMenu.MoveDown();
					break;
				}
			}
			if (event.key.code == sf::Keyboard::Return) {
				sf::RenderWindow Host(sf::VideoMode(windowWidth, windowHeight), "Host Menu");
				sf::RenderWindow Join(sf::VideoMode(windowWidth, windowHeight), "Join Menu");

				int x = mainMenu.MainMenuPressed();
				if (x == 0) {
					runGame(Host, Join, windowWidth,windowHeight);

				}
				if (x == 1) {
					while (Join.isOpen()) {
						sf::Event aevent;
						while (Join.pollEvent(aevent)) {
							if (aevent.type == sf::Event::Closed) {
								Join.close();
							}

						}
						Host.close();
						Join.clear();
						Join.display();
					}
				}
				if (x == 2) {
					MENU.close();
					break;
				}
			}

		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
	}

	return 0;
}
	
	*/
	

	return 0;
}

// lets say you click ------HOST GAME----
	// it will create a server Object, because you are hosting the server.(possibly on another thread??)
	// it should display your local IP address..
	// 
		// then the other players can click ---Join Game--- and type in that IP address, and click 'join'
		// then the client obj will run connectToServer // and display a message if the server gets connected and sends a message back saying its successful

// should the packets be blocking or non-blocking??
// a packet will have a message to client, and also data conatining 4 entities and their postions(etc), and also the state of the game