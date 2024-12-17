// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCollision.h"

#include "DHCar.h"

ASpawnCollision::ASpawnCollision()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create and initialize the collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawnCollision::OnCollisionOccurred);
}


void ASpawnCollision::OnCollisionOccurred(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADHCar* Car = Cast<ADHCar>(OtherActor))
	{
		Car->SpawnDroneCount(SpawnAmount);
	}
}