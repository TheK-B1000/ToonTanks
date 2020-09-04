// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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
	// If the other actor ISN'T self OR Owner AND exists, then apply damage.
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// if the projectile comes in contact with a wall or destructible wall.
		/*if (OnHit(StaticMesh * Wall, StaticMesh * DestructibleWall) == true )
		{
			// OnProjectileBounce();
			// if the projectile hits the wall a second time it destroys itself
		// Destroy();
		}
		// else apply damage
		else
		{*/
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
			Destroy();
		//}
	}	


}


// Ball should bounce from walls and never lose any velocity. You need set up ball with UProjectileMovementComponent where bShouldBounce is true, 
// Bounciness is 1.0 and Friction is 0.0. Then you need set up walls with PhysicalMaterial where Friction is 0.0, Restituation is 1.0,
// Restituation Combine Mode is Max, Restituation Combine Mode is checked.


