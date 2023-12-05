#pragma once

#include "Module.h"

class AutoPhase : public IModule {
private:

public:
	AutoPhase();
	~AutoPhase();

	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onMove(MoveInputHandler* hand) override;
};
