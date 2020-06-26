// K-B 2020


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// Get references and game win/lose conditions

	// Call HandleGameStart to initialise the start countdown, turret activation, pawn check etc.
}


void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If Turret, tally. If Player -> go to lose condition.
	UE_LOG(LogTemp, Warning, TEXT("An Actor died!"));
}

void ATankGameModeBase::HandleGameStart()
{
	// Initialise the start countdown, turret activation, pawn check etc.
	// Call Blueprint version GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win results.
	// else if turret destroyed player, show lose result.
	// Call Blueprint version GameOver();
}
