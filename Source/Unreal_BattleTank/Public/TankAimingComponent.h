// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Hold barrel's properties and Elavate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* _BarrelToSet, UTankTurret * _TurretToSet);

	void AimAt(FVector _HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState m_FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;



	void MoveBarrel(FVector _AimDirection);

	bool IsBarrelMoving();


	UTankBarrel* m_Barrel = nullptr;
	UTankTurret* m_Turret = nullptr;


	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float m_LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> m_ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float		m_fReloadTimeInSeconds = 3.f;

	double		m_dLastFireTime = 0;

	FVector		m_fAimDirection;

	int			m_iRoundsLeft = 3;
};
