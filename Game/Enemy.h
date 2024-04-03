#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Enemy
{
private:
	sf::RectangleShape enemy;
	int id;
public:
	Enemy();
	~Enemy();
	sf::RectangleShape& getEnemy();
	int getId();





};