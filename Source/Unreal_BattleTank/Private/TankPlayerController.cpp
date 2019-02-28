// Copyrights JasonChoi(SEONG_CHAN) 2019


#include "Unreal_BattleTank/Public/TankPlayerController.h"
#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * _InPawn)
{
	Super::SetPawn(_InPawn);
	if (_InPawn)
	{
		auto PossessedTank = Cast<ATank>(_InPawn);
		if (!ensure(PossessedTank)) { return; }

		//TODO Subscribe our local method to the tank's death event
		PossessedTank->m_OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}

void ATankPlayerController::OnPossedTankDeath() //GameOver
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation; //Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
	}

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & _OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * m_fCrosshairXLocation, ViewportSizeY * m_fCrosshairYLocation );

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection,_OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D _ScreenLocation, FVector & _LookDirection) const
{
	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		_ScreenLocation.X,
		_ScreenLocation.Y, 
		CameraWorldLocation, 
		_LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector _LookDirection, FVector & _HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (_LookDirection * m_fLineTraceRange);
	
	if(GetWorld()->LineTraceSingleByChannel(
			HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	)
	{
		_HitLocation = HitResult.Location;
		return true;
	}
	_HitLocation = FVector(0);
	
	return false; // Line trace didn't succeed
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
}
