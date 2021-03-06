// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DelegateCombinations.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class UNREAL_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float _fDamageAmount, struct FDamageEvent const & _DamageEvent, class AController * _EventInstigator, AActor * _DamageCauser) override;

	virtual void BeginPlay() override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate m_OnDeath;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 m_iStartingHealth = 100;


	UPROPERTY(EditAnywhere)
		int32   m_iEnemyDestroyed = 0;

	UPROPERTY(EditAnywhere)
		float m_fClearTime = 0.f;


private:
	// Sets default values for this pawn's properties
	ATank();



	//UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 m_iCurrentHealth;


};
