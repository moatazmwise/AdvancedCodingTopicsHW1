#pragma once
#include "GameObject.h"
#include "Tank.h"
#include "TankBot.h"
#include <vector>

class GameManager {
private:
    int refreshRate = 200; // milliseconds
    bool printBoard = false; // Flag to control board printing
    int rows;
    int cols;
    std::vector<std::vector<GameObject*>> board;
    Tank *player1, *player2;
    int turnNum = 0;

public:
    void InitGame(int r, int c, std::vector<std::vector<char>> boardInput, bool printBoard, int refreshRate);
    void GameLoop();
    bool EndGame();
    void PrintBoard() const;
    int Translate(GameObject* obj, int amount);
    void Destroy(GameObject* obj);
    GameObject* GetGameObject(int r, int c, int offsetR = 0, int offsetC = 0);
    const std::vector<std::vector<GameObject*>>& GetBoard() const;
    int GetTurnNum() const { return turnNum; }
    void logMove(const std::string& message) const;

    template<typename T>
    T* Instantiate(int r, int c, int dR = 0, int dC = 0, int offsetR = 0, int offsetC = 0) {
        r = (r + offsetR + rows) % rows;
        c = (c + offsetC + cols) % cols;

        // Check if the tile is empty
        if (board[r][c] != nullptr) {
            return nullptr;
        }

        T* obj = new T(r, c, dR, dC, this);
        board[r][c] = obj;
        return obj;
    }
    
    friend class GameObject; // Allow GameObject to call Destroy
};