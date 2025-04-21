#include "GameManager.h"

GameManager::GameManager()
    : boardModel(),
      tank1(1, {0,0}, {1,0}),
      tank2(2, {0,0}, {-1,0}),
      algorithm1(nullptr), algorithm2(nullptr),
      stepCount(0), gameOver(false) {}

void GameManager::initializePlayers() {
    boardModel = Board(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = board[y][x];
            boardModel.setcell(x, y, c);
        }
    }

    tank1 = Tank(1, {x1Pos, y1Pos}, {1, 0});
    tank2 = Tank(2, {x2Pos, y2Pos}, {-1, 0});
    boardModel.setcell(x1Pos, y1Pos, '1');
    boardModel.setcell(x2Pos, y2Pos, '2');

    algorithm1 = new Algorithm(1, boardModel);
    algorithm2 = new Algorithm(2, boardModel);
}

void GameManager::runGameLoop() {
    while (!gameOver) {
        ++stepCount;
        displayBoard();

        if (tank1.getHealth() > 0) {
            int action1 = algorithm1->chaserAlgorithm(tank1, tank2, shells, {});
            if (!executeAction(&tank1, action1))
                logBadStep(&tank1, action1);
        }

        if (tank2.getHealth() > 0) {
            int action2 = algorithm2->defenderAlgorithm(tank2, tank1, shells, {});
            if (!executeAction(&tank2, action2))
                logBadStep(&tank2, action2);
        }

        processShells();

        auto p1 = tank1.getPosition();
        if (boardModel.isMine(p1[0], p1[1]) && tank1.getHealth() > 0) {
            tank1.setHealth(0);
            std::cout << "Player 1 hit a mine at step " << stepCount << std::endl;
        }

        auto p2 = tank2.getPosition();
        if (boardModel.isMine(p2[0], p2[1]) && tank2.getHealth() > 0) {
            tank2.setHealth(0);
            std::cout << "Player 2 hit a mine at step " << stepCount << std::endl;
        }

        if (checkGameOver()) {
            gameOver = true;
            if (tank1.getHealth() <= 0 && tank2.getHealth() <= 0)
                std::cout << "Tie game!" << std::endl;
            else if (tank1.getHealth() <= 0)
                std::cout << "Player 2 wins!" << std::endl;
            else
                std::cout << "Player 1 wins!" << std::endl;
        }
    }
}

bool GameManager::checkGameOver() const {
    return tank1.getHealth() <= 0 || tank2.getHealth() <= 0;
}

void GameManager::displayBoard() const {
    for (int y = 0; y < boardModel.getheight(); ++y) {
        for (int x = 0; x < boardModel.getwidth(); ++x) {
            std::cout << boardModel.getCell(x, y);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameManager::moveTankForward(Tank* tank, bool forward) {
    auto dir = tank->getDirection();
    auto pos = tank->getPosition();
    int dx = dir[0] * (forward ? 1 : -1);
    int dy = dir[1] * (forward ? 1 : -1);
    int newX = pos[0] + dx;
    int newY = pos[1] + dy;
    boardModel.manipulate_cords(newX, newY);

    if (boardModel.isSpace(newX, newY) || boardModel.isMine(newX, newY)) {
        boardModel.setcell(pos[0], pos[1], ' ');
        tank->moveForward(forward, boardModel);
        auto newPos = tank->getPosition();
        boardModel.setcell(newPos[0], newPos[1], tank->getId());
    } else {
        logBadStep(tank, forward ? Move_Forward : Move_Backward);
    }
}

void GameManager::handleShooting(Tank* tank) {
    if (!tank->shoot()) {
        std::cout << "Player " << tank->getPlayerid() << " out of shells!" << std::endl;
        return;
    }
    Shell newShell(tank->getPosition(), tank->getDirection(), tank->getPlayerid());
    shells.push_back(newShell);
    std::cout << "Player " << tank->getPlayerid() << " shoots shell!" << std::endl;
}

bool GameManager::executeAction(Tank* tank, int action) {
    switch(action) {
        case Move_Forward:
        case Move_Backward:
            moveTankForward(tank, action == Move_Forward);
            return true;
        case Rotate_Left_1_8:
            tank->turn("left", 45);
            return true;
        case Rotate_Rigth_1_8:
            tank->turn("right", 45);
            return true;
        case Rotate_Left_1_4:
            tank->turn("left", 90);
            return true;
        case Rotate_right_1_4:
            tank->turn("right", 90);
            return true;
        case Shoot:
            handleShooting(tank);
            return true;
        case No_Action:
            return true;
        default:
            return false;
    }
}

void GameManager::processShells() {
    for (auto& shell : shells) {
        if (!shell.isActive()) continue;
        shell.move(boardModel);
        auto pos = shell.getPosition();
        int x = pos[0], y = pos[1];

        if (boardModel.isWall(x, y)) {
            boardModel.setcell(x, y, ' ');
            shell.explode();
            continue;
        }

        if (tank1.getHealth() > 0) {
            auto p1 = tank1.getPosition();
            if (p1[0] == x && p1[1] == y) {
                tank1.setHealth(0);
                shell.explode();
                std::cout << "Player 1 destroyed by shell at step " << stepCount << std::endl;
            }
        }

        if (tank2.getHealth() > 0) {
            auto p2 = tank2.getPosition();
            if (p2[0] == x && p2[1] == y) {
                tank2.setHealth(0);
                shell.explode();
                std::cout << "Player 2 destroyed by shell at step " << stepCount << std::endl;
            }
        }
    }
}

void GameManager::logBadStep(Tank* tank, int action) {
    std::cout << "Bad step by Player " << tank->getPlayerid()
              << ": action " << action << " ignored at step " << stepCount << std::endl;
}






	