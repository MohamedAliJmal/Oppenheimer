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
	this->health =1;
	this->end=sf::RectangleShape(sf::Vector2f(1280, 720));
	this->pause = false;
	
	
	


}

void Game::initializeFont()
{
	if (!font.loadFromFile("assets/font/game_over.ttf"))
	{
		std::cout << "font failed\n";
	}
}

void Game::initializeText()
{
	this->text.setFont(this->font);
	this->gameOver.setFont(this->font);

	this->gameOver.setCharacterSize(130);
	this->text.setCharacterSize(75);

	this->text.setFillColor(sf::Color::White);
	this->gameOver.setFillColor(sf::Color::Red);

	this->gameOver.setPosition(sf::Vector2f(460,138));


	this->text.setString("null");
	this->gameOver.setString("null");
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

	//when game is over the screen get darker
	end.setFillColor(sf::Color(0, 0, 0, 100));
	
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
	
	return this->window->isOpen() && !this->pause;
}

int Game::getPoints()
{
	return this->points;
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points <<"\nHealth: " << this->health ;
	this->text.setString(ss.str());

	std::stringstream sg;
	sg << "Game Over\n" << "Your Score: " << this->points << "\n Best Score:"<<"\nClick To Restart";
	this->gameOver.setString(sg.str());
	
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				this->pause = true;
				std::cout << "backspace\n" << '\n';
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

	this->updateMousePos();

	if (this->health>0)
	{

		
		this->updateText();
		this->updateEnemy();
		
		
	}


	
	//to do zid endgame animation




}

void Game::render()
{
	
	std::cout <<"mousePosWindow " << this->mousePosWindow.x <<" "<< this->mousePosWindow.y << '\n';
	std::cout << "mousePosview " << this->mousePosView.x << " " << this->mousePosView.y << '\n';


	this->window->clear();

	this->window->draw(*bg);

	

	this->renderEnemy();

	this->renderText(*this->window);

	if (this->health == 0)
	{
		this->window->draw(this->end);	
		this->window->draw(this->gameOver);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		
				this->health = 10;
				this->points = 0;

				while (!enemies.empty())
				{
					delete enemies[0];
					enemies.erase(enemies.begin());
				}

				//for (int i = 0; i < this->enemies.size(); i++)
				//{
				//	
				//		//delete enemies.at(i);
				//		this->enemies.erase(this->enemies.begin() + i);
				//	

				//}

			
		}
		
		
	}

	this->window->display();
}

bool Game::getPause()
{
	return this->pause;
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
	std::cout << "scale= " << enemy->getEnemy()->getScale().x << enemy->getEnemy()->getScale().y << '\n';
	enemy->getEnemy()->setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy->getEnemy()->getTexture()->getSize().x * enemy->getEnemy()->getScale().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - enemy->getEnemy()->getTexture()->getSize().y * enemy->getEnemy()->getScale().y - 500))

		);
	
	this->enemies.push_back(enemy);






}

void Game::renderEnemy()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(*e->getEnemy());
	}
}

void Game::updateEnemy()
{
	/*
	*  
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
		enemies.at(i)->getEnemy()->move(0.f, 1.f);


		//if enemy finish the line
		if (enemies.at(i)->getEnemy()->getPosition().y > this->window->getSize().y)
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
				if (enemies.at(i)->getEnemy()->getGlobalBounds().contains(this->mousePosView))
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