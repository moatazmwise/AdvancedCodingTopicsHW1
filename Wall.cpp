#include "Wall.h"

Wall::Wall(char id, const std::vector<int>& position) : GameObject('#', position, 2) {}

void Wall::decreaseHealth() {
    int currentHealth = getHealth();
    if (currentHealth > 0) {
        setHealth(currentHealth - 1);
    }
}

