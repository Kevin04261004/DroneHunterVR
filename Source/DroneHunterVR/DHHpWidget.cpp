#include "DHHpWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UDHHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Ensure that the ProgressBar is valid
	if (HealthProgressBar)
	{
		// Initialize or reset if needed
		HealthProgressBar->SetPercent(1.0f); // Set to full health initially, or to any value you want
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthProgressBar is NULL!"));
	}
}

void UDHHpWidget::UpdateHealth(float curHp, float maxHp)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(curHp / maxHp);
	}

	if (HealthText)
	{
		FString HealthTextString = FString::Printf(TEXT("%d / %d"), FMath::RoundToInt(curHp), FMath::RoundToInt(maxHp));
		HealthText->SetText(FText::FromString(HealthTextString));
	}
}
