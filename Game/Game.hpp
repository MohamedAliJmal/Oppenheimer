#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>

#include <sstream>
#include "Enemy.h"










class Game
{
private:

	sf::RenderWindow* window;
	sf::Event event;

	sf::Texture* image;
	sf::Sprite* bg;

	//mouse postion
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//resource
	sf::Font font;
	sf::Text text;

	

	sf::Text gameOver;
	sf::RectangleShape end;

	//game logic

	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;
	bool pause;
	double level;



	//game object
	std::vector<Enemy*> enemies;


	
	void initializeWindow(sf::RenderWindow* window);
	void initializeVariables();
	
	
	void initializeFont();
	void initializeText();
	void initializeImage();
	void initializeBg();


public:
	Game(sf::RenderWindow* window);
	~Game();

	void spawnEnemy();

	bool running();
	void pollEvents();
	void updateMousePos();

	void update();
	void updateEnemy();
	void updateText();
	
	void renderText(sf::RenderTarget& target);
	void render();
	void renderEnemy();

	int getPoints();
	bool getPause();

	void calculateLevel();
	void setPosition(sf::Sprite sp);
};