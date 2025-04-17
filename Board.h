# pragma once

# include <vector>
#include <string>
#include "GameObject.h"


class Board{

    private:

           int board_width;

           int board_height ;

           std::vector<std::vector<GameObject>> board_matrix;

    public:


           Board(int width,int height);

           const GameObject& getCell(int x,int y) const;

           int getwidth() const;

           int getheight() const;

           void setcell(GameObject obj , int x, int y);

           void  manipulate_cords(int& x, int& y) const;

           


};
