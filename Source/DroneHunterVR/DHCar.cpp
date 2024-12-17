// Fill out your copyright notice in the Description page of Project Settings.


#include "DHCar.h"

#include <string>

#include "DHDroneActor.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"

ADHCar::ADHCar()
{
	PrimaryActorTick.bCanEverTick = true;

	// Ensuring this actor has a root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car Mesh"));
	Mesh->SetupAttachment(RootComponent);
	// Arrow
	PlayerAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerAttachPoint"));
	PlayerAttachPoint->SetupAttachment(Mesh);
	// Box Collision
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(Mesh);
}

void ADHCar::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> Components;
	GetComponents(UActorComponent::StaticClass(), Components);

	for (UActorComponent* Component : Components)
	{
		USplineComponent* Spline = Cast<USplineComponent>(Component);
		if (Spline)
		{
			DroneSplines.Add(Spline);
		}
	}
	
	if (PathSplineActor)
	{
		PathSpline = Cast<USplineComponent>(PathSplineActor->GetComponentByClass(USplineComponent::StaticClass()));
	}
}

void ADHCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PathSpline)
	{
		DistanceAlongSpline += Speed * DeltaTime;

		if (DistanceAlongSpline > PathSpline->GetSplineLength())
		{
			DistanceAlongSpline = 0.f;
		}

		FVector NewLocation = PathSpline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorLocation(NewLocation);

		FRotator NewRotation = PathSpline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorRotation(NewRotation);
	}
}

void ADHCar::SpawnDroneCount(int count)
{
	if (DroneSplines.Num() < count)
	{
		SpawnAllDrone();
		return;
	}
	
	int32 RandomStartIndex = FMath::RandRange(0, DroneSplines.Num() - 3);

	for (int i = 0; i < count; i++)
	{
		SpawnDrone(RandomStartIndex + i);
	}
}

void ADHCar::SpawnDroneOneTimeRandomly()
{
	if (DroneSplines.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No splines available to spawn drones."));
		return;
	}
	
	int32 RandomIndex = FMath::RandRange(0, DroneSplines.Num() - 1);
	SpawnDrone(RandomIndex);
}

void ADHCar::SpawnDrone(int index)
{
	if (index < 0 || index >= DroneSplines.Num()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid spline index"));
		return;
	}
    
	USplineComponent* Spline = DroneSplines[index];
	if (!Spline)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Spline Component"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FRotator SpawnRotation = Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);

	ADHDroneActor* spawnDrone = GetWorld()->SpawnActor<ADHDroneActor>(Drone, SpawnLocation, SpawnRotation, SpawnParams);
	if (spawnDrone)
	{
		spawnDrone->AttachToComponent(Spline, FAttachmentTransformRules::SnapToTargetIncludingScale);
		spawnDrone->Initialize(PlayerAttachPoint, Spline);
	}
}

void ADHCar::SpawnAllDrone()
{
	for (int i = 0; i < DroneSplines.Num(); ++i)
	{
		SpawnDrone(i);
	}
}
