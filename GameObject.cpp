#pragma once
#include "GameObject.h"
#include <vector>


// Default constructor initializes the GameObject with default values
GameObject::GameObject() : id(' '), position({ 0, 0 }), health(0), rows(0), cols(0) {}
// Constructor to initialize the GameObject with an ID, position, and health
GameObject::GameObject(char id, std::vector<int> position, int health, int rows, int cols)
: id(id), position(position), health(health), rows(rows), cols(cols) {}

std::vector<int> GameObject::getPosition() {
    return position;
}

int GameObject::getHealth() {
    return health;
}
   