// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/Tank.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Unreal_BattleTank/Public/TankMovementComponent.h"

void ATank::SetBarrelReference(UTankBarrel * _BarrelToSet)
{
	m_TankAimingComponent->SetBarrelReference(_BarrelToSet);
	m_Barrel = _BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * _TurretToSet)
{
	m_TankAimingComponent->SetTurretReference(_TurretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - m_dLastFireTime) > m_fReloadTimeInSeconds; // Fire delay
	if (!m_Barrel) { 
		UE_LOG(LogTemp, Error, TEXT("Barrel object is missing"));
		return; 
	}
	if (isReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			m_ProjectileBlueprint,
			m_Barrel->GetSocketLocation(FName("Projectile")),
			m_Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(m_LaunchSpeed);
		m_dLastFireTime = FPlatformTime::Seconds(); // reset fire delay
	}
	
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector _HitLocation)
{
	m_TankAimingComponent->AimAt(_HitLocation, m_LaunchSpeed);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* _PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(_PlayerInputComponent);
	
}

