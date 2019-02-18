// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class UNREAL_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector _HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent*	m_TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float		m_fReloadTimeInSeconds = 3.f;
	
	UTankBarrel* m_Barrel = nullptr;

	double		m_dLastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_LaunchSpeed = 4000.f; //TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> m_ProjectileBlueprint;

};
