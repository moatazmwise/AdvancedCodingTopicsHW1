
#include <iostream>
#include <fstream>
#include <string>
#include "GameManager.h"

std::string filename = "input_errors.txt"; // error file name
int width = 0; // board width
int height = 0; // board height
//tanks positions
int x1Pos = 0; // tank1 x position
int y1Pos = 0; // tank1 y position
int x2Pos = 0; // tank2 x position
int y2Pos = 0; // tank2 y position


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
        //check if the line starts with tank1:
        if (line.rfind("tank1:", 0) == 0) {
            // Parse tank information
            // If an error occurs, log it
            std::string tankInfo = line.substr(line.find(":") + 1);
            size_t commaPos = tankInfo.find(',');
            if (commaPos != std::string::npos) {
                std::string x = tankInfo.substr(0, commaPos);
                std::string y = tankInfo.substr(commaPos + 1);
                //convert to int
                x1Pos = std::stoi(x);
                y1Pos = std::stoi(y);
            }
        }
        //check if the line starts with tank2:
        if (line.rfind("tank2:", 0) == 0) {
            // Parse tank information
            // If an error occurs, log it
            std::string tankInfo = line.substr(line.find(":") + 1);
            size_t commaPos = tankInfo.find(',');
            if (commaPos != std::string::npos) {
                std::string x = tankInfo.substr(0, commaPos);
                std::string y = tankInfo.substr(commaPos + 1);
                //convert to int
                x2Pos = std::stoi(x);
                y2Pos = std::stoi(y);
            }
        }
        if(line.empty()) {
            break;
        }
    }
    printf("Width:%d, Height:%d\n", width, height);
    printf("Tank1 Position: %d, %d\n", x1Pos, y1Pos);
    printf("Tank2 Position: %d, %d\n", x2Pos, y2Pos);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: tanks_game <game_board_input_file>" << std::endl;
        return 1;
    }

    std::string inputFilePath = argv[1];
    GameManager game_manager;

    if (!read_input_file(inputFilePath)) {
        return 1;
    }

    game_manager.initializePlayers();  // Load algorithms, setup state, etc.
    game_manager.runGameLoop();        // Main game loop

    return 0;
}
