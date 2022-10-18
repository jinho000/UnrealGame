
#include "ShootingGameModebase.h"
#include <Blueprint/UserWidget.h>
#include <Components/TextBlock.h>
#include "MainWidget.h"
#include "MeneWidget.h"

void AShootingGameModebase::BeginPlay()
{
	// 상위 클래스의 함수 호출
	Super::BeginPlay();


	if (mainWidget != nullptr)
	{
		// 메인 위젯 생성
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

		// 메인 위젯이 생성되면 뷰포트에 추가한다
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
		// UI의 점수데이터 텍스트 설정
		// 정수형 점수를 FText자료형으로 변환 후 설정해야함
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
