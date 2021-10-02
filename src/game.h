#include <entity.h>
#include <vector>

class Game {
    
    public:

    Game(); // Constructor
    ~Game(); // Destructor

    // Function for game to implement and is to be called for each frame
    // to be rendered.    
    void GameUpdateAndRender();

    private:
    
    std::vector<Entity *> entities;

};



