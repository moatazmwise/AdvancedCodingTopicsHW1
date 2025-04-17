#pragma once
#include "GameObject.h"
#include <vector>

class GameObject
{
    protected:
        char id;
        std::vector<int> position;
        int health;

    public:
        // Constructor to initialize the GameObject with an ID, position, and health
        GameObject(char id, std::vector<int> position, int health) 
        : id(id), position(position), health(health) {}
        
        std::vector<int> getPosition() {
            return position;
        }
        int getHealth() {
            return health;
        }
};