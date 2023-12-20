// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
//002-001
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
//002-004
#include "MyActorComponent.h"
//002-006
#include "Kismet/GameplayStatics.h"
//002-007
#include "MyActor.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	P38Box = CreateDefaultSubobject<UBoxComponent>(TEXT("P38Box"));
	RootComponent = P38Box;
	
	P38Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("P38Body"));
	P38Body->SetupAttachment(P38Box);

	P38Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("P38Left"));
	P38Left->SetupAttachment(P38Body);

	P38Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("P38Right"));
	P38Right->SetupAttachment(P38Body);

	P38Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("P38Arrow"));
	P38Arrow->SetupAttachment(P38Box);

	P38SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("P38SpringArm"));
	P38SpringArm->SetupAttachment(P38Box);

	P38Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("P38Camera"));
	P38Camera->SetupAttachment(P38SpringArm);

	P38Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("P38Movement"));
	P38Movement->MaxSpeed = 100.0f;

	//002-003
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_P38_Body.Succeeded())
	{
		P38Body->SetStaticMesh(SM_P38_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_P38_Propeller.Succeeded())
	{
		P38Left->SetStaticMesh(SM_P38_Propeller.Object);
		P38Right->SetStaticMesh(SM_P38_Propeller.Object);
	}

	P38Left->AddLocalOffset(FVector(37.0f, -21.0f, 1.0f));
	P38Right->AddLocalOffset(FVector(37.0f, 21.0f, 1.0f));
	P38Arrow->AddLocalOffset(FVector(30.0f, 0.0f, -30.0f));
	P38SpringArm->TargetArmLength = 150.0f;
	P38SpringArm->bEnableCameraLag = true;
	P38SpringArm->bEnableCameraRotationLag = true;

	P38RotateComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("P38Rotator"));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	//002-004
	P38RotateComponent->Components.Add(P38Left);
	P38RotateComponent->Components.Add(P38Right);
}
// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//002-002
	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC && FireAction && PitchAndRollAction)
	{
		EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
		EIC->BindAction(PitchAndRollAction, ETriggerEvent::Triggered, this, &AMyPawn::PitchAndRoll);
	}
}

void AMyPawn::Fire(const FInputActionValue& Value)
{
	if (RocketTemplate)
	{
		GetWorld()->SpawnActor<AActor>(RocketTemplate, P38Arrow->GetComponentTransform());
	}
}

void AMyPawn::PitchAndRoll(const FInputActionValue& Value)
{
	FVector2D RotationValue = Value.Get<FVector2D>();
	RotationValue = RotationValue* UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;
	AddActorLocalRotation(FRotator(RotationValue.Y, 0, RotationValue.X));
}

//002-006
//void AMyPawn::Fire()
//{
//	GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), P38Arrow->K2_GetComponentLocation(), P38Arrow->K2_GetComponentRotation());
//}
//
//void AMyPawn::Pitch(float Value)
//{
//	if (Value != 0)
//	{
//		AddActorLocalRotation(FRotator(UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Value, 0, 0));
//	}
//}
//
//void AMyPawn::Roll(float Value)
//{
//
//	if (Value != 0)
//	{
//		AddActorLocalRotation(FRotator(0, 0, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Value));
//	}
//}
