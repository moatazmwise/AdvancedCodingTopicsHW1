#include "Tank.h" 

Tank::Tank(int r, int c, int dR, int dC, GameManager* gm, char tankSymbol, TankBot* bot)
    : GameObject(r, c, dR, dC, 100, gm), ammo(10), playerNum(0), shotCooldown(0), isReversing(false), reverseDelay(0), tankBot(bot) {
    symbol = tankSymbol;
}

std::string Tank::GetType() const {
    return "Tank";
}

void Tank::Update() {
    if (!tankBot) return;
    std::string action = tankBot->Decide(manager->GetBoard(), playerNum);

    if (action == "f") MoveForward();
    else if (action == "b") Reverse();
    else if (action == "S") Shoot();
    else if (action == "RC45") Rotate45(true);
    else if (action == "RC90") Rotate90(true);
    else if (action == "RCC45") Rotate45(false);
    else if (action == "RCC90") Rotate90(false);
}

bool Tank::Shoot() {
    // To be implemented
    return false;
}

void Tank::MoveForward() {
    Translate(1);
}

void Tank::Reverse() {
    isReversing = true;
    reverseDelay = 2; // Example delay
}

void Tank::Rotate45(bool clockwise) {
    if (clockwise) RotateClockwise();
    else RotateCounterClockwise();
}

void Tank::Rotate90(bool clockwise) {
    Rotate45(clockwise);
    Rotate45(clockwise);
}