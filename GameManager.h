#pragma once

#include <vector>
#include <iostream>
#include "Tank.h"
#include "Board.h"
#include "Algorithm.h"
#include "Shell.h"

// External globals from main parsing file
extern std::vector<std::vector<char>> board;
extern int x1Pos, y1Pos, x2Pos, y2Pos;
extern int width, height;

class GameManager {
private:
    Board boardModel;
    Tank tank1;
    Tank tank2;
    Algorithm* algorithm1;
    Algorithm* algorithm2;
    std::vector<Shell> shells;
    int stepCount;
    bool gameOver;

    void logBadStep(Tank* tank, int action);
    void processShells();
    bool executeAction(Tank* tank, int action);

public:
    GameManager();
    void initializePlayers();
    void runGameLoop();
    bool checkGameOver() const;
    void displayBoard() const;
    void moveTankForward(Tank* tank, bool forward);
    void handleShooting(Tank* tank);
};



