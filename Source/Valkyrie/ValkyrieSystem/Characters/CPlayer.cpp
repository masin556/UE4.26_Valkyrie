#include "ValkyrieSystem/Characters/CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "ValkyrieSystem/Components/CStatusComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

ACPlayer::ACPlayer()
{
 	PrimaryActorTick.bCanEverTick = true;

	//Character Camera
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	//Components
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//SkeletalMesh'/Game/CharacterSystems/Player_Enemy/Player/Man/Meshes/Separates/Heads/SK_Head.SK_Head'

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/CharacterSystems/Player_Enemy/Player/Man/Meshes/Separates/Heads/SK_Head.SK_Head'");
	GetMesh()->SetSkeletalMesh(mesh);

	//Animation BP
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/CharacterSystems/Animations/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);


	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
}


void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Status->DisableControlRotation();
	Status->SetSpeed(ESpeedType::Run);
}


void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis with Key Moves
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);


	//PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	//PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);
}

//////////////////////////////////////////////////////////////////////////
void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	if (Status->GetTopViewCamera())
		direction = FVector::ForwardVector;

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	if (Status->GetTopViewCamera())
		direction = FVector::RightVector;

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	CheckTrue(Status->GetFixedCamera());

	AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	CheckTrue(Status->GetFixedCamera());

	AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

/////////////////////////////////////////////////////////////////////////