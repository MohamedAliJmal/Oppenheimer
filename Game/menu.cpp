#include "menu.hpp"

Menu::Menu() {
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    this->optionWinClose = nullptr;
    this->optionBg = nullptr;
    this->optionImage = nullptr;

    set_values();
}

Menu::~Menu() {
    //delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

sf::RenderWindow* Menu::getWindow()
{
    return this->window;
}

void Menu::set_values() {

    /*
    * initialise variables
    * and text of menu options
    */

    window->create(sf::VideoMode(1280, 720), "Game", sf::Style::Titlebar | sf::Style::Close);
    //window->setPosition(sf::Vector2i(0, 0));

    this->pos = 0;
    this->start_game=this->windowClose = false;

    font->loadFromFile("assets/font/arial.ttf");
    image->loadFromFile("assets/images/menu-sci-fi-game.png");

    bg->setTexture(*image);

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };

    options = { "Game", "Play", "Options", "About", "Quit" };
    texts.resize(5);
    coords = { {590,40},{610,191},{590,282},{600,370},{623,457} };
    sizes = { 20,28,24,24,24 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(23, 26));
    winclose->setPosition(1178, 39);
    winclose->setFillColor(sf::Color::Transparent);

   
}

bool Menu::getStartGame()
{
    return this->start_game;
}

void Menu::loop_events() {

    /*
    * choose between start game , option , about or quit; 
    */

    sf::Event event;
    pos_mouse = sf::Mouse::getPosition(*window);
    mouse_coord = window->mapPixelToCoords(pos_mouse);
    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
            this->windowClose = true;
            

        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
            if (pos < 4) {
                ++pos;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
               
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
            if (pos > 1) {
                --pos;
                
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                
            }

            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            switch (pos)
            {
            case 1:
                this->start_game = true;
                break;

            case 2:

                //this->option();
                break;

            case 3:

                //this->about();
                break;

            case 4:
                window->close();
                this->windowClose = true;
                this->start_game = true;
                
                break;
            }
              
        }

        

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (winclose->getGlobalBounds().contains(mouse_coord)) {
                //std::cout << "Close the window!" << '\n';
                window->close();
                this->windowClose = true;
                


            }
        }
    }
}



void Menu::draw_all() {
    window->clear();
    window->draw(*bg);
    for (auto t : texts) {
        window->draw(t);
    }
    window->display();
}

void Menu::run_menu() {


    while (this->window->isOpen() && !this->start_game) {
        loop_events();
        draw_all();
    }
}

bool Menu::getWindowClose()
{
    return this->windowClose;
}