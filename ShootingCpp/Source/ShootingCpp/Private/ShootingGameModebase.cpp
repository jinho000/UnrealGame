
#include "ShootingGameModebase.h"
#include <Blueprint/UserWidget.h>
#include <Components/TextBlock.h>
#include "MainWidget.h"
#include "MeneWidget.h"

void AShootingGameModebase::BeginPlay()
{
	// ���� Ŭ������ �Լ� ȣ��
	Super::BeginPlay();


	if (mainWidget != nullptr)
	{
		// ���� ���� ����
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

		// ���� ������ �����Ǹ� ����Ʈ�� �߰��Ѵ�
		if (mainUI != nullptr)
		{
			mainUI->AddToViewport();
		}
	}
}

void AShootingGameModebase::PrintScore()
{
	if (mainUI != nullptr)
	{
		// UI�� ���������� �ؽ�Ʈ ����
		// ������ ������ FText�ڷ������� ��ȯ �� �����ؾ���
		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}
}

void AShootingGameModebase::AddScore(int32 point)
{
	currentScore += point;
	PrintScore();
}

void AShootingGameModebase::ShowMenu()
{
	if (menuWidget != nullptr)
	{
		menuUI = CreateWidget<UMeneWidget>(GetWorld(), menuWidget);

		if (menuUI != nullptr)
		{
			menuUI->AddToViewport();
		}
	}
}
