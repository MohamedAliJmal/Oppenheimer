#include "game.hpp"
#include "menu.hpp"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    // Create the main window
    
    Menu menu;
    if(!menu.getStartGame()) menu.run_menu();

    Game game(menu.getWindow());

    // Load a music to play

    sf::Music music;
    if (!music.openFromFile("assets/music/3.-Avicii-The-Nights.ogg"))
        return EXIT_FAILURE;

    // Play the music
    music.play();

    // Start the game loop
    while (game.running())
    {
        // Process events
        game.render();
        game.update();
       
    }
   

    return EXIT_SUCCESS;
}

