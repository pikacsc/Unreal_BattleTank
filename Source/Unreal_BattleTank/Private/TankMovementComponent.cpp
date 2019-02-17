// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* _LeftTrackToSet, UTankTrack* _RightTrackToSet)
{
	if (!_LeftTrackToSet || !_RightTrackToSet) { return; }
	m_LeftTrack = _LeftTrackToSet;
	m_RightTrack = _RightTrackToSet;
}



void UTankMovementComponent::IntendMoveForward(float _fThrow)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	if (!m_LeftTrack || !m_RightTrack) { return; }

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), _fThrow);

	m_LeftTrack->SetThrottle(_fThrow);
	m_RightTrack->SetThrottle(_fThrow);
}
