// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <EngineUtils.h>

#include "PlayerPawn.h"
#include "ShootingGameModebase.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ڽ� �ݶ��̴� ������Ʈ ����
	{
		// ������ �ڽ� ������Ʈ�� �̸� ����
		boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");

		// �ڽ� ������Ʈ�� ũ�� ����
		FVector boxSize = FVector(50.f, 50.f, 50.f);
		boxRootComponent->SetBoxExtent(boxSize);

		// �浹ó�� �ɼ��� �̸� ������ ���������� ����
		boxRootComponent->SetCollisionProfileName(L"Enemy");

		// �ڽ� ������Ʈ�� BeginOverlap ��������Ʈ�� �Լ� ����
		boxRootComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);

		// ��Ʈ ������Ʈ�� �ڽ� ������Ʈ�� ����
		SetRootComponent(boxRootComponent);
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

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* pPlayer = Cast<APlayerPawn>(OtherActor);
	if (pPlayer != nullptr)
	{
		// �ε��� ���Ͱ� �÷��̾��� ���
		OtherActor->Destroy();

		// ���� ���� ��带 ������ �Ͻ����� �� �޴� ����
		AShootingGameModebase* currentGameMode = Cast<AShootingGameModebase>(GetWorld()->GetAuthGameMode());
		if (currentGameMode != nullptr)
		{
			currentGameMode->ShowMenu();
		}
	}

	Destroy();
}

