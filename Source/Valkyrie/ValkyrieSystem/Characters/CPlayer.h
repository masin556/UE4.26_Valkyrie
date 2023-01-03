#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class VALKYRIE_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float HorizontalLook = 45;

	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float VerticalLook = 45;


//备炼 Component 
private:
	//UPROPERTY(VisibleDefaultsOnly)
	//	class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

//Character 郴何 Component 包府
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	//UPROPERTY(VisibleDefaultsOnly)
	//	class UCStateComponent* State;

	//UPROPERTY(VisibleDefaultsOnly)
	//	class UCZoomComponent* Zoom;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;



public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//Controller
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	
//Actions
//private:
//	void OnRun();
//	void OffRun();

//WeaponType
private:

};
