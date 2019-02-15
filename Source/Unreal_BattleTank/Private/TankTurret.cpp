// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "TankTurret.h"


void UTankTurret::Rotate(float _RelativeSpeed)
{
	_RelativeSpeed = FMath::Clamp<float>(_RelativeSpeed, -1, +1);
	auto RotationChange = _RelativeSpeed * m_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}