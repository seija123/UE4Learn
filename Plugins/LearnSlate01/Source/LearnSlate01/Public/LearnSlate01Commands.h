// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LearnSlate01Style.h"

class FLearnSlate01Commands : public TCommands<FLearnSlate01Commands>
{
public:

	FLearnSlate01Commands()
		: TCommands<FLearnSlate01Commands>(TEXT("LearnSlate01"), NSLOCTEXT("Contexts", "LearnSlate01", "LearnSlate01 Plugin"), NAME_None, FLearnSlate01Style::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};