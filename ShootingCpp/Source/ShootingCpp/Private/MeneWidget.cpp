// Fill out your copyright notice in the Description page of Project Settings.


#include "MeneWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UMeneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼클릭 이벤트에 대응하는 함수 연결
	buttonRestart->OnClicked.AddDynamic(this, &UMeneWidget::Restart);
	buttonQuit->OnClicked.AddDynamic(this, &UMeneWidget::Quit);
}

void UMeneWidget::Restart()
{
	// 레벨을 다시 로드
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UMeneWidget::Quit()
{
	// 앱 종료 처리
	UWorld* pCurrentWorld = GetWorld();
	UKismetSystemLibrary::QuitGame(pCurrentWorld, pCurrentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
