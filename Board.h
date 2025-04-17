# pragma once

# include <vector>

#include <string>

struct Cell{

    Type cell_type= Type::space;
    
    int num_wallhits=0;

};

enum class Type{

    Player1,

    player2,

    wall,

    mine,

    space,

};



class Board{

    private:

           int board_width;

           int board_height ;

           std::vector<std::vector<Cell>> board_matrix;

    public:


           Board(int width,int height);

           const Cell& getCell(int x,int y) const;

           int getwidth() const;

           int getheight() const;

           void setcell(Type type , int x, int y);

           void  manipulate_cords(int& x, int& y) const;

           bool fileloading(const std::string & file );



};
