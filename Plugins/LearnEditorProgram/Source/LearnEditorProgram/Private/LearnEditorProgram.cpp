// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnEditorProgram.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FLearnEditorProgramModule"

void FLearnEditorProgramModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

	MenuExtender->AddMenuExtension("LevelEditor", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Builder) {
		Builder.BeginSection("CustomMenu");

		Builder.AddMenuEntry(
			FText::FromString("Menu1"),
			FText::FromString("Menu1"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FLearnEditorProgramModule::MenuCallback))
		);

		Builder.AddSubMenu(
			FText::FromString("Menu2"),
			FText::FromString("Menu2"),
			FNewMenuDelegate::CreateRaw(this, &FLearnEditorProgramModule::MenuCallback2)
		);

		Builder.EndSection();
		}));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

}

void FLearnEditorProgramModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FLearnEditorProgramModule::MenuCallback()
{
	UE_LOG(LogTemp, Log, TEXT("MenuCallback() !!!"));
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Just a test!"));

}

void FLearnEditorProgramModule::MenuCallback2(FMenuBuilder& MenuBuilder)
{
	UE_LOG(LogTemp, Log, TEXT("MenuCallback() !!!2"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLearnEditorProgramModule, LearnEditorProgram)