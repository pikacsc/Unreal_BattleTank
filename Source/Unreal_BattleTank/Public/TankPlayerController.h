// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h" //

class ATank;

/**
 * 
 */
UCLASS()
class UNREAL_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:
	ATank* GetControlledTank() const;

	void BeginPlay() override;

	virtual void Tick( float _fDeltaTime ) override;

	// start the tank moving the barrel so that a shot would it where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector & _OutHitLocation) const;

	bool GetLookDirection(FVector2D _ScreenLocation, FVector& _LookDirection) const;

	bool GetLookVectorHitLocation(FVector _LookDirection, FVector& _HitLocation) const;


	UPROPERTY(EditDefaultsOnly)
		float m_fCrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float m_fCrosshairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
		float m_fLineTraceRange = 1000000.f;

};


