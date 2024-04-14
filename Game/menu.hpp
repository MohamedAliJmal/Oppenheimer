#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:

    int pos;
    bool start_game,windowClose;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;


    sf::RectangleShape* optionWinClose;
    sf::Texture* optionImage;
    sf::Sprite* optionBg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    Menu();
    ~Menu();
    void run_menu();
    bool getStartGame();
    sf::RenderWindow*  getWindow();
    bool getWindowClose();

    void option();
    void about();
    
    
};