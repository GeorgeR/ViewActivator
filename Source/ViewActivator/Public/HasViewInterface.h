#pragma once

#include "CoreMinimal.h"

#include "HasViewInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UHasViewInterface : public UInterface
{
	GENERATED_BODY()
};

class VIEWACTIVATOR_API IHasViewInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	virtual UClass* GetViewContextClass();
	
	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	virtual void ShowView();

	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	virtual void CloseView();
};