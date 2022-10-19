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

protected:
	// navive construct 생성자 함수를 이용해 버튼 클릭시 호출함수를 연결
	virtual void NativeConstruct() override;

private: 
	
	// 버튼 클릭시 함수 처리
	// 버튼 클릭시 함수를 델리게이트로 연결해야하므로 UFUNCTION키워드 설정
	
	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();
};
