// Fill out your copyright notice in the Description page of Project Settings.


#include "ACloud.h"
#include "AGranule.h"
#include "AInitialization.h"
#include "Engine/Engine.h"

// Sets default values
AACloud::AACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pCloudSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(m_pCloudSceneComponent);
}

void AACloud::CreateCloud(float granuleDiameter, float granuleDiameterTolerance, float outerCloudLimit, float innerCloudLimit)
{
    m_GranuleDiameter = granuleDiameter;
    m_GranuleDiameterTolerance = granuleDiameterTolerance;

    auto granule = GetWorld()->SpawnActor<AAGranule>();

    float angle = 0.f;

    float zGranuleLocation = granuleDiameter + granuleDiameterTolerance;

    for (int instanceNum = 0; instanceNum < 500; instanceNum++, angle+= ((granuleDiameter + granuleDiameterTolerance) / 5) )
    {
        float radius = FMath::RandRange(innerCloudLimit + (granuleDiameter + granuleDiameterTolerance), outerCloudLimit - (granuleDiameter + granuleDiameterTolerance));

        float xGranuleLocation = radius * FMath::Cos(FMath::DegreesToRadians(angle));
        float yGranuleLocation = radius * FMath::Sin(FMath::DegreesToRadians(angle));

        zGranuleLocation += ((granuleDiameter + granuleDiameterTolerance) / 5);

        FVector granuleLocation = GetActorLocation() + FVector(xGranuleLocation, yGranuleLocation, zGranuleLocation);
        FTransform transform = FTransform(FRotator(FRotator::ZeroRotator), granuleLocation, FVector((granuleDiameter / 100.f) + FMath::RandRange(0.0f, granuleDiameterTolerance) / 100.f) );

        UStaticMeshComponent* pstaticMeshComponent = NewObject<UStaticMeshComponent>(this);
        if (pstaticMeshComponent)
        {
            pstaticMeshComponent->SetStaticMesh(granule->m_pISMComponent->GetStaticMesh());
            pstaticMeshComponent->SetWorldTransform(transform);
            pstaticMeshComponent->SetSimulatePhysics(true);
            pstaticMeshComponent->RegisterComponent();
            pstaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
            m_pGranuleMeshComponents.Add(pstaticMeshComponent);
        }
    }
}

TArray<UStaticMeshComponent*>& AACloud::GetGranuleMeshComponents()
{
    return m_pGranuleMeshComponents;
}

// Called when the game starts or when spawned
void AACloud::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

