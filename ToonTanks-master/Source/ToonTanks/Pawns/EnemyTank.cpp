// K-B 2021

#include "EnemyTank.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AEnemyTank::AEnemyTank()
{
    this->ActorHasTag("Destructible");
}

// Called when the game starts or when spawned
void AEnemyTank::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTank::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyTank::HandleDestruction()
{
    // Call base pawn class HandleDestruction to play effects.
    Super::HandleDestruction();
    // Hide Player. TODO - Create new function to handle this. 
    bIsPlayerAlive = false;
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    Destroy();
}

bool AEnemyTank::GetIsPlayerAlive()
{
    return bIsPlayerAlive;
}

// Called every frame
void AEnemyTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    Move();
    RotateTurret(PlayerPawn->GetActorLocation());
    Rotate();

}

void AEnemyTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void AEnemyTank::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

void AEnemyTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}

void AEnemyTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}

void AEnemyTank::CheckFireCondition()
{
    // If Player == null || is Dead THEN BAIL!!
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }
    // If Player IS in range THEN FIRE!!
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float AEnemyTank::ReturnDistanceToPlayer()
{
    // Test if the PlayerPawn is NULL
    if (!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
