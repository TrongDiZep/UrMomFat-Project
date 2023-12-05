#pragma once

#include "Module.h"

class AutoPhase : public IModule {
protected:
	Vec3 Center(const Vec3& pos, const Vec3& selectedBlock);
	bool isValidBlock(const Vec3& pos);
public:
	AutoPhase();
	~AutoPhase();

	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onMove(MoveInputHandler* hand) override;
};
