// K-B 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

public:
	void ActorDied(AActor* DeadActor);
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

private:
	int32 TargetTurrets = 0;
	int32 GetTargetTurretCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLoop", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	APawnTank* PlayerTank;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
};
