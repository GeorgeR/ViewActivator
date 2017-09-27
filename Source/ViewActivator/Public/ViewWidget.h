#pragma once

#include "UMG.h"
#include "Blueprint/UserWidget.h"

#include "ViewWidget.generated.h"

UCLASS()
class VIEWACTIVATOR_API UViewWidget
	: public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UWidgetAnimation*> Animations;

	UPROPERTY()
	UWidgetAnimation* ShowAnimation;

	UPROPERTY()
	UWidgetAnimation* CloseAnimation;

	DECLARE_MULTICAST_DELEGATE(FOnClosed);
	FOnClosed OnClosed;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Empires|UI")
	bool SetContext(UObject* Context);
	virtual bool SetContext_Implementation(UObject* Context);

	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	void PlayShow();

	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	void PlayClose();

	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	void CloseView();

private:
	void GetAnimations();

protected:
	virtual void NativeConstruct() override;
};