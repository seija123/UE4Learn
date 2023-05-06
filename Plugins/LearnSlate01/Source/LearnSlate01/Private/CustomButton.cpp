#include "CustomButton.h"

#define LOCTEXT_NAMESPACE "FLearnSlate01Module"

void CustomButton::Construct(const FArguments& InArgs)
{
	ChildSlot[
		SNew(SButton)
		.Text(LOCTEXT("", "°´Å¥"))
		.OnClicked(FOnClicked::CreateRaw(this, &CustomButton::OnClick))
	];

}

FReply CustomButton::OnClick()
{
	UE_LOG(LogTemp, Log, TEXT("CustomButton::OnClick !!!"));

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE