#pragma once
#include <utility>
class Board;

struct Position {
    int x, y;
};

class Shell {
    private:
    Position position;
    std::pair<int, int> direction;
    int owner;
    bool active;
    
public:
    Shell(Position start, std::pair<int, int> direction, int owner);

    void move(int Width, int Height);
    std::pair<Position, Position> getPathThisStep() const;

    Position getPosition() const;
    std::pair<int, int> getDirection() const;
    int getOwnerId() const;
    bool isActive() const;

    void explode();

private:
    Position position;
    std::pair<int, int> directionDelta; // dx, dy
    int ownerId;
    bool active;
};
