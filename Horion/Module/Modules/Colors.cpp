#include "Colors.h"

Colors::Colors() : IModule(0, Category::CLIENT, "Colors") {
	registerIntSetting("Red", &mainColor.r, mainColor.r, 0, 255);
	registerIntSetting("Green", &mainColor.g, mainColor.g, 0, 255);
	registerIntSetting("Blue", &mainColor.b, mainColor.b, 0, 255);
	registerBoolSetting("Rainbow", &rainbow, rainbow);
	registerFloatSetting("Speed", &speed, speed, 0.5f, 5.f);
	registerFloatSetting("Brightness", &brightness, brightness, 0.f, 1.f);
	registerIntSetting("Seperation", &seperation, seperation, 0, 100);
}

const char* Colors::getModuleName() {
	return "Colors";
}

bool Colors::isEnabled() {
	return true;
}

bool Colors::isVisible() {
	return false;
}

void Colors::onImGuiRender(ImDrawList* d) {
	if (rainbow) {
		this->mainColor = ColorUtil::getRainbowColor(speed, saturation, brightness, 0);
	}
}