#include "Tank.h"
#include "GameManager.h"

Tank::Tank(int r, int c, int dR, int dC, GameManager* gm, char tankSymbol, TankBot* bot)
    : GameObject(r, c, dR, dC, 1, gm), ammo(16), playerNum(0), shotCooldown(0), isReversing(false), reverseDelay(0), tankBot(bot) {
    symbol = tankSymbol;
}

std::string Tank::GetType() const {
    return "tank";
}

void Tank::Update(int turnNum) {
    GameObject::Update();
    if (shotCooldown > 0) {
        shotCooldown--;
    }
    if (initReverse && reverseDelay > 0) {
        reverseDelay--;
    }

    if (!tankBot) return;
    std::string action = tankBot->Decide(manager->GetBoard(), playerNum, turnNum);

    
    if (action == "f") MoveForward();
    else if (!initReverse) {
        if (action == "b") ReverseRequest();
        else if (action == "S") Shoot();
        else if (action == "RC45") Rotate45(true);
        else if (action == "RC90") Rotate90(true);
        else if (action == "RCC45") Rotate45(false);
        else if (action == "RCC90") Rotate90(false);
    } else {
        std::string move = " ";
        if (action == "f") move = "MoveForward";
        else if (action == "b") move = "Reverse";
        else if (action == "S") move = "Shoot";
        else if (action == "RC45") move = "Rotate 45 degrees clockwise";
        else if (action == "RC90") move = "Rotate 90 degrees clockwise";
        else if (action == "RCC45") move = "Rotate 45 degrees counterclockwise";
        else if (action == "RCC90") move = "Rotate 90 degrees counterclockwise";

        logMove("Tank " + std::to_string(playerNum) + " attempted to " + move + " bad move");
    }
}

bool Tank::Shoot() {
    isReversing = false;
    if (shotCooldown > 0) {
        logMove("Tank " + std::to_string(playerNum) + " attempted to shoot but is on cooldown bad move");
        return false;
    }
    if (ammo > 0) {
        //check if the tile in front of the tank is empty
        GameObject* obj = manager->GetGameObject(GetRow(), GetCol(), GetDirRow(), GetDirCol());
        if (obj == nullptr) {
            // instantiate a shell in front of the tank
            manager->Instantiate<Shell>(GetRow(), GetCol(), GetDirRow(), GetDirCol(), GetDirRow(), GetDirCol());
        } else if (obj->GetType() == "mine") {
            // replace the mine with a shell
            manager->Destroy(obj);
            Shell* shell = manager->Instantiate<Shell>(GetRow(), GetCol(), GetDirRow(), GetDirCol(), GetDirRow(), GetDirCol());
            shell->SetOverMine(true);
        } else {
            //damage the object in front of the tank without instantiating a shell
            obj->Damage(1);
        }
        ammo--;
        shotCooldown = 5;
        logMove("Tank " + std::to_string(playerNum) + " shot a shell and has " + std::to_string(ammo) + " ammo left");
        return true;
    }
    logMove("Tank " + std::to_string(playerNum) + " attempted to shoot but is out of ammo bad move");
    return false;
}

void Tank::MoveForward() {
    isReversing = false;
    if (initReverse) {
        initReverse = false; // Stop reversing when moving forward
        logMove("Tank " + std::to_string(playerNum) + " stopped reversing attempt");
    }
    else if (Translate(1) == 0){
        // Check for collision with other objects
        GameObject* obj = manager->GetGameObject(GetRow(), GetCol(), GetDirRow(), GetDirCol());
        std::string objType = obj->GetType();
        if (objType == "mine" || objType == "shell" || objType == "tank") {
            obj->Damage(1); // Damage the object in front
            Damage(1); // Damage the tank itself
            logMove("Tank " + std::to_string(playerNum) + " collided with " + objType + " while moving forward and exploded");
        }
        else logMove("Tank " + std::to_string(playerNum) + " moved forward and collided with " + objType + " bad move");
    }
    else logMove("Tank " + std::to_string(playerNum) + " moved forward");
}

void Tank::ReverseRequest() {
    if (!initReverse && !isReversing) {
        initReverse = true;
        reverseDelay = 3;
        logMove("Tank " + std::to_string(playerNum) + " attempting to reverse");
    }
    if (isReversing){
        Reverse();
    }
    if (initReverse && reverseDelay == 0) {
        initReverse = false;
        isReversing = true;
        Reverse();
    }

}

void Tank::Reverse() {
    if(Translate(-1) == 0) {
        // Check for collision with other objects
        GameObject* obj = manager->GetGameObject(GetRow(), GetCol(), -GetDirRow(), -GetDirCol());
        std::string objType = obj->GetType();
        if (objType == "mine" || objType == "shell" || objType == "tank") {
            obj->Damage(1); // Damage the object in front
            Damage(1); // Damage the tank itself
            logMove("Tank " + std::to_string(playerNum) + " collided with " + objType + " while reversing and exploded");
        }
        else logMove("Tank " + std::to_string(playerNum) + " moved backward and collided with " + objType + " bad move");
    }
    logMove("Tank " + std::to_string(playerNum) + " moved backward");
}
void Tank::Rotate45(bool clockwise) {
    isReversing = false;
    if (clockwise) RotateClockwise();
    else RotateCounterClockwise();
    logMove("Tank " + std::to_string(playerNum) + " rotated 45 degrees " + (clockwise ? "clockwise" : "counterclockwise"));
}

void Tank::Rotate90(bool clockwise) {
    Rotate45(clockwise);
    Rotate45(clockwise);
    logMove("Tank " + std::to_string(playerNum) + " rotated 90 degrees " + (clockwise ? "clockwise" : "counterclockwise"));
}

void Tank::logMove(const std::string& action) const {
    std::ofstream file("OutputLog.txt", std::ios::app);  // append mode
    if (!file) return; // Fail silently if file can't be opened
    file << "Tank " << playerNum << ": " << action << '\n';
}