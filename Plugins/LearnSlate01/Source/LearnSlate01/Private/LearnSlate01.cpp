// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnSlate01.h"
#include "LearnSlate01Style.h"
#include "LearnSlate01Commands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "CustomButton.h"

static const FName LearnSlate01TabName("LearnSlate01");

#define LOCTEXT_NAMESPACE "FLearnSlate01Module"

void FLearnSlate01Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FLearnSlate01Style::Initialize();
	FLearnSlate01Style::ReloadTextures();

	FLearnSlate01Commands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLearnSlate01Commands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FLearnSlate01Module::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLearnSlate01Module::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(LearnSlate01TabName, FOnSpawnTab::CreateRaw(this, &FLearnSlate01Module::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FLearnSlate01TabTitle", "LearnSlate01"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FLearnSlate01Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FLearnSlate01Style::Shutdown();

	FLearnSlate01Commands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LearnSlate01TabName);
}

TSharedRef<SDockTab> FLearnSlate01Module::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FLearnSlate01Module::OnSpawnPluginTab")),
		FText::FromString(TEXT("LearnSlate01.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//// Put your tab content here!
			//SNew(SBox)
			//.HAlign(HAlign_Center)
			//.VAlign(VAlign_Center)
			//[
			//	SNew(STextBlock)
			//	.Text(WidgetText)
			//]
			
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()[
				SNew(SButton)
				.Text(LOCTEXT("", "°´Å¥"))
				.OnClicked(FOnClicked::CreateRaw(this, &FLearnSlate01Module::TestButtonClicked))
			
			]+ SVerticalBox::Slot()[
				SNew(CustomButton)
			]
			
		]
	;
}

void FLearnSlate01Module::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(LearnSlate01TabName);
}

FReply FLearnSlate01Module::TestButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Hello World !!!"));

	return FReply::Handled();
}

void FLearnSlate01Module::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FLearnSlate01Commands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FLearnSlate01Commands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLearnSlate01Module, LearnSlate01)