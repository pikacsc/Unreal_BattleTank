// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Unreal_BattleTank/Public/TankTurret.h"
#include "Projectile.h"
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


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	m_dLastFireTime = FPlatformTime::Seconds(); // reset fire delay
}

void UTankAimingComponent::Initialize(UTankBarrel * _BarrelToSet, UTankTurret * _TurretToSet)
{
	m_Barrel = _BarrelToSet;
	m_Turret = _TurretToSet;
}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	m_CurrentReloadingTime = FPlatformTime::Seconds() - m_dLastFireTime;
	if (m_iRoundsLeft <= 0)
	{
		m_FiringState = EFiringState::OutOfAmmo;
	}
	else if (/**/m_CurrentReloadingTime < m_fReloadTimeInSeconds)
	{
		m_FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		m_FiringState = EFiringState::Aiming;
	}
	else
	{
		m_FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return m_FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return m_iRoundsLeft;
}

float UTankAimingComponent::GetReloadingTime() const
{
	switch (m_FiringState)
	{
	case EFiringState::Reloading:
		return m_CurrentReloadingTime / m_fReloadTimeInSeconds;
		break;
	case EFiringState::Aiming:
	case EFiringState::Locked:
		return m_fReloadTimeInSeconds / m_fReloadTimeInSeconds;
		break;
	default: 
		return 0.f;
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(m_Barrel)) { return false; }
	auto BarrelForward = m_Barrel->GetForwardVector();
	return !BarrelForward.Equals(m_fAimDirection, 0.01);
}


void UTankAimingComponent::AimAt(FVector _HitLocation)
{
	if (!ensure(m_Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		_HitLocation,
		m_LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		m_fAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(m_fAimDirection);
	}
	

	// if no solution found do nothing
}


void UTankAimingComponent::MoveBarrel(FVector _AimDirection)
{
	if (!ensure(m_Barrel) || !ensure(m_Turret)) { return; }
	
	//Work-out difference between current barrel reaction, and AimDirection
	auto BarrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	m_Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
		m_Turret->Rotate(DeltaRotator.Yaw);
	else
		m_Turret->Rotate(-DeltaRotator.Yaw);

}



void UTankAimingComponent::Fire()
{
	if (m_FiringState == EFiringState::Locked || m_FiringState == EFiringState::Aiming)
	{
		if (!ensure(m_Barrel) ) { return; }
		if (!ensure(m_ProjectileBlueprint)) { return; }
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			m_ProjectileBlueprint,
			m_Barrel->GetSocketLocation(FName("Projectile")),
			m_Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(m_LaunchSpeed);
		m_dLastFireTime = FPlatformTime::Seconds(); // reset fire delay
		m_iRoundsLeft--;
	}
}

