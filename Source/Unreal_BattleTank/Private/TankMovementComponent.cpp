// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* _LeftTrackToSet, UTankTrack* _RightTrackToSet)
{
	m_LeftTrack = _LeftTrackToSet;
	m_RightTrack = _RightTrackToSet;
}



void UTankMovementComponent::IntendMoveForward(float _fThrow)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	if (!m_LeftTrack || !m_RightTrack) { return; }

	m_LeftTrack->SetThrottle(_fThrow);
	m_RightTrack->SetThrottle(_fThrow);
}


void UTankMovementComponent::IntendTurnLeft(float _fThrow)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	if (!m_LeftTrack || !m_RightTrack) { return; }

	m_LeftTrack->SetThrottle(-_fThrow);
	m_RightTrack->SetThrottle(_fThrow);
}


void UTankMovementComponent::IntendTurnRight(float _fThrow)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	if (!m_LeftTrack || !m_RightTrack) { return; }

	m_LeftTrack->SetThrottle(_fThrow);
	m_RightTrack->SetThrottle(-_fThrow);
}