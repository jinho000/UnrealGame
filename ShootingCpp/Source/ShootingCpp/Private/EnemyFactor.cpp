// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactor.h"
#include "EnemyActor.h"

// Sets default values
AEnemyFactor::AEnemyFactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (delayTime < currentTime)
	{
		// 지정된 시간이 지나면 Enemy 생성
		// EnemyFactory위치에서 Enemy 생성
		AEnemyActor* spawnActor = GetWorld()->SpawnActor<AEnemyActor>(enemy, GetActorLocation(), GetActorRotation());

		if (spawnActor != nullptr)
		{
			FVector testV = spawnActor->GetActorLocation();
			testV = spawnActor->GetActorLocation();
			testV = spawnActor->GetActorForwardVector();
		}

		currentTime = 0.f;
	}
	else
	{
		currentTime += DeltaTime;
	}
}

