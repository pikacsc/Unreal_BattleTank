// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //

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


	UPROPERTY(EditAnywhere)
		float m_fCrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float m_fCrosshairYLocation = 0.33333f;

};


