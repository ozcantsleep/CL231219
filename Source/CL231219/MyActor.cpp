// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RocketBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RocketBox"));
	RootComponent = RocketBox;

	RocketBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketBody"));
	RocketBody->SetupAttachment(RocketBox);
	RocketBody->SetRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));

	RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("RocketMovement"));
	RocketMovement->InitialSpeed = 3000.f;
	RocketMovement->MaxSpeed = 3000.f;
	RocketMovement->ProjectileGravityScale = 0;

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_P38_Rocket.Succeeded())
	{
		RocketBody->SetStaticMesh(SM_P38_Rocket.Object);
	}

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

