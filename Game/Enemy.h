#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Enemy
{
private:

	sf::Sprite* spirite;
	sf::Texture* texture;

	
public:
	Enemy();
	~Enemy();
	sf::Sprite* getEnemy();
	





};