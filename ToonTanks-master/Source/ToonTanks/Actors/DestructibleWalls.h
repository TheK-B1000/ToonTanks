// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleWalls.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API ADestructibleWalls : public AActor
{
	GENERATED_BODY()
	
private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;


	// VARIABLES
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> DeathShake;

public:	
	// Sets default values for this actor's properties
	ADestructibleWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
