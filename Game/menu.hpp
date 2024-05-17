#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class Menu {
private:

    int pos;
    bool start_game, windowClose;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::RectangleShape* play;
    sf::RectangleShape* option;
    sf::RectangleShape* quit;
    sf::RectangleShape* about;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;

    sf::SoundBuffer* buffer;
    sf::Sound* sound;

    sf::RectangleShape* optionWinClose;
    sf::Texture* optionImage;
    sf::Sprite* optionBg;

    sf::String about_string;
    sf::Text about_text;

    sf::String option_string;
    sf::Text option_text;

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
    sf::RenderWindow* getWindow();
    bool getWindowClose();

    void Option();
    void About();


};