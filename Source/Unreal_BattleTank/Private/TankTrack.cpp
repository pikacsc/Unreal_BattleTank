// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "TankTrack.h"

void UTankTrack::SetThrottle(float _fThrottle)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, _fThrottle);

	auto ForceApplied = GetForwardVector() * _fThrottle * m_fTrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}