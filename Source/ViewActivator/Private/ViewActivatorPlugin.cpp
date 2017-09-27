#include "ViewActivatorPlugin.h"

#define LOCTEXT_NAMESPACE "FViewActivatorModule"

class FViewActivatorModule 
	: public IViewActivatorModule
{
public:
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FViewActivatorModule, ViewActivator)