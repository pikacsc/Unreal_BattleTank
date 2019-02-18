// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/Tank.h"
#include "Unreal_BattleTank/Public/TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "Unreal_BattleTank/Public/TankMovementComponent.h"

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - m_dLastFireTime) > m_fReloadTimeInSeconds; // Fire delay
	if (m_Barrel && isReloaded)
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

}

void ATank::AimAt(FVector _HitLocation)
{
	if (!m_TankAimingComponent) { return; }
	m_TankAimingComponent->AimAt(_HitLocation, m_LaunchSpeed);
}

