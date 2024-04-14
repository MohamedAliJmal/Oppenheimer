#include "game.hpp"
#include "menu.hpp"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    // Create the main window

    Menu menu;
    while (!menu.getStartGame()) menu.run_menu();

    

    // Load a music to play
    if(!menu.getWindowClose())
    {
        sf::Music music;
        if (!music.openFromFile("assets/music/3.-Avicii-The-Nights.ogg"))
            return EXIT_FAILURE;



        // Play the music
        music.play();
        Game game(menu.getWindow());
        // Start the game loop
        while (game.running())
        {
            // Process events
            game.render();
            game.update();

        }
    }


    return EXIT_SUCCESS;
}