#pragma once
#include "GameObject.h"
#include "TankBot.h"
#include <fstream>

class Tank : public GameObject {
private:
	int ammo;
	int playerNum;
	int shotCooldown;
	bool isReversing;
	bool initReverse = false;
	int reverseDelay;
	TankBot* tankBot;

public:
	Tank(int r, int c, int dR, int dC, GameManager* gm, char tankSymbol = 'T', TankBot* bot = nullptr);
	std::string GetType() const override;
	void Update(int turnNum) override;

	bool Shoot();
	void MoveForward();
	void Reverse();
	void ReverseRequest();
	void Rotate45(bool clockwise);
	void Rotate90(bool clockwise);
	void logMove(const std::string& action) const;
	void GetSymbol(char* symbol) const override;

	int GetAmmo() const { return ammo; }
	void SetPlayerNum(int num) { playerNum = num; }
	int GetPlayerNum() const { return playerNum; }
	void SetTankBot(TankBot* bot) { tankBot = bot; }
};