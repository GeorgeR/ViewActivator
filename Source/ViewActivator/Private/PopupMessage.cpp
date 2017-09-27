#include "PopupMessage.h"

#include "ViewActivatorPlugin.h"
#include "ViewManager.h"

UPopupMessage::UPopupMessage()
{
	FViewManager::Get()->RegisterView(UPopupMessage::StaticClass(), TEXT("/Game/Empires/UI/Blueprints/WBP_PopupMessage"));
}

void UPopupMessage::Show_Implementation(UObject* InWorldContextObject, const FText& InText, const FColor& InColor /*= FColor::White*/, const float& InTime /*= 3.0f*/)
{
	Text = InText;
	Color = InColor;

	auto GameInstance = InWorldContextObject->GetWorld()->GetGameInstance();
	FViewManager::Get()->Show(this, this, FInputModeGameOnly());
	
	if (GameInstance->GetTimerManager().GetTimerRate(ShowHandle) > -1)
		GameInstance->GetTimerManager().ClearTimer(ShowHandle);

	GameInstance->GetTimerManager().SetTimer(ShowHandle, this, &UPopupMessage::Close, InTime);
}

void UPopupMessage::Close()
{
	FViewManager::Get()->Close(this);
}