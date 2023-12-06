#include "AutoPhase.h"

static bool abc = false;

AutoPhase::AutoPhase() : IModule(0, Category::MOVEMENT, "Clip to the nearest block.") {
}

AutoPhase::~AutoPhase() {
}

const char* AutoPhase::getModuleName() {
	return ("AutoPhase");
}

void AutoPhase::onDisable() {
}

void AutoPhase::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr) return;
	if (!Game.getLocalPlayer()->onGround) return;

	Vec3 playerPos = *Game.getLocalPlayer()->getPos();
	static const float offset = 0.1001f;
	gm->player->aabb.lower.x = playerPos.x - offset;
	gm->player->aabb.lower.z = playerPos.z - offset;
	gm->player->aabb.upper.x = playerPos.x + offset;
	gm->player->aabb.upper.z = playerPos.z + offset;
}
