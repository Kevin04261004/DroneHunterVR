// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DHHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRONEHUNTERVR_API UDHHpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 체력 값을 바인딩하는 ProgressBar
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;
	
	virtual void NativeConstruct() override;
	// 체력 값 업데이트 함수
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float curHp, float maxHp);
};
