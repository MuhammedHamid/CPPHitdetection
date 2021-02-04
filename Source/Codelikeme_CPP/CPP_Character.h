// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "FightInterface.h"


#include "CPP_Character.generated.h"



UCLASS()
class CODELIKEME_CPP_API ACPP_Character : public ACharacter, public IFightInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* PlayerCamera;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
			UAnimMontage* M_punch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_kick;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_punchReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= SceneReferences)
		ACPP_Character* opponent; 
	
	void MoveForward(float axis);
	void MoveRight(float axis);
	void MoveFaster();
	void MoveSlower();
	void Punch();
	void Kick();
	void PunchReact();

	FName GetClosestBone(FVector hitBonelocation, float maxDistance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// fight interface functions
	//punch hit check
	void CheckPunch_Implementation( bool is_leftHand) override;

	void CheckKick_Implementation( bool is_leftLeg) override;
	// end of fight interface
};
