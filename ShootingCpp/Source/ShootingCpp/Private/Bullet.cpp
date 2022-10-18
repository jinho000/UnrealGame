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

	// �ڽ� �ݶ��̴� ������Ʈ ����
	// ������ �ڽ� ������Ʈ�� �̸� ����
	// ���� �� �ڽ��� �ݶ��̴��� ũ�Ⱚ�� ũ�� �������� �������ش�
	boxComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");
	boxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	boxComponent->SetWorldScale3D(FVector(0.75f, 0.25f, 1.f));
	
	// �浹ó�� �ɼ��� �̸� ������ ���������� ����
	boxComponent->SetCollisionProfileName(L"Bullet");

	// �ڽ� ������Ʈ�� BeginOverlap ��������Ʈ�� �Լ� ����
	// �ڽ� ������Ʈ �浹 ������ �̺�Ʈ�� OnbulletOverlap �Լ��� ����
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);

	// ��Ʈ ������Ʈ�� ����
	SetRootComponent(boxComponent);

	// meshComponent ����
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

	// �Ѿ��� �����Ǹ� ������ ������ ó��
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);

}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyActor* pEnemy = Cast<AEnemyActor>(OtherActor);
	
	if (pEnemy != nullptr)
	{
		// ����ó��
		AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
		AShootingGameModebase* currentGameModeBase = Cast<AShootingGameModebase>(currentMode);
		if (currentGameModeBase != nullptr)
		{
			currentGameModeBase->AddScore(1);
		}

		// ���� ����Ʈ ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		// �浹�� ����� Enemy�ΰ�� Enemy ����
		OtherActor->Destroy();
	}

	// �浹 �� �Ѿ� ����
	Destroy();
}

