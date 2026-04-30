// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"


double TotalDistance = 0;
int32 EventCount = 0;
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{

	Super::BeginPlay();
	TotalDistance = 0;
	EventCount = 0;
	SetActorLocation(FVector(0, 0, 50));
	for (int32 i = 0; i < 10; ++i)
	{
		Move();
		Turn();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, FString::Printf(TEXT("Iteration: %d"), i + 1));
		}
		if (FMath::RandRange(0, 1) == 0)
		{

			EventCount++;
			TriggerEvent();
		}
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, FString::Printf(TEXT("Total Distance : %f, Total Event Count : %d"), TotalDistance, EventCount));
	}
}



void AMyActor::Move()
{
	FVector Target;


	Target.X = FMath::FRandRange(-500.0, 500.0);
	Target.Y = FMath::FRandRange(-500.0, 500.0);
	Target.Z = 0;

	AddActorWorldOffset(Target);

	FVector CurrentLocation = GetActorLocation();
	TotalDistance += FVector::Dist(CurrentLocation, Target);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, FString::Printf(TEXT("Current Location = %s\n Distance = %f"), *CurrentLocation.ToString(), FVector::Dist(CurrentLocation, Target)));
	}
	UE_LOG(LogTemp, Warning, TEXT("Location = %s"), *CurrentLocation.ToString());
}

void AMyActor::Turn()
{
	FRotator DeltaRotation;
	DeltaRotation.Yaw = FMath::FRandRange(-180.0, 180.0);
	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;

	AddActorWorldRotation(DeltaRotation);

	FRotator CurrentRotation = GetActorRotation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, CurrentRotation.ToString());
	}
	UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *CurrentRotation.ToString());
}
void AMyActor::TriggerEvent()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, FString::Printf(TEXT("Event Triggered!")));
	}
	UE_LOG(LogTemp, Warning, TEXT("Event Triggered!"));
}