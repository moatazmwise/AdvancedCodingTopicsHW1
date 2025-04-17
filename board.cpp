# pragma once

#include<iostream>

#include<fstream>

#include "board.hpp"

Board::Board(int width,int height):

    board_width(width), board_height(height),board_matrix(height,std::vector<Cell>(width))
    {

    }
 const Cell& Board::getCell(int x,int y) const{

    manipulate_cords(x,y);

    return board_matrix[y][x];


 }

 int Board::getwidth() const{

    return board_width;

 }

int Board::getheight() const{

    return board_height;
}

void Board::setcell(Type type , int x, int y){

    manipulate_cords(x,y);

    board_matrix[y][x].cell_type= type;

    if(type != Type::wall){

        board_matrix[y][x].num_wallhits=0;
    }





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
