#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk = 0, Run, Sprint, Max,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALKYRIE_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()


//주요 float character status 타입 및 이동
private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 400, 600, 800 };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Stamina")
		float MaxStamina = 100;

//키 입력
public:
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESpeedType::Sprint]; }

	FORCEINLINE bool CanMove() { return bCanMove; }
	FORCEINLINE void SetMove() { bCanMove = true; }
	FORCEINLINE void SetStop() { bCanMove = false; }

	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

	FORCEINLINE bool GetTopViewCamera() { return bTopViewCamera; }
	FORCEINLINE void EnableTopViewCamera() { bTopViewCamera = true; }
	FORCEINLINE void DisableTopViewCamera() { bTopViewCamera = false; }


//데미지, 스피드, ControllerFix
public:	
	UCStatusComponent();

	void SetSpeed(ESpeedType InType);
	void Damage(float InAmount);

	void EnableControlRotation();
	void DisableControlRotation();


protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;

private:
	bool bCanMove = true;
	float Health;
	float Stamina;

	bool bFixedCamera;
	bool bTopViewCamera;

		
};
