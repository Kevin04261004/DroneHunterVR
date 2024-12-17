#include "DHHPUIActor.h"
#include "DHHpWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"  // 필요한 헤더 추가

ADHHPUIActor::ADHHPUIActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* NewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("NewRootComponent"));
	RootComponent = NewRoot;  // RootComponent를 새 SceneComponent로 설정

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);  // UI를 월드 공간에서 표시
	WidgetComponent->SetDrawSize(FVector2D(200, 100));  // UI 크기 설정
	WidgetComponent->SetVisibility(true);  // UI가 보이도록 설정
}

void ADHHPUIActor::BeginPlay()
{
	Super::BeginPlay();
	if (HealthWidgetClass)
	{
		HealthWidget = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
		if (HealthWidget)
		{
			WidgetComponent->SetWidget(HealthWidget);
		}
	}
}

void ADHHPUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADHHPUIActor::UpdateHealthUI(FVector LeftHandLocation, FRotator LeftHandRotation, float curHp, float maxHp)
{
	if (WidgetComponent) {
		// Update the location of the Widget to the given LeftHandLocation
		WidgetComponent->SetWorldLocation(LeftHandLocation);

		// Make the widget face the camera
		APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		if (CameraManager) {
			FVector CameraLocation = CameraManager->GetCameraLocation();
			FVector DirectionToCamera = CameraLocation - LeftHandLocation;
			FRotator LookAtRotation = DirectionToCamera.Rotation();

			WidgetComponent->SetWorldRotation(LookAtRotation);
		}
	}
	if (HealthWidget)
	{
		UDHHpWidget* HealthUI = Cast<UDHHpWidget>(HealthWidget);
		if (HealthUI)
		{
			HealthUI->UpdateHealth(curHp, maxHp);
		}
	}
}
