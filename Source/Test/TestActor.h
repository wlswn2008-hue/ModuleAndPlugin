#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

/**
 * Test 모듈에 속한 액터.
 * 다른 모듈(주 게임 모듈)에서 SpawnActor로 생성해 모듈 간 상호작용을 확인하는 용도.
 */
UCLASS()
class TEST_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	ATestActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
