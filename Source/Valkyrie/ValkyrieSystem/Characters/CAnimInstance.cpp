#include "ValkyrieSystem/Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	//Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	//if (!!Weapon)
		//Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();

	FRotator ownerRotation = UKismetMathLibrary::NormalizedDeltaRotator(OwnerCharacter->GetControlRotation(), OwnerCharacter->GetActorRotation());
	//Direction = CalculateDirection(OwnerCharacter->GetVelocity(), ownerRotation);
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());


	FRotator current = FRotator(Pitch, 0, 0);
	float pitch = UKismetMathLibrary::RInterpTo(current, ownerRotation, DeltaSeconds, 25).Pitch;
	Pitch = FMath::Clamp(pitch, -75.0f, +75.0f);
}
