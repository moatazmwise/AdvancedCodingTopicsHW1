#pragma once
#include "GameObject.h"
#include <vector>



GameObject::GameObject(char id, const std::vector<int>& position, int health): id(id), position(position), health(health) {}



char GameObject::getId() const {
    return id;
}

std::vector<int> GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(int x, int y) {
    position[0] = x;
    position[1] = y;
}

int GameObject::getHealth() const {
    return health;
}

void GameObject::setHealth(int w) {
    health = w;
}


   