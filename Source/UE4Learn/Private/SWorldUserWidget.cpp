// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D ScreenPostion;

	if (!IsValid(AttachedActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachedActor is nullptr !!!"));

		RemoveFromParent();
		return;
	}

	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPostion))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPostion /= Scale;

		if(ParentSizeBox)
			ParentSizeBox->SetRenderTranslation(ScreenPostion);

	}

}