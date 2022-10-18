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
	// 충돌 이벤트 발생시 호출할 함수
	// 충돌한 대상을 매개변수로 넘겨줌
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);



public:
	// 플레이어가 가질 박스 충돌체 컴포넌트
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxRootComponent;

	// 플레이어의 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	// 플레이어를 추적할 확률 지정
	UPROPERTY(EditAnywhere)
	float traceRate = 0.5f;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 400.f;


private:
	FVector direction;
};
