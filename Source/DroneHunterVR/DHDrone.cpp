#include "DHDrone.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

ADHDrone::ADHDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	// 드론 메쉬 초기화
	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = DroneMesh;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(DroneMesh);
	Health = 3;
	AttackTime = 2.0f;
	FollowSpeed = 300.0f;
}

void ADHDrone::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADHDrone::OnOverlapBegin);
}

void ADHDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

void ADHDrone::Initialize(UActorComponent* InTargetLocation, USplineComponent* InSplinePath)
{
	Target = InTargetLocation;
	SplinePath = InSplinePath;
}

void ADHDrone::UpdateMovement(float DeltaTime)
{
	if (SplinePath)
	{
		DistanceAlongSpline += Speed * DeltaTime;
        
		FVector NewLocation = SplinePath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorLocation(NewLocation);

		FRotator NewRotation = SplinePath->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorRotation(NewRotation);

		if (DistanceAlongSpline > SplinePath->GetSplineLength())
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ADHDrone::Shoot, AttackTime, true);
			SplinePath = nullptr;
		}
	}
}

void ADHDrone::Shoot()
{
	if (BulletClass)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		GetWorld()->SpawnActor<AActor>(BulletClass, SpawnLocation, SpawnRotation);
	}
}

void ADHDrone::TakeDamage()
{
	Health--;
	if (Health <= 0)
	{
		DestroyDrone();
	}
}

void ADHDrone::DestroyDrone()
{
	if (DestroyEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation());
	}
	Destroy();
}

void ADHDrone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							  bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TakeDamage();
	}
}