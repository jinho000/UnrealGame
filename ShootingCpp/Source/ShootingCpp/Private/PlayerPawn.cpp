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


	// �ڽ� �ݶ��̴� ������Ʈ ����
	{
		// ������ �ڽ� ������Ʈ�� �̸� ����
		boxRootComponent = CreateDefaultSubobject<UBoxComponent>(L"BoxComp");

		// ��Ʈ ������Ʈ�� �ڽ� ������Ʈ�� ����
		SetRootComponent(boxRootComponent);

		// �ڽ� ������Ʈ�� ũ�� ����
		FVector boxSize = FVector(50.f, 50.f, 50.f);
		boxRootComponent->SetBoxExtent(boxSize);

		// Collision
		{
			// ������ �̺�Ʈ�� �Ҵ�
			boxRootComponent->SetGenerateOverlapEvents(true);

			// �浹 ������ Query And Phsics�� ����
			boxRootComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// Object Type�� 1�� ä�η� ����
			// �𸮾󿡼� ������ ������� ä�ο� ������ 
			// ECC_GameTraceChannel1 -> Player
			// ECC_GameTraceChannel2 -> Enemy
			// ECC_GameTraceChannel3 -> Bullet
			boxRootComponent->SetCollisionObjectType(ECC_GameTraceChannel1);

			// ��� ä���� ������� ����
			boxRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

			// Enemy�� �浹�̺�Ʈ overlap, killzone���� block
			boxRootComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
			boxRootComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		}
	}

	// meshComponent ����
	{
		meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMeshComp");

		// �ڽ�������Ʈ�� �ڽ� ������Ʈ�� ����
		meshComponent->SetupAttachment(boxRootComponent);
	}

	// �ַο� ������Ʈ ����
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

	// �÷��̾��� �Է��� �޾� ��ġ�� ����
	
	// 1 �Էµ� ���� �̿��� ���⺤�͸� ����
	FVector direction = FVector(0, horizon, vertical);

	// 2 ���⺤�� ���� ����ȭ
	direction.Normalize();

	// 3 ���� ��ġ�� �ӵ�(���� * �ӷ�)�� ������ �ð����� ���� �� ���� �̵������ ���� ��ġ�� ���� ����
	FVector newLocation = GetActorLocation() + direction * moveSpeed * DeltaTime;
	
	// ���ŷ �����ϵ��� sweep ����
	SetActorLocation(newLocation, true);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PawnŬ������ ��ӹ޾����Ƿ� PlayerInputComponent ��밡��
	// PlayerInputComponent�� Ű �Է¿� ���� �����Լ��� ���ε��� �� �ִ� �Լ��� ����
	// ������Ʈ���� ������ Ű�Է¿� ���� ���� �Լ� ����(���ε�)
	// Ű �Է½� ������ ���� ���ε��� �Լ��� �Ѿ� ��
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
	// ���콺 Ŭ���� �Ѿ� ����
	// ������ ������Ʈ������ �������Ʈ ������ ����
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

	// �Ѿ� ȿ���� ����
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

