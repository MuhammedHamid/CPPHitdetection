// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Character.h"

#include <string>

// Sets default values
ACPP_Character::ACPP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(0,-90,0));
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}


// Called when the game starts or when spawned
void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	// PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// PlayerInputComponent->BindAxis("MoveForward", this, &ACPP_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPP_Character::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released , this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("MoveFaster",IE_Pressed, this, &ACPP_Character::MoveFaster);
	PlayerInputComponent->BindAction("MoveFaster",IE_Released, this, &ACPP_Character::MoveSlower);

	PlayerInputComponent->BindAction("Punch", IE_Pressed,this, &ACPP_Character::Punch);
	PlayerInputComponent->BindAction("Kick", IE_Pressed,this, &ACPP_Character::Kick);
}




void ACPP_Character::MoveForward(float axis)
{
	const FRotator control_rotation = Controller->GetControlRotation();
	const FRotator control_rotation_yawOnly = FRotator(0, control_rotation.Yaw, 0);
	const FVector fwd = FRotationMatrix(control_rotation_yawOnly).GetUnitAxis(EAxis::X);

	AddMovementInput(fwd, axis);
}

void ACPP_Character::MoveRight(float axis)
{

	// const FRotator control_rotation = Controller->GetControlRotation();
	// const FRotator control_rotation_yawOnly = FRotator(0, control_rotation.Yaw, 0);
	// const FVector right = FRotationMatrix(control_rotation_yawOnly).GetUnitAxis(EAxis::Y);

	AddMovementInput(GetActorForwardVector(), axis);
}

void ACPP_Character::MoveFaster()
{
		GetCharacterMovement()->MaxWalkSpeed = 150;
}

void ACPP_Character::MoveSlower()
{
		GetCharacterMovement()->MaxWalkSpeed = 75;
}

void ACPP_Character::Punch()
{
	if (M_punch)
	{
		PlayAnimMontage(M_punch,1,NAME_None);
	}
}

void ACPP_Character::Kick()
{
	if (M_kick)
	{
		PlayAnimMontage(M_kick,1,NAME_None);
	}
}

void ACPP_Character::PunchReact()
{
	PlayAnimMontage(M_punchReact,1,NAME_None);
}


// fight interface functions

void ACPP_Character::CheckPunch_Implementation(bool is_leftHand)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("checking punch"));

	FVector handLocation;
	if (is_leftHand)
	{
		handLocation = GetMesh()->GetBoneLocation("hand_l",EBoneSpaces::WorldSpace);
	}else
	{
		handLocation = GetMesh()->GetBoneLocation("hand_r",EBoneSpaces::WorldSpace);		
	}

	FName hitBone = opponent->GetClosestBone(handLocation,20);

	if (hitBone != "")
	{
		opponent->PunchReact();
	}

	
}

void ACPP_Character::CheckKick_Implementation(bool is_leftLeg)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("checking kick"));
}


FName ACPP_Character::GetClosestBone(FVector hitBonelocation, float maxDistance)
{
	TArray<FName> boneNames;
	GetMesh()->GetBoneNames(boneNames);

	FName closestBone;
	float minDist= 10000;
	
	for (int i = 0; i < boneNames.Num(); ++i)
	{		
		// GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Green, boneNames[i].ToString());
		FVector boneLocation =  GetMesh()->GetBoneLocation(boneNames[i],EBoneSpaces::WorldSpace);
		float tempDist = FVector::Dist(hitBonelocation,boneLocation);
		if (minDist> tempDist)
		{
			minDist = tempDist;
			closestBone = boneNames[i];
		}		
		
	}

	if (minDist<maxDistance)
	{		
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Green, closestBone.ToString());
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Green, FString::SanitizeFloat(minDist));
		return closestBone;
	}else
	{
		return "";
	}
	
}

// end of fight interface
