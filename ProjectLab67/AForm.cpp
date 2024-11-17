// Fill out your copyright notice in the Description page of Project Settings.


#include "AForm.h"

// Sets default values
AAForm::AAForm()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    m_pCylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
    m_pProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    SetRootComponent(m_pProceduralMesh);
    m_pCylinderMesh->AttachToComponent(m_pProceduralMesh, FAttachmentTransformRules::KeepRelativeTransform);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (CylinderMeshAsset.Succeeded())
    {
        m_pCylinderMesh->SetStaticMesh(CylinderMeshAsset.Object);
    }
    
}

// Called when the game starts or when spawned
void AAForm::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAForm::CreateForm(FVector location, float innerCylinderD, float outerCylinderD, float cylinderH, float cylindersDelta)
{
    m_pProceduralMesh->SetRelativeLocation(FVector(location.X, location.Y, location.Z + (cylinderH / 2)));
    m_pProceduralMesh->SetWorldScale3D(m_pCylinderMesh->GetComponentScale());
    m_pCylinderMesh->SetRelativeScale3D(FVector(innerCylinderD / 100.f, innerCylinderD / 100.f, cylinderH / 100.f));
    m_pCylinderMesh->SetRelativeLocation(FVector(0.f, 0.f,  cylindersDelta));


    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;

    float AngleStep = 2 * PI / SegmentCount;

    for (int32 i = 0; i < SegmentCount; i++)
    {
        float CurrentAngle = i * AngleStep;
        float NextAngle = (i + 1) * AngleStep;

        FVector TopVertex1((outerCylinderD / 2) * FMath::Cos(CurrentAngle), (outerCylinderD / 2) * FMath::Sin(CurrentAngle), cylinderH / 2);
        FVector TopVertex2((outerCylinderD / 2) * FMath::Cos(NextAngle), (outerCylinderD / 2) * FMath::Sin(NextAngle), cylinderH / 2);
        FVector BottomVertex1((outerCylinderD / 2) * FMath::Cos(CurrentAngle), (outerCylinderD / 2) * FMath::Sin(CurrentAngle), -cylinderH / 2);
        FVector BottomVertex2((outerCylinderD / 2) * FMath::Cos(NextAngle), (outerCylinderD / 2) * FMath::Sin(NextAngle), -cylinderH / 2);

        Vertices.Add(TopVertex1);
        Vertices.Add(TopVertex2);
        Vertices.Add(BottomVertex1);
        Vertices.Add(BottomVertex2);

        int32 VertIndex = i * 4;

        // Top face
        //Triangles.Add(VertIndex);
        //Triangles.Add(VertIndex + 1);
        //Triangles.Add(VertIndex + 2);

        // Bottom face
        //Triangles.Add(VertIndex + 2);
        //Triangles.Add(VertIndex + 1);
        //Triangles.Add(VertIndex + 3);

        // Side face 1
        Triangles.Add(VertIndex);
        Triangles.Add(VertIndex + 2);
        Triangles.Add(VertIndex + 3);

        // Side face 2
        Triangles.Add(VertIndex);
        Triangles.Add(VertIndex + 3);
        Triangles.Add(VertIndex + 1);

        FVector Normal1 = TopVertex1.GetSafeNormal();
        FVector Normal2 = TopVertex2.GetSafeNormal();
        Normals.Add(Normal1);
        Normals.Add(Normal2);
        Normals.Add(Normal1);
        Normals.Add(Normal2);

        UVs.Add(FVector2D(i / (float)SegmentCount, 0));
        UVs.Add(FVector2D((i + 1) / (float)SegmentCount, 0));
        UVs.Add(FVector2D(i / (float)SegmentCount, 1));
        UVs.Add(FVector2D((i + 1) / (float)SegmentCount, 1));

        FVector Tangent = FVector::CrossProduct(Normal1, FVector(0, 0, 1)).GetSafeNormal();
        Tangents.Add(FProcMeshTangent(Tangent, false));
        Tangents.Add(FProcMeshTangent(Tangent, false));
        Tangents.Add(FProcMeshTangent(Tangent, false));
        Tangents.Add(FProcMeshTangent(Tangent, false));
    }

    m_pProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, true);

    m_pProceduralMesh->ContainsPhysicsTriMeshData(true);
}

UStaticMeshComponent* AAForm::GetCylinderMesh()
{
    return m_pCylinderMesh;
}

UProceduralMeshComponent* AAForm::GetProceduralMesh()
{
    return m_pProceduralMesh;
}

// Called every frame
void AAForm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

