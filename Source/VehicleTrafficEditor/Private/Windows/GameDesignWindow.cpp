// Fill out your copyright notice in the Description page of Project Settings.
/*
#include "VehicleTrafficEditor.h"
#include "Windows/GameDesignWindow.h"
#include "Framework/Commands/Commands.h"

#define LOCTEXT_NAMESPACE "UGameDesignWindow"

class UGameDesignWindowCommands : public TCommands<UGameDesignWindowCommands>
{
public:

	UGameDesignWindowCommands() : TCommands<UGameDesignWindowCommands> (
		TEXT("MenuTool"), // Context name for fast lookup
		FText::FromString("Example Menu tool"), // Context name for displaying
		NAME_None,   // No parent context
		FEditorStyle::GetStyleSetName() // Icon Style Set
	)
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuCommand1, "Menu Command 1", "Test Menu Command 1.", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand1, "Menu Command 3", "Test Menu Command 3.", EUserInterfaceActionType::Button, FInputGesture());
	}

public:
	TSharedPtr<FUICommandInfo> MenuCommand1;
};

// ---------------------
void UGameDesignWindow::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	UGameDesignWindowCommands::Register();
	MapCommands();
	FVehicleTrafficEditor::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &UGameDesignWindow::MakeMenuEntry),
		FName("Section_1"),
		CommandList);
}

void UGameDesignWindow::OnShutdownModule()
{
	UGameDesignWindowCommands::Unregister();
}

void UGameDesignWindow::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(UGameDesignWindowCommands::Get().MenuCommand1);
}

void UGameDesignWindow::MenuCommand1()
{
	UE_LOG(LogClass, Log, TEXT("clicked MenuCommand1"));
}

void UGameDesignWindow::MapCommands()
{
	const auto& Commands = UGameDesignWindowCommands::Get();

	CommandList->MapAction(
		Commands.MenuCommand1,
		FExecuteAction::CreateSP(this, &UGameDesignWindow::MenuCommand1),
		FCanExecuteAction());
}

#undef LOCTEXT_NAMESPACE*/