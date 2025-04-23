#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include "TankBot.h"

class Tank : public GameObject {
private:
	int ammo;
	int playerNum;
	int shotCooldown;
	bool isReversing;
	int reverseDelay;
	TankBot* tankBot;

public:
	Tank(int r, int c, int dR, int dC, GameManager* gm, char tankSymbol, TankBot* bot);
	std::string GetType() const override;
	void Update() override;

	bool Shoot();
	void MoveForward();
	void Reverse();
	void Rotate45(bool clockwise);
	void Rotate90(bool clockwise);
};