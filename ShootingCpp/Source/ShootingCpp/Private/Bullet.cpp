// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>


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

