//tank main prototype functions
#include <string>
#include <array>
#include<vector>
#include "GameObject.h"
using namespace std;
class Tank : public GameObject
{
private:
	/* data */
	int shellcount;
	std::vector<int> direction;
	int playerid;

public:
	//tank main functions
	Tank(int playerid, std::vector<int> position, std::vector<int> direction, int rows, int cols);

	//tank main prototype functions
	void moveForward(bool forward);
	void turn(string orientation, int degrees);
	bool shoot();

	//get tank info functions
	std::vector<int> getDirection();
	int getPlayerid();
	int getShellCount();
};