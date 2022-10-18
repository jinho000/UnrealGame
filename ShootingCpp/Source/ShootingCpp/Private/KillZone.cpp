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

	// 루트 컴포넌트를 박스 컴포넌트로 설정
	SetRootComponent(boxRootComponent);

	// 박스 컴포넌트의 모빌리티를 고정상태로 설정
	boxRootComponent->SetMobility(EComponentMobility::Static);

	// 박스 컴포넌트 크기 설정
	boxRootComponent->SetBoxExtent(FVector(50.f, 2000.f, 50.f));

	// 박스 컴포넌트 충돌체 채널 설정
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

