// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really tick?
	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	m_Barrel = BarrelToSet;
}



void UTankAimingComponent::AimAt(FVector _HitLocation, float _LaunchSpeed)
{
	if (!m_Barrel) { 
		UE_LOG(LogTemp, Error, TEXT("No barrel object"));
		return; 
	}
	FVector OutLaunchVelocity(0);
	FVector StartLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		_HitLocation,
		_LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	else
	{

		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : No Aim solution found"), Time);
	}

	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrel(FVector _AimDirection)
{
	//Work-out difference between current barrel reaction, and AimDirection
	auto BarrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	m_Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number

	//Move the barrel the right amount this frame


	//Given a max elevation speed, and the frame time
}



