// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTINGCPP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �浹 �̺�Ʈ �߻��� ȣ���� �Լ�
	// �浹�� ����� �Ű������� �Ѱ���
	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
						 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						 bool bFromSweep, const FHitResult& SweepResult);
		

public:
	// �÷��̾ ���� �ڽ� �浹ü ������Ʈ
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;

	// �÷��̾��� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	// �÷��̾��� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.f;

	// ���� ����Ʈ
	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;
};
