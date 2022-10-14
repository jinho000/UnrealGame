// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingTest.h"

// Sets default values
ACodingTest::ACodingTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UE_LOG(LogTemp, Warning, L"Contructor");
}

// Called when the game starts or when spawned
void ACodingTest::BeginPlay()
{
	Super::BeginPlay();
	// 한글
	// 한글
	UE_LOG(LogTemp, Warning, TEXT("string test %d\n"), Add(number1, number2));
}

// Called every frame
void ACodingTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACodingTest::Add(int32 num1, int32 num2)
{
	return num1 + num2;
}

