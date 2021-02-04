// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"

#include "TargetLight.generated.h"

UCLASS()
class CODELIKEME_CPP_API ATargetLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetLight();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Light", meta=(ExposeFunctionCategories="SpotLight,Rendering|Lighting"))
	USpotLightComponent* SpotLightComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Actor")
	AActor* TargetActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
private:
	virtual void LookAtTarget();
	
	
};
