#include "HasViewInterface.h"

#include "ViewActivatorPlugin.h"

UClass* IHasViewInterface::GetViewContextClass()
{
	return nullptr;
}

void IHasViewInterface::ShowView() { }

void IHasViewInterface::CloseView() { }