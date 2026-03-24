// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeGameMode.h"

#include "ActionRougelike/Player/RougePlayerController.h"

ARougeGameMode::ARougeGameMode()
{
	PlayerControllerClass = ARougePlayerController::StaticClass();
}
