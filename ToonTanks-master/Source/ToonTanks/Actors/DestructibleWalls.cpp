// K-B 2020


#include "DestructibleWalls.h"
#include "Components/BoxComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestructibleWalls::ADestructibleWalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	bWallDestroyed = false;


}

// Called when the game starts or when spawned
void ADestructibleWalls::BeginPlay()
{
	Super::BeginPlay();
	if (bWallDestroyed)
	{
		Destroy();
	}
	
}

// Called every frame
void ADestructibleWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADestructibleWalls::ApplyRadialDamage(const UObject* WorldContextObject, float BaseDamage, const FVector& Origin, float DamageRadius, TSubclassOf<class UDamageType> DamageTypeClass, const TArray<AActor*>& IgnoreActors, AActor* DamageCauser, AController* InstigatedByController, bool bDoFullDamage, ECollisionChannel DamagePreventionChannel)
{
	return bWallDestroyed;
}

void ADestructibleWalls::HandleDestruction()
{
	// --- Universal functionality ---
	// Play death effects particle, sound and camera shake. 
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyedParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestroyedSound, GetActorLocation());
}


