# pragma once

#include<iostream>

#include<fstream>

#include "board.h"

Board::Board(int width,int height):

    board_width(width), board_height(height),board_matrix(height,std::vector<GameObject>(width))
    {}

 const GameObject& Board::getCell(int x,int y) const{

    manipulate_cords(x,y);

    return board_matrix[y][x];


 }

 int Board::getwidth() const{

    return board_width;

 }

int Board::getheight() const{

    return board_height;
}

void Board::setcell(GameObject obj , int x, int y){

    manipulate_cords(x,y);
	board_matrix[y][x] = obj;
}

void  Board::manipulate_cords(int& x, int& y) const{

    if(board_width <= 0 || board_height <= 0) return;

    x%=board_width;

    y%=board_height;

    if(x<0) x+=board_width;

    if(y<0) y+=board_height;


}


    



