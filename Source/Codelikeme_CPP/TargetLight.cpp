// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLight.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATargetLight::ATargetLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));

}

// Called when the game starts or when spawned
void ATargetLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATargetLight::LookAtTarget();
}

void ATargetLight::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
    ATargetLight::LookAtTarget();
}

void ATargetLight::LookAtTarget()
{
	if (IsValid(TargetActor))
	{
		this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(),TargetActor->GetActorLocation()));
		
	}
}

