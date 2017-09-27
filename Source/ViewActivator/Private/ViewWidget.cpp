#include "ViewWidget.h"

#include "ViewActivatorPlugin.h"
#include "WidgetAnimation.h"
#include "UObjectBaseUtility.h"
#include "ScriptDelegates.h"

void UViewWidget::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	GetAnimations();
}

bool UViewWidget::SetContext_Implementation(UObject* Context)
{
	return true;
}

void UViewWidget::PlayShow()
{
	if (ShowAnimation != nullptr)
		PlayAnimation(ShowAnimation);
}

void UViewWidget::PlayClose()
{
	if (CloseAnimation != nullptr)
		PlayAnimation(CloseAnimation);
}

void UViewWidget::CloseView()
{
	if (CloseAnimation != nullptr)
	{
		this->PlayClose();
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->bShowMouseCursor = false;
		ActiveSequencePlayers.Last()->OnSequenceFinishedPlaying().AddLambda([&](UUMGSequencePlayer& SequencePlayer) -> void {
			this->RemoveFromParent();
			if (OnClosed.IsBound())
				OnClosed.Broadcast();
		});
	}
	else
	{
		this->RemoveFromParent();
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->bShowMouseCursor = false;
		if (OnClosed.IsBound())
			OnClosed.Broadcast();
	}
}

void UViewWidget::GetAnimations()
{
	ShowAnimation = nullptr;
	CloseAnimation = nullptr;

	UProperty* Property = GetClass()->PropertyLink;
	while (Property != nullptr)
	{
		if (Property->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property);

			if (ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Object = ObjectProperty->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Object);

				if (WidgetAnimation != nullptr)
				{
					Animations.Add(WidgetAnimation);

					FString Name;
					static FString ShowName = TEXT("Show");
					static FString CloseName = TEXT("Close");
					WidgetAnimation->GetName(Name);
					if (Name.Contains(ShowName, ESearchCase::IgnoreCase))
						ShowAnimation = WidgetAnimation;
					if (Name.Contains(CloseName, ESearchCase::IgnoreCase))
					{
						CloseAnimation = WidgetAnimation;
					}
				}
			}
		}

		Property = Property->PropertyLinkNext;
	}
}