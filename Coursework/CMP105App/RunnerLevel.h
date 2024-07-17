#pragma once
#include "Framework/BaseLevel.h"
#include "TextureManager.h"
#include "Player.h"
#include <random>
#include <iostream>

class RunnerLevel : BaseLevel
{
public:	
	RunnerLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm);
	~RunnerLevel();

	void generateObstacles();
	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;
	bool colliding(GameObject obj);
	void reset();

private:
	TextureManager* textMan;
	Player p;
	std::vector<GameObject> BGs;
	std::vector<GameObject> jumpables;
	std::vector<GameObject> kickables;
	std::vector<GameObject> explosions;
	std::vector<float> explosionTimer;

	GameObject progressLine;
	Player progressP;
	sf::CircleShape destinationPoint;

	GameObject moon;
	GameObject finishLine;

	float distance;
	float distance2;
	float travelled = 0.f;
	float speed;

	const float MAX_SPEED = 650;
	const float ACCELERATION = 250;

	int hits = 0;
	float time = 0.f;
	float objects = 0.f;
	
	bool endless = false;



	sf::CircleShape life1;
	sf::CircleShape life2;
	sf::CircleShape life3;
};

