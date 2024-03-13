#include "pathfindingLevel.h"

pathfindingLevel::pathfindingLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	//initialise map
	for (int breadth = 0; breadth <= 100; breadth++) {
		for (int height = 0; height <= 100; height++) {
			map.Data[breadth][height] = ' ';
		}
	}

	// initialise game objects
	tile.setSize(sf::Vector2f(64, 64));
	tile.setFillColor(sf::Color(150, 150, 150));
	tile.setOutlineThickness(1);
	tile.setOutlineColor(sf::Color(0, 0, 0));

	wall.setSize(sf::Vector2f(64, 64));
	wall.setFillColor(sf::Color::Black);
	wall.setOutlineColor(sf::Color::White);

	tileSelect.setSize(sf::Vector2f(64, 64));
	tileSelect.setFillColor(sf::Color(0, 0, 0, 0));
	tileSelect.setOutlineThickness(3);
	tileSelect.setOutlineColor(sf::Color(0, 255, 0));

	player.setRadius(16);
	player.setFillColor(sf::Color(255, 0, 0));
	player.setOutlineColor(sf::Color::White);
	player.setOrigin(16, 16);

	cursor.setRadius(16);
	cursor.setFillColor(sf::Color::White);
	cursor.setOutlineColor(sf::Color::Black);
	cursor.setOrigin(0, 0);

	if (!font.loadFromFile("font/arial.ttf"))
	{
		// error...
	}

	FPS.setFont(font);
	FPS.setPosition(1600, 20);
	FPS.setFillColor(sf::Color::Red);
	FPS.setCharacterSize(30);

	playerCam.setSize(1920, 1080);
}


void pathfindingLevel::drawTile(sf::Vector2i pos, sf::Color color) {
	pos = sf::Vector2i(pos.x * 64, pos.y * 64);
	tile.setPosition((sf::Vector2f)pos);
	tile.setFillColor(color);
	window->draw(tile);

}
bool linearSearch(const std::vector<Node>& nodes, const sf::Vector2i& targetPos)
{
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].pos == targetPos) {
			return true; // Found the target position in the vector
		}
	}
	return false; // Target position not found
}
void pathfindingLevel::generateTileMap(const std::vector<Node>& closedNodes, const std::vector<Node>& openNodes, const std::vector<sf::Vector2i>& path)
{
	int tilesize = 64;

	for (int breadth = 0; breadth <= 100; breadth++) {
		for (int height = 0; height <= 100; height++) {
			sf::Vector2i pos(breadth, height);

			if (map.Data[breadth][height] == ' ') {
				// Check if the position is in the closed list
				if (linearSearch(closedNodes, pos)) {
					drawTile(pos, sf::Color::Red); // Draw closed nodes in red
				}
				// Check if the position is in the open list
				else if (linearSearch(openNodes, pos)) {
					drawTile(pos, sf::Color::Green); // Draw open nodes in green
				}
				else {
					drawTile(pos, sf::Color::White); // Empty space
				}

				// Check if the position is in the path and color it blue
				if (std::find(path.begin(), path.end(), pos) != path.end()) {
					drawTile(pos, sf::Color::Blue);
				}
			}
			else {
				drawTile(pos, sf::Color::Black); // Wall space
			}
		}
	}
}

pathfindingLevel::~pathfindingLevel()
{

}

// handle user input
void pathfindingLevel::handleInput(float dt)
{
	cursor.setPosition(mousePos);
	sf::Vector2f oldPosition = player.getPosition();
	float Speed = dt * 100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { player.move(0, -Speed); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player.move(-Speed, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player.move(0, Speed); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player.move(Speed, 0); }

	if (map.Data[(int)round((player.getPosition().x - 32) / 64)][(int)round((player.getPosition().y - 32) / 64)] == 'X') {
		player.setPosition(oldPosition);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		if (buildMode == true) { buildMode = false; }
		else buildMode = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buildMode)
	{
		int gridx = round(mousePos.x / 64);
		int gridy = round(mousePos.y / 64);
		map.Data[gridx][gridy] = 'X';
	}
}

// Update game objects
void pathfindingLevel::update(float dt)
{
	float fpsFloat = 1 / dt;
	std::string fpsString = "FPS: " + std::to_string((int)trunc(fpsFloat));
	FPS.setString(fpsString);
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window) - sf::Vector2f(16, 16);
	if (buildMode == true)
	{
		float gridsnapx = round(mousePos.x / 64) * 64;
		float gridsnapy = round(mousePos.y / 64) * 64;
		tileSelect.setPosition(gridsnapx, gridsnapy);
	}
}

