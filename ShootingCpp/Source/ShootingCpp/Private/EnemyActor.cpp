// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <EngineUtils.h>

#include "PlayerPawn.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ڽ� �ݶ��̴� ������Ʈ ����
	{
		// ������ �ڽ� ������Ʈ�� �̸� ����
		boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");

		// ��Ʈ ������Ʈ�� �ڽ� ������Ʈ�� ����
		SetRootComponent(boxRootComponent);

		// �ڽ� ������Ʈ�� ũ�� ����
		FVector boxSize = FVector(50.f, 50.f, 50.f);
		boxRootComponent->SetBoxExtent(boxSize);
	}

	// meshComponent ����
	{
		meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMeshComp");

		// �ڽ�������Ʈ�� �ڽ� ������Ʈ�� ����
		meshComponent->SetupAttachment(boxRootComponent);
	}
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Ȯ�� ��÷
	float drawResult = FMath::RandRange(0.f, 1.f);
	if (drawResult <= traceRate)
	{
		// ��÷�� ������� ������ Ȯ���� ���°��
		// �÷��̾� ��ġ�� ���� ����
		// ���� ����� ��ġ�� �÷��̾� ���͸� ã�ƾ���
		
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains(L"BP_PlayerPawn"))
			{
				// �÷��̾���ġ - enemy ��ġ
				direction = player->GetActorLocation() - GetActorLocation();
				direction.Normalize();
			}
		}
	}
	else
	{
		// Ȯ���� ������ ������� ���� ���� ����
		direction = GetActorForwardVector();
	}
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������ �������� �̵�
	FVector newLocation = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);

}

