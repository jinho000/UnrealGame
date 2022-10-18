// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Bullet.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 박스 콜라이더 컴포넌트 생성
	{
		// 생성시 박스 컴포넌트의 이름 설정
		boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");

		// 루트 컴포넌트를 박스 컴포넌트로 설정
		SetRootComponent(boxRootComponent);

		// 박스 컴포넌트의 크기 설정
		FVector boxSize = FVector(50.f, 50.f, 50.f);
		boxRootComponent->SetBoxExtent(boxSize);

		// Collision
		{
			// 오버랩 이벤트를 켠다
			boxRootComponent->SetGenerateOverlapEvents(true);

			// 충돌 응답을 Query And Phsics로 설정
			boxRootComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// Object Type을 1번 채널로 설정
			// 언리얼에서 설정한 순서대로 채널에 배정됨 
			// ECC_GameTraceChannel1 -> Player
			// ECC_GameTraceChannel2 -> Enemy
			// ECC_GameTraceChannel3 -> Bullet
			boxRootComponent->SetCollisionObjectType(ECC_GameTraceChannel1);

			// 모든 채널을 응답없음 설정
			boxRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

			// Enemy와 충돌이벤트 overlap, killzone과는 block
			boxRootComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
			boxRootComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		}
	}

	// meshComponent 생성
	{
		meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMeshComp");

		// 박스컴포넌트의 자식 컴포넌트로 설정
		meshComponent->SetupAttachment(boxRootComponent);
	}

	// 애로우 컴포넌트 생성
	{
		firePosition = CreateDefaultSubobject<UArrowComponent>(L"ArrowComp");
		firePosition->SetupAttachment(boxRootComponent);
	}
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플레이어의 입력을 받아 위치값 세팅
	
	// 1 입력된 값을 이용해 방향벡터를 만듦
	FVector direction = FVector(0, horizon, vertical);

	// 2 방향벡터 길이 정규화
	direction.Normalize();

	// 3 현재 위치에 속도(방향 * 속력)에 보간된 시간값을 곱한 후 나온 이동결과를 현재 위치에 더해 세팅
	FVector newLocation = GetActorLocation() + direction * moveSpeed * DeltaTime;
	
	// 블로킹 가능하도록 sweep 설정
	SetActorLocation(newLocation, true);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Pawn클래스를 상속받았으므로 PlayerInputComponent 사용가능
	// PlayerInputComponent는 키 입력에 대한 매핑함수를 바인딩할 수 있는 함수를 제공
	// 프로젝트에서 설정한 키입력에 대한 매핑 함수 연결(바인딩)
	// 키 입력시 설정한 값이 바인딩한 함수로 넘어 옴
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::MoveVertical);

	PlayerInputComponent->BindAction("Fire", IE_Pressed,this, &APlayerPawn::Fire);
}

void APlayerPawn::MoveHorizontal(float value)
{
	horizon = value;
}

void APlayerPawn::MoveVertical(float value)
{
	vertical = value;
}

void APlayerPawn::Fire()
{
	// 마우스 클릭시 총알 생성
	// 생성할 오브젝트에대한 블루프린트 파일을 전달
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

	// 총알 효과음 실행
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

