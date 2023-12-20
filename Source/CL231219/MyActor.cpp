// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//매 프레임마다 쓸필요가 없는 것이니 false로 바꾼다.
	PrimaryActorTick.bCanEverTick = false;

	RocketBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RocketBox"));
	RootComponent = RocketBox;

	RocketBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketBody"));
	RocketBody->SetupAttachment(RocketBox);
	RocketBody->SetRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));

	RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("RocketMovement"));
	RocketMovement->InitialSpeed = 3000.0f;
	RocketMovement->MaxSpeed = 3000.0f;
	RocketMovement->ProjectileGravityScale = 0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
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

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessActorBeginOverlap);
	OnActorBeginOverlap.RemoveAll(this);
	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessActorBeginOverlap);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMyActor::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OtherActor %s"), *OtherActor->GetName());
	CPPToCallBP(10);
}


void AMyActor::ExistCPPToCallBP_Implementation(int64 Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("NO BP %d"), Damage);
}

