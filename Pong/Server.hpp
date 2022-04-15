#pragma once

#include <SFML/Network.hpp>
#include "Client.hpp"

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
// server accept()s, client connect()s

// sf::socketSelector to wait/listen to a group of sockets, can be passed a time that is will quit after x seconds
// selector.wait()
// once a selector returns true it means something has data ready but it doesnt tell you which.. must use isReady() on each socket to see which is ready

#define SERVER_PORT 53000
#define logl(x) cout << x << endl; // im mind blown rn
// or PORT 55001??


class Server
{
public:
	Server(int nPlayers = 1, bool gActive = false); // should nPlayers defualt to 1 or 0??



	void listenForConections();

	bool acceptConnection(sf::TcpListener& listener);

	// void runServer(); // will contain all stuff

private:
	
	vector<Client*> mClientVector; // changed to Client* from Client// should this contain a vector of sockets or a vector of client Objects that contain a socket member??? // apparently you cant store sockets in a vector // but you can  // std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
/* Source: https://en.sfml-dev.org/forums/index.php?topic=20079.0
* 
		std::list<sf::TcpSocket> connectionList;
		connectionList.emplace_back(); // This creates a new socket, directly inside the list

	*For resizing, this looks dangerous to me to resize without knowing what will happen to the clients connected to your sockets, but this function is also avaiable in list. 
	*You can watch all a list can do here on this link:
		http://www.cplusplus.com/reference/list/list/
	////////////////////////////

*For completeness, what namosca said is true of any "node-based container" (i.e. a container implemented with "nodes" that hold one item alongside pointers to other nodes). 
*That includes std::list, std::map, std::set, and so on. 
*These containers do not require the items they contain to be copyable because they never copy an item after it's been inserted, no matter what methods you call on them, which is why they work with non-copyable classes like sf::TcpSocket.
*The downside of a node-based container is that it can't guarantee contiguous memory like a std::array or std::vector can, and there's the storage and runtime costs of chasing a bunch of pointers. 
*But for many purposes you won't even notice that. 
*It was silly of me not to mention this option in the last post.
*/
	// vector<std::unique_ptr<sf::TcpSocket>> sockets; // another possible way to store a vector of Sockets
	int mNumberOfPlayers;
	bool mGameActive;




};

