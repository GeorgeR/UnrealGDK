// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
#include "SpatialGDKEditorToolbarSettings.h"
#include "Paths.h"

USpatialGDKEditorToolbarSettings::USpatialGDKEditorToolbarSettings(const FObjectInitializer& ObjectInitializer) : SpatialOSLaunchConfig(TEXT("default_launch.json")), bStopSpatialOnExit(false), Super(ObjectInitializer)
{
	ProjectRootFolder.Path = FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPaths::GetProjectFilePath()) + FString(TEXT("/../spatial/")));
	InteropCodegenOutputFolder.Path = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::GameSourceDir(), FString::Printf(TEXT("%s/Generated/"), FApp::GetProjectName())));
}

FString USpatialGDKEditorToolbarSettings::ToString()
{
	TArray<FStringFormatArg> Args;
	Args.Add(ProjectRootFolder.Path);
	Args.Add(SpatialOSLaunchConfig);
	Args.Add(bStopSpatialOnExit);
	Args.Add(InteropCodegenOutputFolder.Path);

	return FString::Format(TEXT("ProjectRootFolder={0}, SpatialOSLaunchArgument={1}, "
								"bStopSpatialOnExit={2}, InteropCodegenOutputFolder={3}"),
						   Args);
}
