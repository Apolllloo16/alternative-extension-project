#pragma once

#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "Maps.h"
#include "Nodes.h"
#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();


	Node* findNodeWithLowestCost() const;
	void drawTile(sf::Vector2i pos, sf::Color color);
	void generateTileMap(const std::vector<Node>& closedNodes, const std::vector<Node>& openNodes, const std::vector<sf::Vector2i>& path);
	int calculateHueristic(int startX, int startY, int endX, int endY);
	void scanMap(Map map);

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	//A*
	std::vector<Node> openNodes;
	std::vector<Node> closedNodes; 
	Node currentNode;
	Node oldNode;
	sf::Vector2i  startNode = sf::Vector2i(0,0);
	sf::Vector2i  endNode = sf::Vector2i(10, 10);
	bool calledOnce = 0;
	Map map;
	//Camera Varibles
	sf::View playerCam;

	// Default functions for rendering to the screen.
	sf::RectangleShape tile;
	sf::RectangleShape wall;
	sf::RectangleShape tileSelect;
	sf::CircleShape player;
	sf::CircleShape cursor;
	sf::Text FPS;
	sf::Font font;

	// Default variables for level class.
	bool buildMode = 0;
	sf::Vector2f mousePos;
};