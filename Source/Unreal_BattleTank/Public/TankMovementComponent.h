// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float _fThrow);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float _fThrow);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnLeft(float _fThrow);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack * _LeftTrackToSet, UTankTrack * _RightTrackToSet);

private:
	UTankTrack* m_LeftTrack = nullptr;
	UTankTrack* m_RightTrack = nullptr;

	

};
