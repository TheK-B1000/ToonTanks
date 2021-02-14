// K-B 2021

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "EnemyTank.generated.h"

class APawnTank;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API AEnemyTank : public APawnBase
{
	GENERATED_BODY()
	
private:
	// Working Variables to control the tank's movement
	FVector MoveDirection;
	FQuat RotationDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRange = 2000.0f;

	// Create our own FTimerHandle
	FTimerHandle FireRateTimerHandle;
	// The pointer of APawnTank called PlayerPawn
	APawnTank* PlayerPawn;
	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive = true;

	// --------------Movement---------------
	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);
	void Move();
	void Rotate();
	// --------------------------------------

	// ---------------Fire-------------------
	void CheckFireCondition();
	float ReturnDistanceToPlayer();
	// --------------------------------------
public:

	AEnemyTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
