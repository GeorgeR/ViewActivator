#include "DialogContext.h"

#include "ViewActivatorPlugin.h"

void UDialogContext::Close(UObject* InWorldContextObject)
{
	if (View != nullptr)
		FViewManager::Get()->Close(this);
}