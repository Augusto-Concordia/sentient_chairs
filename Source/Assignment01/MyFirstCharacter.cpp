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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetupPlayerInputComponent!"));

	// this gets the controller from the current actor (because any actor can have a controller, but it's not necessarily a player controller)
	const APlayerController* InstancePlayerController = Cast<APlayerController>(GetController());
	check(InstancePlayerController);

	// the below line is used mainly to safeguard against multiplayer scenarios where this might not be the local player
	if (const ULocalPlayer* LocalPlayer = InstancePlayerController->GetLocalPlayer())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetupPlayerInputComponent with LocalPlayer! ") + LocalPlayer->GetName());

		// gets the input subsystem for the local player (ECS-style)
		if(UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// adds the mapping context to the input subsystem, making sure it exists (safeguards against not assigning it in the editor)
			if (!Imc_Normal_Controls.IsNull())
			{
				InputSystem->AddMappingContext(Imc_Normal_Controls.LoadSynchronous(), 0);
			}
		}

		// assigns the input component to the player controller to make it respond to input
		UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		Input->BindAction(Ia_Jump, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveJump);
		Input->BindAction(Ia_Move_ForwardBackward, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveFb);
		Input->BindAction(Ia_Move_LeftRight, ETriggerEvent::Triggered, this, &AMyFirstCharacter::MoveLr);
		Input->BindAction(Ia_Look_UpDown, ETriggerEvent::Triggered, this, &AMyFirstCharacter::LookUd);
		Input->BindAction(Ia_Look_LeftRight, ETriggerEvent::Triggered, this, &AMyFirstCharacter::LookLr);
	}
}

void AMyFirstCharacter::MoveJump(const FInputActionValue& Instance)
{
	static uint64 JumpLogKey = 1;

	GEngine->AddOnScreenDebugMessage(JumpLogKey, 2.5f, FColor::Green, TEXT("Jumped! "));
}

void AMyFirstCharacter::MoveFb(const FInputActionValue& Instance)
{
	static uint64 MoveFbLogKey = 2;

	GEngine->AddOnScreenDebugMessage(MoveFbLogKey, 2.5f, FColor::Green, TEXT("Moved Forward/Backward!"));

	const float MoveFbValue = Instance.Get<float>();

	GEngine->AddOnScreenDebugMessage(MoveFbLogKey, 2.5f, FColor::Green, TEXT("Moved Forward/Backward! " + FString::SanitizeFloat(MoveFbValue)));
}

void AMyFirstCharacter::MoveLr(const FInputActionValue& Instance)
{
	static uint64 MoveLrLogKey = 3;

	const float MoveLrValue = Instance.Get<float>();

	GEngine->AddOnScreenDebugMessage(MoveLrLogKey, 2.5f, FColor::Green, TEXT("Moved Left/Right! " + FString::SanitizeFloat(MoveLrValue)));
}

void AMyFirstCharacter::LookUd(const FInputActionValue& instance)
{
	static uint64 LookUDLogKey = 4;

	const float LookUDValue = instance.Get<float>();

	GEngine->AddOnScreenDebugMessage(LookUDLogKey, 2.5f, FColor::Green, TEXT("Looked Up/Down! " + FString::SanitizeFloat(LookUDValue)));
}

void AMyFirstCharacter::LookLr(const FInputActionValue& instance)
{
	static uint64 LookLRLogKey = 5;

	const float LookLRValue = instance.Get<float>();

	GEngine->AddOnScreenDebugMessage(LookLRLogKey, 2.5f, FColor::Green, TEXT("Looked Left/Right! " + FString::SanitizeFloat(LookLRValue)));
}

