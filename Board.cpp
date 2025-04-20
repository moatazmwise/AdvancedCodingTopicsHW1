# pragma once

#include<iostream>

#include<fstream>

#include"Board.h"



Board::Board(int width=0,int height=0):
    board_width(width), board_height(height), board_matrix(width,std::string(height, ' ')) {}



const char  Board::getCell(int x,int y) const{
    manipulate_cords(x, y);
    return board_matrix[y][x];
}

void Board::setcell(int x, int y, char obj){
    manipulate_cords(x, y);
    board_matrix[y][x] = obj;

}

int Board::getwidth() const{
    return board_width;
}

int Board::getheight() const{
    return board_height;
}

void  Board::manipulate_cords(int& x, int& y) const{
    if (board_width <= 0 || board_height <= 0) return;
    x = ((x % board_width) + board_width) % board_width;
    y = ((y % board_height) + board_height) % board_height;
}

void Board::setInputRow(int row, const std::string& inputline){

    if (row < 0 || row >= board_height) return;

    int row_line = static_cast<int>(inputline.size());

    board_matrix[row].assign(inputline.substr(0, std::min(row_line, board_width)));

    if (row_line < board_width) {

        board_matrix[row].append(board_width - row_line, ' ');
    }
}

bool Board::isTank(int x, int y) const{
    char c = getCell(x, y);
    return c == '1' || c == '2';
}


bool Board::isWall(int x, int y) const{
    return getCell(x, y) == '#';
}

bool Board::isMine(int x, int y) const{
    return getCell(x, y) == '@';
}


bool Board::isSpace(int x, int y) const{
    return getCell(x, y) == ' ';
}
//debbuging function 
void Board::printBoard() const {
    std::cout << "Current Board State (" << board_width << " x " << board_height << "):\n";
    for (const auto& row : board_matrix) {
        std::cout << row << '\n';
    }
    std::cout << std::endl;
}
