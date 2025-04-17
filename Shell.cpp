#include "Shell.h"


Shell::Shell(Position start, std::pair<int, int> direction, int owner)
    : position(start), direction(direction), owner(owner), active(true) {}

void Shell::move( int height, int width) {
        if (!active) return;
        position.x = (position.x + 2 * direction.first + width) % width;
        position.y = (position.y + 2 * direction.second + height) % height;
    }
    


std::pair<Position, Position> Shell::getPathThisStep() const {
    Position first = {
        (position.x + direction.first),
        (position.y + direction.second)
    };
    Position second = {
        (position.x + 2 * direction.first),
        (position.y + 2 * direction.second)
    };
    return {first, second};
}

Position Shell::getPosition() const { return position; }

std::pair<int, int> Shell::getDirection() const { return direction; }

int Shell::getOwner() const { return owner; }

bool Shell::isActive() const { return active; }

void Shell::explode() { active = false; }



  




