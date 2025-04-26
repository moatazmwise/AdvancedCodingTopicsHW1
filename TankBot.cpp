#include "TankBot.h"
#include "Tank.h"
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

// functions prototypes
void FindPathToEnemyTankBFS(const std::vector<std::vector<GameObject *>> &board, std::vector<std::pair<int, int>> &path, Tank *myTank, Tank *enemyTank);
void FindObjects(
    const std::vector<std::vector<GameObject *>> &board,
    std::vector<GameObject *> &mines,
    std::vector<GameObject *> &shells,
    std::vector<GameObject *> &tanks);

std::string RunFromShells(const std::vector<std::vector<GameObject *>> &board, Tank *tank, const std::vector<GameObject *> &shells);
bool IsPathStraight(const std::vector<std::pair<int, int>> &path);
std::string GetRotationCommand(Tank tank, int newDR, int newDC);



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

std::string AggressiveBot::Decide(const std::vector<std::vector<GameObject *>> &board, int playerNum, int turnNum) {
    std::vector<GameObject *> mines;
    std::vector<GameObject *> shells;
    std::vector<GameObject *> tanks;
    FindObjects(board, mines, shells, tanks);
    Tank *enemyTank, *myTank;
    for (GameObject *tankObj : tanks) {
        Tank *tank = dynamic_cast<Tank *>(tankObj);
        if (tank->GetPlayerNum() != playerNum) {
            enemyTank = tank;
        }
        else {
            myTank = tank;
        }
    }
    std::string run = RunFromShells(board, myTank, shells);
    if (run != "") {
        return run;
    }

    // Aggressive bot logic
    //while the first tile in the path is not the current position of the tank then remove the first tile in the path
    while (!path.empty() && (path[0].first != myTank->GetRow() || path[0].second != myTank->GetCol())) {
        path.erase(path.begin());
    }
    // step 1: find the fastest route to the enemy tank avoiding mines and walls using bfs algorithm and store it in a vector of pairs of coordinates, in the case of no route then return "S" to shoot
    if (turnNum %turnsToBFS == 0 || path.empty()) FindPathToEnemyTankBFS(board, path, myTank, enemyTank);
    if (path.empty()) {
        return "S";
    }
    // step 2: if the route is a straight line (can also be diagonal) then orient the tank in that direction, if the tank is already in that direction then shoot
    if (IsPathStraight(path)) {
        int dR = path[1].first - path[0].first;
        int dC = path[1].second - path[0].second;
        if (dR == myTank->GetDirRow() && dC == myTank->GetDirCol()) {
            return "S";
        }
        else {
            return GetRotationCommand(*myTank, dR, dC);
        }
    }
    // step 3: if the route is not a straight line then rotate the tank in the direction of the next tile in the route, if the tank is already in that direction then move forward
    else {
        int dR = path[1].first - path[0].first;
        int dC = path[1].second - path[0].second;
        if (dR == myTank->GetDirRow() && dC == myTank->GetDirCol()) {
            return "f";
        }
        else {
            return GetRotationCommand(*myTank, dR, dC);
        }
    }
}

std::string DefensiveBot::Decide(const std::vector<std::vector<GameObject *>> &board, int playerNum, int turnNum) {
    std::vector<GameObject *> mines;
    std::vector<GameObject *> shells;
    std::vector<GameObject *> tanks;
    FindObjects(board, mines, shells, tanks);
    Tank *enemyTank, *myTank;
    for (GameObject *tankObj : tanks) {
        Tank *tank = dynamic_cast<Tank *>(tankObj);
        if (tank->GetPlayerNum() != playerNum) {
            enemyTank = tank;
        }
        else {
            myTank = tank;
        }
    }
    std::string run = RunFromShells(board, myTank, shells);
    if (run != "") {
        return run;
    }

    // TODO: Implement defensive bot logic
    // step 1: calculate the manhattan distance to the enemy tank
    // step 2: if the distance is less than 8 then move away from the enemy tank
    // step 3: if the distance is greater than 8 then orient the tank in the direction of the enemy tank, if already in that direction then shoot
}

void FindObjects(
    const std::vector<std::vector<GameObject *>> &board,
    std::vector<GameObject *> &mines,
    std::vector<GameObject *> &shells,
    std::vector<GameObject *> &tanks) {

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            GameObject *obj = board[i][j];
            if (obj != nullptr) {
                if (obj->GetType() == "mine") {
                    mines.push_back(obj);
                }
                else if (obj->GetType() == "shell") {
                    shells.push_back(obj);
                }
                else if (obj->GetType() == "tank") {
                    tanks.push_back(obj);
                }
            }
        }
    }
}

