// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
//���Ӹ�� ���� ������
#include "MyPawn.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	//001-001
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("It's Debug"));
	}
	UE_LOG(LogTemp, Warning, TEXT("It's LogTemp"));

	//���Ӹ�� ���� ������
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
