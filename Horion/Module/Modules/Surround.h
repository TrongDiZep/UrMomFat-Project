#pragma once
#include "Module.h"

class Surround : public IModule {
private:
	bool disableComplete = false;
	bool center = true;
	bool spoof = true;
	SettingEnum spoofMode = SettingEnum(this);

protected:
	Vec3 regularBlocks[9] = {
		Vec3(0, -1, 0),
		Vec3(1, -1, 0),
		Vec3(1, 0, 0),
		Vec3(0, -1, 1),
		Vec3(0, 0, 1),
		Vec3(-1, -1, 0),
		Vec3(-1, 0, 0),
		Vec3(0, -1, -1),
		Vec3(0, 0, -1)
	};
	Vec3 sidesBlocksOnly[5] = {
		Vec3(1, 0, 0),
		Vec3(0, 0, 1),
		Vec3(-1, 0, 0),
		Vec3(0, 0, -1),
		Vec3(0, -1, 0)
	};
	void getObsidian();
	bool IsSideEmpty();

public:
	Surround();

	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
};