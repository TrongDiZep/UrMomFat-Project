#pragma once

#include "..\ModuleManager.h"
#include "Module.h"

class Arraylist : public IModule {
private:
	bool bottom = true;
	bool outline = true;
	int alpha = 90;
	float blurStrength = 5.f;
public:
	bool showMode = true;
	Arraylist();
	~Arraylist();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onImGuiRender(ImDrawList* d) override;
};
