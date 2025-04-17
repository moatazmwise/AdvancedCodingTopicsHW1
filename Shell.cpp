#include "Shell.h"
include"Board.h"


Shell::Shell(Position start, std::pair<int, int> direction, int owner)
    : position(start), direction(direction), owner(owner), active(true) {}

void Shell::move(int boardWidth, int boardHeight) {
    if (!active) return;
    int height= Board.getheight();
    int width=Board.getwidth();

    position.x = (position.x + 2 * direction.first + width) % width;
    position.y = (position.y + 2 * direction.second + height) % height;
}

std::pair<Position, Position> Shell::getPathThisStep() const {
    Position first = {
        (position.x + direction.first),
        (position.y + directionDelta.second)
    };
    Position second = {
        (position.x + 2 * directionDelta.first),
        (position.y + 2 * directionDelta.second)
    };
    return {first, second};
}

Position Shell::getPosition() const { return position; }

std::pair<int, int> Shell::getDirection() const { return directionDelta; }

int Shell::getOwnerId() const { return ownerId; }

bool Shell::isActive() const { return active; }

void Shell::explode() { active = false; }



  




