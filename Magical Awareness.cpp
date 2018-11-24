#include <Windows.h>
#include "C:/Users/Daniel/Downloads/rift-sdk-master/src/sdkapi.h" 
#include "Magical Awareness.h"

PSDK_CONTEXT SDK_CONTEXT_GLOBAL;
SDK_HEALTH Health;


struct
{
	
	void* Object;

	//
	// The player's team.
	//
	int TeamID;

} _g_LocalPlayer; //This gives us access to the local player object and the local player's teamID

BOOL WINAPI DllMain //Rift DLL Setup
(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD fdwReason,
	_In_ LPVOID lpvReserved
)

{
	UNREFERENCED_PARAMETER(hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return TRUE;

	SDK_EXTRACT_CONTEXT(lpvReserved);
	if (!SDK_CONTEXT_GLOBAL) {
		return FALSE;
	}
	if (!SDKSTATUS_SUCCESS(SdkNotifyLoadedModule("Simple", SDK_VERSION)))
	{
		return FALSE;
	}
	//Setup is finished here, Code is added after this
	SdkRegisterOnLoad //The code here is run as soon as your module is loaded successfuly
	(
		[](void* UserData) -> void
	{
		UNREFERENCED_PARAMETER(UserData);
		SdkGetLocalPlayer(&_g_LocalPlayer.Object); //This stores a pointer to the local player object, so that we may use it in other functions.
		SdkRegisterGameScene(DrawGameScene, NULL); //Callback that will allow us to draw and call code at the start of every frame
		SdkGetUnitHealth(_g_LocalPlayer.Object, &Health); //Grabs the pointer to all health info, useful for getting info about health or shields
	}, NULL
	);

	return TRUE;
}

void __cdecl DrawGameScene //Called by SdkRegisterGameScene, the code in here will be called every frame, useful for drawing visuals
(
	_In_ void* UserData
)

{
	UNREFERENCED_PARAMETER(UserData);
	

	if (Health.Current==0) // This if statement will print "I am dead!" if the localplayers health is 0, otherwise it will print the localplayers health value
		SdkUiConsoleWrite("I am dead!");
	else
		SdkUiConsoleWrite("My current health is: %f", Health.Current);
}


