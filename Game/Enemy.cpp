#include "Enemy.h"


Enemy::Enemy()
{
	int r = rand() % 5;
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setOutlineThickness(1.f);

	switch (r)
	{
	case 0:
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setOutlineColor(sf::Color::Red);
		this->id = 0;
		break;
	case 1:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setOutlineColor(sf::Color::Blue);
		this->id = 1;
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::White);
		this->enemy.setOutlineColor(sf::Color::Red);
		this->id = 2;
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setOutlineColor(sf::Color::Red);
		this->id = 3;
		break;
	case 4:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setOutlineColor(sf::Color::White);
		this->id = 4;
		break;

	}
	std::cout << "Enemy id= " << id << " is created\n";

}

Enemy::~Enemy()
{
	std::cout << "Enemy id= " << id << " is destructed\n";
}


sf::RectangleShape& Enemy::getEnemy()
{
	return this->enemy;
}

int Enemy::getId()
{
	return id;
}

