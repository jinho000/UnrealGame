// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeneWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMeneWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 재시작 버튼
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonRestart;


	// 종료 버튼
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonQuit;

};
