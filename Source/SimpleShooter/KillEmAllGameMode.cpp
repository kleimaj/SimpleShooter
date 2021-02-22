// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		EndGame(false);
	}

	// Iterate over ShooterAI in World
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		// Is not dead?
		if (!Controller->IsDead()) {
			// early return
			return;
		}
	}
	// Call End Game
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// iterate through all controllers in game
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// sends True for the Controllers who've won
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
