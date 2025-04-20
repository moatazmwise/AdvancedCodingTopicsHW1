#include "Algorithm.h"
# include <algorithm>

Algorithm::Algorithm(int playerid, const Board& board)
: playerid(playerid), board(board), shootCooldown(0) {}

std::vector<int> Algorithm::Position(const GameObject& object) const {
    return object.getPosition();
}

std::vector<int> Algorithm::Direction(const Tank& tank) const {
    return tank.getDirection();
}

bool Algorithm::canShoot(const Tank& my_tank, const Tank& other_tank) const {

    std::vector<int> p_1 = Position(my_tank);

    std::vector<int> p_2 = Position(other_tank);

    int x_1 = p_1[0], y_1 = p_1[1];

    int x_2 = p_2[0], y_2 = p_2[1];

    std::vector<int> dir = Direction(my_tank);

    int dx = x_2 - x_1, dy = y_2 - y_1;

    if (dx * dir[1] != dy * dir[0]){

     return false;}

    if ((dx * dir[0] + dy * dir[1]) <= 0){
        return false;
    } 
    int x = x_1 + dir[0];

    int y = y_1 + dir[1];

    while (x != x_2 || y != y_2) {

        if (board.isWall(x, y)){

            return false;

        } 

        x += dir[0];

        y += dir[1];
    }

    return true;
}

bool Algorithm::shellDanger(const Tank& my_tank, const std::vector<Shell>& shells) const {

    std::vector<int> myposition = Position(my_tank);

    for (int i = 0; i < (int)shells.size(); i++) {

        if (!shells[i].isActive()) continue;

        std::vector<int> shellPosition = shells[i].getPosition();

        std::vector<int> shellDirection = shells[i].getDirection();

        int w = shellPosition[0];

        int z = shellPosition[1];

        while (true) {

            w += shellDirection[0];

            z += shellDirection[1];

            board.manipulate_cords(w, z);

            if (board.isWall(w, z)) break;

            if (w == myposition[0] && z == myposition[1]) {
                return true;}
        }
    }
    return false;
}

std::vector<std::vector<int>> Algorithm::bfs(int x_1, int y_1, int x_2, int y_2) const {

    int width = board.getwidth();

    int height = board.getheight();

    std::vector<bool> visited(width * height, false);

    std::vector<int> parent(width * height, -1);

    std::vector<std::vector<int>> queue;

    int queue_head = 0;

    queue.push_back({x_1, y_1});

    visited[toIndex(x_1, y_1)] = true;

    std::vector<std::vector<int>> directions = {{0,1},{0,-1},{-1,0} ,{1,0},{1,-1} ,{-1,1}, {-1,-1},{1,1}};

    bool target_found = false;

    while (queue_head < (int)queue.size() && !target_found) {

        std::vector<int> current_cell = queue[queue_head++];

        for (int i = 0; i < 8; i++) {

            int x_3 = current_cell[0] + directions[i][0];

            int y_3 = current_cell[1] + directions[i][1];

            board.manipulate_cords(x_3, y_3);

            int id = toIndex(x_3, y_3);

            if (visited[id] || board.isWall(x_3, y_3) || board.isMine(x_3, y_3)) continue;

            visited[id] = true;

            parent[id] = toIndex(current_cell[0], current_cell[1]);

            if (x_3 == x_2 && y_3 == y_2) {

                target_found = true;
                
                break;
            }
            queue.push_back({x_3, y_3});
        }
    }
    std::vector<std::vector<int>> path;

    if (!target_found) return path;

    int currentindex = toIndex(x_2, y_2);

    while (currentindex != toIndex(x_1, y_1)) {

        path.push_back({currentindex % width, currentindex / width});

        currentindex = parent[currentindex];
    }
    path.push_back({x_1, y_1});

    std::reverse(path.begin(), path.end());

    return path;
}

int Algorithm::toIndex(int x, int y) const {

    return y * board.getwidth() + x;
}

int Algorithm::chaserAlgorithm(const Tank& myTank,const Tank& enemyTank,const std::vector<Shell>& shells,const std::vector<std::vector<int>>& mines) {

    if (shootCooldown > 0) {
        shootCooldown--;}
    
    if (shootCooldown == 0 && canShoot(myTank, enemyTank)) {

        shootCooldown = 4;

        return Shoot;
    }
    std::vector<int> starting = Position(myTank);

    std::vector<int> target = Position(enemyTank);

    std::vector<std::vector<int>> path = bfs(starting[0], starting[1], target[0], target[1]);

    if (path.size() < 2) return No_Action;

    std::vector<int> nextCell = path[1];

    int dx = nextCell[0] - starting[0];

    int dy = nextCell[1] - starting[1];

    board.manipulate_cords(dx, dy);

    std::vector<int> currentDir = Direction(myTank);

    std::vector<std::vector<int>> directions = {{0,1},{0,-1},{-1,0} ,{1,0},{1,-1} ,{-1,1}, {-1,-1},{1,1}};

    int a = 0, b = 0;

    for (int i = 0; i < 8; i++) {

        if (directions[i] == currentDir) a = i;

        if (directions[i][0] == dx && directions[i][1] == dy) b = i;

    }

    int diff = (b - a + 8) % 8;

    if (diff == 0) return Move_Forward;

    if (diff == 1) return Rotate_Rigth_1_8;

    if (diff == 2) return Rotate_right_1_4;

    if (diff == 6) return Rotate_Left_1_4;

    if (diff == 7) return Rotate_Left_1_8;

    return (diff <= 4) ? Rotate_Rigth_1_8 : Rotate_Left_1_8;
}

int Algorithm::defenderAlgorithm(const Tank& myTank,const Tank& enemyTank,const std::vector<Shell>& shells,const std::vector<std::vector<int>>& mines) {
    if (shellDanger(myTank, shells)) {

        return Move_Forward;
    }
    if (shootCooldown > 0) shootCooldown--;

    if (shootCooldown == 0 && canShoot(myTank, enemyTank)) {

        shootCooldown = 4;
        
        return Shoot;
    }
    return No_Action;
}



