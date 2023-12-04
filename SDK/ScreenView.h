#pragma once
#include "VisualTree.h"
#include "../../Utils/HMath.h"

class ScreenView {
public:
	float timeCounter1; // 0x0
	float deltaTime; // 0x4
	double timeCounter2; // 0x8
	Vec2 windowSize; // 0x10
private:
	char pad_0x18[0x30]; // 0x18
public:
	VisualTree* visualTree; //0x48
};