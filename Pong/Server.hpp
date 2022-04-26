#pragma once

#include <SFML/Network.hpp>
#include "Client.hpp"


#include <iostream>
#include <vector>
#include <functional>
#include <thread>

using std::vector;
using std::cout;
using std::endl;
// server accept()s, client connect()s

// sf::socketSelector to wait/listen to a group of sockets, can be passed a time that is will quit after x seconds
// selector.wait()
// once a selector returns true it means something has data ready but it doesnt tell you which.. must use isReady() on each socket to see which is ready

// info on blocking vs non-blocking sockets // https://www.developerfusion.com/article/28/introduction-to-tcpip/8/

//#define SERVER_PORT 53000
//#define logl(x) cout << x << endl; // im mind blown rn // source:: "Making a basic Multi_Client Chat Appl. Using SFML and C++(...)"

// do i make it so they can click host and they host a server?, or have sevrer completely seperate.. so you would start the server manually, and thye would join..

// or PORT 55001??

/// <summary> good resource : https://github.com/techwithtim/Agar-IO
///  data in python looked like : players[current_id] = {"x":x, "y":y,"color":color,"score":0,"name":name}
/// 
/// 
///	if data.split(" ")[0] == "move":
			//split_data = data.split(" ")
			//x = int(split_data[1])
			//y = int(split_data[2])
			//players[current_id]["x"] = x
			//players[current_id]["y"] = y
			//
			//# only check for collison if the game has started
			//if start:
			//check_collision(players, balls)
			//player_collision(players)
			//
			//# if the amount of balls is less than 150 create more
			//if len(balls) < 150 :
			//	create_balls(balls, random.randrange(100, 150))
			//	print("[GAME] Generating more orbs")
			//
			//	send_data = pickle.dumps((balls, players, game_time))

/// 
/// </summary>
/// 



class Server
{
public: // the server will have the mId = 0; it probably wont be used much, if not ever, but it is reserved for the server
	Server(int nPlayers = 0, bool gActive = false, bool gameJoinable = true); // should nPlayers defualt to 1 or 0??

	~Server();
	
	void run(sf::Thread* threadl);

	void lobbyOperations();

	void runGameOperations();

	void letPeopleJoin();

	bool listenForConections();

	bool acceptConnection(sf::TcpListener& listener);

	void sendInitInfo(Client& newClient);

	void numPlayersPlusOne();

	int getNumPlayers() { return this->mNumberOfPlayers; }

	void onClientConnect(Client*& newClient);

	void messageAllClients(Data* data);

	bool getGameJoinable() { return this->mGameJoinable; }

	void setGameJoinable(bool temp) { this->mGameJoinable = temp; }

//	void messageAllClients(LobbyData& data);


	// void runServer(); // will contain all stuff

private:
	//sf::TcpListener mListenerSocket;
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
	sf::Uint16 mNumberOfPlayers; // made to uint from int
	bool mGameActive;
	bool mGameJoinable;




};

