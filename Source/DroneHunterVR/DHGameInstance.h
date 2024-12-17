// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DHGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRONEHUNTERVR_API UDHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDHGameInstance();
	void AddScore(int32 Points);
	void DecreaseHealth(int32 Damage);
	
	UFUNCTION(BlueprintCallable, Category="Health")
	void UpdateHealthUI(class ADHHPUIActor* UIActor, FVector LeftHandLocation, FRotator LeftHandRotation);
	

	// 상태 확인 함수
	UFUNCTION(BlueprintCallable, Category = "Game State")
	bool IsGameOver() const;

	UFUNCTION(BlueprintCallable, Category = "Game State")
	bool IsVictory() const;

	// 현재 점수와 체력 반환
	UFUNCTION(BlueprintCallable, Category = "Game State")
	int32 GetPlayerScore() const { return PlayerScore; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	int32 GetPlayerHealth() const { return PlayerHealth; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	int32 PlayerMaxHealth = 3;
protected:
	// 게임 상태 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	int32 PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	int32 PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	int32 TargetScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	bool bGameOver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	bool bVictory;

private:
	void UpdateGameState();
};
