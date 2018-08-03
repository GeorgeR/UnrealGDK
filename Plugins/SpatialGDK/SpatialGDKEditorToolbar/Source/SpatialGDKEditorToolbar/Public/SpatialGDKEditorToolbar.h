// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "TickableEditorObject.h"

class FToolBarBuilder;
class FMenuBuilder;
class FUICommandList;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogSpatialGDKEditor, Log, All);

class FSpatialGDKEditorToolbarModule : public IModuleInterface, public FTickableEditorObject
{
public:
	FSpatialGDKEditorToolbarModule();

	void StartupModule() override;
	void ShutdownModule() override;
	void PreUnloadCallback() override;

	/** FTickableEditorObject interface */
	void Tick(float DeltaTime) override;
	bool IsTickable() const override
	{
		return true;
	}

	TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSpatialGDKEditorToolbarModule, STATGROUP_Tickables);
	}

private:
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();

	void MapActions(TSharedPtr<FUICommandList> PluginCommands);
	void SetupToolbar(TSharedPtr<FUICommandList> PluginCommands);
	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	void StartSpatialOSButtonClicked();
	void StopSpatialOSButtonClicked();
	bool StartSpatialOSStackCanExecute() const;
	bool StopSpatialOSStackCanExecute() const;

	void LaunchInspectorWebpageButtonClicked();
	void CreateSnapshotButtonClicked();
	void GenerateInteropCodeButtonClicked();
	void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);

private:
	bool CanExecuteInteropCodeGen();
	void StopRunningStack();
	void CheckForRunningStack();

	void ShowTaskStartNotification(const FString& NotificationText);
	void ShowSuccessNotification(const FString& NotificationText);
	void ShowFailedNotification(const FString& NotificationText);

	static void ShowCompileLog();

	TSharedPtr<FUICommandList> PluginCommands;
	FDelegateHandle OnPropertyChangedDelegateHandle;
	FProcHandle SpatialOSStackProcHandle;
	bool bStopSpatialOnExit;
	
	uint32 SpatialOSStackProcessID;

	TWeakPtr<SNotificationItem> TaskNotificationPtr;

	// Sounds used for execution of tasks.
	USoundBase* ExecutionStartSound;
	USoundBase* ExecutionSuccessSound;
	USoundBase* ExecutionFailSound;

	TFuture<bool> InteropCodegenResult;
	bool bInteropCodeGenRunning;
};
