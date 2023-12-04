#pragma once

#include <stdint.h>

#include "../Utils/HMath.h"
#include "ClientInstance.h"
#include "Entity.h"

class GameMode {
private:
	virtual __int64 destructorGameMode();
	// Duplicate destructor
public:
	virtual __int64 startDestroyBlock(Vec3i const &pos, unsigned char blockSide, bool &isDestroyedOut);
	virtual __int64 destroyBlock(Vec3i *, unsigned char);
	virtual __int64 continueDestroyBlock(Vec3i*, unsigned char blockSide, Vec3*, bool*);
	virtual __int64 stopDestroyBlock(Vec3i const &);
	virtual __int64 startBuildBlock(Vec3i const &, unsigned char);
	virtual __int64 buildBlock(Vec3i *, unsigned char, bool);
	virtual __int64 continueBuildBlock(Vec3i const &, unsigned char);
	virtual __int64 stopBuildBlock(void);
	virtual __int64 tick(void);

public:
	virtual __int64 getPickRange(__int64 const &, bool);
	virtual __int64 useItem(ItemStack &);
	virtual __int64 useItemOn(__int64 &, Vec3i const &, unsigned char, Vec3 const &, __int64 const *);
	virtual __int64 interact(Entity &, Vec3 const &);

public:
	virtual __int64 attack(Entity *);

public:
	virtual __int64 releaseUsingItem(void);

public:
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);

private:
	virtual __int64 registerUpsellScreenCallback(__int64);

public:
	Player *player;

	bool tryPlaceBlock(const Vec3i& BlockPos);

public:
	float getDestroyRate(Block* block) {
		using getDestroyRateFunc = float(__fastcall *)(GameMode*, Block*);
		static getDestroyRateFunc Func = (getDestroyRateFunc)(Utils::getBase() + 0x1DFA970);
		return Func(this, block);	
	}
};