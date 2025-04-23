#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject(int r, int c, int dR, int dC, int hp, GameManager* gm)
    : row(r), col(c), dirRow(dR), dirCol(dC), health(hp), manager(gm), symbol('?') {}

int GameObject::Translate(int amount) {
    return manager->Translate(this, amount);
}

void GameObject::RotateClockwise() {
    int newRow = dirCol;
    int newCol = -dirRow;
    dirRow = newRow;
    dirCol = newCol;
}

void GameObject::RotateCounterClockwise() {
    int newRow = -dirCol;
    int newCol = dirRow;
    dirRow = newRow;
    dirCol = newCol;
}

void GameObject::Damage(int amount) {
    health -= amount;
    if (health <= 0) {
        manager->Destroy(this);
    }
}

Wall::Wall(int r, int c, GameManager* gm) : GameObject(r, c, 0, 0, 1000, gm) {
    symbol = '#';
}

std::string Wall::GetType() const {
    return "Wall";
}

void Wall::Update() {
    // To be implemented
}

Mine::Mine(int r, int c, GameManager* gm) : GameObject(r, c, 0, 0, 1, gm) {
    symbol = '@';
}

std::string Mine::GetType() const {
    return "Mine";
}

void Mine::Update() {
    // To be implemented
}

Shell::Shell(int r, int c, int dR, int dC, GameManager* gm) : GameObject(r, c, dR, dC, 1, gm) {
    symbol = '*';
}

std::string Shell::GetType() const {
    return "Shell";
}

void Shell::Update() {
    // To be implemented
}