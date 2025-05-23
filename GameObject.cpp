#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject(int r, int c, int dR, int dC, int hp, GameManager* gm)
    : row(r), col(c), dirRow(dR), dirCol(dC), health(hp), manager(gm), symbol('?') {}

int GameObject::Translate(int amount) {
    return manager->Translate(this, amount);
}

void GameObject::Update(int turnNum) {
    (void)turnNum; // Unused parameter
    updated = true;
}

void GameObject::ResetUpdated() {
    updated = false;
}

void GameObject::RotateClockwise() {
    auto[newdirCol, newdirRow] = rotate_clockwise[3*dirRow + dirCol + 4];
    dirRow = newdirRow;
    dirCol = newdirCol;
}

void GameObject::RotateCounterClockwise() {
    auto[newdirCol, newdirRow] = rotate_clockwise[3*dirCol + dirRow + 4];
    dirCol= newdirRow;
    dirRow = newdirCol;
}

void GameObject::Damage(int amount, std::string damagerMessage) {
    health -= amount;
    deathMessage = damagerMessage;
    if (health <= 0) {
        manager->Destroy(this);
    }
}

void GameObject::GetSymbol(char* symbol) const {
    for (int i = 0; i < 9; ++i) {
        symbol[i] = this->symbol;
    }
}

Wall::Wall(int r, int c, int dR, int dC, GameManager* gm) : GameObject(r, c, dR, dC, 2, gm) {
    symbol = '#';
}

std::string Wall::GetType() const {
    return "wall";
}

void Wall::Update(int turnNum) {
    (void)turnNum; // Unused parameter
    GameObject::Update();
}

Mine::Mine(int r, int c, int dR, int dC, GameManager* gm) : GameObject(r, c, dR, dC, 1, gm) {
    symbol = '@';
}

std::string Mine::GetType() const {
    return "mine";
}

void Mine::Update(int turnNum) {
    (void)turnNum; // Unused parameter
    GameObject::Update();
}

void Mine::GetSymbol(char* symbol) const {
    for (int i = 0; i < 9; ++i) {
        if (i%2 == 0) {
            symbol[i] = this->symbol;
        } else {
            symbol[i] = ' ';
        }
    }
}

Shell::Shell(int r, int c, int dR, int dC, GameManager* gm) : GameObject(r, c, dR, dC, 1, gm) {
    symbol = '*';
}

void Shell::GetSymbol(char* symbol) const {
    if (isOverMine) {
        for (int i = 0; i < 9; ++i) {
            if (i%2 == 0) {
                symbol[i] = '@';
            } else {
                symbol[i] = ' ';
            }
        }
        symbol[4] = this->symbol;
    } else {
        for (int i = 0; i < 9; ++i) {
            symbol[i] = ' ';
        }
        symbol[4] = this->symbol;
    }
}

std::string Shell::GetType() const {
    return "shell";
}

void Shell::Update(int turnNum) {
    (void)turnNum; // Unused parameter
    GameObject::Update();
    for (int i = 0; i < 2; ++i) {
        int m = Translate(1);
        bool isMine = false;
        if (m == 0){
            //check if the tile in front of the shell is a mine
            GameObject* obj = manager->GetGameObject(GetRow(), GetCol(), GetDirRow(), GetDirCol());
            isMine = (obj != nullptr && obj->GetType() == "mine");
            if (isMine) {
                manager->Destroy(obj);
                m = Translate(1);
            }
        }

        if (m == 0) {
            //damage the object in front of the shell
            GameObject* obj = manager->GetGameObject(GetRow(), GetCol(), GetDirRow(), GetDirCol());
            obj->Damage(1, "destroyed by a shell from player " + std::to_string(playerNum));
            Damage(1);
        }

        if (isOverMine) {
            //restore previous mine
            if (m == 0) {
                manager->Instantiate<Mine>(GetRow(), GetCol(), 0, 0);
            } else {
                manager->Instantiate<Mine>(GetRow(), GetCol(), 0, 0, -GetDirRow(), -GetDirCol());
            }
        }

        isOverMine = isMine;

        if (m == 0) {
            return; // if the shell is destroyed exit
        }
    }
}