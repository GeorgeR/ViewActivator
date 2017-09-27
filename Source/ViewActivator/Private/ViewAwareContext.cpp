#include "ViewAwareContext.h"

#include "ViewActivatorPlugin.h"

UViewAwareContext::UViewAwareContext()
	: View(nullptr) { }

void UViewAwareContext::SetView(FViewPair* InView)
{
	View = InView;
}

class UWorld* UViewAwareContext::GetWorld() const
{
	return GetOuter()->GetWorld();
}