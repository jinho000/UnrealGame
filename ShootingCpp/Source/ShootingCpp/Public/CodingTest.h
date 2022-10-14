// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTest.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTest : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 number1 = 10;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	int32 number2 = 20;

	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultOnly = 20;
	
	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnly = 20;

	UPROPERTY(EditDefaultsOnly)
	FString unrealString = TEXT("한글 테스트");
	
public:	
	// Sets default values for this actor's properties
	ACodingTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	int32 Add(int32 num1, int32 num2);


};
