#include "Board.h"
#include "GameObject"
class Board
{
private:
    std::vector<std::vector<GameObject>> board; // 2D vector to represent the board
public:
    Board(/* args */);
    ~Board();
};

Board::Board(/* args */)
{
}

void  Board::manipulate_cords(int& x, int& y) const{

    if(board_width <= 0 || board_height <= 0) return;

    x%=board_width;

    y%=board_height;

    if(x<0) x+=board_width;

    if(y<0) y+=board_height;


}

bool Board::fileloading(const std::string & file ){

    std::ifstream input(file);

    if(! input){

        std::cerr << "cannot open the file:"<< file <<".\n";

        return false;

    }
    


}
