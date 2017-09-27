using UnrealBuildTool;

public class ViewActivator : ModuleRules
{
	public ViewActivator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"ViewActivator/Public",
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"ViewActivator/Private",
			});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			    "UMG",
            });

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			});
	}
}