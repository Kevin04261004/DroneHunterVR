// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DHCar.generated.h"

class UBoxComponent;
class ADHDroneActor;
class UDHDroneComponent;
class UArrowComponent;
class USplineComponent;

UCLASS()
class DRONEHUNTERVR_API ADHCar : public AActor
{
	GENERATED_BODY()

public:
	ADHCar();
	
protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> PathSplineActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* PlayerAttachPoint;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	float Speed = 300.f;

	UPROPERTY()
	TArray<TObjectPtr<USplineComponent>> DroneSplines;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADHDroneActor> Drone;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
private:
	float DistanceAlongSpline = 0.f;
	UPROPERTY()
	USplineComponent* PathSpline;

public:
	void SpawnDroneCount(int count);
	void SpawnDroneOneTimeRandomly();
	void SpawnDrone(int index);
	void SpawnAllDrone();
};
