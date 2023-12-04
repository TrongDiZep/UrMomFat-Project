#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"

#include "Modules/InventoryCleaner.h"
#include "Modules/Notifications.h"
//#include "Modules/InfiniteAura.h"
#include "Modules/InventoryMove.h"
#include "Modules/AntiImmobile.h"
#include "Modules/EditionFaker.h"
#include "Modules/ChestStealer.h"
#include "Modules/ClientTheme.h"
//#include "Modules/CubeGlide.h"
#include "Modules/CrystalAura.h"
#include "Modules/Criticals.h"
#include "Modules/ClickGuiMod.h"
//#include "Modules/AirStuck.h"
#include "Modules/NoSlowDown.h"
#include "Modules/InstaBreak.h"
#include "Modules/BlockReach.h"
#include "Modules/FullBright.h"
#include "Modules/StorageESP.h"
#include "Modules/AutoSprint.h"
#include "Modules/AutoGapple.h"
#include "Modules/ViewModel.h"
#include "Modules/Arraylist.h"
#include "Modules/NoHurtcam.h"
#include "Modules/NoFriends.h"
//#include "Modules/Jetpack.h"
#include "Modules/HudModule.h"
//#include "Modules/FastEat.h"
#include "Modules/ChestAura.h"
#include "Modules/BowAimbot.h"
#include "Modules/AutoSneak.h"
#include "Modules/AutoArmor.h"
#include "Modules/FastStop.h"
#include "Modules/Freelook.h"
#include "Modules/Scaffold.h"
#include "Modules/NoPacket.h"
#include "Modules/Velocity.h"
#include "Modules/NameTags.h"
#include "Modules/MidClick.h"
#include "Modules/Killaura.h"
#include "Modules/HighJump.h"
#include "Modules/Teleport.h"
#include "Modules/Compass.h"
#include "Modules/Godmode.h"
#include "Modules/NoSwing.h"
#include "Modules/Spammer.h"
#include "Modules/Freecam.h"
#include "Modules/AntiBot.h"
#include "Modules/AirJump.h"
#include "Modules/Spider.h"
#include "Modules/Tracer.h"
#include "Modules/NoFall.h"
#include "Modules/Module.h"
#include "Modules/Hitbox.h"
#include "Modules/Tower.h"
#include "Modules/Timer.h"
#include "Modules/Reach.h"
#include "Modules/Phase.h"
#include "Modules/NoWeb.h"
#include "Modules/Jesus.h"
#include "Modules/Glide.h"
#include "Modules/Blink.h"
#include "Modules/Zoom.h"
#include "Modules/Xray.h"
#include "Modules/Step.h"
#include "Modules/Nbt.h"
#include "Modules/Fly.h"
#include "Modules/ESP.h"
#include "Modules/CustomFont.h"
#include "Modules/Colors.h"
#include "Modules/InventoryView.h"
#include "Modules/PacketMine.h"
#include "Modules/PacketLogger.h"
#include "Modules/AutoCrystal.h"
#include "Modules/Offhand.h"
#include "Modules/NoRender.h"

#ifdef _DEBUG
#include "Modules/PacketLogger.h"
#endif


class ModuleManager {
private:
	GameData* gameData;
	std::vector<std::shared_ptr<IModule>> moduleList;
	bool initialized = false;

public:
	~ModuleManager();
	ModuleManager(GameData* gameData);
	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(GameMode* gameMode);
	void onAttack(Entity* attackedEnt);
	void onWorldTick(GameMode* gameMode);
	void onKeyUpdate(int key, bool isDown);
	void onKey(int key, bool isDown, bool& shouldCancel);
	void onPreRender(MinecraftUIRenderContext* renderCtx);
	void onPostRender(MinecraftUIRenderContext* renderCtx);
	void onLevelRender();
	void onMove(MoveInputHandler* handler);
	void onPlayerTick(Player* player);
	void onSendPacket(Packet*);
	void onSendClientPacket(Packet*);
	void onBaseTick(Entity*);
	void onImGuiRender(ImDrawList* d);
	void onJoiningServer();

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	/*
	 *	Use as follows: 
	 *		IModule* mod = moduleMgr.getModule<NoKnockBack>(); 
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !	
	 */
	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())){
				
				return pRet;
			}
		}
		return nullptr;
	};

	// Dont Use this functions unless you absolutely need to. The function above this one works in 99% of cases
	std::optional<std::shared_ptr<IModule>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
		
		for (std::vector<std::shared_ptr<IModule>>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
			std::shared_ptr<IModule> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<IModule>>(mod);
		}
		return std::optional<std::shared_ptr<IModule>>();
	}
};

extern ModuleManager* moduleMgr;