void getNeighbors(Node& cell, Map& map)
{
	int i = cell.pos.x;
	int j = cell.pos.y;
	int size = map.size;

	// Assuming size is the size of the map and it represents the maximum possible index
	if (i + 1 < size && map.Data[i + 1][j] != 'X') {
		Node* Neighbor = new Node(sf::Vector2i(i + 1, j), 0, 0, 0, &cell);
		cell.neighbors.push_back(Neighbor);
	}
	if (i - 1 >= 0 && map.Data[i - 1][j] != 'X') {
		Node* Neighbor = new Node(sf::Vector2i(i - 1, j), 0, 0, 0, &cell);
		cell.neighbors.push_back(Neighbor);
	}
	if (j + 1 < size && map.Data[i][j + 1] != 'X') {
		Node* Neighbor = new Node(sf::Vector2i(i, j + 1), 0, 0, 0, &cell);
		cell.neighbors.push_back(Neighbor);
	}
	if (j - 1 >= 0 && map.Data[i][j - 1] != 'X') {
		Node* Neighbor = new Node(sf::Vector2i(i, j - 1), 0, 0, 0, &cell);
		cell.neighbors.push_back(Neighbor);
	}
}
void insertionSort(std::vector<Node>& nodes) {
	for (int i = 1; i < nodes.size(); ++i) {
		Node key = nodes[i];
		int j = i - 1;

		while (j >= 0 && nodes[j] <= key) {
			nodes[j + 1] = nodes[j];
			--j;
		}

		nodes[j + 1] = key;
	}
}

int pathfindingLevel::calculateHueristic(int startX, int startY, int endX, int endY)
{
	return abs(startX - endX) + abs(startY - endY);
}

std::vector<sf::Vector2i> findPath(Node* current)
{
	Node* temp = current;
	std::vector<sf::Vector2i> path;
	path.push_back(temp->pos);

	// Keep tracing path until reaching the start node
	while (temp->GetParent()) {
		path.push_back(temp->GetParent()->pos);
		temp = temp->GetParent();
	}

	// Reverse the path to get the correct order from start to end
	std::reverse(path.begin(), path.end());

	return path;
}


void pathfindingLevel::scanMap(Map map) {//this Function is sponsered by A*
	if (!calledOnce) {
		calledOnce = 1;
		openNodes.push_back({ startNode,calculateHueristic(startNode.x,startNode.y,endNode.x,endNode.y),0,calculateHueristic(startNode.x,startNode.y,endNode.x,endNode.y),nullptr });
	}


	if (!openNodes.empty())
	{
		int lowest = 0;
		for (int i = 0; i < openNodes.size(); i++) {
			if (openNodes[i].totalCost < openNodes[lowest].totalCost) {
				lowest = i;
			}
		}
		currentNode = openNodes[lowest];
		if (currentNode.pos == endNode) {
			std::cout << "end reached" << std::endl;
			//std::cout << currentNode.GetParent().pos.x << " , " << currentNode.parent->parent->pos.y << std::endl;
		}
		else {

			closedNodes.push_back(currentNode);
			openNodes.erase(openNodes.begin() + lowest);

			if (currentNode.neighbors.empty()) {
				getNeighbors(currentNode, map);
			}
			for (int i = 0; i < currentNode.neighbors.size(); i++) {
				Node currentNeighbor = *currentNode.neighbors[i];
				if (!linearSearch(closedNodes, currentNeighbor.pos)) {
					int tempCost = currentNode.cost + 1;

					if (linearSearch(openNodes, currentNeighbor.pos)) {
						if (tempCost < currentNeighbor.cost) {
							currentNeighbor.cost = tempCost;
							currentNeighbor.hueristic = calculateHueristic(currentNeighbor.pos.x, currentNeighbor.pos.y, endNode.x, endNode.y);
							currentNeighbor.totalCost = currentNeighbor.hueristic + currentNeighbor.cost;
						}
					}
					else
					{
						currentNeighbor.cost = tempCost;
						currentNeighbor.hueristic = calculateHueristic(currentNeighbor.pos.x, currentNeighbor.pos.y, endNode.x, endNode.y);
						currentNeighbor.totalCost = currentNeighbor.hueristic + currentNeighbor.cost;
						currentNeighbor.setParent(&currentNode);
						openNodes.push_back(currentNeighbor);
					}

					if (currentNeighbor.GetParent()) {

						std::cout << "Node: " << currentNeighbor.pos.x << " , " << currentNeighbor.pos.y << std::endl;
						std::cout << "Parent: " << currentNeighbor.GetParent()->pos.x << " , " << currentNeighbor.GetParent()->pos.y << std::endl;
						std::cout << std::endl;
					}
				}
			}
		}


	}
}

// Render level
void pathfindingLevel::render()
{
	beginDraw();
	scanMap(map);

	// Find the path
	std::vector<sf::Vector2i> path;
	if (currentNode.pos == endNode) {
		std::cout << "End reached";
		path = findPath(&currentNode);
	}

	generateTileMap(closedNodes, openNodes, path); // Ensure you're calling it correctly here
	endDraw();
}

