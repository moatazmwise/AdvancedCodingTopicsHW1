#include "GameObject.h"
#include <vector>

class GameObject
{
    protected:
        int id;
        std::vector<int> position;
        int health;

    public:
        // Constructor to initialize the GameObject with an ID, position, and health
        GameObject(int id, std::vector<int> position, int health) 
        : id(id), position(position), health(health) {}
        
        std::vector<int> getTankPosition() {
            return position;
        }
        int getHealth() {
            return health;
        }
};