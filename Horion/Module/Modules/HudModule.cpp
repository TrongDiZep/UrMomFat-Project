#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"
#include "../../../Utils/ColorUtil.h"
#include "../../../Utils/ImGuiUtils.h"

HudModule::HudModule() : IModule(0, Category::CLIENT, "Displays things like the ArrayList") {
	registerBoolSetting("Position", &showPos, showPos);
	registerBoolSetting("ArmorHud", &armorHud, armorHud);
	registerBoolSetting("Future Color", &futureColor, futureColor);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("HUD");
}

void HudModule::onPostRender(MinecraftUIRenderContext* renderCtx) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr) return;
	if (!Game.canUseMoveKeys()) return;

	Vec2 windowSize = Game.getGuiData()->windowSize;
	if (armorHud) {
		static float constexpr scale = 1.f;
		static float constexpr opacity = 0.25f;
		static float constexpr spacing = scale + 20.f;
		float x = windowSize.x / 2.f + 9.5f;
		float y = windowSize.y - 57.5f;
		if (localPlayer->isInWater() || localPlayer->isInWall()) y -= 10.f;
		for (int i = 0; i < 4; i++) {
			ItemStack* stack = localPlayer->getArmor(i);
			if (stack->isValid()) {
				DrawUtils::drawItem(stack, Vec2(x, y), 1.f);
				DrawUtils::drawBarItem(stack, Vec2(x, y), 1.f);
				x += scale * spacing;
			}
		}
	}
}

void HudModule::onImGuiRender(ImDrawList* drawlist) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr) return;
	if (!Game.canUseMoveKeys()) return;

	static Colors* colorsMod = moduleMgr->getModule<Colors>();
	UIColor mainColor = colorsMod->getColor();
	UIColor extraColor = UIColor(255, 255, 255);
	
	Vec2 windowSize = Game.getGuiData()->windowSizeReal;
	static const float textSize = 1.f;
	static const float textPadding = 1.f * textSize;
	static const float textHeight = ImGuiUtils::getTextHeight(textSize);
	static const float x = 2.f;
	float y = windowSize.y - textHeight - textPadding;
	if (futureColor) {
		mainColor = UIColor::GRAY;
		extraColor = UIColor::WHITE;
	}
	if (showPos) {
		const Vec3 pos = localPlayer->eyePos0;
		std::string mainText = "XYZ ";
		char extraText[50];
		sprintf_s(extraText, 50, "%.1f, %.1f, %.1f", pos.x, pos.y - 1.8f, pos.z);
		ImGuiUtils::drawText(Vec2(x, y), mainText.c_str(), mainColor, textSize);
		ImGuiUtils::drawText(Vec2(x + ImGuiUtils::getTextWidth(mainText.c_str(), textSize), y), extraText, extraColor, textSize);
	}
	static const std::string clientName = "Melody ";
	static const std::string version = "v0.2.3 Dev";
	ImGuiUtils::drawText(Vec2(x, 0.f), clientName.c_str(), mainColor, textSize);
	ImGuiUtils::drawText(Vec2(x + ImGuiUtils::getTextWidth(clientName.c_str(), textSize), 0.f), version.c_str(), extraColor, textSize);

}