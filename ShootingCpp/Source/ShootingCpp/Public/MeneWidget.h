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

protected:
	// navive construct ������ �Լ��� �̿��� ��ư Ŭ���� ȣ���Լ��� ����
	virtual void NativeConstruct() override;

private: 
	
	// ��ư Ŭ���� �Լ� ó��
	// ��ư Ŭ���� �Լ��� ��������Ʈ�� �����ؾ��ϹǷ� UFUNCTIONŰ���� ����
	
	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();
};
