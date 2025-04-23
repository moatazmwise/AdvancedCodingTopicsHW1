#pragma once
#include <string>
#include <vector>

class GameManager; // Forward declaration
class TankBot; // Forward declaration

class GameObject {
private:
    int row;
    int col;
    int dirRow; // -1, 0, 1
    int dirCol; // -1, 0, 1
    int health;

protected:
    GameManager* manager;
    char symbol;

public:
    GameObject(int r, int c, int dR, int dC, int hp, GameManager* gm);

    virtual std::string GetType() const = 0;
    virtual void Update() = 0;
    int Translate(int amount);
    void RotateClockwise();
    void RotateCounterClockwise();
    void Damage(int amount);

    int GetRow() const { return row; }
    int GetCol() const { return col; }
    int GetDirRow() const { return dirRow; }
    int GetDirCol() const { return dirCol; }
    int GetHealth() const { return health; }
    char GetSymbol() const { return symbol; }

    friend class GameManager;
};

class Wall : public GameObject {
public:
    Wall(int r, int c, GameManager* gm);
    std::string GetType() const override;
    void Update() override;
};

class Mine : public GameObject {
public:
    Mine(int r, int c, GameManager* gm);
    std::string GetType() const override;
    void Update() override;
};

class Shell : public GameObject {
public:
    Shell(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update() override;
};