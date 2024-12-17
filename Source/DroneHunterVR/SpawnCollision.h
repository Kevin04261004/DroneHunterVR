// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnCollision.generated.h"

UCLASS()
class DRONEHUNTERVR_API ASpawnCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnCollision();

	UFUNCTION()
	void OnCollisionOccurred(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	int SpawnAmount = 1;
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	
};
