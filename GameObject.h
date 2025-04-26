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
    bool updated = true;

    std::vector<std::pair<int, int>> rotate_clockwise = {
        {-1,  0}, // index 0 = input (-1, -1) 
        {-1, -1}, // index 1 = input ( 0, -1)
        { 0, -1}, // index 2 = input ( 1, -1)
        {-1,  1}, // index 3 = input (-1,  0)
        { 0,  0}, // index 4 = input ( 0,  0)
        { 1, -1}, // index 5 = input ( 1,  0)
        { 0,  1}, // index 6 = input (-1,  1)
        { 1,  1}, // index 7 = input ( 0,  1)
        { 1,  0}  // index 8 = input ( 1,  1)
    };

protected:
    GameManager* manager;
    char symbol;

public:
    GameObject(int r, int c, int dR, int dC, int hp, GameManager* gm);

    virtual std::string GetType() const = 0;
    virtual void Update();
    void ResetUpdated();
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
    bool IsUpdated() const { return updated; }
    int GetTurnNum() const { return manager->GetTurnNum(); }

    friend class GameManager;
};

class Wall : public GameObject {
public:
    Wall(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update();
};

class Mine : public GameObject {
public:
    Mine(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update();
};

class Shell : public GameObject {
private:
    bool isOverMine = false;
public:
    Shell(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update();
    void SetOverMine(bool overMine) { isOverMine = overMine; }
};