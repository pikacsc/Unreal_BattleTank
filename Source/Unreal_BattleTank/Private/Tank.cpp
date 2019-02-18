// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/Tank.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Unreal_BattleTank/Public/TankAimingComponent.h"

void ATank::Fire()
{
	if (!ensure(m_Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - m_dLastFireTime) > m_fReloadTimeInSeconds; // Fire delay
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

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin play to Run

	m_TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::AimAt(FVector _HitLocation)
{
	if (!ensure(m_TankAimingComponent)) { return; }
	m_TankAimingComponent->AimAt(_HitLocation, m_LaunchSpeed);
}

