// K-B 2020


#include "PawnTank.h"
#inlcude "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponnent.h"

// Sets default values
APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEST("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEST("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
