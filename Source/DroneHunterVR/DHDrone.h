#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DHDrone.generated.h"

class USplineComponent;

UCLASS()
class DRONEHUNTERVR_API ADHDrone : public AActor
{
	GENERATED_BODY()

public:	
	ADHDrone();
	virtual void Tick(float DeltaTime) override;

	void Initialize(UActorComponent* InTargetLocation, USplineComponent* InSplinePath);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> DroneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> Collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Health;

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
