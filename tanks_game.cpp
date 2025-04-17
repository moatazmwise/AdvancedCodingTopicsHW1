#include <iostream>
#include <fstream>
#include <string>
#include "GameManager.h"

std::string filename = "input_errors.txt"; // error file name
int width = 0; // board width
int height = 0; // board height

void log_error(const std::string& message) {
    std::ofstream file(filename, std::ios::app);  // append mode
    if (!file) return; // Fail silently if file can't be opened
    file << message << '\n';
}

bool read_input_file(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        log_error("Failed to open input file: " + filePath);
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Process each line of the input file
        // For example, parse game board dimensions or player positions
        // If an error occurs, log it
        if (line.rfind("dimensions:", 0) == 0) {
            std::string dims = line.substr(line.find(":") + 1); // " height x width"
            size_t xPos = dims.find('x');
            if (xPos != std::string::npos) {
                width = std::stoi(dims.substr(0, xPos));
                height = std::stoi(dims.substr(xPos + 1));
            }
        }
    }
    printf("Width: %d, Height: %d\n", width, height);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: tanks_game <game_board_input_file>" << std::endl;
        return 1;
    }

    std::string inputFilePath = argv[1];
    GameManager gameManager;

    if (!read_input_file(inputFilePath)) {
        return 1;
    }

    gameManager.initializePlayers();  // Load algorithms, setup state, etc.
    gameManager.runGameLoop();        // Main game loop

    return 0;
}
