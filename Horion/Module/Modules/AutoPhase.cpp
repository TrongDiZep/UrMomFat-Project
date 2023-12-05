#include "AutoPhase.h"

static bool abc = false;

AutoPhase::AutoPhase() : IModule(0, Category::MOVEMENT, "Clip to the nearest block.") {
}

AutoPhase::~AutoPhase() {
}

const char* AutoPhase::getModuleName() {
	return ("AutoPhase");
}
Vec3 AutoPhase::Center(const Vec3& pos, const Vec3& selectedBlock) {
	Vec3 phasePos = Vec3(floor(Game.getLocalPlayer()->getPos()->x), Game.getLocalPlayer()->getPos()->y, floor(Game.getLocalPlayer()->getPos()->z));
	int place = 0;
	if (selectedBlock == pos.add(1.f, 0.f, 0.f)) place = 1;
	if (selectedBlock == pos.add(-1.f, 0.f, 0.f)) place = 2;
	if (selectedBlock == pos.add(0.f, 0.f, 1.f)) place = 3;
	if (selectedBlock == pos.add(0.f, 0.f, -1.f)) place = 4;

	if (selectedBlock == pos.add(1.f, 0.f, 1.f)) place = 5;
	if (selectedBlock == pos.add(1.f, 0.f, -1.f)) place = 6;
	if (selectedBlock == pos.add(-1.f, 0.f, 1.f)) place = 7;
	if (selectedBlock == pos.add(-1.f, 0.f, -1.f)) place = 8;

	static const float offset1 = 0.8999f; //0.90f lagBack :skull:
	static const float offset2 = (1.f - offset1);

	if (place == 1) {
		phasePos.x += offset1;
		phasePos.z += 0.5f;
	}
	if (place == 2) {
		phasePos.x += offset2;
		phasePos.z += 0.5f;
	}
	if (place == 3) {
		phasePos.x += 0.5f;
		phasePos.z += offset1;
	}
	if (place == 4) {
		phasePos.x += 0.5f;
		phasePos.z += offset2;
	}
	if (place == 5) {
		phasePos.x += offset1;
		phasePos.z += offset1;
	}
	if (place == 6) {
		phasePos.x += offset1;
		phasePos.z += offset2;
	}
	if (place == 7) {
		phasePos.x += offset2;
		phasePos.z += offset1;
	}
	if (place == 8) {
		phasePos.x += offset2;
		phasePos.z += offset2;
	}

	//Game.getLocalPlayer()->setPos(phasePos);
	float dist = Game.getLocalPlayer()->eyePos0.dist(phasePos);
	if (dist > 0.01f && dist < 0.9f) Game.getLocalPlayer()->lerpTo(phasePos, Vec2(1, 1), (int)fmax((int)dist * 0.1, 1));

	return phasePos;
}

bool AutoPhase::isValidBlock(const Vec3& pos) {
	if (Game.getLocalPlayer()->region->getBlock(pos)->blockLegacy->blockId == 49 || Game.getLocalPlayer()->region->getBlock(pos)->blockLegacy->blockId == 7) return true;
	return false;
}

void AutoPhase::onDisable() {
	if (Game.getLocalPlayer() != nullptr) Game.getLocalPlayer()->aabb.upper.y = Game.getLocalPlayer()->aabb.lower.y + 1.6f;
}

void AutoPhase::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr) return;
	if (!Game.getLocalPlayer()->onGround) return;
	Vec3 pos = Game.getLocalPlayer()->getPos()->floor();
	pos.y -= 1.f;

	static std::vector<Vec3> checkList;
	checkList.clear();

	checkList.push_back(Vec3(pos.add(1.f, 0.f, 0.f)));
	checkList.push_back(Vec3(pos.add(-1.f, 0.f, 0.f)));
	checkList.push_back(Vec3(pos.add(0.f, 0.f, 1.f)));
	checkList.push_back(Vec3(pos.add(0.f, 0.f, -1.f)));

	checkList.push_back(Vec3(pos.add(1.f, 0.f, 1.f)));
	checkList.push_back(Vec3(pos.add(1.f, 0.f, -1.f)));
	checkList.push_back(Vec3(pos.add(-1.f, 0.f, 1.f)));
	checkList.push_back(Vec3(pos.add(-1.f, 0.f, -1.f)));

	Vec3 selectedBlock;

	bool shouldPhase = false;

	for (Vec3 checkPos : checkList) {
		if (isValidBlock(checkPos)) {
			selectedBlock = checkPos;
			shouldPhase = true;
		}
	}

	if (shouldPhase) {
		if (abc) {
			Center(pos, selectedBlock);
			gm->player->aabb.upper.y = gm->player->aabb.lower.y;
		} 
		else gm->player->aabb.upper.y = gm->player->aabb.lower.y + 1.6f;
	}

}

void AutoPhase::onMove(MoveInputHandler* hand) {
	if (hand->isJumping) {
		abc = false;
	} 
	else {
		if (hand->forward) {
			abc = false;
		} 
		else if (hand->backward) {
			abc = false;
		} 
		else if (hand->left) {
			abc = false;
		} 
		else if (hand->right) {
			abc = false;
		} 
		else
			abc = true;
	}
}
