// Fill out your copyright notice in the Description page of Project Settings.


#include "DHGameInstance.h"

UDHGameInstance::UDHGameInstance()
{
	PlayerHealth = 100;
	TargetScore = 3100;
	PlayerScore = 0;
	bGameOver = false;
	bVictory = false;
}

void UDHGameInstance::AddScore(int32 Points)
{
	if (!bGameOver)
	{
		PlayerScore += Points;
		UpdateGameState();
	}
}

void UDHGameInstance::DecreaseHealth(int32 Damage)
{
	if (!bGameOver)
	{
		PlayerHealth -= Damage;
		UpdateGameState();
	}
}

void UDHGameInstance::UpdateGameState()
{
	if (PlayerHealth <= 0)
	{
		PlayerHealth = 0;
		bGameOver = true;
		bVictory = false;
	}

	if (PlayerScore >= TargetScore)
	{
		bGameOver = true;
		bVictory = true;
	}
}

bool UDHGameInstance::IsGameOver() const
{
	return bGameOver;
}

bool UDHGameInstance::IsVictory() const
{
	return bVictory;
}
