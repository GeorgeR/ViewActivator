#pragma once

#include "ViewAwareContext.h"

#include "DialogContext.generated.h"

UCLASS(Abstract)
class VIEWACTIVATOR_API UDialogContext
	: public UViewAwareContext
{
	GENERATED_BODY()

public:
	UDialogContext() : UViewAwareContext() { }

	UFUNCTION(BlueprintCallable, Category = "Empires|UI")
	virtual void Close(UObject* InWorldContextObject);
};