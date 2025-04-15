#include "Tank.h"
//the main tank class

class Tank : public GameObject
{
    private:
    /* data */
    int shellcount;
    int rows;
    int cols;
    std::vector<int> direction;

    public:
    //tank main functions
    Tank::Tank(int id, std::vector<int> position, std::vector<int> direction):
        GameObject(id, position, 1), shellcount(16), direction(direction)
    {}

    void moveForward(bool forward) {
        if (forward) {
            position[0] += direction[0];
            position[1] += direction[1];
        } else {
            position[0] -= direction[0];
            position[1] -= direction[1];
        }
        // tanks move through the border of the map to the other side
        //using modol operator to wrap around the map
        position[0] = position[0] % cols;
        position[1] = position[1] % rows;
    }
    void turn(string orientation,int degrees) {
        //turning the tank in the direction of the degrees
        bool right = 0;
        if (orientation == "left")right = false;
        else if (orientation == "right")right = true;

        int& x = direction[0]; // Reference to modify x directly
        int& y = direction[1]; // Reference to modify y directly

        if (degrees == 90) {
            // 90° rotation (swap x/y and flip one sign)
            int new_x = right ? -y : y;
            y = right ? x : -x;
            x = new_x;
        }
        else if (degrees == 45) {
            // 45° rotation (axis-aligned ↔ diagonal)
            if (x == 0 || y == 0) {
                // Axis-aligned → diagonal
                int new_x = (x != 0) ? x : (right ? -y : y);
                int new_y = (y != 0) ? y : (right ? x : -x);
                x = new_x;
                y = new_y;
            }
            else {
                // Diagonal → axis-aligned
                if (right) {
                    x = (x == y) ? x : 0;
                    y = (x == y) ? 0 : y;
                }
                else {
                    x = (x != y) ? 0 : x;
                    y = (x != y) ? y : 0;
                }
            }
        }
        // Else: Invalid angle (do nothing)
    }

    bool shoot() {}
        
    std::vector<int> getTankPosition() {}
    std::vector<int> getTankDirection() {}
    int getShellCount() {}
            
};
