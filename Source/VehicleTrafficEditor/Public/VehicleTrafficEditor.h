// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UnrealEd.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Editor/PropertyEditor/Public/PropertyEditing.h"
#include "IAssetTypeActions.h"
#include "ICustomModuleInterface.h"

class FVehicleTrafficEditor : public ICustomModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() override;

	static inline FVehicleTrafficEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FVehicleTrafficEditor>("ToolExampleEditor");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ToolExampleEditor");
	}

	void AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList = NULL, EExtensionHook::Position position = EExtensionHook::Before);
	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; };

protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;

	static TSharedRef<FWorkspaceItem> MenuRoot;

	void MakePulldownMenu(FMenuBarBuilder &menuBuilder);
	void FillPulldownMenu(FMenuBuilder &menuBuilder);
};