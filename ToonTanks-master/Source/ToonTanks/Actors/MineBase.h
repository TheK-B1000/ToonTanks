// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MineBase.generated.h"

class USphereComponent;

UCLASS()
class TOONTANKS_API AMineBase : public AActor
{
	GENERATED_BODY()
	
private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MineMesh;

	// PROJECTILES
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* Explosion;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ExplosionSound;

	// FUNCTIONS
	/** called when something enters the sphere component */
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	// VARIABLES
	bool bLastSeconds;

public:	
	// Sets default values for this actor's properties
	AMineBase();
	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InProximity();

	void Countdown();



};
