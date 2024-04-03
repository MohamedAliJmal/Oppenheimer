#include "Game.hpp"


void Game::initializeVariables()
{
	std::cout << "initailize variables\n";

	this->window = nullptr;
	this->image = nullptr;

	//game logic

	this->points = 0;
	this->enemySpawnTimer = 999.f;
	this->enemySpawnTimerMax = 1000.f;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 10;
	


}

void Game::initializeFont()
{
	if (!font.loadFromFile("assets/font/arial.ttf"))
	{
		std::cout << "font failed\n";
	}
}

void Game::initializeText()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("null");
}
		

void Game::initializeWindow(sf::RenderWindow* window)
{
	
	this->window =window;
	window->setFramerateLimit(60);
	
}

void Game::initializeImage()
{
	this->image = new sf::Texture();
	if (!this->image->loadFromFile("assets/images/sky2.jpg"))
	{
		std::cout << "image failed\n";
	}
}

void Game::initializeBg()
{
	this->bg  = new sf::Sprite();
	this->bg->setTexture(*image);
	
}





Game::Game(sf::RenderWindow* window)
{
	this->initializeVariables();
	this->initializeImage();
	this->initializeBg();
	this->initializeWindow(window);
	this->initializeFont();
	this->initializeText();
}

Game::~Game()
{
	delete window;
}

bool Game::running()

{

	//std::cout << this->window->isOpen() << '\n';
	return this->window->isOpen();
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points <<"\nHealth " << this->health ;
	this->text.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->text);
}

void Game::pollEvents()
{

	
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;


		case sf::Event::KeyPressed:
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->window->close();

			}
			break;
		}





	}
	
}

void Game::updateMousePos()
{
	/*
	* updates the mouse positions:
	* - mouse position relative to window (vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::update()
{
	this->pollEvents();

	if (this->health>0)
	{

		this->updateMousePos();

		this->updateEnemy();
		
		this->updateText();
	}
	//to do zid endgame animation




}

void Game::render()
{
	this->window->clear();

	this->window->draw(*bg);

	this->renderEnemy();

	this->renderText(*this->window);

	this->window->display();
}

void  Game::spawnEnemy()
{
	/*
	* spawns enemeis and sets their color and positions
	* sets a random position
	* set a random color
	* add enemy to the vector
	*/
	Enemy* enemy = new Enemy();
	enemy->getEnemy().setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy->getEnemy().getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - enemy->getEnemy().getSize().y))

		);
	this->enemies.push_back(enemy);






}

void Game::renderEnemy()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e->getEnemy());
	}
}

void Game::updateEnemy()
{
	/*
	*  @return void
	* updates the enemy spawntimer and spawn enemy
	* when the total amount of enemies is maller than the max
	* moves the enemies downwardds
	* removes the enemies at the edge of the screen
	*/

	if (this->enemies.size() < this->maxEnemies)
	{
		if (enemySpawnTimer >= enemySpawnTimerMax)
		{
			enemySpawnTimer = 0.f;
			this->spawnEnemy();
		}
		else enemySpawnTimer += 10.f;
	}

	/*for (auto& e : this->enemies)
	{
		e.move(0.f, 0.5f);
	}*/

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->getEnemy().move(0.f, 1.f);


		//if enemy finish the line
		if (enemies.at(i)->getEnemy().getPosition().y > this->window->getSize().y)
		{
			delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);
			health--;
		}


	}

	//check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// rq:: see it after


		//mouse held to avoid cheating
		if(this->mouseHeld==false)
		{
			this->mouseHeld = true;
			for (int i = 0; i < this->enemies.size(); i++)
			{
				if (enemies.at(i)->getEnemy().getGlobalBounds().contains(this->mousePosView))
				{
					delete enemies.at(i);
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 10;

				}

			}
		}
		

	}
	else
	{
		this->mouseHeld = false;
	}
}