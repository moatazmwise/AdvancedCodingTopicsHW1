
#ifndef GameObject_h
#define GameObject_h

class GameObject
{
    protected:
        int id;
        std::vector<int> position;
        int health;
        
    public:
        //coonstructor
        GameObject(int id, std::vector<int> position, int health);
        //basic functions for every object on the board
        std::vector<int> getTankPosition() {}
        int getHealth() {}
};

#endif