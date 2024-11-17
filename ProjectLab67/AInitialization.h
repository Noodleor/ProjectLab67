// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACloud.h"
#include "AForm.h"
#include "AInitialization.generated.h"

UCLASS()
class PROJECTLAB67_API AAInitialization : public AActor
{
	GENERATED_BODY()
	
public:	
	//~ Begin AAInitialization interface
	/**
	* Default constructor
	*/
	AAInitialization();

	UPROPERTY(EditAnywhere)
	USceneComponent* m_pInitSceneComponent;

	UPROPERTY(EditAnywhere)
	float m_sphereDiameter;

	UPROPERTY(EditAnywhere)
	float m_sphereDiameterTolerance;

	UPROPERTY(EditAnywhere)
	float m_innerCylinderD;

	UPROPERTY(EditAnywhere)
	float m_outerCylinderD;

	UPROPERTY(EditAnywhere)
	float m_cylinderH;

	UPROPERTY(EditAnywhere)
	float m_cylindersDelta;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Get the inner cylinder diameter
	* @return Inner cylinder diameter
	*/
	float GetInnerCylinderD();

	/**
	* Get the outer cylinder diameter
	* @return Outer cylinder diameter
	*/
	float GetOuterCylinderD();

	/**
	* Get the inner cylinder height
	* @return Inner cylinder height
	*/
	float GetCylinderH();
};