std::string RunFromShells(const std::vector<std::vector<GameObject *>> &board, Tank *tank, const std::vector<GameObject *> &shells) {
    // create a bool matrix of the same size as the board
    std::vector<std::vector<bool>> safe(board.size(), std::vector<bool>(board[0].size(), true));
    
    // for each null tile in the original board, mark it as "safe" in the clone, otherwise mark it as "danger"
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] != nullptr) {
                safe[i][j] = false;
            }
        }
    }

    // for each shell in the original board, mark 8 tiles in front of the shell as "danger" in the bool matrix
    for (GameObject *shell : shells) {
        int r = shell->GetRow();
        int c = shell->GetCol();
        int dR = shell->GetDirRow();
        int dC = shell->GetDirCol();
        // mark the 8 tiles in front of the shell as "danger"
        for (int i = 0; i < 8; ++i) {
            int newR = (r + dR*i + board.size()*8) % board.size();
            int newC = (c + dC*i + board[0].size()*8) % board[0].size();
            safe[newR][newC] = false;
        }
    }

    // if the tank is in a "danger" tile, if its facing a "safe" tile then move forward, if not then rotate in the direction of the "safe" tile
    int r = tank->GetRow();
    int c = tank->GetCol();
    int dR = tank->GetDirRow();
    int dC = tank->GetDirCol();
    if (!safe[r][c]) {
        // check if the tile in front of the tank is safe
        if (safe[(r + dR + board.size()) % board.size()][(c + dC + board[0].size()) % board[0].size()]) {
            return "f";
        } else {
            // find the nearest safe tile
            // create a vector of pairs of coordinates for the 7 possible directions the tank can face
            // even indexes are for clockwise rotation and odd indexes are for counterclockwise rotation
            std::pair<int, int> directions[7];
            for (int i = 0; i < 4; ++i) {
                tank->RotateClockwise();
                directions[2 * i] = {tank->GetDirRow(), tank->GetDirCol()};
            }
            for (int i = 0; i < 3; ++i) {
                tank->RotateClockwise();
                directions[2 * (2 - i) + 1] = {tank->GetDirRow(), tank->GetDirCol()};
            }
            tank->RotateClockwise();

            // return the rotation command for the direction of the nearest safe tile
            for (int i = 0; i < 7; ++i) {
                int newR = (r + directions[i].first + board.size()) % board.size();
                int newC = (c + directions[i].second + board[0].size()) % board[0].size();
                if (safe[newR][newC]) {
                    std::string command = "RC";
                    if (i % 2 != 0) {
                        command += "C";
                    }
                    if (i < 2) {
                        command += "45";
                    } else {
                        command += "90";
                    }
                    return command;
                }
            }

            // if no safe tile is found, return "S" to shoot
            return "S";
        }
    }

    return "";
}

void FindPathToEnemyTankBFS(const std::vector<std::vector<GameObject *>> &board, std::vector<std::pair<int, int>> &path, Tank *myTank, Tank *enemyTank) {
    int rows = board.size();
    int cols = board[0].size();
    std::pair<int, int> start = {myTank->GetRow(), myTank->GetCol()};
    std::pair<int, int> target = {enemyTank->GetRow(), enemyTank->GetCol()};

    std::queue<std::pair<int, int>> q;
    q.push(start);
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> parent;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> visited;
    visited[start] = true;
    bool found = false;

    std::vector<std::pair<int, int>> neighbors = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == target) {
            found = true;
            break;
        }
        for (auto &d : neighbors) {
            int nr = cur.first + d.first;
            int nc = cur.second + d.second;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            std::pair<int, int> next = {nr, nc};
            if (visited.find(next) != visited.end())
                continue;
            // Allow destination regardless of content.
            if (!(nr == target.first && nc == target.second)) {
                // Block cell if not empty and if it contains a mine or wall.
                if (board[nr][nc] != nullptr) {
                    std::string type = board[nr][nc]->GetType();
                    if (type == "mine" || type == "wall")
                        continue;
                }
            }
            visited[next] = true;
            parent[next] = cur;
            q.push(next);
        }
    }

    path = std::vector<std::pair<int, int>>();

    if (!found) {
        return;
    }

    // Reconstruct the path from target to start.
    auto cur = target;
    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    // Now path[0] is start and last element is enemy's position.
}

bool IsPathStraight(const std::vector<std::pair<int, int>> &path) {
    if (path.size() < 2) {
        return false;
    }
    int dR = path[1].first - path[0].first;
    int dC = path[1].second - path[0].second;
    for (size_t i = 2; i < path.size(); ++i) {
        int newDR = path[i].first - path[i - 1].first;
        int newDC = path[i].second - path[i - 1].second;
        if (newDR != dR || newDC != dC) {
            return false;
        }
    }
    return true;
}

std::string GetRotationCommand(Tank tank, int newDR, int newDC) {
    if (newDR == tank.GetDirRow() && newDC == tank.GetDirCol()) {
        throw std::invalid_argument("Tank is already facing the desired direction");
    }

    // Calculate the number of 45-degree clockwise rotations needed
    int needed45Rotations = -1;
    for (int i = 0; i < 8; ++i) {
        tank.RotateClockwise();
        if (tank.GetDirRow() == newDR && tank.GetDirCol() == newDC) {
            needed45Rotations = i + 1;
        }
    }

    // Determine the rotation command based on the number of clockwise rotations
    if (needed45Rotations == 1) {
        return "RC45";
    } else if (needed45Rotations == 7) {
        return "RCC45";
    } else if (needed45Rotations < 5) {
        return "RC90";
    } else {
        return "RCC90";
    }
}