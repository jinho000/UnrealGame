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
	// ������ �����ϱ����� ����
	// �������Ʈ���� ������ ���� �������Ʈ�� �־��ش�
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	// ��������޴��� �����ϱ� ���� ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMeneWidget> menuWidget;


protected:
	// ���۽� ���� ����
	virtual void BeginPlay() override;

public:
	void PrintScore();
	void AddScore(int32 point);
	void ShowMenu();

private:
	int32 currentScore = 0;

	// ���� ������ ���� ���� ����
	class UMainWidget* mainUI;

	// �޴� ���� ����
	class UMeneWidget* menuUI;
};
