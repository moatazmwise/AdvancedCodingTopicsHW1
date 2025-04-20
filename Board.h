# pragma once

# include <vector>
#include <string>



class Board{

    private:

           int board_width;

           int board_height ;

           std::vector<std::string> board_matrix;

    public:


           Board(int width=0,int height=0);

           const char getCell(int x,int y) const;

           void setcell(int x, int y, char obj);

           int getwidth() const;

           int getheight() const;

           void  manipulate_cords(int& x, int& y) const;

           void setInputRow(int row, const std::string& inputline);

           bool isWall(int x, int y) const;

           bool isMine(int x, int y) const;

           bool isTank(int x, int y) const;

           bool isSpace(int x, int y) const;

           void Board::printBoard() const;


           


};


   


