#include "game.hpp"
#include "menu.hpp"


/*
* todo
* - start up menu :: 1/2 done -> option and about
* - save records by name
* - levels::done
* -end game :: done
* save scores and display high score (use heap structure)
*
*/

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    // Create the main window

    Menu menu;
    while (!menu.getStartGame() && !menu.getWindowClose()) menu.run_menu();



   
    if (!menu.getWindowClose())
    {
        




       
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