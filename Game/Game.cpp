#include "Game.hpp"


void Game::initializeVariables()
{
	std::cout << "initailize variables\n";

	this->window = nullptr;
	this->image = nullptr;

	//game logic

	this->points = 0;
	this->enemySpawnTimer = 999.9f;
	this->enemySpawnTimerMax = 1000.f;
	this->maxEnemies = 4;
	this->mouseHeld = false;
	this->health = 3;
	this->end = sf::RectangleShape(sf::Vector2f(1280, 720));
	this->pause = true;
	this->level = 0;
	this->danger = true;





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
	this->playerText.setFont(this->font);
	this->enterName.setFont(this->font);

	this->gameOver.setCharacterSize(130);
	this->text.setCharacterSize(60);
	this->playerText.setCharacterSize(130);
	this->enterName.setCharacterSize(130);

	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);

	this->enterName.setOutlineColor(sf::Color::Black);
	this->enterName.setOutlineThickness(1.f);

	this->gameOver.setOutlineColor(sf::Color::Black);
	this->gameOver.setOutlineThickness(1.f);

	this->playerText.setOutlineColor(sf::Color::Black);
	this->playerText.setOutlineThickness(1.f);

	this->text.setFillColor(sf::Color::White);
	this->gameOver.setFillColor(sf::Color::Red);
	this->playerText.setFillColor(sf::Color::White);
	this->enterName.setFillColor(sf::Color::White);

	this->gameOver.setPosition(sf::Vector2f(400, 138));
	this->enterName.setPosition(sf::Vector2f(460, 138));
	this->playerText.setPosition(sf::Vector2f(460, 200));



	this->text.setString("null");
	this->gameOver.setString("null");
	this->enterName.setString("Enter your name:");
	
}


void Game::initializeWindow(sf::RenderWindow* window)
{

	this->window = window;
	window->setFramerateLimit(45);

}

void Game::initializeImage()
{
	this->image = new sf::Texture();
	if (!this->image->loadFromFile("assets/images/sky2.jpg"))
	{
		std::cout << "image failed\n";
	}

	this->explosion = new sf::Texture;
	this->explosion_sprite = new sf::Sprite;
	this->explosion->loadFromFile("assets/images/explosion.png");
	this->explosion_sprite->setTexture(*explosion);
	this->explosion_sprite->setScale(0.5, 0.5);


}

void Game::initializeBg()
{
	this->bg = new sf::Sprite();
	this->bg->setTexture(*image);

	//when game is over the screen get darker
	end.setFillColor(sf::Color(0, 0, 0, 100));

}

void Game::initializeSound()
{
	
	this->raid_buffer.loadFromFile("assets/music/main2.wav");

	this->raid.setBuffer(raid_buffer);
	this->raid.setLoop(true);
	



	this->exp_buffer.loadFromFile("assets/music/explosion2.wav");

	this->exp.setBuffer(exp_buffer);
	this->exp.setVolume(80);

	this->go_buffer.loadFromFile("assets/music/gameover.wav");
	this->go.setBuffer(go_buffer);

}





Game::Game(sf::RenderWindow* window)
{
	this->initializeVariables();
	this->initializeImage();
	this->initializeBg();
	this->initializeWindow(window);
	this->initializeFont();
	this->initializeText();
	this->initializeSound();
	this->initializeName();
	

}

Game::~Game()
{
	delete window;
	delete image;
	delete bg;
	delete explosion;
	delete explosion_sprite;
	
}


void Game::initializeName()
{
	while (this->pause)
	{
		sf::String tmp;
		this->window->clear();

		this->window->draw(*bg);
		this->window->draw(this->end);
		this->window->draw(this->enterName);
		while (this->window->pollEvent(this->event))
		{


			if (event.type == sf::Event::TextEntered && isalpha(event.text.unicode))
			{
				playerInput += event.text.unicode;
				playerText.setString(playerInput);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && playerInput.begin() != playerInput.end())
			{

				this->pause = false;
				this->raid.play();

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->pause = false;
				this->window->close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{

				tmp = playerInput;

				playerInput.clear();
				if (tmp.begin() != tmp.end())
				{

					for (auto i = tmp.begin(); i < tmp.end() - 1; i++)
					{
						playerInput += *i;

					}
					playerText.setString(playerInput);
				}
			}
		}
		window->draw(playerText);

		this->window->display();
	}
}

bool Game::running()

{
	//std::cout << this->window->isOpen() << '\n';

	return this->window->isOpen() ;
}

int Game::getPoints()
{
	return this->points;
}

void Game::updateText()
{



	std::stringstream ss;
	ss << " Level: " << this->level << "\n Points: " << this->points << "\n Health: " << this->health;
	this->text.setString(ss.str());

	std::stringstream sg;
	sg << "Game Over " << this->playerInput.toAnsiString()<<"\n" << "Your Score : " << this->points << "\n Best Score : 5569 " << "\nClick Right Button To Restart";
	this->gameOver.setString(sg.str());

}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->text);
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

	if (this->health > 0)
	{


		this->updateText();
		this->updateEnemy();


	}

}



