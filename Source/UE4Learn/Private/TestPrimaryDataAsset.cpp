// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPrimaryDataAsset.h"

FPrimaryAssetId UTestPrimaryDataAsset::GetPrimaryAssetId() const
{
    FPrimaryAssetType PrimaryAssetType(TEXT("Monster"));

    return FPrimaryAssetId(PrimaryAssetType, GetFName());
}
