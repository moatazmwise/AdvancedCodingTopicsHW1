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
    std::string deathMessage = "GameObject destroyed";
    char symbol;

public:
    GameObject(int r, int c, int dR, int dC, int hp, GameManager* gm);

    virtual std::string GetType() const = 0;
    virtual void Update(int turnNum = 0);
    void ResetUpdated();
    int Translate(int amount);
    void RotateClockwise();
    void RotateCounterClockwise();
    void Damage(int amount, std::string damagerMessage = "none");

    int GetRow() const { return row; }
    int GetCol() const { return col; }
    int GetDirRow() const { return dirRow; }
    int GetDirCol() const { return dirCol; }
    int GetHealth() const { return health; }
    virtual void GetSymbol(char* symbol) const;
    bool IsUpdated() const { return updated; }
    std::string GetDeathMessage() const { return deathMessage; }

    friend class GameManager;
};

class Wall : public GameObject {
public:
    Wall(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update(int turnNum = 0);
};

class Mine : public GameObject {
public:
    Mine(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update(int turnNum = 0);
};

class Shell : public GameObject {
private:
    bool isOverMine = false;
    int playerNum = 0;
public:
    Shell(int r, int c, int dR, int dC, GameManager* gm);
    std::string GetType() const override;
    void Update(int turnNum = 0);
    void SetOverMine(bool overMine) { isOverMine = overMine; }
    void setPlayerNum(int num) { playerNum = num; }
    void GetSymbol(char* symbol) const override;
};