
#pragma once

#include <vector>
#include "Board.h"
#include "Tank.h"
#include "Shell.h"

// Possible actions a tank can request
#define Move_Forward 0
#define Move_Backward 1
#define Rotate_Left_1_8 2
#define Rotate_Rigth_1_8 3
#define Rotate_Left_1_4 4
#define Rotate_right_1_4 5
#define Shoot 6
#define No_Action 7

class Algorithm {
    private:

    int playerid;

    const Board& board;

    int shootCooldown;

    std::vector<int> Position(const GameObject& object) const;

    std::vector<int> Direction(const Tank& tank) const;

    bool canShoot(const Tank& my_tank, const Tank& other_tank) const;

    bool shellDanger(const Tank& me, const std::vector<Shell>& shells) const;

    std::vector<std::vector<int>> bfs(int x_1, int y_1, int x_2, int y_2) const;

    int toIndex(int x, int y) const;

    public:
          Algorithm(int playerid, const Board& board);
        
         int chaserAlgorithm(const Tank& myTank,const Tank& enemyTank,const std::vector<Shell>& shells,const std::vector<std::vector<int>>& mines);

         int defenderAlgorithm(const Tank& myTank,const Tank& enemyTank,const std::vector<Shell>& shells,const std::vector<std::vector<int>>& mines);


};