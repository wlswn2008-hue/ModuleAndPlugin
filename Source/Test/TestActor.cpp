#include "TestActor.h"
#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	// 1) 출력 로그(Output Log) 확인용
	UE_LOG(LogTemp, Warning, TEXT("[TestActor] BeginPlay 호출됨 - Test 모듈이 정상적으로 동작 중입니다."));

	// 2) 게임 화면(Viewport)에서 직접 확인용
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,            // Key (-1: 새 메시지로 추가)
			5.0f,          // 화면에 표시될 시간(초)
			FColor::Green,
			TEXT("TestActor::BeginPlay - Test 모듈 동작 확인!")
		);
	}
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
