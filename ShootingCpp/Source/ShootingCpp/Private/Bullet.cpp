// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>

#include "EnemyActor.h"
#include "ShootingGameModebase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 박스 콜라이더 컴포넌트 생성
	// 생성시 박스 컴포넌트의 이름 설정
	// 생성 후 박스의 콜라이더의 크기값과 크기 비율값을 설정해준다
	boxComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");
	boxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	boxComponent->SetWorldScale3D(FVector(0.75f, 0.25f, 1.f));
	
	// 충돌처리 옵션을 미리 설정한 프리셋으로 설정
	boxComponent->SetCollisionProfileName(L"Bullet");

	// 박스 컴포넌트의 BeginOverlap 델리게이트에 함수 연결
	// 박스 컴포넌트 충돌 오버렙 이벤트에 OnbulletOverlap 함수를 연결
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);

	// 루트 컴포넌트로 설정
	SetRootComponent(boxComponent);

	// meshComponent 생성
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMeshComp");
	meshComponent->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 총알이 생성되면 앞으로 가도록 처리
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);

}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyActor* pEnemy = Cast<AEnemyActor>(OtherActor);
	
	if (pEnemy != nullptr)
	{
		// 점수처리
		AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
		AShootingGameModebase* currentGameModeBase = Cast<AShootingGameModebase>(currentMode);
		if (currentGameModeBase != nullptr)
		{
			currentGameModeBase->AddScore(1);
		}

		// 폭발 이펙트 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		// 충돌한 대상이 Enemy인경우 Enemy 삭제
		OtherActor->Destroy();
	}

	// 충돌 후 총알 삭제
	Destroy();
}

