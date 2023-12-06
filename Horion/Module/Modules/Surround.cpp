#include "Surround.h"
#include "Notifications.h"

Surround::Surround() : IModule(0, Category::COMBAT, "nigger") {
	registerBoolSetting("Center", &center, center);
	registerBoolSetting("DisableComplete", &disableComplete, disableComplete);
//	registerBoolSetting("Spoof", &spoof, spoof);
//	spoofMode.addEntry("Nukkit", 0);
//	spoofMode.addEntry("Geyser", 1);
//	registerEnumSetting("Spoof Mode", &spoofMode, 0);
}

const char* Surround::getModuleName() {
	return "Surround";
}

const char* Surround::getModName() {
	return nullptr;
}

void Surround::onEnable() {
	LocalPlayer* lp = Game.getLocalPlayer();
	if (lp == nullptr) return;
	if (center) {
		Vec3 playerPos = lp->eyePos0;
		Vec3 yR = Vec3(floor(playerPos.x), playerPos.y, floor(playerPos.z));
		yR.x += 0.5f;
		yR.z += 0.5f;
		lp->setPos(yR);
	}
}

void Surround::getObsidian() {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr) return;
	PlayerInventoryProxy* supplies = localPlayer->getSupplies();
	Inventory* inv = supplies->inventory;
	for (int i = 0; i < 9; i++) {
		ItemStack* stack = inv->getItemStack(i);
		if (stack->isValid()) {
			if (stack->getItem()->itemId == 49) {
				supplies->selectedHotbarSlot = i;
				return;
			}
		}
	}
	Notifications::addNotifBox("You need Obsidian in hotbar to use Surround!", 4.f);
	this->setEnabled(false);
}

bool Surround::IsSideEmpty() {
	LocalPlayer* lp = Game.getLocalPlayer();
	BlockSource* region = lp->region;
	for (const Vec3& checkThis : sidesBlocksOnly) {
		Vec3 playerPos = lp->eyePos0;
		Vec3 rndOffPlayerOn = playerPos.floor();
		rndOffPlayerOn.y -= 1.f;

		Vec3i calcSides = rndOffPlayerOn.add(checkThis);
		if (region->getBlock(calcSides)->toLegacy()->blockId == 0) {
			return true;
		}
	}
	return false;
}

void Surround::onTick(GameMode* gm) {
	LocalPlayer* lp = Game.getLocalPlayer();
	PlayerInventoryProxy* supplies = lp->getSupplies();
	Inventory* inv = supplies->inventory;

	if (IsSideEmpty()) {
		int oldSlot = supplies->selectedHotbarSlot;
		getObsidian();
		if (lp->getSelectedItemId() == 49) {
			Vec3 playerPos = Game.getLocalPlayer()->eyePos0;
			Vec3 rndOffPlayerOn = playerPos.floor();
			rndOffPlayerOn.y -= 1.f;

			for (const Vec3& check : sidesBlocksOnly) {
				Vec3i blockPos = rndOffPlayerOn.add(check);
				gm->tryPlaceBlock(blockPos);
			}
		}
		supplies->selectedHotbarSlot = oldSlot;
	}
}