// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	//SetFocus(PlayerPawn);

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// If line of sight, move to actor and set focus
	// Else, stop moving, clear focus
	if (LineOfSightTo(PlayerPawn)) {
		// Set PlayerLocation
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		// setting LastKnown
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else {
		// clear PlayerLocation
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}
