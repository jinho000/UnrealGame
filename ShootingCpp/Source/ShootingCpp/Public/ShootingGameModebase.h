// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModebase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModebase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// 위젯을 생성하기위한 변수
	// 블루프린트에서 생성할 위젯 블루프린트를 넣어준다
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	// 게임종료메뉴를 생성하기 위한 변수
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMeneWidget> menuWidget;


protected:
	// 시작시 위젯 생성
	virtual void BeginPlay() override;

public:
	void PrintScore();
	void AddScore(int32 point);
	void ShowMenu();

private:
	int32 currentScore = 0;

	// 현재 생성된 메인 위젯 변수
	class UMainWidget* mainUI;

	// 메뉴 위젯 변수
	class UMeneWidget* menuUI;
};
