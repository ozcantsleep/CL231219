// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//003-001
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


//003-002
class USceneComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CL231219_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//003-002
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	TArray<TObjectPtr<USceneComponent>> Components;
};
