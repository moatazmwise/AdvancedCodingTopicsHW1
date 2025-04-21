
#pragma once 

#include <vector>

class GameObject
{
protected:
    char id;

    std::vector<int> position;
    
    int health;
    

public:

    GameObject(char id, const std::vector<int> &position, int health); 

    char getId() const;

    std::vector<int> getPosition() const;

    void setPosition(int x, int y);

    int getHealth() const;

    void setHealth(int w);
};









