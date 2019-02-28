// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float  m_AcceptanceRadius = 8000.f;


private:
	virtual void BeginPlay() override;


	virtual void SetPawn(APawn* _InPawn) override;

	// Called every frame
	virtual void Tick(float _fDeltaTime) override;

	UFUNCTION()
	void OnPossedTankDeath();

};
