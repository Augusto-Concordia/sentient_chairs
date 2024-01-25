// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstCharacter.h"

#include "Camera/CameraComponent.h"

// Sets default values
AMyFirstCharacter::AMyFirstCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFirstCharacterCamera"));

	// when attaching a component to another before it's been registered with Unreal, we call SetupAttachment instead of AttachToComponent
	camera->SetupAttachment(RootComponent);
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
}

// Called when the game starts or when spawned
void AMyFirstCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyFirstCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyFirstCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

