#include "CGameMode.h"
#include "Global.h"


ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/CharacterSystems/Player_Enemy/Player/BP_CPlayer_01.BP_CPlayer_01_C'");
}

