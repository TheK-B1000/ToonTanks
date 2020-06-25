// K-B 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

	// Root 
	UCapsuleComponent* CapsuleComp;

	// Base Mesh
	UStaticMeshComponent* BashMesh;

	// Turret Mesh
	UStaticMeshComponent* TurretMesh;

	// Projectile SpawnPoint
	USceneComponent* ProjectileSpawnPoint;

public:
	// Sets default values for this pawn's properties
	APawnBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
