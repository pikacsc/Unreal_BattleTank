// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class UNREAL_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	ATank* m_AITank = nullptr;
	ATank* m_PlayerTank = nullptr;

	virtual void BeginPlay();

	// Called every frame
	virtual void Tick(float _fDeltaTime) override;

};
