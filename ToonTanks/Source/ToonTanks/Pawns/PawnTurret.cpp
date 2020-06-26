// K-B 2020


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// if the player is valid || dead then BAIL!
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive())
	{
		return;
	}
	// if player IS in range then FIRE!
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		// Fire
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	// Check if we have a valid reference to the player.
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	return Distance;
}
