// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputCharacter.generated.h"

UCLASS()
class PROJECTLAB67_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//~ Begin AInputCharacter interface
	/**
	* Default constructor
	*/
	AInputCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Action;

	/**
	 * Handle the input action triggered by pressing the space bar.
	 */
	void InputAction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Setup player input component
	* @param PlayerInputComponent The player input component to set up
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
