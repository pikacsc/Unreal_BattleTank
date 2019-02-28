// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Projectile.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Unreal_BattleTank/Public/TankProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(m_CollisionMesh);
	m_CollisionMesh->SetNotifyRigidBodyCollision(true);
	m_CollisionMesh->SetVisibility(false);

	m_LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	m_LaunchBlast->SetupAttachment(m_CollisionMesh);

	m_TankProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement"));
	m_TankProjectileMovementComponent->bAutoActivate = false;

	m_ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	m_ImpactBlast->SetupAttachment(m_CollisionMesh);
	m_ImpactBlast->bAutoActivate = false;

	m_ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	m_ExplosionForce->SetupAttachment(m_CollisionMesh);

	m_FireSound = CreateDefaultSubobject<UAudioComponent>(FName("FireSound"));
	m_FireSound->SetupAttachment(m_CollisionMesh);

	m_ExplosionSound = CreateDefaultSubobject<UAudioComponent>(FName("ExplosionSound"));
	m_ExplosionSound->SetupAttachment(m_CollisionMesh);
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	m_CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float _fSpeed)
{
	m_FireSound->Play(0.f);
	m_TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector* _fSpeed);
	m_TankProjectileMovementComponent->Activate();
}


void AProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	m_LaunchBlast->Deactivate();
	m_ImpactBlast->Activate();
	m_ExplosionForce->FireImpulse();

	m_ExplosionSound->Play(0.f);

	SetRootComponent(m_ImpactBlast);
	m_CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		m_fDestroyDelay,
		GetActorLocation(),
		m_ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, m_fDestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}