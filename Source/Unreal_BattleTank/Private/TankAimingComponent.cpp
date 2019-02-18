// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Unreal_BattleTank/Public/TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false; // TODO Should this really tick?
	// ...
}



void UTankAimingComponent::Initialize(UTankBarrel * _BarrelToSet, UTankTurret * _TurretToSet)
{
	m_Barrel = _BarrelToSet;
	m_Turret = _TurretToSet;
}

void UTankAimingComponent::AimAt(FVector _HitLocation, float _LaunchSpeed)
{
	if (!ensure(m_Barrel)) { 
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
	}
	

	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrel(FVector _AimDirection)
{
	if (ensure(m_Barrel) || ensure(m_Turret)) { return; }
	//Work-out difference between current barrel reaction, and AimDirection
	auto BarrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	m_Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
	m_Turret->Rotate(DeltaRotator.Yaw);
}



