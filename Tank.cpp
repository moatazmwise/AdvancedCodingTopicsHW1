#include "Tank.h"
//the main tank class

 
//tank main functions
Tank::Tank(int playerid, std::vector<int> position, std::vector<int> direction, int rows, int cols):
	GameObject(char(playerid), position, 1, rows, cols), shellcount(16), direction(direction), playerid(playerid)
    {}

void Tank::moveForward(bool forward) {
    if (forward) {
        position[0] += direction[0];
        position[1] += direction[1];
    }
    else {
        position[0] -= direction[0];
        position[1] -= direction[1];
    }
    // tanks move through the border of the map to the other side
    //using modol operator to wrap around the map
    position[0] = position[0] % cols;
    position[1] = position[1] % rows;
}
void Tank::turn(string orientation,int degrees) {
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
            // 45 degree rotation
            if (x == 0 || y == 0) {
                int new_x = (x != 0) ? x : (right ? -y : y);
                int new_y = (y != 0) ? y : (right ? x : -x);
                x = new_x;
                y = new_y;
            }
            else {
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
    }

bool Tank::shoot() {
	//shooting the shell
	return true;
}      

std::vector<int> Tank::getDirection() {
	return direction;
}

int Tank::getShellCount() {
	return shellcount;
}

int Tank::getPlayerid() {
	return playerid;
}
