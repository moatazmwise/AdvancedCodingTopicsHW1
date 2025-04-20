#include "Shell.h"

Shell::Shell(const std::vector<int>& start, const std::vector<int>& direction, int ownerid)
    : position(start), direction(direction), ownerid(ownerid), active(true) {}

std::vector<int> Shell::getPosition() const {
        return position;
    }
    
std::vector<int> Shell::getDirection() const {
        return direction;
    }
    
int Shell::getOwnerid() const {
        return ownerid;
    }
    
bool Shell::isActive() const {
        return active;
    }

void Shell::move(const Board& board) {
    if (!active) return;
    position[0] += 2 * direction[0];
    position[1] += 2 * direction[1];

    board.manipulate_cords(position[0], position[1]);
}

std::pair<std::vector<int>, std::vector<int>> Shell::getShellpath() const {
    std::vector<int> beginning = position;
    std::vector<int> finish = {
        (position[0] + 2 * direction[0]),
        (position[1] + 2 * direction[1])
    };
    return {beginning, finish};
}
void Shell::explode() {
    active = false;
}






  




