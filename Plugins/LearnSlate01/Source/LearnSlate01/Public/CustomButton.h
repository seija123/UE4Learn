#pragma once
#include "CoreMinimal.h"
#include "Widgets\SCompoundWidget.h"



class CustomButton : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(CustomButton) : _IsFocusable(true)
    {}
        SLATE_ARGUMENT(bool, IsFocusable)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    FReply OnClick();
private:
    bool IsFocusable;
};


