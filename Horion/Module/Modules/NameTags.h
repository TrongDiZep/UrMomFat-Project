#pragma once

#include "Module.h"
#include <set>

class NameTags : public IModule {
public:
	bool displayArmor = true;
	float opacity = 0.2f;
	NameTags();
	~NameTags();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
};
