// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTrafficEditor.h"
#include "Modules/ModuleManager.h"
#include "Windows/MenuTool.h"

IMPLEMENT_GAME_MODULE(FVehicleTrafficEditor, VehicleTrafficEditor);

void FVehicleTrafficEditor::AddModuleListeners()
{
	//ModuleListeners.Add(MakeShareable(new MenuTool));
}

void FVehicleTrafficEditor::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FVehicleTrafficEditor::MakePulldownMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}
	ICustomModuleInterface::StartupModule();
}

void FVehicleTrafficEditor::ShutdownModule()
{
}

void FVehicleTrafficEditor::AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList, EExtensionHook::Position position)
{
	MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FVehicleTrafficEditor::MakePulldownMenu(FMenuBarBuilder &menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString("Vehicle Traffic"),
		FText::FromString("Open the Example menu"),
		FNewMenuDelegate::CreateRaw(this, &FVehicleTrafficEditor::FillPulldownMenu),
		"Vehicle Traffic",
		FName(TEXT("ExampleMenu"))
	);
}

void FVehicleTrafficEditor::FillPulldownMenu(FMenuBuilder &menuBuilder)
{
	// just a frame for tools to fill in
	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 1"));
	menuBuilder.AddMenuSeparator(FName("Section_1"));
	menuBuilder.EndSection();

	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
	menuBuilder.AddMenuSeparator(FName("Section_2"));
	menuBuilder.EndSection();
}