#pragma once

#include "ViewManager.h"

#include "ViewAwareContext.generated.h"

// DEPRECATE
UCLASS()
class VIEWACTIVATOR_API UViewAwareContext
	: public UObject
{
	GENERATED_BODY()

public:
	UViewAwareContext();
	
	void SetView(FViewPair* InView);

	virtual class UWorld* GetWorld() const override;

protected:
	FViewPair* View;
};