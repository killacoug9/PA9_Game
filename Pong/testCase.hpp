#pragma once

#include"MainMenu.hpp"

void networkTestCase() {

	
	Server serverObj;

	if (true) {
		cout << "Successfully made a server object" << endl;

		Client clientObj;
		if (true) {
			cout << "created a client object" << endl;
		}
		else {
			cout << "failed to create a client object" << endl;
		}

		sf::Thread* passedThread; // thread i pass into run so i can terminate the listen thread from here

		std::thread threadl(&Server::run, std::ref(serverObj), passedThread);

		//clientObj.joinHost();

		clientObj.connect("10.219.207.40", SERVER_PORT);



	} else{
		cout << "Failed to make a sever obj" << endl;
	}

}