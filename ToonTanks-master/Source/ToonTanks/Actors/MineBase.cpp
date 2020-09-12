// K-B 2020

#include "MineBase.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "CollisionQueryParams.h"

// Sets default values
AMineBase::AMineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mine Mesh"));
	RootComponent = MineMesh;
	MineMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComp->SetupAttachment(MineMesh);
	SphereComp->SetSphereRadius(240.f);
	if (SphereComp)
	{
		SphereComp->SetCollisionProfileName("Trigger");
		SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMineBase::OnCollision);
	}

	bLastSeconds = false;

}

// Called when the game starts or when spawned
void AMineBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMineBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MineWasDeployed = GetWorld()->GetTimeSeconds();

	if (GetWorld()->GetTimeSeconds() - MineWasDeployed > MineDelay)
	{
		// Spawn emiter
		UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation());
		// Destroy mine
		Destroy();
		// play sound
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}
}

void AMineBase::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
		//HandleDestruction();
}

void AMineBase::InProximity()
{
	// The last few (5) seconds remaining mine ready to blow, inititate red flashing mine
	bLastSeconds = true;
	// if timer reaches 5 seconds blow up mine
}

void AMineBase::Countdown()
{
	// The mine if not touched blows up in 20 seconds. 
	// if mine has been active for 20 seconds bLastSeconds becomes true
	// Mine destroys itself and play blow up animation
}

void AMineBase::HandleDestruction()
{
	//if (TimeAlive > 20.0f)
	//{
		
	//}
}

