// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

// Sets default values
AMyFirstActor::AMyFirstActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyFirstActorStaticMesh"));
	check(static_mesh);

	static_mesh->SetSimulatePhysics(true);

	// we're telling the engine that this is the base component (so get all of its transform data from the mesh) of the actor
	// (Unity doesn't really have this, as it's all GameObjects and all GameOjects have a Transform component)
	RootComponent = static_mesh;

	// this creates a single instance of the mesh asset finder to use for all instances of this class
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair"));

	if (!MeshAsset.Succeeded())
	{
		if (GEngine != nullptr)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to load mesh asset!"));

		return;
	}

	static_mesh->SetStaticMesh(MeshAsset.Object);

	if (GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Loaded mesh asset!"));
}

// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

