// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AForm.generated.h"

UCLASS()
class PROJECTLAB67_API AAForm : public AActor
{
	GENERATED_BODY()
	
public:	
	//~ Begin AAFrom interface
	/**
	* Default constructor
	*/
	AAForm();

	/**
	 * Create a form
	 * @param location The location to create the form
	 * @param innerCylinderD Inner cylinder diameter
	 * @param outerCylinderD Outer cylinder diameter
	 * @param cylinderH Cylinder height
	 * @param cylindersDelta Difference in cylinder height
	 */
	void CreateForm(FVector location, float innerCylinderD, float outerCylinderD, float cylinderH, float cylindersDelta);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_pCylinderMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProceduralMeshComponent* m_pProceduralMesh;

	UPROPERTY(EditAnywhere, Category = "Procedural Cylinder")
	int32 SegmentCount = 32;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	*  Get the cylinder mesh component
	* @return Cylinder mesh component
	*/
	UStaticMeshComponent* GetCylinderMesh();

	/**
	* Get the procedural mesh component
	* @return Procedural mesh component
	*/
	UProceduralMeshComponent* GetProceduralMesh();

};
