// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankBarrel.h"


void UTankBarrel::Elevate(float _DegreesPerSecond)
{

	//Move the barrel the right amount this frame


	//Given a max elevation speed, and the frame time

	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at speed %f"), _DegreesPerSecond);

}