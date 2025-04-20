
#include <string>
#include <array>
#include<vector>
#include "GameObject.h"
#include"Board.h"

using namespace std;
class Tank : public GameObject
{
private:
	/* data */
	int shellcounter;
	std::vector<int> direction;
	int playerid;

public:
	//tank main functions
	Tank(int playerid, const std::vector<int>& position, const std::vector<int>& direction);

	int getPlayerid() const;

    int getShellcounter() const;

	std::vector<int> getDirection() const;

	
	void moveForward(bool forward, const Board& board);

	void turn(const std::string& orientation, int degrees);

	bool shoot();

	
};



