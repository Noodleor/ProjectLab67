// Fill out your copyright notice in the Description page of Project Settings.


#include "AInitialization.h"

// Sets default values
AAInitialization::AAInitialization()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pInitSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(m_pInitSceneComponent);

	m_sphereDiameter = 100.f;
	m_sphereDiameterTolerance = 50.f;
	m_innerCylinderD = 500.f;
	m_outerCylinderD = 1000.f;
	m_cylinderH = 1000.f;
	m_cylindersDelta = 250.f;

}

// Called when the game starts or when spawned
void AAInitialization::BeginPlay()
{
	Super::BeginPlay();
	
	const auto world = GetWorld();

	FTransform cloudSpawnTransform;
	cloudSpawnTransform.SetLocation(m_pInitSceneComponent->GetComponentLocation());
	cloudSpawnTransform.SetRotation(m_pInitSceneComponent->GetComponentRotation().Quaternion());

	AACloud* m_pCloud = world->SpawnActor<AACloud>(AACloud::StaticClass(), cloudSpawnTransform);
	m_pCloud->CreateCloud(m_sphereDiameter, m_sphereDiameterTolerance, m_outerCylinderD / 2, m_innerCylinderD / 2);

	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), cloudSpawnTransform.GetLocation().X, cloudSpawnTransform.GetLocation().Y, cloudSpawnTransform.GetLocation().Z);

	FTransform formSpawnTransform;
	formSpawnTransform.SetLocation(m_pInitSceneComponent->GetComponentLocation());
	formSpawnTransform.SetRotation(m_pInitSceneComponent->GetComponentRotation().Quaternion());

	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), formSpawnTransform.GetLocation().X, formSpawnTransform.GetLocation().Y, formSpawnTransform.GetLocation().Z);

	AAForm* m_pForm = world->SpawnActor<AAForm>(AAForm::StaticClass(), formSpawnTransform);
	m_pForm->CreateForm(GetActorLocation(), m_innerCylinderD, m_outerCylinderD, m_cylinderH, m_cylindersDelta);
	
}

float AAInitialization::GetInnerCylinderD()
{
	return m_innerCylinderD;
}

float AAInitialization::GetOuterCylinderD()
{
	return m_outerCylinderD;
}

float AAInitialization::GetCylinderH()
{
	return m_cylinderH;
}

// Called every frame
void AAInitialization::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

