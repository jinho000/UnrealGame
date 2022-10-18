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

	// 박스 콜라이더 컴포넌트 생성
	{
		// 생성시 박스 컴포넌트의 이름 설정
		boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");

		// 박스 컴포넌트의 크기 설정
		FVector boxSize = FVector(50.f, 50.f, 50.f);
		boxRootComponent->SetBoxExtent(boxSize);

		// 충돌처리 옵션을 미리 설정한 프리셋으로 설정
		boxRootComponent->SetCollisionProfileName(L"Enemy");

		// 박스 컴포넌트의 BeginOverlap 델리게이트에 함수 연결
		boxRootComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);

		// 루트 컴포넌트를 박스 컴포넌트로 설정
		SetRootComponent(boxRootComponent);
	}

	// meshComponent 생성
	{
		meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMeshComp");

		// 박스컴포넌트의 자식 컴포넌트로 설정
		meshComponent->SetupAttachment(boxRootComponent);
	}
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 확률 추첨
	float drawResult = FMath::RandRange(0.f, 1.f);
	if (drawResult <= traceRate)
	{
		// 추첨한 결과값이 설정한 확률에 들어온경우
		// 플레이어 위치로 방향 설정
		// 현재 월드상에 배치된 플레이어 액터를 찾아야함
		
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains(L"BP_PlayerPawn"))
			{
				// 플레이어위치 - enemy 위치
				direction = player->GetActorLocation() - GetActorLocation();
				direction.Normalize();
			}
		}
	}
	else
	{
		// 확률에 들어오지 않은경우 전방 방향 설정
		direction = GetActorForwardVector();
	}
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 지정된 방향으로 이동
	FVector newLocation = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);

}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* pPlayer = Cast<APlayerPawn>(OtherActor);
	if (pPlayer != nullptr)
	{
		// 부딪힌 액터가 플레이어인 경우
		OtherActor->Destroy();

		// 현재 게임 모드를 가져와 일시정지 후 메뉴 생성
		AShootingGameModebase* currentGameMode = Cast<AShootingGameModebase>(GetWorld()->GetAuthGameMode());
		if (currentGameMode != nullptr)
		{
			currentGameMode->ShowMenu();
		}
	}

	Destroy();
}

