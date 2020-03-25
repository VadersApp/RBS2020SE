#include "common/IDebugLog.h"  // IDebugLog
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION
#include "skse64/PluginAPI.h"  // SKSEInterface, PluginInfo

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS

#include "version.h"  // VERSION_VERSTRING, VERSION_MAJOR
#include "skse64/GameTypes.h"  // BSFixedString
#include "skse64/PapyrusNativeFunctions.h"
#include <stdlib.h> 
#include "common/ITypes.h"  // SInt32
#include "skse64/GameTypes.h"  // BSFixedString
#include "skse64/PapyrusVM.h"
#include "plugin.h"
#include "morph.h"
#include "skee/IPluginInterface.h"
#include "skee/FaceMorphInterface.h"
//#include "versiondb.h"
static SKSEPapyrusInterface* g_papyrus = NULL;
static PluginHandle	g_pluginHandle = kPluginHandle_Invalid;
static SKSEMessagingInterface* g_messaging = 0;
static IBodyMorphInterface* g_bodyMorphInterface;
static FaceMorphInterface* g_faceMorphInterface;
const char* PLUGIN_NAME = "RBS2020";
extern "C" {

	void SKSEMessageHandler(SKSEMessagingInterface::Message* message)
	{
		switch (message->type)
		{
		case SKSEMessagingInterface::kMessage_PostLoad:
		{
			InterfaceExchangeMessage message;
			g_messaging->Dispatch(g_pluginHandle, InterfaceExchangeMessage::kMessage_ExchangeInterface, (void*)&message, sizeof(InterfaceExchangeMessage*), "skee");
			if (message.interfaceMap) {
				g_bodyMorphInterface = (IBodyMorphInterface*)message.interfaceMap->QueryInterface("BodyMorph");
				
				if (!g_bodyMorphInterface) {
					_FATALERROR("couldn't get serialization MorphInterface");
				}
				else  {
					_MESSAGE("BodyMorph Version %i", g_bodyMorphInterface->GetVersion()); 
					if (!RBS2020::Morph::SetMorphInterface(g_bodyMorphInterface)) {
						_MESSAGE("BodyMorphInterace not provided");
					}
				}
				
		
			
			}
		}
		break;
		}
	}

	void PluginsLoaded(SKSEMessagingInterface::Message* a_msg)
	{
		_MESSAGE("RBS2020 MessageHandler loaded");
		g_messaging->RegisterListener(g_pluginHandle, "SKSE", SKSEMessageHandler);
	}

	//__declspec(dllexport)
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
	
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\RBS2020.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);
	
		_MESSAGE("RBS2020 v%s", "0.24");

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "RBS2020";
		a_info->version = MYFP_VERSION_MAJOR;

		g_pluginHandle = a_skse->GetPluginHandle();

		if (a_skse->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}
		else if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_97) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->runtimeVersion);
			return false;
		}

		return true;
	}

	//__declspec(dllexport)
	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
	
		g_messaging = (SKSEMessagingInterface*)a_skse->QueryInterface(kInterface_Messaging);
		if (g_messaging->RegisterListener(g_pluginHandle, "SKSE", SKSEMessageHandler)) {
			_MESSAGE("[MESSAGE] Messaging interface registration successful");
		}
		else {
			_FATALERROR("[FATAL ERROR] Messaging interface registration failed!\n");
			return false;
		}

		g_papyrus = (SKSEPapyrusInterface*)a_skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		
		bool btest = g_papyrus->Register(RBS2020::RegisterFuncs);
	
		if (btest) {
			_MESSAGE("Register Succeeded");
		}
		
		return true;
	}
	
};

