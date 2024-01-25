#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MyFirstActor.generated.h"

UCLASS()
class ASSIGNMENT01_API AMyFirstActor : public AActor
{
	GENERATED_BODY()

private:
	//Static Mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* static_mesh;
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
