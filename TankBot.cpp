#include "TankBot.h"

std::string AggressiveBot::Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum) {
    // Implement aggressive strategy here
    return "f"; // Move forward as an example
}

std::string DefensiveBot::Decide(const std::vector<std::vector<GameObject*>>& board, int playerNum) {
    // Implement defensive strategy here
    return "b"; // Move backward as an example
}

/*
    MOVEMENT COMMANDS:
    output: f, b, S, RC45, RC90, RCC45, RCC90 as string
    move forward: f
    move backward: b
    shoot: S
    rotate clockwise 45 degrees: RC45
    rotate clockwise 90 degrees: RC90
    rotate counter clockwise 45 degrees: RCC45
    rotate counter clockwise 90 degrees: RCC90

*/