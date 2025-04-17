#pragma once
#include <utility>


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

    void Shell::move( int height, int width) ;
    std::pair<Position, Position> getPathThisStep() const;

    Position getPosition() const;
    std::pair<int, int> getDirection() const;
    int getOwner() const;
    bool isActive() const;

    void explode();

};
