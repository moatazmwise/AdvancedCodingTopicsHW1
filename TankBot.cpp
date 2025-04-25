
#include "TankBot.h"
#include "GameObject.h"
#include <queue>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include "Tank.h"
// 8-directional vectors
static const std::vector<std::pair<int,int>> directions = {
    std::pair<int,int>(-1,  0), std::pair<int,int>(1,  0),
    std::pair<int,int>(0, -1), std::pair<int,int>(0,  1),
    std::pair<int,int>(-1, -1), std::pair<int,int>(-1, 1),
    std::pair<int,int>(1, -1), std::pair<int,int>(1,  1)
};


std::string AggressiveBot::Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum) {
    Tank* selfTank = nullptr;
    Tank* enemyTank = nullptr;
    
    for (auto i = 0u; i < board.size(); ++i) {

        for (auto j = 0u; j < board[i].size(); ++j) {

            GameObject* obj = board[i][j];

            if (obj && obj->GetType() == "tank") {

                Tank* tank = static_cast<Tank*>(obj);

                if (tank->GetPlayerNum() == playerNum) {

                    selfTank = tank;
                } else if (tank->GetPlayerNum() == (playerNum == 1 ? 2 : 1)) {
                    enemyTank = tank;
                }
            }
            if (selfTank && enemyTank) {
                break; // Break the inner loop when both tanks are found
            }
        }
        if (selfTank && enemyTank) {
            break; // Break the outer loop as well
        }
    }
    
    if (!selfTank || !enemyTank) {
            std::cerr << "error: null tank pointer for player " << playerNum << std::endl;
            return "f";
        }
        
        int rows = static_cast<int>(board.size());
        int cols = static_cast<int>(board[0].size());
        int self_R = selfTank->GetRow();
        int self_C = selfTank->GetCol();
        int enemy_R = enemyTank->GetRow();
        int enemy_C = enemyTank->GetCol();
    
        // BFS to find shortest path
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    
        std::vector<std::vector<std::pair<int,int>>> parent(rows, std::vector<std::pair<int,int>>(cols, std::pair<int,int>(-1, -1)));
        std::queue<std::pair<int,int>> queue;
        visited[self_R][self_C] = true;
        queue.push(std::pair<int,int>(self_R, self_C));
        bool found = false;
    
        while (!queue.empty() && !found) {
            std::pair<int,int> current_cell = queue.front();queue.pop();
            int i = current_cell.first;
            int j = current_cell.second;
            for (const std::pair<int,int>& dir : directions) {
    
                int x = dir.first;
    
                int y = dir.second;
    
                int a = (i + x + rows) % rows;
    
                int b = (j + y + cols) % cols;
    
                if (!visited[a][b]) {
    
                    GameObject* obj = board[a][b];
    
                    if (obj && obj->GetType() == "wall") {
    
                        continue;
    
                    }
    
                    visited[a][b] = true;
    
                    parent[a][b] = std::pair<int,int>(i, j);
    
                    if (a == enemy_R && b == enemy_C) {
    
                        found = true;
                        
                        break;
                    }
                    queue.push(std::pair<int,int>(a, b));
                }
            }
        }
        // If no path is found, move forward
        if (!found) {
            return "f";
        }
    
        // Backtrack to determine first move
        int w = enemy_R;
    
        int z = enemy_C;
    
        while (!(parent[w][z].first == self_R && parent[w][z].second == self_C)) {
    
            std::pair<int,int> p = parent[w][z];
    
            w = p.first;
    
            z = p.second;
    
        }
    
        // Normalize to [-1,0,1]
        int diff_Row = w - self_R;
    
        int diff_col = z - self_C;
    
        int stepi = (diff_Row > 0) ? 1 : ((diff_Row < 0) ? -1 : 0);
    
        int stepj = (diff_col > 0) ? 1 : ((diff_col < 0) ? -1 : 0);
    
    
        int dir_Row = selfTank->GetDirRow();
    
        int dir_Col= selfTank->GetDirCol();
    
        // If already facing desired direction, try to shoot
        if (dir_Row == stepi && dir_Col == stepj) {
    
            int i_ = self_R;
    
            int j_ = self_C;
    
            while (true) {
    
                i_ = (i_ + dir_Row + rows) % rows;
    
                j_ = (j_ + dir_Col + cols) % cols;
    
                if (i_ == enemy_R && j_ == enemy_C) {
    
                    return "S";
                }
    
                GameObject* obj = board[i_][j_];
    
                if (obj && obj->GetType() == "wall") {
    
                    break;
                }
            }
    
            return "f";
        }
        // Rotate toward desired direction
        int crossing = dir_Row * stepj - dir_Col * stepi;
        if (crossing < 0) {
    
            return "RC45";
    
        } else {
    
            return "RCC45";
        }
    }

std::string DefensiveBot::Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum) {
    Tank* selfTank = nullptr;
    
    for (auto i = 0u; i < board.size(); ++i) {

        for (auto j = 0u; j < board[i].size(); ++j) {

            GameObject* obj = board[i][j];
            if (obj && obj->GetType() == "tank") {

                Tank* tank = static_cast<Tank*>(obj);

                if (tank->GetPlayerNum() == playerNum) {
                    selfTank = tank;
                    break ;
                }
            }
            }
            }
     if (!selfTank) {
        std::cerr << "error: null tank pointer for player " << playerNum << std::endl;
        return "f";
        }
        int rows = static_cast<int>(board.size());
        int cols = static_cast<int>(board[0].size());
        int self_Row = selfTank->GetRow();
        int self_Col = selfTank->GetCol();
        int self_R_Dir = selfTank->GetDirRow();
        int self_C_Dir = selfTank->GetDirCol();
    
        // Evade incoming shells within 3 steps
        for (const std::pair<int,int>& dir : directions) {
    
            int i = dir.first;
    
            int j = dir.second;
    
            for (int step = 1; step <= 3; ++step) {
                int x = (self_Row + i * step + rows) % rows;
                int y = (self_Col + j * step + cols) % cols;
                GameObject* obj = board[x][y];
                if (obj && obj->GetType() == "shell") {
                    return "b";
                }
                if (obj && obj->GetType() == "wall") {
                    break;
                }
            }
        }
        // Avoid stepping on mine ahead
    
        int i_ = (self_Row + self_R_Dir + rows) % rows;
    
        int j_ = (self_Col + self_C_Dir + cols) % cols;
    
        GameObject* obj_ = board[i_][j_];
    
        if (obj_ && obj_->GetType() == "mine") {
    
            int crossing = self_R_Dir * 0 - self_C_Dir * 1;
    
            if (crossing < 0) {
    
                return "RC45";
            } else {
    
                return "RCC45";
            }
        }
        // Default patrol: rotate 90° clockwise
        return "RC90";
    }
   

/*
    MOVEMENT COMMANDS:
    output: f, b, S, RC45, RC90, RCC45, RCC90 as string
    move forward: f
    move backward: b
    shoot: S
    rotate clockwise 45 degrees: RC45
    rotate clockwise 90 degrees: RC90
    rotate counter clockwise 45 degrees: RCC45
    rotate counter clockwise 90 degrees: RCC90

*/