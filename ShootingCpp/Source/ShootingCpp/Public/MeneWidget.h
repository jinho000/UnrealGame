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
	// ����� ��ư
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonRestart;


	// ���� ��ư
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonQuit;

};
