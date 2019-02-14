// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float _RelativeSpeed)
{

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	_RelativeSpeed = FMath::Clamp<float>(_RelativeSpeed, -1, +1);
	auto ElevationChange = _RelativeSpeed * m_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, m_MinElevationDegrees, m_MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}