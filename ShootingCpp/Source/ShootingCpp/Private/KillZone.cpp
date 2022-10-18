// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include <Components/BoxComponent.h>

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// box collision component
	boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxCollider");

	// ��Ʈ ������Ʈ�� �ڽ� ������Ʈ�� ����
	SetRootComponent(boxRootComponent);

	// �ڽ� ������Ʈ�� �����Ƽ�� �������·� ����
	boxRootComponent->SetMobility(EComponentMobility::Static);

	// �ڽ� ������Ʈ ũ�� ����
	boxRootComponent->SetBoxExtent(FVector(50.f, 2000.f, 50.f));

	// �ڽ� ������Ʈ �浹ü ä�� ����
	boxRootComponent->SetCollisionProfileName(L"KillZone");

}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

