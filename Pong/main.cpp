// This example will use SFML libraries to implement
// the game of Pong

// History: 4/16 - Started from the SFML tutorial code that draws
//                a circle in the window.

#include <SFML/Graphics.hpp>
#include "Client.hpp"
#include "Server.hpp"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

// screen is blacked out for x seconds while hiders hide...

/// note to self::  when you start program you are a client with a socket.. when you actually start a game you get a player constructed which is an entity 
// ? when do I assign a userNumber/name/userID

// should i use TCP or UDP???

// will have a menu,[and then a you will connect to a lobby], and then you will go into a game

// someone will be host(preferably beefy computer), and the host will have server and client, others will jsut have client
#define SERVER_LOCAL_IP "10.219.207.40"

int main()
{
	/*
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game!");
	sf::CircleShape shape(100.f);

	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	Server server;
	Client clientObj;
	sf::TcpSocket socket;

	//sf::Thread threadListen(&(socket.connect), SERVER_LOCAL_IP, SERVER_PORT);

	//sf::Thread thread(&Server::listenForConections, &socket);
	//// /*sf::Thread thread([]() {
	//	std::cout << "I am in thread!" << std::endl;
	//	});*/
	
	// This works too
	sf::Thread thread(&Server::listenForConections, &server); // works?
	thread.launch();
	socket.connect(SERVER_LOCAL_IP, SERVER_PORT);
	logl("is this working") // this doesnt need a semi colon???!??!?!?!?!?!??!?!?!?!??!?!?!?!?!??!?!?!?!??!?!?!?!?!?!?!?
	/* WORKS!!!
	sf::TcpListener listener;
	sf::TcpSocket client;

	listener.listen(SERVER_PORT);

	
	socket.connect(SERVER_LOCAL_IP, SERVER_PORT);

	server.acceptConnection(listener);
*/	

		//if (listener.accept(client) == sf::Socket::Done) {
		//	cout << "A new client just connected from " << client.sf::TcpSocket::getRemoteAddress() << endl;
		//	//this->mClientVector.push_back(newClient);
		//}
		//else {
		//	cout << " it tried " << endl;
		//}
	
	


	//server.listenForConections();
	//client.getSocket();
	
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