#include <iostream>
#include <fstream>
#include <string>
#include "GameManager.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: tanks_game <game_board_input_file>" << std::endl;
        return 1;
    }

    std::string inputFilePath = argv[1];

    try {
        GameManager gameManager;

        if (!gameManager.loadGameBoard(inputFilePath)) {
            std::cerr << "Failed to load game board from file: " << inputFilePath << std::endl;
            return 1;
        }

        //gameManager.initializePlayers();  // Load algorithms, setup state, etc.

        //gameManager.runGameLoop();        // Main game loop

        //gameManager.writeOutputFiles();   // Steps, results, errors

    } catch (const std::exception& ex) {
        std::cerr << "Unexpected error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}