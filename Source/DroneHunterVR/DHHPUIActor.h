// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DHGameInstance.h"
#include "GameFramework/Actor.h"
#include "DHHPUIActor.generated.h"

UCLASS()
class DRONEHUNTERVR_API ADHHPUIActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADHHPUIActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* WidgetComponent;

	// Health UI의 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;

	// 생성된 UI 위젯
	UPROPERTY()
	UUserWidget* HealthWidget;

	UPROPERTY()
	UDHGameInstance* GameInstance;

	// 손 위치 업데이트 함수
	void UpdateHealthUI(FVector LeftHandLocation, FRotator LeftHandRotation, float curHp, float maxHp);

};
