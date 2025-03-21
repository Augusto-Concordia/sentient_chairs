// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyFirstCharacter::AMyFirstCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFirstCharacterCamera"));

	// when attaching a component to another before it's been registered with Unreal, we call SetupAttachment instead of AttachToComponent
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));

	// contrary to the default character, we don't have the below line, which is why we need to manually rotate the camera
	// to have pitch rotation follow the controller
	//FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyFirstCharacter::BeginPlay()
{
	Super::BeginPlay();

	// this gets the controller from the current actor (because any actor can have a controller, but it's not necessarily a player controller)
	const APlayerController* InstancePlayerController = Cast<APlayerController>(Controller);

	// the below line is used mainly to safeguard against multiplayer scenarios where this might not be the local player
	if (const ULocalPlayer* LocalPlayer = InstancePlayerController->GetLocalPlayer())
	{
		// gets the input subsystem for the local player (ECS-style)
		if(UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// adds the mapping context to the input subsystem, making sure it exists (safeguards against not assigning it in the editor)
			if (!Imc_Normal_Controls.IsNull())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Added MappingContext with LocalPlayer! ") + LocalPlayer->GetName());
				InputSystem->AddMappingContext(Imc_Normal_Controls.LoadSynchronous(), 0);
			}
		}
	}
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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetupPlayerInputComponent!"));

	// assigns the input component to the player controller to make it respond to input
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(Ia_Jump, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveJump);
	Input->BindAction(Ia_Move_ForwardBackward, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveFb);
	Input->BindAction(Ia_Move_LeftRight, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveLr);
	Input->BindAction(Ia_Look_UpDown, ETriggerEvent::Triggered, this, &AMyFirstCharacter::LookUd);
	Input->BindAction(Ia_Look_LeftRight, ETriggerEvent::Triggered, this, &AMyFirstCharacter::LookLr);
	Input->BindAction(Ia_TeleportForward, ETriggerEvent::Triggered, this, &AMyFirstCharacter::TeleportForward);
	Input->BindAction(Ia_TeleportRight, ETriggerEvent::Triggered, this, &AMyFirstCharacter::TeleportRight);
	Input->BindAction(Ia_TeleportUp, ETriggerEvent::Triggered, this, &AMyFirstCharacter::TeleportUp);
}

void AMyFirstCharacter::MoveJump(const FInputActionValue& Instance)
{
	Jump();

	static constexpr uint64 JumpLogKey = 1;
	GEngine->AddOnScreenDebugMessage(JumpLogKey, 2.5f, FColor::Green, TEXT("Jumped!"));
}

void AMyFirstCharacter::MoveFb(const FInputActionValue& Instance)
{
	const float MoveFbValue = Instance.Get<float>();
	AddMovementInput(GetActorForwardVector(), MoveFbValue);

	static constexpr uint64 MoveFbLogKey = 2;
	GEngine->AddOnScreenDebugMessage(MoveFbLogKey, 2.5f, FColor::Green, TEXT("Moved Forward/Backward! " + FString::SanitizeFloat(MoveFbValue)));
}

void AMyFirstCharacter::MoveLr(const FInputActionValue& Instance)
{
	const float MoveLrValue = Instance.Get<float>();
	AddMovementInput(GetActorRightVector(), MoveLrValue);

	static constexpr uint64 MoveLrLogKey = 3;
	GEngine->AddOnScreenDebugMessage(MoveLrLogKey, 2.5f, FColor::Green, TEXT("Moved Left/Right! " + FString::SanitizeFloat(MoveLrValue)));
}

void AMyFirstCharacter::LookUd(const FInputActionValue& Instance)
{
	const float LookUdValue = Instance.Get<float>();
	Camera->AddLocalRotation(FRotator(1.0f, 0.0f, 0.0f) * LookUdValue * VerticalLookSensitivity);

	static constexpr uint64 LookUdLogKey = 4;
	GEngine->AddOnScreenDebugMessage(LookUdLogKey, 2.5f, FColor::Green, TEXT("Looked Up/Down! " + FString::SanitizeFloat(LookUdValue)));
}

void AMyFirstCharacter::LookLr(const FInputActionValue& Instance)
{
	const float LookLrValue = Instance.Get<float>();
	AddControllerYawInput(LookLrValue * HorizontalLookSensitivity);

	static constexpr uint64 LookLrLogKey = 5;
	GEngine->AddOnScreenDebugMessage(LookLrLogKey, 2.5f, FColor::Green, TEXT("Looked Left/Right! " + FString::SanitizeFloat(LookLrValue)));
}

void AMyFirstCharacter::TeleportForward(const FInputActionValue& Instance)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * 100.0f);

	static constexpr uint64 LogKey = 6;
	GEngine->AddOnScreenDebugMessage(LogKey, 2.5f, FColor::Green, TEXT("Teleport Forward!"));
}

void AMyFirstCharacter::TeleportRight(const FInputActionValue& Instance)
{
	SetActorLocation(GetActorLocation() + GetActorRightVector() * 100.0f);

	static constexpr uint64 LogKey = 7;
	GEngine->AddOnScreenDebugMessage(LogKey, 2.5f, FColor::Green, TEXT("Teleport Right!"));
}

void AMyFirstCharacter::TeleportUp(const FInputActionValue& Instance)
{
	SetActorLocation(GetActorLocation() + GetActorUpVector() * 100.0f);

	static constexpr uint64 LogKey = 8;
	GEngine->AddOnScreenDebugMessage(LogKey, 2.5f, FColor::Green, TEXT("Teleport Up!"));
}

