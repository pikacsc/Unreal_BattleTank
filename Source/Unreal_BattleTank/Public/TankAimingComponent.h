// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Hold barrel's properties and Elavate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* _BarrelToSet);

	void SetTurretReference(UTankTurret* _TurretToSet);


	// TODO add SetTurretReference

	void AimAt(FVector _HitLocation, float _LaunchSpeed);

private:
	UTankBarrel* m_Barrel = nullptr;
	
	UTankTurret* m_Turret = nullptr;

	void MoveBarrel(FVector _AimDirection);

};
