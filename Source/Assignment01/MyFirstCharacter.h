// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyFirstCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;

UCLASS()
class ASSIGNMENT01_API AMyFirstCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input|Settings")
	float HorizontalLookSensitivity = 2.0f;

	UPROPERTY(EditAnywhere, Category="Input|Settings")
	float VerticalLookSensitivity = 1.8f;

private:
	// camera component
	UPROPERTY(EditAnywhere, Category="Components|Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> Imc_Normal_Controls;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_Move_LeftRight;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_Move_ForwardBackward;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_Look_LeftRight;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_Look_UpDown;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_Jump;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_TeleportForward;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_TeleportRight;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	UInputAction* Ia_TeleportUp;

public:
	// Sets default values for this character's properties
	AMyFirstCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveJump(const FInputActionValue& Instance);
	void MoveFb(const FInputActionValue& Instance);
	void MoveLr(const FInputActionValue& Instance);
	void LookUd(const FInputActionValue& Instance);
	void LookLr(const FInputActionValue& Instance);
	void TeleportForward(const FInputActionValue& Instance);
	void TeleportRight(const FInputActionValue& Instance);
	void TeleportUp(const FInputActionValue& Instance);
};
