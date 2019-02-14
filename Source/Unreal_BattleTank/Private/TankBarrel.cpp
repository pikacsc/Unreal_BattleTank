// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float _RelativeSpeed)
{

	//Move the barrel the right amount this frame


	//Given a max elevation speed, and the frame time

	auto Time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%f : Barrel-Elevate() called at speed %f"), Time, _RelativeSpeed);

}