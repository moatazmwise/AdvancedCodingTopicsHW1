#pragma once
#include <vector>
#include <string>

class GameManager;
class GameObject;

class TankBot {
public:
    virtual ~TankBot() = default;
    // Decide next action given the game manager and board
    // Return one of: f, b, S, RC45, RC90, RCC45, RCC90
    virtual std::string Decide(GameManager* gamemanager,const std::vector<std::vector<GameObject*>>& board,int playerNum) = 0;
};

// Defensive strategy: evade shells and mines
class DefensiveBot : public TankBot {
public:
    std::string Decide(GameManager* gamemanager,const std::vector<std::vector<GameObject*>>& board,int playerNum) override;
};

// Aggressive strategy: BFS chase and shoot
class AggressiveBot : public TankBot {
public:
    std::string Decide(GameManager* gamemanager,const std::vector<std::vector<GameObject*>>& board,int playerNum) override;
};
