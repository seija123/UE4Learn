// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnSlate01Commands.h"

#define LOCTEXT_NAMESPACE "FLearnSlate01Module"

void FLearnSlate01Commands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "LearnSlate01", "Bring up LearnSlate01 window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
