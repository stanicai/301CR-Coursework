#include <iostream>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>

using namespace std;

struct Vector2Test {
	float x;
	float y;
	float direction;
	bool weapon;
};

void main()
{
	//setting up the window that will be rendered 
	sf::RenderWindow window(sf::VideoMode(1119, 721), "Server Window");
	sf::Event e;
	
	//this is setting up the rectangle that will take the image that will be shown when the code runs with the instructions 
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1119, 721));
	background.setPosition(0.0f, 0.0f);

	//loading the texture and setting it up
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../Textures/background.png"))
	{
		cout << "Texture did not load!" << "\n";
	}

	background.setTexture(&backgroundTexture);


	Vector2Test position;

	//initialising enet
	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	//creating the enet, address, client host, peer, event and the new position
	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;
	ENetPacket* dataPacket;

	//setting up the address
	address.host = ENET_HOST_ANY;
	address.port = 1234;

	//creating the host server
	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}

	//setting up the initial position of the vector
	position.x = 3.5f;
	position.y = -0.5f;
	position.direction = 1;
	position.weapon = false;

	while (window.isOpen())
	{
		window.pollEvent(e);

		if (e.type == sf::Event::Closed) {
			window.close();

		}

		//checking if there is a connection happening 
		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				
				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";
				enetEvent.peer->data = "This is a client";
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";
				enetEvent.peer->data = NULL;
				break;
			}
		}

		//the controls that move the second player (by sending the values for the setting of linear velocity) 
		//and the direction for the sprites so they would know how to move properly
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.x = -1.0f;
			position.y = 0.0f;
			position.direction = 3;
			position.weapon = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.x = 1.0f;
			position.y = 0.0f;
			position.direction = 4;
			position.weapon = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position.x = 0.0f;
			position.y = 1.0f;
			position.direction = 1;
			position.weapon = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position.x = 0.0f;
			position.y = -1.0f;
			position.direction = 2;
			position.weapon = true;
		}
		else
		{
			position.direction = 5;
			position.x = 0.0f;
			position.y = 0.0f;
			position.weapon = false;
		}
		cout << "x     " << position.x << "       y     " << position.y << endl;

		//if the escape key is pressed then the window closes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		//sending the packet 
		dataPacket = enet_packet_create(&position, sizeof(Vector2Test), ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, dataPacket);
		
		window.clear(sf::Color::Blue);
		window.draw(background); //drawing the background image
		window.display();
	}

	//destroying the ENet Host instance, and deinitializing the library on shutdown.

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}