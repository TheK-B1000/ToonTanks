// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "CollisionQueryParams.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
	// InitialLifeSpan = 3.0f;

 
	bshouldBounce = ProjectileMovement->bShouldBounce = true; // Bullet should always bounce once unless it hits an enemy tank or mine
	NumberOfHits = 0; // Track of hits to know when to destroy
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay() 
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());	
}



void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	// Try to get a reference to the owning class.
	AActor* MyOwner = GetOwner();
	// If for some reason we can't get a valid reference, return as we need to check against the owner. 
	if(!MyOwner)
	{
		return;
	}
	if (OtherActor)
	{
		NumberOfHits++;
		if (OtherActor->ActorHasTag("Destructible"))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
			if (OtherActor->ActorHasTag("Destructible"))
			{
				bshouldBounce = false;
				Destroy();
			}
		}
	}

	if (NumberOfHits == 2)
	{
		bshouldBounce = false;
		Destroy();
	}
}

void AProjectileBase::WhenToDestroy()
{
	// Control when the projectile destroys itself depending on how many times it bouncies, if it hits a mine, enemy tank, or player tank.
	if ( !bshouldBounce)
	{
		//Destroy();
	}
	else
	{
		// bounce off wall one time
	// bShouldBounce = false
	// destroy itself when it hits wall again
	}



}

// DONE 
// You need set up ball with UProjectileMovementComponent where bShouldBounce is true, 
// Bounciness is 1.0 and Friction is 0.0. Then you need set up walls with PhysicalMaterial where Friction is 0.0, Restituation is 1.0,
// Restituation Combine Mode is Max, Restituation Combine Mode is checked.


