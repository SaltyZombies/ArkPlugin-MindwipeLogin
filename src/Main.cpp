#include "API/ARK/Ark.h"


/**
 * @brief Callback function called when the server is ready.
 * 
 * This function is called when the server is ready and the plugin is loaded successfully.
 * It logs a message indicating that the plugin is up and running.
 */
void OnServerReady()
{
    Log::GetLog()->info("Plugin loaded successfully and is up!");
}

/**
 * @brief Hook function for AShooterPlayerController::OnPossess.
 * 
 * This function is called when a player controller possesses a pawn.
 * It performs a mindwipe on the player character if the player state and character are valid.
 * 
 * @param _this The player controller instance.
 * @param inPawn The pawn being possessed.
 */
DECLARE_HOOK(AShooterPlayerController_OnPossess, void, AShooterPlayerController*, APawn*);
void Hook_AShooterPlayerController_OnPossess(AShooterPlayerController* _this, APawn* inPawn)
{
    return AShooterPlayerController_OnPossess_original(_this, inPawn);
    AShooterPlayerState* playerState = static_cast<AShooterPlayerState*>(_this->PlayerStateField().Get());
    if (!playerState)
        return;

    AShooterCharacter* playerCharacter = static_cast<AShooterCharacter*>(_this->CharacterField().Get());
    if (!playerCharacter)
        return;

    UPrimalPlayerData* playerData = playerCharacter->GetPlayerData();
    if (!playerData)
        return;

    playerState->DoRespec(playerData, playerCharacter, false);
    Log::GetLog()->info("Mindwipe ran on Possession");
}

/**
 * @brief Initializes the plugin.
 * 
 * This function is called by AsaApi when the plugin is loaded. It performs pre-"server ready" initialization.
 * It initializes the log, sets a hook for the "AShooterPlayerController.OnPossess(APawn*)" function, and checks the server status.
 * If the server status is "Ready", it calls the OnServerReady() function.
 */
extern "C" __declspec(dllexport) void Plugin_Init()
{
    Log::Get().Init(PROJECT_NAME);

    AsaApi::GetHooks().SetHook("AShooterPlayerController.OnPossess(APawn*)", &Hook_AShooterPlayerController_OnPossess, &AShooterPlayerController_OnPossess_original);

    if (AsaApi::GetApiUtils().GetStatus() == AsaApi::ServerStatus::Ready)
        OnServerReady();
}

/**
 * @brief Unloads the plugin.
 * 
 * This function is called when the plugin is being unloaded. It disables the hook for the "AShooterPlayerController.OnPossess(APawn*)" function.
 */
extern "C" __declspec(dllexport) void Plugin_Unload()
{
    AsaApi::GetHooks().DisableHook("AShooterPlayerController.OnPossess(APawn*)", &Hook_AShooterPlayerController_OnPossess);
}
