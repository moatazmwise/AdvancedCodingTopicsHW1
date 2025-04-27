#pragma once
#include <vector>
#include <string>
#include "GameObject.h"

class TankBot {

    public:
        virtual std::string Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum, int turnNum) = 0;
};

class DefensiveBot : public TankBot {
    public:
        std::string Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum, int turnNum) override;
};

class AggressiveBot : public TankBot {
    private:
        int turnsToBFS = 1;
        std::vector<std::pair<int, int>> path = std::vector<std::pair<int, int>>();
    public:
        std::string Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum, int turnNum) override;
};