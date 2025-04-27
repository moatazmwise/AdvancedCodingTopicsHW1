#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GameManager.h"

std::string filename = "input_errors.txt"; // error file name

bool printBoard = false; // Flag to control board printing
int refreshRate = 200; // milliseconds

//tanks positions
int x1Pos = 0; // tank1 x
int y1Pos = 0; // tank1 y
int x2Pos = 0; // tank2 x
int y2Pos = 0; // tank2 y

std::vector<std::vector<char>> board; // game board
int width = 0; // width
int height = 0; // height

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

    int i = 0, j = 0;
    std::string line;
    while (std::getline(file, line))
    {
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
            // Check if width and height are valid
            if (width <= 0 || height <= 0) {
                log_error("Invalid dimensions in input file: " + dims);
                return false;
            }
            if (width <= 1 && height <= 1) {
                log_error("Dimentions are too small: " + dims);
                return false;
            }
            // Initialize the board with the given dimensions
            board.resize(height, std::vector<char>(width, ' ')); // Initialize with spaces
            continue;
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
            continue;
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
            continue;
        }
        //check if the line starts with refreshRate:
        if (line.rfind("refreshRate:", 0) == 0) {
            // Parse refresh rate information
            // If an error occurs, log it
            std::string rateInfo = line.substr(line.find(":") + 1);
            try {
                int NrefreshRate = std::stoi(rateInfo);
                if (NrefreshRate > 0) {
                    refreshRate = NrefreshRate;
                }
            }
            catch (const std::exception& e) {
                log_error("Invalid refresh rate in input file: " + rateInfo);
                continue;
            }
            
        }
        //check if the line starts with printBoard:
        if (line.rfind("printBoard:", 0) == 0) {
            // Parse print board information
            // If an error occurs, log it
            std::string printInfo = line.substr(line.find(":") + 1);
            if (printInfo == "true") {
                printBoard = true;
            } else if (printInfo == "false") {
                printBoard = false;
            } else {
                log_error("Invalid print board value in input file: " + printInfo);
                continue;
            }
        }
        //skip empty lines
        if (line.empty()) {
            continue;
        }
        // Check for other game elements
        if(!line.empty()) {
            if (i >= height) {
                log_error("Number of rows in the board exceeds expected height. Expected: " + std::to_string(height) + ", but got: " + std::to_string(i));
                break; // Stop processing if we exceed the expected height
            }
            if (line[0]!= '~'){
                continue;; //not a board line
            }
            line = line.substr(1);
            for (char c : line)
            {
                if (j+1 > width) {
                    log_error("Row " + std::to_string(i) + " exceeds expected width. Expected: " + std::to_string(width) + ", but got: " + std::to_string(j));
                    break; // Stop processing this line
                }
                //fill the board
                if (c == '#') {
                    board[i][j] = '#'; // Wall
                } else if (c == '1') {
                    board[i][j] = '1'; // Tank1
                } else if (c == '2') {
                    board[i][j] = '2'; // Tank2
                } else if (c == '@') {
                    board[i][j] = '@'; // Mine
                } else if (c == ' ') {
                    board[i][j] = ' '; // Empty space
                } else {
                    log_error("Invalid character in input file: " + std::string(1, c));
                    //place an empty tile
                    board[i][j] = ' ';
                }
                j++;
            }
            // check if the row is not full and complete it
            if (j+1 < width) {
                log_error("Row " + std::to_string(i) + " is not full. Expected width: " + std::to_string(width) + ", but got: " + std::to_string(j));
                //fill the rest of the row with empty spaces
                for (int k = j; k < width; k++) {
                    board[i][k] = ' ';
                }
            }
            j = 0;
            i++;
        }
    }

    // Check if the board rows are as expected
    if (i < height) {
        log_error("Number of rows in the board does not match the expected height. Expected: " + std::to_string(height) + ", but got: " + std::to_string(i));
        // Fill the rest of the board with empty spaces
        for (int k = i; k < height; k++) {
            board[k] = (std::vector<char>(width, ' '));
        }
    }

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
    //put the tanks in the board
    if (x1Pos >= 0 && x1Pos < height && y1Pos >= 0 && y1Pos < width) {
        board[x1Pos][y1Pos] = '1'; // Tank1
    } else {
        log_error("Tank1 position is out of bounds: (" + std::to_string(x1Pos) + ", " + std::to_string(y1Pos) + ")");
        board[0][0] = '1';
    }
    if (x2Pos >= 0 && x2Pos < height && y2Pos >= 0 && y2Pos < width) {
        board[x2Pos][y2Pos] = '2'; // Tank2
    } else {
        log_error("Tank2 position is out of bounds: (" + std::to_string(x2Pos) + ", " + std::to_string(y2Pos) + ")");
        board[height-1][width-1] = '2';
    }

    game_manager.InitGame(width, height, board, printBoard, refreshRate); // Initialize the game with the board
    game_manager.GameLoop(); // Main game loop

    return 0;
}
