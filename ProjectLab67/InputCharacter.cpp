// Fill out your copyright notice in the Description page of Project Settings.


#include "InputCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AInitialization.h"
#include "ACloud.h"
#include "AForm.h"


// Sets default values
AInputCharacter::AInputCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(Action, ETriggerEvent::Triggered, this, &AInputCharacter::InputAction);
	}
}

void AInputCharacter::InputAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Space Bar pressed");

	FVector formLocation;
	float outerD;
	float innerD;
	float height;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAInitialization::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			AAInitialization* InitializationActor = Cast<AAInitialization>(Actor);
			if (InitializationActor)
			{
				formLocation = InitializationActor->GetActorLocation();
				outerD = InitializationActor->GetOuterCylinderD();
				innerD = InitializationActor->GetInnerCylinderD();
				height = InitializationActor->GetCylinderH();
			}
		}
	}
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AACloud::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			AACloud* CloudActor = Cast<AACloud>(Actor);
			if (CloudActor)
			{
				TArray<UStaticMeshComponent*>& MeshComponents = CloudActor->GetGranuleMeshComponents();

				for (UStaticMeshComponent* MeshComponent : MeshComponents)
				{
					if (MeshComponent)
					{
						MeshComponent->SetSimulatePhysics(false);

						FVector granuleLocation = MeshComponent->GetComponentLocation();

						if (FVector::DistXY(formLocation, granuleLocation) > (outerD / 2) || FVector::DistXY(formLocation, granuleLocation) < (innerD / 2) ||
							FMath::Abs(granuleLocation.Z - formLocation.Z) > (height))	
						{
							MeshComponent->DestroyComponent();
						}

					}
				}
			}
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAForm::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}
}

