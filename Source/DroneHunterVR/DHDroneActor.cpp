#include "DHDroneActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ADHDroneActor::ADHDroneActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 드론 메쉬 초기화
	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = DroneMesh;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(DroneMesh);

	LoopingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopingSound"));
	LoopingSound->bAutoActivate = false;
	
	Health = 3;
	AttackTime = 2.0f;
	FollowSpeed = 300.0f;
}

void ADHDroneActor::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADHDroneActor::OnOverlapBegin);

	if (DroneSound)
	{
		// 오디오 컴포넌트에 사운드 할당 및 재생
		LoopingSound->SetSound(DroneSound);
		LoopingSound->Play();
	}
}

void ADHDroneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

void ADHDroneActor::Initialize(UActorComponent* InTargetLocation, USplineComponent* InSplinePath, int InHealth,
	float InSpeed)
{
	Target = InTargetLocation;
	SplinePath = InSplinePath;
	Health = InHealth;
	Speed = InSpeed;
}

void ADHDroneActor::BeginDestroy()
{
	Super::BeginDestroy();
	Collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADHDroneActor::OnOverlapBegin);
}

void ADHDroneActor::UpdateMovement(float DeltaTime)
{
	if (SplinePath)
	{
		DistanceAlongSpline += Speed * DeltaTime;
        
		FVector NewLocation = SplinePath->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorLocation(NewLocation);

		FRotator NewRotation = SplinePath->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorRotation(NewRotation);

		if (Target)
		{
			// Target 위치 가져오기
			FVector TargetLocation = Target->GetOwner()->GetActorLocation();
			FVector CurrentLocation = GetActorLocation();

			// LookAt 회전 계산
			FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
			SetActorRotation(LookAtRotation);  // 드론 회전 적용
		}
		
		if (DistanceAlongSpline > SplinePath->GetSplineLength())
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ADHDroneActor::Shoot, AttackTime, true);
			SplinePath = nullptr;
		}
	}
}

void ADHDroneActor::Shoot()
{
	if (BulletClass && Target)
	{
		// 드론의 현재 위치를 총알 스폰 위치로 설정
		FVector SpawnLocation = GetActorLocation();

		// 타겟 위치를 가져와 방향 계산
		FVector TargetLocation = Target->GetOwner()->GetActorLocation();
		FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal(); // 방향 벡터 정규화

		// 총알이 타겟을 향하도록 회전 설정
		FRotator SpawnRotation = Direction.Rotation();

		// 총알 생성
		AActor* SpawnedBullet = GetWorld()->SpawnActor<AActor>(BulletClass, SpawnLocation, SpawnRotation);
		if (SpawnedBullet)
		{
			// 총알에 초기 속도 부여 (Projectile Movement가 필요할 경우)
			UProjectileMovementComponent* ProjectileComp = SpawnedBullet->FindComponentByClass<UProjectileMovementComponent>();
			if (ProjectileComp)
			{
				ProjectileComp->Velocity = Direction * ProjectileComp->InitialSpeed;
			}
		}
	}
}

void ADHDroneActor::TakeDamage()
{
	if (--Health <= 0)
	{
		DestroyDrone();
	}
	else
	{
		// 3D 사운드 재생
		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
		}
	}
}

void ADHDroneActor::DestroyDrone()
{
	if (DestroyEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation());
	}
	Destroy();
}

void ADHDroneActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							  bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		TakeDamage();
	}
}