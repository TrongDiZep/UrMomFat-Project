#pragma once

#include "Module.h"

class HudModule : public IModule {
private:
	bool showPos = true;
	bool armorHud = true;
	bool futureColor = false;

public:
	HudModule();
	~HudModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onImGuiRender(ImDrawList* drawlist) override;
};
