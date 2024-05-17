#include "menu.hpp"

Menu::Menu() {
    this->window = new sf::RenderWindow();
    this->winclose = new sf::RectangleShape();
    this->play = new sf::RectangleShape();
    this->quit = new sf::RectangleShape();
    this->option = new sf::RectangleShape();
    this->about = new sf::RectangleShape();

    this->buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();

    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();

    

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
    delete sound;
    delete buffer;
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



    /*window->create(sf::VideoMode(1280, 720), "Oppenheimer", sf::Style::Titlebar | sf::Style::Fullscreen );*/
    window->create(sf::VideoMode(1920, 1080), "Oppenheimer", sf::Style::Titlebar | sf::Style::Fullscreen);
    window->setFramerateLimit(30);
    //window->setPosition(sf::Vector2i(0, 0));

    this->pos = 0;
    this->start_game = this->windowClose = false;

    font->loadFromFile("assets/font/arial.ttf");
    image->loadFromFile("assets/images/menu-game.png");

    bg->setTexture(*image);

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };

    options = { "Oppenheimer", "Play", "Options", "about", "Quit" };
    texts.resize(5);
    coords = { {874,43},{877,287},{877,424},{887,556},{887,681} };
    sizes = { 45,42,40,40,40 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(55, 55));
    winclose->setPosition(1755, 60);
    winclose->setFillColor(sf::Color::Black);

    play->setSize(sf::Vector2f(300, 100));
    play->setPosition(866, 275);
   
   

    option->setSize(sf::Vector2f(300, 100));
    option->setPosition(866, 410);
    

    about->setSize(sf::Vector2f(300, 100));
    about->setPosition(866, 530);
    

    quit->setSize(sf::Vector2f(300, 100));
    quit->setPosition(866,660);
    

    buffer->loadFromFile("assets/music/bloop.ogg");

    sound->setBuffer(*buffer);

    about_string = "Hello Friends this game was designed and\ndeveloped By two awesome men \nGilfoyle and Dinesh .\nthis is V0.2 can't wait for V0.3\nall right reserved ©Tangente 2024\nAcknowledgement:\nTo that indian guy on youtube \nand to Bjarne Stroustrup  ";
    about_text.setFillColor(sf::Color::White);
    about_text.setFont(*font);
    about_text.setPosition(sf::Vector2f(584, 205));
    about_text.setCharacterSize(45);
    about_text.setString(about_string);
    about_text.setLineSpacing(1.5f);


    option_string = "\t\t\t\tUnder Construction\nWill be available in V0.3\nContact Tangente For more Details";
    option_text.setFillColor(sf::Color::White);
    option_text.setFont(*font);
    option_text.setPosition(sf::Vector2f(584, 205));
    option_text.setCharacterSize(55);
    option_text.setString(option_string);
    option_text.setLineSpacing(1.5f);

    icon.loadFromFile("assets/images/icon.png");
    
    
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());












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
    std::cout << pos_mouse.x << " " << pos_mouse.y << "\n";
    mouse_coord = window->mapPixelToCoords(pos_mouse);

    while (window->pollEvent(event)) {

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
            this->windowClose = true;
            sound->play();


        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (pos < 4) {
                ++pos;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);

            }
            sound->play();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (pos > 1) {
                --pos;

                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);

            }
            sound->play();


        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            sound->play();
            switch (pos)
            {
            case 1:
                this->start_game = true;
                break;

            case 2:

                this->Option();
                break;

            case 3:

                this->About();
                break;

            case 4:
                window->close();
                this->windowClose = true;
                this->start_game = true;

                break;
            }

        }



        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (winclose->getGlobalBounds().contains(mouse_coord) || quit->getGlobalBounds().contains(mouse_coord)) {
                sound->play();
                //std::cout << "Close the window!" << '\n';
                window->close();
                this->windowClose = true;
               


            }
            if (play->getGlobalBounds().contains(mouse_coord))
            {
                sound->play();
                this->start_game = true;
            }

            if (option->getGlobalBounds().contains(mouse_coord)) {
                sound->play();
                this->Option();
            }
            if (about->getGlobalBounds().contains(mouse_coord)) {
                sound->play();
                this->About();
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
    //window->draw(*quit);
    
    window->display();
}

void Menu::About()
{
    
    sf::Event event;
    sf::Texture about_image;
    sf::Sprite about_bg;
    about_image.loadFromFile("assets/images/menu_without_boxer.png");
    about_bg.setTexture(about_image);
    while (this->window->isOpen() ) {
        
        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);
        while (window->pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sound->play();
                return;
               
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (winclose->getGlobalBounds().contains(mouse_coord) ) {
                    mouse_coord.x = 0.f;
                    mouse_coord.y = 0.f;
                    pos_mouse.x = 0.f;
                    pos_mouse.y = 0.f;
                    sound->play();
                    
                    return;
                }
            }

        }
        window->clear();
        window->draw(about_bg);
        window->draw(texts[0]);
        window->draw(about_text);
        window->display();

    }

}
void Menu::Option()
{

    sf::Event event;
    sf::Texture about_image;
    sf::Sprite about_bg;
    about_image.loadFromFile("assets/images/menu_without_boxer.png");
    about_bg.setTexture(about_image);
    while (this->window->isOpen()) {

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);
        while (window->pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sound->play();
                return;

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (winclose->getGlobalBounds().contains(mouse_coord)) {
                    mouse_coord.x = 0.f;
                    mouse_coord.y = 0.f;
                    pos_mouse.x = 0.f;
                    pos_mouse.y = 0.f;
                    sound->play();
                    
                    return;
                }
            }

        }
        window->clear();
        window->draw(about_bg);
        window->draw(texts[0]);
        window->draw(option_text);
        window->display();

    }

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