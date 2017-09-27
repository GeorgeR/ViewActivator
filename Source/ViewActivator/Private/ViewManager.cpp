#include "ViewManager.h"

#include "ViewAwareContext.h"
#include "ViewActivatorPlugin.h"

FViewPair::FViewPair(FName InViewName)
	: ViewName(InViewName),
	ViewClass(nullptr),
	View(nullptr),
	bIsShowing(false)
{
	ConstructorHelpers::FClassFinder<UViewWidget> ViewClassFinder(*InViewName.ToString());
	ViewClass = ViewClassFinder.Class;

	check(ViewClass);
}

void FViewPair::PreShow(UObject* InParent)
{
	check(InParent);

	if (View != nullptr)
		return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(InParent);
	check(GameInstance);

	View = CreateWidget<UViewWidget>(GameInstance, ViewClass);
}

void FViewPair::SetContext(UObject* InContext)
{
	check(View);
	check(InContext);

	View->SetContext(InContext);
	if (InContext->GetClass()->IsChildOf(UViewAwareContext::StaticClass()))
	{
		UViewAwareContext* ViewAwareContext = Cast<UViewAwareContext>(InContext);
		ViewAwareContext->SetView(this);
	}
}

FViewManager* FViewManager::Get()
{
	static FViewManager* Instance = nullptr;
	if (Instance == nullptr)
		Instance = new FViewManager();

	return Instance;
}

void FViewManager::Show(UObject* InParent, UObject* InContext, const FInputModeDataBase& InInputMode /*= FInputModeGameAndUI()*/, bool bShowMouse /*= false*/, float delay /*= 0.0f*/)
{
	FViewPair* View = GetViewForContext(InContext);
	check(View);

	if (delay != 0.0f)
		UGameplayStatics::GetGameMode(InParent)->GetWorldTimerManager().SetTimer(TimerHandle, [&]()->void { ShowInternal(View, InParent, InContext, InInputMode, bShowMouse); }, delay, false);
	else
		ShowInternal(View, InParent, InContext, InInputMode, bShowMouse);
}

void FViewManager::ShowInSlot(UObject* InParent, UObject* InContext, UViewWidget* InParentView, FName InSlotName, float delay /*= 0.0f*/)
{
	FViewPair* View = GetViewForContext(InContext);
	check(View);

	if (delay != 0.0f)
		UGameplayStatics::GetGameMode(InParent)->GetWorldTimerManager().SetTimer(TimerHandle, [&]()->void { ShowInSlotInternal(InParentView, InSlotName, View, InParent, InContext); }, delay, false);
	else
		ShowInSlotInternal(InParentView, InSlotName, View, InParent, InContext);
}

void FViewManager::Close(UObject* InContext)
{
	FViewPair* ViewPair = GetViewForContext(InContext);

	SetInputMode(InContext, FInputModeGameOnly(), false);
	check(ViewPair->View);

	ViewPair->View->CloseView();
	ViewPair->bIsShowing = false;
}

void FViewManager::RegisterView(UClass* InContextClass, FName InViewName)
{
	if (Views.Contains(InContextClass))
		Views[InContextClass] = FViewPair(InViewName);

	Views.Add(InContextClass, FViewPair(InViewName));
}

FViewPair* FViewManager::GetViewForContext(UClass* InContextClass)
{
	if (Views.Contains(InContextClass))
		return &Views[InContextClass];

	//UE_LOG(LogViewManager, Error, TEXT("No View found for %s"), *InContextClass->GetFName());

	return nullptr;
}

FViewPair* FViewManager::GetViewForContext(UObject* InContext)
{
	check(InContext);

	if (Views.Contains(InContext->GetClass()))
		return &Views[InContext->GetClass()];

	return nullptr;
}

void FViewManager::SetInputMode(UObject* InWorldContext, const FInputModeDataBase& InInputMode /*= FInputModeGameAndUI()*/, bool bShowMouse)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(InWorldContext, 0);
	Controller->SetInputMode(InInputMode);
	Controller->bShowMouseCursor = bShowMouse;
}

void FViewManager::ShowInternal(FViewPair* InView, UObject* InParent, UObject* InContext, const FInputModeDataBase& InInputMode /*= FInputModeGameAndUI()*/, bool bShowMouse /*= false*/)
{
	check(InView);
	check(InParent);

	SetInputMode(InParent, InInputMode, bShowMouse);

	InView->PreShow(InParent);
	InView->SetContext(InContext);

	InView->bIsShowing = true;

	InView->View->AddToViewport();
	InView->View->PlayShow();
}

void FViewManager::ShowInSlotInternal(UViewWidget* InParentView, FName InSlotName, FViewPair* InView, UObject* InParent, UObject* InContext)
{
	check(InParentView);
	check(InView);

	InView->PreShow(InParent);
	InView->SetContext(InContext);

	InView->bIsShowing = true;

	InParentView->SetContentForSlot(InSlotName, InView->View);
	InView->View->PlayShow();
}