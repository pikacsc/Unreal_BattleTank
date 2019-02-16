// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class UNREAL_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector _HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* _BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* _TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	UTankAimingComponent* m_TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* _PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float		m_fReloadTimeInSeconds = 3.f;
	
	double		m_dLastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float m_LaunchSpeed = 4000.f; //TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> m_ProjectileBlueprint;

	//Local barrel reference for spawning projectile
	UTankBarrel* m_Barrel = nullptr;

};
