#pragma once

#include "UObject/NoExportTypes.h"

#include "PopupMessage.generated.h"

UCLASS(BlueprintType)
class VIEWACTIVATOR_API UPopupMessage
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPopupMessage();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FText Text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Color;

	FTimerHandle ShowHandle;

	UFUNCTION(BlueprintCallable, Client, Reliable, Category = "Empires|UI")
	void Show(UObject* InWorldContextObject, const FText& InText, const FColor& InColor = FColor::White, const float& InTime = 3.0f);

private:
	void Close();
};