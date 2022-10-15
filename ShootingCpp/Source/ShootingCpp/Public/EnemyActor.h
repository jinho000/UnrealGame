// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �÷��̾ ���� �ڽ� �浹ü ������Ʈ
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxRootComponent;

	// �÷��̾��� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	// �÷��̾ ������ Ȯ�� ����
	UPROPERTY(EditAnywhere)
	float traceRate = 0.5f;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 400.f;

private:
	FVector direction;
};
