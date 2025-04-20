#include "GameObject.h"

class Wall : public GameObject
{
public:
    Wall(char id, const std::vector<int>& position);
    void decreaseHealth();
};