bool Game::getPause()
{
	return this->pause;
}

void Game::calculateLevel()
{
	//this->level = ceil(static_cast<double>(this->points - 10) / ((2000 - 10) / 30));
	//this->level = floor(static_cast < double>(30 * (1 - exp(-0.0007 * this->points))));
	this->level = floor(0.3 * sqrt(this->points));
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
	enemy->getEnemy()->setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy->getEnemy()->getTexture()->getSize().x * enemy->getEnemy()->getScale().x)),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - enemy->getEnemy()->getTexture()->getSize().y * enemy->getEnemy()->getScale().y - 1000))
		-200

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
	* when the total amount of enemies is smaller than the max
	* moves the enemies downwardds
	* removes the enemies at the edge of the screen
	*/

	if (this->enemies.size() < this->maxEnemies)
	{
		//std::cout << enemies.size()<<'\n';
		if (enemySpawnTimer >= enemySpawnTimerMax)
		{
			this->maxEnemies = 4 + static_cast<int>(floor(sqrt(this->level)));
			enemySpawnTimer = 0.f;
			this->spawnEnemy();
		}
		else enemySpawnTimer += static_cast<float>(sqrt(this->level + 1)) * 20.f;
	}

	/*for (auto& e : this->enemies)
	{
		e.move(0.f, 0.5f);
	}*/

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->getEnemy()->move(0.f, static_cast<float>(sqrt(this->level + 1))+2);


		//if enemy finish the line
		if (enemies.at(i)->getEnemy()->getPosition().y > this->window->getSize().y)
		{
			
			this->explosion_sprite->setPosition(enemies.at(i)->getEnemy()->getPosition().x-70.f, this->window->getSize().y-250.f);
			
			
			//delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);

			health--;
			this->go.play();

			
		}


	}

	//check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// rq:: see it after


		//mouse held to avoid cheating
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			for (int i = 0; i < this->enemies.size(); i++)
			{
				if (enemies.at(i)->getEnemy()->getGlobalBounds().contains(this->mousePosView))
				{
					this->exp.play();
					

					
					//delete enemies.at(i);
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 10;
					
					calculateLevel();
				}

			}
		}


	}
	else
	{
		this->mouseHeld = false;
	}
}



	


void Game::render()
{

	/*std::cout << "mousePosWindow " << this->mousePosWindow.x << " " << this->mousePosWindow.y << '\n';
	std::cout << "mousePosview " << this->mousePosView.x << " " << this->mousePosView.y << '\n';*/

	this->window->clear();

	this->window->draw(*bg);
	
	this->renderEnemy();
	this->renderText(*this->window);
	if (this->explosion_sprite->getPosition().y == this->window->getSize().y-250.f)
	{
		this->window->draw(*explosion_sprite);
		this->explosion_sprite->setPosition(0, 0);
	}
	
	


	if (this->health == 0)
	{
		
		this->raid.stop();
		this->window->draw(this->end);
		this->window->draw(this->gameOver);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->raid.play();
			this->health = 3;
			this->points = 0;
			this->level = 0;
			this->maxEnemies = 4;

			while (!enemies.empty())
			{
				//delete enemies[0];
				enemies.erase(enemies.begin());
			}

			//for (int i = 0; i < this->enemies.size(); i++)
			//{
			//	
			//		//delete enemies.at(i);
			//		this->enemies.erase(this->enemies.begin() + i);
			//	

			//}
			this->window->display();

		}


	}



	this->window->display();
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
				/*this->pause = true;
				std::cout << "backspace\n" << '\n';*/
			}
			break;
		}






	}

}