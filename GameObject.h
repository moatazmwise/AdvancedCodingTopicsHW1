
#pragma once 

#include <vector>

class GameObject
{
protected:
    char id;
    std::vector<int> position;
    int health;
    int rows;
    int cols;

public:
	//default constructor
    GameObject();
    //constructor
    GameObject(char id, std::vector<int> position, int health, int rows, int cols);

    //basic functions for every object on the board
    std::vector<int> getPosition();
    int getHealth();
};

