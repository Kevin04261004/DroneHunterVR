// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DHDroneBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DRONEHUNTERVR_API ADHDroneBullet : public AActor
{
	GENERATED_BODY()
	
public:
	ADHDroneBullet();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlayerClass;
	
public:	
	virtual void Tick(float DeltaTime) override;

	// 충돌 처리
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 1.0f;

};
