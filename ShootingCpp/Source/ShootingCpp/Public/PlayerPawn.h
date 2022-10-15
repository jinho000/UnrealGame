// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 플레이어가 가질 박스 충돌체 컴포넌트
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxRootComponent;

	// 플레이어의 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	// 총알을 발사할 위치를 지정하는 애로우 컴포넌트
	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;

	// 생성할 총알 블루프린트 클래스 파일
	// 이 변수를 통해 설정한 블루프린트 클래스의 객체가 생성됨
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;


	// 속력변수
	UPROPERTY(EditAnywhere)
	float moveSpeed = 500.f;

	// 총알 효과음
	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;

private:
	// 사용자의 키입력을 받을 변수
	float horizon;
	float vertical;

	// 사용자 입력 처리함수
	void MoveHorizontal(float value);
	void MoveVertical(float value);
	void Fire();
};
