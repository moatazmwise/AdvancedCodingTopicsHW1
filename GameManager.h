#pragma once
#include "GameObject.h"
#include "Tank.h"
#include "TankBot.h"
#include <vector>

class GameManager {
private:
    int rows;
    int cols;
    std::vector<std::vector<GameObject*>> board;

public:
    void InitGame(int r, int c, std::vector<std::vector<char>> boardInput);
    void GameLoop();
    int Translate(GameObject* obj, int amount);
    void Explode(int r, int c, int radius);
    void Destroy(GameObject* obj);
    GameObject* GetGameObject(int r, int c);
    const std::vector<std::vector<GameObject*>>& GetBoard() const;

    template<typename T>
    T* Instantiate(int r, int c);
    template<typename T>
    T* Instantiate(int r, int c, int dR, int dC, int playerNum, TankBot* bot);

    friend class GameObject; // Allow GameObject to call Destroy
};