// K-B 2020


#include "DestructibleWalls.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestructibleWalls::ADestructibleWalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADestructibleWalls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

