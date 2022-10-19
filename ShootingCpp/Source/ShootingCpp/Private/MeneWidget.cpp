// Fill out your copyright notice in the Description page of Project Settings.


#include "MeneWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UMeneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ưŬ�� �̺�Ʈ�� �����ϴ� �Լ� ����
	buttonRestart->OnClicked.AddDynamic(this, &UMeneWidget::Restart);
	buttonQuit->OnClicked.AddDynamic(this, &UMeneWidget::Quit);
}

void UMeneWidget::Restart()
{
	// ������ �ٽ� �ε�
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UMeneWidget::Quit()
{
	// �� ���� ó��
	UWorld* pCurrentWorld = GetWorld();
	UKismetSystemLibrary::QuitGame(pCurrentWorld, pCurrentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
