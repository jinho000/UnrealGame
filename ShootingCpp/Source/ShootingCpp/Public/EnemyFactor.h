// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	float delayTime = 2.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemy;

private:
	float currentTime = 0.f;

};
