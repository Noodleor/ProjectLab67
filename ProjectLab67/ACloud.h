// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACloud.generated.h"

UCLASS()
class PROJECTLAB67_API AACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	//~ Begin AACloud interface
	/**
	* Default constructor
	*/
	AACloud();

	UPROPERTY(EditAnywhere)
	USceneComponent* m_pCloudSceneComponent;

	/**
	 * Create a cloud with granules
	 * @param granuleDiameter Diameter of the granules
	 * @param granuleDiameterTolerance Tolerance for granule diameter
	 * @param outerCloudLimit Outer limit of the cloud
	 * @param innerCloudLimit Inner limit of the cloud
	 */
	void CreateCloud(float granuleDiameter, float granuleDiameterTolerance, float outerCloudLimit, float innerCloudLimit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float m_GranuleDiameter;

	float m_GranuleDiameterTolerance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<UStaticMeshComponent*> m_pGranuleMeshComponents;

	/**
	* Get the granules mesh components
	* @return Pointer to array granules mesh components
	*/
	TArray<UStaticMeshComponent*>& GetGranuleMeshComponents();

};
