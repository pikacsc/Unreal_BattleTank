// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}