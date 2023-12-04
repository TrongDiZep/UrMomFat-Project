#pragma once
#include "Module.h"
#include "../../Utils/ColorUtil.h"

class Colors : public IModule {
private:
	UIColor mainColor = UIColor(135, 50, 255);
	bool rainbow = false;
	float speed = 3.f;
	float saturation = 1.f;
	float brightness = 1.f;
	int seperation = 25;

public:
	Colors();
	const UIColor getColor() { return this->mainColor; }
	virtual const char* getModuleName() override;
	virtual bool isEnabled() override;
	virtual bool isVisible() override;
	virtual void onImGuiRender(ImDrawList* d);
};