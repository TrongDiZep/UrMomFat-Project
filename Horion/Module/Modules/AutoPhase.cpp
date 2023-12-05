#include "AutoPhase.h"

static bool abc = false;

AutoPhase::AutoPhase() : IModule(0, Category::MOVEMENT, "Clip to the nearest block.") {
}

AutoPhase::~AutoPhase() {
}

const char* AutoPhase::getModuleName() {
	return ("AutoPhase");
}
Vec3 Center(Vec3 pos, Vec3 selectedBlock) {
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

	if (place == 1) {
		phasePos.x += 0.85f;
		phasePos.z += 0.5f;
	}
	if (place == 2) {
		phasePos.x += 0.15f;
		phasePos.z += 0.5f;
	}
	if (place == 3) {
		phasePos.x += 0.5f;
		phasePos.z += 0.85f;
	}
	if (place == 4) {
		phasePos.x += 0.5f;
		phasePos.z += 0.15f;
	}
	if (place == 5) {
		phasePos.x += 0.85f;
		phasePos.z += 0.85f;
	}
	if (place == 6) {
		phasePos.x += 0.85f;
		phasePos.z += 0.15f;
	}
	if (place == 7) {
		phasePos.x += 0.15f;
		phasePos.z += 0.85f;
	}
	if (place == 8) {
		phasePos.x += 0.15f;
		phasePos.z += 0.15f;
	}

	//Game.getLocalPlayer()->setPos(phasePos);
	float dist = Game.getLocalPlayer()->getPos()->dist(phasePos);
	Game.getLocalPlayer()->lerpTo(phasePos, Vec2(1, 1), (int)fmax((int)dist * 0.1, 1));
	Game.getLocalPlayer()->lerpMotion(phasePos);

	return phasePos;
}

bool isValidBlock(Vec3 pos) {
	if (Game.getLocalPlayer()->region->getBlock(pos)->blockLegacy->blockId == 49 || Game.getLocalPlayer()->region->getBlock(pos)->blockLegacy->blockId == 7) return true;
	return false;
}

std::vector<Vec3> checkList;

void AutoPhase::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr) return;

	Vec3 pos = Game.getLocalPlayer()->getPos()->floor();
	pos.y -= 1.f;

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
		else if (gm->player->aabb.upper.y = gm->player->aabb.lower.y) Game.getLocalPlayer()->aabb.upper.y += 1.8f;
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
