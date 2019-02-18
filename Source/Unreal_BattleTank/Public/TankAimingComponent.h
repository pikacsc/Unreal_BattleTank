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
	Locked
};


// Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Hold barrel's properties and Elavate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* _BarrelToSet, UTankTurret * _TurretToSet);

	// TODO add SetTurretReference

	void AimAt(FVector _HitLocation, float _LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState m_FiringState = EFiringState::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* m_Barrel = nullptr;
	
	UTankTurret* m_Turret = nullptr;

	void MoveBarrel(FVector _AimDirection);

};
