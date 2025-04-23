#include "GameManager.h"
#include <iostream>

void GameManager::InitGame(int r, int c, std::vector<std::vector<char>> boardInput) {
    rows = r;
    cols = c;
    board.resize(rows, std::vector<GameObject*>(cols, nullptr));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char c = boardInput[i][j];
            if (c == '#') {
                Instantiate<Wall>(i, j);
            } else if (c == '@') {
                Instantiate<Mine>(i, j);
            } else if (c == '1') {
                Instantiate<Tank>(i, j, 0, 1, '1', new AggressiveBot());
            } else if (c == '2') {
                Instantiate<Tank>(i, j, 0, -1, '2', new DefensiveBot());
            } else if (c == ' ') {
                // Empty space, do nothing
            }
        }
    }
}

void GameManager::GameLoop(){
    // Placeholder game loop
    while (true) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j]) {
                    board[i][j]->Update();
                }
            }
        }
        // Handle other game logic here...
    }
}

int GameManager::Translate(GameObject* obj, int amount) {
    int moved = 0;
    int r = obj->row;
    int c = obj->col;

    for (int i = 0; i < amount; ++i) {
        int newR = (r + obj->dirRow + rows) % rows;
        int newC = (c + obj->dirCol + cols) % cols;

        if (board[newR][newC] == nullptr) {
            board[r][c] = nullptr;
            board[newR][newC] = obj;
            r = newR;
            c = newC;
            moved++;
        } else {
            break;
        }
    }
    obj->row = r;
    obj->col = c;
    return moved;
}

void GameManager::Explode(int r, int c, int radius) {
    for (int i = r - radius; i <= r + radius; ++i) {
        for (int j = c - radius; j <= c + radius; ++j) {
            int wrappedI = (i + rows) % rows;
            int wrappedJ = (j + cols) % cols;
            if (board[wrappedI][wrappedJ]) {
                board[wrappedI][wrappedJ]->Damage(10); // Arbitrary damage value
            }
        }
    }
}

void GameManager::Destroy(GameObject* obj) {
    int r = obj->row;
    int c = obj->col;
    if (board[r][c] == obj) {
        board[r][c] = nullptr;
    }
}

GameObject* GameManager::GetGameObject(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) return nullptr;
    return board[r][c];
}

template<typename T>
T* GameManager::Instantiate(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != nullptr) return nullptr;
    T* obj = new T();
    obj->row = r;
    obj->col = c;
    obj->manager = this;
    board[r][c] = obj;
    return obj;
}

template<typename T>
T* GameManager::Instantiate(int r, int c, int dR, int dC, int playerNum, TankBot* bot) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != nullptr) return nullptr;
    T* obj = new T();
    obj->row = r;
    obj->col = c;
    obj->dirRow = dR;
    obj->dirCol = dC;
    obj->playerNum = playerNum;
    obj->tankBot = bot;
    obj->manager = this;
    obj->symbol = char(playerNum);
    board[r][c] = obj;
    return obj;
}

const std::vector<std::vector<GameObject*>>& GameManager::GetBoard() const {
    return board;
}