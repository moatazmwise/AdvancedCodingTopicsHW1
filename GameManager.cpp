#include "GameManager.h"
#include <iostream>
#include <thread>
#include <chrono>

void GameManager::InitGame(int r, int c, std::vector<std::vector<char>> boardInput) {
    rows = r;
    cols = c;
    board.resize(rows, std::vector<GameObject*>(cols, nullptr));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char c = boardInput[i][j];
            if (c == '#') {
                Instantiate<Wall>(i, j);
            } else if (c == '@') {
                Instantiate<Mine>(i, j);
            } else if (c == '1') {
                player1 = Instantiate<Tank>(i, j, 0, 1);
                player1->SetPlayerNum(1);
                player1->ResetUpdated();
                player1->SetTankBot(new AggressiveBot());
                player1->symbol = '1';
            } else if (c == '2') {
                player2 = Instantiate<Tank>(i, j, 0, -1);
                player2->SetPlayerNum(2);
                player2->ResetUpdated();
                player2->SetTankBot(new DefensiveBot());
                player2->symbol = '2';
            } else if (c == ' ') {
                // Empty space, do nothing
            }
        }
    }
    
}

void GameManager::GameLoop(){
    // Main game loop
    int noAmmo = 0;
    while (true) { 
        PrintBoard();

        // check if both tamks ran out of ammo if so end the game after 40 turns
        if (player1->GetAmmo() <= 0 && player2->GetAmmo() <= 0) {
            noAmmo++;
        }
        // Update all game objects
        player1->Update(turnNum);
        //check if player 2 is dead
        if (player2->GetHealth() > 0) {
            player2->Update(turnNum);
        }
        // Update all game objects on the board
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] && !board[i][j]->IsUpdated()) {
                    board[i][j]->Update(turnNum);
                }
            }
        }
        // Clear the updated flag for the next iteration
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j]) {
                    board[i][j]->ResetUpdated();
                }
            }
        }
        // wait for user input or a timer then clear the screen
        std::cout << turnNum;
        std::this_thread::sleep_for(std::chrono::seconds(refreshRate/1000));
        std::cout << "\033[2J\033[H";
        #ifdef _WIN32
            system("cls"); // Clear console on Windows
        #else
            std::cout << "\033[2J\033[H"; // Clear console on Linux/macOS
        #endif
        turnNum++;
        
        if (EndGame() || noAmmo >= 40) {
            break; // Exit the loop if game over
        }
    }
}

bool GameManager::EndGame(){
     // Check for game over conditions
     if (player1->GetHealth() <= 0 && player2->GetHealth() <= 0) {
        std::cout << "Game Over! DRAW! " << std::endl;
        logMove("Game Over! DRAW!");
        std::cout << "player 1 " + player1->GetDeathMessage() << std::endl;
        logMove("player 1 " + player1->GetDeathMessage());
        std::cout << "player 2 " + player2->GetDeathMessage() << std::endl;
        logMove("player 2 " + player2->GetDeathMessage());
        return true;
    } else if (player1->GetHealth() <= 0) {
        std::cout << "Player 2 wins!" << std::endl;
        logMove("Player 2 wins!");
        std::cout << "player 1 " + player1->GetDeathMessage() << std::endl;
        logMove("player 1 " + player1->GetDeathMessage());
        return true;
    } else if (player2->GetHealth() <= 0) {
        std::cout << "Player 1 wins!" << std::endl;
        logMove("Player 1 wins!");
        std::cout << "player 2 " + player2->GetDeathMessage() << std::endl;
        logMove("player 2 " + player2->GetDeathMessage());
        return true;
    }
    return false;
}

void GameManager::PrintBoard() const {
    //print the board with symbols and one space between each symbol
    for (int i = 0; i < rows; ++i) {
        std::cout << " "; 
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] != nullptr) {
                std::cout << board[i][j]->GetSymbol() << " ";
            } else {
                std::cout << "  "; 
            }
        }
        std::cout << std::endl;
        std::cout << std::endl; // Extra space between rows
    }
}

int GameManager::Translate(GameObject* obj, int amount) {
    int moved = 0;
    int r = obj->row;
    int c = obj->col;

    for (int i = 0; i < amount; ++i) {
        int newR = (r + obj->dirRow + rows) % rows;
        int newC = (c + obj->dirCol + cols) % cols;

        if (board[newR][newC] == nullptr) {
            board[r][c] = nullptr;
            board[newR][newC] = obj;
            r = newR;
            c = newC;
            moved++;
        } else {
            break;
        }
    }
    obj->row = r;
    obj->col = c;
    return moved;
}

void GameManager::Destroy(GameObject* obj) {
    int r = obj->row;
    int c = obj->col;
    if (board[r][c] == obj) {
        board[r][c] = nullptr;
    }
}

GameObject* GameManager::GetGameObject(int r, int c, int offsetR, int offsetC) {
    r = (r + offsetR + rows) % rows;
    c = (c + offsetC + cols) % cols;
    return board[r][c];
}

const std::vector<std::vector<GameObject*>>& GameManager::GetBoard() const {
    return board;
}

void GameManager::logMove(const std::string& message) const {
    std::ofstream file("OutputLog.txt", std::ios::app);  // append mode
    if (!file) return; // Fail silently if file can't be opened
    file << message << '\n';
}