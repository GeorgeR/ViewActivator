#pragma once

#include "ViewWidget.h"

struct VIEWACTIVATOR_API FViewPair
{
public:
	FViewPair() { }
	FViewPair(FName InViewName);

	FName ViewName;
	TSubclassOf<UViewWidget> ViewClass;
	UViewWidget* View;
	bool bIsShowing;

	void PreShow(UObject* InParent);
	void SetContext(UObject* InContext);
};

class VIEWACTIVATOR_API FViewManager
{
public:
	static FViewManager* Get();

	void Show(UObject* InParent, UObject* InContext, const FInputModeDataBase& InInputMode = FInputModeGameAndUI(), bool bShowMouse = false, float delay = 0.0f);
	void ShowInSlot(UObject* InParent, UObject* InContext, UViewWidget* InParentView, FName InSlotName, float delay = 0.0f);
	void Close(UObject* InContext);

	void RegisterView(UClass* InContextClass, FName InViewName);
	FViewPair* GetViewForContext(UClass* InContextClass);

private:
	TMap<UClass*, FViewPair> Views;
	FTimerHandle TimerHandle;

	FViewPair* GetViewForContext(UObject* InContext);

	void SetInputMode(UObject* InWorldContext, const FInputModeDataBase& InInputMode = FInputModeGameAndUI(), bool bShowMouse = false);
	void ShowInternal(FViewPair* InView, UObject* InParent, UObject* InContext, const FInputModeDataBase& InInputMode = FInputModeGameAndUI(), bool bShowMouse = false);
	void ShowInSlotInternal(UViewWidget* InParentView, FName InSlotName, FViewPair* InView, UObject* InParent, UObject* InContext);
};