// Fill out your copyright notice in the Description page of Project Settings.


#include "AGranule.h"

// Sets default values
AAGranule::AAGranule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pISMComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(m_pISMComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		m_pISMComponent->SetStaticMesh(SphereVisualAsset.Object);
	}
}

// Called when the game starts or when spawned
void AAGranule::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAGranule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

