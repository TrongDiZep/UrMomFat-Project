#pragma once

#include "Module.h"

class NoPacket : public IModule {
public:
	bool SoundPacket = false;
	NoPacket();
	~NoPacket();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	bool allowAutoStart() override;
	void onEnable() override;
};
