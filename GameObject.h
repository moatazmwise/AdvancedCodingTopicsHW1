
#pragma once 

#include <vector>

class GameObject
{
    protected:
        char id;

        std::vector<int> position;

        int health;
        
    public:
        //coonstructor
        GameObject(char id, std::vector<int> position, int health);
        
        //basic functions for every object on the board
        std::vector<int> getTankPosition() {}

        int getHealth() {}
};

