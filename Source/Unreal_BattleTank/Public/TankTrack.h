// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UNREAL_BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float _fThrottle);


	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
		float m_fTrackMaxDrivingForce = 40000000.f; // Assume 40 tonne tank, and 1g accelleration
	
private:
	float m_fCurrentThrottle = 0.f;

	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
