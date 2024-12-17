#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DHDroneActor.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class DRONEHUNTERVR_API ADHDroneActor : public AActor
{
	GENERATED_BODY()

public:	
	ADHDroneActor();
	virtual void Tick(float DeltaTime) override;

	void Initialize(UActorComponent* InTargetLocation, USplineComponent* InSplinePath, int InHealth = 3, float InSpeed = 150.f);
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerBullet;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> DroneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> Collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Health = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AActor> BulletClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UParticleSystem> DestroyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float FollowSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAudioComponent> LoopingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> DroneSound; // loop sound
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> DamageSound; // 대미지 받을 떄 사운드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> ShootSound;
private:
	FTimerHandle AttackTimerHandle;
	UPROPERTY()
	USplineComponent* SplinePath;
	UPROPERTY()
	UActorComponent* Target;

	void Shoot();
	void UpdateMovement(float DeltaTime);
	void TakeDamage();
	void DestroyDrone();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float DistanceAlongSpline;
};
