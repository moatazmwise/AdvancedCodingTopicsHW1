#pragma once

#include <vector>
#include "Board.h"

class Shell {
private:
    std::vector<int> position;
    std::vector<int> direction;
    int ownerid;
    bool active;

public:
    Shell(const std::vector<int>& start, const std::vector<int>& direction, int ownerid);

    std::vector<int> getPosition() const;
    
    std::vector<int> getDirection() const;

    int getOwnerid() const;

    bool isActive() const;

    void move(const Board& board);

    std::pair<std::vector<int>, std::vector<int>> getShellpath() const;

    void explode();
};
