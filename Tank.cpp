#include "Tank.h"

	
	Tank::Tank(int playerid,  const std::vector<int>& position, const std::vector<int>& direction):
     GameObject(char('0' + playerid), position, 1),
    direction{direction[0], direction[1]}, playerid(playerid), shellcounter(16) {}


	int Tank::getPlayerid() const{
        return playerid;
    }

    int Tank::getShellcounter() const{
        return shellcounter;
    }

	std::vector<int> Tank::getDirection() const{
        return direction;
    }

	
	void Tank::moveForward(bool forward, const Board& board){
        int delta_x = direction[0] * (forward ? 1 : -1);
        int delta_y = direction[1] * (forward ? 1 : -1);

        int x = position[0] + delta_x;
        int y = position[1] + delta_y;
        board.manipulate_cords(x, y);
        position = {x, y};


    }

	void Tank::turn(const std::string& orientation, int degrees){

        bool right = (orientation == "right");
    int& x = direction[0];
    int& y = direction[1];

    if (degrees == 90) {
        int x1 = right ? -y : y;
        y = right ? x : -x;
        x = x1;}
    else if (degrees == 45) {
        if (x == 0 || y == 0) {
            int x1 = (x != 0) ? x : (right ? -y : y);
            int y1 = (y != 0) ? y : (right ? x : -x);
            x = x1;
            y = y1;}
         else {
            int x1 = right ? (y > 0 ? 1 : -1) : (y > 0 ? -1 : 1);
            int y1 = right ? (x < 0 ? 1 : -1) : (x < 0 ? -1 : 1);
            x = x1;
            y = y1;
        }}
    else {
        // Invalid rotation angle; no change
    }

    
    }
    

	bool Tank::shoot(){
        if (shellcounter > 0) {
            --shellcounter;
            return true;
        }
        return false;
    }

	

