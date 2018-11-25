#include <Windows.h>
#include "C:/Users/Daniel/Downloads/rift-sdk-master/src/sdkapi.h" 
#include "Magical Awareness.h"

SDK_HEALTH Health;

struct {
	void* Object;
	int TeamID;
} localPlayer;

PLUGIN_SETUP("Magical Awareness", OnLoad);

void __cdecl DrawGameScene(_In_ void* UserData) {
	UNREFERENCED_PARAMETER(UserData);
	SdkEnumHeroes(PrintHealth, NULL);
}

bool __cdecl PrintHealth(void* Object, unsigned int NetworkID, void* UserData) {

	SdkGetUnitHealth(Object, &Health); //Grabs the pointer to all health info, useful for getting info about health or shields
	if (Health.Current == 0) // This if statement will print "I am dead!" if the localplayers health is 0, otherwise it will print the localplayers health value
		SdkUiConsoleWrite("A hero is dead!");
	else
		SdkUiConsoleWrite("A heroes health is: %f", Health.Current);
	return true;
}

void __cdecl OnLoad(void* UserData) {
	UNREFERENCED_PARAMETER(UserData);
	SdkGetLocalPlayer(&localPlayer.Object); //This stores a pointer to the local player object, so that we may use it in other functions.
	SdkRegisterGameScene(DrawGameScene, NULL); //Callback that will allow us to draw and call code at the start of every frame
	return;
}