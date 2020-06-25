// K-B 2020

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:
	// Constructor - Sets default values for the pawn's properties.
	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	void CheckFireCondition();
	FTimerHandle FireRateTimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
